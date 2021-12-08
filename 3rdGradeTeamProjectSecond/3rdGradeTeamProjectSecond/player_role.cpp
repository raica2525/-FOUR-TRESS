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

//========================================
// �}�N����`
//========================================
//==========================
// �E�H�[���A�[�n��
//==========================
// ��{�_���[�W
#define WARRIOR_GROUND_BASE_DAMAGE 100.0f
// �����蔻�����
#define WARRIOR_GROUND_EMIT_DISTANCE 350.0f
#define WARRIOR_GROUND_RADIUS 450.0f
#define WARRIOR_GROUND_HEIGHT 200.0f
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define WARRIOR_GROUND_WHOLE_FRAME 30
#define WARRIOR_GROUND_START_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 10)
#define WARRIOR_GROUND_END_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 20)
// �d���t���[��
#define WARRIOR_GROUND_STOP_FRAME 5
// ���̑�
#define WARRIOR_GROUND_DUSH_SPEED 20.0f
#define WARRIOR_GROUND_COMBO_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 15)

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
#define HUNTER_SKY_WHOLE_FRAME 45
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
        case ATTACK_STATE_SIT_DOWN:
            AtkSitDown(playerPos, move);
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
                    m_attackState = ATTACK_STATE_CARRIER_GROUND;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_GROUND;
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
                    m_attackState = ATTACK_STATE_CARRIER_SKY;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_SKY;
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

            // �G�̃C���f�b�N�X���擾
            int nIdx = pEnemy->GetIdx();
            if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
            {
                return false;
            }

            // ���i�q�b�g���p�t���O��false�Ȃ�
            if (!m_abUseAvoidMultipleHits[nIdx])
            {
                // �������Ă���Ȃ�
                if (IsCollisionCylinder(attackPos, attackSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                {
                    // �G�Ƀ_���[�W����������
                    if (pEnemy->TakeDamage(fPower, attackPos, playerPos))
                    {
                        // ��������
                        bHit = true;

                        // ���i�q�b�g���p�̃t���O��true��
                        m_abUseAvoidMultipleHits[nIdx] = true;
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
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // �v���C���[�̌����Ă������
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
        float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
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
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // �v���C���[�̌����Ă������
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
        float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
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
// �n���^�[�n��U��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::AtkHunterGround(D3DXVECTOR3& playerPos)
{
    // �U�������t���[��
    if (m_nCntAttackTime == HUNTER_GROUND_FIRE_FRAME)
    {
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_HUNTER_GROUND, GetPartsPos(PARTS_WEP), moveAngle);
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
            CBullet*pBullet = CBullet::Create(CBullet::TYPE_HUNTER_SKY, GetPartsPos(PARTS_WEP), moveAngle);
            D3DXVECTOR3 targetPos = D3DXVECTOR3(m_afParam[PARAM_HUNTER_TARGET_POS_X], m_afParam[PARAM_HUNTER_TARGET_POS_Y], m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
            pBullet->SetTargetPos(targetPos);
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