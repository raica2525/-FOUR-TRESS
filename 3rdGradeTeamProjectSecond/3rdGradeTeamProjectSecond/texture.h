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
#include <map>
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEXTURE (256) 

//=============================================================================
// �e�N�X�`���N���X
//=============================================================================
class CTexture
{
public:
    CTexture();		// �R���X�g���N�^
    ~CTexture();	// �f�X�g���N�^

    typedef struct
    {
        LPDIRECT3DTEXTURE9 pTexture;
        int nParagraph;
        int nPattern;
        int nSpeed;
        bool bRepeat;
    }Info;    // �e�N�X�`�����i�O���t�@�C�����Ŗ��ݒ�̂��̂������̂ŁA�����I�ɏ���������j

    HRESULT Init(void);
    void Uninit(void);

    Info* GetInfo(const int nNum);	// �e�N�X�`�����

    int GetCntLoadTextureByTxt(void) { return m_nCntLoadTextureByTxt; }
	int GetIndexByName(std::string name) { return m_nameIndexMap.at(name); }	//���O����ԍ����擾

private:
    Info m_aInfo[MAX_TEXTURE];	// �e�N�X�`�����

    //=====================================
    // Second�ȍ~�Œǉ���������
    //=====================================
    int m_nCntLoadTextureByTxt; // �e�L�X�g�t�@�C������ǂݍ��񂾃e�N�X�`���̐�
	std::map<std::string, int> m_nameIndexMap;	//���O�Ɣԍ��̑Ή��z��

	HRESULT LoadTextureFromTxt(std::string path);	//�e�L�X�g����e�N�X�`����ǂݍ���
	HRESULT LoadTextureFromJson(std::string path);	//JSON����e�N�X�`����ǂݍ���
	
};
#endif