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
#include "object.h"
#include "scene2d.h"
#include "camera.h"
#include "resource.h"
#include "imguimanager.h"
#include "modelData.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::m_pRenderer = NULL;
CCamera* CManager::m_pCamera = NULL;
CImGuiManager* CManager::m_pImGuiManager = NULL;
CModelData* CManager::m_pModelData = NULL;

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
	
	m_pImGuiManager = new CImGuiManager;
	m_pImGuiManager->Init(hWnd);
	
	m_pCamera = new CCamera;		//�J�����I�u�W�F�N�g�̐���
	m_pCamera->Init();

	m_pModelData = new CModelData;
	m_pModelData->Init();
	
	LoadFile();						//�t�@�C���ǂݍ���

	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Uninit(void)
{
	//�V�[���̏I��
	CObject::ReleaseAll();
	
	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		SAFE_DELETE(m_pCamera);
	}
	
	//IMGUI�̏I��
	if (m_pImGuiManager != NULL)
	{
		m_pImGuiManager->Uninit();
		SAFE_DELETE(m_pImGuiManager);
	}

	//�����_���̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		SAFE_DELETE(m_pRenderer);
	}

	if (m_pModelData != NULL) 
	{
		m_pModelData->Uninit();
		SAFE_DELETE(m_pModelData);
	}

	//�ǂݍ��񂾃t�@�C���̃A�����[�h
	UnloadFiles();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Update(void)
{
	//�����_���̍X�V
	m_pRenderer->Update();	
	
	//IMGUI�̍X�V
	m_pImGuiManager->Update();

	//�J�����̍X�V
	m_pCamera->Update();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Draw(void)
{
	//�J�����ݒ�
	m_pCamera->SetCamera();

	//IMGUI�̍X�V
	m_pImGuiManager->Draw();
	
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
