//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "manager.h"
#include <stdio.h>
#include "renderer.h"
#include "object.h"
#include "scene2d.h"
#include "camera.h"
#include "resource.h"
#include "imguimanager.h"
#include "modelData.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::m_pRenderer = NULL;
CCamera* CManager::m_pCamera = NULL;
CImGuiManager* CManager::m_pImGuiManager = NULL;
CModelData* CManager::m_pModelData = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::CManager()
{
	m_pRenderer = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::~CManager()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	m_pRenderer = new CRenderer;	//レンダラを生成
	m_pRenderer->Init(hWnd, true);	//レンダラを初期化
	
	m_pImGuiManager = new CImGuiManager;
	m_pImGuiManager->Init(hWnd);
	
	m_pCamera = new CCamera;		//カメラオブジェクトの生成
	m_pCamera->Init();

	m_pModelData = new CModelData;
	m_pModelData->Init();
	
	LoadFile();						//ファイル読み込み

	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Uninit(void)
{
	//シーンの終了
	CObject::ReleaseAll();
	
	//カメラの終了
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		SAFE_DELETE(m_pCamera);
	}
	
	//IMGUIの終了
	if (m_pImGuiManager != NULL)
	{
		m_pImGuiManager->Uninit();
		SAFE_DELETE(m_pImGuiManager);
	}

	//レンダラの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		SAFE_DELETE(m_pRenderer);
	}

	if (m_pModelData != NULL) 
	{
		m_pModelData->Uninit();
		SAFE_DELETE(m_pModelData);
	}

	//読み込んだファイルのアンロード
	UnloadFiles();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Update(void)
{
	//レンダラの更新
	m_pRenderer->Update();	
	
	//IMGUIの更新
	m_pImGuiManager->Update();

	//カメラの更新
	m_pCamera->Update();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Draw(void)
{
	//カメラ設定
	m_pCamera->SetCamera();

	//IMGUIの更新
	m_pImGuiManager->Draw();
	
	//レンダラの描画
	m_pRenderer->Draw();	
	
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイルのロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::LoadFile(void)
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイルのアンロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::UnloadFiles(void)
{

}
