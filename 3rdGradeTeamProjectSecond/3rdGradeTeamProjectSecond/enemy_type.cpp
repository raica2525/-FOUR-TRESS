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
#define ARMY_WHOLE_FRAME 80
#define ARMY_FIRE_FRAME 60
#define ARMY_WAIT_COUNT 30
#define ARMY_FOLLOW_FRAME 60

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
    m_fDiscoveryPlayerDistance = DEFAULT_DISCOVERY_PLAYER_DISTANCE;
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
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 150.0f));
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
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 150.0f));
        m_fSpeed = 5.0f;
        fHP = 200.0f;
        m_fChargeValue = 5.0f;
        m_walkMotion = KAMIKAZE_ANIM_WALK;
        m_attackMotion = KAMIKAZE_ANIM_ATTACK;
        m_deathMotion = KAMIKAZE_ANIM_DEATH;
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
        SetCollisionSizeDefence(D3DXVECTOR2(400.0f, 200.0f));
        m_fSpeed = 0.0f;
        fHP = 450.0f;
        m_fChargeValue = 10.0f;
        SetUseKnockBack(false);
        SetTurnSpeed(1.0f);
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(CANNON_PARTS_MAX);
        CCharacter::BindParts(CANNON_PARTS_BODY, 51);
        CCharacter::BindParts(CANNON_PARTS_FIRE_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_cannon.txt");
        CCharacter::SetDontUseAnimation();
        break;
    case TYPE_COMMANDER:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 200.0f));
        m_fSpeed = 0.0f;
        fHP = 850.0f;
        m_fChargeValue = 20.0f;
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
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_ARMY_ATTACK, GetPos(), moveAngle, m_fStrength);
    }
    else if (m_nCntTime == ARMY_WHOLE_FRAME)
    {
        // �ҋ@AI��
        SetBaseState(BASE_STATE_WAIT, ARMY_WAIT_COUNT);
    }
}