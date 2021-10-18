//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imobjectwindow.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "imobjectwindow.h"
#include "imgui.h"
#include "resource.h"
CImObjectWindow::CImObjectWindow()
{

}
CImObjectWindow::~CImObjectWindow()
{

}

void CImObjectWindow::Init(void)
{
	SetMenuID(ID_WINDOW_OBJECTINFO);
}

void CImObjectWindow::Update(void)
{
	bool bShowBuff = m_bShow;
	if (m_bShow)
	{
		ImGui::SetNextWindowSize(IMGUI_DEFAULT_SIZE, ImGuiCond_Once);
		ImGui::Begin(u8"�I�u�W�F�N�g���", &m_bShow);
		ImGui::Text("FPS:%d", GetFPS());
		ImGui::Text(u8"�e�X�gTest");
		ImGui::End();
	}
	if (bShowBuff != m_bShow)
	{
		ChangeCheckMenuItem(GetMenuID());
	}
}

CImObjectWindow* CImObjectWindow::Create(void)
{
	CImObjectWindow* pImObjectWindow = new CImObjectWindow;
	pImObjectWindow->Init();
	return pImObjectWindow;
}

