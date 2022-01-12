//===============================================
//
// AI���� (ai.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "ai.h"
#include "game.h"
#include "library.h"
#include "fortress.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �e���߂��Ƃ݂Ȃ��l
#define BULLET_CLOSE_VALUE 750.0f

// �U���̎˒�
#define ATTACK_RANGE_WARRIOR 750.0f
#define ATTACK_RANGE_HUNTER 3000.0f
#define ATTACK_RANGE_CARRIER 1250.0f
#define ATTACK_RANGE_TANK 1500.0f
#define ATTACK_RANGE_HEALER 2500.0f

// �W�I�擾�Ԋu
#define TARGETTING_INTERVAL_AI_LEVEL_1_MAX 30
#define TARGETTING_INTERVAL_AI_LEVEL_1_MIN 20
#define TARGETTING_INTERVAL_AI_LEVEL_2_MAX 20
#define TARGETTING_INTERVAL_AI_LEVEL_2_MIN 10
#define TARGETTING_INTERVAL_AI_LEVEL_3_MAX 10
#define TARGETTING_INTERVAL_AI_LEVEL_3_MIN 5

// �l������
#define THINKING_TIME_AI_LEVEL_1_MAX 45
#define THINKING_TIME_AI_LEVEL_1_MIN 30
#define THINKING_TIME_AI_LEVEL_2_MAX 20
#define THINKING_TIME_AI_LEVEL_2_MIN 10
#define THINKING_TIME_AI_LEVEL_3_MAX 5
#define THINKING_TIME_AI_LEVEL_3_MIN 1

// �R�A�̗D�揇��
#define CORE_PRIORITY_1 60
#define CORE_PRIORITY_2 30
#define CORE_PRIORITY_3 10

// ���P����
#define ASSAULT_TIME_AI_LEVEL_1_MAX 60
#define ASSAULT_TIME_AI_LEVEL_1_MIN 30
#define ASSAULT_TIME_AI_LEVEL_2_MAX 150
#define ASSAULT_TIME_AI_LEVEL_2_MIN 90
#define ASSAULT_TIME_AI_LEVEL_3_MAX 180
#define ASSAULT_TIME_AI_LEVEL_3_MIN 120

// �����鎞��
#define AVOID_TIME_AI_LEVEL_1_MAX 30
#define AVOID_TIME_AI_LEVEL_1_MIN 15
#define AVOID_TIME_AI_LEVEL_2_MAX 40
#define AVOID_TIME_AI_LEVEL_2_MIN 25
#define AVOID_TIME_AI_LEVEL_3_MAX 35
#define AVOID_TIME_AI_LEVEL_3_MIN 20

// �҂���
#define WAIT_TIME_AI_LEVEL_1_MAX 30
#define WAIT_TIME_AI_LEVEL_1_MIN 15
#define WAIT_TIME_AI_LEVEL_2_MAX 40
#define WAIT_TIME_AI_LEVEL_2_MIN 25
#define WAIT_TIME_AI_LEVEL_3_MAX 35
#define WAIT_TIME_AI_LEVEL_3_MIN 20

// �U�����ɑ_�����U�����ł��邩�ǂ����i100���̉��j
#define ATTACK_TARGET_AI_LEVEL_1 30
#define ATTACK_TARGET_AI_LEVEL_2 75
#define ATTACK_TARGET_AI_LEVEL_3 95

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CAi::CAi()
{
    m_buttonStateOld.bButtonA = false;
    m_buttonStateOld.bButtonX = false;
    m_buttonStateOld.bButtonB = false;
    m_buttonStateOld.bButtonR2 = false;
    m_pPlayer = NULL;

    m_core = CORE_THINKING;
    m_nCntActionTime = 0;

    m_targetPos = DEFAULT_VECTOR;
    m_nCntSearchTarget = 0;
    m_fAttackRange = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CAi::~CAi()
{
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CAi::Update(void)
{
    // �^�[�Q�b�g�ʒu�����߂鏈��
    if (m_nCntSearchTarget <= 0)
    {
        GetTargetPos();
    }
    else
    {
        m_nCntSearchTarget--;
    }

    // �ϐ��錾
    bool bCurrentButtonA = false;         // ���݂�A�{�^��
    bool bCurrentButtonX = false;         // ���݂�X�{�^��
    bool bCurrentButtonB = false;         // ���݂�B�{�^��
    bool bCurrentButtonR2 = false;        // ���݂�R2�{�^��

    // �ǉ�
    RushToTarget();
    bCurrentButtonA = JumpBecauseEnemyBulletClose();
    bCurrentButtonX = DecideAttack();

    //// �R�A���Ƃɏꍇ����
    //switch (m_core)
    //{
    //case CORE_THINKING:
    //    Thinking();
    //    DontMove(false);
    //    break;
    //case CORE_ASSAULT:
    //    AnotherAction();
    //    RushToBall();
    //    bCurrentButtonA = JumpBecauseBallUp();
    //    switch (m_pPlayer->GetAILevel())
    //    {
    //    case CPlayer::AI_LEVEL_1:
    //    case CPlayer::AI_LEVEL_2:
    //        bCurrentButtonX = DecideAttack();
    //        break;
    //    case CPlayer::AI_LEVEL_3:
    //        bCurrentButtonX = DecideAttack();
    //        break;
    //    }
    //    break;
    //case CORE_AVOID:
    //    AnotherAction();
    //    RunAwayFromBall();
    //    bCurrentButtonA = JumpBecauseBallMoveDown();
    //    bCurrentButtonX = DecideAttack();
    //    break;
    //case CORE_WAIT:
    //    AnotherAction();
    //    DontMove(true);
    //    bCurrentButtonX = DecideAttack();
    //    break;
    //}

    //==============================================================
    // �R���g���[���̑���ɒu��������
    // A�{�^���g���K�[
    if (bCurrentButtonA && !m_buttonStateOld.bButtonA)
    {
        m_pPlayer->GetControlInput()->bTriggerA = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bTriggerA = false;
    }

    // A�{�^���v���X
    if (bCurrentButtonA && m_buttonStateOld.bButtonA)
    {
        m_pPlayer->GetControlInput()->bPressA = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bPressA = false;
    }

    // X�{�^���g���K�[
    if (bCurrentButtonX && !m_buttonStateOld.bButtonX)
    {
        m_pPlayer->GetControlInput()->bTriggerX = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bTriggerX = false;
    }

    // X�{�^���v���X
    if (bCurrentButtonX && m_buttonStateOld.bButtonX)
    {
        m_pPlayer->GetControlInput()->bPressX = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bPressX = false;
    }

    // X�{�^�������[�X
    if (!bCurrentButtonX && m_buttonStateOld.bButtonX)
    {
        m_pPlayer->GetControlInput()->bReleaseX = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bReleaseX = false;
    }

    // B�{�^���g���K�[
    if (bCurrentButtonB && !m_buttonStateOld.bButtonB)
    {
        m_pPlayer->GetControlInput()->bTriggerB = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bTriggerB = false;
    }

    // R2�{�^���v���X
    if (bCurrentButtonR2 && m_buttonStateOld.bButtonR2)
    {
        m_pPlayer->GetControlInput()->bPressR2 = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bPressR2 = false;
    }
    //==============================================================

    // 1F�O�̏��Ƃ��ċL�����Ă���
    m_buttonStateOld.bButtonA = bCurrentButtonA;
    m_buttonStateOld.bButtonX = bCurrentButtonX;
    m_buttonStateOld.bButtonB = bCurrentButtonB;
    m_buttonStateOld.bButtonR2 = bCurrentButtonR2;
}

//=============================================================================
// �C���X�^���X��������
// Author : �㓡�T�V��
//=============================================================================
CAi * CAi::Create(CPlayer *pPlayer)
{
    // �C���X�^���X�̐���
    CAi *pAI;
    pAI = new CAi;

    pAI->m_pPlayer = pPlayer;
    pAI->GetThinkingTime();

    pAI->GetAttackAngle();

    return pAI;
}

//=============================================================================
// �l�����̏���
// Author : �㓡�T�V��
//=============================================================================
void CAi::Thinking(void)
{
    // ���Ԃ𐔂���
    m_nCntActionTime--;

    // ���J�E���^�ŁA���̃R�A�����߂�
    if (m_nCntActionTime < 0)
    {
        m_nCntActionTime = 0;

        // �����_���ɐ��������߂�
        int nRandNum = GetRandNum(100, 1);

        // ���̍U�����̗p���ꂽ���AAI���x���ɂ���Č��߂�
        if (nRandNum >= 1 && nRandNum <= CORE_PRIORITY_1)
        {
            switch (m_pPlayer->GetAILevel())
            {
            case CPlayer::AI_LEVEL_1:
                GetAvoidTime();
                break;
            case CPlayer::AI_LEVEL_2:
                GetWaitTime();
                break;
            case CPlayer::AI_LEVEL_3:
                //// ���݂̃v���C���[�l���ɂ���ďꍇ����
                //if (CGame::GetNumCurrentDispPlayer() > 2)
                //{
                //    GetAvoidTime();
                //}
                //else
                //{
                //    GetAssaultTime();
                //}
                GetAssaultTime();
                break;
            }
        }
        else if (nRandNum > CORE_PRIORITY_1 && nRandNum <= CORE_PRIORITY_1 + CORE_PRIORITY_2)
        {
            switch (m_pPlayer->GetAILevel())
            {
            case CPlayer::AI_LEVEL_1:
                GetAssaultTime();
                break;
            case CPlayer::AI_LEVEL_2:
                GetAssaultTime();
                break;
            case CPlayer::AI_LEVEL_3:
                GetWaitTime();
                break;
            }
        }
        else if (nRandNum > CORE_PRIORITY_1 + CORE_PRIORITY_2
            && nRandNum <= CORE_PRIORITY_1 + CORE_PRIORITY_2 + CORE_PRIORITY_3)
        {
            switch (m_pPlayer->GetAILevel())
            {
            case CPlayer::AI_LEVEL_1:
                GetWaitTime();
                break;
            case CPlayer::AI_LEVEL_2:
                GetAvoidTime();
                break;
            case CPlayer::AI_LEVEL_3:
                //// ���݂̃v���C���[�l���ɂ���ďꍇ����
                //if (CGame::GetNumCurrentDispPlayer() > 2)
                //{
                //    GetAssaultTime();
                //}
                //else
                //{
                //    GetAvoidTime();
                //}
                GetAvoidTime();
                break;
            }
        }
    }
}

//=============================================================================
// �l����ȊO�̍s����
// Author : �㓡�T�V��
//=============================================================================
void CAi::AnotherAction(void)
{
    // ���Ԃ𐔂���
    m_nCntActionTime--;

    // ���J�E���^�ŁA���l����
    if (m_nCntActionTime < 0)
    {
        GetThinkingTime();
    }
}

//=============================================================================
// �l�����Ԃ𓾂鏈��
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetThinkingTime(void)
{
    // �R�A���l������
    m_core = CORE_THINKING;

    // ���x���ɉ����čl�����Ԃ𓾂�
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(THINKING_TIME_AI_LEVEL_1_MAX, THINKING_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(THINKING_TIME_AI_LEVEL_2_MAX, THINKING_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(THINKING_TIME_AI_LEVEL_3_MAX, THINKING_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// ���P���Ԃ𓾂鏈��
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetAssaultTime(void)
{
    // �R�A�����P��
    m_core = CORE_ASSAULT;

    // ���x���ɉ����čl�����Ԃ𓾂�
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(ASSAULT_TIME_AI_LEVEL_1_MAX, ASSAULT_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(ASSAULT_TIME_AI_LEVEL_2_MAX, ASSAULT_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(ASSAULT_TIME_AI_LEVEL_3_MAX, ASSAULT_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// �����鎞�Ԃ𓾂鏈��
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetAvoidTime(void)
{
    // �R�A�������
    m_core = CORE_AVOID;

    // ���x���ɉ����čl�����Ԃ𓾂�
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(AVOID_TIME_AI_LEVEL_1_MAX, AVOID_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(AVOID_TIME_AI_LEVEL_2_MAX, AVOID_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(AVOID_TIME_AI_LEVEL_3_MAX, AVOID_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// �҂��Ԃ𓾂鏈��
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetWaitTime(void)
{
    // �R�A��ҋ@����
    m_core = CORE_WAIT;

    // ���x���ɉ����čl�����Ԃ𓾂�
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(WAIT_TIME_AI_LEVEL_1_MAX, WAIT_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(WAIT_TIME_AI_LEVEL_2_MAX, WAIT_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(WAIT_TIME_AI_LEVEL_3_MAX, WAIT_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// �ړ����Ȃ�����
// Author : �㓡�T�V��
//=============================================================================
void CAi::DontMove(bool bUseTurn)
{
    //m_pPlayer->GetControlInput()->bTiltedLeftStick = false;

    //// �ړ����Ȃ����x�ɓG��U������Ȃ�
    //if (bUseTurn)
    //{
    //    // �G�̂ق��������Ă��Ȃ��Ȃ炻���������
    //    if (!IsFacingBall())
    //    {
    //        // �{�[�����擾
    //        CBall* pBall = CGame::GetBall();
    //        float fAngle = GetAngleToTarget3D2D(m_pPlayer->GetPos(), pBall->GetPos());

    //        m_pPlayer->GetControlInput()->bTiltedLeftStick = true;
    //        m_pPlayer->GetControlInput()->fLeftStickAngle = fAngle;
    //    }
    //}
}

//=============================================================================
// �G�̕��������Ă��邩
// Author : �㓡�T�V��
//=============================================================================
bool CAi::IsFacingEnemy(void)
{
    //// �{�[�����擾
    //CBall* pBall = CGame::GetBall();

    //// �{�[���̂ق��������Ă��Ȃ�
    //if (pBall->GetPos().x > m_pPlayer->GetPos().x && m_pPlayer->GetRot().y == PLAYER_ROT_LEFT ||
    //    pBall->GetPos().x < m_pPlayer->GetPos().x && m_pPlayer->GetRot().y == PLAYER_ROT_RIGHT)
    //{
    //    return false;
    //}

    // �{�[���̕��������Ă���
    return true;
}

//=============================================================================
// �^�[�Q�b�g�ɋl�ߊ�鏈��
// Author : �㓡�T�V��
//=============================================================================
void CAi::RushToTarget(void)
{
    // �^�[�Q�b�g�ւ̊p�x���擾
    float fAngle = GetAngleToTargetXZ(m_pPlayer->GetPos(), m_targetPos);
    float fPlayerAngle = GetAngleToTargetXZ(m_targetPos, m_pPlayer->GetPos());

    m_pPlayer->GetControlInput()->bTiltedLeftStick = true;
    m_pPlayer->GetControlInput()->fLeftStickAngle = fAngle;
    m_pPlayer->GetControlInput()->fPlayerAngle = fPlayerAngle;
}

//=============================================================================
// �{�[�����瓦���鏈��
// Author : �㓡�T�V��
//=============================================================================
void CAi::RunAwayFromBall(void)
{
    //// �{�[�����擾
    //CBall* pBall = CGame::GetBall();
    //float fAngle = GetAngleToTarget3D2D(pBall->GetPos(), m_pPlayer->GetPos());

    //// �E�����Ɋp�x����
    //if (fAngle > D3DXToRadian(0.0f) && fAngle <= D3DXToRadian(180.0f))
    //{
    //    fAngle = D3DXToRadian(90.0f);
    //}
    //else
    //{
    //    fAngle = D3DXToRadian(-90.0f);
    //}

    //// �X�e�[�W�̉����̖񔼕��܂ŗ��ꂽ��A�����I�ɍl����i���x��3�͑҂��ɂ���j
    //float fDistance = GetDistance2D(m_pPlayer->GetPos(), CGame::GetBall()->GetPos());
    //if (fDistance >= CGame::GetMapLimit().fWidth - BALL_COLLISION_SIZE_SIDE)
    //{
    //    if (m_pPlayer->GetAILevel() == CPlayer::AI_LEVEL_3)
    //    {
    //        // ���펞�͑҂����ق�������
    //        GetWaitTime();

    //        // �����Ă�������ɓ��͂�����
    //        if (m_pPlayer->GetRot().y == PLAYER_ROT_LEFT)
    //        {
    //            fAngle = D3DXToRadian(-90.0f);
    //        }
    //        else if (m_pPlayer->GetRot().y == PLAYER_ROT_RIGHT)
    //        {
    //            fAngle = D3DXToRadian(90.0f);
    //        }
    //    }
    //    else
    //    {
    //        GetThinkingTime();
    //    }
    //}

    //// �v���C���[�̓��͂ɔ��f
    //m_pPlayer->GetControlInput()->bTiltedLeftStick = true;
    //m_pPlayer->GetControlInput()->fLeftStickAngle = fAngle;
}

//=============================================================================
// �G�̒e���߂�����W�����v���鏈��
// Author : �㓡�T�V��
//=============================================================================
bool CAi::JumpBecauseEnemyBulletClose(void)
{
    // �W�����v���邩�ǂ���
    bool bUseJump = false;

    // �G�̒e���߂��Ȃ�W�����v
    if (CGame::GetDistanceToClosestEnemyBullet(m_pPlayer->GetPos()) < BULLET_CLOSE_VALUE)
    {
        bUseJump = true;
    }

    // �n��ɂ��āA�W�����v�{�^���𒷉������悤�Ƃ��Ă���Ȃ�A����������
    if (m_pPlayer->GetGround() && m_buttonStateOld.bButtonA)
    {
        return false;
    }

    // �󒆂ɂ��āA�؋󂪏I�������Ȃ�A����������
    if (m_pPlayer->GetPressJumpTime() > PLAYER_JUMP_KEEP_FRAME)
    {
        return false;
    }

    return bUseJump;
}

//=============================================================================
// �{�[�������Ɉړ����Ă��Ă��邩��W�����v���鏈��
// Author : �㓡�T�V��
//=============================================================================
bool CAi::JumpBecauseBallMoveDown(void)
{
    // �W�����v���邩�ǂ���
    bool bUseJump = false;

    //// �{�[�����擾
    //CBall* pBall = CGame::GetBall();

    //// �{�[�������ɓ����Ă邩��
    //if (pBall->GetPosOld().y > pBall->GetPos().y)
    //{
    //    bUseJump = true;
    //}

    //// �n��ɂ��āA�W�����v�{�^���𒷉������悤�Ƃ��Ă���Ȃ�A����������
    //if (m_pPlayer->GetGround() && m_buttonStateOld.bButtonA)
    //{
    //    return false;
    //}

    //// �󒆂ɂ��āA�؋󂪏I�������Ȃ�A����������
    //if (m_pPlayer->GetPressJumpTime() > PLAYER_JUMP_KEEP_FRAME)
    //{
    //    return false;
    //}

    //// �{�[�����z�u����Ă��Ȃ��Ȃ�A�W�����v���Ȃ�
    //if (!pBall->GetDisp())
    //{
    //    return false;
    //}

    return bUseJump;
}

//=============================================================================
// ���߂���U�������邩�ǂ����̏���
// Author : �㓡�T�V��
//=============================================================================
bool CAi::DecideAttack(void)
{
    // ��{�I�ȍU�������邩�ǂ���
    bool bUseDecideAttack = false;

    // �U��������Ɣ��f���鋗��
    if (GetDistanceXZ(m_pPlayer->GetPos(), m_targetPos) <= m_fAttackRange)
    {
        bUseDecideAttack = true;
    }

    // �n���^�[�ȊO�́A�L�[�v���X�ł̍U�����Ȃ��i�^���N�͗v�ύX�j
    if (m_pPlayer->GetRole() != CPlayer::ROLE_HUNTER)
    {
        if (m_buttonStateOld.bButtonX)
        {
            return false;
        }
    }

    return bUseDecideAttack;
}

//=============================================================================
// �U�����ɂǂ̕����ɃX�e�B�b�N��|����|����
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetAttackAngle(void)
{
    //// �X�e�B�b�N��|���̂͊m��
    //m_pPlayer->GetControlInput()->bTiltedLeftStick = true;

    //// �����_���ɐ��������߂�
    //int nRandNum = GetRandNum(100, 1);
    //int nBorderNum = 0;

    //switch (m_pPlayer->GetAILevel())
    //{
    //case CPlayer::AI_LEVEL_1:
    //    nBorderNum = ATTACK_TARGET_AI_LEVEL_1;
    //    break;
    //case CPlayer::AI_LEVEL_2:
    //    nBorderNum = ATTACK_TARGET_AI_LEVEL_2;
    //    break;
    //case CPlayer::AI_LEVEL_3:
    //    nBorderNum = ATTACK_TARGET_AI_LEVEL_3;
    //    break;
    //}

    //// ���E�̒l�͈͓̔��Ȃ�A�߂��̓G��_�����p�x�ɓ|���i���x��3�������x���A�b�v�j
    //float fAttackAngle = 0.0f;
    //CBall* pBall = CGame::GetBall();
    //if (nRandNum >= 1 && nRandNum <= nBorderNum)
    //{
    //    switch (m_pPlayer->GetAILevel())
    //    {
    //    case CPlayer::AI_LEVEL_1:
    //    case CPlayer::AI_LEVEL_2:
    //        fAttackAngle = CGame::GetAngleToClosestPlayer(m_pPlayer->GetIdxCreate(), m_pPlayer->GetPos());   //�i�����ƑΏۃv���C���[�̊p�x�j
    //        break;
    //    case CPlayer::AI_LEVEL_3:
    //        // �ł��n�߂Ȃ�A�󒆂ƒn��ōU�����g��������
    //        if (m_pPlayer->GetStopTime() == 0)
    //        {
    //            if (m_pPlayer->GetGround())
    //            {
    //                // �X�C���O�i����͂łȂ�j
    //                fAttackAngle = D3DXToRadian(0.0f);
    //            }
    //            else
    //            {
    //                // �󒆂Ȃ�A�{�[���Ƃ̈ʒu�֌W�Ŏg���U����ς���
    //                if (pBall->GetPos().y > m_pPlayer->GetPos().y + m_pPlayer->GetCollisionSizeDeffence().y)
    //                {
    //                    // �X�}�b�V���i���������킹��j
    //                    if (pBall->GetPos().x > m_pPlayer->GetPos().x)
    //                    {
    //                        fAttackAngle = D3DXToRadian(90.0f);
    //                    }
    //                    else
    //                    {
    //                        fAttackAngle = D3DXToRadian(-90.0f);
    //                    }
    //                }
    //                else if (pBall->GetPos().y < m_pPlayer->GetPos().y)
    //                {
    //                    // �X�p�C�N
    //                    fAttackAngle = D3DXToRadian(180.0f);
    //                }
    //                else
    //                {
    //                    // �X�C���O�i����͂łȂ�j
    //                    fAttackAngle = D3DXToRadian(0.0f);
    //                }
    //            }
    //        }
    //        else if (m_pPlayer->GetStopTime() == 1)
    //        {
    //            // ��΂��Ƃ��́A�߂��̓G��_���i�{�[���ƑΏۃv���C���[�̊p�x�j
    //            fAttackAngle = GetAngleToTarget3D2D(pBall->GetPos(),
    //                CGame::GetPosToClosestPlayer(m_pPlayer->GetIdxCreate(), m_pPlayer->GetPos()));
    //        }
    //        break;
    //    }
    //}
    //else
    //{
    //    // �͈͊O�Ȃ�A�K���ɃX�e�B�b�N��|��
    //    fAttackAngle = float(rand() % 314) / 100 - float(rand() % 314) / 100;
    //}

    //// �����U���p�x�����т���
    //m_pPlayer->GetControlInput()->fLeftStickAngle = fAttackAngle;
}

//=============================================================================
// �W�I�̈ʒu�擾
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetTargetPos(void)
{
    // ����W�I�Ƃ݂Ȃ����ɂ���āA����ʒu���ς��
    if (m_pPlayer->GetCurrentEnergy() >= m_pPlayer->GetCurrentEnergyMax())
    {
        // �G�i�W�[�ʂ��ő�ɒB���Ă�����A�ړ��v�ǂ�_��
        m_targetPos = CGame::GetFortress()->GetPos();
        m_fAttackRange = 0.0f;
    }
    else
    {
        // �߂��̓G
        m_targetPos = CGame::GetPosToClosestEnemy(m_pPlayer->GetPos());

        if (m_targetPos == DEFAULT_VECTOR)
        {
            // �G�����Ȃ��Ƃ��́A�ړ��v�ǂ�_��
            m_targetPos = CGame::GetFortress()->GetPos();
            m_fAttackRange = -100.0f;
        }
        else
        {
            GetAttackRange();
        }
    }

    // ���̕W�I�擾���Ԃ𓾂�
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntSearchTarget = GetRandNum(TARGETTING_INTERVAL_AI_LEVEL_1_MAX, TARGETTING_INTERVAL_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntSearchTarget = GetRandNum(TARGETTING_INTERVAL_AI_LEVEL_2_MAX, TARGETTING_INTERVAL_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntSearchTarget = GetRandNum(TARGETTING_INTERVAL_AI_LEVEL_3_MAX, TARGETTING_INTERVAL_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// �U���̎˒��̎擾
// Author : �㓡�T�V��
//=============================================================================
void CAi::GetAttackRange(void)
{
    switch (m_pPlayer->GetRole())
    {
    case CPlayer::ROLE_WARRIOR:
        m_fAttackRange = ATTACK_RANGE_WARRIOR;
        break;
    case CPlayer::ROLE_HUNTER:
        m_fAttackRange = ATTACK_RANGE_HUNTER;
        break;
    case CPlayer::ROLE_CARRIER:
        m_fAttackRange = ATTACK_RANGE_CARRIER;
        break;
    case CPlayer::ROLE_TANK:
        m_fAttackRange = ATTACK_RANGE_TANK;
        break;
    case CPlayer::ROLE_HEALER:
        m_fAttackRange = ATTACK_RANGE_HEALER;
        break;
    }
}