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
// 静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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
	SetRot(D3DXVECTOR3(90.0f, m_fAngle, 0.0f));
}

void CGround::SetTexKey(const std::string &key)
{
	m_texKey = key;
	BindTexture(CManager::GetTextureManager()->GetTexture(key));
}


CGround* CGround::Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR3 size, std::string textureName)
{
	CGround* pGround = new CGround;
	pGround->m_fAngle = fAngle;
	pGround->SetTexKey(textureName);
	return pGround;
}

