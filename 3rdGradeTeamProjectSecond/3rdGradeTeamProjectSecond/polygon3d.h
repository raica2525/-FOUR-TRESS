//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	polygon3d.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

#include "scene3d.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPolygon3D : public CScene3D
{
public:

	CPolygon3D();		//コンストラクタ
	virtual ~CPolygon3D();		//デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetShow(bool bShow) { m_bShow = bShow; }
	static CPolygon3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
protected:
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
private:
	bool m_bShow;
};

#endif

