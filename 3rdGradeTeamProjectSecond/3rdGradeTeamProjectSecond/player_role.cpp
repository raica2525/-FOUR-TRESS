//======================================================================================
//
// �v���C���[�̖������Ƃ̏��� (player_role.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "player.h"
#include "debug.h"
#include "enemy.h"
#include "animation.h"
#include "fortress.h"
#include "game.h"
#include "bullet.h"
#include "item.h"
#include "modelEffect.h"
#include "wave.h"

//========================================
// �}�N����`
//========================================

// �ߋ����U���̃t���O
typedef enum
{
    CLOSE_ATTACK_FLAG_NONE = 0,             // �Ȃ�
    CLOSE_ATTACK_FLAG_TAUNT = 0x001 << 1,   // ����
}CLOSE_ATTACK_FLAG;

//==========================
// �E�H�[���A�[�n��
//==========================
// ��{�_���[�W
#define WARRIOR_GROUND_BASE_DAMAGE 100.0f
// �����蔻�����
#define WARRIOR_GROUND_EMIT_DISTANCE 350.0f
#define WARRIOR_GROUND_RADIUS 450.0f
#define WARRIOR_GROUND_HEIGHT 300.0f
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define WARRIOR_GROUND_WHOLE_FRAME 30
#define WARRIOR_GROUND_START_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 10)
#define WARRIOR_GROUND_END_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 20)
// �d���t���[��
#define WARRIOR_GROUND_STOP_FRAME 5
// ���̑�
#define WARRIOR_GROUND_DUSH_SPEED 25.0f
#define WARRIOR_GROUND_COMBO_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 15)
#define WARRIOR_GROUND_SLIDE_SPEED 10.0f

//==========================
// �E�H�[���A�[��
//==========================
// ��{�_���[�W
#define WARRIOR_SKY_BASE_DAMAGE 300.0f
// �����蔻�����
#define WARRIOR_SKY_EMIT_DISTANCE -500.0f
#define WARRIOR_SKY_RADIUS 750.0f
#define WARRIOR_SKY_HEIGHT 500.0f
// �S�̃t���[���A�U�������t���[��
#define WARRIOR_SKY_WHOLE_FRAME 9999
#define WARRIOR_SKY_START_FRAME (WARRIOR_SKY_WHOLE_FRAME - 20)
// ���̑�
#define WARRIOR_SKY_UP_VALUE 20.0f
#define WARRIOR_SKY_CHANCE_FRAME 30

//==========================
// �n���^�[�n��
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define HUNTER_GROUND_WHOLE_FRAME 20
#define HUNTER_GROUND_FIRE_FRAME (HUNTER_GROUND_WHOLE_FRAME - 10)

//==========================
// �n���^�[��
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define HUNTER_SKY_WHOLE_FRAME 50
#define HUNTER_SKY_FIRE_FRAME (HUNTER_SKY_WHOLE_FRAME - 35)
// ���̑�
#define HUNTER_SKY_MOVE_LIMIT 0.5f
#define HUNTER_SKY_ONCE_SHOT 4
#define HUNTER_SKY_ANGLE_Y D3DXToRadian(50.0f)
#define HUNTER_SKY_TARGETING_FRAME (HUNTER_SKY_WHOLE_FRAME - 1)
// �ėp�p�����[�^�̓���
typedef enum
{
    PARAM_HUNTER_TARGET_POS_X = 0,
    PARAM_HUNTER_TARGET_POS_Y,
    PARAM_HUNTER_TARGET_POS_Z,
}PARAM_HUNTER;

//==========================
// �L�����A�[�n��
//==========================
// ��{�_���[�W
#define CARRIER_GROUND_BASE_DAMAGE 40.0f
// �����蔻�����
#define CARRIER_GROUND_RADIUS 450.0f
#define CARRIER_GROUND_HEIGHT 300.0f
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define CARRIER_GROUND_WHOLE_FRAME 70
#define CARRIER_GROUND_START_FRAME (CARRIER_GROUND_WHOLE_FRAME - 30)
#define CARRIER_GROUND_END_FRAME (CARRIER_GROUND_WHOLE_FRAME - 40)
// ���̑�
#define CARRIER_GROUND_DUSH_SPEED 150.0f
#define CARRIER_GROUND_CREATE_ENERGY 1.0f
#define CARRIER_GROUND_CREATE_AFTERIMAGE_FRAME 2
#define CARRIER_GROUND_AFTERIMAGE_COLOR D3DXCOLOR(0.694f, 0.298f, 1.0f, 1.0f)
#define CARRIER_GROUND_AFTERIMAGE_COLOR_CHANGE_RATE D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.04f)
#define CARRIER_GROUND_COMBO_FRAME (CARRIER_GROUND_WHOLE_FRAME - 50)
#define CARRIER_GROUND_SECOND_ATTACK_WHOLE_FRAME 40

//==========================
// �L�����A�[��
//==========================
// ��{�_���[�W
#define CARRIER_SKY_BASE_DAMAGE 150.0f
// �����蔻�����
#define CARRIER_SKY_EMIT_DISTANCE -200.0f
#define CARRIER_SKY_RADIUS 700.0f
#define CARRIER_SKY_HEIGHT 450.0f
// �S�̃t���[���A�U�������t���[��
#define CARRIER_SKY_WHOLE_FRAME 9999
#define CARRIER_SKY_START_ATTACK_FRAME (CARRIER_SKY_WHOLE_FRAME - 35)
#define CARRIER_SKY_START_WIND_FRAME (CARRIER_SKY_WHOLE_FRAME - 15)
// ���̑�
#define CARRIER_SKY_UP_VALUE 20.0f
#define CARRIER_SKY_CHANCE_FRAME 35

//==========================
// �^���N�n��1_���\��
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define TANK_GROUND1_WHOLE_FRAME 300
#define TANK_GROUND1_CREATE_SHIELD_FRAME (TANK_GROUND1_WHOLE_FRAME - 20)
// ���̑�
#define TANK_GROUND1_WALK_SPEED 8.5f
#define TANK_GROUND1_LV2 3
#define TANK_GROUND1_LV3 10
// �ėp�p�����[�^�̓���
typedef enum
{
    PARAM_TANK_GUARD_WIDTH = 0,
}PARAM_TANK;

//==========================
// �^���N�n��2_�����e
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define TANK_GROUND2_WHOLE_FRAME 45
#define TANK_GROUND2_FIRE_FRAME (TANK_GROUND2_WHOLE_FRAME - 25)

//==========================
// �^���N��
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define TANK_SKY_WHOLE_FRAME 80
#define TANK_SKY_START_FRAME (TANK_SKY_WHOLE_FRAME - 20)
#define TANK_SKY_END_FRAME (TANK_SKY_WHOLE_FRAME - 60)
// �����蔻�����
#define TANK_SKY_RADIUS 7500.0f
#define TANK_SKY_HEIGHT 500.0f

//==========================
// �q�[���[�n��
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define HEALER_GROUND_WHOLE_FRAME 60
#define HEALER_GROUND_FIRE_FRAME (HEALER_GROUND_WHOLE_FRAME - 30)
#define HEALER_GROUND_BASE_DAMAGE 40.0f

//==========================
// �q�[���[��
//==========================
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define HEALER_SKY_WHOLE_FRAME 90
#define HEALER_SKY_FIRE_FRAME (HEALER_SKY_WHOLE_FRAME - 45)

//=============================================================================
// �U���X�V����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AttackUpdate(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // �������Ă��Ȃ��Ȃ�
    if (GetDamageState() == DAMAGE_STATE_NONE)
    {
        // �g���Z�ɂ���ď������قȂ�
        switch (m_attackState)
        {
        case ATTACK_STATE_WARRIOR_GROUND1:
            AtkWarriorGround1(playerPos);
            break;
        case ATTACK_STATE_WARRIOR_GROUND2:
            AtkWarriorGround2(playerPos);
            break;
        case ATTACK_STATE_WARRIOR_SKY:
            AtkWarriorSky(playerPos, move);
            break;
        case ATTACK_STATE_HUNTER_GROUND:
            AtkHunterGround(playerPos);
            break;
        case ATTACK_STATE_HUNTER_SKY:
            AtkHunterSky(playerPos, move);
            break;
        case ATTACK_STATE_CARRIER_GROUND1:
            AtkCarrierGround1(playerPos);
            break;
        case ATTACK_STATE_CARRIER_GROUND2:
            AtkCarrierGround2(playerPos);
            break;
        case ATTACK_STATE_CARRIER_SKY:
            AtkCarrierSky(playerPos, move);
            break;
        case ATTACK_STATE_TANK_GROUND1:
            AtkTankGround1(playerPos);
            break;
        case ATTACK_STATE_TANK_GROUND2:
            AtkTankGround2(playerPos);
            break;
        case ATTACK_STATE_TANK_SKY:
            AtkTankSky(playerPos, move);
            break;
        case ATTACK_STATE_SIT_DOWN:
            AtkSitDown(playerPos, move);
            break;
        case ATTACK_STATE_HEALER_GROUND:
            AtkHealerGround(playerPos);
            break;
        case ATTACK_STATE_HEALER_SKY:
            AtkHealerSky(playerPos, move);
            break;
        }
    }
}

//=============================================================================
// �U����������
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AttackGenerator(void)
{
    // �������Ă��Ȃ���Ԃ��A�U�����łȂ��Ȃ�
    if (GetDamageState() == DAMAGE_STATE_NONE && m_attackState == ATTACK_STATE_NONE)
    {
        // �n��ɂ���Ȃ�
        if (m_bGround)
        {
            // �ʏ�U���{�^������������A�e�����ɂ���Ďg���U����ς���
            if (m_controlInput.bTriggerX)
            {
                switch (m_role)
                {
                case ROLE_WARRIOR:
                    m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
                    break;
                case ROLE_CARRIER:
                    m_nCntAttackTime = CARRIER_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_CARRIER_GROUND1;
                    break;
                case ROLE_TANK:
                    m_nCntAttackTime = TANK_GROUND1_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_TANK_GROUND1;
                    break;
                case ROLE_HEALER:
                    m_nCntAttackTime = HEALER_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HEALER_GROUND;
                    break;
                }
            }
            else if (m_controlInput.bPressX)
            {
                // �A���U���n
                switch (m_role)
                {
                case ROLE_HUNTER:
                    m_nCntAttackTime = HUNTER_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HUNTER_GROUND;
                    break;
                }
            }
            else if (m_controlInput.bTriggerB)
            {
                // �ړ��v�ǂɏ��
                RideFortress();
            }
        }
        else
        {
            // �ʏ�U���{�^������������A�e�����ɂ���Ďg���U����ς���
            if (m_controlInput.bTriggerX)
            {
                switch (m_role)
                {
                case ROLE_WARRIOR:
                    m_nCntAttackTime = WARRIOR_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_WARRIOR_SKY;
                    break;
                case ROLE_HUNTER:
                    m_nCntAttackTime = HUNTER_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HUNTER_SKY;
                    break;
                case ROLE_CARRIER:
                    m_nCntAttackTime = CARRIER_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_CARRIER_SKY;
                    break;
                case ROLE_TANK:
                    m_nCntAttackTime = TANK_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_TANK_SKY;
                    break;
                case ROLE_HEALER:
                    m_nCntAttackTime = HEALER_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HEALER_SKY;
                    break;
                }
            }
            else if (m_controlInput.bTriggerB)
            {
                // �ړ��v�ǂɏ��
                RideFortress();
            }
        }
    }
}

//=============================================================================
// �U�����[�V�����̊Ǘ�
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AttackMotion(void)
{
    // �U����Ԃɉ����āA���[�V���������߂�
    switch (m_attackState)
    {
    case ATTACK_STATE_WARRIOR_GROUND1:
        GetAnimation()->SetAnimation(ANIM_WARRIOR_GROUND1);
        break;
    case ATTACK_STATE_WARRIOR_GROUND2:
        GetAnimation()->SetAnimation(ANIM_WARRIOR_GROUND2);
        break;
    case ATTACK_STATE_WARRIOR_SKY:
        GetAnimation()->SetAnimation(ANIM_WARRIOR_SKY);
        break;
    case ATTACK_STATE_HUNTER_GROUND:
        GetAnimation()->SetAnimation(ANIM_HUNTER_GROUND);
        break;
    case ATTACK_STATE_HUNTER_SKY:
        GetAnimation()->SetAnimation(ANIM_HUNTER_SKY);
        break;
    case ATTACK_STATE_CARRIER_GROUND1:
        GetAnimation()->SetAnimation(ANIM_CARRIER_GROUND);
        break;
    case ATTACK_STATE_CARRIER_GROUND2:
        GetAnimation()->SetAnimation(ANIM_CARRIER_GROUND);
        break;
    case ATTACK_STATE_CARRIER_SKY:
        GetAnimation()->SetAnimation(ANIM_CARRIER_SKY);
        break;
    case ATTACK_STATE_TANK_GROUND1:
        GetAnimation()->SetAnimation(ANIM_TANK_GROUND1);
        break;
    case ATTACK_STATE_TANK_GROUND2:
        GetAnimation()->SetAnimation(ANIM_TANK_GROUND2);
        break;
    case ATTACK_STATE_TANK_SKY:
        GetAnimation()->SetAnimation(ANIM_TANK_SKY);
        break;
    case ATTACK_STATE_HEALER_GROUND:
        GetAnimation()->SetAnimation(ANIM_HEALER_GROUND);
        break;
    case ATTACK_STATE_HEALER_SKY:
        GetAnimation()->SetAnimation(ANIM_HEALER_SKY);
        break;
    case ATTACK_STATE_SIT_DOWN:
        GetAnimation()->SetAnimation(ANIM_SIT_DOWN);
        break;
    }
}

//=============================================================================
// �ߐڍU���������������ǂ����̃`�F�b�N
// Author : �㓡�T�V��
//=============================================================================
bool CPlayer::IsHitCloseRangeAttack(D3DXVECTOR3 playerPos, D3DXVECTOR3 attackPos, D3DXVECTOR2 attackSize, float fPower, int flag)
{
    // �h�䓖���蔻��̑傫�����擾
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

    // �����������ǂ���
    bool bHit = false;

    // �G�Ƃ̓����蔻��
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
    {
        // ���g������Ȃ�
        if (pScene)
        {
            // ���̃V�[�����L��
            CScene*pNextScene = pScene->GetNextScene();

            // �G�ɃL���X�g
            CEnemy *pEnemy = (CEnemy*)pScene;

            // �o�����Ă��Ȃ��Ȃ�A����
            if (pEnemy->GetAppearState() != CEnemy::APPEAR_STATE_EXIST)
            {
                // ���̃V�[���ɂ���
                pScene = pNextScene;
                continue;
            }

            // �G�̃C���f�b�N�X���擾
            int nIdx = pEnemy->GetIdx();
            if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
            {
                continue;
            }

            // ���i�q�b�g���p�t���O��false�Ȃ�
            if (!m_abUseAvoidMultipleHits[nIdx])
            {
                // �������Ă���Ȃ�
                if (IsCollisionCylinder(attackPos, attackSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                {
                    // �����t���O������Ȃ�
                    if (IS_BITON(flag, CLOSE_ATTACK_FLAG_TAUNT))
                    {
                        // ������Ԃɂ���
                        pEnemy->DiscoveryTarget((CCharacter*)this);

                        // ��������
                        bHit = true;

                        // ���i�q�b�g���p�̃t���O��true��
                        m_abUseAvoidMultipleHits[nIdx] = true;
                    }
                    else
                    {
                        // �G�Ƀ_���[�W����������
                        if (pEnemy->TakeDamage(fPower, attackPos, playerPos, OBJTYPE_PLAYER))
                        {
                            // ��������
                            bHit = true;

                            // ���i�q�b�g���p�̃t���O��true��
                            m_abUseAvoidMultipleHits[nIdx] = true;
                        }
                    }
                }
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }

    return bHit;
}

//=============================================================================
// �ړ��v�ǂɏ�鏈��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::RideFortress(void)
{
    // �ړ��v�ǂ��擾
    CFortress *pFortress = CGame::GetFortress();
    if (pFortress)
    {
        // �N�������Ă��Ȃ��Ȃ�
        if (!pFortress->GetNowWhoRiding())
        {
            // �������Ă���Ȃ�
            if (IsCollisionCylinder(GetPos(), GetCollisionSizeDefence(), pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
            {
                // ����i�U�����Ԃ�ݒ肵�Ȃ����ƂŁA��莞�ԂōU�������Z�b�g����t���O�𗧂����Ȃ��j
                m_attackState = ATTACK_STATE_SIT_DOWN;
                pFortress->SetNowWhoRiding(true);
            }
        }
    }
}

//=============================================================================
// �ړ��v�ǂɍ����čU�����鏈��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkSitDown(D3DXVECTOR3 &playerPos, D3DXVECTOR3& move)
{
    // �ړ��v�ǂ��擾
    CFortress *pFortress = CGame::GetFortress();
    if (pFortress)
    {
        // ���g�̈ʒu���A���Ȃɂ���
        playerPos = pFortress->GetPartsPos(CFortress::PARTS_SEAT);

        // �ړ��ʂ�O�̂��߃��Z�b�g����
        move = DEFAULT_VECTOR;

        // ���������킹��
        SetRot(pFortress->GetRot());
    }

    // �d�͏���U��
    if (m_controlInput.bTriggerX)
    {
        if (pFortress)
        {
            pFortress->SetAttackPhase(true);
        }
    }
    else if (m_controlInput.bTriggerB)
    {
        // �U���t�F�[�Y���͍~����Ȃ�
        if (pFortress)
        {
            if (!pFortress->GetAttackPhase())
            {
                // �~��鏈���i�U����������Z�b�g�j
                ResetAttack();

                // �ړ��v�Ǒ��̍����Ă���t���O��߂�
                pFortress->SetNowWhoRiding(false);
            }
        }
        else
        {
            // �ړ��v�ǂ��Ȃ��Ȃ�A�����ō~���
            ResetAttack();
        }
    }
}

//=============================================================================
// �E�H�[���A�[�n��U��1
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkWarriorGround1(D3DXVECTOR3& playerPos)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= WARRIOR_GROUND_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND_END_FRAME)
    {
        // �ϐ��錾
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // �v���C���[�̌����Ă������
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                            // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                           // �U�������ʒu
        float fFinalPower = 0.0f;                                         // �ŏI�I�ȍU����
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND_EMIT_DISTANCE;  // �U����������
        const float ATTACK_RADIUS = WARRIOR_GROUND_RADIUS;                // �U���̑傫��
        const float ATTACK_HEIGHT = WARRIOR_GROUND_HEIGHT;                // �U���̍���
        const float BASE_DAMAGE = WARRIOR_GROUND_BASE_DAMAGE;             // ��{�_���[�W

        // �U�������ʒu�����炷
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // �U�������ʒu�����߂�
        attackPos = playerPos + slidePos;

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // �ړ��ł���
        if (m_controlInput.bTiltedLeftStick)
        {
            playerPos.x += sinf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
            playerPos.z += cosf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
        }

        // �O�i
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;

        // �����������ǂ���
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // �A���U���̔���
    if (m_nCntAttackTime <= WARRIOR_GROUND_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_WARRIOR_GROUND2;
        }
    }
}

//=============================================================================
// �E�H�[���A�[�n��U��2
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkWarriorGround2(D3DXVECTOR3& playerPos)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= WARRIOR_GROUND_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND_END_FRAME)
    {
        // �ϐ��錾
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // �v���C���[�̌����Ă������
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                            // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                           // �U�������ʒu
        float fFinalPower = 0.0f;                                         // �ŏI�I�ȍU����
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND_EMIT_DISTANCE;  // �U����������
        const float ATTACK_RADIUS = WARRIOR_GROUND_RADIUS;                // �U���̑傫��
        const float ATTACK_HEIGHT = WARRIOR_GROUND_HEIGHT;                // �U���̍���
        const float BASE_DAMAGE = WARRIOR_GROUND_BASE_DAMAGE;             // ��{�_���[�W

        // �U�������ʒu�����炷
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // �U�������ʒu�����߂�
        attackPos = playerPos + slidePos;

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // �ړ��ł���
        if (m_controlInput.bTiltedLeftStick)
        {
            playerPos.x += sinf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
            playerPos.z += cosf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
        }

        // �O�i
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;

        // �����������ǂ���
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // �A���U���̔���
    if (m_nCntAttackTime <= WARRIOR_GROUND_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
        }
    }
}

//=============================================================================
// �E�H�[���A�[�󒆍U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkWarriorSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= WARRIOR_SKY_START_FRAME &&
        m_nCntAttackTime > WARRIOR_SKY_CHANCE_FRAME)
    {
        // ���n������A�����������A�U���͏I��
        if (m_bGround)
        {
            m_nCntAttackTime = WARRIOR_SKY_CHANCE_FRAME;
        }
        // �h�䓖���蔻��̑傫�����擾
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

        // �ϐ��錾
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
        float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
        const float ATTACK_EMIT_DISTANCE = WARRIOR_SKY_EMIT_DISTANCE;      // �U����������
        const float ATTACK_RADIUS = WARRIOR_SKY_RADIUS;                    // �U���̑傫��
        const float ATTACK_HEIGHT = WARRIOR_SKY_HEIGHT;                    // �U���̍���
        const float BASE_DAMAGE = WARRIOR_SKY_BASE_DAMAGE;                 // ��{�_���[�W

        // �U�������ʒu�����炷
        slidePos.y += ATTACK_EMIT_DISTANCE;

        // �U�������ʒu�����߂�
        attackPos = playerPos + slidePos;

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // ����
        move.y -= WARRIOR_SKY_UP_VALUE;

        // �����������ǂ���
        IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower);

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > WARRIOR_SKY_START_FRAME)
    {
        playerPos.y += WARRIOR_SKY_UP_VALUE;
        move.y = WARRIOR_SKY_UP_VALUE;
    }
}

//=============================================================================
// �n���^�[�n��U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkHunterGround(D3DXVECTOR3& playerPos)
{
    // �U�������t���[��
    if (m_nCntAttackTime == HUNTER_GROUND_FIRE_FRAME)
    {
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_HUNTER_GROUND, GetPartsPos(PARTS_WEP), moveAngle, OBJTYPE_PLAYER);
    }
    else if (m_nCntAttackTime > HUNTER_GROUND_FIRE_FRAME)
    {
        // �L�����̌�����ς���P�\�t���[��
        SetRotDestY(m_controlInput.fPlayerAngle);
    }
}

//=============================================================================
// �n���^�[�󒆍U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkHunterSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // �U�������t���[��
    if (m_nCntAttackTime == HUNTER_SKY_FIRE_FRAME)
    {
        // ��x�ɕ����̖���A�ϓ��ɕ���
        for (int nCnt = 0; nCnt < HUNTER_SKY_ONCE_SHOT; nCnt++)
        {
            float fDigitAngle = (float)(nCnt + 1) * (D3DXToRadian(180.0f) / (float)(HUNTER_SKY_ONCE_SHOT + 1));
            float fAngleXZ = GetRot().y + fDigitAngle - D3DXToRadian(90.0f);
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(fAngleXZ), HUNTER_SKY_ANGLE_Y, -cosf(fAngleXZ));
            CBullet*pBullet = CBullet::Create(CBullet::TYPE_HUNTER_SKY, GetPartsPos(PARTS_WEP), moveAngle, OBJTYPE_PLAYER);
            D3DXVECTOR3 targetPos = D3DXVECTOR3(m_afParam[PARAM_HUNTER_TARGET_POS_X], m_afParam[PARAM_HUNTER_TARGET_POS_Y], m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
            pBullet->SetParam(0, m_afParam[PARAM_HUNTER_TARGET_POS_X]);
            pBullet->SetParam(1, m_afParam[PARAM_HUNTER_TARGET_POS_Y]);
            pBullet->SetParam(2, m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
        }
    }
    else if (m_nCntAttackTime > HUNTER_SKY_FIRE_FRAME)
    {
        // �ړ�����
        move.x *= HUNTER_SKY_MOVE_LIMIT;
        move.z *= HUNTER_SKY_MOVE_LIMIT;
        move.y = 0.0f;

        // �^�[�Q�b�g�̈ʒu�����߂�t���[��
        if (m_nCntAttackTime == HUNTER_SKY_TARGETING_FRAME)
        {
            // �ʒu��ۑ�
            D3DXVECTOR3 targetPos = CGame::GetPosToClosestEnemy(playerPos);
            m_afParam[PARAM_HUNTER_TARGET_POS_X] = targetPos.x;
            m_afParam[PARAM_HUNTER_TARGET_POS_Y] = targetPos.y;
            m_afParam[PARAM_HUNTER_TARGET_POS_Z] = targetPos.z;
            // �L�����̌������^�[�Q�b�g�̕���
            SetRotDestY(GetAngleToTargetXZ(targetPos, playerPos));
        }
    }
}

//=============================================================================
// �L�����A�[�n��U��1
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkCarrierGround1(D3DXVECTOR3& playerPos)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= CARRIER_GROUND_START_FRAME &&
        m_nCntAttackTime >= CARRIER_GROUND_END_FRAME)
    {
        // ���̍U�����͖��G
        SetInvincible(true);

        // �ϐ��錾
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // �v���C���[�̌����Ă������
        float fFinalPower = 0.0f;                                         // �ŏI�I�ȍU����
        const float ATTACK_RADIUS = CARRIER_GROUND_RADIUS;                // �U���̑傫��
        const float ATTACK_HEIGHT = CARRIER_GROUND_HEIGHT;                // �U���̍���
        const float BASE_DAMAGE = CARRIER_GROUND_BASE_DAMAGE;             // ��{�_���[�W
        D3DXVECTOR3 posOld = GetPosOld();

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // �O�i
        playerPos.x += -sinf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;

        // �c�����c��
        if (m_nCntAttackTime % CARRIER_GROUND_CREATE_AFTERIMAGE_FRAME == 0)
        {
            CModelEffect*pAfterimage = CModelEffect::Create(27, posOld, playerRot, CARRIER_GROUND_AFTERIMAGE_COLOR, CARRIER_GROUND_AFTERIMAGE_COLOR_CHANGE_RATE, true);
            pAfterimage->SetAdditiveSynthesis();
        }

        // �����������ǂ���
        if (IsHitCloseRangeAttack(playerPos, playerPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            CItem::Create(CItem::TYPE_DENTI_5, posOld, CARRIER_GROUND_CREATE_ENERGY);
        }

#ifdef COLLISION_TEST
        CDebug::Create(playerPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > CARRIER_GROUND_START_FRAME)
    {
        // �L�����̌�����ς���P�\�t���[��
        SetRotDestY(m_controlInput.fPlayerAngle);
    }

    // �A���U���̔���
    if (m_nCntAttackTime <= CARRIER_GROUND_COMBO_FRAME)
    {
        // ���X�e�B�b�N���X���Ă���Ȃ�A��
        if (m_controlInput.bTiltedLeftStick)
        {
            ResetAttack();
            m_nCntAttackTime = CARRIER_GROUND_SECOND_ATTACK_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_CARRIER_GROUND2;
            SetRotY(m_controlInput.fPlayerAngle);
            SetRotDestY(m_controlInput.fPlayerAngle);
        }
    }
}

//=============================================================================
// �L�����A�[�n��U��2
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkCarrierGround2(D3DXVECTOR3& playerPos)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime >= CARRIER_GROUND_END_FRAME)
    {
        // ���̍U�����͖��G
        SetInvincible(true);

        // �ϐ��錾
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // �v���C���[�̌����Ă������
        float fFinalPower = 0.0f;                                         // �ŏI�I�ȍU����
        const float ATTACK_RADIUS = CARRIER_GROUND_RADIUS;                // �U���̑傫��
        const float ATTACK_HEIGHT = CARRIER_GROUND_HEIGHT;                // �U���̍���
        const float BASE_DAMAGE = CARRIER_GROUND_BASE_DAMAGE;             // ��{�_���[�W
        D3DXVECTOR3 posOld = GetPosOld();

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // �O�i
        playerPos.x += -sinf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;

        // �c�����c��
        if (m_nCntAttackTime % CARRIER_GROUND_CREATE_AFTERIMAGE_FRAME == 0)
        {
            CModelEffect*pAfterimage = CModelEffect::Create(27, posOld, playerRot, CARRIER_GROUND_AFTERIMAGE_COLOR, CARRIER_GROUND_AFTERIMAGE_COLOR_CHANGE_RATE, true);
            pAfterimage->SetAdditiveSynthesis();
        }

        // �����������ǂ���
        if (IsHitCloseRangeAttack(playerPos, playerPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            CItem::Create(CItem::TYPE_DENTI_5, posOld, CARRIER_GROUND_CREATE_ENERGY);
        }

#ifdef COLLISION_TEST
        CDebug::Create(playerPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }
}

//=============================================================================
// �L�����A�[�󒆍U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkCarrierSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= CARRIER_SKY_START_ATTACK_FRAME &&
        m_nCntAttackTime > CARRIER_SKY_CHANCE_FRAME)
    {
        // ���n������A�����������A�U���͏I��
        if (m_bGround)
        {
            m_nCntAttackTime = CARRIER_SKY_CHANCE_FRAME;
        }
        // �h�䓖���蔻��̑傫�����擾
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

        // �ϐ��錾
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
        float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
        const float ATTACK_EMIT_DISTANCE = CARRIER_SKY_EMIT_DISTANCE;      // �U����������
        const float ATTACK_RADIUS = CARRIER_SKY_RADIUS;                    // �U���̑傫��
        const float ATTACK_HEIGHT = CARRIER_SKY_HEIGHT;                    // �U���̍���
        const float BASE_DAMAGE = CARRIER_SKY_BASE_DAMAGE;                 // ��{�_���[�W

        // �U�������ʒu�����炷
        slidePos.y += ATTACK_EMIT_DISTANCE;

        // �U�������ʒu�����߂�
        attackPos = playerPos + slidePos;

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // ����
        move.y -= CARRIER_SKY_UP_VALUE;

        // �����������ǂ���
        IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower);

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > CARRIER_SKY_START_ATTACK_FRAME)
    {
        playerPos.y += CARRIER_SKY_UP_VALUE;
        move.y = CARRIER_SKY_UP_VALUE;
        move.x = 0.0f;
        move.z = 0.0f;

        // �G�������񂹂�e�𐶐�
        if (m_nCntAttackTime == CARRIER_SKY_START_WIND_FRAME)
        {
            D3DXVECTOR3 windPos = D3DXVECTOR3(playerPos.x, 1.0f, playerPos.z);
            CBullet::Create(CBullet::TYPE_CARRIER_SKY, windPos, DEFAULT_VECTOR, OBJTYPE_PLAYER);
        }
    }
}

//=============================================================================
// �^���N�n��U��1_���\��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkTankGround1(D3DXVECTOR3& playerPos)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= TANK_GROUND1_CREATE_SHIELD_FRAME && m_nCntAttackTime > 1)
    {
        // �K�[�h��
        m_bUsingGuard = true;

        // �ړ��ł���
        if (m_controlInput.bTiltedLeftStick)
        {
            playerPos.x += sinf(m_controlInput.fLeftStickAngle)*TANK_GROUND1_WALK_SPEED;
            playerPos.z += cosf(m_controlInput.fLeftStickAngle)*TANK_GROUND1_WALK_SPEED;
        }

        // �ʏ�U���ŃL�����Z���\
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = TANK_GROUND2_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_TANK_GROUND2;
        }
    }
    else if (m_nCntAttackTime == 1)
    {
        ResetAttack();
        m_nCntAttackTime = TANK_GROUND2_WHOLE_FRAME;
        m_attackState = ATTACK_STATE_TANK_GROUND2;
    }
}

//=============================================================================
// �^���N�n��U��2_�����e
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkTankGround2(D3DXVECTOR3& playerPos)
{
    // �U�������t���[��
    if (m_nCntAttackTime == TANK_GROUND2_FIRE_FRAME)
    {
        // ���̍U�����͖��G
        SetInvincible(true);

        // ���ˊp�x�A�ʒu���擾
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        D3DXVECTOR3 collisionSize = GetCollisionSizeDefence();
        D3DXVECTOR3 firePos = playerPos + D3DXVECTOR3(0.0f, collisionSize.y / 2.0f, 0.0f);

        // �K�[�h�񐔂ɉ����āA���˂���^�C�v��ς���
        if (m_nCntGuards < TANK_GROUND1_LV2)
        {
            CBullet::Create(CBullet::TYPE_TANK_GROUND_LV1, firePos, moveAngle, OBJTYPE_PLAYER);
        }
        else if (m_nCntGuards >= TANK_GROUND1_LV2 && m_nCntGuards < TANK_GROUND1_LV3)
        {
            CBullet::Create(CBullet::TYPE_TANK_GROUND_LV2, firePos, moveAngle, OBJTYPE_PLAYER);
        }
        else if (m_nCntGuards >= TANK_GROUND1_LV3)
        {
            CBullet::Create(CBullet::TYPE_TANK_GROUND_LV3, firePos, moveAngle, OBJTYPE_PLAYER);
        }

        // ���Ă��Ȃ�A�K�[�h�񐔂����Z�b�g
        m_nCntGuards = 0;
    }
    else if (m_nCntAttackTime > TANK_GROUND2_FIRE_FRAME)
    {
        // ���܂ł͖��G
        SetInvincible(true);
    }
}

//=============================================================================
// �^���N���K�[�h���Ƀ_���[�W���󂯂鏈��
// Author : �㓡�T�V��
//=============================================================================
bool CPlayer::TakeDamage_TankUsingGuard(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, int effectType)
{
    // �ʒu����_���[�W�ւ̌������擾
    D3DXVECTOR3 myPos = GetPos();
    float fAngleToDamagePos = D3DXToDegree(GetAngleToTargetXZ(damageOldPos, myPos));  // �_���[�W�ւ̊p�x
    if (fAngleToDamagePos < 0.0f)
    {
        fAngleToDamagePos += 360.0f;
    }

    // ���@�̌������擾
    D3DXVECTOR3 myRot = GetRot();
    float fPlayerAngle = D3DXToDegree(myRot.y);
    if (fPlayerAngle < 0.0f)
    {
        fPlayerAngle += 360.0f;
    }

    // �_���[�W�������K�[�h�͈͓��ɂ����܂��Ă���Ȃ�
    if (fAngleToDamagePos <= fPlayerAngle + (m_afParam[PARAM_TANK_GUARD_WIDTH] / 2.0f)&&
        fAngleToDamagePos >= fPlayerAngle - (m_afParam[PARAM_TANK_GUARD_WIDTH] / 2.0f))
    {
        // �K�[�h�񐔉��Z
        m_nCntGuards++;
        if (m_nCntGuards > TANK_GROUND1_LV3)
        {
            m_nCntGuards = TANK_GROUND1_LV3;
        }

        // �K�[�h�G�t�F�N�g����

        // �K�[�h�����������߁A�֐��𔲂���
        return true;
    }

    // �_���[�W���󂯂�
    return TakeDamage(fDamage, damagePos, damageOldPos, OBJTYPE_ENEMY, effectType);
}

//=============================================================================
// �^���N�󒆍U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkTankSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // �U�������t���[���ƏI���t���[�����l��
    if (m_nCntAttackTime <= TANK_SKY_START_FRAME &&
        m_nCntAttackTime >= TANK_SKY_END_FRAME)
    {
        // �����G�t�F�N�g
        if (m_nCntAttackTime == TANK_SKY_START_FRAME)
        {
            CWave::Create(playerPos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));
        }

        // �ړ��ł��Ȃ�
        move = DEFAULT_VECTOR;

        // ���̍U�����͖��G
        SetInvincible(true);

        // �ϐ��錾
        const float ATTACK_RADIUS = TANK_SKY_RADIUS;    // �U���̑傫��
        const float ATTACK_HEIGHT = TANK_SKY_HEIGHT;    // �U���̍���
        int flag = 0;                                   // �ߐڍU���̃t���O
        D3DXVECTOR3 tauntPos = D3DXVECTOR3(playerPos.x, 0.0f, playerPos.z);

        // �����̓����蔻��
        BITON(flag, CLOSE_ATTACK_FLAG_TAUNT);
        IsHitCloseRangeAttack(tauntPos, tauntPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), 0.0f, flag);

#ifdef COLLISION_TEST
        CDebug::Create(tauntPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > CARRIER_GROUND_START_FRAME)
    {
        // �ړ��ł��Ȃ�
        move = DEFAULT_VECTOR;
    }
}

//=============================================================================
// �q�[���[�n��U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkHealerGround(D3DXVECTOR3& playerPos)
{
    // �U�������t���[��
    if (m_nCntAttackTime == HEALER_GROUND_FIRE_FRAME)
    {
        // ���ˊp�x�A�ʒu���擾
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        D3DXVECTOR3 collisionSize = GetCollisionSizeDefence();
        D3DXVECTOR3 firePos = playerPos + D3DXVECTOR3(0.0f, collisionSize.y / 2.0f, 0.0f);
        CBullet *pBullet = CBullet::Create(CBullet::TYPE_HEALER_GROUND, firePos, moveAngle, OBJTYPE_PLAYER);
        if (pBullet)
        {
            pBullet->SetDamage(HEALER_GROUND_BASE_DAMAGE);
        }
    }
    else if (m_nCntAttackTime > HEALER_GROUND_FIRE_FRAME)
    {
        // �L�����̌�����ς���P�\�t���[��
        SetRotDestY(m_controlInput.fPlayerAngle);
    }
}

//=============================================================================
// �q�[���[�󒆍U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkHealerSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // �U�������t���[��
    if (m_nCntAttackTime == HUNTER_SKY_FIRE_FRAME)
    {
        // ��x�ɕ����̖���A�ϓ��ɕ���
        for (int nCnt = 0; nCnt < HUNTER_SKY_ONCE_SHOT; nCnt++)
        {
            float fDigitAngle = (float)(nCnt + 1) * (D3DXToRadian(180.0f) / (float)(HUNTER_SKY_ONCE_SHOT + 1));
            float fAngleXZ = GetRot().y + fDigitAngle - D3DXToRadian(90.0f);
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(fAngleXZ), HUNTER_SKY_ANGLE_Y, -cosf(fAngleXZ));
            CBullet*pBullet = CBullet::Create(CBullet::TYPE_HUNTER_SKY, GetPartsPos(PARTS_WEP), moveAngle, OBJTYPE_PLAYER);
            D3DXVECTOR3 targetPos = D3DXVECTOR3(m_afParam[PARAM_HUNTER_TARGET_POS_X], m_afParam[PARAM_HUNTER_TARGET_POS_Y], m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
            pBullet->SetParam(0, m_afParam[PARAM_HUNTER_TARGET_POS_X]);
            pBullet->SetParam(1, m_afParam[PARAM_HUNTER_TARGET_POS_Y]);
            pBullet->SetParam(2, m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
        }
    }
    else if (m_nCntAttackTime > HUNTER_SKY_FIRE_FRAME)
    {
        // �ړ�����
        move.x *= HUNTER_SKY_MOVE_LIMIT;
        move.z *= HUNTER_SKY_MOVE_LIMIT;
        move.y = 0.0f;

        // �^�[�Q�b�g�̈ʒu�����߂�t���[��
        if (m_nCntAttackTime == HUNTER_SKY_TARGETING_FRAME)
        {
            // �ʒu��ۑ�
            D3DXVECTOR3 targetPos = CGame::GetPosToClosestEnemy(playerPos);
            m_afParam[PARAM_HUNTER_TARGET_POS_X] = targetPos.x;
            m_afParam[PARAM_HUNTER_TARGET_POS_Y] = targetPos.y;
            m_afParam[PARAM_HUNTER_TARGET_POS_Z] = targetPos.z;
            // �L�����̌������^�[�Q�b�g�̕���
            SetRotDestY(GetAngleToTargetXZ(targetPos, playerPos));
        }
    }
}