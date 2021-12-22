//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 後藤慎之助
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// インクルードファイル
//========================
#include "game.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "input.h"
#include "scene.h"
#include "library.h"
#include "debug.h"
#include "pause.h"
#include "scene2d.h"
#include "camera.h"
#include "bg.h"
#include "wave.h"
#include "effect2d.h"
#include "effect3d.h"
#include "number_array.h"
#include "text.h"
#include "enemy.h"
#include "road.h"
#include "fortress.h"
#include "block.h"
#include "bullet.h"
#include "mapmanager.h"

//========================================
// マクロ定義
//========================================

// ゲーム状態の管理フレーム
#define BLOW_MOMENT_FRAME 180          // 一撃の瞬間フレーム数
#define FINISH_WAIT_FRAME 240          // 決着時に、待つフレーム数
#define CREATE_POS_Y_RATE 0.8f         // ボールの発生位置Yの割合
#define FADE_IN_TELOP 30               // テロップのフェードイン開始フレーム
#define FADE_OUT_TELOP 150             // テロップのフェードアウト開始フレーム
#define FADE_IN_FINISH_TELOP 90        // フィニッシュテロップのフェードイン開始フレーム

#define DISTANCE_INIT_VALUE 999999.9f  // 距離初期化値
#define DEFAULT_INIT_DISTANCE 2000.0f

#define MAP_FILENAME ("data/TXT/testdata.json")			// マップで使用するモデルデータのファイル

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CGame::m_bStopObjUpdate = false;

CPlayer *CGame::m_apPlayer[] = {};
CPause *CGame::m_pPause = NULL;
CEffect2D *CGame::m_pEffect2d_Nega = NULL;
CEffect2D *CGame::m_pEffect2d_Posi = NULL;

CGame::TYPE CGame::m_type = TYPE_TRAINING;
int CGame::m_nNumAllPlayer = 0;
bool CGame::m_bUseKeyboard = false;      // デバッグ時はここを変える
int CGame::m_anMemoryIdxPlayer[] = {};
CPlayer::AI_LEVEL CGame::m_aMemoryAILevel[] = {};
int CGame::m_anMemoryRole[] = {};
CGame::STATE CGame::m_state = STATE_ROUND_START;

CPlayer *CGame::m_pSpPlayer = NULL;
bool CGame::m_bCurrentSpShot = false;
CText *CGame::m_pSpText = NULL;

CFortress *CGame::m_pFortress = NULL;
int CGame::m_nCharacterIdx = 0;
CNumberArray *CGame::m_pScore = NULL;
int CGame::m_nScore = 0;

CGame::INFO_IN_RESULT CGame::m_aInfoInResult[] = {};
bool CGame::m_bWin = false;

//=============================================================================
// ゲームのコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CGame::CGame()
{
    m_bStopObjUpdate = false;
    m_bCurrentSpShot = false;
    m_pSpText = NULL;

    memset(m_apPlayer, 0, sizeof(m_apPlayer));
    m_pPause = NULL;
    m_pEffect2d_Nega = NULL;
    m_pEffect2d_Posi = NULL;
    m_pSpPlayer = NULL;

    // 静的メンバ変数を初期化（遷移時に毎回必要なものだけ）
    //m_type = TYPE_TRAINING;
    //m_nNumAllPlayer = 0;
    //m_nNumStock = 0;
    //m_bUseKeyboard = false;
    //memset(m_anMemoryIdxPlayer, 0, sizeof(m_anMemoryIdxPlayer));
    //memset(m_aMemoryAILevel, 0, sizeof(m_aMemoryAILevel));
    m_state = STATE_ROUND_START;

    m_nCntGameTime = 0;
    m_bFirestRound = true;

    m_pFortress = NULL;
    m_nCharacterIdx = 0;
    m_pScore = NULL;
    m_nScore = 0;

    memset(m_aInfoInResult, 0, sizeof(m_aInfoInResult));
    m_bWin = false;
}

//=============================================================================
// ゲームのデストラクタ
// Author : 後藤慎之助
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CGame::Init(void)
{
    // テキスト生成
    m_pSpText = CText::Create(D3DXVECTOR3(640.0f, 500.0f, 0.0f), 100,
        "なし", CText::ALIGN_CENTER, "Reggae One", TEXT_NOT_EXIST_COLOR);

    // 定義
    const float SPLIT_RATE_UNDER_3 = 0.5f;
    const float SPLIT_RATE_ABOVE_2 = 0.333f;

    // プレイヤーの生成
    D3DXVECTOR3 player1Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);
    D3DXVECTOR3 player2Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);
    D3DXVECTOR3 player3Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);
    D3DXVECTOR3 player4Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);

    if (m_type == TYPE_TRAINING)
    {
        //m_nNumAllPlayer = 1;                // トレーニングは1人固定
        //CBg::Create(84, DEFAULT_VECTOR);    // デバッグステージの床
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(0.0f, 0.0f, 3300.0f), D3DXVECTOR3(6500.0f, 500.0f, 500.0f), DEFAULT_VECTOR);  // ブロック生成
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(0.0f, 0.0f, -3300.0f), D3DXVECTOR3(6500.0f, 500.0f, 500.0f), DEFAULT_VECTOR);  // ブロック生成
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(3300.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 6500.0f), DEFAULT_VECTOR);  // ブロック生成
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(-3300.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 6500.0f), DEFAULT_VECTOR);  // ブロック生成

        //CBg::Create(66, D3DXVECTOR3(1000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(66, D3DXVECTOR3(-1000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(66, D3DXVECTOR3(3000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(66, D3DXVECTOR3(-3000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);

        //CBg::Create(67, D3DXVECTOR3(1000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(67, D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(67, D3DXVECTOR3(3000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(67, D3DXVECTOR3(-3000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);

        // ジェイソンファイルからマップを生成し、初期地点も取得する
        CMapManager *pMapManager = CManager::GetMapManager();
        pMapManager->CreateMapFromJson(MAP_FILENAME);
        D3DXVECTOR3 startPos = pMapManager->GetStartPos();
        player1Pos = startPos;
        player2Pos = startPos;
        player3Pos = startPos;
        player4Pos = startPos;
        m_pFortress = CFortress::Create(startPos); // 移動要塞生成（無敵状態）
        //m_pFortress->SetSpeed(0.0f);
    }
    else if (m_type == TYPE_ARENA)
    {
        m_pFortress = CFortress::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f)); // 移動要塞生成
        // 仮の道生成
        D3DXVECTOR3 roadPos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
        for (int nCnt = 0; nCnt < 20; nCnt++)
        {
            D3DXVECTOR3 rot = DEFAULT_VECTOR;
            roadPos.x += 1000.0f;
            rot = D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f);
            CRoad::Create(roadPos, rot);
        }

        // 仮の敵（最初の壁に至るまで）
        D3DXVECTOR3 enemyPos = D3DXVECTOR3(3000.0f, 0.0f, 1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_ARMY, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        enemyPos = D3DXVECTOR3(4000.0f, 0.0f, 1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_KAMIKAZE, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        enemyPos = D3DXVECTOR3(3000.0f, 0.0f, -1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_KAMIKAZE, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        enemyPos = D3DXVECTOR3(4000.0f, 0.0f, -1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_ARMY, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        //CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(7000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        //CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(7000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(10000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(10000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(10000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);

        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(15000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(15000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(15000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(17000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(17000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(17000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(14000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(14000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(14000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(16000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(16000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(16000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(19000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(20500.0f, 0.0f, 750.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(20500.0f, 0.0f, -750.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST, 3000.0f);

        // 仮のゴールゲート
        CBlock::Create(CBlock::TYPE_NORMAL_GATE, D3DXVECTOR3(12000.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 5000.0f, 5000.0f), MODEL_DIRECT_LEFT);
        CBlock::Create(CBlock::TYPE_GOAL_GATE, D3DXVECTOR3(22000.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 5000.0f, 5000.0f), MODEL_DIRECT_LEFT);
    }

    // ステージのモデルを生成
    //CBg::Create(34, DEFAULT_VECTOR);    // ステージ1は34

    // UIを生成
    CUI::Place(CUI::SET_GAME);

    // ポーズの生成
    m_pPause = CPause::Create();

    // プレイヤーの生成続き
    float fSplitXRate = 0.0f;
    switch (m_nNumAllPlayer)
    {
    case 1:
        fSplitXRate = SPLIT_RATE_UNDER_3;
        player1Pos.x *= -fSplitXRate;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        break;
    case 2:
        fSplitXRate = SPLIT_RATE_UNDER_3;
        player1Pos.x *= -fSplitXRate;
        player2Pos.x *= fSplitXRate;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        m_apPlayer[1] = CPlayer::CreateInGame(player2Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            1, m_anMemoryIdxPlayer[1], m_aMemoryAILevel[1], m_anMemoryRole[1]);
        break;
    case 3:
        fSplitXRate = SPLIT_RATE_ABOVE_2;
        player1Pos.x *= -fSplitXRate * 2.0f;
        player2Pos.x *= -fSplitXRate;
        player3Pos.x *= fSplitXRate;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        m_apPlayer[1] = CPlayer::CreateInGame(player2Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            1, m_anMemoryIdxPlayer[1], m_aMemoryAILevel[1], m_anMemoryRole[1]);
        m_apPlayer[2] = CPlayer::CreateInGame(player3Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            2, m_anMemoryIdxPlayer[2], m_aMemoryAILevel[2], m_anMemoryRole[2]);
        break;
    case 4:
        fSplitXRate = SPLIT_RATE_ABOVE_2;
        player1Pos.x *= -fSplitXRate * 2.0f;
        player2Pos.x *= -fSplitXRate;
        player3Pos.x *= fSplitXRate;
        player4Pos.x *= fSplitXRate * 2.0f;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        m_apPlayer[1] = CPlayer::CreateInGame(player2Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            1, m_anMemoryIdxPlayer[1], m_aMemoryAILevel[1], m_anMemoryRole[1]);
        m_apPlayer[2] = CPlayer::CreateInGame(player3Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            2, m_anMemoryIdxPlayer[2], m_aMemoryAILevel[2], m_anMemoryRole[2]);
        m_apPlayer[3] = CPlayer::CreateInGame(player4Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            3, m_anMemoryIdxPlayer[3], m_aMemoryAILevel[3], m_anMemoryRole[3]);
        break;
    }
    // カメラのロックオン場所を変える
    CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_GAME);

    // 反転合成用のエフェクトを生成
    m_pEffect2d_Nega = CEffect2D::Create(3, DEFAULT_VECTOR);
    m_pEffect2d_Nega->SetUseUpdate(false);
    m_pEffect2d_Posi = CEffect2D::Create(3, DEFAULT_VECTOR);
    m_pEffect2d_Posi->SetUseUpdate(false);

    // スコア表示を生成
    m_pScore = CNumberArray::Create(12, D3DXVECTOR3(640.0f, 675.0f, 0.0f), NUMBER_SIZE_X_BALL_SPD, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 0, false);

    // BGMをランダム再生
    int nRand = GetRandNum(2, 0);
    switch (nRand)
    {
    case 0:
        CManager::SoundPlay(CSound::LABEL_BGM_BATTLE00);
        break;
    case 1:
        CManager::SoundPlay(CSound::LABEL_BGM_BATTLE01);
        break;
    case 2:
        CManager::SoundPlay(CSound::LABEL_BGM_BATTLE02);
        break;
    }

    //// 仮の見た目確認用モデル生成
    //CDebug::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CDebug::TYPE_PERMANENT, 31);
    //CDebug::Create(D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CDebug::TYPE_PERMANENT, 0);

    //// 仮の敵配置
    //D3DXVECTOR3 enemyPos = D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
    //bool bNextParagraph = false;
    //for (int nCnt = 1; nCnt < 26; nCnt++)
    //{
    //    if (bNextParagraph)
    //    {
    //        enemyPos.x = -2000.0f;
    //        bNextParagraph = false;
    //    }

    //    CEnemy::Create(CEnemy::TYPE_SPIDER, enemyPos);

    //    if (nCnt % 5 == 0)
    //    {
    //        enemyPos.z += 1000.0f;
    //        bNextParagraph = true;
    //    }
    //    
    //    enemyPos.x += 1000.0f;
    //}
    //CEnemy::Create(CEnemy::TYPE_SPIDER, D3DXVECTOR3(-1000.0f, 1000.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_SPIDER, D3DXVECTOR3(0.0f, 0.0f, 1500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER);
    //CEnemy::Create(CEnemy::TYPE_SPIDER, D3DXVECTOR3(1000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS);
    //CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(2000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(2000.0f, 0.0f, 1000.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_CANNON, D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(2000.0f, 0.0f, 3000.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);

    //// 仮の道生成
    //D3DXVECTOR3 roadPos = D3DXVECTOR3(-1500.0f, 0.0f, -1500.0f);
    //for (int nCnt = 0; nCnt < 10; nCnt++)
    //{
    //    D3DXVECTOR3 rot = DEFAULT_VECTOR;
    //    if (nCnt < 5)
    //    {
    //        roadPos.z += 500.0f;
    //    }
    //    else
    //    {
    //        roadPos.x += 500.0f;
    //        rot = D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f);
    //    }
    //    CRoad::Create(roadPos, rot);
    //}
    
    //// 背景生成
    //CBg::Create(56, D3DXVECTOR3(0.0f, 0.0f, 3000.0f), CBg::COLOR_PHASE_G_UP);
    //CBg::Create(56, D3DXVECTOR3(-500.0f, 0.0f, 3000.0f), CBg::COLOR_PHASE_G_UP);
    //CBg::Create(56, D3DXVECTOR3(500.0f, 0.0f, 3000.0f), CBg::COLOR_PHASE_G_UP);

    //// ブロック生成
    //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(-500.0f, 0.0f, 3000.0f), D3DXVECTOR3(5000.0f, 500.0f, 500.0f), DEFAULT_VECTOR);
    //CBlock::Create(CBlock::TYPE_GOAL_GATE, D3DXVECTOR3(5000.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 5000.0f), MODEL_DIRECT_LEFT);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CGame::Uninit(void)
{
    // 全ての音を停止
    CManager::SoundStopAll();

    // ポーズを破棄
    if (m_pPause != NULL)
    {
        m_pPause->Uninit();
        delete m_pPause;
        m_pPause = NULL;
    }
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CGame::Update(void)
{
    // ゲーム状態の管理
    ManageState();

    // 反転合成の終了チェック
    if (m_pEffect2d_Nega && m_pEffect2d_Posi)
    {
        // ポジのほうが一定の大きさに達したら、どちらもサイズを戻す
        if (m_pEffect2d_Posi->GetSize().x >= SCREEN_WIDTH * 2)
        {
            m_pEffect2d_Nega->SetSize(DEFAULT_VECTOR);
            m_pEffect2d_Posi->SetSize(DEFAULT_VECTOR);
            m_pEffect2d_Nega->SetUseUpdate(false);
            m_pEffect2d_Posi->SetUseUpdate(false);
            m_pEffect2d_Nega->SetRotVertex(0.0f);     // 更新を止める代わりに、頂点はここで調整
            m_pEffect2d_Posi->SetRotVertex(0.0f);     // 更新を止める代わりに、頂点はここで調整
        }
    }

}

//=============================================================================
// ゲーム状態の管理
// Author : 後藤慎之助
//=============================================================================
void CGame::ManageState(void)
{
    switch (m_state)
    {
    case STATE_ROUND_START:
        // ラウンド開始
        RoundStart();
        break;

    case STATE_BUTTLE:
        // バトル中
        InButtle();
        break;

    case STATE_BLOW_MOMENT:
        // 一撃の瞬間
        BlowMoment();
        break;

    case STATE_FINISH:
        // 勝敗判定
        JudgmentFinish();
        break;

    case STATE_PAUSE_MENU:
        // ポーズの更新
        m_pPause->Update();
        break;
    }
}

//=============================================================================
// ラウンド開始処理
// Author : 後藤慎之助
//=============================================================================
void CGame::RoundStart(void)
{
    // リスポーン処理
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 生存していないなら
        if (!m_apPlayer[nCntPlayer]->GetDisp())
        {
            m_apPlayer[nCntPlayer]->Respawn();
        }

        // 毎ラウンドリセットするステータス
        m_apPlayer[nCntPlayer]->ResetStatusEveryRound();
    }

    // カウンタを加算
    m_nCntGameTime++;

    // 一定フレームで、バトル中に
    if (m_nCntGameTime >= 180)
    {
        // カウンタリセット
        m_nCntGameTime = 0;

        //// ミッションスタート表示
        //CUI::Create(UI_EXTEND_MISSION_POS, DEFAULT_VECTOR, DEFAULT_COLOR, CUI::TYPE_MISSION_START);

        // バトル中に
        m_state = STATE_BUTTLE;
    }
    else if (m_nCntGameTime == FADE_OUT_TELOP)
    {
        if (!m_bFirestRound)
        {
            // ネクストラウンド
            CUI *pTelopBg = CUI::GetAccessUI(4);
            CUI *pTelop = CUI::GetAccessUI(5);
            if (pTelopBg)
            {
                pTelopBg->SetActionLock(2, false);
            }
            if (pTelop)
            {
                pTelop->SetActionLock(2, false);
            }
        }
        else
        {
            // ファーストラウンドのフラグを切る
            m_bFirestRound = false;

            // バトルスタート
            CUI *pTelopBg = CUI::GetAccessUI(2);
            CUI *pTelop = CUI::GetAccessUI(3);
            if (pTelopBg)
            {
                pTelopBg->SetActionLock(2, false);
            }
            if (pTelop)
            {
                pTelop->SetActionLock(2, false);
            }
        }
    }
    else if (m_nCntGameTime == FADE_IN_TELOP)
    {
        if (!m_bFirestRound)
        {
            // ネクストラウンド
            CUI *pTelopBg = CUI::GetAccessUI(4);
            CUI *pTelop = CUI::GetAccessUI(5);
            if (pTelopBg)
            {
                pTelopBg->SetActionReset(0);
                pTelopBg->SetActionLock(0, false);
                pTelopBg->SetActionReset(2);
            }
            if (pTelop)
            {
                pTelop->SetActionReset(0);
                pTelop->SetActionLock(0, false);
                pTelop->SetActionReset(1);
                pTelop->SetActionLock(1, false);
                pTelop->SetActionReset(2);
            }
        }
        else
        {
            // バトルスタート
            CUI *pTelopBg = CUI::GetAccessUI(2);
            CUI *pTelop = CUI::GetAccessUI(3);
            if (pTelopBg)
            {
                pTelopBg->SetActionReset(0);
                pTelopBg->SetActionLock(0, false);
                pTelopBg->SetActionReset(2);
            }
            if (pTelop)
            {
                pTelop->SetActionReset(0);
                pTelop->SetActionLock(0, false);
                pTelop->SetActionReset(1);
                pTelop->SetActionLock(1, false);
                pTelop->SetActionReset(2);
            }
        }
    }
}

//=============================================================================
// バトル中
// Author : 後藤慎之助
//=============================================================================
void CGame::InButtle(void)
{
    switch (m_type)
    {
    case TYPE_TRAINING:
    {
        // 任意の敵を出現させるための位置
        D3DXVECTOR3 spawnPos = DEFAULT_VECTOR;
        const int SPAWN_RADIUS_MAX = 2750;
        const int SPAWN_RADIUS_MIN = 500;
        spawnPos.x = float(GetRandNum(SPAWN_RADIUS_MAX, SPAWN_RADIUS_MIN));
        spawnPos.z = float(GetRandNum(SPAWN_RADIUS_MAX, SPAWN_RADIUS_MIN));
        int nToggleX = GetRandNum(1, 0);
        if (nToggleX == 1)
        {
            spawnPos.x *= -1.0f;
        }
        int nToggleZ = GetRandNum(1, 0);
        if (nToggleZ == 1)
        {
            spawnPos.z *= -1.0f;
        }

        // キーボード操作
        CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
        if (pInputKeyboard->GetKeyboardTrigger(DIK_1))
        {
            CEnemy::Create(CEnemy::TYPE_ARMY, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_2))
        {
            CEnemy::Create(CEnemy::TYPE_KAMIKAZE, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_3))
        {
            CEnemy::Create(CEnemy::TYPE_CANNON, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_4))
        {
            CEnemy::Create(CEnemy::TYPE_COMMANDER, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_5))
        {
            CEnemy::Create(CEnemy::TYPE_SHINIGAMI, spawnPos);
        }
    }
        break;
    case TYPE_ARENA:
        //// アリーナモードで1人残ったら
        //if (m_nNumDefeatPlayer >= m_nNumAllPlayer - m_nNumDeathPlayer - 1)
        //{
        //    // その残った人を、1位にする
        //    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
        //    {
        //        if (m_apPlayer[nCntPlayer]->GetDisp())
        //        {
        //            m_anPlayerRank[CPlayer::RANK_1] = m_apPlayer[nCntPlayer]->GetIdxControlAndColor();
        //            m_anPlayerRankInThisRound[CPlayer::RANK_1] = m_apPlayer[nCntPlayer]->GetIdxControlAndColor();
        //        }
        //    }

        //    // 一撃の瞬間へ
        //    m_state = STATE_BLOW_MOMENT;

        //    // 更新を止めておく
        //    m_bStopObjUpdate = true;

        //    // 勝者と敗者の注視へ
        //    CManager::GetCamera()->SetState(CCamera::STATE_FINISH_EACH);

        //    // このフレームはポーズをさせないため、関数を抜ける
        //    return;
        //}
        break;
    }

    //================================================================================
    // ポーズ処理
    if (!m_bStopObjUpdate && !m_bCurrentSpShot)
    {
        const int NO_PAUSE_PLAYER = -1; // 誰もポーズを押していない

                                        // 変数宣言
        CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();  // キーボード
        CInputJoypad *pInputJoypad = CManager::GetInputJoypad();        // コントローラ
        int nNumPausePlayer = NO_PAUSE_PLAYER;  // ポーズを押したプレイヤー

                                                // スタートボタンを押した人を結びつける
        if (pInputJoypad->GetJoypadTrigger(PLAYER_1, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_1;
        }
        else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_2;
        }
        else if (pInputJoypad->GetJoypadTrigger(PLAYER_3, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_3;
        }
        else if (pInputJoypad->GetJoypadTrigger(PLAYER_4, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_4;
        }

        // ポーズするなら
        if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || nNumPausePlayer != NO_PAUSE_PLAYER)
        {
            // SE
            CManager::SoundPlay(CSound::LABEL_SE_OPEN_POSE);

            // キーボード操作でポーズする際は、1Pのコントローラを使う
            if (nNumPausePlayer == NO_PAUSE_PLAYER)
            {
                nNumPausePlayer = PLAYER_1;
            }

            // ポーズ状態にする
            m_state = STATE_PAUSE_MENU;
            m_pPause->SetPauseMenuSelect(nNumPausePlayer);
            m_bStopObjUpdate = true;

            // カメラも止める
            CManager::GetCamera()->SetState(CCamera::STATE_NONE);
        }
    }
    //================================================================================
}

//=============================================================================
// 一撃の瞬間
// Author : 後藤慎之助
//=============================================================================
void CGame::BlowMoment(void)
{
    // 背景と黒線を取得
    CUI *pBg = CUI::GetAccessUI(100);
    CUI *pLine = CUI::GetAccessUI(101);
    // 背景と黒線を見えるように
    if (pBg)
    {
        pBg->SetDisp(true);
    }
    if (pLine)
    {
        pLine->SetDisp(true);
    }

    // カウンタを加算
    m_nCntGameTime++;

    // 一定フレームで、勝敗判定
    if (m_nCntGameTime >= BLOW_MOMENT_FRAME)
    {
        // 背景と黒線を見えないように
        if (pBg)
        {
            pBg->SetDisp(false);
        }
        if (pLine)
        {
            pLine->SetDisp(false);
        }

        // カウンタをリセット
        m_nCntGameTime = 0;

        // カメラのロックオン場所をリセット
        CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_GAME);

        // 更新開始
        m_bStopObjUpdate = false;

        // 勝敗判定へ
        m_state = STATE_FINISH;

        // 一撃の瞬間時、念のためリセットするもの
        BlowMomentMakeSureReset();
    }
}

//=============================================================================
// 一撃の瞬間時、念のためリセットするもの
// Author : 後藤慎之助
//=============================================================================
void CGame::BlowMomentMakeSureReset(void)
{
    // 反転合成を、念のため止める（AIつよい同士で戦わせた際、反転合成が戻らないままゲームが進行したため）（←打ち始め1Fに当たったから?）
    if (m_pEffect2d_Nega && m_pEffect2d_Posi)
    {
        m_pEffect2d_Nega->SetSize(DEFAULT_VECTOR);
        m_pEffect2d_Posi->SetSize(DEFAULT_VECTOR);
        m_pEffect2d_Nega->SetUseUpdate(false);
        m_pEffect2d_Posi->SetUseUpdate(false);
        m_pEffect2d_Nega->SetRotVertex(0.0f);     // 更新を止める代わりに、頂点はここで調整
        m_pEffect2d_Posi->SetRotVertex(0.0f);     // 更新を止める代わりに、頂点はここで調整
    }

    // 現在必殺技を使っている状況を、念のためリセットする（必殺技を使った直後1Fに倒されると、ここのフラグが戻らなくなったため）
    m_bCurrentSpShot = false;
    if (m_pSpText)
    {
        m_pSpText->SetColor(TEXT_NOT_EXIST_COLOR);
    }
}

//=============================================================================
// 勝敗判定
// Author : 後藤慎之助
//=============================================================================
void CGame::JudgmentFinish(void)
{
    // カウンタを加算
    m_nCntGameTime++;

    // 一定フレームで、勝敗判定
    if (m_nCntGameTime >= FINISH_WAIT_FRAME)
    {
        // カウンタをリセット
        m_nCntGameTime = 0;

        // リザルト画面に渡すための情報を持っておく
        for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
        {
            m_aInfoInResult[nCntPlayer].nIdxControlAndColor = m_apPlayer[nCntPlayer]->GetIdxControlAndColor();
            m_aInfoInResult[nCntPlayer].nContributionPoint = m_apPlayer[nCntPlayer]->GetContributionPoint();
        }

        //// 死んだプレイヤーが全体のプレイヤー-1に達したら
        //if (m_nNumDeathPlayer >= m_nNumAllPlayer - 1)
        //{
            // リザルトに移行
            CFade::SetFade(CManager::MODE_RESULT);
        //}
        //else
        //{
        //    // やられたプレイヤー人数をリセット
        //    m_nNumDefeatPlayer = 0;

        //    // もう一度ラウンド開始へ
        //    m_state = STATE_ROUND_START;
        //}
    }
    else if (m_nCntGameTime == FADE_IN_FINISH_TELOP)
    {
        //// 死んだプレイヤーが全体のプレイヤー-1に達したら
        //if (m_nNumDeathPlayer >= m_nNumAllPlayer - 1)
        //{
        //    // SE
        //    CManager::SoundPlay(CSound::LABEL_SE_FINISH);

        //    // フィニッシュ
        //    CUI *pTelopBg = CUI::GetAccessUI(6);
        //    CUI *pTelop = CUI::GetAccessUI(7);
        //    if (pTelopBg)
        //    {
        //        pTelopBg->SetActionReset(0);
        //        pTelopBg->SetActionLock(0, false);
        //        pTelopBg->SetActionReset(2);
        //    }
        //    if (pTelop)
        //    {
        //        pTelop->SetActionReset(0);
        //        pTelop->SetActionLock(0, false);
        //        pTelop->SetActionReset(1);
        //        pTelop->SetActionLock(1, false);
        //        pTelop->SetActionReset(2);
        //    }
        //}
    }
}

//========================================
// 決着状態にするための関数
// Author : 後藤慎之助
//========================================
void CGame::SetFinish(bool bWin)
{
    m_bWin = bWin;
    m_state = STATE_FINISH;
}

//========================================
// 一番近いプレイヤーへの角度を求める
// Author : 後藤慎之助
//========================================
float CGame::GetAngleToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer)
{
    // 変数宣言
    float fAngle = 0.0f;                        // 返す角度
    float fFirstDistance = DISTANCE_INIT_VALUE; // 距離
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;     // 対象の位置

    // 対象の位置を、自分の正面へ一度決めておく
    targetPos = D3DXVECTOR3(myPos.x + DEFAULT_INIT_DISTANCE, 0.0f, myPos.z);

    // 距離が一番近いプレイヤーを決める（自分以外で）
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 自分以外で
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // 生存しているなら
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // 他のプレイヤーの位置
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // 距離を求める
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // 距離の比較と、対象の位置を更新
            if (fFirstDistance > fSecondDistance)
            {
                fFirstDistance = fSecondDistance;
                targetPos = otherPlayerPos;
            }
        }
    }

    // 角度を求める
    fAngle = atan2((targetPos.x - myPos.x), (targetPos.z - myPos.z));

    return fAngle;
}

//========================================
// 一番近いプレイヤーの位置を求める
// Author : 後藤慎之助
//========================================
D3DXVECTOR3 CGame::GetPosToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer)
{
    // 変数宣言
    float fFirstDistance = DISTANCE_INIT_VALUE; // 距離
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;     // 対象の位置

    // 対象の位置を、自分の正面へ一度決めておく
    targetPos = D3DXVECTOR3(myPos.x + DEFAULT_INIT_DISTANCE, 0.0f, myPos.z);

    // 距離が一番近いプレイヤーを決める（自分以外で）
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 自分以外で
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // 生存しているなら
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // 他のプレイヤーの位置
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // 距離を求める
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // 距離の比較と、対象の位置を更新
            if (fFirstDistance > fSecondDistance)
            {
                fFirstDistance = fSecondDistance;
                targetPos = otherPlayerPos;
            }
        }
    }

    return targetPos;
}

//========================================
// 一番近いプレイヤーとの距離とポインタを得る
// Author : 後藤慎之助
//========================================
CCharacter *CGame::GetDistanceAndPointerToClosestPlayer(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer)
{
    // 変数宣言
    CCharacter*pTarget = NULL;

    // 距離が一番近いプレイヤーを決める（自分以外で）
    fKeepDistance = DISTANCE_INIT_VALUE;
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 自分以外で
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // 生存しているなら
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // 他のプレイヤーの位置
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // 距離を求める
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // 距離の比較と、対象のポインタを更新
            if (fKeepDistance > fSecondDistance)
            {
                fKeepDistance = fSecondDistance;
                pTarget = (CCharacter*)m_apPlayer[nCntPlayer];
            }
        }
    }

    return pTarget;
}

//========================================
// 一番近いプレイヤーとの距離とポインタを得る_電池バージョン
// Author : 後藤慎之助
//========================================
CPlayer *CGame::GetDistanceAndPointerToClosestPlayer_Denti(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer)
{
    // 変数宣言
    CPlayer*pTarget = NULL;

    // 距離が一番近いプレイヤーを決める（自分以外で）
    fKeepDistance = DISTANCE_INIT_VALUE;
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 自分以外で
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // 生存しているかつ、チャージ量が最大でないなら
        if (m_apPlayer[nCntPlayer]->GetDisp() && m_apPlayer[nCntPlayer]->GetCurrentEnergy() < m_apPlayer[nCntPlayer]->GetCurrentEnergyMax())
        {
            // 他のプレイヤーの位置
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // 距離を求める
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // 距離の比較と、対象のポインタを更新
            if (fKeepDistance > fSecondDistance)
            {
                fKeepDistance = fSecondDistance;
                pTarget = m_apPlayer[nCntPlayer];
            }
        }
    }

    return pTarget;
}

//========================================
// 一番近いプレイヤーか移動要塞との距離とポインタを得る
// Author : 後藤慎之助
//========================================
CCharacter *CGame::GetDistanceAndPointerToClosestPlayerOrFortress(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer)
{
    // 変数宣言
    CCharacter*pTarget = NULL;

    // 距離が一番近いプレイヤーを決める（自分以外で）
    fKeepDistance = DISTANCE_INIT_VALUE;
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 自分以外で
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // 生存しているなら
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // 他のプレイヤーの位置
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // 距離を求める
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // 距離の比較と、対象のポインタを更新
            if (fKeepDistance > fSecondDistance)
            {
                fKeepDistance = fSecondDistance;
                pTarget = (CCharacter*)m_apPlayer[nCntPlayer];
            }
        }
    }

    // 距離が一番近いプレイヤーと移動要塞でどちらが近いか比べる
    D3DXVECTOR3 fortressPos = m_pFortress->GetPos();
    float fDistanceToFortress = sqrtf(
        powf((myPos.x - fortressPos.x), 2.0f) +
        powf((myPos.z - fortressPos.z), 2.0f));
    if (fKeepDistance > fDistanceToFortress)
    {
        fKeepDistance = fDistanceToFortress;
        pTarget = (CCharacter*)m_pFortress;
    }

    return pTarget;
}

//========================================
// 一番近い移動要塞との距離とポインタを得る
// Author : 後藤慎之助
//========================================
CCharacter *CGame::GetDistanceAndPointerToClosestFortress(D3DXVECTOR3 myPos, float &fKeepDistance)
{
    // 変数宣言
    CCharacter*pTarget = NULL;

    // 距離が一番近い移動要塞が近いか比べる
    fKeepDistance = DISTANCE_INIT_VALUE;

    // 生存していないなら、関数を抜ける
    if (!m_pFortress->GetDisp())
    {
        return NULL;
    }

    D3DXVECTOR3 fortressPos = m_pFortress->GetPos();
    float fDistanceToFortress = sqrtf(
        powf((myPos.x - fortressPos.x), 2.0f) +
        powf((myPos.z - fortressPos.z), 2.0f));
    if (fKeepDistance > fDistanceToFortress)
    {
        fKeepDistance = fDistanceToFortress;
        pTarget = (CCharacter*)m_pFortress;
    }

    return pTarget;
}

//========================================
// ボール発射ゲージの設定
// Author : 後藤慎之助
//========================================
void CGame::SetBallGauge(int nMax, int nNow)
{
    // UIを取得
    CUI *pBallGaugeR = CUI::GetAccessUI(0);
    CUI *pBallGaugeL = CUI::GetAccessUI(1);

    // 左右のゲージを設定
    if (pBallGaugeR)
    {
        pBallGaugeR->SetLeftToRightGauge((float)nMax, (float)nNow);
    }
    if (pBallGaugeL)
    {
        pBallGaugeL->SetRightToLeftGauge((float)nMax, (float)nNow);
    }
}

//=============================================================================
// マップ制限処理
// Author : 後藤慎之助
//=============================================================================
HIT_SURFACE CGame::MapLimit(D3DXVECTOR3 &pos, D3DXVECTOR3 posOld, D3DXVECTOR3 myCubeSize)
{
    HIT_SURFACE returnHitSurface = HIT_SURFACE_NONE;

    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
    {
        // 中身があるなら
        if (pScene)
        {
            // 次のシーンを記憶
            CScene*pNextScene = pScene->GetNextScene();

            // ブロックにキャスト
            CBlock *pBlock = (CBlock*)pScene;

            // マップ制限を反映
            HIT_SURFACE hitSurface = IsBlockCollisionXZ(pos, posOld, pBlock->GetPos(), myCubeSize, pBlock->GetCollisionSize());
            if (hitSurface != HIT_SURFACE_NONE)
            {
                returnHitSurface = hitSurface;
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
    }

    return returnHitSurface;
}

//========================================
// 一番近い敵の位置を求める
// Author : 後藤慎之助
//========================================
D3DXVECTOR3 CGame::GetPosToClosestEnemy(D3DXVECTOR3 myPos)
{
    // 変数宣言
    float fFirstDistance = DISTANCE_INIT_VALUE; // 距離
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;     // 対象の位置

    // 対象の位置を、自分の正面へ一度決めておく
    targetPos = D3DXVECTOR3(myPos.x + DEFAULT_INIT_DISTANCE, 0.0f, myPos.z);

    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
    {
        // 中身があるなら
        if (pScene)
        {
            // 次のシーンを記憶
            CScene*pNextScene = pScene->GetNextScene();

            // 敵にキャスト
            CEnemy *pEnemy = (CEnemy*)pScene;

            // 出現しているなら
            if (pEnemy->GetAppearState() == CEnemy::APPEAR_STATE_EXIST)
            {
                // 敵の位置
                D3DXVECTOR3 enemyPos = pEnemy->GetPos();

                // 距離を求める
                float fSecondDistance = sqrtf(
                    powf((myPos.x - enemyPos.x), 2.0f) +
                    powf((myPos.z - enemyPos.z), 2.0f));

                // 距離の比較と、対象の位置を更新
                if (fFirstDistance > fSecondDistance)
                {
                    fFirstDistance = fSecondDistance;
                    targetPos = enemyPos;
                }
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
    }

    return targetPos;
}

//========================================
// 一番近い敵の弾の距離を求める
// Author : 後藤慎之助
//========================================
float CGame::GetDistanceToClosestEnemyBullet(D3DXVECTOR3 myPos)
{
    // 変数宣言
    float fFirstDistance = DISTANCE_INIT_VALUE; // 距離

    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BULLET);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BULLET); nCntScene++)
    {
        // 中身があるなら
        if (pScene)
        {
            // 次のシーンを記憶
            CScene*pNextScene = pScene->GetNextScene();

            // 敵にキャスト
            CBullet *pBullet = (CBullet*)pScene;

            // 敵の弾なら
            if (pBullet->GetWhoShot() == CScene::OBJTYPE_ENEMY)
            {
                // 弾の位置
                D3DXVECTOR3 bulletPos = pBullet->GetPos();

                // 距離を求める
                float fSecondDistance = sqrtf(
                    powf((myPos.x - bulletPos.x), 2.0f) +
                    powf((myPos.z - bulletPos.z), 2.0f));

                // 距離の比較と、対象の位置を更新
                if (fFirstDistance > fSecondDistance)
                {
                    fFirstDistance = fSecondDistance;
                }
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
    }

    return fFirstDistance;
}

//========================================
// スコアを加算する処理
// Author : 後藤慎之助
//========================================
void CGame::AddScore(const int nScore)
{
    m_nScore += nScore;
    m_pScore->SetDispNumber(m_nScore);
}

//========================================
// プレイヤーが誰かしら存在しているか取得する
// Author : 後藤慎之助
//========================================
bool CGame::GetDispAnyPlayer(void)
{
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // 生存しているなら
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            return true;
        }
    }

    return false;
}