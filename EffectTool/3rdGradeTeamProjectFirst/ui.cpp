//===============================================
//
// UI (ui.cpp)
// Author : ã¡TV
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// CN[ht@C
//========================
#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "input.h"
#include "title.h"
#include "character.h"
#include "texture.h"
//#include "player.h"

//=======================================
// ÃIoÏé¾
//=======================================

//========================================
// UIÌRXgN^
// Author : ã¡TV
//========================================
CUI::CUI() :CScene2D(OBJTYPE::OBJTYPE_UI)
{
    m_nTexType = 0;
    m_move = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
    m_action = CUI::ACTION_NONE;
    m_fAngle = 0.0f;
    m_bUse = true;
    m_bBlinking = false;
    m_nCntTime = 0;
    m_bFadeOut = false;
}

//========================================
// UIÌfXgN^
// Author : ã¡TV
//========================================
CUI::~CUI()
{

}

//========================================
// UIÌú»
// Author : ã¡TV
//========================================
HRESULT CUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ú»
    CScene2D::Init(pos, size);

    // eNX`ðèÄ
    BindTexture(m_nTexType);

    return S_OK;
}

//========================================
// UIÌI¹
// Author : ã¡TV
//========================================
void CUI::Uninit(void)
{
    // I¹
    CScene2D::Uninit();
}

//========================================
// UIÌXV
// Author : ã¡TV
//========================================
void CUI::Update(void)
{
    // Ïé¾
    D3DXVECTOR3 pos = GetPosition();                   // Êuðæ¾
    D3DXVECTOR3 size = GetSize();                      // TCYðæ¾
    int nPatternAnim = 0;                              // p^[AjÌJE^ðp·éÆ«

                                                       //L[{[hÌmÛµ½ðæ¾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // Rg[ðæ¾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    switch (m_action)
    {
    case ACTION_TITLE_LOGO:

        // ¬ê¿é
        pos.y += TITLE_LOGO_FLOW_DOWN_SPEED;

        // êèÌlÅ~ßÄ¨­
        if (pos.y >= TITLE_LOGO_TARGET_POS_Y)
        {
            pos.y = TITLE_LOGO_TARGET_POS_Y;
        }

        // G^[AÜ½ÍX^[g{^ðµ½ç
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // ^CgSð·®Éº·
            pos.y = TITLE_LOGO_TARGET_POS_Y;
        }

        break;

    case ACTION_TITLE_PRESS_ENTER:

        // ^CgÌÔðJEg
        m_nCntTime++;

        // ^CgÌÅåÔ
        if (m_nCntTime > TITLE_MAX_TIME)
        {
            m_nCntTime = TITLE_MAX_TIME;
        }

        // FðÏ¦é
        if (m_bFadeOut == true)
        {
            m_col.r -= PRESS_START_FADE_RATE;
            m_col.g -= PRESS_START_FADE_RATE;
            m_col.b -= PRESS_START_FADE_RATE;
        }
        else
        {
            m_col.r += PRESS_START_FADE_RATE;
            m_col.g += PRESS_START_FADE_RATE;
            m_col.b += PRESS_START_FADE_RATE;
        }
        if (m_col.r <= PRESS_START_FADE_OUT_MIN)
        {
            m_bFadeOut = false;
        }
        else if (m_col.r >= 1.0f)
        {
            m_bFadeOut = true;
        }

        // G^[AÜ½ÍX^[g{^ðµ½ç
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // êèÔoßÅ_ÅÂ\É
            if (m_nCntTime >= TITLE_NEXT_SCENE)
            {
                // _ÅÌtOðtrueÉ
                m_bBlinking = true;
            }
            // »êÈOÍAJE^ðJÚÂ\ÜÅêCÉißé
            else
            {
                m_nCntTime = TITLE_NEXT_SCENE;
            }
        }

        // _Å·éÈç
        if (m_bBlinking == true)
        {
            // JE^[ðißÄAp^[ðØèÖ¦é
            nPatternAnim = CountAnimation(2, 2);

            // Fð2p^[ÅØèÖ¦é
            if (nPatternAnim == 1)
            {
                m_col.r = PRESS_START_FADE_OUT_MIN;
                m_col.g = PRESS_START_FADE_OUT_MIN;
                m_col.b = PRESS_START_FADE_OUT_MIN;
            }
            else
            {
                m_col.r = 1.0f;
                m_col.g = 1.0f;
                m_col.b = 1.0f;
            }
        }

        break;
    }

    // Fð½f
    SetColor(m_col);

    // Êuð½f
    SetPosition(pos);

    // TCYð½f
    SetSize(size);

    // Q[WnÈOÍAÊíÌ¸_ÀW
    if (m_action != ACTION_GAUGE)
    {
        SetVertex();
    }

    // gptOªfalseÈçÁ·
    if (m_bUse == false)
    {
        Uninit();
    }
}

//========================================
// UIÌ`æ
// Author : ã¡TV
//========================================
void CUI::Draw(void)
{
    // `æ
    CScene2D::Draw();
}

//========================================
// UIÌì¬
// Author : ã¡TV
//========================================
CUI *CUI::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, ACTION action)
{
    CUI *pUI = NULL;

    // ðmÛ
    pUI = new CUI;

    // eNX`Ì^CvÍæÉÑÂ¯Ä¨­
    pUI->m_nTexType = nTexType;

    // ú»
    pUI->Init(pos, size);

    // oÏðÑÂ¯é
    pUI->m_col = col;
    pUI->m_action = action;

    return pUI;
}

//========================================
// UIÌÝu
// Author : ã¡TV
//========================================
void CUI::Place(SET set)
{
    // t@C|Cg
    FILE *pFile = NULL;

    // Ïé¾
    char cReadText[256];	             // ¶ÆµÄÇÝæèp
    char cHeadText[256];	             // ¶Ì»Êp
    char cDie[256];		                 // gíÈ¢¶
    int nNumType = 0;                    // ^CvÌio[
    D3DXVECTOR3 pos = DEFAULT_VECTOR;    // Êu
    D3DXVECTOR3 size = DEFAULT_VECTOR;   // å«³
    D3DXCOLOR col = DEFAULT_COLOR;       // F
    int nAction = 0;                     // ®«

    // t@CðJ­
    switch (set)
    {
    case SET_TITLE:
        pFile = fopen("data/TXT/ui_title.txt", "r");
        break;
    case SET_MANUAL:
        pFile = fopen("data/TXT/ui_manual.txt", "r");
        break;
    case SET_GAME:
        pFile = fopen("data/TXT/ui_game.txt", "r");
        break;
    case SET_RESULT:
        pFile = fopen("data/TXT/ui_result.txt", "r");
        break;
    }

    // J¯½ç
    if (pFile != NULL)
    {
        // SCRIPTÌ¶ª©Â©éÜÅ
        while (strcmp(cHeadText, "SCRIPT") != 0)
        {
            // eLXg©çcReadTextª¶ðó¯æé
            fgets(cReadText, sizeof(cReadText), pFile);

            // cReedTextðcHeadTextÉi[
            sscanf(cReadText, "%s", &cHeadText);
        }

        // cHeadTextªSCRIPTÌ
        if (strcmp(cHeadText, "SCRIPT") == 0)
        {
            // cHeadTextªEND_SCRIPTÉÈéÜÅ
            while (strcmp(cHeadText, "END_SCRIPT") != 0)
            {
                fgets(cReadText, sizeof(cReadText), pFile);
                sscanf(cReadText, "%s", &cHeadText);

                // cHeadTextªUISETÌ
                if (strcmp(cHeadText, "UISET") == 0)
                {
                    // cHeadTextªEND_UISETÉÈéÜÅ
                    while (strcmp(cHeadText, "END_UISET") != 0)
                    {
                        fgets(cReadText, sizeof(cReadText), pFile);
                        sscanf(cReadText, "%s", &cHeadText);

                        if (strcmp(cHeadText, "TYPE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nNumType);

                            // s³ÈlÍSÄftHgðÄÑo·
                            if (nNumType < 0 || nNumType >= MAX_TEXTURE)
                            {
                                nNumType = 0;
                            }
                        }
                        else if (strcmp(cHeadText, "POS") == 0)
                        {
                            sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &pos.x, &pos.y);
                        }
                        else if (strcmp(cHeadText, "SIZE") == 0)
                        {
                            sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &size.x, &size.y);
                        }
                        else if (strcmp(cHeadText, "COL") == 0)
                        {
                            sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie, &col.r, &col.g, &col.b, &col.a);
                        }
                        else if (strcmp(cHeadText, "ACTION") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nAction);

                            // s³ÈlÍSÄftHgðÄÑo·
                            if (nAction < ACTION_NONE || nAction >= ACTION_MAX)
                            {
                                nAction = ACTION_NONE;
                            }

                            // ¶¬
                            Create(nNumType, pos, size, col, (ACTION)nAction);
                        }
                    }
                }
            }
        }
        // t@CðÂ¶é
        fclose(pFile);
    }
    // J¯È©Á½ç
    else
    {
        printf("J¯êÜ¹ñÅµ½\n");
    }
}

//========================================
// gå·éUI
// Author : ã¡TV
//========================================
D3DXVECTOR3 CUI::Extend(D3DXVECTOR3 size)
{
    // Ïé¾
    D3DXVECTOR3 returnSize = size;  // Ô·TCY
    int nCnt = 0;                   // JE^

                                    // ¡TCYgå
    returnSize.x += UI_EXTEND_MISSION_EXTEND_RATE_X;

    // cTCYgå
    returnSize.y += UI_EXTEND_MISSION_EXTEND_RATE_Y;

    // ¡TCYÌ§À
    if (returnSize.x >= UI_EXTEND_MISSION_MAX_SIZE_X)
    {
        returnSize.x = UI_EXTEND_MISSION_MAX_SIZE_X;
    }

    // cTCYÌ§À
    if (returnSize.y >= UI_EXTEND_MISSION_MAX_SIZE_Y)
    {
        returnSize.y = UI_EXTEND_MISSION_MAX_SIZE_Y;
    }

    // Aj[VÌJE^ðpµÄAUIÌtF[hAEgÉÂÈ°é
    nCnt = CountAnimation(1, MAX_ANIM_COUNTER);

    // tF[hAEgðnßéJEgð´¦½çA¿lðº°Ä¢­
    if (nCnt >= UI_EXTEND_MISSION_FADE_OUT_COUNT)
    {
        m_col.a -= UI_EXTEND_MISSION_FADE_OUT_RATE;
    }

    // §¾xª0ðºñÁ½çAÁ·
    if (m_col.a <= 0.0f)
    {
        m_bUse = false;
    }

    return returnSize;
}