//====================================================================
//
// グリッドの処理 (grid.h)
// Author : 伊藤陽梧
//
//====================================================================
#ifndef _GRID_H_
#define _GRID_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene.h"

//================================================
// クラス宣言
//================================================

// グリッドクラス
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

	void ZXAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance);	// ZX軸の線
	void XYAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance);	// XY軸の線
	void YZAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance);	// YZ軸の線

	void XAxisLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance);	// X軸の線
	void YAxisLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance);	// Y軸の線
	void ZAxisLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance);	// Z軸の線

	void ShowLine(VERTEX_3D* pVtx, const int nCount, const int nVertex, const int nAxisLine);	// 表示するかしないか

	float& GetSize(void);	// 大きさの取得
	bool& GetbShowLine(const int nAxisLine);	// 大きさの取得

private:
	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		// 頂点バッファー
	D3DXVECTOR3				m_pos;			// 座標
	D3DXCOLOR				m_col;			// 色
	float					m_fsize;		// 大きさ
	float					m_fAllsize;		// 一本線の大きさ
	float					m_fDistance;	// 間隔
	bool					m_bShow[3];		// 表示するかしないか
};

#endif