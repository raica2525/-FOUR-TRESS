//====================================================================
//
// シーン上の2Dポリゴン処理 (scene2d.h)
// Author : 後藤慎之助、池田悠希（テクスチャブレンディング対応）
//
//====================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "object.h"

//================================================
// マクロ定義
//================================================
#define MAX_BREND_TEXTURE (4)			// テクスチャブレンドの最大数    //池田追加
#undef MAX_BREND_TEXTURE

#define MAX_ANIM_COUNTER (10000)        // アニメーションのカウンタを利用する際の、最大カウント

//================================================
// クラス宣言
//================================================

// 2Dポリゴンクラス
class CScene2D : public CObject
{
public:
	CScene2D();
	virtual ~CScene2D();
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindTexture(const int nNumTexture);                                   // テクスチャを割り当てる
	void SetVertex(void);                                                                                       // 頂点座標を設定
	void SetRotVertex(float fAngle);                                                                            // 回転する頂点座標を設定
	void SetVisualVertex(D3DXVECTOR3 posVisual, D3DXVECTOR3 sizeVisual);                                        // 見かけ上の頂点座標を設定
	void SetTextureRange(int nRange, int nPattern);                                               // テクスチャの描画範囲を設定
	void SetTexturePlace(int nPlace, int nPattern);                                               // テクスチャの描画場所を決める

	/*========================================================
	y// セッター
	y//======================================================*/
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetAlphaTestBorder(int nValue) { m_nAlphaTestBorder = nValue; }
	void SetAdditiveSynthesis(void) { m_bAdditiveSynthesis = true; }
	void SetColor(D3DXCOLOR col);


	/*========================================================
	// ゲッター
	//======================================================*/
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	static bool m_bAdditiveSynthesis;                       // 加算合成するかどうか
	LPDIRECT3DTEXTURE9		m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		                // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;	                        // 位置
	D3DXVECTOR3             m_size;                         // 大きさ
	int m_nAlphaTestBorder;                                 // アルファテストの境界値
};

#endif