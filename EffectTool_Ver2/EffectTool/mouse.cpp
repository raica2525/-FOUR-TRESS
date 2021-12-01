//====================================================================
//
// マウスの処理 (mouse.cpp)
// Author : 伊藤陽梧
//
//====================================================================

//========================
// インクルードファイル
//========================
#include "mouse.h"

//========================================================
// マウスクラスのコンストラクタ
//========================================================
CMouse::CMouse()
{
	memset(m_aMouseState, 0, sizeof(m_aMouseState));
	memset(m_aMouseStateTrigger, 0, sizeof(m_aMouseStateTrigger));
	memset(m_aMouseStateRelease, 0, sizeof(m_aMouseStateRelease));
	memset(m_mousState.rgbButtons, 0, sizeof(m_mousState.rgbButtons));
	m_mousState.lX = 0;
	m_mousState.lY = 0;
	m_mousState.lZ = 0;
	m_fMouseSensi = MOUSE_SENSITIVITY;
	m_fWheelSensi = MOUSE_WHEEL_SENSITIVITY;
}

//========================================================
// マウスクラスのデストラクタ
//========================================================
CMouse::~CMouse()
{

}

//========================================================
// マウスの初期化
//========================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	m_pDevice->Acquire();
	return S_OK;
}

//========================================================
// マウスの終了処理
//========================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}


//========================================================
// マウスの更新処理
//========================================================
void CMouse::Update(void)
{
	HRESULT hr;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mousState);

		//デバイスからデータを取得
		if (SUCCEEDED(hr))
		{
			for (int nCntKey = 0; nCntKey < MAX_MOUSE_BOTTON; nCntKey++)
			{
				//キートリガー
				m_aMouseStateTrigger[nCntKey] = (m_aMouseState[nCntKey] ^ m_mousState.rgbButtons[nCntKey]) &  m_mousState.rgbButtons[nCntKey];

				//キーリリース
				m_aMouseStateRelease[nCntKey] = (m_aMouseState[nCntKey] ^ m_mousState.rgbButtons[nCntKey]) & ~m_mousState.rgbButtons[nCntKey];

				//キープレス情報を保存
				m_aMouseState[nCntKey] = m_mousState.rgbButtons[nCntKey];
			}
		}
		else
		{
			m_pDevice->Acquire();
		}
	}

	//マウスの感度とホイールの感度がマイナスにならないように
	if (m_fMouseSensi < 0)
	{
		m_fMouseSensi = 0;
	}
	if (m_fWheelSensi < 0)
	{
		m_fWheelSensi = 0;
	}
}

//========================================================
// マウスのプレスの情報を取得
//========================================================
bool CMouse::GetMousePress(int nKey)
{
	return m_aMouseState[nKey] & 0x80 ? true : false;
}

//========================================================
// マウスのトリガーの情報を取得
//========================================================
bool CMouse::GetMouseTrigger(int nKey)
{
	return m_aMouseStateTrigger[nKey] & 0x80 ? true : false;
}

//========================================================
// マウスのリリースの情報を取得
//========================================================
bool CMouse::GetMouseRelease(int nKey)
{
	return m_aMouseStateRelease[nKey] & 0x80 ? true : false;
}

//========================================================
// マウスの移動量を取得
//========================================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3((float)m_mousState.lX, (float)m_mousState.lY, 0.0f) * m_fMouseSensi;
}

//========================================================
// マウスのホイールを取得
//========================================================
float CMouse::GetMouseWheel(void)
{
	return (float)m_mousState.lZ * m_fWheelSensi;
}

//========================================================
// マウスの感度を取得
//========================================================
float & CMouse::GetMouseSensi(void)
{
	return m_fMouseSensi;
}

//========================================================
// ホイールの感度を取得
//========================================================
float & CMouse::GetWheelSensi(void)
{
	return m_fWheelSensi;
}
