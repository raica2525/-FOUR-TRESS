//=============================================================================
//
// Ug [result.cpp]
// Author : ã¡TV
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "game.h"
#include "debug.h"
#include "camera.h"
#include "effect2d.h"
#include "effectData.h"
#include "number_array.h"

//========================================
// }Nè`
//========================================

//=============================================================================
// UgÌRXgN^
// Author : ã¡TV
//=============================================================================
CResult::CResult()
{

}

//=============================================================================
// UgÌfXgN^
// Author : ã¡TV
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ú»
// Author : ã¡TV
//=============================================================================
HRESULT CResult::Init(void)
{
    // UIð¶¬
    CUI::Place(CUI::SET_RESULT);

    // v£xð\¦
    float fDigitY = 0.0f;
    fDigitY -= 130.0f * (MAX_PLAYER - CGame::GetNumAllPlayer());

    for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
    {
        CGame::INFO_IN_RESULT infoInResult = CGame::GetInfoInResult(nCntPlayer);

        CUI *pBar = CUI::GetAccessUI(infoInResult.nIdxControlAndColor);
        if (pBar)
        {
            pBar->SetPosition(D3DXVECTOR3(640.0f, 600.0f + fDigitY, 0.0f));
        }

        CNumberArray::Create(12, D3DXVECTOR3(835.0f, 600.0f + fDigitY, 0.0f), NUMBER_SIZE_X_RESULT_CONTRIBUTION, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), infoInResult.nContributionPoint, false);

        fDigitY -= 130.0f;
    }

    //// vC[¶¬
    //for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
    //{
    //    switch (nCntPlayer)
    //    {
    //    case CPlayer::RANK_1:
    //        CPlayer::CreateInResult(D3DXVECTOR3(250.0f, 200.0f, -1200.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_1);
    //        break;
    //    case CPlayer::RANK_2:
    //        CPlayer::CreateInResult(D3DXVECTOR3(-640.0f, 100.0f, -600.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_2);
    //        break;
    //    case CPlayer::RANK_3:
    //        CPlayer::CreateInResult(D3DXVECTOR3(-325.0f, 25.0f, -310.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_3);
    //        break;
    //    case CPlayer::RANK_4:
    //        CPlayer::CreateInResult(D3DXVECTOR3(125.0f, -40.0f, -100.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_4);
    //        break;
    //    }
    //}

    // JÌbNIêðÏ¦é
    CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_CUSTOM);

    // BGMðÄ¶
    CManager::SoundPlay(CSound::LABEL_BGM_RESULT);

    return S_OK;
}

//=============================================================================
// I¹
// Author : ã¡TV
//=============================================================================
void CResult::Uninit(void)
{

}

//=============================================================================
// XV
// Author : ã¡TV
//=============================================================================
void CResult::Update(void)
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
        // LOæÊÉÚs
        CManager::SoundPlay(CSound::LABEL_SE_OK);
        CFade::SetFade(CManager::MODE_RANKING);
    }
}