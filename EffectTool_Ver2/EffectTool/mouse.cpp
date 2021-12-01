//====================================================================
//
// �}�E�X�̏��� (mouse.cpp)
// Author : �ɓ��z��
//
//====================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "mouse.h"

//========================================================
// �}�E�X�N���X�̃R���X�g���N�^
//========================================================
CMouse::CMouse()
{
	memset(m_aMouseState, 0, sizeof(m_aMouseState));
	memset(m_aMouseStateTrigger, 0, sizeof(m_aMouseStateTrigger));
	memset(m_aMouseStateRelease, 0, sizeof(m_aMouseStateRelease));
	memset(m_mousState.rgbButtons, 0, sizeof(m_mousState.rgbButtons));
	m_mousState.lX = 0;
	m_mousState.lY = 0;
	m_mousState.lZ = 0;
	m_fMouseSensi = MOUSE_SENSITIVITY;
	m_fWheelSensi = MOUSE_WHEEL_SENSITIVITY;
}

//========================================================
// �}�E�X�N���X�̃f�X�g���N�^
//========================================================
CMouse::~CMouse()
{

}

//========================================================
// �}�E�X�̏�����
//========================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// �f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	m_pDevice->Acquire();
	return S_OK;
}

//========================================================
// �}�E�X�̏I������
//========================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}


//========================================================
// �}�E�X�̍X�V����
//========================================================
void CMouse::Update(void)
{
	HRESULT hr;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mousState);

		//�f�o�C�X����f�[�^���擾
		if (SUCCEEDED(hr))
		{
			for (int nCntKey = 0; nCntKey < MAX_MOUSE_BOTTON; nCntKey++)
			{
				//�L�[�g���K�[
				m_aMouseStateTrigger[nCntKey] = (m_aMouseState[nCntKey] ^ m_mousState.rgbButtons[nCntKey]) &  m_mousState.rgbButtons[nCntKey];

				//�L�[�����[�X
				m_aMouseStateRelease[nCntKey] = (m_aMouseState[nCntKey] ^ m_mousState.rgbButtons[nCntKey]) & ~m_mousState.rgbButtons[nCntKey];

				//�L�[�v���X����ۑ�
				m_aMouseState[nCntKey] = m_mousState.rgbButtons[nCntKey];
			}
		}
		else
		{
			m_pDevice->Acquire();
		}
	}

	//�}�E�X�̊��x�ƃz�C�[���̊��x���}�C�i�X�ɂȂ�Ȃ��悤��
	if (m_fMouseSensi < 0)
	{
		m_fMouseSensi = 0;
	}
	if (m_fWheelSensi < 0)
	{
		m_fWheelSensi = 0;
	}
}

//========================================================
// �}�E�X�̃v���X�̏����擾
//========================================================
bool CMouse::GetMousePress(int nKey)
{
	return m_aMouseState[nKey] & 0x80 ? true : false;
}

//========================================================
// �}�E�X�̃g���K�[�̏����擾
//========================================================
bool CMouse::GetMouseTrigger(int nKey)
{
	return m_aMouseStateTrigger[nKey] & 0x80 ? true : false;
}

//========================================================
// �}�E�X�̃����[�X�̏����擾
//========================================================
bool CMouse::GetMouseRelease(int nKey)
{
	return m_aMouseStateRelease[nKey] & 0x80 ? true : false;
}

//========================================================
// �}�E�X�̈ړ��ʂ��擾
//========================================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3((float)m_mousState.lX, (float)m_mousState.lY, 0.0f) * m_fMouseSensi;
}

//========================================================
// �}�E�X�̃z�C�[�����擾
//========================================================
float CMouse::GetMouseWheel(void)
{
	return (float)m_mousState.lZ * m_fWheelSensi;
}

//========================================================
// �}�E�X�̊��x���擾
//========================================================
float & CMouse::GetMouseSensi(void)
{
	return m_fMouseSensi;
}

//========================================================
// �z�C�[���̊��x���擾
//========================================================
float & CMouse::GetWheelSensi(void)
{
	return m_fWheelSensi;
}
