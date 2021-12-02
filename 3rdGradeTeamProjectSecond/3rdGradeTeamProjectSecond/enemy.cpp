//======================================================================================
//
// �G�l�~�[���� (enemy.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "enemy.h"
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
#include "fortress.h"
#include "item.h"

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CEnemy::CEnemy() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_SPIDER;
    m_fSpeed = 0.0f;
    m_fStrength = 1.0f;

    m_nCntTime = 0;
    m_bSquashedByFortress = true;
    m_bDetectPlayer = false;

    m_appearState = APPEAR_STATE_EXIST;
    m_bDeath = false;
    m_nIdx = 0;

    m_walkMotion = 0;
    m_attackMotion = 0;
    m_damageMotion = 0;
    m_deathMotion = 0;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ��ނ��Ƃ̏����ݒ�
    SetupInfoByType();

    // �L�����N�^�[�ɔ��f
    CCharacter::Init(pos, DEFAULT_SCALE);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Update(void)
{
    // �������Ԃ�����Ȃ�A�J�E���^��������
    CntDownTakeDamageTime();

    // �o�����Ă��Ȃ��Ȃ�A�o������
    if (m_appearState != APPEAR_STATE_EXIST)
    {
        Appear();
    }
    else
    {
        // ���[�V�������܂��͑ҋ@�ɂ���
        if (GetAnimation())
        {
            GetAnimation()->SetAnimation(0);
        }

        // �ʒu�A�ړ��ʁA������Ԃ��擾
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
        D3DXVECTOR3 myPos = DEFAULT_VECTOR;
        D3DXVECTOR3 move = DEFAULT_VECTOR;
        myPos = GetPos();
        move = GetMove();

        // 1F�O�̈ʒu���L��
        SetPosOld(myPos);

        // 1F�O�̈ړ��ʂ��L��
        SetMoveOld(move);

        // ���Ɖ��s���̈ړ��ʐ���
        ControlMove(move.x);
        ControlMove(move.z);

        // �ړ��ʂƈʒu�����т���
        myPos += move;

        // ���̏���
        CPlayer *pPlayer = CGame::GetPlayer(0);
        if (pPlayer)
        {
            // �v���C���[�̈ʒu
            D3DXVECTOR3 playerPos = pPlayer->GetPos();

            // �����v�Z
            const float SEARCH_DISTANCE = 1000.0f;
            if (IsInsideCircleXZ(myPos, playerPos, SEARCH_DISTANCE))
            {
                SetRotDestY(GetAngleToTargetXZ(playerPos, myPos));

                RotControl();

                m_nCntTime++;

                if (m_nCntTime >= 75)
                {
                    m_nCntTime = 0;
                    D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
                    //CBullet::Create(CBullet::TYPE_ARMY_ATTACK, GetPos(), moveAngle, m_fStrength);
                }
            }
        }

        // �ړ��v�ǂɓ��݂Ԃ���邩�ǂ���
        SquashedByFortress(myPos);

        // �ʒu�A�ړ��ʂ𔽉f
        SetPos(myPos);
        SetMove(move);

        // �A�j���[�V����������
        CCharacter::Update();

#ifdef COLLISION_TEST
        D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST

        // ���C�t���Ȃ��Ȃ��������
        float fLife = GetLife();
        if (fLife <= 0.0f)
        {
            CItem::Create(CItem::TYPE_DENTI_3, myPos, 5.0f);
            Uninit();
        }
    }
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Draw(void)
{
    // �o�����Ă���Ȃ�`��
    if (m_appearState == APPEAR_STATE_EXIST)
    {
        CCharacter::Draw();
    }
}

//=============================================================================
// ��������
// Author : �㓡�T�V��
//=============================================================================
CEnemy * CEnemy::Create(int type, D3DXVECTOR3 pos, float fStrength, int appearState)
{
    // �������m��
    CEnemy *pEnemy = NULL;
    pEnemy = new CEnemy;

    // ��Ɉ��������т��Ă���
    pEnemy->m_type = type;
    pEnemy->CCharacter::SetPos(pos);
    pEnemy->m_fStrength = fStrength;
    pEnemy->m_appearState = appearState;

    // ���Ɍ����𐳖ʂ�
    pEnemy->CCharacter::SetRot(DEFAULT_VECTOR);

    // ������
    pEnemy->Init(pos, DEFAULT_SCALE);

    // �C���f�b�N�X���擾
    pEnemy->m_nIdx = CGame::GetEnemyIdx();

    // �o�����Ă��Ȃ��Ȃ�A���G�ɂ��Ă���
    if (pEnemy->m_appearState != APPEAR_STATE_EXIST)
    {
        pEnemy->SetInvincible(true);
    }

    return pEnemy;
}

//=============================================================================
// �o������
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Appear(void)
{
    // �ʒu���擾
    D3DXVECTOR3 myPos = GetPos();
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;

    // �o����Ԃɂ���ďꍇ����
    switch (m_appearState)
    {
    case APPEAR_STATE_WAIT_FORTRESS:
    {
        // �ړ��v�ǂ��擾
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            targetPos = pFortress->GetPos();
        }
    }
        break;
    case APPEAR_STATE_WAIT_PLAYER:
    {
        // �v���C���[���擾
        float fKeepDistance = 99999.9f;         // ����
        bool bIsKeepDistanceChanged = false;    // �������X�V���ꂽ���ǂ���
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_PLAYER);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_PLAYER); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // �v���C���[�ɃL���X�g
                CPlayer *pPlayer = (CPlayer*)pScene;

                // �v���C���[���\������Ă���Ȃ�
                if (pPlayer->GetDisp())
                {
                    // �v���C���[�̈ʒu
                    D3DXVECTOR3 playerPos = pPlayer->GetPos();

                    // �����v�Z
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - playerPos.x), 2.0f) +
                        powf((myPos.z - playerPos.z), 2.0f));

                    // ���������L�[�v���Ă�����̂��߂��Ȃ�A�������X�V
                    if (fKeepDistance > fCurrentDistance)
                    {
                        fKeepDistance = fCurrentDistance;
                        targetPos = playerPos;
                        bIsKeepDistanceChanged = true;
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }

        // �������X�V����Ă��Ȃ��Ȃ�A�֐��𔲂���
        if (!bIsKeepDistanceChanged)
        {
            return;
        }
    }
    break;
    default:
        return;
        break;
    }

    // ���m�����ɓ�������A�������^�[�Q�b�g�ɕς��ďo���i�����Ŗ��G�����j
    const float SEARCH_DISTANCE = 2000.0f;
    if (IsInsideCircleXZ(myPos, targetPos, SEARCH_DISTANCE))
    {
        float fAngleToTarget = GetAngleToTargetXZ(targetPos, myPos);
        SetRotDestY(fAngleToTarget);
        SetRotY(fAngleToTarget);
        m_appearState = APPEAR_STATE_EXIST;
        SetInvincible(false);
    }
}

//=============================================================================
// �ړ��v�ǂɓ��݂Ԃ���邩�ǂ����̏���
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::SquashedByFortress(D3DXVECTOR3 myPos)
{
    if (m_bSquashedByFortress)
    {
        // �ړ��v�ǂ��擾
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            // �������Ă���Ȃ�
            D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
            if (IsCollisionCylinder(myPos, collisionSizeDefence, pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
            {
                // HP0��
                TakeDamage(FORTRESS_CRUSH_DAMAGE, myPos, pFortress->GetPos());
            }
        }
    }
}