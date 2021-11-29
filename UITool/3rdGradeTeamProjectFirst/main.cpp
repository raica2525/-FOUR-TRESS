//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 後藤慎之助
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"

#include "imgui/imgui.h"// 工藤追加
#include "resource.h"
#include "edit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#undef _DEBUG
#define FONT "C:\\Windows\\Fonts\\meiryo.ttc"       // フォントファイル
#define MSG(m) {MessageBoxA(NULL,m,NULL,MB_OK);}

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// IMGUIの設定
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
#ifdef _DEBUG
int						g_nCountFPS;
#endif
bool g_bDeviceChange = false;		//池田変更

//=============================================================================
// メイン関数
// Author : 後藤慎之助
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
     //コンソールを作成する
    AllocConsole();
    // 標準入出力に割り当てる
    FILE* fp = NULL;
    // 現在のコード
    freopen_s(&fp, "CONOUT$", "w", stdout);
    printf("%s", "起動中\n");
#endif // _DEBUG

    WNDCLASSEX wcex =
    {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        WndProc,
        0,
        0,
        hInstance,
        LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAND)),  // アイコン
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        MAKEINTRESOURCE(IDR_MENU1),                             // メニューの名前
        CLASS_NAME,
        LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION))
    };

    RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    HWND hWnd;
    MSG msg;
    DWORD dwCurrentTime;
    DWORD dwFrameCount;
    DWORD dwExecLastTime;
    DWORD dwFPSLastTime;

    // ウィンドウクラスの登録
    RegisterClassEx(&wcex);

    // 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    // ウィンドウの作成
    hWnd = CreateWindow(CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (rect.right - rect.left),
        (rect.bottom - rect.top),
        NULL,
        NULL,
        hInstance,
        NULL);

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    //===============================================
    // マネージャー処理（レンダラーやシーンの代わり）
    CManager *pManager = NULL;

    // マネージャー生成
    pManager = new CManager;

    // 初期化処理
    if (FAILED(pManager->Init(hInstance, hWnd, TRUE))) //FALSEにすると、全画面表示
    {
        return -1;
    }
    //================================================

    // 分解能を設定
    timeBeginPeriod(1);

    // フレームカウント初期化
    dwCurrentTime =
        dwFrameCount = 0;
    dwExecLastTime =
        dwFPSLastTime = timeGetTime();

    // ウインドウの表示
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // IMGUIの設定(Author : AYANO KUDO)
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF(FONT, 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    // メッセージループ
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {// PostQuitMessage()が呼ばれたらループ終了
                break;
            }
            else
            {
                // メッセージの翻訳とディスパッチ
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            dwCurrentTime = timeGetTime();	// 現在の時間を取得
            if ((dwCurrentTime - dwFPSLastTime) >= 500)
            {// 0.5秒ごとに実行
#ifdef _DEBUG
             // FPSを算出
                g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
                dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
                dwFrameCount = 0;
            }

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
            {// 1/60秒経過
                dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

                pManager->Update();

                pManager->Draw();

                dwFrameCount++;
            }
        }
    }

    // 終了処理
    if (pManager != NULL)
    {
        pManager->Uninit();

        delete pManager;
        pManager = NULL;
    }

    // ウィンドウクラスの登録を解除
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    // 分解能を戻す
    timeEndPeriod(1);

    return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
// Author : 後藤慎之助、池田悠希（コントローラの再接続対応）
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // IMGUIの設定(Author : AYANO KUDO)
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    {
        return true;
    }

    switch (uMsg)
    {
    case WM_CREATE:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:				// [ESC]キーが押された
            DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
            break;
        }

    case WM_DEVICECHANGE:		//デバイスの構成が変わった時			//池田追加
        g_bDeviceChange = true;	//コントローラーを再生成するフラグ
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_40001:
            //バージョン(A)
            MSG("メニューの実装Ver1.0", "バージョン情報");
            break;

        case ID_40002:
            //終了(X)
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;

        case FLEME_MANUAL:// 操作方法フレーム表示
            CEdit::GetInstance()->SetIsOpen(CEdit::FREME_MANUAL, true);
            break;

        case FLEME_SYSTEM:
            CEdit::GetInstance()->SetIsOpen(CEdit::FREME_SYSTEM, true);

            break;

        case FLEME_OBJECT:
            CEdit::GetInstance()->SetIsOpen(CEdit::FREME_OBJECT, true);

            break;

        case FLEME_INFO:
            CEdit::GetInstance()->SetIsOpen(CEdit::FREME_INFO, true);

            break;

        }
        break;

    default:
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================
// FPS取得
// Author : 後藤慎之助
//=========================================
#ifdef _DEBUG
int GetFPS(void)
{
    return g_nCountFPS;
}
#endif
