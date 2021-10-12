//=============================================================================
//
// GUI�N���X [gui.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "gui.h"
#include "manager.h"
#include "file_manager.h"
#include "ui.h"
#include "debug.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// [CGUI] �R���X�g���N�^
//=============================================================================
CGUI::CGUI()
{

}

//=============================================================================
// [~CGUI] �f�X�g���N�^
//=============================================================================
CGUI::~CGUI()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CGUI* CGUI::Create(HWND hWnd)
{
    CGUI *pUi = NULL;
    if (!pUi)
    {
        pUi = new CGUI;
        pUi->Init(hWnd);
    }
    return pUi;
}

//=============================================================================
// [Init] ����������
//=============================================================================
void CGUI::Init(HWND hWnd)
{
    // IMGUI�̐ݒ�
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CGUI::Uninit(void)
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CGUI::Update(void)
{
    ImGuiWindowFlags window_flags = 0;
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // �V�X�e���t���[��
    ImGui::Begin(u8"�V�X�e��");

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    static bool show_app_main_menu_bar = false;

    if (ImGui::Button(u8"�t�@�C���̕ۑ�"))
    {
        CFile_Manager* pFileManager;
        // �t�@�C���̏�������
        pFileManager = CFile_Manager::Create();
        delete pFileManager;

    }
    ImGui::SameLine();
    ImGui::SameLine(110);

    if (ImGui::Button(u8"�v���r���["))
    {
        // �v���r���[�t���O���I��
        CDebug::SetIsReload(true);
    }

    if (ImGui::CollapsingHeader(u8"�܂���"))
    {

    }

    static int Value = 0;
    static float col1[3] = { 1.0f,0.0f,0.2f };
    ImGui::ColorEdit3("color 1", col1);

    ImGui::DragInt("Value", &Value, 100, 0, 100);// �o�[�̂��

    Manual();// ������@�\��
    information();
    ImGui::End();// �I���


    ImGui::EndFrame();
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CGUI::Draw(void)
{
    // ImGui�̕`��
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

}

//=============================================================================
// [Manual] ������@�t���[��
//=============================================================================
void CGUI::Manual(void)
{
    static bool open = true;
    if (open)
    {
        // IMGUI�J�n
        ImGui::Begin(u8"������@", &open);
        ImGui::Text(u8"F4�L�[�Ńv���r���[");
        ImGui::Text(u8"ESC�L�[�ŏI��");

        ImGui::End();// �I���
    }
}

//=============================================================================
//[information] ���t���[��
//=============================================================================
void CGUI::information(void)
{

    // UI�̏����擾
    CUI* pUI = CUI::GetAccessUI(0);
    D3DXVECTOR3 pos = pUI->GetPosition();
            ImGui::Begin(u8"���");

            static float fpos[3] = { 0.0f,0.0,0.0, };
            static float size[3] = { 0.0,0.0,0.0, };

            // �܂肽���݃{�b�N�X
            if (!ImGui::CollapsingHeader(u8"�I��"))
            {

            }
            // �܂肽���݃{�b�N�X
            if (!ImGui::CollapsingHeader(u8"�g�����X�t�H�[��"))
            {
                ImGui::InputFloat3("POS", pos);
                ImGui::InputFloat3("SIZE", size);
            }

            pUI->SetPosition(pos);

            static float begin = 10, end = 90, z = 100;

            static int item = 0;
            static int e = 0;

            // �܂肽���݃{�b�N�X
            if (!ImGui::CollapsingHeader(u8"�A�N�V����"))
            {
                // ���1������̒l���Əo��
                ImGui::Combo(u8"���2", &e, u8"�Ȃ� \0�Q�[�W \0�g�k \0�ړ� \0�����x \0�F�ς� \0��] \0�e�N�X�`���u�����h \0���[�v�A�j���[�V���� \0�e�N�X�`���̕`��ʒu�w�� \0�G�t�F�N�g����");
            }

            // �`�F�b�N�{�b�N�X
            static bool no_titlebar = false;
            ImGui::Checkbox(u8"���b�N", &no_titlebar);
            // �c�[���`�b�v
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(u8"�J�[�\���ȂǂɎg�p����ꍇ�̓��b�N���Ă�������");
            static int i1 = 0;
    ImGui::End();// �I���

}

//=============================================================================
//[UIEdit] UI�̕ҏW
//=============================================================================
void CGUI::UIEdit(void)
{

}

