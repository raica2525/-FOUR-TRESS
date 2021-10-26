//====================================================================
//
// �V�[�����2D�|���S������ (scene2d.h)
// Author : �㓡�T�V���A�r�c�I��i�e�N�X�`���u�����f�B���O�Ή��j
//
//====================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "object.h"

//================================================
// �}�N����`
//================================================
#define MAX_BREND_TEXTURE (4)			// �e�N�X�`���u�����h�̍ő吔    //�r�c�ǉ�
#undef MAX_BREND_TEXTURE

#define MAX_ANIM_COUNTER (10000)        // �A�j���[�V�����̃J�E���^�𗘗p����ۂ́A�ő�J�E���g

//================================================
// �N���X�錾
//================================================

// 2D�|���S���N���X
class CScene2D : public CObject
{
public:
	CScene2D();
	virtual ~CScene2D();
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindTexture(const int nNumTexture);                                   // �e�N�X�`�������蓖�Ă�
	void SetVertex(void);                                                                                       // ���_���W��ݒ�
	void SetRotVertex(float fAngle);                                                                            // ��]���钸�_���W��ݒ�
	void SetVisualVertex(D3DXVECTOR3 posVisual, D3DXVECTOR3 sizeVisual);                                        // ��������̒��_���W��ݒ�
	void SetTextureRange(int nRange, int nPattern);                                               // �e�N�X�`���̕`��͈͂�ݒ�
	void SetTexturePlace(int nPlace, int nPattern);                                               // �e�N�X�`���̕`��ꏊ�����߂�

	/*========================================================
	y// �Z�b�^�[
	y//======================================================*/
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetAlphaTestBorder(int nValue) { m_nAlphaTestBorder = nValue; }
	void SetAdditiveSynthesis(void) { m_bAdditiveSynthesis = true; }
	void SetColor(D3DXCOLOR col);


	/*========================================================
	// �Q�b�^�[
	//======================================================*/
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	static bool m_bAdditiveSynthesis;                       // ���Z�������邩�ǂ���
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		                // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;	                        // �ʒu
	D3DXVECTOR3             m_size;                         // �傫��
	int m_nAlphaTestBorder;                                 // �A���t�@�e�X�g�̋��E�l
};

#endif