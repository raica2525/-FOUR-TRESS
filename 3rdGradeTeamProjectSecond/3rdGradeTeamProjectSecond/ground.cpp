//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	ground.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "ground.h"
#include "manager.h"
#include "polygon3d.h"
#include "texturemanager.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
const float CGround::DEFAULT_SIZE = 500.0f;
const std::string CGround::DEFAULT_NAME = "Ground";
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGround::CGround()
{
	m_fAngle = 0.0f;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGround::~CGround()
{

}



//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CGround::Update(void)
{
	pPolygon3D->SetPos(GetPos());
	pPolygon3D->SetSize(GetSize());
	pPolygon3D->SetRot(D3DXVECTOR3(90.0f, m_fAngle, 0.0f));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CGround::Uninit(void)
{
	if (pPolygon3D != NULL)
	{
		pPolygon3D->Uninit();
		pPolygon3D = NULL;
	}

	CMapObject::Uninit();
}

void CGround::SetTexKey(const std::string &key)
{
	m_texKey = key;
	pPolygon3D->BindTexture(CManager::GetTextureManager()->GetTexture(key));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// デフォルト生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGround* CGround::CreateDefault(void)
{
	CGround* pGround = new CGround;
	pGround->m_name = DEFAULT_NAME;
	pGround->SetSize(D3DXVECTOR3(DEFAULT_SIZE, DEFAULT_SIZE, 0.0f));
	pGround->pPolygon3D = CPolygon3D::Create(ZERO_VEC, D3DXVECTOR3(90.0f, 0.0f, 0.0f), pGround->GetSize());
	return pGround;
}

CGround* CGround::Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR3 size, std::string name, std::string textureName)
{
	CGround* pGround = new CGround;
	pGround->m_fAngle = fAngle;
	pGround->m_name = name;
	pGround->SetPos(pos);
	pGround->SetSize(size);
	pGround->pPolygon3D = CPolygon3D::Create(pos, D3DXVECTOR3(90.0f, fAngle, 0.0f),size);
	pGround->SetTexKey(textureName);
	return pGround;
}

