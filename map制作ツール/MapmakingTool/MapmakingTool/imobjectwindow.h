//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imobjectwindow.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _IMOBJECTWINDOW_H_
#define _IMOBJECTWINDOW_H_

#include "main.h"
#include "imguiwindow.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CImObjectWindow : public CImGuiWindow
{
public:

	CImObjectWindow();		//�R���X�g���N�^
	~CImObjectWindow();		//�f�X�g���N�^
	void Init(void);
	void Update(void);		//�X�V�֐�
	static CImObjectWindow* Create(void);
};

#endif

