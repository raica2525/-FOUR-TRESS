//========================================================================================================================
//
// カメラ処理 [camera.h]
// Author : 後藤慎之助
//
//========================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//================================================
// マクロ定義
//================================================

// カメラの振動
#define SHAKE_VALUE_BALL_HIT_WALL 6.25f
#define SHAKE_VALUE_SHOOT_BALL_SMALL 25.0f
#define SHAKE_VALUE_SHOOT_BALL_BIG 50.0f
#define SHAKE_VALUE_SHOOT_BALL_ULTRA 50.0f

#define CAMERA_DEFAULT_ROT D3DXToRadian(90.0f)

//================================================
// カメラクラス宣言
//================================================
class CCamera
{
public:
    CCamera();
    ~CCamera();

    // カメラの状態
    typedef enum
    {
        STATE_NONE = 0,         // なし
        STATE_OUT_GAME,         // アウトゲーム
        STATE_BUTTLE,           // バトル中
        STATE_FINISH_EACH,      // 決着時の各自注視
        STATE_SP,               // 必殺技中
    }STATE;

    // カメラの使用場面
    typedef enum
    {
        SETTING_GAME = 0,         // ゲーム中
        SETTING_CUSTOM,           // カスタマイズ中
    }SETTING;

    // カメラの振動段階
    typedef enum
    {
        SHAKE_PHASE_NONE = 0,
        SHAKE_PHASE_1,
        SHAKE_PHASE_2,
        SHAKE_PHASE_3,
        SHAKE_PHASE_4,
        SHAKE_PHASE_5,
        SHAKE_PHASE_6,
        SHAKE_PHASE_MAX
    }SHAKE_PHASE;

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    CCamera *Create(void);
    void ResetCamera(D3DXVECTOR3 pos, float fRot, SETTING setting);     // カメラのリセット
    void Shake(void);

    /*========================================================
    // セッター
    //======================================================*/
    void SetState(STATE state) { m_nCntState = 0; m_shakePhase = SHAKE_PHASE_NONE; m_state = state; }    // 状態をセットするときは、カウンタも同時にリセット
    void SetLookAt(D3DXVECTOR3 pos) { m_posRDest = pos; }
    void SetShake(float fShakeValue, bool bResetShake = true);

    /*========================================================
    // ゲッター
    //======================================================*/
    STATE GetState(void) { return m_state; }
    D3DXVECTOR3 GetPos(void) { return m_posV; }
    D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }
    D3DXMATRIX GetViewMtx(void) { return m_mtxView; }

private:
    D3DXVECTOR3	m_posRDest;         // カメラの注視点（目的値）
    D3DXVECTOR3	m_posVDest;         // カメラの座標（目的値）
    STATE m_state;                  // カメラの状態
    D3DXVECTOR3	m_posV;             // カメラの座標
    D3DXVECTOR3	m_pos;              // カメラの座標
    D3DXVECTOR3	m_posR;             // 注視点
    D3DXVECTOR3	m_vecU;             // 上方向のベクトル
    D3DXMATRIX	m_mtxProjection;    // プロジェクションマトリクス
    D3DXMATRIX	m_mtxView;          // ビューマトリクス
    float		m_fDistance;        // 距離
    float		m_fPhi;             // 横回転
    float		m_fTheta;           // 縦回転
    int m_nCntState;                // 状態カウンタ
    int m_shakePhase;               // 振動段階
    float m_fShakeValue;            // 振動量
};

#endif