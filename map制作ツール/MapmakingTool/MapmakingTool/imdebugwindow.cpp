//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imdebugwindow.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "imdebugwindow.h"
#include "imgui.h"
#include "resource.h"
CImDebugWindow::CImDebugWindow()
{

}
CImDebugWindow::~CImDebugWindow()
{

}

void CImDebugWindow::Init(void)
{
	SetMenuID(ID_WINDOW_OBJECTINFO);
}

void CImDebugWindow::Update(void)
{
	bool bShowBuff = m_bShow;
	if (m_bShow)
	{
		ImGui::SetNextWindowSize(IMGUI_DEFAULT_SIZE, ImGuiCond_Once);
		ImGui::Begin(u8"�f�o�b�O���", &m_bShow);
		ImGui::Text("FPS:%d", GetFPS());
		ImGui::Text(u8"�e�X�gTest");
		ImGui::End();
	}
	if (bShowBuff != m_bShow)
	{
		ChangeCheckMenuItem(GetMenuID());
	}
}

CImDebugWindow* CImDebugWindow::Create(void)
{
	CImDebugWindow* pImDebugWindow = new CImDebugWindow;
	pImDebugWindow->Init();
	return pImDebugWindow;
}

