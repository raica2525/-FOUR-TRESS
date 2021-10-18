//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imobjectwindow.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _IMOBJECTWINDOW_H_
#define _IMOBJECTWINDOW_H_

#include "main.h"
#include "imguiwindow.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CImObjectWindow : public CImGuiWindow
{
public:

	CImObjectWindow();		//コンストラクタ
	~CImObjectWindow();		//デストラクタ
	void Init(void);
	void Update(void);		//更新関数
	static CImObjectWindow* Create(void);
};

#endif

