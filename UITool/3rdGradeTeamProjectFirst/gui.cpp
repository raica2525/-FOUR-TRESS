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
    static OPENFILENAME ofn = { 0 };// �t�@�C���_�C�A���O�\����
    static TCHAR strFile[MAX_PATH], strCustom[256] = TEXT("Before files\0*.*\0\0");

    // �\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = TEXT("Text files {*.txt}\0*.txt\0")
        TEXT("HTML files {*.htm}\0*.htm;*.html\0")
        TEXT("All files {*.*}\0*.*\0\0");
    ofn.lpstrCustomFilter = strCustom;
    ofn.nMaxCustFilter = 256;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = strFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;

    ImGuiWindowFlags window_flags = 0;

    //  ImGui�t���[���̊J�n
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // �V�X�e���t���[��
    ImGui::Begin(u8"�V�X�e��");

    // ���j���[�o�[�i�������j
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

    if (ImGui::Button(u8"�J��"))
    {
        // �t�@�C���I���_�C�A���O��\��
        std::cout << "�Q�Ƃ�I��" << std::endl;
        GetOpenFileName(&ofn);// �_�C�A���O�\��
        // �t�@�C���̓ǂݍ���
        CFile_Manager::GetInstance()->CFile_Manager::Read(ofn.lpstrFile);
        std::cout << ofn.lpstrFile<<std::endl;
    }

    ImGui::SameLine();
    ImGui::SameLine(110);

    // �`�F�b�N�{�b�N�X
    if (ImGui::Checkbox(u8"�v���r���[", &CUI::GetPreview()))
    {
        // IsPreview��true���ƃv���r���[���[�h�ɐ؂�ւ�
        CDebug::SetIsReload(CUI::GetPreview());
    }
    // �c�[���`�b�v
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(u8"���[�h��؂�ւ��܂�");


    if (ImGui::CollapsingHeader(u8"�܂���"))
    {

    }

    static int Value = 0;
    static float col1[3] = { 1.0f,0.0f,0.2f };
    ImGui::ColorEdit3("color 1", col1);


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

            ImGui::Begin(u8"���");

            static int nUI = 0;// �I�����Ă���UI

            // �܂肽���݃{�b�N�X
            if (!ImGui::CollapsingHeader(u8"�I��"))
            {
                static int e = 0;
                ImGui::Combo(u8"�e�N�X�`��", &e, u8"�Ȃ� \0�Q�[�W \0�g�k \0�ړ� \0�����x \0�F�ς� \0��] \0�e�N�X�`���u�����h \0���[�v�A�j���[�V���� \0�e�N�X�`���̕`��ʒu�w�� \0�G�t�F�N�g����");

                const char* listbox_items[] = { u8"�w�i", u8"���S", u8"Cherry",  };
                ImGui::ListBox(u8"�I�u�W�F�N�g", &nUI, listbox_items, IM_ARRAYSIZE(listbox_items), 5);

            }

            // UI�̏����擾
            CUI* pUI = CUI::GetUI(nUI);

            assert(pUI);

            D3DXVECTOR3 pos = pUI->GetPosition();
            D3DXVECTOR3 size = pUI->GetSize();

            // �܂肽���݃{�b�N�X
            if (!ImGui::CollapsingHeader(u8"�g�����X�t�H�[��"))
            {
                ImGui::InputFloat3("POS", pos);
                ImGui::InputFloat3("SIZE", size);
            }

            pUI->SetPosition(pos);
            pUI->SetSize(size);

            static int item = 0;

            // �܂肽���݃{�b�N�X
            if (!ImGui::CollapsingHeader(u8"�A�N�V����"))
            {
                static int e = 0;
                // ���1������̒l���Əo��
                ImGui::Combo(u8"���2", &e, u8"�Ȃ� \0�Q�[�W \0�g�k \0�ړ� \0�����x \0�F�ς� \0��] \0�e�N�X�`���u�����h \0���[�v�A�j���[�V���� \0�e�N�X�`���̕`��ʒu�w�� \0�G�t�F�N�g����");
            }

            // �`�F�b�N�{�b�N�X
            static bool no_titlebar = false;
            ImGui::Checkbox(u8"���b�N", &no_titlebar);
            // �c�[���`�b�v
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(u8"�J�[�\���ȂǂɎg�p����ꍇ�̓��b�N���Ă�������");
    ImGui::End();// �I���

}

//=============================================================================
//[UIEdit] UI�̕ҏW
//=============================================================================
void CGUI::UIEdit(void)
{

}

