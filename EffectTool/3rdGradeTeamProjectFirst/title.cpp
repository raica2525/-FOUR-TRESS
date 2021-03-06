//=============================================================================
//
// ^Cg [title.cpp]
// Author : ã¡TV
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "game.h"
#include "debug.h"
//#include "effect.h"

//=============================================================================
// ^CgÌRXgN^
// Author : ã¡TV
//=============================================================================
CTitle::CTitle()
{
    m_nCntTime = 0;
    m_bNextScene = false;
}

//=============================================================================
// ^CgÌfXgN^
// Author : ã¡TV
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ú»
// Author : ã¡TV
//=============================================================================
HRESULT CTitle::Init(void)
{
    // }EXJ[\Ì\¦(OÌ½ß)
    ShowCursor(TRUE);

    // UIð¶¬
    CUI::Place(CUI::SET_TITLE);

    //// BGMðÄ¶
    //CSound *pSound = CManager::GetSound();
    //pSound->Play(CSound::LABEL_BGM_TITLE);

    return S_OK;
}

//=============================================================================
// I¹
// Author : ã¡TV
//=============================================================================
void CTitle::Uninit(void)
{
    //// BGMðâ~(¼)
    //CSound *pSound = CManager::GetSound();
    //pSound->Stop(CSound::LABEL_BGM_TITLE);
}

//=============================================================================
// XV
// Author : ã¡TV
//=============================================================================
void CTitle::Update(void)
{
    // ^CgÌÔðJEg
    m_nCntTime++;

    // ^CgÌÅåÔ
    if (m_nCntTime > TITLE_MAX_TIME)
    {
        m_nCntTime = TITLE_MAX_TIME;
    }

    //L[{[hÌmÛµ½ðæ¾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // Rg[ðæ¾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // JÚÌtOªtrueÈç
    if (m_bNextScene == true)
    {
        // G^[AÜ½ÍX^[g{^ðµ½ç
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // tF[hµÄ¢È¢Èç
            if (CFade::GetFade() == CFade::FADE_NONE)
            {
                //// è¹Ä¶
                //CSound *pSound = CManager::GetSound();
                //pSound->Play(CSound::LABEL_SE_SYSTEM_MODE_CHANGE);

                //// VÑû[hÉÚs
                //CFade::SetFade(CManager::MODE_MANUAL);

                // ¼ÉQ[[hÉÚs
                CFade::SetFade(CManager::MODE_GAME);
            }
        }
    }
    // JÚÌtOªfalseÈç
    else
    {
        // êèÔoßÅJÚÂ\É
        if (m_nCntTime >= TITLE_NEXT_SCENE)
        {
            m_bNextScene = true;
        }
        // êèÔoßµÄ¢È­Äà
        else
        {
            // G^[AÜ½ÍX^[g{^ðµ½ç
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
            {
                // JÚÂ\É
                m_bNextScene = true;
            }
        }
    }

#ifdef _DEBUG
    CDebug::TitleCommand();
#endif
}
