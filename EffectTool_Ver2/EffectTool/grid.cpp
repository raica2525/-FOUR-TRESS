//================================================
//
// グリッドの処理 (grid.cpp)
// Author : 伊藤陽梧
//
//================================================

//================================================
// インクルードファイル
//================================================
#include "grid.h"
#include "manager.h"
#include "renderer.h"

//================================================
// マクロ定義
//================================================
#define MAX_GRID_LINE_NUM (11)							// グリッドの線の最大数
#define GRID_DISTANCE_SIZE (100.0f)						// グリッドごとの間隔
#define GRID_SIDE_SIZE (GRID_DISTANCE_SIZE * 10.0f)		// グリッドの一本線の長さ
#define GRID_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// グリッドの色
#define AXIS_VERTEX_NUM (22)							// 軸ごとに使う頂点の数
#define ZX_AXIS_LINE (0)
#define XY_AXIS_LINE (1)
#define YZ_AXIS_LINE (2)

//=============================================================================
// オーバーライドされたコンストラクタ
//=============================================================================
CGrid::CGrid(CScene::OBJTYPE objtype) :CScene(objtype)
{
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = DEFAULT_VECTOR;
	m_fsize = GRID_DISTANCE_SIZE;
	m_fAllsize = GRID_SIDE_SIZE;
	m_col = GRID_COLOR;
	m_fDistance = 0.0f;
	memset(m_bShow, true, sizeof(m_bShow));
}

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGrid::CGrid()
{
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = DEFAULT_VECTOR;
	m_fsize = GRID_DISTANCE_SIZE;
	m_fAllsize = GRID_SIDE_SIZE;
	m_col = GRID_COLOR;
	m_fDistance = 0.0f;
	memset(m_bShow, true, sizeof(m_bShow));
}

//=============================================================================
// デストラクタ
//=============================================================================
CGrid::~CGrid()
{
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = DEFAULT_VECTOR;
	m_fsize = 0.0f;
	m_fAllsize = 0.0f;
	m_col = GRID_COLOR;
	m_fDistance = 0.0f;
	memset(m_bShow, true, sizeof(m_bShow));
}

//=============================================================================
// クリエイト
//=============================================================================
CGrid * CGrid::Create()
{
	CGrid* pGrid = nullptr;

	if (pGrid == nullptr)
	{
		pGrid = new CGrid(OBJTYPE_GRID);

		// 初期化
		pGrid->Init();
	}

	return pGrid;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGrid::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AXIS_VERTEX_NUM * 6, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGrid::Uninit(void)
{
	// 頂点バッファを開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// シーンの開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGrid::Update(void)
{
	// 一辺ごとの大きさの合計
	m_fAllsize = m_fsize * (MAX_GRID_LINE_NUM - 1);

	// 等分したときの間隔
	m_fDistance = m_fAllsize / (MAX_GRID_LINE_NUM - 1);

	VERTEX_3D *pVtx = NULL;	// 頂点情報へのポインタ

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// 各頂点の色と法線ベクトルを更新
	for (int nCount = 0; nCount < AXIS_VERTEX_NUM * 6; nCount++)
	{
		// 各頂点のテクスチャ座標を更新
		pVtx[nCount].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCount].col = m_col;
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	for (int nCount = 0; nCount < MAX_GRID_LINE_NUM; nCount++)
	{
		// 線を引く間隔
		float fDistance = (m_fAllsize / 2) - (nCount * m_fDistance);

		ZXAxisLine(pVtx, nCount, fDistance);	// ZX軸の線
		XYAxisLine(pVtx, nCount, fDistance);	// XY軸の線
		YZAxisLine(pVtx, nCount, fDistance);	// YZ軸の線
	}

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGrid::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ライトを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	// Zバッファを無効化
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NUM_POLYGON * MAX_GRID_LINE_NUM * 3);

	// テクスチャをNULLに
	pDevice->SetTexture(0, NULL);

	// Zバッファを有効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライトを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ZX軸の線
//=============================================================================
void CGrid::ZXAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance)
{
	// Z軸に平行な線
	ZAxisLine(pVtx, nCount, 0, D3DXVECTOR3(fDistance, 0.0f, 0.0f));

	// X軸に平行な線
	XAxisLine(pVtx, nCount, AXIS_VERTEX_NUM, D3DXVECTOR3(0.0f, 0.0f, fDistance));

	// 線を表示するかしないか
	ShowLine(pVtx, nCount, 0, ZX_AXIS_LINE);
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM, ZX_AXIS_LINE);
}

//=============================================================================
// XY軸の線
//=============================================================================
void CGrid::XYAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance)
{
	// X軸に平行な線
	XAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 2, D3DXVECTOR3(0.0f, fDistance, 0.0f));

	// Y軸に平行な線
	YAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 3, D3DXVECTOR3(fDistance, 0.0f, 0.0f));

	// 線を表示するかしないか
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 2, XY_AXIS_LINE);
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 3, XY_AXIS_LINE);
}

//=============================================================================
// YZ軸の線
//=============================================================================
void CGrid::YZAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance)
{
	// Y軸に平行な線
	YAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 4, D3DXVECTOR3(0.0f, 0.0f, fDistance));

	// Z軸に平行な線
	ZAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 5, D3DXVECTOR3(0.0f, fDistance, 0.0f));

	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 4, YZ_AXIS_LINE);
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 5, YZ_AXIS_LINE);
}

//=============================================================================
// X軸の線
//=============================================================================
void CGrid::XAxisLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance)
{
	// X軸に平行な線
	// 頂点座標の設定
	pVtx[(nCount * 2) + nVertex].pos = m_pos + Distance + D3DXVECTOR3(-m_fAllsize, 0.0f, 0.0f) / 2.0f;
	pVtx[(nCount * 2) + nVertex + 1].pos = m_pos + Distance + D3DXVECTOR3(m_fAllsize, 0.0f, 0.0f) / 2.0f;

	// 中心の線を赤に
	if (nCount == 5)
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

//=============================================================================
// Y軸の線
//=============================================================================
void CGrid::YAxisLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance)
{
	// Y軸に平行な線
	// 頂点座標の設定
	pVtx[(nCount * 2) + nVertex].pos = m_pos + Distance + D3DXVECTOR3(0.0f, -m_fAllsize, 0.0f) / 2.0f;
	pVtx[(nCount * 2) + nVertex + 1].pos = m_pos + Distance + D3DXVECTOR3(0.0f, m_fAllsize, 0.0f) / 2.0f;

	// 中心の線を緑に
	if (nCount == 5)
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
}

//=============================================================================
// Z軸の線
//=============================================================================
void CGrid::ZAxisLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance)
{
	// Z軸に平行な線
	// 頂点座標の設定
	pVtx[(nCount * 2) + nVertex].pos = m_pos + Distance + D3DXVECTOR3(0.0f, 0.0f, -m_fAllsize) / 2.0f;
	pVtx[(nCount * 2) + nVertex + 1].pos = m_pos + Distance + D3DXVECTOR3(0.0f, 0.0f, m_fAllsize) / 2.0f;

	// 中心の線を青に
	if (nCount == 5)
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
// 線を表示するかしないか
//=============================================================================
void CGrid::ShowLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const int nAxisLine)
{
	if (!m_bShow[nAxisLine])
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// 大きさの取得
//=============================================================================
float & CGrid::GetSize(void)
{
	return m_fsize;
}

//=============================================================================
// グリッドを表示するかしないかを取得
//=============================================================================
bool & CGrid::GetbShowLine(const int nAxisLine)
{
	return m_bShow[nAxisLine];
}
