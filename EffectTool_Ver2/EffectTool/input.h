//====================================================================
//
// ���͏��� (input.h)
// Author : �ɓ��z��
//
//====================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �N���X�錾
//================================================

// ���͂̃N���X
class CInput
{
public:
	CInput();
	virtual ~CInput();  // �e�N���X�̃f�X�g���N�^��virtual�����邱�ƂŁA���������[�N��}����
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;	// ���̓f�o�C�X�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;	// DirectInput�ւ̃|�C���^
};
#endif