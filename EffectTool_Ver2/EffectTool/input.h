//====================================================================
//
// 入力処理 (input.h)
// Author : 伊藤陽梧
//
//====================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//================================================
// クラス宣言
//================================================

// 入力のクラス
class CInput
{
public:
	CInput();
	virtual ~CInput();  // 親クラスのデストラクタにvirtualをつけることで、メモリリークを抑える
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;	// 入力デバイスへのポインタ
	static LPDIRECTINPUT8 m_pInput;	// DirectInputへのポインタ
};
#endif