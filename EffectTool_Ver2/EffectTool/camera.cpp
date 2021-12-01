//==============================================================================================================================
//
// カメラ処理 (camera.cpp)
// Author : 伊藤陽梧
//
//==============================================================================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	m_posRDest = DEFAULT_VECTOR;
	m_posVDest = DEFAULT_VECTOR;
	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_fDistance = CAMERA_DISTANCE;

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fPhi = CAMERA_INIT_PHI;
	m_fTheta = CAMERA_INIT_THETA;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ゲーム遷移時のカメラのリセット
//=============================================================================
void CCamera::ResetGameCamera(void)
{
	m_posRDest = DEFAULT_VECTOR;
	m_posVDest = DEFAULT_VECTOR;
	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_fDistance = CAMERA_DISTANCE;

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fPhi = CAMERA_INIT_PHI;
	m_fTheta = CAMERA_INIT_THETA;

	// 位置の目的地を更新(球面座標の公式)
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fPhi) * cosf(m_fTheta);
	m_posV.y = m_posR.y + m_fDistance * cosf(m_fPhi);
	m_posV.z = m_posR.z + m_fDistance * sinf(m_fPhi) * sinf(m_fTheta);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// カメラのリセット
	ResetGameCamera();

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, CAMERA_VIEW_FOV, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	//  カメラ位置修正処理
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 右クリックしているなら視点移動
	if (CManager::GetMouse()->GetMousePress(1) == true)
	{
		// カメラと自身の距離(マウスのホイールで距離の調節)
		m_fDistance -= CManager::GetMouse()->GetMouseWheel();

		// マウスの移動量を計算
		m_fTheta -= CManager::GetMouse()->GetMouseMove().x;
		m_fPhi -= CManager::GetMouse()->GetMouseMove().y;
	}

	// カメラの距離と視点移動が反転しないように
	if (m_fDistance < 0.0f)
	{
		m_fDistance = 0.0001f;
	}
	if (m_fPhi < 0.0f)
	{
		m_fPhi = 0.0001f;
	}
	else if(m_fPhi >= D3DX_PI)
	{
		m_fPhi = D3DX_PI - 0.0001f;
	}

	// 一回転以上しないように
	if (m_fTheta < -D3DX_PI)
	{
		m_fTheta += D3DX_PI * 2.0f;
	}
	else if (m_fTheta > D3DX_PI)
	{
		m_fTheta -= D3DX_PI * 2.0f;
	}

	// 位置の目的地を更新(球面座標の公式)
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fPhi) * cosf(m_fTheta);
	m_posV.y = m_posR.y + m_fDistance * cosf(m_fPhi);
	m_posV.z = m_posR.z + m_fDistance * sinf(m_fPhi) * sinf(m_fTheta);

	//// カメラの位置と注視点を更新
	//m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
	//m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;

	// ビューマトリックスの作成
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの作成
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, CAMERA_VIEW_FOV, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, CAMERA_VIEW_RANGE);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CCamera * CCamera::Create(void)
{
    CCamera *pCamera = NULL;
    pCamera = new CCamera;
    pCamera->Init();
    return pCamera;
}