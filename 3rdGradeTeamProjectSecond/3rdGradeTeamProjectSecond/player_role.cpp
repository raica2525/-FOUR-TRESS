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

//========================================
// �}�N����`
//========================================
//==========================
// �E�H�[���A�[�n��1
//==========================
// ��{�_���[�W
#define WARRIOR_GROUND1_BASE_DAMAGE 100.0f
// ������K�E�Q�[�W��
#define WARRIOR_GROUND1_GAIN_SP_GAUGE 100.0f
// �����蔻�����
#define WARRIOR_GROUND1_EMIT_DISTANCE 500.0f
#define WARRIOR_GROUND1_RADIUS 350.0f
#define WARRIOR_GROUND1_HEIGHT 150.0f
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define WARRIOR_GROUND1_WHOLE_FRAME 30
#define WARRIOR_GROUND1_START_FRAME (WARRIOR_GROUND1_WHOLE_FRAME - 5)
#define WARRIOR_GROUND1_END_FRAME (WARRIOR_GROUND1_WHOLE_FRAME - 15)
// �d���t���[��
#define WARRIOR_GROUND1_STOP_FRAME 3
// ���̑�
#define WARRIOR_GROUND1_DUSH_SPEED 20.0f
#define WARRIOR_GROUND1_COMBO_FRAME (WARRIOR_GROUND1_WHOLE_FRAME - 10)

//==========================
// �E�H�[���A�[�n��2
//==========================
// ��{�_���[�W
#define WARRIOR_GROUND2_BASE_DAMAGE 1000.0f
// ������K�E�Q�[�W��
#define WARRIOR_GROUND2_GAIN_SP_GAUGE 100.0f
// �����蔻��̑傫��
#define WARRIOR_GROUND2_EMIT_DISTANCE 500.0f
#define WARRIOR_GROUND2_RADIUS 350.0f
#define WARRIOR_GROUND2_HEIGHT 150.0f
// �S�̃t���[���A�U�������t���[���A�U���I���t���[��
#define WARRIOR_GROUND2_WHOLE_FRAME 30
#define WARRIOR_GROUND2_START_FRAME (WARRIOR_GROUND2_WHOLE_FRAME - 5)
#define WARRIOR_GROUND2_END_FRAME (WARRIOR_GROUND2_WHOLE_FRAME - 15)
// �d���t���[��
#define WARRIOR_GROUND2_STOP_FRAME 3
// ���̑�
#define WARRIOR_GROUND2_DUSH_SPEED 20.0f
#define WARRIOR_GROUND2_COMBO_FRAME (WARRIOR_GROUND2_WHOLE_FRAME - 10)

//==========================
// �E�H�[���A�[��
//==========================
// ��{�_���[�W
#define WARRIOR_SKY_BASE_DAMAGE 500.0f
// ������K�E�Q�[�W��
#define WARRIOR_SKY_GAIN_SP_GAUGE 100.0f
// �S�̃t���[���A�U�������t���[��
#define WARRIOR_SKY_WHOLE_FRAME 9999
#define WARRIOR_SKY_START_FRAME (WARRIOR_SKY_WHOLE_FRAME - 20)
// ���̑�
#define WARRIOR_SKY_UP_VALUE 20.0f
#define WARRIOR_SKY_CHANCE_FRAME 30

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
                    m_nCntAttackTime = WARRIOR_GROUND1_WHOLE_FRAME;
                    m_fNextGainSpGauge = WARRIOR_GROUND1_GAIN_SP_GAUGE;
                    m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
                    break;
                case ROLE_HUNTER:
                    m_attackState = ATTACK_STATE_HUNTER_GROUND;
                    break;
                case ROLE_CARRIER:
                    m_attackState = ATTACK_STATE_CARRIER_GROUND;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_GROUND;
                    break;
                }
            }
            else if (m_controlInput.bTriggerY)
            {
                // �K�E�Z�����g���Ȃ炱���ɏ���
            }
            else if (m_controlInput.bTriggerB)
            {
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
                    m_fNextGainSpGauge = WARRIOR_SKY_GAIN_SP_GAUGE;
                    m_attackState = ATTACK_STATE_WARRIOR_SKY;
                    break;
                case ROLE_HUNTER:
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
            else if (m_controlInput.bTriggerY)
            {
                // �K�E�Z�����g���Ȃ炱���ɏ���
            }
            else if (m_controlInput.bTriggerB)
            {
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
            if (nIdx < 0 || nIdx >= ENEMY_IDX_MAX)
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

                        // Sp�Q�[�W�㏸
                        GainSpGauge();
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
        // �������Ă���Ȃ�
        if (IsCollisionCylinder(GetPos(), GetCollisionSizeDefence(), pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
        {
            // ����i�U�����Ԃ�ݒ肵�Ȃ����ƂŁA��莞�ԂōU�������Z�b�g����t���O�𗧂����Ȃ��j
            m_attackState = ATTACK_STATE_SIT_DOWN;
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
    if (m_nCntAttackTime <= WARRIOR_GROUND1_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND1_END_FRAME)
    {
        // �ϐ��錾
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // �v���C���[�̌����Ă������
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
        float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND1_EMIT_DISTANCE;  // �U����������
        const float ATTACK_RADIUS = WARRIOR_GROUND1_RADIUS;                // �U���̑傫��
        const float ATTACK_HEIGHT = WARRIOR_GROUND1_HEIGHT;                // �U���̍���
        const float BASE_DAMAGE = WARRIOR_GROUND1_BASE_DAMAGE;             // ��{�_���[�W

        // �U�������ʒu�����炷
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // �U�������ʒu�����߂�
        attackPos = playerPos + slidePos;

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // �O�i
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND1_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND1_DUSH_SPEED;

        // �����������ǂ���
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND1_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // �A���U���̔���
    if (m_nCntAttackTime <= WARRIOR_GROUND1_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND2_WHOLE_FRAME;
            m_fNextGainSpGauge = WARRIOR_GROUND2_GAIN_SP_GAUGE;
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
    if (m_nCntAttackTime <= WARRIOR_GROUND2_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND2_END_FRAME)
    {
        // �ϐ��錾
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // �v���C���[�̌����Ă������
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
        float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND2_EMIT_DISTANCE;  // �U����������
        const float ATTACK_RADIUS = WARRIOR_GROUND2_RADIUS;                // �U���̑傫��
        const float ATTACK_HEIGHT = WARRIOR_GROUND2_HEIGHT;                // �U���̍���
        const float BASE_DAMAGE = WARRIOR_GROUND2_BASE_DAMAGE;             // ��{�_���[�W

                                                                           // �U�������ʒu�����炷
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // �U�������ʒu�����߂�
        attackPos = playerPos + slidePos;

        // �U���͂��l��
        fFinalPower = BASE_DAMAGE;

        // �O�i
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND2_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND2_DUSH_SPEED;

        // �����������ǂ���
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND2_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // �A���U���̔���
    if (m_nCntAttackTime <= WARRIOR_GROUND2_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND1_WHOLE_FRAME;
            m_fNextGainSpGauge = WARRIOR_GROUND1_GAIN_SP_GAUGE;
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
        else
        {
            // �h�䓖���蔻��̑傫�����擾
            D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

            // �ϐ��錾
            D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // �v���C���[�̌����Ă������
            D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ���炷�ʒu
            D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // �U�������ʒu
            float fFinalPower = 0.0f;                                          // �ŏI�I�ȍU����
            const float ATTACK_EMIT_DISTANCE = collisionSizeDefence.y * 1.5f;  // �U����������
            const float ATTACK_RADIUS = 500.0f;                                // �U���̑傫��
            const float ATTACK_HEIGHT = 200.0f;                                // �U���̍���
            const float BASE_DAMAGE = WARRIOR_SKY_BASE_DAMAGE;             // ��{�_���[�W

                                                                           // �U�������ʒu�����炷
            slidePos.y -= ATTACK_EMIT_DISTANCE;

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

    // �~��鏈��
    if (m_controlInput.bTriggerB)
    {
        ResetAttack();
    }
}