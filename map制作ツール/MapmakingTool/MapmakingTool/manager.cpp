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
#include "scene.h"
#include "scene2d.h"
#include "camera.h"
#include "scene3d.h"
#include "model.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imjapaneserange.h"
#include "resource.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::m_pRenderer = NULL;
CCamera* CManager::m_pCamera = NULL;
bool CManager::m_bImShowMainWindow = false;

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

	InitImGui(hWnd);				//ImGuiの初期化
	m_pCamera = new CCamera;		//カメラオブジェクトの生成
	m_pCamera->Init();
	
	LoadFile();						//ファイル読み込み

	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Uninit(void)
{
	//シーンの終了
	CScene::ReleaseAll();
	
	//カメラの終了
	m_pCamera->Uninit();	
	delete m_pCamera;		
	m_pCamera = NULL;	

	//レンダラの終了
	m_pRenderer->Uninit();	
	delete m_pRenderer;
	m_pRenderer = NULL; 

	//読み込んだファイルのアンロード
	UnloadFiles();
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Update(void)
{
	//レンダラの更新
	m_pRenderer->Update();	
	
	m_pCamera->Update();

	UpdateImGui();

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Draw(void)
{
	m_pCamera->SetCamera();
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// ImGuiの初期化
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::InitImGui(HWND hWnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//設定を渡す構造体を取得
	ImGuiIO& io = ImGui::GetIO();
	//日本語が入力できるようにフォントを追加
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 18.0f, nullptr, glyphRangesJapanese);
	//ImGUI側にスクリーンサイズを渡す
	io.DisplaySize.x = SCREEN_WIDTH;
	io.DisplaySize.y = SCREEN_HEIGHT;
	//ImGuiに必要な初期化
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(m_pRenderer->GetDevice());
	//黒色のスタイルに変更
	ImGui::StyleColorsDark();
}

void CManager::UpdateImGui(void)
{
	//フレームが変わったことをImGuiに教える
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	//初期のウィンドウサイズを指定
	ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
	bool bBuffMainWindow = m_bImShowMainWindow;
	//BeginからEndで一つのウィンドウ
	if (m_bImShowMainWindow)
	{
		ImGui::Begin(u8"オブジェクト情報", &m_bImShowMainWindow);
		ImGui::Text("FPS:%d", GetFPS());
		ImGui::Text(u8"テストTest");
		ImGui::End();
	}
	if (bBuffMainWindow != m_bImShowMainWindow)
	{
		ChangeCheckMenuItem(ID_WINDOW_OBJECTINFO);
	}

	ImGui::EndFrame();
}


bool CManager::ChangeShowMainWindow(void)
{
	m_bImShowMainWindow = !m_bImShowMainWindow;
	return m_bImShowMainWindow;
}