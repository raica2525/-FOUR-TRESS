//===============================================
//
// デバッグ周りの処理 (debug.cpp)
// Author : 後藤慎之助
//
//===============================================

//========================
// インクルードファイル
//========================
#include "debug.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "scene.h"
#include "game.h"
#include "modelData.h"
#include "player.h"
#include "effectData.h"
#include "custom.h"
#include "wave.h"

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CDebug::CDebug() :CScene3D(CScene::OBJTYPE_MODEL_EFFECT)
{
    m_nModelType = 0;
    m_nLife = 2;
    m_type = TYPE_PERMANENT;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CDebug::~CDebug()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CDebug::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CScene3D::Init(pos, size);

    SetScale(size);

    BindModelData(m_nModelType);   // 当たり判定可視化は1番

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CDebug::Uninit(void)
{
    CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CDebug::Update(void)
{
    CScene3D::Update();

    // 1Fずつ生成するモデルなら、その都度消す(あえて少し負荷をかけ、それ以上ゲームが重くならないように作る)
    if (m_type == TYPE_MOMENT)
    {
        m_nLife--;
    }

    if (m_nLife <= 0)
    {
        Uninit();
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CDebug::Draw(void)
{
    CScene3D::Draw();
}

//=============================================================================
// インスタンス生成処理
// Author : 後藤慎之助
//=============================================================================
void CDebug::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nModelType)
{
#ifdef _DEBUG
    if (!CManager::GetRenderer()->GetDispFont())
    {
        return;
    }
#endif

    CDebug *pDebug = NULL;
    pDebug = new CDebug;
    pDebug->m_type = type;
    pDebug->m_nModelType = nModelType;
    pDebug->Init(pos, size);
}

//=============================================================================
// UIのリロード
// Author : 後藤慎之助
//=============================================================================
#ifdef _DEBUG
void CDebug::ReloadUI(CUI::SET set)
{
    // リロードするUIを削除
    CScene::ReleaseReloadUI();

    // UIの再配置
    CUI::Place(set);
}

//=============================================================================
// 共通のデバッグコマンド
// Author : 後藤慎之助
//=============================================================================
void CDebug::CommonCommand(void)
{
    // キーボードを取得
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // F4キーはUI等のリロード
    if (pInputKeyboard->GetKeyboardTrigger(DIK_F4))
    {
        // どのUI等をリロードするか、現在のモードで決める
        CManager::MODE mode = CManager::GetMode();
        switch (mode)
        {
        case CManager::MODE_TITLE:
            ReloadUI(CUI::SET_TITLE);
            break;
        case CManager::MODE_CUSTOM:
            ReloadUI(CUI::SET_CUSTOM);
            break;
        case CManager::MODE_MANUAL:
            ReloadUI(CUI::SET_MANUAL);
            break;
        case CManager::MODE_RESULT:
            ReloadUI(CUI::SET_RESULT);
            break;
        case CManager::MODE_RANKING:
            ReloadUI(CUI::SET_RANKING);
            break;
        case CManager::MODE_GAME:
        {
            // UIのリロード
            ReloadUI(CUI::SET_GAME);

            // プレイヤーのパーツ設定をリロード
            CModelData* pModelData = CManager::GetModelData();
            pModelData->LoadPartsList();
            pModelData->LoadPartsRate();
            for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
            {
                CPlayer* pPlayer = CGame::GetPlayer(nCnt);
                if (pPlayer)
                {
                    pPlayer->LoadCustom();
                }
            }
            break;
        }
        }
        // エフェクトデータのリロード
        CEffectData* pEffectData = CManager::GetEffectData();
        pEffectData->Init();
    }

    // F8キーはデバッグ表記のONOFF
    if (pInputKeyboard->GetKeyboardTrigger(DIK_F8))
    {
        CRenderer::SwitchDispFont();
    }

    // F7キーはデバッグメニューに遷移
    if (pInputKeyboard->GetKeyboardTrigger(DIK_F7))
    {
        CFade::SetFade(CManager::MODE_DEBUG_MENU);
    }
}
#endif

//=============================================================================
// デバッグメニューのコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CDebugMenu::CDebugMenu()
{
    m_pUI_Cursor = NULL;
    m_nSelectCoolTime = 0;
    m_select = SELECT_TRAINING;
}

//=============================================================================
// デバッグメニューのデストラクタ
// Author : 後藤慎之助
//=============================================================================
CDebugMenu::~CDebugMenu()
{
}

//=============================================================================
// デバッグメニューの初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CDebugMenu::Init(void)
{
    m_pUI_Cursor = CUI::Create(19, DEFAULT_VECTOR, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 0, DEFAULT_COLOR);

    return S_OK;
}

//=============================================================================
// デバッグメニューの終了処理
// Author : 後藤慎之助
//=============================================================================
void CDebugMenu::Uninit(void)
{
}

//=============================================================================
// デバッグメニューの更新処理
// Author : 後藤慎之助
//=============================================================================
void CDebugMenu::Update(void)
{
    // 選択のクールタイムを数える
    if (m_nSelectCoolTime > 0)
    {
        m_nSelectCoolTime--;
    }

    // キーボードを取得
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // コントローラを取得
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

    // フェードしていないなら、選択可能
    if (CFade::GetFade() == CFade::FADE_NONE)
    {
        // Aが押された(決定)
        if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(PLAYER_1, XINPUT_GAMEPAD_A))
        {
            // 選んだモードに移行
            switch (m_select)
            {
            case SELECT_TRAINING:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_TRAINING, 1, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_TRAINING, 1);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                break;
            case SELECT_CUSTOMIZE:
                CFade::SetFade(CManager::MODE_CUSTOM);
                break;
            case SELECT_TITLE:
                CFade::SetFade(CManager::MODE_TITLE);
                break;
            case SELECT_ARENA_1:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_NONE);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                break;
            case SELECT_ARENA_2:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_1);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                break;
            case SELECT_ARENA_3:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_2);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                break;
            case SELECT_ARENA_4:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 2);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_3);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                break;
            case SELECT_ARENA_5:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 4, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 4);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_1);
                CGame::SetAILevel(PLAYER_3, CPlayer::AI_LEVEL_2);
                CGame::SetAILevel(PLAYER_4, CPlayer::AI_LEVEL_3);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                CGame::SetIdxPlayer(2, 2);
                CGame::SetIdxPlayer(3, 3);
                break;
            case SELECT_ARENA_6:
                CFade::SetFade(CManager::MODE_GAME);
                if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 4, true);
                }
                else
                {
                    CGame::SetNextGameInDebug(CGame::TYPE_ARENA, 4);
                }
                CGame::SetAILevel(PLAYER_1, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_2, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_3, CPlayer::AI_LEVEL_NONE);
                CGame::SetAILevel(PLAYER_4, CPlayer::AI_LEVEL_NONE);
                CGame::SetIdxPlayer(0, 0);
                CGame::SetIdxPlayer(1, 1);
                CGame::SetIdxPlayer(2, 2);
                CGame::SetIdxPlayer(3, 3);
                break;
            }
        }
        else
        {
            // 役割決定
            if (pInputKeyboard->GetKeyboardTrigger(DIK_1))
            {
                CGame::SetRole(PLAYER_1, CPlayer::ROLE_WARRIOR);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_2))
            {
                CGame::SetRole(PLAYER_1, CPlayer::ROLE_HUNTER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_3))
            {
                CGame::SetRole(PLAYER_1, CPlayer::ROLE_CARRIER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_4))
            {
                CGame::SetRole(PLAYER_1, CPlayer::ROLE_TANK);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_5))
            {
                CGame::SetRole(PLAYER_1, CPlayer::ROLE_HEALER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_Q))
            {
                CGame::SetRole(PLAYER_2, CPlayer::ROLE_WARRIOR);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_W))
            {
                CGame::SetRole(PLAYER_2, CPlayer::ROLE_HUNTER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_E))
            {
                CGame::SetRole(PLAYER_2, CPlayer::ROLE_CARRIER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_R))
            {
                CGame::SetRole(PLAYER_2, CPlayer::ROLE_TANK);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_T))
            {
                CGame::SetRole(PLAYER_2, CPlayer::ROLE_HEALER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_A))
            {
                CGame::SetRole(PLAYER_3, CPlayer::ROLE_WARRIOR);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_S))
            {
                CGame::SetRole(PLAYER_3, CPlayer::ROLE_HUNTER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_D))
            {
                CGame::SetRole(PLAYER_3, CPlayer::ROLE_CARRIER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_F))
            {
                CGame::SetRole(PLAYER_3, CPlayer::ROLE_TANK);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_G))
            {
                CGame::SetRole(PLAYER_3, CPlayer::ROLE_HEALER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_Z))
            {
                CGame::SetRole(PLAYER_4, CPlayer::ROLE_WARRIOR);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_X))
            {
                CGame::SetRole(PLAYER_4, CPlayer::ROLE_HUNTER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_C))
            {
                CGame::SetRole(PLAYER_4, CPlayer::ROLE_CARRIER);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_V))
            {
                CGame::SetRole(PLAYER_4, CPlayer::ROLE_TANK);
            }
            if (pInputKeyboard->GetKeyboardTrigger(DIK_B))
            {
                CGame::SetRole(PLAYER_4, CPlayer::ROLE_HEALER);
            }

            // 上移動
            if (pInputKeyboard->GetKeyboardTrigger(DIK_UP) || pInputJoypad->GetStickValue(PLAYER_1,CInputJoypad::LEFT).y > 0 && m_nSelectCoolTime <= 0)
            {
                // 上の選択肢に
                m_select--;

                // 一番上の選択肢なら、一番下へ
                if (m_select < SELECT_TRAINING)
                {
                    m_select = SELECT_MAX - 1;
                }

                // 選択のクールタイムを設定
                m_nSelectCoolTime = MENU_SELECT_COOL_TIME;
            }

            // 下移動
            if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWN) || pInputJoypad->GetStickValue(PLAYER_1, CInputJoypad::LEFT).y < 0 && m_nSelectCoolTime <= 0)
            {
                // 下の選択肢に
                m_select++;

                // 一番下の選択肢なら、一番上へ
                if (m_select >= SELECT_MAX)
                {
                    m_select = SELECT_TRAINING;
                }

                // 選択のクールタイムを設定
                m_nSelectCoolTime = MENU_SELECT_COOL_TIME;
            }
        }
    }

    // カーソルの位置を変える
    D3DXVECTOR3 pos = D3DXVECTOR3(190.0f, 209.5f, 0.0f);
    float fDigitPosY = 18.2f * m_select;
    pos.y += fDigitPosY;
    if (m_pUI_Cursor)
    {
        m_pUI_Cursor->SetPosition(pos);
    }
}
