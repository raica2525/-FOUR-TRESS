//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	immapwindow.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _IMMAPWINDOW_H_
#define _IMMAPWINDOW_H_

#include "main.h"
#include "imguiwindow.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CImMapWindow : public CImGuiWindow
{
public:

	CImMapWindow();		//�R���X�g���N�^
	~CImMapWindow();		//�f�X�g���N�^
	void Init(void);
	void Update(void);		//�X�V�֐�
	static CImMapWindow* Create(void);
};

#endif

