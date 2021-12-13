//====================================================================
//
// �G�t�F�N�g�f�[�^�Ǘ� (effectData.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _EFFECT_DATA_H_
#define _EFFECT_DATA_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define EFFECT_PI 314                   // �~�̕\���̍ۂɎg���l�i������G�t�F�N�g�̕��������_�Ŋ���j
#define EFFECT_FLOATING_POINT 100.0f    // �G�t�F�N�g�̕��������_

// �u���b�N���ɓ��������ہA�|���̃G�t�F�N�g��u�����߂̉�]�ʁi�u���b�N�̒����猩�Ă���̂Œ��Ӂj
#define LAY_ROT_TOP D3DXVECTOR3(D3DXToRadian(-90.0f), 0.0f, 0.0f)    // �V��
#define LAY_ROT_LEFT D3DXVECTOR3(0.0f, D3DXToRadian(270.0f), 0.0f)  // ����
#define LAY_ROT_BOT D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f)    // �n��
#define LAY_ROT_RIGHT D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f)  // �E��
#define LAY_ROT_BACK D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f)
#define LAY_ROT_FRONT D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0001f))

#define MAX_EFFECT_TYPE 64

//================================================
// �N���X�錾
//================================================

// �G�t�F�N�g�f�[�^�̊Ǘ��N���X
class CEffectData
{
public:
    CEffectData();
    ~CEffectData();

    typedef enum
    {
        TYPE_HEAL = 0,              // ��
        TYPE_HEART,                 // �n�[�g�e
        TYPE_THRUST,                // �q�b�g�G�t�F�N�g(�˂��A�|)
        TYPE_NEGA,                  // ���]����
        TYPE_SLASH,                 // �q�b�g�G�t�F�N�g�i�a���j
        TYPE_LIGHTNING_0,           // �d���e_0
        TYPE_LIGHTNING_1,           // �d���e_1
        TYPE_SECOND_JUMP_AIR_RING,  // ��i�W�����v�̋�C�̗�
        TYPE_SECOND_JUMP_SMOKE,     // ��i�W�����v�̍���
        TYPE_LIGHTNING_RANGE,       // �d��(�͈�)
        TYPE_SMOKE,                 // ��
        TYPE_GET,                   // �A�C�e���擾
        TYPE_EXPLOSION_0,           // [12] ����_0
        TYPE_EXPLOSION_1,           // [13] ����_1
        TYPE_EXPLOSION_2,           // [14] ����_2
        TYPE_ENEMY_POP_0,           // [15] �G�o��_0
        TYPE_ENEMY_POP_1,           // [16] �G�o��_1
        TYPE_ENEMY_DESTROYING,      // [17] �G����
        TYPE_WIND_0,                // [18] ��_0
        TYPE_WIND_1,                // [19] ��_1
        TYPE_HIT_BALL,              // �{�[��������������
        TYPE_ROAR_0,                // [21] ���K_0
        TYPE_ROAR_1,                // [22] ���K_1
        TYPE_ROAR_2,                // [23] ���K_2
        TYPE_ARROW,                 // [24] ��̃G�t�F�N�g
        TYPE_KIRA,                  // �J�[�\���N���b�N���̃L���L��
        TYPE_SHADOW,                // �e
        TYPE_MAGIC_CIRCLE_0,        // [27] ���@�w_0
        TYPE_MAGIC_CIRCLE_1,        // [28] ���@�w_1
        TYPE_MAGIC_CIRCLE_2,        // [29] ���@�w_2
        TYPE_IMPACT_WAVE_0,         // [30] �E�H�[���A�[�W�����v�U��0
        TYPE_IMPACT_WAVE_1,         // [31] �E�H�[���A�[�W�����v�U��1
        TYPE_IMPACT_WAVE_2,         // [32] �E�H�[���A�[�W�����v�U��2
        TYPE_DARKNESS_AURA_0,       // [33] �����I�[��_0
        TYPE_DARKNESS_AURA_1,       // [34] �����I�[��_1
        TYPE_LANDING_FUGITIVE_DUST,              // [35] ���n����
        TYPE_JUMP_FUGITIVE_DUST,             // [36] �W�����v����
        TYPE_SPARK,        // [37] �Ή�
        TYPE_WALL_HIT_SHOCK,        // �ǃo�E���h�Ռ��g
        TYPE_ABSORB,                // �����オ��z��
        TYPE_READY_TO_FIGHT1,       // ��������1
        TYPE_READY_TO_FIGHT2,       // ��������2
        TYPE_READY_TO_FIGHT3,       // ��������3
        TYPE_READY_TO_FIGHT4,       // ��������4
        TYPE_CHARGE_SWING_LEFT,     // �`���[�W�X�C���O�G�t�F�N�g��
        TYPE_CHARGE_SWING_RIGHT,    // �`���[�W�X�C���O�G�t�F�N�g�E
        TYPE_CHARGE_LIGHT,          // �`���[�W���̌�
        TYPE_BARRIER,               // �o���A
        TYPE_SP_MAX_1,              // �K�E�Q�[�WMAX1
        TYPE_SP_MAX_2,              // �K�E�Q�[�WMAX2
        TYPE_KAMI,                  // ������
        TYPE_SS_1,                  // �X�g���C�N�V���[�g1
        TYPE_SS_2,                  // �X�g���C�N�V���[�g2
        TYPE_SS_3,                  // �X�g���C�N�V���[�g3
        TYPE_SS_BG,                 // �X�g���C�N�V���[�g�w�i
        TYPE_SS_TEXT,               // �X�g���C�N�V���[�g����
    }TYPE;  // ��������G�t�F�N�g�̎��

    typedef enum
    {
        PLANE_XY = 0,   // XY����
        PLANE_XZ,       // XZ����
    }PLANE;  // ���ʂ̏��

    typedef struct
    {
        int nTexType;                 // �g���e�N�X�`���̎��
        int nNumOnce;                 // ����������
        int plane;                    // ����

        bool bOnCircleEdge;           // �~�̉�������o���邩�ǂ���
        bool bEmitVectorInside;       // ���o����������ɂ��邩�ǂ���
        int nScatterAngle;            // ��U�p�x�i0�`314�j
        int nScatterWidth;            // ��U���i0�`314�j
        int nSpeedMax;                // �ő呬�x
        int nSpeedMin;                // �ŏ����x
        int nAuxiliaryAxisSpeedMax;   // �⏕���̍ő呬�x�i2D��3D�ŁA���̊����o�����߂̂��́j
        int nAuxiliaryAxisSpeedMin;   // �⏕���̍ŏ����x�i2D��3D�ŁA���̊����o�����߂̂��́j

        float fAcceleration;          // �����x�i1.0��j
        float fGravity;               // �d��
        float fGravityLimit;          // �d�͐���

        int nLayRot;                  // �|���S�����̂��̂����ɂ��邩�ǂ����i1���A2���A3��A4�E�j
        bool bRotEqualMoveAngle;      // ��]���ړ��̌����ɍ��킹�邩
        int nRotSpeedMax;             // �ő��]���x
        int nRotSpeedMin;             // �ŏ���]���x

        D3DXCOLOR col;                // �F
        D3DXCOLOR colChangeRate;      // �F�ω�����
        float fFadeOutRate;           // ���l�������Ă��������i�F�ω������ł��\�����A�����I�ɗp�ӂ����j
        int nCntFadeOutLock;          // ���l�����b�N����J�E���^

        int nSizeMax;                 // �ő�傫��
        int nSizeMin;                 // �ŏ��傫��
        D3DXVECTOR3 sizeChangeRate;   // �g��/�k������
        int nCntSizeChangeLock;       // �傫�������b�N����J�E���^
        bool bSizeChangeStartOrFinish;// �傫����ς���̂��n�܂邩�A�I���̂�
        float fEmitRadius;            // ���o���a

        bool bUseAdditiveSynthesis;   // ���Z�����ɂ��邩�ǂ���
        bool bUseZBuffer;             // Z�o�b�t�@���������ǂ���
        int nAlphaTestBorder;         // ���e�X�g�̃{�[�_�[
    }CreateInfo;    // �������

    HRESULT Init(void);
    void Uninit(void);

    CreateInfo* GetCreateInfo(const int nNum);

private:
    CreateInfo m_aCreateInfo[MAX_EFFECT_TYPE];    // �������
};

#endif