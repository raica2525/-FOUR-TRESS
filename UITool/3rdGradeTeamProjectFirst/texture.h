//=============================================================================
//
// �e�N�X�`���̃f�[�^�̏��� [texture.h]
// Author : �㓡�T�V��
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEXTURE (256) // �e�N�X�`���̍ő吔

//=============================================================================
// �e�N�X�`���N���X
//=============================================================================
class CTexture
{
    static CTexture* m_pInstance;// �I�u�W�F�N�g�ւ̃|�C���^

public:
	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

    // �e�N�X�`�����i�O���t�@�C�����Ŗ��ݒ�̂��̂������̂ŁA�����I�ɏ���������j
    typedef struct
    {
        LPDIRECT3DTEXTURE9 pTexture;// �e�N�X�`���̃|�C���^
        int nParagraph;
        int nPattern;
        int nSpeed;
        bool bRepeat;
    }Info;   

    HRESULT Init(void);
    void Uninit(void);

    // Get�֐�
    Info* GetInfo(const int nNum);	// �e�N�X�`�����
    static int GetnNumTexture(void) {
        return m_nNumTexture; }
private:
    Info m_aInfo[MAX_TEXTURE];	// �e�N�X�`�����
    static int m_nNumTexture;// �e�N�X�`���̐�
};
#endif