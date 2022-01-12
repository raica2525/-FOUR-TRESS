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

//========================================
// �}�N����`
//========================================
// ��{���S���v���x
#define DEFAULT_DEATH_CONTRIBUTION 1

// �o����������
#define APPEAR_WAIT_FRAME 30    // ���t���[���Ɉ�񌟒m���邩�̑ҋ@�t���[��

// ���˂܂ł̃`���[�W����
#define CHARGE_FIRE_FRAME 90

// ���񂪏I���J�E���^
#define PATROL_COUNT_MAX 180
#define PATROL_COUNT_MIN 60

// �ҋ@���I���J�E���^
#define WAIT_COUNT_AFTER_PATROL 30
#define WAIT_COUNT_AFTER_DISCOVERY 20
#define WAIT_COUNT_AFTER_DAMAGE 25

// �`���[�W�ʂɉ������A���Ƃ��d�r�̌����ڂ̕ω�
#define CHARGE_VALUE_DENTI_3 10.0f
#define CHARGE_VALUE_DENTI_1 50.0f

// �_���[�W���󂯂��ۂ̃t���[��
#define DAMAGE_FRAME 30
#define DEATH_FRAME 50

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CEnemy::CEnemy() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_SPIDER;
    m_fSpeed = 0.0f;
    m_fStrength = 1.0f;
    m_fChargeValue = NOT_EXIST_F;

    m_nCntTime = 0;
    m_bSquashedByFortress = true;

    m_appearState = APPEAR_STATE_EXIST;
    m_bDeath = false;
    m_baseState = BASE_STATE_WAIT;

    m_walkMotion = 0;
    m_attackMotion = 0;
    m_damageMotion = 0;
    m_deathMotion = 0;

    m_fSearchDistanceForAppear = 0.0f;
    m_patrolCentralPos = DEFAULT_VECTOR;
    m_moveAngle = DEFAULT_VECTOR;
    m_nPatrolDistance = 0;
    m_nCurrentStateEndFrame = 0;

    m_bWarning = false;
    m_fDiscoveryTargetDistance = 0.0f;
    m_pTarget = NULL;
    m_setAnimationThisFrame = 0;

    m_bUseCommonAtkFollow = false;
    m_targetTrend = TARGET_TREND_PLAYER;
    m_nAddScore = 1;
    m_nWhoContribution = NOT_EXIST;
    m_nDeathContributionPoint = DEFAULT_DEATH_CONTRIBUTION;

    m_Effect.type = NOT_EXIST;
    m_Effect.interval = 1;
    m_Effect.nCntTrail = 0;
 
    m_bDeathBySquashed = false;
    m_bAtkStartFlag = false;
    m_pModelEffect = NULL;
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
    // ���f���G�t�F�N�g���g���Ă������̂́A�����t���O�𗧂Ă�i�A���t�@�l��0���������������������p�j
    if (m_pModelEffect)
    {
        m_pModelEffect->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f));
    }

    CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Update(void)
{
    // �_���[�W�ɂ���čU�������Z�b�g����t���O�������Ă���Ȃ�
    if (GetResetAttackByDamage())
    {
        SetBaseState(BASE_STATE_DAMAGE, DAMAGE_FRAME);
        SetResetAttackByDamage(false);
    }

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
        m_setAnimationThisFrame = 0;

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

        // AI����
        switch (m_baseState)
        {
        case BASE_STATE_WAIT:
            WaitAI(myPos);
            break;
        case BASE_STATE_PATROL:
            PatrolAI(myPos);
            break;
        case BASE_STATE_ATTACK:
            AttackAI(myPos);
            break;
        case BASE_STATE_DAMAGE:
            DamageAI();
            break;
        case BASE_STATE_DEATH:
            m_nCntTime++;
            m_setAnimationThisFrame = m_deathMotion;
            break;
        }

        // �ړ��v�ǂɓ��݂Ԃ���邩�ǂ���
        SquashedByFortress(myPos);

        // �}�b�v����
        D3DXVECTOR3 myCubeSize = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CGame::MapLimit(myPos, GetPosOld(), myCubeSize);

        // �ʒu�A�ړ��ʂ𔽉f
        SetPos(myPos);
        SetMove(move);

        // �A�j���[�V����������
        if (GetAnimation())
        {
            GetAnimation()->SetAnimation(m_setAnimationThisFrame);
        }
        CCharacter::Update();

#ifdef COLLISION_TEST
        D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 65);
#endif // COLLISION_TEST

        // ���C�t���Ȃ��Ȃ��������
        float fLife = GetLife();
        if (fLife <= 0.0f)
        {
            // �̗͂̉���
            fLife = 0.0f;

            // �ړ��v�ǂɓ��݂Ԃ���Ȃ��Ȃ�
            m_bSquashedByFortress = false;

            // ���S���[�V�������Ȃ��Ȃ�
            if (m_deathMotion == 0)
            {
                // �����ɏ���
                DeathOneFrame(myPos);
            }
            else
            {
                // �ړ��v�ǂɓ��݂Ԃ��ꂽ�Ȃ�
                if (m_bDeathBySquashed)
                {
                    // �����ɏ���
                    DeathOneFrame(myPos);
                }
                else
                {
                    // ���S��ԉ��o
                    m_baseState = BASE_STATE_DEATH;

                    // ���J�E���^�ŁA����
                    if (m_nCntTime >= DEATH_FRAME)
                    {
                        DeathOneFrame(myPos);
                    }
                }
            }
        }
    }
}

//=============================================================================
// ���S��1F�����ʂ鏈��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::DeathOneFrame(D3DXVECTOR3 myPos)
{
    // ���X�g�q�b�g���v���C���[�Ȃ�A�A�C�e�����o���X�R�A�����Z
    OBJTYPE lastHit = GetLastHit();
    if (lastHit == OBJTYPE_PLAYER)
    {
        // �A�C�e��
        CItem::TYPE dentiType = CItem::TYPE_DENTI_5;
        if (m_fChargeValue >= CHARGE_VALUE_DENTI_3 && m_fChargeValue < CHARGE_VALUE_DENTI_1)
        {
            dentiType = CItem::TYPE_DENTI_3;
        }
        else if (m_fChargeValue >= CHARGE_VALUE_DENTI_1)
        {
            dentiType = CItem::TYPE_DENTI_1;
        }
        // �Œ�ۏ�
        if (m_fChargeValue < 1.0f)
        {
            m_fChargeValue = 1.0f;
        }
        CItem::Create(dentiType, myPos, m_fChargeValue);
        CEffect3D::Emit(CEffectData::TYPE_ENEMY_DESTROYING, myPos, myPos);

        // �X�R�A���Z
        CGame::AddScore(m_nAddScore);

        // �v���҂̃|�C���g���Z
        if (m_nWhoContribution != NOT_EXIST)
        {
            CGame::GetPlayer(m_nWhoContribution)->GainContribution(m_nDeathContributionPoint);
        }
    }
    else
    {
        // �J�~�J�[�̏ꍇ�A�v���C���[�ȊO�ɂ��ꂽ�甚���𐶂ݏo��
        if (m_type == TYPE_KAMIKAZE)
        {
            // �J�~�J�[������
            CManager::SoundPlay(CSound::LABEL_SE_EXPLOSION_KAMIKAZE);
            CBullet::Create(CBullet::TYPE_KAMIKAZE_EX, myPos, DEFAULT_VECTOR, OBJTYPE_ENEMY, m_fStrength);
            CEffect3D::Emit(CEffectData::TYPE_EXPLOSION_0, myPos, myPos);
            CEffect3D::Emit(CEffectData::TYPE_EXPLOSION_1, myPos, myPos);
            CEffect3D::Emit(CEffectData::TYPE_EXPLOSION_2, myPos, myPos);
        }
        else
        {// �J�~�J�[�ȊO�͒ʏ�̃G�t�F�N�g���o��
            CEffect3D::Emit(CEffectData::TYPE_ENEMY_DESTROYING, myPos, myPos);
        }
    }

    // �I������
    Uninit();
}

//=============================================================================
// �ď��񏈗�
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::RePatrol(void)
{
    // �v���C���[���S������Ă���Ȃ�A�ړ��v�ǂ�_���i�قڋl�݁j
    if (!CGame::GetDispAnyPlayer())
    {
        m_bWarning = true;
        m_pTarget = (CCharacter*)CGame::GetFortress();
        SetBaseState(BASE_STATE_ATTACK);
    }
    else
    {
        m_bWarning = false;
        SetBaseState(BASE_STATE_PATROL);
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
CEnemy *CEnemy::Create(int type, D3DXVECTOR3 pos, float fStrength, int appearState, float fChargeValue, float fSearchDistanceForAppear)
{
    // �������m��
    CEnemy *pEnemy = NULL;
    pEnemy = new CEnemy;

    // ��Ɉ��������т��Ă���
    pEnemy->m_type = type;
    pEnemy->CCharacter::SetPos(pos);
    pEnemy->m_fStrength = fStrength;
    pEnemy->m_appearState = appearState;
    pEnemy->m_fSearchDistanceForAppear = fSearchDistanceForAppear;
    pEnemy->m_patrolCentralPos = pos;

    // ���Ɍ����𐳖ʂ�
    pEnemy->CCharacter::SetRot(DEFAULT_VECTOR);

    // ������
    pEnemy->Init(pos, DEFAULT_SCALE);

    // �o�����Ă��Ȃ��Ȃ�A���G�ɂ��Ă���
    if (pEnemy->m_appearState != APPEAR_STATE_EXIST)
    {
        pEnemy->SetInvincible(true);
    }

    // �`���[�W�ʂ��f�t�H���g�ȊO�̒l�ɂ��Ă���Ȃ�A�����D��
    if (fChargeValue != NOT_EXIST_F)
    {
        pEnemy->m_fChargeValue = fChargeValue;
    }

    return pEnemy;
}

//=============================================================================
// �^�[�Q�b�g��������
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::DiscoveryTarget(CCharacter *pTarget)
{
    // �x�����łȂ�������
    if (!m_bWarning)
    {
        // �ҋ@��Ԃɂ���
        SetBaseState(BASE_STATE_WAIT, WAIT_COUNT_AFTER_DISCOVERY);
    }

    // �x������
    m_bWarning = true;

    // �^�[�Q�b�g�����т���
    if (pTarget)
    {
        m_pTarget = pTarget;
    }

    // �����ŁA�r�b�N���}�[�N�I�Ȃ��̂��o��

}

//=============================================================================
// �o������
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Appear(void)
{
    // ���t���[���Ɉ��̏����ɂ���
    m_nCntTime++;
    if (m_nCntTime < APPEAR_WAIT_FRAME)
    {
        return;
    }
    m_nCntTime = 0;

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
        float fKeepDistance = 999999.9f;        // ����
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
    if (IsInsideCircleXZ(myPos, targetPos, m_fSearchDistanceForAppear))
    {
        float fAngleToTarget = GetAngleToTargetXZ(targetPos, myPos);
        SetRotDestY(fAngleToTarget);
        SetRotY(fAngleToTarget);
        m_appearState = APPEAR_STATE_EXIST;
        SetInvincible(false);
        // �G�o���G�t�F�N�g
        CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_0, GetPos(), GetPos());
        CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_1, GetPos(), GetPos());
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
                TakeDamage(FORTRESS_CRUSH_DAMAGE, myPos, pFortress->GetPos(), OBJTYPE_FORTRESS);

                // �ړ��v�ǂɓ��݂Ԃ��ꂽ
                m_bDeathBySquashed = true;
            }
        }
    }
}

//=============================================================================
// ��{��Ԑݒ� ����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::SetBaseState(BASE_STATE nextBaseState, int nNextStateEndFrame)
{
    // ���S��Ԃ���́A�����Ȃ��Ԃɂ��Ȃ�Ȃ�
    if (m_baseState != BASE_STATE_DEATH)
    {
        // ��Ԃɂ�����郁���o�ϐ����Đݒ�
        m_baseState = nextBaseState;
        m_nCntTime = 0;
        m_bUseCommonAtkFollow = false;
        m_bAtkStartFlag = false;

        // �����̎�ނɂ���āA�Đݒ肷�����
        if (m_type == TYPE_PENPEN)
        {
            m_pModelEffect->SetUseDraw(false);
            SetCollisionSizeDefence(D3DXVECTOR2(350.0f, 350.0f));
            SetPartsDisp(PENPEN_PARTS_CUTTER_R, true);
            SetPartsDisp(PENPEN_PARTS_CUTTER_L, true);
        }

        // ���̏�Ԃɂ���āA�擾�������
        switch (nextBaseState)
        {
        case BASE_STATE_ATTACK:
        {
            // �x�����Ȃ�A�ΏۂƂ̋���������Ă���Ƃ��ɒǏ]�ɂ���
            if (m_bWarning)
            {
                // �^�[�Q�b�g�Ƃ̋����������Ȃ�A�Ǐ]
                if (m_pTarget)
                {
                    D3DXVECTOR3 myPos = GetPos();
                    D3DXVECTOR3 targetPos = m_pTarget->GetPos();
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - targetPos.x), 2.0f) +
                        powf((myPos.z - targetPos.z), 2.0f));
                    if (fCurrentDistance > m_fDiscoveryTargetDistance)
                    {
                        // ���݂̈ʒu�ƁA�ړI�n�܂ł̈ړ��p�x/���������߂�
                        float fDestAngle = atan2((myPos.x - targetPos.x), (myPos.z - targetPos.z));
                        m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
                        SetRotDestY(fDestAngle);
                        m_bUseCommonAtkFollow = true;   // ���ʂ̍U���t���O�𗧂Ă�
                    }
                }
            }
        }
        break;
        case BASE_STATE_PATROL:
        {
            // ���̖ړI�n�����߂�
            D3DXVECTOR3 destPos = DEFAULT_VECTOR;
            destPos.x = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.x;
            destPos.z = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.z;

            // ���݂̈ʒu�ƁA�ړI�n�܂ł̈ړ��p�x/���������߂�
            D3DXVECTOR3 myPos = GetPos();
            float fDestAngle = atan2((myPos.x - destPos.x), (myPos.z - destPos.z));
            m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
            SetRotDestY(fDestAngle);

            // ���񎞊Ԃ𓾂�
            m_nCurrentStateEndFrame = GetRandNum(PATROL_COUNT_MAX, PATROL_COUNT_MIN);
        }
        break;
        }

        // ���̏�Ԃ̏I�����Ԃ𓾂�
        if (nNextStateEndFrame != NOT_EXIST)
        {
            m_nCurrentStateEndFrame = nNextStateEndFrame;
        }
    }
}

//=============================================================================
// �ҋ@AI����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::WaitAI(D3DXVECTOR3& myPos)
{
    // �J�E���^�����Z
    m_nCntTime++;

    // �x�����Ȃ�A�������^�[�Q�b�g�ɒǏ]
    if (m_bWarning)
    {
        if (m_pTarget)
        {
            if (m_pTarget->GetDisp())
            {
                SetRotDestY(GetAngleToTargetXZ(m_pTarget->GetPos(), myPos));
                RotControl();
            }
            else
            {
                // �^�[�Q�b�g�����ꂽ�Ȃ�A�����Ɍx���������čď���
                RePatrol();
            }
        }
    }

    // �ҋ@���I���J�E���^�Ȃ�
    if (m_nCntTime >= m_nCurrentStateEndFrame)
    {
        // �x�����Ȃ�
        if (m_bWarning)
        {
            // �U����Ԃ�
            SetBaseState(BASE_STATE_ATTACK);
        }
        else
        {
            // �����Ԃ�
            SetBaseState(BASE_STATE_PATROL);
        }
    }
}

//=============================================================================
// ����AI����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::PatrolAI(D3DXVECTOR3& myPos)
{
    // �J�E���^�����Z
    m_nCntTime++;

    // ���񂪏I���J�E���^�Ȃ�
    if (m_nCntTime >= m_nCurrentStateEndFrame)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, WAIT_COUNT_AFTER_PATROL);
        return;
    }

    // �ʒu�Ɉړ��ʂ����т���
    myPos += m_moveAngle * m_fSpeed;

    // �^�[�Q�b�g��������
    float fKeepDistance = 0.0f;
    CCharacter *pTarget = NULL;
    switch (m_targetTrend)
    {
    case TARGET_TREND_PLAYER:
        pTarget = CGame::GetDistanceAndPointerToClosestPlayer(myPos, fKeepDistance);
        break;
    case TARGET_TREND_FORTRESS:
        pTarget = CGame::GetDistanceAndPointerToClosestFortress(myPos, fKeepDistance);
        break;
    case TARGET_TREND_PLAYER_AND_FORTRESS:
        pTarget = CGame::GetDistanceAndPointerToClosestPlayerOrFortress(myPos, fKeepDistance);
        break;
    }

    // �^�[�Q�b�g�Ƃ̋���������������菬�����Ȃ�A����������
    if (fKeepDistance <= m_fDiscoveryTargetDistance)
    {
        if (pTarget)
        {
            DiscoveryTarget(pTarget);
        }
    }

    // ���s���[�V������
    m_setAnimationThisFrame = m_walkMotion;

    // �����𒲐�
    RotControl();
}

//=============================================================================
// �U��AI����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::AttackAI(D3DXVECTOR3 &myPos)
{
    // �J�E���^���Z
    m_nCntTime++;

    // �Ǐ]����Ȃ�
    if (m_bUseCommonAtkFollow)
    {
        AtkCommonFollow(myPos);

        // �ړ����[�V������
        m_setAnimationThisFrame = m_walkMotion;
    }
    else
    {
        // �U�����[�V�����Ɂi��ނ��Ƃ̏����ŁA�U�����[�V�����ȊO�ɕς���ꍇ������̂ŁA��ɐݒ�j
        m_setAnimationThisFrame = m_attackMotion;

        // ��ނ��Ƃ̏���
        switch (m_type)
        {
        case TYPE_ARMY:
            AtkArmy(myPos);
            break;
        case TYPE_KAMIKAZE:
            AtkKamikaze(myPos);
            break;
        case TYPE_CANNON:
            AtkCannon(myPos);
            break;
        case TYPE_COMMANDER:
            AtkCommander(myPos);
            break;
		case TYPE_SHINIGAMI:
			AtkShinigami(myPos);
            break;
        case TYPE_PENPEN:
            AtkPenpen(myPos);
            break;
        }
    }
}

//=============================================================================
// �_���[�WAI����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::DamageAI(void)
{
    // �J�E���^�����Z
    m_nCntTime++;

    // �_���[�W���[�V�������I���J�E���^�Ȃ�
    if (m_nCntTime >= m_nCurrentStateEndFrame)
    {
        // �^�[�Q�b�g������Ȃ�U��AI��
        if (m_pTarget)
        {
            SetBaseState(BASE_STATE_ATTACK, WAIT_COUNT_AFTER_DAMAGE);
        }
        else
        {
            // �^�[�Q�b�g�����Ȃ��Ȃ珄���
            RePatrol();
        }
    }

    // �_���[�W���[�V������
    m_setAnimationThisFrame = m_damageMotion;
}