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

    void Manual(void);
    void information(void);

    void UIEdit(void);
private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);// �F
};
#endif // !_UI_H_
