//======================================================================================
//
// �ړ��v�Ǐ��� (fortress.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "fortress.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "effect3d.h"
#include "modelEffect.h"
#include "debug.h"
#include "bullet.h"
#include "block.h"
#include "fade.h"
#include "camera.h"

//========================================
// �}�N����`
//========================================
// �K�v�`���[�W��
#define CHARGE_VALUE_LV1 50.0f
#define CHARGE_VALUE_LV2 100.0f
#define CHARGE_VALUE_LV3 150.0f

// ���˂܂ł̃`���[�W����
#define CHARGE_FIRE_FRAME_LV1 30
#define CHARGE_FIRE_FRAME_LV2 60
#define CHARGE_FIRE_FRAME_LV3 90

// �v���x
#define CHARGE_POINT_LV1 5
#define CHARGE_POINT_LV2 10
#define CHARGE_POINT_LV3 15

// �̗͎���
#define MAX_LIFE 3000.0f
#define SMOKE_EFFECT_LIFE 1000.0f

// �^�C���̉�]
#define TIRE_ROT_SPEED D3DXToRadian(1.0f)

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CFortress::CFortress() :CCharacter(OBJTYPE::OBJTYPE_FORTRESS)
{
    m_fSpeed = 0.0f;

    m_bSearchRoad = true;
    m_moveAngle = DEFAULT_VECTOR;
    m_pTargetRoad = NULL;
    m_bNowWhoRiding = false;

    m_fChargeValue = 150.0f;
    m_bAttackPhase = false;
    m_nCntTime = 0;

    m_bDisp = true;
    m_nWhoAttackPhase = 0;

    // �G�t�F�N�g
    for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
    {
        m_Effect[nCnt].type = NOT_EXIST;
        m_Effect[nCnt].interval = 1;
        m_Effect[nCnt].nCntTrail = 0;
    }
    m_fTireRotAngle = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CFortress::~CFortress()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CFortress::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �����ݒ�
    SetCollisionSizeDefence(D3DXVECTOR2(1450.0f, 1000.0f));
    m_fSpeed = 4.0f;    // �v�ύX
    SetUpLife(MAX_LIFE);
    SetTakeKnockBack(false);

    // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
    CCharacter::SetPartNum(PARTS_MAX);
    CCharacter::BindParts(PARTS_BODY, 55);
    CCharacter::BindParts(PARTS_CANNON_CENTER, 50);
    CCharacter::BindParts(PARTS_SEAT, 50);
    CCharacter::BindParts(PARTS_FIRE_POS, 50);
    CCharacter::BindParts(PARTS_TIRE_1, 64);
    CCharacter::BindParts(PARTS_TIRE_2, 64);
    CCharacter::BindParts(PARTS_TIRE_3, 64);
    CCharacter::BindParts(PARTS_TIRE_4, 64);
    CCharacter::SetDontUseAnimation();
    CCharacter::LoadModelData("./data/ANIMATION/motion_fortress.txt");

    // �L�����N�^�[�ɔ��f
    CCharacter::Init(pos, DEFAULT_SCALE);

    // �G�t�F�N�g�̐ݒ�
    // ��
    m_Effect[EFFECT_SMOKE].type = CEffectData::TYPE_SMOKE;                  // �G�t�F�N�g�̎��
    m_Effect[EFFECT_SMOKE].interval = 18;                                   // �G�t�F�N�g�̔������o
    m_Effect[EFFECT_LIGHTNING].type = CEffectData::TYPE_LIGHTNING_RANGE;    // �G�t�F�N�g�̎��
    m_Effect[EFFECT_LIGHTNING].interval = 20;                                // �G�t�F�N�g�̔������o
    m_Effect[EFFECT_LIGHTNING_CHARGE_0].interval = 30;                                  // �G�t�F�N�g�̔������o
    m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV1;    // �`���[�W���̓d�C�G�t�F�N�g(Lv�ɂ���ĕύX)
    m_Effect[EFFECT_LIGHTNING_CHARGE_1].type = CEffectData::TYPE_LIGHTNING_CHARGE_2;    // �`���[�WLv2�ȍ~�̌��̃G�t�F�N�g
    // �d���C����
    m_Effect[EFFECT_LIGHTNING_SETUP].type = CEffectData::TYPE_LIGHTNING_SETUP;          // �G�t�F�N�g�̎��
    m_Effect[EFFECT_LIGHTNING_SETUP].interval = 20;                                     // �G�t�F�N�g�̔������o

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CFortress::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CFortress::Update(void)
{
    // �������Ԃ�����Ȃ�A�J�E���^��������
    CntDownTakeDamageTime();

    // �ʒu���擾
    D3DXVECTOR3 myPos = GetPos();

    // ����T���Ă��邩�ǂ���
    SearchRoad(myPos);

    // �ړ��i�U���t�F�[�Y���͈ړ��ł��Ȃ��j
    if (!m_bAttackPhase)
    {
        myPos += m_moveAngle * m_fSpeed;
    }

    // �ʒu��ݒ�
    SetPos(myPos);

    // �^�C���̉�]
    m_fTireRotAngle -= TIRE_ROT_SPEED;
    if (m_fTireRotAngle > D3DX_PI)
    {
        m_fTireRotAngle -= D3DX_PI * 2.0f;
    }
    else if (m_fTireRotAngle < -D3DX_PI)
    {
        m_fTireRotAngle += D3DX_PI * 2.0f;
    }
    SetPartRotX(PARTS_TIRE_1, m_fTireRotAngle);
    SetPartRotX(PARTS_TIRE_2, m_fTireRotAngle);
    SetPartRotX(PARTS_TIRE_3, m_fTireRotAngle);
    SetPartRotX(PARTS_TIRE_4, m_fTireRotAngle);

    // �ǂɓ����������ǂ���
    if (!CollisionWall(myPos))
    {
        // �U���t�F�[�Y�̏���
        AttackPhase();
    }

    // �����𒲐�
    RotControl();

    // �A�j���[�V����������
    CCharacter::Update();

#ifdef COLLISION_TEST
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 65);
#endif // COLLISION_TEST

    if (m_fChargeValue >= CHARGE_VALUE_LV1
        &&m_fChargeValue < CHARGE_VALUE_LV2)//�d���@���łĂ��Ԃ̂Ƃ��d���G�t�F�N�g����(Lv.1)
    {
        if (m_Effect[EFFECT_LIGHTNING].type != NOT_EXIST)
        {
            m_Effect[EFFECT_LIGHTNING].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING].nCntTrail >= m_Effect[EFFECT_LIGHTNING].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//�C��̈ʒu���擾

                m_Effect[EFFECT_LIGHTNING].nCntTrail = 0;
                
                m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV1;// �G�t�F�N�g��Lv1�̂��̂ɕύX
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_0].type, lightningPos, lightningPos);
            }
        }
    }
    if (m_fChargeValue >= CHARGE_VALUE_LV2
        &&m_fChargeValue < CHARGE_VALUE_LV3)//�d���@���łĂ��Ԃ̂Ƃ��d���G�t�F�N�g����(Lv.2)
    {
        if (m_Effect[EFFECT_LIGHTNING].type != NOT_EXIST)
        {
            m_Effect[EFFECT_LIGHTNING].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING].nCntTrail >= m_Effect[EFFECT_LIGHTNING].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//�C��̈ʒu���擾

                m_Effect[EFFECT_LIGHTNING].nCntTrail = 0;
                m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV2;// �G�t�F�N�g��Lv2�̂��̂ɕύX
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_0].type, lightningPos, lightningPos);
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_1].type, lightningPos, lightningPos);
            }
        }
    }
    if (m_fChargeValue >= CHARGE_VALUE_LV3)//�d���@���łĂ��Ԃ̂Ƃ��d���G�t�F�N�g����(Lv.3)
    {
        if (m_Effect[EFFECT_LIGHTNING].type != NOT_EXIST)
        {
            m_Effect[EFFECT_LIGHTNING].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING].nCntTrail >= m_Effect[EFFECT_LIGHTNING].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//�C��̈ʒu���擾

                m_Effect[EFFECT_LIGHTNING].nCntTrail = 0;
                m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV3;// �G�t�F�N�g��Lv3�̂��̂ɕύX
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_0].type, lightningPos, lightningPos);
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_1].type, lightningPos, lightningPos);
            }
        }
    }
float fLife = GetLife();// �ړ��v�ǂ̗͎̑擾

    // ���C�t���Ȃ��Ȃ�����
    if (fLife <= 0.0f)
    {
        SetLife(0.0f);

        // �g���[�j���O�łȂ��Ȃ�
        if (CGame::GetType() != CGame::TYPE_TRAINING)
        {
            // �����ŁA�S�[���Q�[�g��j��ł��Ă���Ȃ�A���������D��

            // ���ɔ�\����
            m_bDisp = false;

            // �s�k��Ԃ�
            CGame::SetFinish(false);
        }
        else
        {
            // �g���[�j���O�ł͂���Ȃ�
            SetLife(MAX_LIFE);
            SetDisp(true);
        }
    }
    
    // HP���Ⴂ�Ƃ��ɉ��𔭐�������
    if (fLife <= SMOKE_EFFECT_LIFE)
    {
        if (m_Effect[EFFECT_SMOKE].type != NOT_EXIST)
        {
            m_Effect[EFFECT_SMOKE].nCntTrail++;
            if (m_Effect[EFFECT_SMOKE].nCntTrail >= m_Effect[EFFECT_SMOKE].interval)
            {
                m_Effect[EFFECT_SMOKE].nCntTrail = 0;
                D3DXVECTOR3 smokePos = myPos + D3DXVECTOR3(0.0f, GetCollisionSizeDefence().y, 0.0f);
                CEffect3D::Emit(m_Effect[EFFECT_SMOKE].type, smokePos, smokePos);
            }
        }
    }
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CFortress::Draw(void)
{
    if (m_bDisp)
    {
        CCharacter::Draw();
    }
}

//=============================================================================
// ��������
// Author : �㓡�T�V��
//=============================================================================
CFortress *CFortress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // �������m��
    CFortress *pFortress = NULL;
    pFortress = new CFortress;

    // ��Ɍ��т��Ă���
    pFortress->CCharacter::SetPos(pos);
    pFortress->CCharacter::SetRot(rot);

    // ������
    pFortress->Init(pos, DEFAULT_SCALE);

    return pFortress;
}

//=============================================================================
// �U�����Z�b�g����
// Author : �㓡�T�V��
//=============================================================================
void CFortress::ResetAttack(void)
{
    m_nCntTime = 0;
    m_fChargeValue = 0.0f;
    m_bAttackPhase = false;
}

//=============================================================================
// �`���[�W�ʉ��Z
// Author : �㓡�T�V��
//=============================================================================
void CFortress::AddChargeValue(const float fChargeValue)
{
    m_fChargeValue += fChargeValue;
    if (m_fChargeValue > CHARGE_VALUE_LV3)
    {
        m_fChargeValue = CHARGE_VALUE_LV3;
    }
}

//=============================================================================
// �v���C���[�̃��X�|�[���ʒu��Ԃ�����
// Author : �㓡�T�V��
//=============================================================================
D3DXVECTOR3 CFortress::GetPlayerSpawnPos(int nIndex)
{
    D3DXVECTOR3 returnPos = GetPos();
    D3DXVECTOR3 addPos = DEFAULT_VECTOR;

    switch (nIndex)
    {
    case PLAYER_1:
        addPos = D3DXVECTOR3(-850.0f, RESPAWN_HEIGHT, 850.0f);
        break;
    case PLAYER_2:
        addPos = D3DXVECTOR3(850.0f, RESPAWN_HEIGHT, 850.0f);
        break;
    case PLAYER_3:
        addPos = D3DXVECTOR3(-850.0f, RESPAWN_HEIGHT, -850.0f);
        break;
    case PLAYER_4:
        addPos = D3DXVECTOR3(850.0f, RESPAWN_HEIGHT, -850.0f);
        break;
    }

    returnPos += addPos;

    return returnPos;
}

//=============================================================================
// ����T������
// Author : �㓡�T�V��
//=============================================================================
void CFortress::SearchRoad(D3DXVECTOR3 myPos)
{
    if (m_bSearchRoad)
    {
        // ����T��
        float fKeepDistance = 999999.9f; // ����
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ROAD);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ROAD); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // ���ɃL���X�g
                CRoad *pRoad = (CRoad*)pScene;

                // �ʉ߂��Ă��Ȃ��Ȃ�
                if (!pRoad->GetPast())
                {
                    // ���̈ʒu
                    D3DXVECTOR3 roadPos = pRoad->GetPos();

                    // �����v�Z
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - roadPos.x), 2.0f) +
                        powf((myPos.z - roadPos.z), 2.0f));

                    // ���������L�[�v���Ă�����̂��߂��Ȃ�A�ړ��̌������X�V
                    if (fKeepDistance > fCurrentDistance)
                    {
                        fKeepDistance = fCurrentDistance;
                        m_pTargetRoad = pRoad;
                        float fAngleToRoad = GetAngleToTargetXZ(myPos, roadPos);
                        SetRotDestY(GetAngleToTargetXZ(roadPos, myPos));
                        m_moveAngle = D3DXVECTOR3(sinf(fAngleToRoad), 0.0f, cosf(fAngleToRoad));
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }

        // ���T���I��
        m_bSearchRoad = false;
    }
    else
    {
        // �ړI�̈ʒu�ɒB�����Ȃ�A���̓���T��
        if (m_pTargetRoad)
        {
            D3DXVECTOR3 targetRoadPos = m_pTargetRoad->GetPos();
            float fDistanceToTargetRoad = sqrtf(
                powf((myPos.x - targetRoadPos.x), 2.0f) +
                powf((myPos.z - targetRoadPos.z), 2.0f));
            const float SEARCH_NEXT_ROAD_DISTANCE = 25.0f;
            if (fDistanceToTargetRoad < SEARCH_NEXT_ROAD_DISTANCE)
            {
                m_bSearchRoad = true;
                m_pTargetRoad->SetPast(true);   // ����ʂ�߂������Ƃɂ���
            }
        }
    }
}

//=============================================================================
// �U���t�F�[�Y�̏���
// Author : �㓡�T�V��
//=============================================================================
void CFortress::AttackPhase(void)
{
    // �U���t�F�[�Y�ɂȂ��Ă���Ȃ�
    if (m_bAttackPhase)
    {
        // �����`���[�W�ʂ�Lv1�ɂ���B���Ă��Ȃ��Ȃ�A�֐��𔲂���
        if (m_fChargeValue < CHARGE_VALUE_LV1)
        {
            // �����ł܂��`���[�W����Ă��Ȃ��|��\������UI�𐶐�

            m_bAttackPhase = false;
            return;
        }

        // �J�E���^�����Z
        m_nCntTime++;

        // �`���[�W��
        if (m_nCntTime == 1)
        {
            CManager::SoundPlay(CSound::LABEL_SE_CHARGE_ELECTROMAGNETIC_CANNON);
        }

        // �`���[�W�܂ł����鎞��
        int nCntMaxTime = 0;
        if (m_fChargeValue >= CHARGE_VALUE_LV1 && m_fChargeValue < CHARGE_VALUE_LV2)
        {
            nCntMaxTime = CHARGE_FIRE_FRAME_LV1;
        }
        else if (m_fChargeValue >= CHARGE_VALUE_LV2 && m_fChargeValue < CHARGE_VALUE_LV3)
        {
            nCntMaxTime = CHARGE_FIRE_FRAME_LV2;
        }
        else if (m_fChargeValue >= CHARGE_VALUE_LV3)
        {
            nCntMaxTime = CHARGE_FIRE_FRAME_LV3;
        }

        // ���J�E���^�ŁA�U��
        if (m_nCntTime >= nCntMaxTime)
        {
            // �`���[�W�󋵂ɉ����ĕς���
            D3DXVECTOR3 firePos = GetPartsPos(PARTS_FIRE_POS);
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
            CBullet *pBullet = NULL;
            int nContributionPoint = 0;
            if (m_fChargeValue >= CHARGE_VALUE_LV1 && m_fChargeValue < CHARGE_VALUE_LV2)
            {
                // �J�����̐U��
                CManager::GetCamera()->CCamera::SetShake(400.0f);
                CManager::SoundPlay(CSound::LABEL_SE_ELECTROMAGNETIC_CANNON_Lv1);
                pBullet = CBullet::Create(CBullet::TYPE_THUNDER, GetPos(), DEFAULT_VECTOR, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV1;
            }
            else if (m_fChargeValue >= CHARGE_VALUE_LV2 && m_fChargeValue < CHARGE_VALUE_LV3)
            {
                // �J�����̐U��
                CManager::GetCamera()->CCamera::SetShake(500.0f);
                CManager::SoundPlay(CSound::LABEL_SE_ELECTROMAGNETIC_CANNON_Lv2);
                pBullet = CBullet::Create(CBullet::TYPE_RAILGUN_LV2, firePos, moveAngle, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV2;
            }
            else if (m_fChargeValue >= CHARGE_VALUE_LV3)
            {
                // �J�����̐U��
                CManager::GetCamera()->CCamera::SetShake(600.0f);
                CManager::SoundPlay(CSound::LABEL_SE_ELECTROMAGNETIC_CANNON_Lv2);
                pBullet = CBullet::Create(CBullet::TYPE_RAILGUN_LV3, firePos, moveAngle, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV3;
            }
            if (pBullet)
            {
                pBullet->SetWhoContribution(m_nWhoAttackPhase);
            }

            // �v���x�������������ł��グ��
            CGame::GetPlayer(m_nWhoAttackPhase)->GainContribution(nContributionPoint);

            // �U����Ԃ����Z�b�g
            ResetAttack();
        }
        else
        {
            // �U�������G�t�F�N�g�𔭐�
            m_Effect[EFFECT_LIGHTNING_SETUP].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING_SETUP].nCntTrail >= m_Effect[EFFECT_LIGHTNING_SETUP].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//�C��̈ʒu���擾
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_SETUP].type, lightningPos, lightningPos);
            }
        }
    }
}

//=============================================================================
// �ǂɓ����������ǂ����̏���
// Author : �㓡�T�V��
//=============================================================================
bool CFortress::CollisionWall(D3DXVECTOR3 myPos)
{
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
    {
        // ���g������Ȃ�
        if (pScene)
        {
            // ���̃V�[�����L��
            CScene*pNextScene = pScene->GetNextScene();

            // �u���b�N�ɃL���X�g
            CBlock *pBlock = (CBlock*)pScene;

            // �������Ă���Ȃ�
            D3DXVECTOR2 collisionSize = GetCollisionSizeDefence();
            D3DXVECTOR3 myCubeSize = D3DXVECTOR3(collisionSize.x, collisionSize.y, collisionSize.x);
            D3DXVECTOR3 blockPos = pBlock->GetPos();
            if (IsCollisionRectangle3D(&myPos, &blockPos,
                &myCubeSize, &pBlock->GetCollisionSize()))
            {
                // �v���_���[�W
                TakeDamage(FORTRESS_CRUSH_DAMAGE, myPos, blockPos, OBJTYPE_BLOCK);
                return true;
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }

    return false;
}
