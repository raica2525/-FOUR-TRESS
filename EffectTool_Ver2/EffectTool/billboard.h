//====================================================================
//
// �r���{�[�h���� (billboard.h)
// Author : �ɓ��z��
//
//====================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define DEFAULT_ALPHA_TEST_BORDER 100           // ���e�X�g�̃{�[�_�[

//================================================
// �N���X�錾
//================================================

// �r���{�[�h�N���X
class CBillboard : public CScene
{
public:
    CBillboard();
    CBillboard(OBJTYPE objtype);
    virtual ~CBillboard();
    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    void Update(float fAngle);
    virtual void Draw(void);
    void BindTexture(const int nNumTexture);

    // �Z�b�^�[
    void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
    void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
    void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
    void SetSize(D3DXVECTOR3 size) { m_fsize = size; }
    void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetColorVertex(D3DXCOLOR col);     // ���_�̐F�𒼐ڐݒ肷��i���Create����1F���������Ȃ錻�ۂɁA�g���j
    void SetTexUV(float x1, float x2, float y1, float y2) { m_fTexX1 = x1; m_fTexX2 = x2; m_fTexY1 = y1; m_fTexY2 = y2; }          // �e�N�X�`�����W��ݒ�
    bool SetUpdateTexLeftToRight(int nMaxPattern);                                // ������E�Ƀe�N�X�`�����W���X�V
    void SetAlphaTestBorder(int nValue) { m_nAlphaTestBorder = nValue; }          // �A���t�@�e�X�g�̋��E�l��ݒ�

    // �Q�b�^�[
    D3DXVECTOR3 GetPos(void) { return m_pos; }
    D3DXVECTOR3 GetSize(void) { return m_fsize; }
	float GetRotAngle(void) { return m_fRotAngle; }

    static void SetAdditiveSynthesis(void) { m_bAdditiveSynthesis = true; } // ���Z�����ɂ���
    static void SetZBufferNone(void) { m_bUseZBuffer = false; }             // Z�o�b�t�@�𖳌���
	void SetRotAngle(float fAngle) { m_fRotAngle = fAngle; }
private:
    static bool m_bAdditiveSynthesis;       // ���Z�������邩�ǂ���
    static bool m_bUseZBuffer;              // Z�o�b�t�@���g�p���邩�ǂ���
    LPDIRECT3DTEXTURE9		m_pTexture;
    D3DXMATRIX			    m_mtxWorld;		// ���[���h�}�g���b�N�X
    LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		// ���_�o�b�t�@�[
    D3DXVECTOR3				m_pos;			// ���W
    D3DXVECTOR3				m_fsize;			// �傫��
    D3DXVECTOR3				m_rot;			// ��]
    D3DXVECTOR3				m_scale;		// �g�嗦
    D3DXCOLOR				m_col;          // �F
    float					m_fTexX1;       // �e�N�X�`�����WX1
    float					m_fTexX2;       // �e�N�X�`�����WX2
    float					m_fTexY1;		// �e�N�X�`�����WY1
    float					m_fTexY2;		// �e�N�X�`�����WY2

    int m_nAlphaTestBorder;                 // �A���t�@�e�X�g�̋��E�l
	float m_fRotAngle;						// ��]�p�x
};

#endif