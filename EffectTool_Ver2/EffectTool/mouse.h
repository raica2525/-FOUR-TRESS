//====================================================================
//
// マウスの処理 (mouse.h)
// Author : 伊藤陽梧
//
//====================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "input.h"

//================================================
// マクロ定義
//================================================
#define MAX_MOUSE_BOTTON (3)//キーの最大数

#define MOUSE_SENSITIVITY (0.0025f)	// マウス感度
#define MOUSE_WHEEL_SENSITIVITY (1.0f)	// マウスホイール感度

// マウスのクラス
class CMouse : public CInput
{
public:
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetMousePress(int nKey);
	bool GetMouseTrigger(int nKey);
	bool GetMouseRelease(int nKey);

	D3DXVECTOR3 GetMouseMove(void);
	float GetMouseWheel(void);

	float& GetMouseSensi(void);
	float& GetWheelSensi(void);
private:
	BYTE m_aMouseState[MAX_MOUSE_BOTTON];			// キーボードの入力情報ワーク
	BYTE m_aMouseStateTrigger[MAX_MOUSE_BOTTON];	// キーボードのトリガー情報
	BYTE m_aMouseStateRelease[MAX_MOUSE_BOTTON];	// キーボードのリリース情報
	DIMOUSESTATE m_mousState;						// マウス状態
	float m_fMouseSensi;							// マウスのセンシ
	float m_fWheelSensi;							// ホイールのセンシ
};

#endif