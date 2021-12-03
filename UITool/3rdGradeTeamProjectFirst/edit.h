//=============================================================================
//
// �ҏW���[�h�N���X [edit.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _GUI_H_
#define _GUI_H_

#include "main.h"
#include "imgui/imgui.h"
#include "ui.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUI;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CEdit
{
   static CEdit* m_pInstance;
    CEdit();

public:

    ~CEdit();

    // �t���[����
    typedef enum
    {
        FREME_MANUAL = 0,
        FREME_INFO,
        FREME_OBJECT,
        FREME_SYSTEM,
        FREME_MAX
    }FREME;

    static CEdit* Create(HWND hWnd);

    void Init(HWND hWnd);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // �e�t���[��
    void Manual(void);
    void information(void);
    void UIEdit(void);
    void System(void);
    void SetAction(CUI* pUI);

    void ActionSize         (CUI::ActionInfo& Action);
    void ActionPos          (CUI::ActionInfo& Action);
    void ActionAlpha        (CUI::ActionInfo& Action);
    void ActionColor        (CUI::ActionInfo& Action);
    void ActionRot          (CUI::ActionInfo& Action);
    void ActionTexBrend     (CUI::ActionInfo& Action);
    void ActionLoopAnim     (CUI::ActionInfo& Action);
    void ActionTexPlace     (CUI::ActionInfo& Action);
    void ActionEmitEffect   (CUI::ActionInfo& Action);

    //std::string TextureName(void);// �e�N�X�`���̖��O
    int TextureCheck(int nTextureNum);// �e�N�X�`���̃`�F�b�N
    //char** ObjectList(void);         // UI�̐��擾

    //  Set�֐�
    void SetIsOpen(FREME freme, bool isOpen) { m_IsOpen[freme] = isOpen; }

    // Get�֐�
    static CEdit* GetInstance(void) { return m_pInstance; }
private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);// �F
    HWND m_hwnd;
    int m_UINum;// �I�����Ă���UI�̔ԍ�
    OPENFILENAME ofn;// �t�@�C���_�C�A���O�\����
    bool m_IsOpen[FREME_MAX];// �t���[�����J���Ă��邩
};
#endif // !_UI_H_
