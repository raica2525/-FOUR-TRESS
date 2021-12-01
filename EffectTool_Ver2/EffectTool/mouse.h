//====================================================================
//
// �}�E�X�̏��� (mouse.h)
// Author : �ɓ��z��
//
//====================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "input.h"

//================================================
// �}�N����`
//================================================
#define MAX_MOUSE_BOTTON (3)//�L�[�̍ő吔

#define MOUSE_SENSITIVITY (0.0025f)	// �}�E�X���x
#define MOUSE_WHEEL_SENSITIVITY (1.0f)	// �}�E�X�z�C�[�����x

// �}�E�X�̃N���X
class CMouse : public CInput
{
public:
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetMousePress(int nKey);
	bool GetMouseTrigger(int nKey);
	bool GetMouseRelease(int nKey);

	D3DXVECTOR3 GetMouseMove(void);
	float GetMouseWheel(void);

	float& GetMouseSensi(void);
	float& GetWheelSensi(void);
private:
	BYTE m_aMouseState[MAX_MOUSE_BOTTON];			// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aMouseStateTrigger[MAX_MOUSE_BOTTON];	// �L�[�{�[�h�̃g���K�[���
	BYTE m_aMouseStateRelease[MAX_MOUSE_BOTTON];	// �L�[�{�[�h�̃����[�X���
	DIMOUSESTATE m_mousState;						// �}�E�X���
	float m_fMouseSensi;							// �}�E�X�̃Z���V
	float m_fWheelSensi;							// �z�C�[���̃Z���V
};

#endif