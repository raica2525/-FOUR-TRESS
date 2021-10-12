//=============================================================================
//
// GUIクラス [gui.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "gui.h"
#include "manager.h"
#include "file_manager.h"
#include "ui.h"
#include "debug.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// [CGUI] コンストラクタ
//=============================================================================
CGUI::CGUI()
{

}

//=============================================================================
// [~CGUI] デストラクタ
//=============================================================================
CGUI::~CGUI()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CGUI* CGUI::Create(HWND hWnd)
{
    CGUI *pUi = NULL;
    if (!pUi)
    {
        pUi = new CGUI;
        pUi->Init(hWnd);
    }
    return pUi;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
void CGUI::Init(HWND hWnd)
{
    // IMGUIの設定
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CGUI::Uninit(void)
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CGUI::Update(void)
{
    ImGuiWindowFlags window_flags = 0;
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // システムフレーム
    ImGui::Begin(u8"システム");

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    static bool show_app_main_menu_bar = false;

    if (ImGui::Button(u8"ファイルの保存"))
    {
        CFile_Manager* pFileManager;
        // ファイルの書き込み
        pFileManager = CFile_Manager::Create();
        delete pFileManager;

    }
    ImGui::SameLine();
    ImGui::SameLine(110);

    if (ImGui::Button(u8"プレビュー"))
    {
        // プレビューフラグをオン
        CDebug::SetIsReload(true);
    }

    if (ImGui::CollapsingHeader(u8"折り畳み"))
    {

    }

    static int Value = 0;
    static float col1[3] = { 1.0f,0.0f,0.2f };
    ImGui::ColorEdit3("color 1", col1);

    ImGui::DragInt("Value", &Value, 100, 0, 100);// バーのやつ

    Manual();// 操作方法表示
    information();
    ImGui::End();// 終わり


    ImGui::EndFrame();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CGUI::Draw(void)
{
    // ImGuiの描画
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

}

//=============================================================================
// [Manual] 操作方法フレーム
//=============================================================================
void CGUI::Manual(void)
{
    static bool open = true;
    if (open)
    {
        // IMGUI開始
        ImGui::Begin(u8"操作方法", &open);
        ImGui::Text(u8"F4キーでプレビュー");
        ImGui::Text(u8"ESCキーで終了");

        ImGui::End();// 終わり
    }
}

//=============================================================================
//[information] 情報フレーム
//=============================================================================
void CGUI::information(void)
{

    // UIの情報を取得
    CUI* pUI = CUI::GetAccessUI(0);
    D3DXVECTOR3 pos = pUI->GetPosition();
            ImGui::Begin(u8"情報");

            static float fpos[3] = { 0.0f,0.0,0.0, };
            static float size[3] = { 0.0,0.0,0.0, };

            // 折りたたみボックス
            if (!ImGui::CollapsingHeader(u8"選択"))
            {

            }
            // 折りたたみボックス
            if (!ImGui::CollapsingHeader(u8"トランスフォーム"))
            {
                ImGui::InputFloat3("POS", pos);
                ImGui::InputFloat3("SIZE", size);
            }

            pUI->SetPosition(pos);

            static float begin = 10, end = 90, z = 100;

            static int item = 0;
            static int e = 0;

            // 折りたたみボックス
            if (!ImGui::CollapsingHeader(u8"アクション"))
            {
                // 情報1が特定の値だと出現
                ImGui::Combo(u8"情報2", &e, u8"なし \0ゲージ \0拡縮 \0移動 \0透明度 \0色変え \0回転 \0テクスチャブレンド \0ループアニメーション \0テクスチャの描画位置指定 \0エフェクト発生");
            }

            // チェックボックス
            static bool no_titlebar = false;
            ImGui::Checkbox(u8"ロック", &no_titlebar);
            // ツールチップ
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(u8"カーソルなどに使用する場合はロックしてください");
            static int i1 = 0;
    ImGui::End();// 終わり

}

//=============================================================================
//[UIEdit] UIの編集
//=============================================================================
void CGUI::UIEdit(void)
{

}

