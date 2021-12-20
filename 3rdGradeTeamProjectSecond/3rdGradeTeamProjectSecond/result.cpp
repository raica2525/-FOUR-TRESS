//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 後藤慎之助
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
// マクロ定義
//========================================

//=============================================================================
// リザルトのコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CResult::CResult()
{

}

//=============================================================================
// リザルトのデストラクタ
// Author : 後藤慎之助
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CResult::Init(void)
{
    // UIを生成
    CUI::Place(CUI::SET_RESULT);

    // 貢献度を表示
    float fDigitY = 0.0f;
    for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
    {
        CGame::INFO_IN_RESULT infoInResult = CGame::GetInfoInResult(nCntPlayer);
        CNumberArray::Create(12, D3DXVECTOR3(640.0f, 175.0f + fDigitY, 0.0f), NUMBER_SIZE_X_RESULT_CONTRIBUTION, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), infoInResult.nContributionPoint, false);

        fDigitY += 100.0f;
    }

    //// プレイヤー生成
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

    // カメラのロックオン場所を変える
    CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_CUSTOM);

    // BGMを再生
    CManager::SoundPlay(CSound::LABEL_BGM_RESULT);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CResult::Uninit(void)
{
    // BGMを停止
    CManager::SoundStop(CSound::LABEL_BGM_RESULT);
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CResult::Update(void)
{
    // 変数宣言
    const float ANGLE_ADJUST = 90.0f;   // 時計でいう0が0度の時に合わせる（2Dポリゴンの頂点をZで指定しているから）
    const float POS_Y_ADJUST = 50.0f;
    const int RAND_X = 1380;
    const float BASE_ANGLE = 67.5f;
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    CEffectData::TYPE effectType = CEffectData::TYPE_KAMI;

    // 位置を決める
    pos.y = -POS_Y_ADJUST;
    pos.x = float(rand() % RAND_X);
    fAngle = D3DXToRadian(180.0f) + BASE_ANGLE - ANGLE_ADJUST;

    // 紙吹雪生成
    CEffect2D *pKami = CEffect2D::Create(effectType, pos, fAngle);
    float fRed = (float)GetRandNum(100, 0) / 100.0f;
    float fGreen = (float)GetRandNum(100, 0) / 100.0f;
    float fBlue = (float)GetRandNum(100, 0) / 100.0f;
    pKami->CEffect2D::SetCol(D3DXCOLOR(fRed, fGreen, fBlue, 1.0f));

    // エンター、または何かボタンを押したら
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
        // 仮にタイトル画面に移行
        CManager::SoundPlay(CSound::LABEL_SE_OK);
        CFade::SetFade(CManager::MODE_TITLE);
    }
}