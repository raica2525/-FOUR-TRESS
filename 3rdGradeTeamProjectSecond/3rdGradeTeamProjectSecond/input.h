//====================================================================
//
// 入力処理 (input.h)
// Author : 後藤慎之助、池田悠希（コントローラの振動対応）
//
//====================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include <XInput.h>
//================================================
// ライブラリのリンク
//================================================
#pragma comment (lib,"xinput.lib")
//================================================
// マクロ定義
//================================================
#define NUM_KEY_MAX (256)//キーの最大数

#define BUTTON_UP     (0)	    // 十字キー上
#define BUTTON_DOWN   (18000)	// 十字キー下
#define BUTTON_LEFT   (27000)	// 十字キー左
#define BUTTON_RIGHT  (9000)	// 十字キー右

#define BUTTON_UP_RIGHT     (4500)	// 十字キー上右
#define BUTTON_RIGHT_DOWN  (13500)	// 十字キー右下
#define BUTTON_DOWN_LEFT   (22500)	// 十字キー下左
#define BUTTON_LEFT_UP   (31500)	// 十字キー左上

#define BUTTON_NEUTRAL -1       // 何も入力していないとき
#define CROSSZONE (4500)        // 十字キーの許容範囲

// スティックの各範囲を判別
#define STICK_UP(angle) angle < D3DXToRadian(45.0f) && angle > D3DXToRadian(-45.0f)
#define STICK_RIGHT(angle) angle >= D3DXToRadian(45.0f) && angle <= D3DXToRadian(135.0f)
#define STICK_DOWN(angle) angle > D3DXToRadian(135.0f) && angle <= D3DXToRadian(180.0f) || angle < D3DXToRadian(-135.0f) && angle > D3DXToRadian(-180.0f)
#define STICK_LEFT(angle) angle <= D3DXToRadian(-45.0f) && angle >= D3DXToRadian(-135.0f)

// バイブレーションの最大強さ
#define MAX_VIBRATION_POWER (65535)

// スティックの最大傾き
#define STICK_MAX_TILT (32767)

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

// キーボード入力のクラス
class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();
    ~CInputKeyboard();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit(void);
    void Update(void);
    bool GetKeyboardPress(int nKey);
    bool GetKeyboardTrigger(int nKey);
    bool GetKeyboardRelease(int nKey);

private:
    BYTE m_aKeyStateOld[NUM_KEY_MAX];       // 1F前のキーボードの入力情報ワーク
    BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報
    BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報
};

// ジョイパッドのクラス
class CInputJoypad : public CInput
{
public:

	enum LR
	{
		LEFT = 0,
		RIGHT,
		LR_MAX,
	};

	enum BEHAVIOR
	{
		BEHAVIOR_AND = 0,
		BEHAVIOR_OR,
		BEHAVIOR_MAX
	};

	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	HRESULT GetState(int nPad, XINPUT_STATE* state);
	bool GetButtonState(int nPad, WORD wButtons, BEHAVIOR behavir = BEHAVIOR_AND);
	bool GetTriggerState(int nPad, LR LR, int nDeadzone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	int GetConnectedPadNum(void);
	D3DXVECTOR2 GetStickValue(int nPad, LR LR);
	void StartVibration(int nPad, int LMoter, int RMoter, int nFrame = -1);
	void StopVibration(int nPad);
	static CInputJoypad* Create(void);

	bool GetJoypadTrigger(int nPad, WORD wButtons, BEHAVIOR behavir = BEHAVIOR_AND);
	bool GetJoypadRelease(int nPad, WORD wButtons, BEHAVIOR behavir = BEHAVIOR_AND);
private:
	bool m_abConnected[XUSER_MAX_COUNT];
	int m_anRemainFrameVibration[XUSER_MAX_COUNT]; 
	XINPUT_STATE m_aJoyStateOld[XUSER_MAX_COUNT];
	WORD m_aJoyStateTrigger[XUSER_MAX_COUNT];	// ジョイパッドのトリガー情報
	WORD m_aJoyStateRelease[XUSER_MAX_COUNT];	// ジョイパッドのリリース情報
};

//class CInputJoypad :public CInput
//{
//public:
//
//    // ボタンの種類
//    typedef enum
//    {
//        BUTTON_X = 0,
//        BUTTON_Y,
//        BUTTON_A,
//        BUTTON_B,
//        BUTTON_L1,
//        BUTTON_R1,
//        BUTTON_L2,
//        BUTTON_R2,
//        BUTTON_L3,
//        BUTTON_R3,
//        BUTTON_SELECT,
//        BUTTON_START,
//        BUTTON_GUIDE,
//        MAX_BUTTON
//    }BUTTON;
//
//    // コントローラの情報
//    typedef struct
//    {
//        LPDIRECTINPUTDEVICE8 pDIJoypad = NULL; // コントローラーデバイス
//        DIJOYSTATE2 State;       // コントローラーのプレス情報
//        DIJOYSTATE2 Trigger;     // コントローラーのトリガー情報
//        DIJOYSTATE2 Release;     // コントローラーのプレス情報
//    }CONTROLLER;
//
//    CInputJoypad();
//    ~CInputJoypad();
//    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
//    void Update(void);
//    void Release(void);
//    bool GetJoypadPress(int nController, int nButton);
//    bool GetJoypadTrigger(int nController, int nButton);
//    bool GetJoypadRelease(int nController, int nButton);
//    DIJOYSTATE2 GetController(int nController);
//    static LPDIRECTINPUT8 GetInput(void) { return m_pInput; }
//    HRESULT CreateDevice(LPDIDEVICEINSTANCE lpddi);
//    HRESULT StartEffect(int nController, int nFrame);	//池田追加
//    HRESULT StopEffect(int nController);				//池田追加
//    static HRESULT CALLBACK EnumObjectCallBack(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
//private:
//    static CONTROLLER m_aController[MAX_PLAYER];    // コントローラーの情報	//池田修正
//    static int m_nCntController;					// コントローラーの接続数
//    LPDIRECTINPUTEFFECT m_aEffectInput[MAX_PLAYER];	// エフェクトのポインタ//池田
//    int m_anFrameEffect[MAX_PLAYER];				// 振動する残りフレーム//池田
//    DWORD m_adwNumFFBAxis[MAX_PLAYER];				// 振動の軸の数//池田
//};

// マウスのクラス
class CMouse : public CInput
{
public:
    typedef struct _MSTATE {
        RECT    moveRect;     // 画面上で動ける範囲
        int     x;            // X座標
        int     y;            // Y座標
        bool    lButton;      // 左ボタン
        bool    rButton;      // 右ボタン
        bool    cButton;      // 真ん中ボタン
        int     moveAdd;      // 移動量
        RECT    imgRect;      // マウス用画像矩形
        int     imgWidth;     // マウス画像幅
        int     imgHeight;    // マウス画像高さ
    } MSTATE;

    CMouse();
    ~CMouse();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit(void);
    void Update(void);

    static MSTATE *GetMouse(void);
    bool GetMouseTriggerLeft(void);
    bool GetMouseTriggerRight(void);
    bool GetMousePressLeft(void);
    bool GetMousePressRight(void);

private:
    DIMOUSESTATE2 m_dIMouseState;
    static CMouse::MSTATE m_MState;
};

#endif