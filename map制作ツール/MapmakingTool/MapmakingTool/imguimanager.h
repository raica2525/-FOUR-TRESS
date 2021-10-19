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
	bool GetShowStructure(void) { return m_bShowStructures; };
	bool GetShowCollisions(void) { return m_bShowCollisions; };
	void GetStr(char* _Dest) { strcpy(_Dest, m_str); };

	void SetShowStructures(bool bShowStructures) { m_bShowStructures = bShowStructures; };
	void SetShowCollisions(bool bShowCollisions) { m_bShowCollisions = bShowCollisions; };
	void SetStr(char* str) { strcpy(m_str, str); };
private:
	bool m_bShowStructures;
	bool m_bShowCollisions;
	bool m_bShowEnemys;
	char m_str[1024];
	CImGuiWindow* m_pImGuiWindow[IMWINDOW_MAX];
};

#endif

