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

//================================================
// �}�N����`
//================================================

//================================================
// �O���錾
//================================================
class CEffect3D;

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
    static CBullet *Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, float fStrength = 1.0f, D3DXVECTOR3 rot = DEFAULT_VECTOR);           // ��������

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
    }TYPE;

    // ���ɓ����邩�̃t���O
    typedef enum
    {
        COLLISION_FLAG_NONE = 0,                    // �Ȃ�
        COLLISION_FLAG_ENEMY = 0x001 << 0,          // �G�ɓ�����
        COLLISION_FLAG_PLAYER = 0x001 << 1,         // �v���C���[�ɓ�����
        COLLISION_FLAG_OFF_BLOCK = 0x001 << 2,      // �u���b�N�ɓ�����Ȃ�
        COLLISION_FLAG_REFLECT_BLOCK = 0x001 << 3,  // �u���b�N�Œ��˕Ԃ�
    }COLLISION_FLAG;

    //=============================
    // �Q�b�^�[
    //=============================
    D3DXVECTOR2 GetCollisionSize(void) { return m_collisionSize; }

    //=============================
    // �Z�b�^�[
    //=============================
    void SetTargetPos(D3DXVECTOR3 targetPos) { m_targetPos = targetPos; }

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

    D3DXVECTOR3 m_targetPos;        // �^�[�Q�b�g�̈ʒu

    //=============================
    // ��ނ��Ƃ̏���
    //=============================
    void SetupInfoByType(float fStrength, const D3DXVECTOR3 pos);
    void CommanderAttackMove(D3DXVECTOR3 &myPos);
    void HunterSkyMove(D3DXVECTOR3 &myPos);

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void Collision(D3DXVECTOR3 &bulletPos);
};

#endif