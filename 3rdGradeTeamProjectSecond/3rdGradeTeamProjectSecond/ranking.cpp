//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 後藤慎之助
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
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// ランキングのコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// ランキングのデストラクタ
// Author : 後藤慎之助
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CRanking::Init(void)
{
    // UIを生成
    CUI::Place(CUI::SET_RANKING);

    // ランキングを生成
    CRanking2::Create(RANKING2_FIRST_POS, RANKING2_CREATE_SCORE_SIZE);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CRanking::Uninit(void)
{
    // BGMを停止
    CManager::SoundStop(CSound::LABEL_BGM_RESULT);
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CRanking::Update(void)
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
        // タイトル画面に移行
        CManager::SoundPlay(CSound::LABEL_SE_OK);
        CFade::SetFade(CManager::MODE_TITLE);
    }
}
