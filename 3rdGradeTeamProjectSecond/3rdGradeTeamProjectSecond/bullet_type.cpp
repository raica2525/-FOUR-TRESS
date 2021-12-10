//======================================================================================
//
// �e�̎�ޔh������ (bullet_type.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "effect3d.h"
#include "modelEffect.h"

//========================================
// �}�N����`�i�����I�ȏ�����������̂̂݁j
//========================================
//===========================
// �R�}���_�[�̒e
//===========================
#define COMMANDER_ATTACK_GRAVITY_VALUE -0.1f
#define COMMANDER_ATTACK_GRAVITY_LIMIT -10.0f

//===========================
// �n���^�[�̋󒆍U��
//===========================
#define HUNTER_SKY_HOMING_START_FRAME 30
#define HUNTER_SKY_HOMING_SPEED 60.0f
// �ėp�p�����[�^�̓���
typedef enum
{
    PARAM_HUNTER_SKY_TARGET_POS_X = 0,
    PARAM_HUNTER_SKY_TARGET_POS_Y,
    PARAM_HUNTER_SKY_TARGET_POS_Z,
}PARAM_HUNTER_SKY;

//=============================================================================
// ��ނ��Ƃ̏����ݒ�
// Author : �㓡�T�V��
//=============================================================================
void CBullet::SetupInfoByType(float fStrength, const D3DXVECTOR3 pos)
{
    // �e�𐶐����邩�ǂ���
    bool bUseShadow = true;

    switch (m_type)
    {
    case TYPE_ARMY_ATTACK:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 50.0f;
        m_bUseDraw = true;  // ��
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_RAILGUN_LV2:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(500.0f, 500.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 180;
        m_fDamage = 5000.0f;
        m_bUseDraw = true;  // ��
        m_bHitErase = false;// �ђ�
        m_bBreakGoalGate = true;    // �S�[���Q�[�g���󂹂�
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_RAILGUN_LV3:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 10000.0f;
        m_bUseDraw = true;  // ��
        m_bHitErase = false;// �ђ�
        m_bBreakGoalGate = true;    // �S�[���Q�[�g���󂹂�
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_KAMIKAZE_EX:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 60;
        m_fDamage = 300.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// �ђ�
        bUseShadow = false; // �e���g�p���Ȃ�
        break;
    case TYPE_CANNON_ATTACK:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(75.0f, 75.0f);
        m_fSpeed = 25.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 15.0f;
        m_bUseDraw = true;
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_COMMANDER_ATTACK:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(75.0f, 75.0f);
        m_fSpeed = 5.0f;
        m_nLife = 999;
        m_bUseDraw = true;
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK);   // �u���b�N�Ŕ��˂́A�u���b�N�ŏ����Ȃ�����̂ƃ����Z�b�g
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_HUNTER_GROUND:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 50.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK);
        m_nLife = 45;
        m_fDamage = 70.0f;
        m_bUseDraw = true;
        m_bHitErase = false;// �ђʁi�v�����j
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_HUNTER_SKY:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 40.0f;
        m_bUseDraw = true;
        m_bHitErase = false;// �ђ�
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_CARRIER_SKY:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(2000.0f, 500.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_PULL_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 30;
        m_fDamage = 0.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// �ђ�
        bUseShadow = false; // �e���g�p���Ȃ�
        break;
    case TYPE_TANK_GROUND_LV1:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(150.0f, 150.0f);
        m_fSpeed = 40.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 50.0f;
        m_bUseDraw = true;
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_TANK_GROUND_LV2:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(200.0f, 200.0f);
        m_fSpeed = 45.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 150.0f;
        m_bUseDraw = true;
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_TANK_GROUND_LV3:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(250.0f, 250.0f);
        m_fSpeed = 50.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 0.0f;
        m_bUseDraw = true;
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_TANK_GROUND_EX:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(1250.0f, 1250.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 60;
        m_fDamage = 450.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// �ђ�
        bUseShadow = false; // �e���g�p���Ȃ�
        break;
    }

    // �����𔽉f
    //m_fSpeed *= fStrength;    // �ړ����x�������Ȃ�͈̂�a���H
    m_fDamage *= fStrength;

    // �e����
    if (bUseShadow)
    {
        m_pEffect3d_Shadow = CEffect3D::Create(CEffectData::TYPE_SHADOW, D3DXVECTOR3(pos.x, SHADOW_POS_Y, pos.z));
        m_pEffect3d_Shadow->SetSize(D3DXVECTOR3(m_collisionSize.x, m_collisionSize.x, 0.0f));
        m_pEffect3d_Shadow->SetDisp(false); // �o���b�g���ŕ`����Ǘ����邽��
    }
}

//=============================================================================
// �R�}���_�[�̒e�̈ړ�����
// Author : �㓡�T�V��
//=============================================================================
void CBullet::CommanderAttackMove(D3DXVECTOR3 &myPos)
{
    // �J�E���^���Z
    m_nCntTime++;

    // �d�͂��g���Ȃ�
    float fGravity = COMMANDER_ATTACK_GRAVITY_VALUE * m_nCntTime;
    if (fGravity < COMMANDER_ATTACK_GRAVITY_LIMIT)
    {
        fGravity = COMMANDER_ATTACK_GRAVITY_LIMIT;
    }
    myPos += m_moveAngle * m_fSpeed + D3DXVECTOR3(0.0f, fGravity, 0.0f);
}

//=============================================================================
// �n���^�[�̋󒆍U���e�̈ړ�����
// Author : �㓡�T�V��
//=============================================================================
void CBullet::HunterSkyMove(D3DXVECTOR3 &myPos)
{
    // �J�E���^���Z
    m_nCntTime++;

    // �z�[�~���O����
    if (m_nCntTime == HUNTER_SKY_HOMING_START_FRAME)
    {
        // ���x������
        m_fSpeed = HUNTER_SKY_HOMING_SPEED;

        // ���̊p�x�����߂�
        float fAngleXZ = atan2f((myPos.x - m_afParam[PARAM_HUNTER_SKY_TARGET_POS_X]), (myPos.z - m_afParam[PARAM_HUNTER_SKY_TARGET_POS_Z]));

        // �c�̊p�x�����߂�
        float fDistance = sqrtf(
            powf((m_afParam[PARAM_HUNTER_SKY_TARGET_POS_X] - myPos.x), 2.0f) +
            powf((m_afParam[PARAM_HUNTER_SKY_TARGET_POS_Z] - myPos.z), 2.0f));
        float fHeight = fabsf(m_afParam[PARAM_HUNTER_SKY_TARGET_POS_Y] - myPos.y);
        float fAngleY = atan2(fDistance, fHeight);

        // �ړ��̊p�x�ɔ��f
        m_moveAngle.x = -sinf(fAngleXZ);
        m_moveAngle.y = -cosf(fAngleY);
        m_moveAngle.z = -cosf(fAngleXZ);
    }

    // �ړ�
    myPos += m_moveAngle * m_fSpeed;
}