//=============================================================================
//
// GUIクラス [gui.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _GUI_H_
#define _GUI_H_

#include "main.h"
#include "imgui/imgui.h"
#include "ui.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;

//*****************************************************************************
// クラスの定義
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

    // 各フレーム
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
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);// 色
    HWND m_hwnd;
    int m_UINum;// 選択しているUIの番号
    OPENFILENAME ofn;// ファイルダイアログ構造体
};
#endif // !_UI_H_
