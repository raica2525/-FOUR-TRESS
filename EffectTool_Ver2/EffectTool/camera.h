//========================================================================================================================
//
// カメラ処理 [camera.h]
// Author : 伊藤陽梧
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
#define CAMERA_DISTANCE (750.0f)
#define CAMERA_VIEW_RANGE (25000.0f)			// 視野
#define CAMERA_VIEW_FOV D3DXToRadian(45.0f)		// 視野角
#define CAMERA_INIT_PHI (D3DXToRadian(90.0f))	// ファイの初期値
#define CAMERA_INIT_THETA (D3DXToRadian(-90.0f))	// シータの初期値

//================================================
// カメラクラス宣言
//================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	CCamera *Create(void);		// 生成処理
	void ResetGameCamera(void);	// カメラのリセット

	float GetDistance(void) { return m_fDistance; }	// 距離の取得
	float GetPhi(void) { return m_fPhi; }			// ファイの取得
	float GetTheta(void) { return m_fTheta; }		// シータの取得

private:
	D3DXVECTOR3	m_posRDest;			// カメラの注視点（目的値）
	D3DXVECTOR3	m_posVDest;			// カメラの座標（目的値）
	D3DXVECTOR3	m_posV;				// カメラの座標
	D3DXVECTOR3	m_posR;				// 注視点
	D3DXVECTOR3	m_vecU;				// 上方向のベクトル
	D3DXMATRIX	m_mtxProjection;	// プロジェクションマトリクス
	D3DXMATRIX	m_mtxView;			// ビューマトリクス
	float		m_fDistance;		// 距離
	float		m_fPhi;				// ファイ
	float		m_fTheta;			// シータ
};

#endif