//====================================================================
//
// 建物の処理 (enemy.h)
// Author : 東村哲士
//
//====================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene3d.h"

//================================================
// 前方宣言
//================================================

class CEnemy : public CScene3D 
{
public:
	CEnemy();
	~CEnemy();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
};

#endif