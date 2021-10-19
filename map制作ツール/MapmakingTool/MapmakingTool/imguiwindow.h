//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imguiwindow.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _IMGUIWINDOW_H_
#define _IMGUIWINDOW_H_

#include "main.h"
#include "imgui.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CImGuiWindow
{
public:

	CImGuiWindow();		//コンストラクタ
	virtual ~CImGuiWindow();		//デストラクタ

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;		//更新関数
	void ChangeShowWindow(void) { m_bShow = !m_bShow; };
	
protected:
	void SetMenuID(UINT unMenuID) { m_unMenuID = unMenuID; };
	UINT GetMenuID(void) { return m_unMenuID; };
	bool m_bShow;
	static const ImVec2 IMGUI_DEFAULT_SIZE;

private:
	UINT m_unMenuID;
};

#endif

