//=============================================================================
//
// ���C������ [main.cpp]
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
// �}�N����`
//*****************************************************************************
#define WINDOW_NAME		"�}�b�v����c�[��"	// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)


#ifdef _DEBUG
LPD3DXFONT				g_pFont = NULL;			// �t�H���g�ւ̃|�C���^
int						g_nCountFPS;			// FPS�J�E���^
#endif

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CManager* pManager = NULL;		//�}�l�[�W���̃|�C���^
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

	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);

	// �E�B���h�E�̍쐬
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

	//����������
	pManager = new CManager;
	pManager->Init(hWnd,true, hInstance);
	
	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime =
	dwFrameCount = 0;
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else if(!TranslateAccelerator(hWnd, hAccel,&msg))
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
#ifdef _DEBUG
				// FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
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
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
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

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ���j���[�o�[�̏���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ���j���[�o�[�̃`�F�b�N�}�[�N�؂�ւ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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