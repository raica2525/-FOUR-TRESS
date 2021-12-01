//====================================================================
//
// ���͏��� (input.cpp)
// Author : �ɓ��z��
//
//====================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "input.h"

//*****************************************************************************
// Joypad�p�ݒ�l
//*****************************************************************************
#define DEADZONE        2500            // �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX       10000           // �L���͈͂̍ő�l
#define RANGE_MIN       -10000          // �L���͈͂̍ŏ��l

//========================================
// �ÓI�����o�ϐ��錾
//========================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//========================================
// ���͂̃f�t�H���g�R���X�g���N�^
//========================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//========================================
// ���͂̃f�X�g���N�^
//========================================
CInput::~CInput()
{

}

//========================================
// ���͂̏���������
//========================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���łɍ�������ǂ�������
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================================
// ���͂̏I������
//========================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		// �L�[�{�[�h�̃A�N�Z�X�����J��(���͐���I��)
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// Directinput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}