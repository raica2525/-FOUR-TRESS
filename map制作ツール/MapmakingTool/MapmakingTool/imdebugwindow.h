//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imdebugwindow.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _IMDEBUGWINDOW_H_
#define _IMDEBUGWINDOW_H_

#include "main.h"
#include "imguiwindow.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CImDebugWindow : public CImGuiWindow
{
public:

	CImDebugWindow();		//�R���X�g���N�^
	~CImDebugWindow();		//�f�X�g���N�^
	void Init(void);
	void Update(void);		//�X�V�֐�
	static CImDebugWindow* Create(void);
};

#endif

