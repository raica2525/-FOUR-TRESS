//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	imguiwindow.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "main.h"
#include "imguiwindow.h"

const ImVec2 CImGuiWindow::IMGUI_DEFAULT_SIZE = ImVec2(320.0f, 100.0f);

CImGuiWindow::CImGuiWindow()
{
	m_bShow = false;
}

CImGuiWindow::~CImGuiWindow()
{

}