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
#include "texture.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGround::CGround():CPolygon3D(CScene::OBJTYPE_BG)
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
	SetRot(D3DXVECTOR3(90.0f, m_fAngle, 0.0f));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 名前でテクスチャを指定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CGround::SetTexKey(const std::string &key)
{
	CTexture* pTexture = CManager::GetTexture();
	BindTexture(pTexture->GetInfo(pTexture->GetIndexByName(key))->pTexture);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGround* CGround::Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR3 size, std::string textureName)
{
	CGround* pGround = new CGround;
	pGround->m_fAngle = fAngle;
	pGround->SetTexKey(textureName);
	return pGround;
}

