//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	polygon3d.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

#include "scene3d.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CPolygon3D : public CScene
{
public:

	CPolygon3D(OBJTYPE objType);	// �R���X�g���N�^
	virtual ~CPolygon3D();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos = DEFAULT_VECTOR, D3DXVECTOR3 size = DEFAULT_VECTOR);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPos(void) const { return m_pos; }
	D3DXVECTOR3 GetSize(void) const { return m_size; }
	D3DXVECTOR3 GetRot(void) const { return m_rot; }
	D3DCOLOR GetCol(void) const { return m_col; }

	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetCol(const D3DCOLOR& col) { m_col = col; }

protected:
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DCOLOR m_col;
};

#endif

