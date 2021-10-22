//====================================================================
//
// シーン上のオブジェクト処理 (scene.h)
// Author : 後藤慎之助
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
class CObject
{
public:
	CObject();    // イニシャライザでオブジェクトタイプを紐づけ
	virtual ~CObject();  // 親クラスのデストラクタにvirtualをつけることで、メモリリークを抑える
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);                                                        // 全て更新
	static void DrawAll(void);															// 全て描画
	static void ReleaseAll(void);                                                       // 全て開放

	static int GetNumObjAll(void) { return m_nNumObjectAll; }                           // シーン上の全てのオブジェクト個数
	static CObject*GetTopScene(void) { return m_apTop; }              // 先頭のオブジェクトを取得
	CObject* GetNextScene(void) { return m_pNext; }                                      // 次のオブジェクトを取得

/*============================================================================================================================
// オブジェクトのタイプごとでコンストラクタで次のシーン等を記憶しているため、絶対にオブジェクトタイプを書き換えてはいけない
//void SetObjType(OBJTYPE objtype) { m_objType = objtype; }
// トップに種類を入れて取得できるので、ゲッターも使う機会がなくなった
//OBJTYPE GetObjType(void) { return m_objType; }
============================================================================================================================*/

protected:
	void Release(void);                 // 単体を開放

private:
	static CObject *m_apTop;  // 先頭のオブジェクトへのポインタ
	static CObject *m_apCur;  // 現在における最新のオブジェクトへのポインタ
	CObject *m_pPrev;                      // 前のオブジェクトへのポインタ
	CObject *m_pNext;                      // 次のオブジェクトへのポインタ

	static int m_nNumObjectAll;          // シーン上のすべてのオブジェクトの数

	bool m_bUse;                         // 使用するかどうか
};

#endif