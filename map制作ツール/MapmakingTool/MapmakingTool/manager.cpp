//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::m_pRenderer = NULL;
CCamera* CManager::m_pCamera = NULL;
bool CManager::m_bImShowMainWindow = false;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::CManager()
{
	m_pRenderer = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::~CManager()
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	m_pRenderer = new CRenderer;	//�����_���𐶐�
	m_pRenderer->Init(hWnd, true);	//�����_����������

	InitImGui(hWnd);				//ImGui�̏�����
	m_pCamera = new CCamera;		//�J�����I�u�W�F�N�g�̐���
	m_pCamera->Init();
	
	LoadFile();						//�t�@�C���ǂݍ���

	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Uninit(void)
{
	//�V�[���̏I��
	CScene::ReleaseAll();
	
	//�J�����̏I��
	m_pCamera->Uninit();	
	delete m_pCamera;		
	m_pCamera = NULL;	

	//�����_���̏I��
	m_pRenderer->Uninit();	
	delete m_pRenderer;
	m_pRenderer = NULL; 

	//�ǂݍ��񂾃t�@�C���̃A�����[�h
	UnloadFiles();
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Update(void)
{
	//�����_���̍X�V
	m_pRenderer->Update();	
	
	m_pCamera->Update();

	UpdateImGui();

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Draw(void)
{
	m_pCamera->SetCamera();
	//�����_���̕`��
	m_pRenderer->Draw();	
	
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃��[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::LoadFile(void)
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::UnloadFiles(void)
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ImGui�̏�����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::InitImGui(HWND hWnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//�ݒ��n���\���̂��擾
	ImGuiIO& io = ImGui::GetIO();
	//���{�ꂪ���͂ł���悤�Ƀt�H���g��ǉ�
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 18.0f, nullptr, glyphRangesJapanese);
	//ImGUI���ɃX�N���[���T�C�Y��n��
	io.DisplaySize.x = SCREEN_WIDTH;
	io.DisplaySize.y = SCREEN_HEIGHT;
	//ImGui�ɕK�v�ȏ�����
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(m_pRenderer->GetDevice());
	//���F�̃X�^�C���ɕύX
	ImGui::StyleColorsDark();
}

void CManager::UpdateImGui(void)
{
	//�t���[�����ς�������Ƃ�ImGui�ɋ�����
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	//�����̃E�B���h�E�T�C�Y���w��
	ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
	bool bBuffMainWindow = m_bImShowMainWindow;
	//Begin����End�ň�̃E�B���h�E
	if (m_bImShowMainWindow)
	{
		ImGui::Begin(u8"�I�u�W�F�N�g���", &m_bImShowMainWindow);
		ImGui::Text("FPS:%d", GetFPS());
		ImGui::Text(u8"�e�X�gTest");
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