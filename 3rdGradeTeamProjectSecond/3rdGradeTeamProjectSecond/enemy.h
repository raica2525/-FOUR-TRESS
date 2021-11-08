//======================================================================================
//
// �G�l�~�[���� (enemy.h)
// Author : �㓡�T�V��
//
//======================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "character.h"
#include "model.h"

//================================================
// �}�N����`
//================================================

//================================================
// �O���錾
//================================================

//================================================
// �N���X�錾
//================================================

// �G�l�~�[�N���X
class CEnemy : public CCharacter
{
public:
    CEnemy();
    ~CEnemy();

    // �G�̎��
    typedef enum
    {
        TYPE_SPIDER = 0,           // �w�
    }TYPE;

    // �w偂̃A�j���[�V����
    typedef enum
    {
        SPIDER_ANIM_IDLE = 0,      // �ҋ@
        SPIDER_ANIM_WALK,          // ����
        SPIDER_ANIM_TAUNT,         // ����
        SPIDER_ANIM_ATTACK,        // �U��
        SPIDER_ANIM_JUMP,          // �W�����v
        SPIDER_ANIM_MAX,           // �ő吔
    }SPIDER_ANIMATION;

    // �w偂̃p�[�c
    typedef enum
    {
        SPIDER_PARTS_BODY = 0,
        SPIDER_PARTS_STOMACH,
        SPIDER_PARTS_FANG_RIGHT,
        SPIDER_PARTS_FANG_LEFT,
        SPIDER_PARTS_LEG_RIGHT_0,
        SPIDER_PARTS_LEG_RIGHT_1,
        SPIDER_PARTS_LEG_RIGHT_2,
        SPIDER_PARTS_LEG_RIGHT_3,
        SPIDER_PARTS_LEG_LEFT_0,
        SPIDER_PARTS_LEG_LEFT_1,
        SPIDER_PARTS_LEG_LEFT_2,
        SPIDER_PARTS_LEG_LEFT_3,
        SPIDER_PARTS_STOMACH_CUBE, // �����甭�������铖���蔻��̈ʒu
        SPIDER_PARTS_MAX,
    }SPIDER_PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CEnemy *Create(int type, D3DXVECTOR3 pos, float fStrength = 1.0f, D3DXVECTOR3 rot = DEFAULT_VECTOR);                  // ��������

    //=============================
    // �Q�b�^�[
    //=============================
    D3DXVECTOR2 GetCollisionSizeDeffence(void) { return m_collisionSizeDeffence; }

    //=============================
    // �Z�b�^�[
    //=============================

private:
    int m_type;                              // ���
    D3DXVECTOR2 m_collisionSizeDeffence;     // �h��Փ˃T�C�Y
    float m_fSpeed;                          // ����
    float m_fStrength;                       // ����(��{1.0�{)
    float m_fLife;                           // �̗�

    int m_nCntTime;                          // ���Ԃ𐔂���

    //=============================
    // ��ނ��Ƃ̏���
    //=============================
    void SetupInfoByType(void);
};

#endif