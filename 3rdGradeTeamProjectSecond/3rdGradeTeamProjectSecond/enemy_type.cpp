//======================================================================================
//
// �G�l�~�[�̎�ޔh������ (enemy_type.cpp)
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
#include "bullet.h"

//========================================
// �}�N����`
//========================================
#define DEFAULT_PATROL_DISTANCE 2500                    // �f�t�H���g�̏��񋗗�
#define DEFAULT_DISCOVERY_PLAYER_DISTANCE 2000.0f       // �f�t�H���g�̔�������
#define DEFAULT_ENEMY_TURN_SPEED 5.0f                   // �f�t�H���g�̐U��������x
#define DEFAULT_FOLLOW_WHOLE_FRAME 60                   // �f�t�H���g�̒Ǐ]�t���[���i�����o�ϐ��ɂ͒u���Ă��Ȃ��j
#define DEFAULT_FOLLOW_WAIT_FRAME 30                    // �f�t�H���g�̒Ǐ]��̑ҋ@�t���[���i�����o�ϐ��ɂ͒u���Ă��Ȃ��j

//===========================
// �A�[�~�[
//===========================
#define ARMY_WHOLE_FRAME 80     // �S�̃t���[��
#define ARMY_FIRE_FRAME 60      // ���˃t���[��
#define ARMY_WAIT_COUNT 35      // �U����̑ҋ@�t���[���i����30�j

//===========================
// �J�~�J�[
//===========================
#define KAMIKAZE_ATK_SPEED 10.0f // �U�����̃X�s�[�h
#define KAMIKAZE_WHOLE_FRAME 180 // �S�̃t���[��
#define KAMIKAZE_TARGET_FRAME 2  // �^�[�Q�b�g�����߂�t���[��

//===========================
// �L���m��
//===========================
#define CANNON_WHOLE_FRAME 180       // �S�̃t���[��
#define CANNON_FIRE_START_FRAME 60   // ���ˊJ�n�t���[��
#define CANNON_FIRE_INTERVAL_FRAME 6 // ���ˊԊu�t���[��
#define CANNON_FIRE_END_FRAME 120    // ���ˏI���t���[��
#define CANNON_WAIT_COUNT 30         // �U����̑ҋ@�t���[��

//===========================
// �R�}���_�[
//===========================
#define COMMANDER_WHOLE_FRAME 50     // �S�̃t���[��
#define COMMANDER_FIRE_FRAME 30      // ���˃t���[��
#define COMMANDER_WAIT_COUNT 60      // �U����̑ҋ@�t���[��
#define COMMANDER_ONCE_SPAWN 5       // ��x�̐�����
#define COMMANDER_SPAWN_ANGLE_Y D3DXToRadian(80.0f) // �����p�xY

//=============================================================================
// ��ނ��Ƃ̏����ݒ�
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::SetupInfoByType(void)
{
    // ��{�ݒ�
    CCharacter::SetHPDisp(CCharacter::HP_DISP_FOLLOW);  // HP�\���͊�{�Ǐ]
    float fHP = 0.0f;
    m_nPatrolDistance = DEFAULT_PATROL_DISTANCE;
    m_fDiscoveryTargetDistance = DEFAULT_DISCOVERY_PLAYER_DISTANCE;     // ��ɍU������̌��m�Ŏg��
    SetTurnSpeed(DEFAULT_ENEMY_TURN_SPEED);

    switch (m_type)
    {
    case TYPE_SPIDER:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 100.0f));
        m_fSpeed = 5.0f;
        fHP = 500.0f;
        m_fChargeValue = 3.0f;
        m_walkMotion = SPIDER_ANIM_WALK;
        m_attackMotion = SPIDER_ANIM_ATTACK;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(SPIDER_PARTS_MAX);
        CCharacter::BindParts(SPIDER_PARTS_BODY, 18);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH, 19);
        CCharacter::BindParts(SPIDER_PARTS_FANG_LEFT, 20);
        CCharacter::BindParts(SPIDER_PARTS_FANG_RIGHT, 21);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_0, 22);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_1, 23);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_2, 24);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_3, 25);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_0, 26);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_1, 27);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_2, 28);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_3, 29);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH_CUBE, 30);
        CCharacter::LoadModelData("./data/ANIMATION/motion_spider.txt");
        break;
    case TYPE_ARMY:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 300.0f));
        m_fSpeed = 5.0f;
        fHP = 280.0f;
        m_fChargeValue = 3.0f;
        m_walkMotion = ARMY_ANIM_WALK;
        m_attackMotion = ARMY_ANIM_ATTACK;
        m_deathMotion = ARMY_ANIM_DEATH;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(ARMY_PARTS_MAX);
        CCharacter::BindParts(ARMY_PARTS_BODY, 43);
        CCharacter::BindParts(ARMY_PARTS_RHAND, 44);
        CCharacter::BindParts(ARMY_PARTS_LHAND, 45);
        CCharacter::LoadModelData("./data/ANIMATION/motion_army.txt");
        break;
    case TYPE_KAMIKAZE:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 325.0f));
        m_fSpeed = 5.0f;
        fHP = 200.0f;
        m_fChargeValue = 5.0f;
        m_walkMotion = KAMIKAZE_ANIM_WALK;
        m_attackMotion = KAMIKAZE_ANIM_ATTACK;
        m_deathMotion = KAMIKAZE_ANIM_DEATH;
        m_targetTrend = TARGET_TREND_FORTRESS;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(KAMIKAZE_PARTS_MAX);
        CCharacter::BindParts(KAMIKAZE_PARTS_BODY, 46);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARML, 47);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARMR, 48);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB, 49);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_kamikaze.txt");
        break;
    case TYPE_CANNON:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(400.0f, 400.0f));
        m_fSpeed = 0.0f;
        fHP = 450.0f;
        m_fChargeValue = 10.0f;
        SetUseKnockBack(false);
        SetTurnSpeed(1.2f);
        m_targetTrend = TARGET_TREND_PLAYER_AND_FORTRESS;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(CANNON_PARTS_MAX);
        CCharacter::BindParts(CANNON_PARTS_BODY, 51);
        CCharacter::BindParts(CANNON_PARTS_FIRE_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_cannon.txt");
        CCharacter::SetDontUseAnimation();
        break;
    case TYPE_COMMANDER:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(600.0f, 400.0f));
        m_fSpeed = 0.0f;
        fHP = 850.0f;
        m_fChargeValue = 20.0f;
        m_attackMotion = COMMANDER_ANIM_SPAWN_ENEMY;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(COMMANDER_PARTS_MAX);
        CCharacter::BindParts(COMMANDER_PARTS_BODY, 58);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL1, 59);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL2, 60);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL3, 61);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL4, 62);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL5, 63);
        CCharacter::BindParts(COMMANDER_PARTS_SPAWN_POS, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_commander.txt");
        break;
    }

    // �����𔽉f
    //m_fSpeed *= m_fStrength;  // �ړ����x�������Ȃ�͈̂�a���H
    fHP *= m_fStrength;

    // HP�𔽉f
    SetUpLife(fHP);
}

//=============================================================================
// ���ʂ̍U���i�^�[�Q�b�g��Ǐ]�j
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::AtkCommonFollow(D3DXVECTOR3 &myPos)
{
    // �ʒu�Ɉړ��ʂ����т���
    myPos += m_moveAngle * m_fSpeed;

    // �����𒲐�
    RotControl();

    if (m_nCntTime >= DEFAULT_FOLLOW_WHOLE_FRAME)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, DEFAULT_FOLLOW_WAIT_FRAME);
    }
}

//=============================================================================
// �A�[�~�[�̍U��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::AtkArmy(D3DXVECTOR3& myPos)
{
    if (m_nCntTime == ARMY_FIRE_FRAME)
    {
        // ���˃t���[��
        D3DXVECTOR3 collisionSize = GetCollisionSizeDefence();
        D3DXVECTOR3 firePos = myPos + D3DXVECTOR3(0.0f, collisionSize.y / 2.0f, 0.0f);
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_ARMY_ATTACK, firePos, moveAngle, OBJTYPE_ENEMY, m_fStrength);
    }
    else if (m_nCntTime == ARMY_WHOLE_FRAME)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, ARMY_WAIT_COUNT);
    }
}

//=============================================================================
// �J�~�J�[�̍U��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::AtkKamikaze(D3DXVECTOR3 &myPos)
{
    // �ʒu�Ɉړ��ʂ����т���
    myPos += m_moveAngle * KAMIKAZE_ATK_SPEED;

    // �����𒲐�
    RotControl();

    if (m_nCntTime >= KAMIKAZE_WHOLE_FRAME)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, DEFAULT_FOLLOW_WAIT_FRAME);

    }
    else if (m_nCntTime == KAMIKAZE_TARGET_FRAME)
    {
        if (m_pTarget)
        {
            // ���݂̈ʒu�ƁA�ړI�n�܂ł̈ړ��p�x/���������߂�
            D3DXVECTOR3 targetPos = m_pTarget->GetPos();
            float fDestAngle = atan2((myPos.x - targetPos.x), (myPos.z - targetPos.z));
            m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
            SetRotDestY(fDestAngle);

        }
    }
}

//=============================================================================
// �L���m���̍U��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::AtkCannon(D3DXVECTOR3& myPos)
{
    if (m_nCntTime >= CANNON_FIRE_START_FRAME && m_nCntTime <= CANNON_FIRE_END_FRAME)
    {
        // ���˃t���[��
        if (m_nCntTime % CANNON_FIRE_INTERVAL_FRAME == 0)
        {
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
            CBullet::Create(CBullet::TYPE_CANNON_ATTACK, GetPartsPos(CANNON_PARTS_FIRE_CUBE), moveAngle, OBJTYPE_ENEMY, m_fStrength);
        }
    }
    else if (m_nCntTime == CANNON_WHOLE_FRAME)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, CANNON_WAIT_COUNT);
    }
}

//=============================================================================
// �R�}���_�[�̍U��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::AtkCommander(D3DXVECTOR3 &myPos)
{
    if (m_nCntTime == COMMANDER_FIRE_FRAME)
    {
        // ����
        for (int nCnt = 0; nCnt < COMMANDER_ONCE_SPAWN; nCnt++)
        {
            float fAngle = float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT - float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT;
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(fAngle), COMMANDER_SPAWN_ANGLE_Y, -cosf(fAngle));
            CBullet::Create(CBullet::TYPE_COMMANDER_ATTACK, GetPartsPos(COMMANDER_PARTS_SPAWN_POS), moveAngle, OBJTYPE_ENEMY, m_fStrength);
        }
    }
    else if (m_nCntTime == COMMANDER_WHOLE_FRAME)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, COMMANDER_WAIT_COUNT);
    }
}