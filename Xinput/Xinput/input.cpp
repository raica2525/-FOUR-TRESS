//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	input.cpp(ver.XInput)
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "input.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CInputJoypad::CInputJoypad()
{
	ZeroMemory(m_abConnected, sizeof(m_abConnected));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CInputJoypad::~CInputJoypad()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CInputJoypad::Init(void)
{
	//XInputを有効化
	XInputEnable(true);
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputJoypad::Update(void)
{
	XINPUT_STATE state;
	for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
	{
		if (XInputGetState(nCount, &state) == ERROR_SUCCESS)
		{
			m_abConnected[nCount] = true;
		}
		else
		{
			m_abConnected[nCount] = false;
		}
	}
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputJoypad::Uninit(void)
{
	XInputEnable(false);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// コントローラーの状態を取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CInputJoypad::GetState(int nPad, XINPUT_STATE* pState)
{
	if (nPad < XUSER_MAX_COUNT)
	{
		XINPUT_STATE state;
		if (XInputGetState(nPad, &state) == ERROR_SUCCESS)
		{
			*pState = state;
			return S_OK;
		}
	}
	return E_FAIL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// ボタンの状態を取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CInputJoypad::GetButtonState(int nPad, WORD wButtons)
{
	XINPUT_STATE state;
	if ((GetState(nPad, &state)) == S_OK)
	{
		if (state.Gamepad.wButtons & wButtons)
		{
			return true;
		}
	}
	return false;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 接続されているコントローラーの数を取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
int CInputJoypad::GetConnectedPadNum(void)
{
	XINPUT_STATE state;
	int nPads = 0;
	for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
	{
		if (XInputGetState(nCount, &state) == ERROR_SUCCESS)
		{
			nPads++;
		}
	}
	return nPads;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// トリガーの押下状況を取得(LTrigger = 0,RTrigger = 1)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CInputJoypad::GetTriggerState(int nPad, int LR, int nDeadzone)
{
	XINPUT_STATE state;
	if (XInputGetState(nPad, &state) == ERROR_SUCCESS)
	{
		if (LR == 0)
		{
			if (state.Gamepad.bLeftTrigger > nDeadzone)
			{
				return true;
			}
		}
		else
		{
			if (state.Gamepad.bRightTrigger > nDeadzone)
			{
				return true;
			}
		}
	}
	return false;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// スティックの傾き具合を取得（LStick = 0, RStick = 1)（X軸 = 0, Y軸 = 1)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR2 CInputJoypad::GetStickValue(int nPad, int LR)
{
	XINPUT_STATE state;
	D3DXVECTOR2 vec2 = {};
	if (XInputGetState(nPad, &state) == ERROR_SUCCESS)
	{
		if (LR == 0)
		{
			if (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > state.Gamepad.sThumbLX &&
				-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbLX &&
				XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > state.Gamepad.sThumbLY &&
				-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbLY)
			{
				vec2.x = 0;
				vec2.y = 0;
			}
			else
			{
				vec2.x = state.Gamepad.sThumbLX;
				vec2.y = state.Gamepad.sThumbLY;
			}
		}
		else
		{
			if (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > state.Gamepad.sThumbRX &&
				-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < state.Gamepad.sThumbRX &&
				XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > state.Gamepad.sThumbRY &&
				-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < state.Gamepad.sThumbRY)
			{
				vec2.x = 0;
				vec2.y = 0;
			}
			else
			{
				vec2.x = state.Gamepad.sThumbRX;
				vec2.y = state.Gamepad.sThumbRY;
			}
		}
	}
	return vec2;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 振動を開始
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputJoypad::StartVibration(int nPad, int LMoter, int RMoter)
{
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = LMoter;
	vibration.wRightMotorSpeed = RMoter;
	XInputSetState(nPad, &vibration);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 振動を終了
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputJoypad::StopVibration(int nPad)
{
	StartVibration(nPad, 0, 0);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CInputJoypad* CInputJoypad::Create(void)
{
	CInputJoypad* pInput = new CInputJoypad;
	pInput->Init();

	return pInput;
}