//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene3d.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CModel;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//オブジェクトクラス
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CScene3d : public CScene
{
public:
	CScene3d();
	virtual ~CScene3d();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void)	= 0;
	virtual void Draw(void)		= 0;

	void SetPos(D3DXVECTOR3 pos)	{ m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot)	{ m_rot = rot; }
	void SetSize(D3DXVECTOR3 size)	{ m_size = size; }
	D3DXVECTOR3 GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 GetRot(void)		{ return m_rot; }
	D3DXVECTOR3 GetSize(void)		{ return m_size; }
private:
	D3DXVECTOR3	m_pos;								// 位置
	D3DXVECTOR3 m_rot;								// 回転情報
	D3DXVECTOR3 m_size;								// サイズ
};

#endif