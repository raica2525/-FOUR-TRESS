//=============================================================================
//
// 編集モードクラス [edit.h]
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
class CEdit
{
   static CEdit* m_pInstance;
    CEdit();

public:

    ~CEdit();

    // フレーム列挙
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

    //std::string TextureName(void);// テクスチャの名前
    int TextureCheck(int nTextureNum);// テクスチャのチェック
    //char** ObjectList(void);         // UIの数取得

    //  Set関数
    void SetIsOpen(FREME freme, bool isOpen) { m_IsOpen[freme] = isOpen; }

    // Get関数
    static CEdit* GetInstance(void) { return m_pInstance; }
private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);// 色
    HWND m_hwnd;
    int m_UINum;// 選択しているUIの番号
    OPENFILENAME ofn;// ファイルダイアログ構造体
    bool m_IsOpen[FREME_MAX];// フレームを開いているか
};
#endif // !_UI_H_
