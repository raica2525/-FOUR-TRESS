//===============================================
//
// 生成の管理処理 (manager.cpp)
// Author : 伊藤陽梧
//
//===============================================

//========================
// インクルードファイル
//========================
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "mode.h"
#include <typeinfo.h>
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "effectData.h"
#include "effecttool.h"
#include "tool.h"
#include "scene.h"

//========================================
// マクロ定義
//========================================

//========================================
// 静的メンバ変数宣言
//========================================
CRenderer *CManager::m_pRenderer = NULL;
CMouse *CManager::m_pMouse = NULL;
CMode *CManager::m_pMode = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CTexture *CManager::m_pTexture = NULL;
CEffectData *CManager::m_pEffectData = NULL;
CEffectTool *CManager::m_pEffectTool = NULL;

//========================================
// 生成の管理のデフォルトコンストラクタ
//========================================
CManager::CManager()
{

}

//========================================
// 生成の管理のデストラクタ
//========================================
CManager::~CManager()
{

}

//========================================
// 生成の管理の初期化処理
//========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// レンダラーの生成(一回しか生成しないものは、Createを用意していない)
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// マウスの生成
	m_pMouse = new CMouse;
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ライトの生成
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// カメラの生成
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// テクスチャの生成
	m_pTexture = new CTexture;
	if (FAILED(m_pTexture->Init()))
	{
		return E_FAIL;
	}

	// エフェクトデータ管理の生成
	m_pEffectData = new CEffectData;
	if (FAILED(m_pEffectData->Init()))
	{
		return E_FAIL;
	}
	// エフェクトツールの生成
	m_pEffectTool = new CEffectTool;
	if (FAILED(m_pEffectTool->Init(hWnd)))
	{
		return E_FAIL;
	}

	SetMode(MODE_TOOL);

	return S_OK;
}
//========================================
// 生成の管理の終了処理
//========================================
void CManager::Uninit(void)
{
	// 全てのオブジェクトを破棄
	CScene::ReleaseAll();

	// モード破棄
	if (m_pMode != NULL)
	{
		// モードの終了処理
		m_pMode->Uninit();

		// モードのメモリの開放
		delete m_pMode;
		m_pMode = NULL;
	}

	// エフェクトツール破棄
	if (m_pEffectTool != NULL)
	{
		// エフェクトツールの終了処理
		m_pEffectTool->Uninit();

		// エフェクトツールのメモリの開放
		delete m_pEffectTool;
		m_pEffectTool = NULL;
	}

	// エフェクトデータ管理破棄
	if (m_pEffectData != NULL)
	{
		// モデルデータの終了処理2
		m_pEffectData->Uninit();

		// モデルデータのメモリの開放
		delete m_pEffectData;
		m_pEffectData = NULL;
	}

	// テクスチャ破棄
	if (m_pTexture != NULL)
	{
		// テクスチャの終了処理
		m_pTexture->Uninit();

		// テクスチャのメモリの開放
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// マウスの破棄
	if (m_pMouse != NULL)
	{
		// マウス終了処理
		m_pMouse->Uninit();

		// マウスのメモリの開放
		delete m_pMouse;
		m_pMouse = NULL;
	}

	// レンダラー破棄
	if (m_pRenderer != NULL)
	{
		// レンダラー終了処理
		m_pRenderer->Uninit();

		// レンダラーのメモリの開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//========================================
// 生成の管理の更新処理
//========================================
void CManager::Update(void)
{
	// マウス更新処理
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	// レンダラー更新処理
	if (m_pRenderer != NULL)
	{
		// モードがあるなら
		if (m_pMode != NULL)
		{
			// 常に全て更新
			m_pRenderer->Update();
		}
	}

	// モードの更新処理
	if (m_pMode != NULL)
	{
		m_pMode->Update();
	}

	// カメラの更新処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// エフェクトツールの更新処理
	if (m_pEffectTool != NULL)
	{
		m_pEffectTool->Update();
	}
}

//========================================
// 生成の管理の描画処理
//========================================
void CManager::Draw(void)
{
	// 描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//========================================
// モードの取得
//========================================
CManager::MODE CManager::GetMode(void)
{
	// 返り値に使うモード
	MODE mode = MODE_NONE;

	// 何のモードが入っているか見て、型名ごとに場合分け
	if (typeid(*m_pMode) == typeid(CTool))
	{
		mode = MODE_TOOL;
	}

	return mode;
}

//========================================
// モードの設定
// mode	:	設定するモード
//========================================
void CManager::SetMode(MODE mode)
{
    // モードの中身があるなら
    if (m_pMode != NULL)
    {
        // 終了処理
        m_pMode->Uninit();

        // メモリの破棄
        delete m_pMode;
        m_pMode = NULL;
    }

    // シーン上のオブジェクトを全て終了処理
    CScene::ReleaseAll();

    // 受け取ったモードに画面遷移
    switch (mode)
    {
	case MODE_TOOL:
		m_pMode = new CTool;
		break;
    }

    // 確保したモードの初期化
    m_pMode->Init();
}