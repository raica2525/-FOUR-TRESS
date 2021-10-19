//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imguimanager.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "imguimanager.h"
#include "manager.h"
#include "renderer.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imjapaneserange.h"
#include "resource.h"
#include "imobjectwindow.h"
#include "imguiwindow.h"
#include "immapwindow.h"
#include "imdebugwindow.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define FONT_SIZE (18.0f)
#define FONT_PATH ("c:\\Windows\\Fonts\\msgothic.ttc")
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CImGuiManager::CImGuiManager()
{
	m_bShowStructures = true;
	m_str[0] = '\0';
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CImGuiManager::~CImGuiManager()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CImGuiManager::Init(HWND hWnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//設定を渡す構造体を取得
	ImGuiIO& io = ImGui::GetIO();
	//日本語が入力できるようにフォントを追加
	io.Fonts->AddFontFromFileTTF(FONT_PATH, FONT_SIZE, nullptr, glyphRangesJapanese);
	//ImGUI側にスクリーンサイズを渡す
	io.DisplaySize.x = SCREEN_WIDTH;
	io.DisplaySize.y = SCREEN_HEIGHT;
	//ImGuiに必要な初期化
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());
	//黒色のスタイルに変更
	ImGui::StyleColorsDark();
	m_pImGuiWindow[IMWINDOW_OBJ_INFO] = CImObjectWindow::Create();
	m_pImGuiWindow[IMWINDOW_MAP_INFO] = CImMapWindow::Create();
	m_pImGuiWindow[IMWINDOW_DEBUG_INFO] = CImDebugWindow::Create();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CImGuiManager::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CImGuiManager::Update(void)
{
	//フレームが変わったことをImGuiに教える
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	for (int nCount = 0; nCount < IMWINDOW_MAX; nCount++)
	{
		m_pImGuiWindow[nCount]->Update();
	}
	ImGui::EndFrame();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CImGuiManager::Draw(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
