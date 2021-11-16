//=============================================================================
//
// 編集モードクラス [edit.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "edit.h"
#include "manager.h"
#include "file_manager.h"
#include "ui.h"
#include "debug.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include <sstream>

//*****************************************************************************
// 静的メンバ関数
//*****************************************************************************
CEdit* CEdit::m_pInstance = nullptr;// オブジェクトへのポインタ

//=============================================================================
// [CEdit] コンストラクタ
//=============================================================================
CEdit::CEdit()
{
    m_UINum = 0;
    ofn = { 0 };

    for (int nCnt = 0; nCnt > FREME_MAX; nCnt++)
    {
        m_IsOpen[nCnt] = true;
    }
}

//=============================================================================
// [~CEdit] デストラクタ
//=============================================================================
CEdit::~CEdit()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CEdit* CEdit::Create(HWND hWnd)
{
    // オブジェクト生成
    if (!m_pInstance)
    {
        m_pInstance = new CEdit;
        m_pInstance->Init(hWnd);
    }
    return m_pInstance;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
void CEdit::Init(HWND hWnd)
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
void CEdit::Uninit(void)
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CEdit::Update(void)
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
void CEdit::Draw(void)
{
    // ImGuiの描画
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//=============================================================================
// [Manual] 操作方法フレーム
//=============================================================================
void CEdit::Manual(void)
{
    if (!m_IsOpen[FREME_MANUAL])    // フレームが閉じているときは生成しない
        return;

        // IMGUI開始
        ImGui::Begin(u8"操作方法", &m_IsOpen[FREME_MANUAL]);
        ImGui::Text(u8"F4キーでプレビュー");
        ImGui::Text(u8"ESCキーで終了");

        ImGui::End();// 終わり
}


//=============================================================================
//[information] 情報フレーム
//=============================================================================
void CEdit::information(void)
{
    // UIの情報を取得
    CUI* pUI = CUI::GetUI(m_UINum);
    assert(pUI);

    // トランスフォームの情報取得
    D3DXVECTOR3 pos = pUI->GetMemoryPos();
    D3DXVECTOR3 size = pUI->GetMemorySize();
    float rot = D3DXToDegree( pUI->GetRot());// 取得した角度をデグリーに変換

    if (!m_IsOpen[FREME_INFO])
        return;

    ImGui::Begin(u8"情報", &m_IsOpen[FREME_INFO]);

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
        ImGui::DragFloat2("POS", pos, 1, -600, 1500.0f);        // 位置の設定
        ImGui::DragFloat2("SIZE", size, 1, 0.0f, 1500.0f);      // サイズの設定
        ImGui::DragFloat("ROT", &rot, 1.0f, -180.0f, 180.0f);   // 角度の設定
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
//[UIEdit] オブジェクトフレーム
//=============================================================================
void CEdit::UIEdit(void)
{
    if (!m_IsOpen[FREME_OBJECT])    // フレームが閉じているときは生成しない
        return;

    ImGui::Begin(u8"オブジェクト", &m_IsOpen[FREME_OBJECT]);

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
void CEdit::System(void)
{
    if (!m_IsOpen[FREME_SYSTEM])    // フレームが閉じているときは生成しない
        return;

    // システムフレーム
    ImGui::Begin(u8"システム", &m_IsOpen[FREME_SYSTEM]);

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
void CEdit::SetAction(CUI * pUI)
{
    static int ActionNum = 0;       // アクション番号

    ImGui::Combo(u8"アクション番号", &ActionNum, u8"0 \0 1 \0 2 \0 3");

    CUI::ActionInfo Action = pUI->GetActionInfo(ActionNum); // アクション情報の取得

    int ActionType = Action.action;       // アクションの種類

    ImGui::Combo(u8"種類", &ActionType, u8"0:なし \0 1:ゲージ \0 2:拡縮 \0 3:移動 \0 4:透明度 \0 5:色変え \0 6:回転 \0 7:テクスチャブレンド \0 8:ループアニメーション \0 9:テクスチャの描画位置指定 \0 10:エフェクト発生");

    // アクションの種類によって内容が変わる
    switch (ActionType)
    {
    case CUI::ACTION_NONE:

        break;

    case CUI::ACTION_GAUGE:// ゲージ
    // ゲージはゲーム側のプログラムでいじるので設定はない
        break;

    case CUI::ACTION_SIZE:    // サイズ変更
        ActionSize(Action);
        break;

    case CUI::ACTION_POS:     // 移動量設定
        ActionPos(Action);
        break;

    case CUI::ACTION_ALPHA:   // アルファ値変更
        ActionAlpha(Action);
        break;

    case CUI::ACTION_COLOR:   // 色変更
        ActionColor(Action);
        break;

    case CUI::ACTION_ROT:    // 角度変更

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
        assert(ActionType);
        break;
    }

    // アクションのセット
    pUI->SetActionInfo(ActionNum, ActionType, Action.bLock, Action.afParam[0], Action.afParam[1], Action.afParam[2], Action.afParam[3], Action.afParam[4], Action.afParam[5], Action.afParam[6], Action.afParam[7]);

}

//=============================================================================
//[ActionSize] 拡縮の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionSize(CUI::ActionInfo& Action)
{
    // 変数定義
    static D3DXVECTOR2 size      = { Action.afParam[0],Action.afParam[1] };   // XY拡縮率
    static bool IsEqualRatio     = Action.afParam[2];                         // 等比変形かどうか
    static int nAction           = Action.afParam[3];                         // 動作の種類
    static float fFrame          = Action.afParam[4];                         // フレーム数
    static D3DXVECTOR2 limit     = { Action.afParam[5], Action.afParam[6] };  // XY限界値

    // 拡縮
    ImGui::DragFloat2(u8"サイズ", size, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(u8"PARAM0：拡縮X \n PARAM1：拡縮Y");
    Action.afParam[0] = size.x;
    Action.afParam[1] = size.y;

    //等比変形かどうか（bool）
    ImGui::Checkbox(u8"等比変形", &IsEqualRatio);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：等比変形かどうか");
    Action.afParam[2] = IsEqualRatio ? 1.0f : 0.0f;    // bool値をfloat型に変換

    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：動作設定");
    Action.afParam[3] = nAction;

    // フレーム
    ImGui::DragFloat(u8"フレーム", &fFrame, 1, 0, 1000);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM4：フレーム");
    Action.afParam[4] = fFrame;

    // X Y〇値まで
    ImGui::DragFloat2(u8"XYの限界値", limit, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM5：限界値X \n PARAM6：限界値Y");
    Action.afParam[5] = limit.x;
    Action.afParam[6] = limit.y;
}

//=============================================================================
//[ActionPos] 位置の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionPos(CUI::ActionInfo &Action)
{
    // 変数定義
    static D3DXVECTOR2 move      = { Action.afParam[0],Action.afParam[1] };    // XY拡縮率
    static float Acceleration    = Action.afParam[2];                          // 加速度
    static int nAction           = Action.afParam[3];                          // 動作の種類
    static float fFrame          = Action.afParam[4];                          // フレーム数
    static D3DXVECTOR2 limit     = { Action.afParam[5],Action.afParam[6] };    // 限界値

    // X Y
    ImGui::DragFloat2(u8"移動量", move, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：移動量X \n PARAM1：移動量Y");
    Action.afParam[0] = move.x;
    Action.afParam[1] = move.y;

    // 加速度
    ImGui::DragFloat(u8"加速度", &Acceleration, 1, 0, 100.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：加速度");
    Action.afParam[2] = Acceleration;

    // 動作設定
    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：動作設定");
    Action.afParam[3] = nAction;

    // フレーム
    ImGui::DragFloat(u8"フレーム", &fFrame, 1, 0, 1000.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM4：フレーム");
    Action.afParam[4] = fFrame;

    // X Y〇値まで
    ImGui::DragFloat2(u8"限界値", limit, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM5：X限界値 \n PARAM6：Y限界値");
    Action.afParam[5] = limit.x;
    Action.afParam[6] = limit.y;
}

//=============================================================================
//[ActionAlpha] アルファの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionAlpha(CUI::ActionInfo & Action)
{
    // 変数定義
    static float alpha   = Action.afParam[0];    // アルファ値
    static int nAction   = Action.afParam[1];    // 動作の種類
    static float fFrame  = Action.afParam[2];    // フレーム数
    static float limit   = Action.afParam[3];    // 限界値

    // アルファ値増減
    ImGui::DragFloat(u8"透明度", &alpha, 1, 0.0f, 256.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：透明度");
    Action.afParam[0] = alpha;

    // 動作設定
    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM1：動作設定");
    Action.afParam[1] = nAction;

    // フレーム
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：フレーム");
    Action.afParam[2] = fFrame;

    // 限界値
    ImGui::DragFloat(u8"限界値", &limit, 1.0f, 0, 256.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：限界値");
    Action.afParam[3] = limit;
}

//=============================================================================
//[ActionColor] 色の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionColor(CUI::ActionInfo & Action)
{
    // 変数定義
    static D3DXCOLOR col    = { Action.afParam[0] ,Action.afParam[1] ,Action.afParam[2],0.0f };           // 色
    static int nAction      = Action.afParam[3];                                                          // 動作の種類
    static float fFrame     = Action.afParam[4];                                                          // フレーム数
    static D3DXCOLOR limit  = { Action.afParam[5] , Action.afParam[6] , Action.afParam[7] ,0.0f };        // 限界値

    // 色の設定
    ImGui::ColorEdit3(u8"色の設定", col);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：Rの値 \n PARAM1：Gの値 \n PARAM2：Bの値");
    Action.afParam[0] = col.r;    // r
    Action.afParam[1] = col.g;    // g
    Action.afParam[2] = col.b;    // b

    // 動作設定
    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：動作設定");
    Action.afParam[3] = nAction;

    // フレーム
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM4：フレーム");
    Action.afParam[4] = fFrame;

    // 色限界値
    ImGui::DragFloat3(u8"色の限界値", limit, 1.0f, 0.0f, 256.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM5：Rの限界値 \n PARAM6：Gの限界値 \n  PARAM7：Bの限界値");
    Action.afParam[5] = limit.r;    // R限界値
    Action.afParam[6] = limit.g;    // G限界値
    Action.afParam[7] = limit.b;    // B限界値
}

//=============================================================================
//[ActionRot] 回転の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionRot(CUI::ActionInfo & Action)
{
    // 変数定義
    static float rot     = Action.afParam[0];    // 角度
    static int nAction   = Action.afParam[1];    // 動作の種類
    static float fFrame  = Action.afParam[2];    // フレーム数
    static float limit   = Action.afParam[3];    // 限界値

    // 回転速度
    ImGui::DragFloat(u8"回転速度", &rot, 1.0f, -180, 180.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：回転速度");
    Action.afParam[0] = rot;

    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM1：動作設定");
    Action.afParam[1] = nAction;

    // フレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：フレーム");
    Action.afParam[2] = fFrame;

    // 限界値
    ImGui::DragFloat(u8"限界値", &limit, 1.0f, 0, 256.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：限界値");
    Action.afParam[3] = limit;
}

//=============================================================================
//[ActionTexBrend] テクスチャブレンドの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionTexBrend(CUI::ActionInfo & Action)
{
    // 変数定義
    static int ntexture     = Action.afParam[0];    // テクスチャ番号
    static int nBlend       = Action.afParam[1];    // 動作の種類
    static float fFrame     = Action.afParam[2];    // フレーム数
    static float fInterval  = Action.afParam[3];    // インターバル
    static bool isRight     = Action.afParam[4];    // 右からか
    static int fDirection   = Action.afParam[5];    // 流れる方向

    TextureCheck(ntexture);// テクスチャが存在するかチェック
    //テクスチャ番号
    ImGui::DragInt(u8"テクスチャ番号", &ntexture, 1, 0, CTexture::GetnNumTexture());
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：テクスチャ番号");

    TextureCheck(ntexture);// テクスチャが存在するかチェック
    Action.afParam[0] = ntexture;

    ImGui::Combo(u8"合成方法", &nBlend, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM1：合成方法");
    Action.afParam[1] = nBlend;

    // 一周するまでのフレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, 0.0f, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：一周するまでのフレーム数");
    Action.afParam[2] = fFrame;

    // インターバルのフレーム数
    ImGui::DragFloat(u8"インターバル", &fInterval, 1.0f, 0.0f, 100.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：インターバル");
    Action.afParam[3] = fInterval;

    //右から左か（bool）
    ImGui::Checkbox(u8"右から流す", &isRight);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM4：テクスチャを右から流すかどうか");
    Action.afParam[4] = isRight ? 1.0f : 0.0f;    // bool値をfloat型に変換

    ImGui::Combo(u8"流れる方向", &fDirection, u8"縦 \0横 \0右肩上がり \0右肩下がり");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM5：テクスチャの流れる方向");
    Action.afParam[5] = fDirection;

    Action.afParam[6] = 1;   //1から3で固定
}

//=============================================================================
//[ActionLoopAnim] ループアニメの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionLoopAnim(CUI::ActionInfo & Action)
{
    static float fFrame     = Action.afParam[0];    // フレーム数
    static float fInterval  = Action.afParam[1];    // インターバル
    static bool isRight     = Action.afParam[2];    // 右からか
    static int fDirection   = Action.afParam[3];    // 流れる方向

    // 一周するまでのフレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, 0.0f, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：一周するまでのフレーム数");
    Action.afParam[0] = fFrame;

    // インターバルのフレーム数
    ImGui::DragFloat(u8"インターバル", &fInterval, 1.0f, 0.0f, 100.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM1：インターバル");
    Action.afParam[1] = fInterval;

    //右から左か（bool）
    ImGui::Checkbox(u8"右から流す", &isRight);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：テクスチャを右から流すかどうか");
    Action.afParam[2] = isRight ? 1.0f : 0.0f;    // bool値をfloat型に変換

    ImGui::Combo(u8"流れる方向", &fDirection, u8"縦 \0横 \0右肩上がり \0右肩下がり");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：テクスチャの流れる方向");
    Action.afParam[3] = fDirection;
}

//=============================================================================
//[ActionTexPlace] テクスチャの描画場所指定の設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionTexPlace(CUI::ActionInfo & Action)
{
    static float fDivision  = Action.afParam[0];    // 分割数
    static float fNum       = Action.afParam[1];    // 左から何番目か

    // 分割数
    ImGui::DragFloat(u8"分割数", &fDivision, 1, 0.0f, 10);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：分割数");
    Action.afParam[0] = fDivision;

    // 左から何番目か
    ImGui::DragFloat(u8"番号", &fNum, 1, 0.0f, 10.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM1：テクスチャの番号(左から)");
    Action.afParam[1] = fNum;
}

//=============================================================================
//[ActionEmitEffect] エフェクトの設定
// 引数
// Action : 設定したいアクション
//=============================================================================
void CEdit::ActionEmitEffect(CUI::ActionInfo & Action)
{
    // 変数定義
    static int ntexture     = Action.afParam[0];                          // テクスチャ番号
    static int nAction      = Action.afParam[1];                          // 動作の種類
    static float fFrame     = Action.afParam[2];                          // フレーム数
    static D3DXVECTOR2 pos  = { Action.afParam[3],Action.afParam[4]};     // 発生位置

    TextureCheck(ntexture);// テクスチャが存在するかチェック

    // エフェクト番号
    //ImGui::Combo(u8"テクスチャ番号", &ntexture, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    ImGui::DragInt(u8"テクスチャ番号", &ntexture, 1, 0, CTexture::GetnNumTexture());
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM0：テクスチャ番号");

    ntexture = TextureCheck(ntexture);// テクスチャが存在するかチェック
    Action.afParam[0] = ntexture;

    ImGui::Combo(u8"動作設定", &nAction, u8"無制限 \0〇フレームまで \0〇フレームから \0〇値まで \0フレームリピート \0値リピート \0(〇フレームから)〇値に即座にする ");
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM1：動作設定");
    Action.afParam[1] = nAction;

    // フレーム数
    ImGui::DragFloat(u8"フレーム", &fFrame, 1.0f, 0.0f, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM2：フレーム");
    Action.afParam[2] = fFrame;

    //発生位置Xをずらす〇値
    //発生位置Yをずらす〇値
    ImGui::DragFloat2(u8"発生位置", pos, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//ツールチップ
        ImGui::SetTooltip(u8"PARAM3：発生位置X \n PARAM3：発生位置Y");
    Action.afParam[3] = pos.x;
    Action.afParam[4] = pos.y;
}


//=============================================================================
//[TextureCheck] テクスチャのチェック
// 引数
// nTextureNum : テクスチャ番号
//=============================================================================
int CEdit::TextureCheck(int nTextureNum)
{
    // テクスチャへのポインタを取得
    CTexture* pTexture = CManager::GetTexture();
    // 引数の番号のテクスチャが存在するかチェック
    if (pTexture->CTexture::GetInfo(nTextureNum) == nullptr)
    {
    // 存在しない場合
        return 0;
    }
   
    return  nTextureNum;
}

//=============================================================================
//[TextureName] テクスチャ名取得
// 引数
// Action : 設定したいアクション
//=============================================================================
//std::string CEdit::TextureName(void)
//{
//    CTexture* pTexture = CManager::GetTexture();
//    std::ostringstream oss;
//
//    // テクスチャ名を取得
//    for (int nCnt = 0; nCnt < CTexture::GetnNumTexture(); nCnt++)
//    {
//        std::string strName = pTexture->CTexture::GetInfo(nCnt);
//        oss << "\0";
//    }
//
//    return oss.str();
//}

