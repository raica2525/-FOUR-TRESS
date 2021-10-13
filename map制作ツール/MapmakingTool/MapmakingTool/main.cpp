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
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

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
	if(pManager != NULL)
	pManager->Uninit();
	delete pManager;
	pManager = NULL;


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
// �_�C�A���O���J��(func��0�̏ꍇ�ۑ��A1�̏ꍇ�ǂݍ���)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void OpenDialog(HWND hWnd,int func)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	char SavePath[512];
	char FileName[256];
	FileName[0] = '\0';
	GetCurrentDirectory(512, SavePath);
	strcat(SavePath, "\\Save");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrInitialDir = SavePath;
	ofn.lpstrFile = FileName;
	ofn.nMaxFile = 256;
	ofn.lpstrDefExt = "ini";
	ofn.lpstrFilter = "�ݒ�t�@�C��(*.ini)\0*.ini\0" "�e�L�X�g�t�@�C��(*.txt)\0*.txt\0" "���ׂẴt�@�C��(*.*)\0*.*\0";
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	if (func == 0)
	{
		GetSaveFileName(&ofn);
	}
	else if (func == 1)
	{
		GetOpenFileName(&ofn);
	}
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ���j���[�o�[�̏���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void MenuBar(MENUITEMINFO menuinfo,HWND hWnd,WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_WINDOW_OBJECTINFO:
		CManager::ChangeShowMainWindow();
		ChangeCheckMenuItem(ID_WINDOW_OBJECTINFO);
		break;
	case ID_FILE_OPEN:
		OpenDialog(hWnd, 1);
		break;
	case ID_FILE_SAVE:
		OpenDialog(hWnd, 0);
		break;
	case ID_FILE_EXIT:
		DestroyWindow(hWnd);
		break;
	default:
		break;
	}
}

void ChangeCheckMenuItem(UINT nItem)
{
	MENUITEMINFO menuinfo;
	ZeroMemory(&menuinfo, sizeof(menuinfo));
	menuinfo.cbSize = sizeof(menuinfo);
	menuinfo.fMask = MIIM_STATE;
	GetMenuItemInfo(GetMenu(FindWindow(CLASS_NAME, NULL)), nItem, FALSE, &menuinfo);
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