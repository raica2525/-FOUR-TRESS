//======================================================================================
//
// �e���� (bullet.h)
// Author : �㓡�T�V��
//
//======================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene3d.h"
#include "effect3d.h"
#include "effectData.h"

//================================================
// �}�N����`
//================================================

//================================================
// �O���錾
//================================================

//================================================
// �N���X�錾
//================================================

// �e�N���X
class CBullet : public CScene3D
{
public:
    CBullet();
    ~CBullet();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CBullet *Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, OBJTYPE whoShot, float fStrength = 1.0f, D3DXVECTOR3 rot = DEFAULT_VECTOR);           // ��������

    // �e�̎��
    typedef enum
    {
        TYPE_ARMY_ATTACK = 0,   // �A�[�~�[�̍U��
        TYPE_THUNDER,           // ��
        TYPE_RAILGUN_LV2,       // �d���Clv2
        TYPE_RAILGUN_LV3,       // �d���Clv3
        TYPE_KAMIKAZE_EX,       // �J�~�J�[�̔���
        TYPE_CANNON_ATTACK,     // �L���m���̍U��
        TYPE_COMMANDER_ATTACK,  // �R�}���_�[�̍U��
        TYPE_HUNTER_GROUND,     // �n���^�[�̒n��U��
        TYPE_HUNTER_SKY,        // �n���^�[�̋󒆍U��
        TYPE_CARRIER_SKY,       // �L�����A�[�̋󒆍U��
        TYPE_TANK_GROUND_LV1,   // �^���N�̒n��U��_LV1
        TYPE_TANK_GROUND_LV2,   // �^���N�̒n��U��_LV2
        TYPE_TANK_GROUND_LV3,   // �^���N�̒n��U��_LV3
        TYPE_TANK_GROUND_EX,    // �^���N�̒n��U���̔���
        TYPE_HEALER_GROUND,     // �q�[���[�̒n��U��
        TYPE_HEALER_SKY,        // �q�[���[�̋󒆍U��
		TYPE_SHINIGAMI_ATTACK,	// �V�j�K�~�̍U��
        TYPE_PENPEN_ATTACK,     // �y���y���̍U��
    }TYPE;

    // ���ɓ����邩�̃t���O
    typedef enum
    {
        COLLISION_FLAG_NONE = 0,                    // �Ȃ�
        COLLISION_FLAG_ENEMY = 0x001 << 0,          // �G�ɓ�����
        COLLISION_FLAG_PLAYER = 0x001 << 1,         // �v���C���[�ɓ�����
        COLLISION_FLAG_OFF_BLOCK = 0x001 << 2,      // �u���b�N�ɓ�����Ȃ�
        COLLISION_FLAG_REFLECT_BLOCK = 0x001 << 3,  // �u���b�N�Œ��˕Ԃ�
        COLLISION_FLAG_PULL_ENEMY = 0x001 << 4,     // �G�������񂹂�
        COLLISION_FLAG_HEAL_PLAYER = 0x001 << 5,    // �v���C���[���񕜂���
        COLLISION_FLAG_HEAL_ENEMY = 0x001 << 6 ,    // �G���񕜂���
    }COLLISION_FLAG;

    //=============================
    // �Q�b�^�[
    //=============================
    D3DXVECTOR2 GetCollisionSize(void) { return m_collisionSize; }
    OBJTYPE GetWhoShot(void) { return m_whoShot; }

    //=============================
    // �Z�b�^�[
    //=============================
    void SetParam(int nIdx, float fValue) { m_afParam[nIdx] = fValue; }
    void SetDamage(float fDamage) { m_fDamage = fDamage; }
    void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
    void SetCollisionSizeAndShadow(D3DXVECTOR2 size) { m_collisionSize = size; if (m_pEffect3d_Shadow)m_pEffect3d_Shadow->CEffect3D::SetSize(D3DXVECTOR3(size.x, size.x, 0.0f)); }
    void SetHealValue(float fHealValue) { m_fHealValue = fHealValue; }
    void SetUseUpdate(bool bUseUpdate) { m_bUseUpdate = bUseUpdate; }
    void SetCntTime(int nCntTime) { m_nCntTime = nCntTime; }
    void SetWhoContribution(int nWho) { m_nWhoContribution = nWho; }

private:
    int m_type;                     // ���
    D3DXVECTOR2 m_collisionSize;    // �Փ˃T�C�Y
    D3DXVECTOR3 m_moveAngle;        // �ړ��̊p�x
    float m_fSpeed;                 // ����
    int m_collisionFlag;            // �����蔻��̃t���O

    D3DXVECTOR3 m_posOld;           // 1F�O�̈ʒu
    int m_nLife;                    // ����
    float m_fDamage;                // �_���[�W

    int m_nCntTime;                 // ��������Ă���̎��Ԃ𐔂���
    bool m_bUseDraw;                // �`�悷�邩�ǂ���

    bool m_bHitErase;               // �����������ɏ������ǂ���
    CEffect3D *m_pEffect3d_Shadow;  // �e�ւ̃|�C���^
    bool m_bBreakGoalGate;          // �S�[���Q�[�g���󂷂��ǂ���
    bool m_abUseAvoidMultipleHits[CHARACTER_IDX_MAX]; // ���i�q�b�g������g�����ǂ���
    float m_fStrength;              // ����

    float m_afParam[PARAM_DATA_MAX];// �ėp�f�[�^
    OBJTYPE m_whoShot;              // �N����������
    float m_fHealValue;             // �񕜗�
    bool m_bUseUpdate;              // �X�V�������g�����ǂ���
    bool m_bUseUninit;              // �I���������g�����ǂ���
    bool m_bUseKnockBack;           // �m�b�N�o�b�N���g�����ǂ���

    CEffectData::IntervalEffect m_Effect;   // �O�ՃG�t�F�N�g�̏��
    
    int m_nWhoContribution;         // �N�̍v����
    int m_nHitContributionPoint;    // ���������ۂ̍v���x
    int m_nIdxHitEffect;            // �q�b�g�G�t�F�N�g

    //=============================
    // ��ނ��Ƃ̏���
    //=============================
    void SetupInfoByType(float fStrength, const D3DXVECTOR3 pos);
    void CommanderAttackMove(D3DXVECTOR3 &myPos);
    void HunterSkyMove(D3DXVECTOR3 &myPos);
    bool HealerSkyUseCollision(void);

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void Collision(D3DXVECTOR3 &bulletPos);
};

#endif