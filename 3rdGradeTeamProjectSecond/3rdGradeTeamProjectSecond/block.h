//======================================================================================
//
// �u���b�N���� (block.h)
// Author : �㓡�T�V��
//
//======================================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

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

//================================================
// �N���X�錾
//================================================

// �u���b�N�N���X
class CBlock : public CScene3D
{
public:
    CBlock();
    ~CBlock();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CBlock *Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 collisionSize, D3DXVECTOR3 rot);        // ��������

    void TakeDamage(bool bBreakGoalGate);

    // �u���b�N�̎��
    typedef enum
    {
        TYPE_FRAME = 0,   // �g
        TYPE_GOAL_GATE,   // �S�[���̖�
        TYPE_NORMAL_GATE, // �m�[�}���Q�[�g
    }TYPE;

    //=============================
    // �Q�b�^�[
    //=============================
    D3DXVECTOR3 GetCollisionSize(void) { return m_collisionSize; }

    //=============================
    // �Z�b�^�[
    //=============================

private:
    int m_type;                     // ���
    D3DXVECTOR3 m_collisionSize;    // �Փ˃T�C�Y

    bool m_bBreak;                  // ���邩�ǂ���
    bool m_bUse;                    // �g�p���邩�ǂ���

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
};

#endif