//=============================================================================
//
// 編集クラス [edit.cpp]
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
    m_UINum = 0;
    ofn = { 0 };
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

    m_hwnd = hWnd;
    m_UINum = 0;

    static TCHAR strFile[MAX_PATH], strCustom[256] = TEXT("Before files\0*.*\0\0");

    // 構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = m_hwnd;
    ofn.lpstrFilter = TEXT("Text files {*.txt}\0*.txt\0")
        TEXT("HTML files {*.htm}\0*.htm;*.html\0")
        TEXT("All files {*.*}\0*.*\0\0");
    ofn.lpstrCustomFilter = strCustom;
    ofn.nMaxCustFilter = 256;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = strFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;

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

    //  ImGuiフレームの開始
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Manual();// 操作方法表示
    System();// システムフレームの表示
    UIEdit();// オブジェクトの選択
    information();// オブジェクトの情報

    ImGui::EndFrame();// ImGuiフレームの終了
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
    CUI* pUI = CUI::GetUI(m_UINum);
    assert(pUI);

    // トランスフォームの情報取得
    D3DXVECTOR3 pos = pUI->GetMemoryPos();
    D3DXVECTOR3 size = pUI->GetMemorySize();
    float rot = pUI->GetRot();

    ImGui::Begin(u8"情報");

    // 折りたたみボックス
    if (!ImGui::CollapsingHeader(u8"基本情報"))
    {
        static char str0[8] = "test";
        ImGui::InputText(u8"UI名", str0, IM_ARRAYSIZE(str0));

        static int e = 0;
        ImGui::Combo(u8"使用テクスチャ", &e, u8"なし \0ゲージ \0拡縮 \0移動 \0透明度 \0色変え \0回転 \0テクスチャブレンド \0ループアニメーション \0テクスチャの描画位置指定 \0エフェクト発生");
    }

    // 折りたたみボックス
    if (!ImGui::CollapsingHeader(u8"トランスフォーム"))
    {
        ImGui::DragFloat2("POS", pos, 1, -600, 1500.0f);
        ImGui::DragFloat2("SIZE", size, 1, 0.0f, 1500.0f);
        ImGui::DragFloat("ROT", &rot, 1.0f, -180.0f, 180.0f);
    }
     
    // トランスフォームを反映
    pUI->SetPosition(pos);
    pUI->SetMemoryPos(pos);
    pUI->SetSize(size);
    pUI->SetMemorySize(size);
    pUI->SetRot(D3DXToRadian( rot));
    pUI->SetMemoryRot(D3DXToRadian(rot));

    // 色の設定
    static D3DXCOLOR col = pUI->GetCol();
    ImGui::ColorEdit4("color 1", col);

    pUI->SetCol(col);// 色の反映
    pUI->SetMemoryCol(col);// 色の反映

    // アクションの設定
    if (!ImGui::CollapsingHeader(u8"アクション"))
    {
        SetAction(pUI);
    }

    // チェックボックス
    static bool no_titlebar = false;
    ImGui::Checkbox(u8"ロック", &no_titlebar);
    // ツールチップ
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(u8"カーソルなどに使用する場合はロックしてください");
    ImGui::End();// 終わり

}

//=============================================================================
//[UIEdit] UIの編集
//=============================================================================
void CGUI::UIEdit(void)
{
    ImGui::Begin(u8"オブジェクト");

    const char* listbox_items[] = { u8"背景", u8"ロゴ", u8"Cherry", };
    ImGui::ListBox("\0", &m_UINum, listbox_items, IM_ARRAYSIZE(listbox_items), 5);

    // メニューバー（未完成）
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

    ImGui::End();// 終わり
}

//=============================================================================
//[System] システムフレーム
//=============================================================================
void CGUI::System(void)
{
    // システムフレーム
    ImGui::Begin(u8"システム");

    static bool show_app_main_menu_bar = false;

    if (ImGui::Button(u8"ファイルの保存"))
    {
        CFile_Manager* pFileManager;
        // ファイルの書き込み
        pFileManager = CFile_Manager::Create();
        delete pFileManager;
    }

    if (ImGui::Button(u8"開く"))
    {
        // ファイル選択ダイアログを表示
        std::cout << "参照を選択" << std::endl;
        GetOpenFileName(&ofn);// ダイアログ表示
                              // ファイルの読み込み
                              //CFile_Manager::GetInstance()->CFile_Manager::Read(ofn.lpstrFile);
        std::cout << ofn.lpstrFile << std::endl;
    }

    ImGui::SameLine();
    ImGui::SameLine(110);

    // チェックボックス
    if (ImGui::Checkbox(u8"プレビュー", &CUI::GetPreview()))
    {
        // IsPreviewがtrueだとプレビューモードに切り替え
        CDebug::SetIsReload(CUI::GetPreview());
    }
    // ツールチップ
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(u8"モードを切り替えます");

    static float vec4f[2] = {};
    if (ImGui::CollapsingHeader(u8"折り畳み"))
    {
        ImGui::SliderFloat2("slider float2", vec4f, -600, 1500.0f);
    }

    ImGui::End();// 終わり
}

//=============================================================================
//[SetAction] アクションの設定
// 引数
// pUI : 設定したいUIへのポインタ
//=============================================================================
void CGUI::SetAction(CUI * pUI)
{
    CUI::ActionInfo Action = pUI->GetActionInfo(0);

    ImGui::Combo(u8"種類", &Action.action, u8"なし \0ゲージ \0拡縮 \0移動 \0透明度 \0色変え \0回転 \0テクスチャブレンド \0ループアニメーション \0テクスチャの描画位置指定 \0エフェクト発生");

    // アクションの種類によって内容が変わる
    switch (Action.action)
    {
    case CUI::ACTION_NONE:

        break;

    case CUI::ACTION_GAUGE:// ゲージ
    // ゲージはゲーム側のプログラムでいじるので設定はない
        break;

    case CUI::ACTION_SIZE:// サイズ変更
        ActionSize(Action);
        break;

    case CUI::ACTION_POS:// 位置変更
        ActionPos(Action);
        break;

    case CUI::ACTION_ALPHA:// アルファ値変更
        ActionAlpha(Action);
        break;

    case CUI::ACTION_COLOR:// 色変更
        ActionColor(Action);
        break;

    case CUI::ACTION_ROT:// 角度変更

        ActionRot(Action);
        break;

    case CUI::ACTION_TEX_BREND:// αブレンド
        ActionTexBrend(Action);
        break;

    case CUI::ACTION_LOOP_ANIM:// ループアニメ
        ActionLoopAnim(Action);
        break;

    case CUI::ACTION_TEX_PLACE:// テクスチャの分割
        ActionTexPlace(Action);
        break;

    case CUI::ACTION_EMIT_EFFECT:// エフェクト
        ActionEmitEffect(Action);
        break;
    default:
        assert(Action.action);
        break;
    }

    // アクションのセット
    pUI->SetActionInfo(0, Action.action, Action.bLock, Action.afParam[0], Action.afParam[1], Action.afParam[2], Action.afParam[3], Action.afParam[4], Action.afParam[5], Action.afParam[6], Action.afParam[7]);

}

//=============================================================================
//[ActionSize] 拡縮の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionSize(CUI::ActionInfo& Action)
{
    // 変数定義
    static D3DXVECTOR2 size = {};   // XY拡縮率
    static bool IsEqualRatio;       // 等比変形かどうか
    static int nAction;             // 動作の種類
    static float fFrame;            // フレーム数
    static D3DXVECTOR2 limit = {};  // XY限界値

    // 拡縮
    ImGui::DragFloat2(u8"サイズ", size, 1, -600, 1500.0f);
    Action.afParam[0] = size.x;
    Action.afParam[1] = size.y;

    //等比変形かどうか（bool）
    ImGui::Checkbox(u8"等比変形", &IsEqualRatio);
    Action.afParam[2] = IsEqualRatio ? 1.0f : 0.0f;    // bool値をfloat型に変換

    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[3] = nAction;

    // フレーム
    ImGui::DragFloat(u8"加速度", &fFrame, 1, 0, 1000);
    Action.afParam[4] = fFrame;

    // X Y〇値まで
    ImGui::DragFloat2(u8"XYの限界値", limit, 1, -600, 1500.0f);
    Action.afParam[5] = limit.x;
    Action.afParam[6] = limit.y;
}

//=============================================================================
//[ActionPos] 位置の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionPos(CUI::ActionInfo &Action)
{
    // 変数定義
    static D3DXVECTOR2 pos = {};    // XY拡縮率
    static float Acceleration;      // 加速度
    static int nAction;             // 動作の種類
    static float fFrame;            // フレーム数
    static D3DXVECTOR2 limit = {};  // 限界値

    // X Y
    ImGui::DragFloat2(u8"位置", pos, 1, -600, 1500.0f);
    Action.afParam[0] = pos.x;
    Action.afParam[1] = pos.y;

    // 加速度
    ImGui::DragFloat(u8"加速度", &Acceleration, 1, 0, 100.0f);
    Action.afParam[2] = Acceleration;

    // 動作設定
    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[3] = nAction;

    // フレーム
    ImGui::DragFloat(u8"加速度", &fFrame, 1, 0, 1000.0f);
    Action.afParam[4] = fFrame;

    // X Y〇値まで
    ImGui::DragFloat2(u8"サイズ", limit, 1, -600, 1500.0f);
    Action.afParam[5] = limit.x;
    Action.afParam[6] = limit.y;

}

//=============================================================================
//[ActionAlpha] アルファの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionAlpha(CUI::ActionInfo & Action)
{
    // 変数定義
    static float alpha;             // アルファ値
    static int nAction;             // 動作の種類
    static float fFrame;            // フレーム数
    static float limit = {};  // 限界値

    // アルファ値増減
    ImGui::DragFloat(u8"透明度", &alpha, 1, 0.0f, 256.0f);
    Action.afParam[0] = alpha;

    // 動作設定
    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[1] = nAction;

    // フレーム
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, -600, 1500.0f);
    Action.afParam[2] = fFrame;

    // 限界値
    ImGui::DragFloat(u8"限界値", &limit, 1.0f, 0, 256.0f);
    Action.afParam[3] = limit;
}

//=============================================================================
//[ActionColor] 色の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionColor(CUI::ActionInfo & Action)
{
    // 変数定義
    D3DXCOLOR col;                  // 色
    static int nAction;             // 動作の種類
    static float fFrame;            // フレーム数
    static D3DXCOLOR limit = {};        // 限界値

    // 色の設定
    ImGui::ColorEdit3(u8"色の設定", col);
    Action.afParam[0] = col.r;    // r
    Action.afParam[1] = col.g;    // g
    Action.afParam[2] = col.b;    // b

    // 動作設定
    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[3] = nAction;

    // フレーム
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, -600, 1500.0f);
    Action.afParam[4] = fFrame;

    // 色限界値
    ImGui::DragFloat3(u8"色の限界値", limit, 1.0f, 0.0f, 256.0f);
    Action.afParam[5] = limit.r;    // R限界値
    Action.afParam[6] = limit.g;    // G限界値
    Action.afParam[7] = limit.b;    // B限界値

}

//=============================================================================
//[ActionRot] 回転の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionRot(CUI::ActionInfo & Action)
{
    // 変数定義
    float rot;                      // 角度
    static int nAction;             // 動作の種類
    static float fFrame;            // フレーム数
    static float limit ;    // 限界値

    // 回転速度
    ImGui::DragFloat(u8"回転速度", &rot, 1.0f, 0, 360.0f);
    Action.afParam[0] = rot;

    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[1] = nAction;

    // フレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, -600, 1500.0f);
    Action.afParam[2] = fFrame;

    // 限界値
    ImGui::DragFloat(u8"限界値", &limit, 1.0f, 0, 256.0f);
    Action.afParam[3] = limit;
}

//=============================================================================
//[ActionTexBrend] テクスチャブレンドの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionTexBrend(CUI::ActionInfo & Action)
{
    // 変数定義
    int ntexture;              // テクスチャ番号
    static int nBlend;         // 動作の種類
    static float fFrame;       // フレーム数
    static float fInterval;    // インターバル
    bool isRight;              // 右からか
    static int fDirection;     // 流れる方向

    //テクスチャ番号
    ImGui::Combo(u8"テクスチャ番号", &ntexture, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[0] = ntexture;

    ImGui::Combo(u8"合成方法", &nBlend, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[1] = nBlend;

    // 一周するまでのフレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, 0.0f, 1500.0f);
    Action.afParam[2] = fFrame;

    // インターバルのフレーム数
    ImGui::DragFloat(u8"フレーム", &fInterval, 1.0f, 0.0f, 100.0f);
    Action.afParam[3] = fInterval;

    //右から左か（bool）
    ImGui::Checkbox(u8"右から流す", &isRight);
    Action.afParam[4] = isRight ? 1.0f : 0.0f;    // bool値をfloat型に変換

    ImGui::Combo(u8"流れる方向", &fDirection, u8"縦 \0横 \0右肩上がり \0右肩下がり");
    Action.afParam[5] = fDirection;
}

//=============================================================================
//[ActionLoopAnim] ループアニメの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionLoopAnim(CUI::ActionInfo & Action)
{
    static float fFrame;       // フレーム数
    static float fInterval;    // インターバル
    bool isRight;              // 右からか
    static int fDirection;     // 流れる方向

    // 一周するまでのフレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, 0.0f, 1500.0f);
    Action.afParam[0] = fFrame;

    // インターバルのフレーム数
    ImGui::DragFloat(u8"フレーム", &fInterval, 1.0f, 0.0f, 100.0f);
    Action.afParam[1] = fInterval;

    //右から左か（bool）
    ImGui::Checkbox(u8"右から流す", &isRight);
    Action.afParam[2] = isRight ? 1.0f : 0.0f;    // bool値をfloat型に変換

    ImGui::Combo(u8"流れる方向", &fDirection, u8"縦 \0横 \0右肩上がり \0右肩下がり");
    Action.afParam[3] = fDirection;
}

//=============================================================================
//[ActionTexPlace] テクスチャの描画場所指定の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionTexPlace(CUI::ActionInfo & Action)
{
    static float fDivision;       // 分割数
    static float fNum;         // 左から何番目か
    // 分割数
    ImGui::DragFloat(u8"分割数", &fDivision, 1, 0.0f, 10);
    Action.afParam[0] = fDivision;

    // 左から何番目か
    ImGui::DragFloat(u8"番号", &fNum, 1, 0.0f, 10.0f);
    Action.afParam[1] = fNum;
}

//=============================================================================
//[ActionEmitEffect] エフェクトの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CGUI::ActionEmitEffect(CUI::ActionInfo & Action)
{
    // 変数定義
    int ntexture;              // テクスチャ番号
    static int nAction;             // 動作の種類
    static float fFrame;                // フレーム数
    static D3DXVECTOR2 pos = {};        // 発生位置

    // エフェクト番号
    ImGui::Combo(u8"テクスチャ番号", &ntexture, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[0] = ntexture;

    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    Action.afParam[1] = nAction;

    // フレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, 0.0f, 1500.0f);
    Action.afParam[2] = fFrame;

    //発生位置Xをずらす〇値
    //発生位置Yをずらす〇値
    ImGui::DragFloat2(u8"発生位置", pos, 1, -600, 1500.0f);
    Action.afParam[3] = pos.x;
    Action.afParam[4] = pos.y;
}

