//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imguimanager.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define FONT_SIZE (18.0f)
#define FONT_PATH ("c:\\Windows\\Fonts\\msgothic.ttc")
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CImGuiManager::CImGuiManager()
{
	m_bShowStructures = true;
	m_str[0] = '\0';
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CImGuiManager::~CImGuiManager()
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CImGuiManager::Init(HWND hWnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//�ݒ��n���\���̂��擾
	ImGuiIO& io = ImGui::GetIO();
	//���{�ꂪ���͂ł���悤�Ƀt�H���g��ǉ�
	io.Fonts->AddFontFromFileTTF(FONT_PATH, FONT_SIZE, nullptr, glyphRangesJapanese);
	//ImGUI���ɃX�N���[���T�C�Y��n��
	io.DisplaySize.x = SCREEN_WIDTH;
	io.DisplaySize.y = SCREEN_HEIGHT;
	//ImGui�ɕK�v�ȏ�����
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());
	//���F�̃X�^�C���ɕύX
	ImGui::StyleColorsDark();
	m_pImGuiWindow[IMWINDOW_OBJ_INFO] = CImObjectWindow::Create();
	m_pImGuiWindow[IMWINDOW_MAP_INFO] = CImMapWindow::Create();
	m_pImGuiWindow[IMWINDOW_DEBUG_INFO] = CImDebugWindow::Create();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CImGuiManager::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CImGuiManager::Update(void)
{
	//�t���[�����ς�������Ƃ�ImGui�ɋ�����
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	for (int nCount = 0; nCount < IMWINDOW_MAX; nCount++)
	{
		m_pImGuiWindow[nCount]->Update();
	}
	ImGui::EndFrame();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CImGuiManager::Draw(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
