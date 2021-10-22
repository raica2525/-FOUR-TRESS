//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CRenderer;
class CCamera;
class CImGuiManager;
class CModelData;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CManager
{
public:
	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);	//初期化関数
	void Uninit(void);						//終了関数
	void Update(void);						//更新関数
	void Draw(void);						//描画関数
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CImGuiManager* GetImGuiManager(void) { return m_pImGuiManager; }
	static CModelData* GetModelData(void) { return m_pModelData; }
	static void LoadFile(void);
	static void UnloadFiles(void);

private:
	static CImGuiManager* m_pImGuiManager;
	static CRenderer* m_pRenderer;			//レンダラのポインタ
	static CCamera* m_pCamera;
	static CModelData* m_pModelData;
};

#endif

