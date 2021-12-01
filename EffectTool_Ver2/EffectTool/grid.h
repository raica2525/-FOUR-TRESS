//====================================================================
//
// �O���b�h�̏��� (grid.h)
// Author : �ɓ��z��
//
//====================================================================
#ifndef _GRID_H_
#define _GRID_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"

//================================================
// �N���X�錾
//================================================

// �O���b�h�N���X
class CGrid : public CScene
{
public:
	CGrid();
	CGrid(OBJTYPE objtype);

	~CGrid();
	static CGrid* Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void ZXAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance);	// ZX���̐�
	void XYAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance);	// XY���̐�
	void YZAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance);	// YZ���̐�

	void XAxisLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance);	// X���̐�
	void YAxisLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance);	// Y���̐�
	void ZAxisLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance);	// Z���̐�

	void ShowLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const int nAxisLine);	// �\�����邩���Ȃ���

	float& GetSize(void);	// �傫���̎擾
	bool& GetbShowLine(const int nAxisLine);	// �傫���̎擾

private:
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		// ���_�o�b�t�@�[
	D3DXVECTOR3				m_pos;			// ���W
	D3DXCOLOR				m_col;			// �F
	float					m_fsize;		// �傫��
	float					m_fAllsize;		// ��{���̑傫��
	float					m_fDistance;	// �Ԋu
	bool					m_bShow[3];		// �\�����邩���Ȃ���
};

#endif