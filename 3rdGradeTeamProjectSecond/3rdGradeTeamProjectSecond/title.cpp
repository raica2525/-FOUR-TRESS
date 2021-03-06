//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 後藤慎之助
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
#include "effect2d.h"

//=============================================================================
// タイトルのコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CTitle::CTitle()
{
    m_nCntTime = 0;
    m_bEmitWingEffect = true;
}

//=============================================================================
// タイトルのデストラクタ
// Author : 後藤慎之助
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CTitle::Init(void)
{
    // マウスカーソルの表示(念のため)
    ShowCursor(TRUE);

    // UIを生成
    CUI::Place(CUI::SET_TITLE);

    // BGMを再生
    CManager::SoundPlay(CSound::LABEL_BGM_TITLE);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CTitle::Uninit(void)
{
    // BGMを停止
    CManager::SoundStop(CSound::LABEL_BGM_TITLE);
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助 池田悠
//=============================================================================
void CTitle::Update(void)
{
    // 炎エフェクトを上下に発生(6回分でちょうどよくなった)
    for (int nCnt = 0; nCnt < 6; nCnt++)
    {
        EmitFire(FIRE_POS_UP);
        EmitFire(FIRE_POS_DOWN);
    }

    // タイトルの時間をカウント
    m_nCntTime++;

    // 一定時間経過で遷移可能に
    if (m_nCntTime >= TITLE_SHOW_TIME)
    {
        // カウンタストップ
        m_nCntTime = TITLE_SHOW_TIME;

        // 翼エフェクトを放出
        if (m_bEmitWingEffect)
        {
            //CManager::SoundPlay(CSound::LABEL_SE_WING);
            m_bEmitWingEffect = false;
            //CEffect2D::Emit(CEffectData::TYPE_RED_WING, D3DXVECTOR3(640.0f, 160.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f));
            //CEffect2D::Emit(CEffectData::TYPE_BLUE_WING, D3DXVECTOR3(640.0f, 160.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f));
        }

        // プレスボタンのUIを出現させる
        CUI *pPressButton = CUI::GetAccessUI(0);
        if (pPressButton)
        {
            pPressButton->SetActionLock(1, false);
        }

        // フェードしていないなら、遷移可能
        if (CFade::GetFade() == CFade::FADE_NONE)
        {
            //キーボードの確保したメモリを取得
            CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

            // コントローラを取得
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
            // エンター、または何かボタンを押したら
            if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || bPressedAnyButtons)
            {
                // 仮にカスタマイズ画面に移行
                CFade::SetFade(CManager::MODE_GAME);

                CManager::SoundPlay(CSound::LABEL_SE_KO);

                // 仮にベータ用のステージへ
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 4, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 4);
                }

                // 発表会バージョンは、全員プレイヤー
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_3, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_4, CPlayer::AI_LEVEL_NONE);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                CGame::SetIdxPlayer(2, 2);
                CGame::SetIdxPlayer(3, 3);

                // 役割はランダム
                CGame::SetRole(PLAYER_1, GetRandNum(CPlayer::ROLE_HEALER, CPlayer::ROLE_WARRIOR));
                CGame::SetRole(PLAYER_2, GetRandNum(CPlayer::ROLE_HEALER, CPlayer::ROLE_WARRIOR));
                CGame::SetRole(PLAYER_3, GetRandNum(CPlayer::ROLE_HEALER, CPlayer::ROLE_WARRIOR));
                CGame::SetRole(PLAYER_4, GetRandNum(CPlayer::ROLE_HEALER, CPlayer::ROLE_WARRIOR));

                // 誰か確定でウォーリアーにする
                int nRandPlayer = GetRandNum(PLAYER_4, PLAYER_1);
                CGame::SetRole(nRandPlayer, CPlayer::ROLE_WARRIOR);

                // プレスボタンを点滅させる
                if (pPressButton)
                {
                    // 色変えをリセットしてロックする
                    pPressButton->SetActionReset(0);
                    pPressButton->SetActionLock(0, true);

                    // 点滅をアンロック
                    pPressButton->SetActionLock(2, false);
                }
            }
        }
    }
}

//=============================================================================
// 画面の上か下に炎を出す処理
// Author : 後藤慎之助
//=============================================================================
void CTitle::EmitFire(FIRE_POS firePos)
{
    // 変数宣言
    const float ANGLE_ADJUST = 90.0f;   // 時計でいう0が0度の時に合わせる（2Dポリゴンの頂点をZで指定しているから）
    const float POS_Y_ADJUST = 50.0f;
    const int RAND_X = 1380;
    const float BASE_ANGLE = 67.5f;
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    //CEffectData::TYPE effectType = CEffectData::TYPE_TITLE_FIRE_RED;

    // 位置と向きと色を決める
    switch (firePos)
    {
    case FIRE_POS_UP:
        pos.y = -POS_Y_ADJUST;
        pos.x = float(rand() % RAND_X);
        fAngle = D3DXToRadian(180.0f) + BASE_ANGLE - ANGLE_ADJUST;
        //effectType = CEffectData::TYPE_TITLE_FIRE_BLUE;
        break;
    case FIRE_POS_DOWN:
        pos.y = SCREEN_HEIGHT + POS_Y_ADJUST;
        pos.x = float(rand() % RAND_X) - float(RAND_X - SCREEN_WIDTH);
        fAngle = BASE_ANGLE - ANGLE_ADJUST;
        //effectType = CEffectData::TYPE_TITLE_FIRE_RED;
        break;
    }

    // 炎生成
    //CEffect2D::Create(effectType, pos, fAngle);
}
