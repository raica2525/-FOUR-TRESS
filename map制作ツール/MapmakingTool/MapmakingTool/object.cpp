//===============================================
//
// シーン上のオブジェクト処理 (scene.cpp)
// Author : 後藤慎之助
//
//===============================================

//========================
// インクルードファイル
//========================
#include "object.h"
#include "renderer.h"

//========================================
// 静的メンバ変数宣言
//========================================
int CObject::m_nNumObjectAll = 0;

CObject *CObject::m_apTop = {};
CObject *CObject::m_apCur = {};

//========================================
// シーン上のオブジェクトのオーバーライドされたコンストラクタ
// Author : 後藤慎之助
//========================================
CObject::CObject()
{
	// 先頭がないなら、先頭に
	if (m_apTop == NULL)
	{
		m_apTop = this;
	}

	// 現在における最新のオブジェクトがないなら、最新に
	if (m_apCur == NULL)
	{
		m_apCur = this;
	}

	// 現在のオブジェクトの次のオブジェクトを、自分にする
	m_apCur->m_pNext = this;

	// 現在のオブジェクトが自分の場合
	if (m_apCur == this)
	{
		// 自分の前のオブジェクトを、NULLにする
		m_pPrev = NULL;
	}
	else
	{
		// 自分の前のオブジェクトを、現在のオブジェクトにする
		m_pPrev = m_apCur;
	}

	// 現在のオブジェクトを、自分にする
	m_apCur = this;

	// 自分の次のオブジェクトを、NULLにする
	m_pNext = NULL;

	// 全体の数をインクリメント
	m_nNumObjectAll++;

	// 使用するフラグをtrueに
	m_bUse = true;
}

//========================================
// シーン上のオブジェクトのデストラクタ
// Author : 後藤慎之助
//========================================
CObject::~CObject()
{

}

//==============================================
// シーン上のオブジェクトを全て更新
// Author : 後藤慎之助
//==============================================
void CObject::UpdateAll(void)
{
	// 先頭、最新のものがあるなら
	if (m_apTop != NULL && m_apCur != NULL)
	{
		// 記憶用の変数
		CObject* pObject = m_apTop;

		do
		{
			// 記憶用の変数(Update中に、Uninitされることを考慮)
			CObject* pNextScene = pObject->m_pNext;

			// 更新処理
			pObject->Update();

			// 使用フラグがfalseなら
			if (pObject->m_bUse == false)
			{
				// メモリの開放
				delete pObject;
				pObject = NULL;
			}

			// 次のシーンに変えていく
			pObject = pNextScene;

		} while (pObject != NULL);
	}
}

//==============================================
// シーン上のオブジェクトを全て描画
// Author : 東村哲士
//==============================================
void CObject::DrawAll(void) 
{
	// 先頭、最新のものがあるなら
	if (m_apTop != NULL && m_apCur != NULL)
	{
		// 記憶用の変数
		CObject* pObject = m_apTop;

		do
		{
			// 記憶用の変数(Update中に、Uninitされることを考慮)
			CObject* pNextScene = pObject->m_pNext;

			// 更新処理
			pObject->Draw();

			// 使用フラグがfalseなら
			if (pObject->m_bUse == false)
			{
				// メモリの開放
				delete pObject;
				pObject = NULL;
			}

			// 次のシーンに変えていく
			pObject = pNextScene;

		} while (pObject != NULL);
	}
}

//==============================================
// シーン上のオブジェクトを全て開放
// Author : 後藤慎之助
//==============================================
void CObject::ReleaseAll(void)
{
	// 先頭、最新のものがあるなら
	if (m_apTop != NULL && m_apCur != NULL)
	{
		// 記憶用の変数
		CObject* pObject = m_apTop;

		do
		{
			// 記憶用の変数
			CObject* pNextScene = pObject->m_pNext;

			// 終了処理
			pObject->Uninit();

			// 使用フラグがfalseなら
			if (pObject->m_bUse == false)
			{
				// メモリの開放
				delete pObject;
				pObject = NULL;
			}

			// 次のシーンに変えていく
			pObject = pNextScene;

		} while (pObject != NULL);
	}
}

//==============================================
// シーン上のオブジェクトを全て開放
// Author : 後藤慎之助
//==============================================
void CObject::Release(void)
{
	// 中身があるなら、
	if (this != NULL)
	{
		// 先頭なら
		if (this == m_apTop)
		{
			// 次の中身があるなら
			if (m_pNext != NULL)
			{
				// 次のものの前の情報を、NULLに
				m_pNext->m_pPrev = NULL;

				// それを先頭に
				m_apTop = m_pNext;
			}
			else
			{
				// 先頭の次がないなら、先頭と現在を示すポインタをNULLに
				m_apTop = NULL;
				m_apCur = NULL;
			}
		}
		// 先頭でないなら
		else
		{
			// 次の中身があるなら
			if (m_pNext != NULL)
			{
				// 前のものの次の情報を、自身の次の情報に
				m_pPrev->m_pNext = m_pNext;

				// 次のものの前の情報を、自身の前の情報に
				m_pNext->m_pPrev = m_pPrev;
			}
			else
			{
				// 前のものの次の情報を、なくす
				m_pPrev->m_pNext = NULL;

				// 現在の最新のものを、前の情報に
				m_apCur = m_pPrev;
			}
		}

		//// メモリの開放(リスト構造はm_pNextでシーンを切り替えていく際に支障が出るので、ここでは行わない)
		//delete this;
		////this = NULL;

		// 使用フラグをfalseに
		m_bUse = false;

		// 全体の数をデクリメント
		m_nNumObjectAll--;
	}
}
