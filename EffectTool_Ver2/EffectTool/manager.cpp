//===============================================
//
// �����̊Ǘ����� (manager.cpp)
// Author : �ɓ��z��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "mode.h"
#include <typeinfo.h>
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "effectData.h"
#include "effecttool.h"
#include "tool.h"
#include "scene.h"

//========================================
// �}�N����`
//========================================

//========================================
// �ÓI�����o�ϐ��錾
//========================================
CRenderer *CManager::m_pRenderer = NULL;
CMouse *CManager::m_pMouse = NULL;
CMode *CManager::m_pMode = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CTexture *CManager::m_pTexture = NULL;
CEffectData *CManager::m_pEffectData = NULL;
CEffectTool *CManager::m_pEffectTool = NULL;

//========================================
// �����̊Ǘ��̃f�t�H���g�R���X�g���N�^
//========================================
CManager::CManager()
{

}

//========================================
// �����̊Ǘ��̃f�X�g���N�^
//========================================
CManager::~CManager()
{

}

//========================================
// �����̊Ǘ��̏���������
//========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���(��񂵂��������Ȃ����̂́ACreate��p�ӂ��Ă��Ȃ�)
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// �}�E�X�̐���
	m_pMouse = new CMouse;
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���C�g�̐���
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// �J�����̐���
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`���̐���
	m_pTexture = new CTexture;
	if (FAILED(m_pTexture->Init()))
	{
		return E_FAIL;
	}

	// �G�t�F�N�g�f�[�^�Ǘ��̐���
	m_pEffectData = new CEffectData;
	if (FAILED(m_pEffectData->Init()))
	{
		return E_FAIL;
	}
	// �G�t�F�N�g�c�[���̐���
	m_pEffectTool = new CEffectTool;
	if (FAILED(m_pEffectTool->Init(hWnd)))
	{
		return E_FAIL;
	}

	SetMode(MODE_TOOL);

	return S_OK;
}
//========================================
// �����̊Ǘ��̏I������
//========================================
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g��j��
	CScene::ReleaseAll();

	// ���[�h�j��
	if (m_pMode != NULL)
	{
		// ���[�h�̏I������
		m_pMode->Uninit();

		// ���[�h�̃������̊J��
		delete m_pMode;
		m_pMode = NULL;
	}

	// �G�t�F�N�g�c�[���j��
	if (m_pEffectTool != NULL)
	{
		// �G�t�F�N�g�c�[���̏I������
		m_pEffectTool->Uninit();

		// �G�t�F�N�g�c�[���̃������̊J��
		delete m_pEffectTool;
		m_pEffectTool = NULL;
	}

	// �G�t�F�N�g�f�[�^�Ǘ��j��
	if (m_pEffectData != NULL)
	{
		// ���f���f�[�^�̏I������2
		m_pEffectData->Uninit();

		// ���f���f�[�^�̃������̊J��
		delete m_pEffectData;
		m_pEffectData = NULL;
	}

	// �e�N�X�`���j��
	if (m_pTexture != NULL)
	{
		// �e�N�X�`���̏I������
		m_pTexture->Uninit();

		// �e�N�X�`���̃������̊J��
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �}�E�X�̔j��
	if (m_pMouse != NULL)
	{
		// �}�E�X�I������
		m_pMouse->Uninit();

		// �}�E�X�̃������̊J��
		delete m_pMouse;
		m_pMouse = NULL;
	}

	// �����_���[�j��
	if (m_pRenderer != NULL)
	{
		// �����_���[�I������
		m_pRenderer->Uninit();

		// �����_���[�̃������̊J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//========================================
// �����̊Ǘ��̍X�V����
//========================================
void CManager::Update(void)
{
	// �}�E�X�X�V����
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	// �����_���[�X�V����
	if (m_pRenderer != NULL)
	{
		// ���[�h������Ȃ�
		if (m_pMode != NULL)
		{
			// ��ɑS�čX�V
			m_pRenderer->Update();
		}
	}

	// ���[�h�̍X�V����
	if (m_pMode != NULL)
	{
		m_pMode->Update();
	}

	// �J�����̍X�V����
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// �G�t�F�N�g�c�[���̍X�V����
	if (m_pEffectTool != NULL)
	{
		m_pEffectTool->Update();
	}
}

//========================================
// �����̊Ǘ��̕`�揈��
//========================================
void CManager::Draw(void)
{
	// �`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//========================================
// ���[�h�̎擾
//========================================
CManager::MODE CManager::GetMode(void)
{
	// �Ԃ�l�Ɏg�����[�h
	MODE mode = MODE_NONE;

	// ���̃��[�h�������Ă��邩���āA�^�����Ƃɏꍇ����
	if (typeid(*m_pMode) == typeid(CTool))
	{
		mode = MODE_TOOL;
	}

	return mode;
}

//========================================
// ���[�h�̐ݒ�
// mode	:	�ݒ肷�郂�[�h
//========================================
void CManager::SetMode(MODE mode)
{
    // ���[�h�̒��g������Ȃ�
    if (m_pMode != NULL)
    {
        // �I������
        m_pMode->Uninit();

        // �������̔j��
        delete m_pMode;
        m_pMode = NULL;
    }

    // �V�[����̃I�u�W�F�N�g��S�ďI������
    CScene::ReleaseAll();

    // �󂯎�������[�h�ɉ�ʑJ��
    switch (mode)
    {
	case MODE_TOOL:
		m_pMode = new CTool;
		break;
    }

    // �m�ۂ������[�h�̏�����
    m_pMode->Init();
}