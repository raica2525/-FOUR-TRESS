//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imdebugwindow.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _IMDEBUGWINDOW_H_
#define _IMDEBUGWINDOW_H_

#include "main.h"
#include "imguiwindow.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CImDebugWindow : public CImGuiWindow
{
public:

	CImDebugWindow();		//コンストラクタ
	~CImDebugWindow();		//デストラクタ
	void Init(void);
	void Update(void);		//更新関数
	static CImDebugWindow* Create(void);
};

#endif

