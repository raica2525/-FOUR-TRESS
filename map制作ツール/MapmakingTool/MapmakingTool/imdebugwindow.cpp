//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imdebugwindow.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "imdebugwindow.h"
#include "imgui.h"
#include "manager.h"
#include "resource.h"
#include "imguimanager.h"
CImDebugWindow::CImDebugWindow()
{

}
CImDebugWindow::~CImDebugWindow()
{

}

void CImDebugWindow::Init(void)
{
	SetMenuID(ID_WINDOW_DEBUGINFO);
}

void CImDebugWindow::Update(void)
{
	bool bShowBuff = m_bShow;
	if (m_bShow)
	{
		CImGuiManager* pImGuiManager = CManager::GetImGuiManager();
		bool bShowModel = pImGuiManager->GetShowStructure();
		bool bShowCollisions = pImGuiManager->GetShowCollisions();
		char str[1024];
		pImGuiManager->GetStr(str);
		ImGui::SetNextWindowSize(IMGUI_DEFAULT_SIZE, ImGuiCond_Once);
		ImGui::Begin(u8"デバッグ情報", &m_bShow);
		ImGui::Text("FPS:%d", GetFPS());
		ImGui::Checkbox(u8"モデルを表示", &bShowModel);
		ImGui::Checkbox(u8"コリジョンを表示", &bShowCollisions);
		if (ImGui::InputText("text", str, 1024))
		{
			pImGuiManager->SetStr(str);
		}
		ImGui::End();
		pImGuiManager->SetShowCollisions(bShowCollisions);
		pImGuiManager->SetShowStructures(bShowModel);
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

