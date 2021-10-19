//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	immapwindow.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _IMMAPWINDOW_H_
#define _IMMAPWINDOW_H_

#include "main.h"
#include "imguiwindow.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CImMapWindow : public CImGuiWindow
{
public:

	CImMapWindow();		//コンストラクタ
	~CImMapWindow();		//デストラクタ
	void Init(void);
	void Update(void);		//更新関数
	static CImMapWindow* Create(void);
};

#endif

