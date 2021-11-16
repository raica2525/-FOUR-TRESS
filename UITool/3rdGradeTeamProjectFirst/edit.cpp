//=============================================================================
//
// �ҏW���[�h�N���X [edit.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "edit.h"
#include "manager.h"
#include "file_manager.h"
#include "ui.h"
#include "debug.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include <sstream>

//*****************************************************************************
// �ÓI�����o�֐�
//*****************************************************************************
CEdit* CEdit::m_pInstance = nullptr;// �I�u�W�F�N�g�ւ̃|�C���^

//=============================================================================
// [CEdit] �R���X�g���N�^
//=============================================================================
CEdit::CEdit()
{
    m_UINum = 0;
    ofn = { 0 };

    for (int nCnt = 0; nCnt > FREME_MAX; nCnt++)
    {
        m_IsOpen[nCnt] = true;
    }
}

//=============================================================================
// [~CEdit] �f�X�g���N�^
//=============================================================================
CEdit::~CEdit()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CEdit* CEdit::Create(HWND hWnd)
{
    // �I�u�W�F�N�g����
    if (!m_pInstance)
    {
        m_pInstance = new CEdit;
        m_pInstance->Init(hWnd);
    }
    return m_pInstance;
}

//=============================================================================
// [Init] ����������
//=============================================================================
void CEdit::Init(HWND hWnd)
{
    // IMGUI�̐ݒ�
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

    m_hwnd = hWnd;
    m_UINum = 0;

    static TCHAR strFile[MAX_PATH], strCustom[256] = TEXT("Before files\0*.*\0\0");

    // �\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = m_hwnd;
    ofn.lpstrFilter = TEXT("Text files {*.txt}\0*.txt\0")
        TEXT("HTML files {*.htm}\0*.htm;*.html\0")
        TEXT("All files {*.*}\0*.*\0\0");
    ofn.lpstrCustomFilter = strCustom;
    ofn.nMaxCustFilter = 256;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = strFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;

}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CEdit::Uninit(void)
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CEdit::Update(void)
{
    ImGuiWindowFlags window_flags = 0;

    //  ImGui�t���[���̊J�n
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Manual();// ������@�\��
    System();// �V�X�e���t���[���̕\��
    UIEdit();// �I�u�W�F�N�g�̑I��
    information();// �I�u�W�F�N�g�̏��

    ImGui::EndFrame();// ImGui�t���[���̏I��
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CEdit::Draw(void)
{
    // ImGui�̕`��
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//=============================================================================
// [Manual] ������@�t���[��
//=============================================================================
void CEdit::Manual(void)
{
    if (!m_IsOpen[FREME_MANUAL])    // �t���[�������Ă���Ƃ��͐������Ȃ�
        return;

        // IMGUI�J�n
        ImGui::Begin(u8"������@", &m_IsOpen[FREME_MANUAL]);
        ImGui::Text(u8"F4�L�[�Ńv���r���[");
        ImGui::Text(u8"ESC�L�[�ŏI��");

        ImGui::End();// �I���
}


//=============================================================================
//[information] ���t���[��
//=============================================================================
void CEdit::information(void)
{
    // UI�̏����擾
    CUI* pUI = CUI::GetUI(m_UINum);
    assert(pUI);

    // �g�����X�t�H�[���̏��擾
    D3DXVECTOR3 pos = pUI->GetMemoryPos();
    D3DXVECTOR3 size = pUI->GetMemorySize();
    float rot = D3DXToDegree( pUI->GetRot());// �擾�����p�x���f�O���[�ɕϊ�

    if (!m_IsOpen[FREME_INFO])
        return;

    ImGui::Begin(u8"���", &m_IsOpen[FREME_INFO]);

    // �܂肽���݃{�b�N�X
    if (!ImGui::CollapsingHeader(u8"��{���"))
    {
        static char str0[8] = "test";
        ImGui::InputText(u8"UI��", str0, IM_ARRAYSIZE(str0));

        static int e = 0;
        ImGui::Combo(u8"�g�p�e�N�X�`��", &e, u8"�Ȃ� \0�Q�[�W \0�g�k \0�ړ� \0�����x \0�F�ς� \0��] \0�e�N�X�`���u�����h \0���[�v�A�j���[�V���� \0�e�N�X�`���̕`��ʒu�w�� \0�G�t�F�N�g����");
    }

    // �܂肽���݃{�b�N�X
    if (!ImGui::CollapsingHeader(u8"�g�����X�t�H�[��"))
    {
        ImGui::DragFloat2("POS", pos, 1, -600, 1500.0f);        // �ʒu�̐ݒ�
        ImGui::DragFloat2("SIZE", size, 1, 0.0f, 1500.0f);      // �T�C�Y�̐ݒ�
        ImGui::DragFloat("ROT", &rot, 1.0f, -180.0f, 180.0f);   // �p�x�̐ݒ�
    }
     
    // �g�����X�t�H�[���𔽉f
    pUI->SetPosition(pos);
    pUI->SetMemoryPos(pos);
    pUI->SetSize(size);
    pUI->SetMemorySize(size);
    pUI->SetRot(D3DXToRadian( rot));
    pUI->SetMemoryRot(D3DXToRadian(rot));

    // �F�̐ݒ�
    static D3DXCOLOR col = pUI->GetCol();
    ImGui::ColorEdit4("color 1", col);

    pUI->SetCol(col);// �F�̔��f
    pUI->SetMemoryCol(col);// �F�̔��f

    // �A�N�V�����̐ݒ�
    if (!ImGui::CollapsingHeader(u8"�A�N�V����"))
    {
        SetAction(pUI);
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
//[UIEdit] �I�u�W�F�N�g�t���[��
//=============================================================================
void CEdit::UIEdit(void)
{
    if (!m_IsOpen[FREME_OBJECT])    // �t���[�������Ă���Ƃ��͐������Ȃ�
        return;

    ImGui::Begin(u8"�I�u�W�F�N�g", &m_IsOpen[FREME_OBJECT]);

    const char* listbox_items[] = { u8"�w�i", u8"���S", u8"Cherry", };
    ImGui::ListBox("\0", &m_UINum, listbox_items, IM_ARRAYSIZE(listbox_items), 5);

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

    ImGui::End();// �I���
}

//=============================================================================
//[System] �V�X�e���t���[��
//=============================================================================
void CEdit::System(void)
{
    if (!m_IsOpen[FREME_SYSTEM])    // �t���[�������Ă���Ƃ��͐������Ȃ�
        return;

    // �V�X�e���t���[��
    ImGui::Begin(u8"�V�X�e��", &m_IsOpen[FREME_SYSTEM]);

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
                              //CFile_Manager::GetInstance()->CFile_Manager::Read(ofn.lpstrFile);
        std::cout << ofn.lpstrFile << std::endl;
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

    static float vec4f[2] = {};
    if (ImGui::CollapsingHeader(u8"�܂���"))
    {
        ImGui::SliderFloat2("slider float2", vec4f, -600, 1500.0f);
    }

    ImGui::End();// �I���
}

//=============================================================================
//[SetAction] �A�N�V�����̐ݒ�
// ����
// pUI : �ݒ肵����UI�ւ̃|�C���^
//=============================================================================
void CEdit::SetAction(CUI * pUI)
{
    static int ActionNum = 0;       // �A�N�V�����ԍ�

    ImGui::Combo(u8"�A�N�V�����ԍ�", &ActionNum, u8"0 \0 1 \0 2 \0 3");

    CUI::ActionInfo Action = pUI->GetActionInfo(ActionNum); // �A�N�V�������̎擾

    int ActionType = Action.action;       // �A�N�V�����̎��

    ImGui::Combo(u8"���", &ActionType, u8"0:�Ȃ� \0 1:�Q�[�W \0 2:�g�k \0 3:�ړ� \0 4:�����x \0 5:�F�ς� \0 6:��] \0 7:�e�N�X�`���u�����h \0 8:���[�v�A�j���[�V���� \0 9:�e�N�X�`���̕`��ʒu�w�� \0 10:�G�t�F�N�g����");

    // �A�N�V�����̎�ނɂ���ē��e���ς��
    switch (ActionType)
    {
    case CUI::ACTION_NONE:

        break;

    case CUI::ACTION_GAUGE:// �Q�[�W
    // �Q�[�W�̓Q�[�����̃v���O�����ł�����̂Őݒ�͂Ȃ�
        break;

    case CUI::ACTION_SIZE:    // �T�C�Y�ύX
        ActionSize(Action);
        break;

    case CUI::ACTION_POS:     // �ړ��ʐݒ�
        ActionPos(Action);
        break;

    case CUI::ACTION_ALPHA:   // �A���t�@�l�ύX
        ActionAlpha(Action);
        break;

    case CUI::ACTION_COLOR:   // �F�ύX
        ActionColor(Action);
        break;

    case CUI::ACTION_ROT:    // �p�x�ύX

        ActionRot(Action);
        break;

    case CUI::ACTION_TEX_BREND:// ���u�����h
        ActionTexBrend(Action);
        break;

    case CUI::ACTION_LOOP_ANIM:// ���[�v�A�j��
        ActionLoopAnim(Action);
        break;

    case CUI::ACTION_TEX_PLACE:// �e�N�X�`���̕���
        ActionTexPlace(Action);
        break;

    case CUI::ACTION_EMIT_EFFECT:// �G�t�F�N�g
        ActionEmitEffect(Action);
        break;
    default:
        assert(ActionType);
        break;
    }

    // �A�N�V�����̃Z�b�g
    pUI->SetActionInfo(ActionNum, ActionType, Action.bLock, Action.afParam[0], Action.afParam[1], Action.afParam[2], Action.afParam[3], Action.afParam[4], Action.afParam[5], Action.afParam[6], Action.afParam[7]);

}

//=============================================================================
//[ActionSize] �g�k�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionSize(CUI::ActionInfo& Action)
{
    // �ϐ���`
    static D3DXVECTOR2 size      = { Action.afParam[0],Action.afParam[1] };   // XY�g�k��
    static bool IsEqualRatio     = Action.afParam[2];                         // ����ό`���ǂ���
    static int nAction           = Action.afParam[3];                         // ����̎��
    static float fFrame          = Action.afParam[4];                         // �t���[����
    static D3DXVECTOR2 limit     = { Action.afParam[5], Action.afParam[6] };  // XY���E�l

    // �g�k
    ImGui::DragFloat2(u8"�T�C�Y", size, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(u8"PARAM0�F�g�kX \n PARAM1�F�g�kY");
    Action.afParam[0] = size.x;
    Action.afParam[1] = size.y;

    //����ό`���ǂ����ibool�j
    ImGui::Checkbox(u8"����ό`", &IsEqualRatio);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F����ό`���ǂ���");
    Action.afParam[2] = IsEqualRatio ? 1.0f : 0.0f;    // bool�l��float�^�ɕϊ�

    ImGui::Combo(u8"����ݒ�", &nAction, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F����ݒ�");
    Action.afParam[3] = nAction;

    // �t���[��
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1, 0, 1000);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM4�F�t���[��");
    Action.afParam[4] = fFrame;

    // X Y�Z�l�܂�
    ImGui::DragFloat2(u8"XY�̌��E�l", limit, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM5�F���E�lX \n PARAM6�F���E�lY");
    Action.afParam[5] = limit.x;
    Action.afParam[6] = limit.y;
}

//=============================================================================
//[ActionPos] �ʒu�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionPos(CUI::ActionInfo &Action)
{
    // �ϐ���`
    static D3DXVECTOR2 move      = { Action.afParam[0],Action.afParam[1] };    // XY�g�k��
    static float Acceleration    = Action.afParam[2];                          // �����x
    static int nAction           = Action.afParam[3];                          // ����̎��
    static float fFrame          = Action.afParam[4];                          // �t���[����
    static D3DXVECTOR2 limit     = { Action.afParam[5],Action.afParam[6] };    // ���E�l

    // X Y
    ImGui::DragFloat2(u8"�ړ���", move, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F�ړ���X \n PARAM1�F�ړ���Y");
    Action.afParam[0] = move.x;
    Action.afParam[1] = move.y;

    // �����x
    ImGui::DragFloat(u8"�����x", &Acceleration, 1, 0, 100.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F�����x");
    Action.afParam[2] = Acceleration;

    // ����ݒ�
    ImGui::Combo(u8"����ݒ�", &nAction, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F����ݒ�");
    Action.afParam[3] = nAction;

    // �t���[��
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1, 0, 1000.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM4�F�t���[��");
    Action.afParam[4] = fFrame;

    // X Y�Z�l�܂�
    ImGui::DragFloat2(u8"���E�l", limit, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM5�FX���E�l \n PARAM6�FY���E�l");
    Action.afParam[5] = limit.x;
    Action.afParam[6] = limit.y;
}

//=============================================================================
//[ActionAlpha] �A���t�@�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionAlpha(CUI::ActionInfo & Action)
{
    // �ϐ���`
    static float alpha   = Action.afParam[0];    // �A���t�@�l
    static int nAction   = Action.afParam[1];    // ����̎��
    static float fFrame  = Action.afParam[2];    // �t���[����
    static float limit   = Action.afParam[3];    // ���E�l

    // �A���t�@�l����
    ImGui::DragFloat(u8"�����x", &alpha, 1, 0.0f, 256.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F�����x");
    Action.afParam[0] = alpha;

    // ����ݒ�
    ImGui::Combo(u8"����ݒ�", &nAction, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM1�F����ݒ�");
    Action.afParam[1] = nAction;

    // �t���[��
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1.0f, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F�t���[��");
    Action.afParam[2] = fFrame;

    // ���E�l
    ImGui::DragFloat(u8"���E�l", &limit, 1.0f, 0, 256.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F���E�l");
    Action.afParam[3] = limit;
}

//=============================================================================
//[ActionColor] �F�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionColor(CUI::ActionInfo & Action)
{
    // �ϐ���`
    static D3DXCOLOR col    = { Action.afParam[0] ,Action.afParam[1] ,Action.afParam[2],0.0f };           // �F
    static int nAction      = Action.afParam[3];                                                          // ����̎��
    static float fFrame     = Action.afParam[4];                                                          // �t���[����
    static D3DXCOLOR limit  = { Action.afParam[5] , Action.afParam[6] , Action.afParam[7] ,0.0f };        // ���E�l

    // �F�̐ݒ�
    ImGui::ColorEdit3(u8"�F�̐ݒ�", col);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�FR�̒l \n PARAM1�FG�̒l \n PARAM2�FB�̒l");
    Action.afParam[0] = col.r;    // r
    Action.afParam[1] = col.g;    // g
    Action.afParam[2] = col.b;    // b

    // ����ݒ�
    ImGui::Combo(u8"����ݒ�", &nAction, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F����ݒ�");
    Action.afParam[3] = nAction;

    // �t���[��
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1.0f, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM4�F�t���[��");
    Action.afParam[4] = fFrame;

    // �F���E�l
    ImGui::DragFloat3(u8"�F�̌��E�l", limit, 1.0f, 0.0f, 256.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM5�FR�̌��E�l \n PARAM6�FG�̌��E�l \n  PARAM7�FB�̌��E�l");
    Action.afParam[5] = limit.r;    // R���E�l
    Action.afParam[6] = limit.g;    // G���E�l
    Action.afParam[7] = limit.b;    // B���E�l
}

//=============================================================================
//[ActionRot] ��]�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionRot(CUI::ActionInfo & Action)
{
    // �ϐ���`
    static float rot     = Action.afParam[0];    // �p�x
    static int nAction   = Action.afParam[1];    // ����̎��
    static float fFrame  = Action.afParam[2];    // �t���[����
    static float limit   = Action.afParam[3];    // ���E�l

    // ��]���x
    ImGui::DragFloat(u8"��]���x", &rot, 1.0f, -180, 180.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F��]���x");
    Action.afParam[0] = rot;

    ImGui::Combo(u8"����ݒ�", &nAction, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM1�F����ݒ�");
    Action.afParam[1] = nAction;

    // �t���[����
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1.0f, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F�t���[��");
    Action.afParam[2] = fFrame;

    // ���E�l
    ImGui::DragFloat(u8"���E�l", &limit, 1.0f, 0, 256.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F���E�l");
    Action.afParam[3] = limit;
}

//=============================================================================
//[ActionTexBrend] �e�N�X�`���u�����h�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionTexBrend(CUI::ActionInfo & Action)
{
    // �ϐ���`
    static int ntexture     = Action.afParam[0];    // �e�N�X�`���ԍ�
    static int nBlend       = Action.afParam[1];    // ����̎��
    static float fFrame     = Action.afParam[2];    // �t���[����
    static float fInterval  = Action.afParam[3];    // �C���^�[�o��
    static bool isRight     = Action.afParam[4];    // �E���炩
    static int fDirection   = Action.afParam[5];    // ��������

    TextureCheck(ntexture);// �e�N�X�`�������݂��邩�`�F�b�N
    //�e�N�X�`���ԍ�
    ImGui::DragInt(u8"�e�N�X�`���ԍ�", &ntexture, 1, 0, CTexture::GetnNumTexture());
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F�e�N�X�`���ԍ�");

    TextureCheck(ntexture);// �e�N�X�`�������݂��邩�`�F�b�N
    Action.afParam[0] = ntexture;

    ImGui::Combo(u8"�������@", &nBlend, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM1�F�������@");
    Action.afParam[1] = nBlend;

    // �������܂ł̃t���[����
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1.0f, 0.0f, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F�������܂ł̃t���[����");
    Action.afParam[2] = fFrame;

    // �C���^�[�o���̃t���[����
    ImGui::DragFloat(u8"�C���^�[�o��", &fInterval, 1.0f, 0.0f, 100.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F�C���^�[�o��");
    Action.afParam[3] = fInterval;

    //�E���獶���ibool�j
    ImGui::Checkbox(u8"�E���痬��", &isRight);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM4�F�e�N�X�`�����E���痬�����ǂ���");
    Action.afParam[4] = isRight ? 1.0f : 0.0f;    // bool�l��float�^�ɕϊ�

    ImGui::Combo(u8"��������", &fDirection, u8"�c \0�� \0�E���オ�� \0�E��������");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM5�F�e�N�X�`���̗�������");
    Action.afParam[5] = fDirection;

    Action.afParam[6] = 1;   //1����3�ŌŒ�
}

//=============================================================================
//[ActionLoopAnim] ���[�v�A�j���̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionLoopAnim(CUI::ActionInfo & Action)
{
    static float fFrame     = Action.afParam[0];    // �t���[����
    static float fInterval  = Action.afParam[1];    // �C���^�[�o��
    static bool isRight     = Action.afParam[2];    // �E���炩
    static int fDirection   = Action.afParam[3];    // ��������

    // �������܂ł̃t���[����
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1.0f, 0.0f, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F�������܂ł̃t���[����");
    Action.afParam[0] = fFrame;

    // �C���^�[�o���̃t���[����
    ImGui::DragFloat(u8"�C���^�[�o��", &fInterval, 1.0f, 0.0f, 100.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM1�F�C���^�[�o��");
    Action.afParam[1] = fInterval;

    //�E���獶���ibool�j
    ImGui::Checkbox(u8"�E���痬��", &isRight);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F�e�N�X�`�����E���痬�����ǂ���");
    Action.afParam[2] = isRight ? 1.0f : 0.0f;    // bool�l��float�^�ɕϊ�

    ImGui::Combo(u8"��������", &fDirection, u8"�c \0�� \0�E���オ�� \0�E��������");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F�e�N�X�`���̗�������");
    Action.afParam[3] = fDirection;
}

//=============================================================================
//[ActionTexPlace] �e�N�X�`���̕`��ꏊ�w��̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionTexPlace(CUI::ActionInfo & Action)
{
    static float fDivision  = Action.afParam[0];    // ������
    static float fNum       = Action.afParam[1];    // �����牽�Ԗڂ�

    // ������
    ImGui::DragFloat(u8"������", &fDivision, 1, 0.0f, 10);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F������");
    Action.afParam[0] = fDivision;

    // �����牽�Ԗڂ�
    ImGui::DragFloat(u8"�ԍ�", &fNum, 1, 0.0f, 10.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM1�F�e�N�X�`���̔ԍ�(������)");
    Action.afParam[1] = fNum;
}

//=============================================================================
//[ActionEmitEffect] �G�t�F�N�g�̐ݒ�
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
void CEdit::ActionEmitEffect(CUI::ActionInfo & Action)
{
    // �ϐ���`
    static int ntexture     = Action.afParam[0];                          // �e�N�X�`���ԍ�
    static int nAction      = Action.afParam[1];                          // ����̎��
    static float fFrame     = Action.afParam[2];                          // �t���[����
    static D3DXVECTOR2 pos  = { Action.afParam[3],Action.afParam[4]};     // �����ʒu

    TextureCheck(ntexture);// �e�N�X�`�������݂��邩�`�F�b�N

    // �G�t�F�N�g�ԍ�
    //ImGui::Combo(u8"�e�N�X�`���ԍ�", &ntexture, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    ImGui::DragInt(u8"�e�N�X�`���ԍ�", &ntexture, 1, 0, CTexture::GetnNumTexture());
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM0�F�e�N�X�`���ԍ�");

    ntexture = TextureCheck(ntexture);// �e�N�X�`�������݂��邩�`�F�b�N
    Action.afParam[0] = ntexture;

    ImGui::Combo(u8"����ݒ�", &nAction, u8"������ \0�Z�t���[���܂� \0�Z�t���[������ \0�Z�l�܂� \0�t���[�����s�[�g \0�l���s�[�g \0(�Z�t���[������)�Z�l�ɑ����ɂ��� ");
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM1�F����ݒ�");
    Action.afParam[1] = nAction;

    // �t���[����
    ImGui::DragFloat(u8"�t���[��", &fFrame, 1.0f, 0.0f, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM2�F�t���[��");
    Action.afParam[2] = fFrame;

    //�����ʒuX�����炷�Z�l
    //�����ʒuY�����炷�Z�l
    ImGui::DragFloat2(u8"�����ʒu", pos, 1, -600, 1500.0f);
    if (ImGui::IsItemHovered())//�c�[���`�b�v
        ImGui::SetTooltip(u8"PARAM3�F�����ʒuX \n PARAM3�F�����ʒuY");
    Action.afParam[3] = pos.x;
    Action.afParam[4] = pos.y;
}


//=============================================================================
//[TextureCheck] �e�N�X�`���̃`�F�b�N
// ����
// nTextureNum : �e�N�X�`���ԍ�
//=============================================================================
int CEdit::TextureCheck(int nTextureNum)
{
    // �e�N�X�`���ւ̃|�C���^���擾
    CTexture* pTexture = CManager::GetTexture();
    // �����̔ԍ��̃e�N�X�`�������݂��邩�`�F�b�N
    if (pTexture->CTexture::GetInfo(nTextureNum) == nullptr)
    {
    // ���݂��Ȃ��ꍇ
        return 0;
    }
   
    return  nTextureNum;
}

//=============================================================================
//[TextureName] �e�N�X�`�����擾
// ����
// Action : �ݒ肵�����A�N�V����
//=============================================================================
//std::string CEdit::TextureName(void)
//{
//    CTexture* pTexture = CManager::GetTexture();
//    std::ostringstream oss;
//
//    // �e�N�X�`�������擾
//    for (int nCnt = 0; nCnt < CTexture::GetnNumTexture(); nCnt++)
//    {
//        std::string strName = pTexture->CTexture::GetInfo(nCnt);
//        oss << "\0";
//    }
//
//    return oss.str();
//}

