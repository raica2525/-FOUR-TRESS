//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	input.h(ver.XInput)
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef INPUT_H_
#define INPUT_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include <Windows.h>
#include<XInput.h>

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// ライブラリのインポート
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#pragma comment (lib,"xinput.lib")

typedef struct
{
	float x;
	float y;
}D3DXVECTOR2;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

class CInput
{
public:

	CInput();
	~CInput();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	HRESULT GetState(int nPad, XINPUT_STATE* state);
	bool GetButtonState(int nPad, WORD wButtons);
	bool GetTriggerState(int nPad,int LR,int nDeadzone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	int GetConnectedPadNum(void);
	D3DXVECTOR2 GetStickValue(int nPad,int LR);
	void StartVibration(int nPad, int LMoter, int RMoter);
	void StopVibration(int nPad);
	static CInput* Create(void);
private:
	bool m_abConnected[XUSER_MAX_COUNT];
};

#endif // !INPUT_H_
