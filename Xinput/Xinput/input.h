//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	input.h(ver.XInput)
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef INPUT_H_
#define INPUT_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include <Windows.h>
#include<XInput.h>

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ���C�u�����̃C���|�[�g
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#pragma comment (lib,"xinput.lib")

typedef struct
{
	float x;
	float y;
}D3DXVECTOR2;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

class CInput
{
public:

	CInput();
	~CInput();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	HRESULT GetState(int nPad, XINPUT_STATE* state);
	bool GetButtonState(int nPad, WORD wButtons);
	bool GetTriggerState(int nPad,int LR,int nDeadzone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	int GetConnectedPadNum(void);
	D3DXVECTOR2 GetStickValue(int nPad,int LR);
	void StartVibration(int nPad, int LMoter, int RMoter);
	void StopVibration(int nPad);
	static CInput* Create(void);
private:
	bool m_abConnected[XUSER_MAX_COUNT];
};

#endif // !INPUT_H_
