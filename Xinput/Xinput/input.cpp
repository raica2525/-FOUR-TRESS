//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	input.cpp(ver.XInput)
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "input.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputJoypad::CInputJoypad()
{
	ZeroMemory(m_abConnected, sizeof(m_abConnected));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputJoypad::~CInputJoypad()
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CInputJoypad::Init(void)
{
	//XInput��L����
	XInputEnable(true);
	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputJoypad::Update(void)
{
	XINPUT_STATE state;
	for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
	{
		if (XInputGetState(nCount, &state) == ERROR_SUCCESS)
		{
			m_abConnected[nCount] = true;
		}
		else
		{
			m_abConnected[nCount] = false;
		}
	}
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputJoypad::Uninit(void)
{
	XInputEnable(false);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �R���g���[���[�̏�Ԃ��擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CInputJoypad::GetState(int nPad, XINPUT_STATE* pState)
{
	if (nPad < XUSER_MAX_COUNT)
	{
		XINPUT_STATE state;
		if (XInputGetState(nPad, &state) == ERROR_SUCCESS)
		{
			*pState = state;
			return S_OK;
		}
	}
	return E_FAIL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �{�^���̏�Ԃ��擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CInputJoypad::GetButtonState(int nPad, WORD wButtons)
{
	XINPUT_STATE state;
	if ((GetState(nPad, &state)) == S_OK)
	{
		if (state.Gamepad.wButtons & wButtons)
		{
			return true;
		}
	}
	return false;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �ڑ�����Ă���R���g���[���[�̐����擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CInputJoypad::GetConnectedPadNum(void)
{
	XINPUT_STATE state;
	int nPads = 0;
	for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
	{
		if (XInputGetState(nCount, &state) == ERROR_SUCCESS)
		{
			nPads++;
		}
	}
	return nPads;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �g���K�[�̉����󋵂��擾(LTrigger = 0,RTrigger = 1)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CInputJoypad::GetTriggerState(int nPad, int LR, int nDeadzone)
{
	XINPUT_STATE state;
	if (XInputGetState(nPad, &state) == ERROR_SUCCESS)
	{
		if (LR == 0)
		{
			if (state.Gamepad.bLeftTrigger > nDeadzone)
			{
				return true;
			}
		}
		else
		{
			if (state.Gamepad.bRightTrigger > nDeadzone)
			{
				return true;
			}
		}
	}
	return false;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �X�e�B�b�N�̌X������擾�iLStick = 0, RStick = 1)�iX�� = 0, Y�� = 1)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR2 CInputJoypad::GetStickValue(int nPad, int LR)
{
	XINPUT_STATE state;
	D3DXVECTOR2 vec2 = {};
	if (XInputGetState(nPad, &state) == ERROR_SUCCESS)
	{
		if (LR == 0)
		{
			if (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > state.Gamepad.sThumbLX &&
				-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbLX &&
				XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > state.Gamepad.sThumbLY &&
				-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbLY)
			{
				vec2.x = 0;
				vec2.y = 0;
			}
			else
			{
				vec2.x = state.Gamepad.sThumbLX;
				vec2.y = state.Gamepad.sThumbLY;
			}
		}
		else
		{
			if (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > state.Gamepad.sThumbRX &&
				-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < state.Gamepad.sThumbRX &&
				XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > state.Gamepad.sThumbRY &&
				-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < state.Gamepad.sThumbRY)
			{
				vec2.x = 0;
				vec2.y = 0;
			}
			else
			{
				vec2.x = state.Gamepad.sThumbRX;
				vec2.y = state.Gamepad.sThumbRY;
			}
		}
	}
	return vec2;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �U�����J�n
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputJoypad::StartVibration(int nPad, int LMoter, int RMoter)
{
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = LMoter;
	vibration.wRightMotorSpeed = RMoter;
	XInputSetState(nPad, &vibration);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �U�����I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputJoypad::StopVibration(int nPad)
{
	StartVibration(nPad, 0, 0);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputJoypad* CInputJoypad::Create(void)
{
	CInputJoypad* pInput = new CInputJoypad;
	pInput->Init();

	return pInput;
}