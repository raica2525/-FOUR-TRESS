//====================================================================
//
// シーン上のオブジェクト処理 (scene.h)
// Author : 伊藤陽梧
//
//====================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//================================================
// マクロ定義
//================================================

//================================================
// クラス宣言
//================================================

// オブジェクトのクラス
class CScene
{
public:
	// オブジェクトの種類(描画順)
	typedef enum
	{
		OBJTYPE_NONE,				// なし
		OBJTYPE_GRID,				// グリッド
		OBJTYPE_EFFECT3D,			// エフェクト3D
		OBJTYPE_EFFECT3D_Z_NONE,	// エフェクト3D、Zバッファなし
		OBJTYPE_MAX					// オブジェクトの種類の最大数
	}OBJTYPE;

	CScene();
	CScene(OBJTYPE objType);	// イニシャライザでオブジェクトタイプを紐づけ
	virtual ~CScene();			// 親クラスのデストラクタにvirtualをつけることで、メモリリークを抑える
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);											// 全て更新
	static void DrawAll(void);												// 全て描画
	static void QuickSort(CScene*apScene[], int left, int right);			// クイックソート
	static void ReleaseAll(void);											// 全て開放

	static int GetNumObjAll(void) { return m_nNumObjectAll; }				// シーン上の全てのオブジェクト個数
	static int GetNumAll(OBJTYPE objtype) { return m_nNumAll[objtype]; }	// その種類の全体の数を取得
	static CScene*GetTopScene(OBJTYPE objtype) { return m_pTop[objtype]; }	// その種類の先頭のオブジェクトを取得
	CScene* GetNextScene(void) { return m_pNext; }							// 次のオブジェクトを取得

protected:
	void Release(void);					// 単体を開放

private:
	static CScene *m_pTop[OBJTYPE_MAX];	// 先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];	// 現在における最新のオブジェクトへのポインタ
	CScene *m_pPrev;					// 前のオブジェクトへのポインタ
	CScene *m_pNext;					// 次のオブジェクトへのポインタ

	static int m_nNumObjectAll;			// シーン上のすべてのオブジェクトの数
	static int m_nNumAll[OBJTYPE_MAX];	// シーン上の種類ごとのオブジェクトの最大数
	OBJTYPE m_objType;					// オブジェクトの種類

	bool m_bUse;						// 使用するかどうか
};

#endif