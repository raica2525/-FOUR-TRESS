//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imobjectwindow.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "immapwindow.h"
#include "imgui.h"
#include "resource.h"
CImMapWindow::CImMapWindow()
{

}
CImMapWindow::~CImMapWindow()
{

}

void CImMapWindow::Init(void)
{
	SetMenuID(ID_WINDOW_MAPINFO);
}

void CImMapWindow::Update(void)
{
	bool bShowBuff = m_bShow;
	if (m_bShow)
	{
		ImGui::SetNextWindowSize(IMGUI_DEFAULT_SIZE, ImGuiCond_Once);
		ImGui::Begin(u8"マップ情報", &m_bShow);
		ImGui::Text("FPS:%d", GetFPS());
		ImGui::Text(u8"テストTest");
		ImGui::End();
	}
	if (bShowBuff != m_bShow)
	{
		ChangeCheckMenuItem(GetMenuID());
	}
}

CImMapWindow* CImMapWindow::Create(void)
{
	CImMapWindow* pImMapWindow = new CImMapWindow;
	pImMapWindow->Init();
	return pImMapWindow;
}

