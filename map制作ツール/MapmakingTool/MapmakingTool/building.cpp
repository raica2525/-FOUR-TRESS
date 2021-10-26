//===============================================
//
// 建物の処理 (building.cpp)
// Author : 東村哲士
//
//===============================================

//========================
// インクルードファイル
//========================
#include "building.h"
#include "manager.h"
#include "renderer.h"

//========================
// コンストラクタ
//========================
CBuilding::CBuilding() 
{
}

//========================
// デストラクタ
//========================
CBuilding::~CBuilding() 
{
}

//========================
// 初期化処理
//========================
HRESULT CBuilding::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) 
{
	CScene3D::Init(pos, scale);

	SetScale(scale);

	return S_OK;
}

//========================
// 更新処理
//========================
void CBuilding::Update() 
{

}

//========================
// 描画処理
//========================
void CBuilding::Draw() 
{
	// ステンシルバッファを使う
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Zテスト有効
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// Zテストを必ず失敗に
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

	// ステンシルテスト有効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// ステンシルバッファへ反映する参照値
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	// 参照値マスク
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	// ステンシルテストを必ず成功に
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// ステンシルテストのテスト設定
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// 通常の描画の前後で、スケールをいじる
	D3DXVECTOR3 memoryScale = GetScale();
	CScene3D::Draw(false, false);
	SetScale(memoryScale);

	// ステンシルテスト無効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// ZBUFFER比較設定変更 => (参照値 <= バッファ値)(戻す)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// 通常の描画
	CScene3D::Draw(false, false);
}

//========================
// 終了処理
//========================
void CBuilding::Uninit() 
{
	CScene3D::Uninit();
}

//========================
// 生成処理
//========================
CBuilding* CBuilding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot) 
{
	// ポインタを用意
	CBuilding *pBuilding = NULL;

	// メモリ確保
	pBuilding = new CBuilding;

	// 初期化
	pBuilding->Init(pos, scale);

	// 向き設定
	pBuilding->SetRot(rot);

	return pBuilding;
}