//=============================================================================
//
// GUI�N���X [gui.h]
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
class CGUI
{
public:
    CGUI();
    ~CGUI();

    static CGUI* Create(HWND hWnd);

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

private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);// �F
    HWND m_hwnd;
    int m_UINum;// �I�����Ă���UI�̔ԍ�
    OPENFILENAME ofn;// �t�@�C���_�C�A���O�\����
};
#endif // !_UI_H_
