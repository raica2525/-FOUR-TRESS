//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "imgui_impl_win32.h"
#include "resource.h"
#include "imguimanager.h"
#include "imguiwindow.h"
#include "fileio.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WINDOW_NAME		"マップ制作ツール"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)


#ifdef _DEBUG
LPD3DXFONT				g_pFont = NULL;			// フォントへのポインタ
int						g_nCountFPS;			// FPSカウンタ
#endif

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CManager* pManager = NULL;		//マネージャのポインタ
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1)),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		CLASS_NAME,
		NULL
	};

	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);

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

	//初期化処理
	pManager = new CManager;
	pManager->Init(hWnd,true, hInstance);
	
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

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else if(!TranslateAccelerator(hWnd, hAccel,&msg))
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
#ifdef _DEBUG
				// FPSを算出
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

				// 更新処理
				pManager->Update();

				// 描画処理
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
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	MENUITEMINFO menuinfo;
	ZeroMemory(&menuinfo, sizeof(menuinfo));
	menuinfo.cbSize = sizeof(menuinfo);
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	case WM_COMMAND:
		MenuBar(menuinfo,hWnd,wParam);
		return 0;
	default:
		break;
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GetFPS(void)
{
	return g_nCountFPS;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// メニューバーの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void MenuBar(MENUITEMINFO menuinfo,HWND hWnd,WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_WINDOW_OBJECTINFO:
		CManager::GetImGuiManager()->GetImGuiWindow(CImGuiManager::IMWINDOW_OBJ_INFO)->ChangeShowWindow();
		ChangeCheckMenuItem(ID_WINDOW_OBJECTINFO);
		break;
	case ID_WINDOW_MAPINFO:
		CManager::GetImGuiManager()->GetImGuiWindow(CImGuiManager::IMWINDOW_MAP_INFO)->ChangeShowWindow();
		ChangeCheckMenuItem(ID_WINDOW_MAPINFO);
		break;
	case ID_WINDOW_DEBUGINFO:
		CManager::GetImGuiManager()->GetImGuiWindow(CImGuiManager::IMWINDOW_DEBUG_INFO)->ChangeShowWindow();
		ChangeCheckMenuItem(ID_WINDOW_DEBUGINFO);
		break;
	case ID_FILE_LOAD:
		CFileIO::OpenDialog(hWnd, CFileIO::DIALOG_LOAD);
		break;
	case ID_FILE_SAVE:
		CFileIO::OpenDialog(hWnd, CFileIO::DIALOG_SAVE);
		break;
	case ID_FILE_OVERRIDE:
		CFileIO::OverWrite(hWnd);
		break;
	case ID_FILE_EXIT:
		DestroyWindow(hWnd);
		break;
	default:
		break;
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// メニューバーのチェックマーク切り替え
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void ChangeCheckMenuItem(UINT nItem)
{
	MENUITEMINFO menuinfo;
	ZeroMemory(&menuinfo, sizeof(menuinfo));
	menuinfo.cbSize = sizeof(menuinfo);
	menuinfo.fMask = MIIM_STATE;
	GetMenuItemInfo(GetMenu(FindWindow(CLASS_NAME, NULL)), nItem, FALSE, &menuinfo);
	DWORD error = GetLastError();
	if (menuinfo.fState == MFS_UNCHECKED) 
	{
		menuinfo.fState = MFS_CHECKED;
	}
	else
	{
		menuinfo.fState = MFS_UNCHECKED;
	}
	SetMenuItemInfo(GetMenu(FindWindow(CLASS_NAME, NULL)), nItem, FALSE, &menuinfo);
}