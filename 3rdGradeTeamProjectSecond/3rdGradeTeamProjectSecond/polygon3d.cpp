//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	polygon3d.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "polygon3d.h"
#include "manager.h"
#include "renderer.h"



//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPolygon3D::CPolygon3D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_bShow = true;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPolygon3D::~CPolygon3D()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CPolygon3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_3D* pVtx = NULL;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 size = GetSize();
	pVtx[0].pos = D3DXVECTOR3(-size.x / 2.0f,  size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3( size.x / 2.0f,  size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3( size.x / 2.0f, -size.y / 2.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DCOLOR col = GetCol();
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPolygon3D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene3D::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPolygon3D::Update(void)
{
	VERTEX_3D* pVtx = NULL;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 size = GetSize();
	pVtx[0].pos = D3DXVECTOR3(-size.x / 2.0f,  size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3( size.x / 2.0f,  size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3( size.x / 2.0f, -size.y / 2.0f, 0.0f);

	D3DCOLOR col = GetCol();
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPolygon3D::Draw(void)
{
	if (m_bShow)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
		D3DXVECTOR3 rot = GetRot();
		D3DXVECTOR3 pos = GetPos();

		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//アルファテスト有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 40);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		//単位行列生成
		D3DXMatrixIdentity(&mtxWorld);
		//回転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(rot.y), D3DXToRadian(rot.x), D3DXToRadian(rot.z));
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		//移動
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
		//行列適用
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pDevice->SetTexture(0, m_pTexture);
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetTexture(0, NULL);

		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPolygon3D* CPolygon3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPolygon3D* pPolygon3D = new CPolygon3D;

	pPolygon3D->SetPos(pos);
	pPolygon3D->SetRot(rot);
	pPolygon3D->SetSize(size);

	pPolygon3D->Init();

	return pPolygon3D;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// テクスチャ設定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPolygon3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
