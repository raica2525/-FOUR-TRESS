//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imguiwindow.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

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