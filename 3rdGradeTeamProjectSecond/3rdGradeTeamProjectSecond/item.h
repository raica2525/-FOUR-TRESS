//======================================================================================
//
// �A�C�e������ (item.h)
// Author : �㓡�T�V��
//
//======================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

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
class CPlayer;

//================================================
// �N���X�錾
//================================================

// �A�C�e���N���X
class CItem : public CScene3D
{
public:
    CItem();
    ~CItem();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);    // ����������
    void Uninit(void);                                  // �I������
    void Update(void);                                  // �X�V����
    void Draw(void);                                    // �`�揈��
    static CItem *Create(int type, D3DXVECTOR3 pos, float fEnergy = 0.0f);    // ��������

    // �A�C�e���̎��                                                                                                                                               // �A�C�e���̎��
    typedef enum
    {
        TYPE_DENTI_5 = 0,   // �P5�d�r
        TYPE_DENTI_3,       // �P3�d�r
        TYPE_DENTI_1,       // �P1�d�r
    }TYPE;

    //=============================
    // �Q�b�^�[
    //=============================
    D3DXVECTOR2 GetCollisionSize(void) { return m_collisionSize; }
    float GetEnergy(void) { return m_fGetEnergy; }

    //=============================
    // �Z�b�^�[
    //=============================

private:
    int m_type;                     // ���
    D3DXVECTOR2 m_collisionSize;    // �Փ˃T�C�Y
    D3DXVECTOR3 m_move;             // �ړ���
    float m_fSpeed;                 // ���x

    D3DXVECTOR3 m_posOld;           // 1F�O�̈ʒu
    int m_nLife;                    // ����
    float m_fGetEnergy;             // �l���G�i�W�[

    bool m_bUseDraw;                // �`�悷�邩�ǂ���
    CEffect3D *m_pEffect3d_Shadow;  // �e�ւ̃|�C���^
    bool m_bGround;                 // �n�ʂɒ��n�������ǂ����i���n������A�v���C���[���z���ł���j
    CPlayer *m_pTargetPlayer;       // �^�[�Q�b�g�̃v���C���[�̃|�C���^

    bool m_bUseCollision;           // �Փ˔�����g�����ǂ���

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void MoveTowardPlayer(D3DXVECTOR3 myPos);
    void SearchPlayer(D3DXVECTOR3 myPos);
    void Collision(D3DXVECTOR3 myPos);
};

#endif