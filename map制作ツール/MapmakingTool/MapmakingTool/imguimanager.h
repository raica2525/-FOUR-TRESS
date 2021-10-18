//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imguimanager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _IMGUIMANAGER_H_
#define _IMGUIMANAGER_H_

#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CImGuiWindow;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CImGuiManager
{
public:

	enum IMWINDOW
	{
		IMWINDOW_OBJ_INFO = 0,
		IMWINDOW_MAP_INFO,
		IMWINDOW_DEBUG_INFO,
		IMWINDOW_MAX,
	};

	CImGuiManager();		//コンストラクタ
	~CImGuiManager();		//デストラクタ

	void Init(HWND hWnd);	//初期化関数
	void Uninit(void);		//終了関数
	void Update(void);		//更新関数
	void Draw(void);		//描画関数
	CImGuiWindow* GetImGuiWindow(IMWINDOW imWindow) { return m_pImGuiWindow[imWindow]; };

private:
	CImGuiWindow* m_pImGuiWindow[IMWINDOW_MAX];
};

#endif

