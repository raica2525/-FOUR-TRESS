//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imguiwindow.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _IMGUIWINDOW_H_
#define _IMGUIWINDOW_H_

#include "main.h"
#include "imgui.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CImGuiWindow
{
public:

	CImGuiWindow();		//�R���X�g���N�^
	virtual ~CImGuiWindow();		//�f�X�g���N�^

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;		//�X�V�֐�
	void ChangeShowWindow(void) { m_bShow = !m_bShow; };
	
protected:
	void SetMenuID(UINT unMenuID) { m_unMenuID = unMenuID; };
	UINT GetMenuID(void) { return m_unMenuID; };
	bool m_bShow;
	static const ImVec2 IMGUI_DEFAULT_SIZE;

private:
	UINT m_unMenuID;
};

#endif

