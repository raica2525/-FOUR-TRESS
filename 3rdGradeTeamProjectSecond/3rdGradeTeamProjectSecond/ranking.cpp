//=============================================================================
//
// LO [ranking.cpp]
// Author : ã¡TV
//
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "debug.h"
#include "effect2d.h"
#include "effectData.h"
#include "ranking2.h"

//=============================================================================
// ÃIoÏé¾
//=============================================================================

//=============================================================================
// LOÌRXgN^
// Author : ã¡TV
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// LOÌfXgN^
// Author : ã¡TV
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ú»
// Author : ã¡TV
//=============================================================================
HRESULT CRanking::Init(void)
{
    // UIð¶¬
    CUI::Place(CUI::SET_RANKING);

    // LOð¶¬
    CRanking2::Create(RANKING2_FIRST_POS, RANKING2_CREATE_SCORE_SIZE);

    return S_OK;
}

//=============================================================================
// I¹
// Author : ã¡TV
//=============================================================================
void CRanking::Uninit(void)
{
    // BGMðâ~
    CManager::SoundStop(CSound::LABEL_BGM_RESULT);
}

//=============================================================================
// XV
// Author : ã¡TV
//=============================================================================
void CRanking::Update(void)
{
    // Ïé¾
    const float ANGLE_ADJUST = 90.0f;   // vÅ¢¤0ª0xÌÉí¹éi2D|SÌ¸_ðZÅwèµÄ¢é©çj
    const float POS_Y_ADJUST = 50.0f;
    const int RAND_X = 1380;
    const float BASE_ANGLE = 67.5f;
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    CEffectData::TYPE effectType = CEffectData::TYPE_KAMI;

    // Êuðßé
    pos.y = -POS_Y_ADJUST;
    pos.x = float(rand() % RAND_X);
    fAngle = D3DXToRadian(180.0f) + BASE_ANGLE - ANGLE_ADJUST;

    // á¶¬
    CEffect2D *pKami = CEffect2D::Create(effectType, pos, fAngle);
    float fRed = (float)GetRandNum(100, 0) / 100.0f;
    float fGreen = (float)GetRandNum(100, 0) / 100.0f;
    float fBlue = (float)GetRandNum(100, 0) / 100.0f;
    pKami->CEffect2D::SetCol(D3DXCOLOR(fRed, fGreen, fBlue, 1.0f));

    // G^[AÜ½Í½©{^ðµ½ç
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

    bool bPressedAnyButtons = false;
    for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
    {
        if (pInputJoypad->GetJoypadTrigger(nCount, XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_Y | XINPUT_GAMEPAD_START, CInputJoypad::BEHAVIOR_OR))
        {
            bPressedAnyButtons = true;
            break;
        }
    }
    if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || bPressedAnyButtons)
    {
        // ^CgæÊÉÚs
        CManager::SoundPlay(CSound::LABEL_SE_OK);
        CFade::SetFade(CManager::MODE_TITLE);
    }
}
