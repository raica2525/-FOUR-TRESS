//======================================================================================
//
// プレイヤー処理 (player.cpp)
// Author : 後藤慎之助、池田悠希（リザルトやカスタマイズのクリッピングマスク対応）
//
//======================================================================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "library.h"
#include "camera.h"
#include "character.h"
#include "debug.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "ai.h"
#include "wave.h"
#include "effect3d.h"
#include "ui.h"
#include "effect2d.h"
#include "number_array.h"
#include "text.h"
#include "cliping_musk.h"
#include "modelEffect.h"
#include "number_array.h"
#include "enemy.h"
#include "fortress.h"
#include "bullet.h"

//========================================
// マクロ定義
//========================================
#define CUSTOM_ATK_COLOR D3DXCOLOR(0.874f, 0.329f, 0.094f, 1.0f)
#define CUSTOM_DEF_COLOR D3DXCOLOR(0.203f, 0.768f, 0.196f, 1.0f)
#define CUSTOM_SPD_COLOR D3DXCOLOR(0.156f, 0.56f, 0.854f, 1.0f)
#define CUSTOM_WEI_COLOR D3DXCOLOR(1.0f, 0.501f, 0.0f, 1.0f)

// 最大量（昔のまま）
#define MAX_ATK 2250.0f
#define MAX_DEF 2000.0f
#define MAX_SPD 2700.0f
#define MAX_WEI 4100.0f

// 持ち運びエナジー量
#define CARRY_ENERGY_DEFAULT 50.0f
#define CARRY_ENERGY_CARRIER 80.0f 

// リスポーン時間
#define RESPAWN_FRAME 600

//=======================
// ウォーリアー
//=======================
#define WARRIOR_LIFE 500.0f
#define WARRIOR_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define WARRIOR_SPD 840.0f
#define WARRIOR_WEI 3060.0f

//=======================
// ハンター
//=======================
#define HUNTER_LIFE 290.0f
#define HUNTER_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define HUNTER_SPD 940.0f
#define HUNTER_WEI 3060.0f

//=======================
// キャリアー
//=======================
#define CARRIER_LIFE 370.0f
#define CARRIER_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define CARRIER_SPD 1040.0f
#define CARRIER_WEI 3060.0f

//=======================
// タンク
//=======================
#define TANK_LIFE 850.0f
#define TANK_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define TANK_COLLISION_SIZE_GUARD D3DXVECTOR2(500.0f, 450.0f)
#define TANK_SPD 740.0f
#define TANK_WEI 3360.0f
#define TANK_GUARD_WIDTH 180.0f
#define TANK_GUARD_DISTANCE 100.0f
#define TANK_GUARD_COLOR D3DXCOLOR(1.0f,0.933f,0.0f,1.0f)

//=======================
// ヒーラー
//=======================
#define HEALER_LIFE 350.0f
#define HEALER_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define HEALER_SPD 790.0f
#define HEALER_WEI 3060.0f

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CPlayer::CPlayer() :CCharacter(OBJTYPE::OBJTYPE_PLAYER)
{
    m_bMannequin = false;
    m_controlInput.bTiltedLeftStick = false;
    m_controlInput.fLeftStickAngle = 0.0f;
    m_controlInput.bTiltedRightStick = false;
    m_controlInput.fRightStickAngle = 0.0f;
    m_controlInput.fPlayerAngle = 0.0f;
    m_controlInput.bTriggerA = false;
    m_controlInput.bPressA = false;
    m_controlInput.bTriggerX = false;
    m_controlInput.bPressX = false;
    m_controlInput.bReleaseX = false;
    m_controlInput.bPressR2 = false;
    m_controlInput.bTriggerB = false;
    m_bUseKeyboard = false;
    m_AIlevel = AI_LEVEL_NONE;
    m_pAI = NULL;
    m_pUI_SP = NULL;
    m_pUI_Playable = NULL;
    m_pNumArray_SP = NULL;
    m_pUI_Custom_Atk = NULL;
    m_pUI_Custom_Def = NULL;
    m_pUI_Custom_Spd = NULL;
    m_pUI_Custom_Wei = NULL;
    m_pUI_Custom_Ability = NULL;
    m_pText_Custom_Ex_Head = NULL;
    m_pText_Custom_Ex_Up = NULL;
    m_pText_Custom_Ex_Down = NULL;
    m_pText_Custom_Ex_Wep = NULL;
    m_pText_Custom_Sp = NULL;
    m_bDispAbility = false;

    m_nIdxCreate = PLAYER_1;
    m_nIdxControlAndColor = PLAYER_1;

    m_exFlag = EX_FLAG_NONE;
    m_bGround = true;

    m_nCntLandingTime = 0;
    m_bGroundOld = true;

    memset(m_anNumCustomParts, 0, sizeof(m_anNumCustomParts));
    m_fAtk = 0.0f;
    m_fDef = 0.0f;
    m_fSpd = 0.0f;
    m_fWei = 0.0f;
    memset(m_afParam, 0, sizeof(m_afParam));
    m_nModelPosDefUp = 0;
    m_nModelPosDefDown = 0;

    m_nCntPressJump = 0;
    m_bUsedSecondJump = false;
    m_nCntStartGlide = 0;

    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    m_nCntAttackAnimTime = 0;

    m_spShot = SP_SHOT_HEAL;
    m_fCurrentEnergy = 0.0f;
    m_fCurrentEnergyMax = 0.0f;

    m_pClipingMusk = NULL;
    m_rank = RANK_1;
    m_hipPosOld = DEFAULT_VECTOR;

    m_nCntCurrentEnergyMaxTime = 0;
    m_voiceSet = VOICE_SET_ROBO;

    //===================================
    // 特殊能力対応周り
    //===================================

    //===================================    
    // Secondで追加したメンバ変数
    //===================================
    m_role = ROLE_WARRIOR;
    m_attackState = ATTACK_STATE_NONE;
    m_nCntStopTime = 0;
    m_nCntAttackTime = 0;
    m_fCurrentEnergy = 0.0f;
    m_waitMotion = ANIM_IDLE;
    m_walkMotion = ANIM_MOVE;
    m_bUsingGuard = false;
    m_nCntGuards = 0;
    m_pLightGuard = NULL;
    m_pHealingCircle = NULL;
    m_nCntRespawnTime = 0;
    m_nContributionPoint = 0;
    m_bGetOffFortressInThisFrame = false;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // パーツ数を設定
    CCharacter::SetPartNum(PARTS_MAX);

    // アニメーションを読み込む
    //CCharacter::LoadModelData("./data/ANIMATION/motion_player.txt");  // 座標・親子関係の読み込みと、アニメーションの読み込みを分けた
    //CCharacter::SetAnimFilePass("./data/ANIMATION/motion_player.txt");// 今回のゲームはカスタマイズしないため、LoadCustom内に移住

    // プレイアブルキャラの設定を読み込む
    LoadCustom();

    return S_OK;
}

//=============================================================================
// カスタマイズ読み込み処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::LoadCustom(void)
{
    // ファイルポインタ
    FILE *pFile = NULL;

    // パーツリストから情報取得
    CModelData *pModelData = CManager::GetModelData();

    // 変数宣言
    int nPartsListType = 0;                // パーツリスト内の種類
    int nExNumber = 0;                     // 特殊能力番号

                                           // 定義
    const int PARTS_LIST_HEAD = 0;         // パーツリスト_頭
    const int PARTS_LIST_UP = 1;           // パーツリスト_上半身
    const int PARTS_LIST_DOWN = 2;         // パーツリスト_下半身
    const int PARTS_LIST_WEP = 3;          // パーツリスト_武器

    // 反映させるメンバ変数を一回初期化
    m_fAtk = 0.0f;
    m_fDef = 0.0f;
    m_fSpd = 0.0f;
    m_fWei = 0.0f;
    m_exFlag = EX_FLAG_NONE;
    D3DXVECTOR2 collisionSizeDefence = D3DXVECTOR2(0.0f, 0.0f);
    //memset(m_afParam, 0, sizeof(m_afParam));

    //// カスタマイズデータのファイルを開く
    //switch (m_nIdxControlAndColor)
    //{
    //case PLAYER_1:
    //    pFile = fopen("data/TXT/custom1.txt", "r");
    //    break;
    //case PLAYER_2:
    //    pFile = fopen("data/TXT/custom2.txt", "r");
    //    break;
    //case PLAYER_3:
    //    pFile = fopen("data/TXT/custom3.txt", "r");
    //    break;
    //case PLAYER_4:
    //    pFile = fopen("data/TXT/custom4.txt", "r");
    //    break;
    //}

    //// 開けたら
    //if (pFile != NULL)
    //{
    //    for (int nCntPartsList = 0; nCntPartsList < MAX_PARTS; nCntPartsList++)
    //    {
    //        // 読み込み
    //        fscanf(pFile, "%d", &nPartsListType);

    //        // 基本4能力
    //        m_fAtk += pModelData->GetPartsList(nPartsListType)->fAtk * pModelData->GetPartsRate(nCntPartsList)->fAtkRate;
    //        m_fDef += pModelData->GetPartsList(nPartsListType)->fDef * pModelData->GetPartsRate(nCntPartsList)->fDefRate;
    //        m_fSpd += pModelData->GetPartsList(nPartsListType)->fSpd * pModelData->GetPartsRate(nCntPartsList)->fSpdRate;
    //        m_fWei += pModelData->GetPartsList(nPartsListType)->fWei * pModelData->GetPartsRate(nCntPartsList)->fWeiRate;

    //        // 特殊能力
    //        int customPartsExFlag = 0;  // カスタマイズ画面で使う、パーツ毎の特殊能力
    //        nExNumber = pModelData->GetPartsList(nPartsListType)->nEx0;
    //        BITON(m_exFlag, 0x001 << nExNumber);
    //        BITON(customPartsExFlag, 0x001 << nExNumber);
    //        nExNumber = pModelData->GetPartsList(nPartsListType)->nEx1;
    //        BITON(m_exFlag, 0x001 << nExNumber);
    //        BITON(customPartsExFlag, 0x001 << nExNumber);

    //        // 各パーツリストから、細部のパーツを決定
    //        if (nCntPartsList == PARTS_LIST_HEAD)
    //        {
    //            // カスタマイズ画面で特殊能力表示を更新
    //            if (m_pText_Custom_Ex_Head)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Head->SetText(cExName);
    //            }

    //            // モデルをバインド
    //            BindParts(PARTS_HEAD, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);

    //            // カスタマイズパーツ番号を取得
    //            m_anNumCustomParts[CUSTOM_PARTS_HEAD] = nPartsListType;

    //            // スイングの向きを、補助値から補助値へ
    //            m_afParam[PARAM_SWING_UP] = pModelData->GetPartsList(nPartsListType)->afParam[1];
    //            m_afParam[PARAM_SWING_DOWN] = pModelData->GetPartsList(nPartsListType)->afParam[2];
    //            m_afParam[PARAM_SMASH] = pModelData->GetPartsList(nPartsListType)->afParam[3];
    //            m_afParam[PARAM_SPIKE_RIGHT] = pModelData->GetPartsList(nPartsListType)->afParam[4];
    //            m_afParam[PARAM_SPIKE_LEFT] = pModelData->GetPartsList(nPartsListType)->afParam[5];

    //            // ボイスセットの番号を保持
    //            m_voiceSet = (int)pModelData->GetPartsList(nPartsListType)->afParam[6];

    //            // 防御当たり判定の更新
    //            if (collisionSizeDefence.x < pModelData->GetPartsList(nPartsListType)->fWidth)
    //            {
    //                collisionSizeDefence.x = pModelData->GetPartsList(nPartsListType)->fWidth;
    //            }
    //            collisionSizeDefence.y += pModelData->GetPartsList(nPartsListType)->fHeight;
    //        }
    //        else if (nCntPartsList == PARTS_LIST_UP)
    //        {
    //            // カスタマイズ画面で特殊能力表示を更新
    //            if (m_pText_Custom_Ex_Up)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Up->SetText(cExName);
    //            }

    //            // モデルをバインド
    //            BindParts(PARTS_BODY, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);
    //            BindParts(PARTS_RSHOULDER, (int)pModelData->GetPartsList(nPartsListType)->afParam[1]);
    //            BindParts(PARTS_RARM, (int)pModelData->GetPartsList(nPartsListType)->afParam[2]);
    //            BindParts(PARTS_RHAND, (int)pModelData->GetPartsList(nPartsListType)->afParam[3]);
    //            BindParts(PARTS_LSHOULDER, (int)pModelData->GetPartsList(nPartsListType)->afParam[4]);
    //            BindParts(PARTS_LARM, (int)pModelData->GetPartsList(nPartsListType)->afParam[5]);
    //            BindParts(PARTS_LHAND, (int)pModelData->GetPartsList(nPartsListType)->afParam[6]);

    //            // カスタマイズパーツ番号を取得
    //            m_anNumCustomParts[CUSTOM_PARTS_UP] = nPartsListType;

    //            // 上半身の初期位置データ
    //            m_nModelPosDefUp = (int)pModelData->GetPartsList(nPartsListType)->afParam[7];

    //            // 防御当たり判定の更新
    //            if (collisionSizeDefence.x < pModelData->GetPartsList(nPartsListType)->fWidth)
    //            {
    //                collisionSizeDefence.x = pModelData->GetPartsList(nPartsListType)->fWidth;
    //            }
    //            collisionSizeDefence.y += pModelData->GetPartsList(nPartsListType)->fHeight;
    //        }
    //        else if (nCntPartsList == PARTS_LIST_DOWN)
    //        {
    //            // カスタマイズ画面で特殊能力表示を更新
    //            if (m_pText_Custom_Ex_Down)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Down->SetText(cExName);
    //            }

    //            // モデルをバインド
    //            BindParts(PARTS_HIP, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);
    //            BindParts(PARTS_RTHIGH, (int)pModelData->GetPartsList(nPartsListType)->afParam[1]);
    //            BindParts(PARTS_RLEG, (int)pModelData->GetPartsList(nPartsListType)->afParam[2]);
    //            BindParts(PARTS_RFOOT, (int)pModelData->GetPartsList(nPartsListType)->afParam[3]);
    //            BindParts(PARTS_LTHIGH, (int)pModelData->GetPartsList(nPartsListType)->afParam[4]);
    //            BindParts(PARTS_LLEG, (int)pModelData->GetPartsList(nPartsListType)->afParam[5]);
    //            BindParts(PARTS_LFOOT, (int)pModelData->GetPartsList(nPartsListType)->afParam[6]);

    //            // カスタマイズパーツ番号を取得
    //            m_anNumCustomParts[CUSTOM_PARTS_DOWN] = nPartsListType;

    //            // 下半身の初期位置データ
    //            m_nModelPosDefDown = (int)pModelData->GetPartsList(nPartsListType)->afParam[7];

    //            // 防御当たり判定の更新
    //            if (collisionSizeDefence.x < pModelData->GetPartsList(nPartsListType)->fWidth)
    //            {
    //                collisionSizeDefence.x = pModelData->GetPartsList(nPartsListType)->fWidth;
    //            }
    //            collisionSizeDefence.y += pModelData->GetPartsList(nPartsListType)->fHeight;
    //        }
    //        else if (nCntPartsList == PARTS_LIST_WEP)
    //        {
    //            // カスタマイズ画面で特殊能力表示を更新
    //            if (m_pText_Custom_Ex_Wep)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Wep->SetText(cExName);
    //            }

    //            // モデルをバインド
    //            BindParts(PARTS_WEP, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);
    //            m_nNumWep = (int)pModelData->GetPartsList(nPartsListType)->afParam[0];

    //            // カスタマイズパーツ番号を取得
    //            m_anNumCustomParts[CUSTOM_PARTS_WEP] = nPartsListType;

    //            // 必殺技と、そのゲージ量
    //            m_spShot = (int)pModelData->GetPartsList(nPartsListType)->afParam[1];
    //            m_fSpGaugeMax = pModelData->GetPartsList(nPartsListType)->afParam[2];

    //            // 必殺技の補助値を補助値へ
    //            m_afParam[PARAM_5_WEAPON_SP] = pModelData->GetPartsList(nPartsListType)->afParam[5];
    //            m_afParam[PARAM_6_WEAPON_SP] = pModelData->GetPartsList(nPartsListType)->afParam[6];
    //            m_afParam[PARAM_7_WEAPON_SP] = pModelData->GetPartsList(nPartsListType)->afParam[7];
    //        }
    //    }
    //    // ファイルを閉じる
    //    fclose(pFile);
    //}

    // カスタマイズ画面で必殺技表示を更新
    if (m_pText_Custom_Sp)
    {
        char cSpName[256];
        CustomSpName(cSpName);
        m_pText_Custom_Sp->SetText(cSpName);
    }

    // 適当な設定
    m_spShot = 1;

    // 最大持ち運びエナジー量
    switch (m_role)
    {
    case ROLE_CARRIER:
        m_fCurrentEnergyMax = CARRY_ENERGY_CARRIER;
        break;
    default:
        m_fCurrentEnergyMax = CARRY_ENERGY_DEFAULT;
        break;
    }

    // 共通の設定
    BindParts(PARTS_BODY, 3);
    BindParts(PARTS_RSHOULDER, 5);
    BindParts(PARTS_RARM, 6);
    BindParts(PARTS_RHAND, 7);
    BindParts(PARTS_LSHOULDER, 8);
    BindParts(PARTS_LARM, 9);
    BindParts(PARTS_LHAND, 10);
    BindParts(PARTS_HIP, 2);
    BindParts(PARTS_RTHIGH, 11);
    BindParts(PARTS_RLEG, 12);
    BindParts(PARTS_RFOOT, 13);
    BindParts(PARTS_LTHIGH, 14);
    BindParts(PARTS_LLEG, 15);
    BindParts(PARTS_LFOOT, 16);

    // 各役職で異なる設定
    float fLife = 1.0f;
    switch (m_role)
    {
    case ROLE_WARRIOR:
        BindParts(PARTS_HEAD, 4);
        BindParts(PARTS_WEP, 17);
        fLife = WARRIOR_LIFE;
        collisionSizeDefence = WARRIOR_COLLISION_SIZE;
        m_fSpd = WARRIOR_SPD;
        m_fWei = WARRIOR_WEI;
        break;
    case ROLE_HUNTER:
        BindParts(PARTS_HEAD, 18);
        BindParts(PARTS_WEP, 19);
        fLife = HUNTER_LIFE;
        collisionSizeDefence = HUNTER_COLLISION_SIZE;
        m_fSpd = HUNTER_SPD;
        m_fWei = HUNTER_WEI;
        break;
    case ROLE_CARRIER:
        BindParts(PARTS_HEAD, 20);
        BindParts(PARTS_WEP, 50);
        BindParts(PARTS_RHAND, 21);
        BindParts(PARTS_LHAND, 22);
        BindParts(PARTS_RFOOT, 23);
        BindParts(PARTS_LFOOT, 24);
        fLife = CARRIER_LIFE;
        collisionSizeDefence = CARRIER_COLLISION_SIZE;
        m_fSpd = CARRIER_SPD;
        m_fWei = CARRIER_WEI;
        m_waitMotion = ANIM_CARRIER_IDLE;
        m_walkMotion = ANIM_CARRIER_DUSH;
        break;
    case ROLE_TANK:
        BindParts(PARTS_HEAD, 25);
        BindParts(PARTS_WEP, 26);
        fLife = TANK_LIFE;
        collisionSizeDefence = TANK_COLLISION_SIZE;
        m_fSpd = TANK_SPD;
        m_fWei = TANK_WEI;
        m_afParam[0] = TANK_GUARD_WIDTH;
        break;
    case ROLE_HEALER:
        BindParts(PARTS_HEAD, 28);
        BindParts(PARTS_WEP, 29);
        fLife = HEALER_LIFE;
        collisionSizeDefence = HEALER_COLLISION_SIZE;
        m_fSpd = HEALER_SPD;
        m_fWei = HEALER_WEI;
        break;
    }
    SetUpLife(fLife);

    // キャラクターに反映
    CCharacter::SetCollisionSizeDefence(collisionSizeDefence);
    CCharacter::LoadModelData("./data/ANIMATION/motion_player.txt");
    CCharacter::Init(CCharacter::GetPos(), DEFAULT_SCALE);
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Uninit(void)
{
    // AI情報をメモリ開放
    if (m_pAI != NULL)
    {
        // メモリ開放
        delete m_pAI;
        m_pAI = NULL;
    }

    // クリッピングの情報を開放
    if (m_pClipingMusk != NULL)
    {
        m_pClipingMusk->Uninit();
        delete m_pClipingMusk;
        m_pClipingMusk = NULL;
    }

    CCharacter::Uninit();
}

//=============================================================================
// 入力処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Input(void)
{
    // コントローラorキーボード操作（1Pの場合、Enterで遷移したならキーボード操作に変える）
    if (m_bUseKeyboard)
    {
        // キーボードを取得
        CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

        // ボタン情報を取得
        m_controlInput.bTriggerA = pInputKeyboard->GetKeyboardTrigger(DIK_SPACE);
        m_controlInput.bPressA = pInputKeyboard->GetKeyboardPress(DIK_SPACE);
        m_controlInput.bTriggerX = pInputKeyboard->GetKeyboardTrigger(DIK_RETURN);
        m_controlInput.bPressX = pInputKeyboard->GetKeyboardPress(DIK_RETURN);
        m_controlInput.bReleaseX = pInputKeyboard->GetKeyboardRelease(DIK_RETURN);
        m_controlInput.bPressR2 = pInputKeyboard->GetKeyboardPress(DIK_UP);
        m_controlInput.bTriggerB = pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT);

        // 左スティックが傾いているかどうか
        if (pInputKeyboard->GetKeyboardPress(DIK_W) ||
            pInputKeyboard->GetKeyboardPress(DIK_A) ||
            pInputKeyboard->GetKeyboardPress(DIK_S) ||
            pInputKeyboard->GetKeyboardPress(DIK_D))
        {
            m_controlInput.bTiltedLeftStick = true;

            // 角度を求める
            if (pInputKeyboard->GetKeyboardPress(DIK_A))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(-45.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(135.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_S))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(-135.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(45.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_D))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(-90.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(90.0f);
                }
            }
            else if (pInputKeyboard->GetKeyboardPress(DIK_D))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(45.0f);
                    m_controlInput.fPlayerAngle = -D3DXToRadian(135.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_S))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(135.0f);
                    m_controlInput.fPlayerAngle = -D3DXToRadian(45.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_A))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(90.0f);
                    m_controlInput.fPlayerAngle = -D3DXToRadian(90.0f);
                }
            }
            else if (pInputKeyboard->GetKeyboardPress(DIK_W))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_S))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(0.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(180.0f);
                }
            }
            else if (pInputKeyboard->GetKeyboardPress(DIK_S))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(180.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(0.0f);
                }
            }
        }
        else
        {
            m_controlInput.bTiltedLeftStick = false;
        }
    }
    else
    {
        // コントローラを取得
        CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

        // ボタン情報を取得
        m_controlInput.bTriggerA = pInputJoypad->GetJoypadTrigger(m_nIdxControlAndColor, XINPUT_GAMEPAD_A);
        m_controlInput.bPressA = pInputJoypad->GetButtonState(m_nIdxControlAndColor, XINPUT_GAMEPAD_A);
        m_controlInput.bTriggerX = pInputJoypad->GetJoypadTrigger(m_nIdxControlAndColor, XINPUT_GAMEPAD_X);
        m_controlInput.bPressX = pInputJoypad->GetButtonState(m_nIdxControlAndColor, XINPUT_GAMEPAD_X);
        m_controlInput.bReleaseX = pInputJoypad->GetJoypadRelease(m_nIdxControlAndColor, XINPUT_GAMEPAD_X);
        m_controlInput.bPressR2 = pInputJoypad->GetTriggerState(m_nIdxControlAndColor, CInputJoypad::RIGHT);
        m_controlInput.bTriggerB = pInputJoypad->GetJoypadTrigger(m_nIdxControlAndColor, XINPUT_GAMEPAD_B);

		D3DXVECTOR2 stickValue[CInputJoypad::LR_MAX];
		for (int nCount = 0; nCount < CInputJoypad::LR_MAX; nCount++)
		{
			stickValue[nCount] = pInputJoypad->GetStickValue(m_nIdxControlAndColor, (CInputJoypad::LR)nCount);
		}

        // 左スティックが傾いているかどうか
        if (stickValue[CInputJoypad::LEFT].x || stickValue[CInputJoypad::LEFT].y)
        {
            m_controlInput.bTiltedLeftStick = true;

            // 角度を求める
			m_controlInput.fLeftStickAngle = atan2f(stickValue[CInputJoypad::LEFT].x, stickValue[CInputJoypad::LEFT].y);
			m_controlInput.fPlayerAngle = atan2f(stickValue[CInputJoypad::LEFT].x*-1, stickValue[CInputJoypad::LEFT].y * -1);
        }
        else
        {
            m_controlInput.bTiltedLeftStick = false;
        }

        // 右スティックが傾いているかどうか
        if (stickValue[CInputJoypad::RIGHT].x || stickValue[CInputJoypad::RIGHT].y)
        {
            m_controlInput.bTiltedRightStick = true;

            // 角度を求める
            m_controlInput.fRightStickAngle = atan2(stickValue[CInputJoypad::RIGHT].x, stickValue[CInputJoypad::RIGHT].y);
        }
        else
        {
            m_controlInput.bTiltedRightStick = false;
        }
    }
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Update(void)
{
    // ゴリ押し
    m_bGetOffFortressInThisFrame = false;

    // 1F前の腰の位置を記憶
    m_hipPosOld = GetPartsPos(PARTS_HIP);

    // ダメージによって攻撃をリセットするフラグが立っているなら
    if (GetResetAttackByDamage())
    {
        m_nCntGuards = 0;   // 攻撃を受けた時のみ、タンクのガード回数はリセットされる
        ResetAttack();
        SetResetAttackByDamage(false);
        if (GetLife() <= 0.0f)
        {
            m_nCntStopTime = PLAYER_DEATH_STOP_FRAME;
        }
    }

    // 負傷していないor起き上がり中は、無敵
    DAMAGE_STATE damageState = GetDamageState();
    if (damageState == DAMAGE_STATE_NONE || damageState == DAMAGE_STATE_STAND_UP && GetTakeDamageTime() <= PLAYER_TAKE_DAMAGE_STAND_UP_INVINCIBLE_FRAME)
    {
        SetInvincible(false);
    }
    else
    {
        SetInvincible(true);
    }

    // マネキンモードでないなら
    if (!m_bMannequin)
    {
        // 表示しているなら
        if (GetDisp())
        {
            // AIでないなら
            if (!m_pAI)
            {
                // 入力処理
                Input();
            }
            else
            {
                // AI更新処理
                m_pAI->Update();
            }

            // 硬直していないなら
            if (m_nCntStopTime <= 0)
            {
                // 負傷時間があるなら、カウンタを下げる
                CntDownTakeDamageTime();

                // 攻撃のクールタイム
                if (m_nCntAttackTime > 0)
                {
                    // 攻撃中はカウントダウン
                    m_nCntAttackTime--;

                    // 攻撃終了時にメンバ変数を戻す
                    if (m_nCntAttackTime == 0)
                    {
                        ResetAttack();
                    }
                }

                // アタックアニメーションカウンタ
                if (m_nCntAttackAnimTime > 0)
                {
                    // カウントダウン
                    m_nCntAttackAnimTime--;
                }

                // 着地しているなら、色々フラグをリセット
                if (m_bGround)
                {
                    ResetOnGround();
                }

                // 行動
                float fSpeed = PLAYER_BASE_MINIMUM_SPEED + (m_fSpd * PLAYER_ADD_BASE_SPEED_RATE); // 最低保証の速度に、パラメータ分を足す
                Movement(fSpeed);

                // アニメーションさせる
                CCharacter::Update();
            }
            else
            {
                // 硬直時間をカウント
                m_nCntStopTime--;
            }
        }
        else
        {
            // やられた時の挙動
            DeadMove();
        }

        // ゲームUIの更新
        UpdateGameUI();
    }
    else
    {
        // マネキンモードの更新
        UpdateMannequin();
    }

    // 吹っ飛ばされエフェクトは、画面内で吹っ飛ばされているなら出す
    if (GetDamageState() == DAMAGE_STATE_BLOWN)
    {
        if (m_nCntStopTime <= 0)
        {
            D3DXVECTOR3 hipPos = GetPartsPos(PARTS_HIP);
            if (hipPos.y > -500.0f) // 画面外対応
            {
                //CEffect3D::Emit(CEffectData::TYPE_BLOWN, hipPos, m_hipPosOld);
            }
        }
    }

    // 体力が0になったら
    if (GetLife() <= 0.0f && GetDisp())
    {
        // KO音（各自の処理は、各自のクラス内で書く）
        CManager::SoundPlay(CSound::LABEL_SE_KO);

        m_fCurrentEnergy = 0.0f;
        SetDisp(false);
    }

    // 盾を生成しているかどうか
    if (m_pLightGuard)
    {
        // 盾を使っているなら
        if (m_bUsingGuard)
        {
            // 当たり判定を変える
            SetCollisionSizeDefence(TANK_COLLISION_SIZE_GUARD);

            // 変数宣言
            D3DXVECTOR3 playerRot = CCharacter::GetRot();   // プレイヤーの向いている向き
            D3DXVECTOR3 slidePos = DEFAULT_VECTOR;          // ずらす位置
            D3DXVECTOR3 shieldPos = DEFAULT_VECTOR;         // 盾の位置

            // 発生位置をずらす
            slidePos.x = TANK_GUARD_DISTANCE * -sinf(playerRot.y);
            slidePos.z = TANK_GUARD_DISTANCE * -cosf(playerRot.y);

            // 盾の位置を決める
            shieldPos = GetPos() + slidePos;

            // チャージ量に応じて、色を変える
            D3DXCOLOR color = TANK_GUARD_COLOR;
            float gDownValue = 0.0933f * (float)m_nCntGuards;
            color.g -= gDownValue;

            // 表示を反映
            m_pLightGuard->SetUseDraw(true);
            m_pLightGuard->SetRot(playerRot);
            m_pLightGuard->SetPos(shieldPos);
            m_pLightGuard->SetColor(color);
        }
        else
        {
            SetCollisionSizeDefence(TANK_COLLISION_SIZE);
            m_pLightGuard->SetUseDraw(false);
            m_pLightGuard->SetColor(TANK_GUARD_COLOR);
        }
    }
}

//=============================================================================
// マネキンモードの更新処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::UpdateMannequin(void)
{
    CManager::MODE mode = CManager::GetMode();

    switch (mode)
    {
    case CManager::MODE_CUSTOM:
    {
        // カスタマイズ画面での待機
        GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);

        // 武器を変えたら、武器を見る
        if (m_nCntAttackAnimTime > 0)
        {
            // 武器を見る
            m_nCntAttackAnimTime--;
            GetAnimation()->SetAnimation(ANIM_WEAPON_LOOK);
        }

        // 表示中なら
        if (GetDisp())
        {
            // 入力処理
            Input();

            // 1Pは、キーボードで右スティックの回転ができる
            if (m_nIdxControlAndColor == PLAYER_1)
            {
                CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
                if (pInputKeyboard->GetKeyboardPress(DIK_UP) ||
                    pInputKeyboard->GetKeyboardPress(DIK_LEFT) ||
                    pInputKeyboard->GetKeyboardPress(DIK_DOWN) ||
                    pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
                {
                    m_controlInput.bTiltedRightStick = true;

                    // 角度を求める
                    if (pInputKeyboard->GetKeyboardPress(DIK_LEFT))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(-45.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(-135.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(-90.0f);
                        }
                    }
                    else if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(45.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(135.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_LEFT))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(90.0f);
                        }
                    }
                    else if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                    }
                    else if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(180.0f);
                        }
                    }
                }
            }

            // 右スティックが倒れているなら向きを変える
            D3DXVECTOR3 rot = GetRot();
            const float ROT_SPEED = 3.0f;
            if (m_controlInput.bTiltedRightStick)
            {
                // 右回転
                if (STICK_RIGHT(m_controlInput.fRightStickAngle))
                {
                    rot.y -= D3DXToRadian(ROT_SPEED);
                }
                else if (STICK_LEFT(m_controlInput.fRightStickAngle))
                {
                    // 左回転
                    rot.y += D3DXToRadian(ROT_SPEED);
                }
            }

            // 回転の制限
            if (rot.y > D3DXToRadian(180.0f) || rot.y < D3DXToRadian(-180.0f))
            {
                rot.y *= -1;
            }

            // 回転の設定
            SetRot(rot);

            // カスタマイズ画面のUIの更新
            m_pUI_Custom_Atk->SetLeftToRightGauge(MAX_ATK, m_fAtk);
            m_pUI_Custom_Def->SetLeftToRightGauge(MAX_DEF, m_fDef);
            m_pUI_Custom_Spd->SetLeftToRightGauge(MAX_SPD, m_fSpd);
            m_pUI_Custom_Wei->SetLeftToRightGauge(MAX_WEI, m_fWei);
            if (m_bDispAbility)
            {
                m_pUI_Custom_Ability->SetDisp(true);
                m_pText_Custom_Ex_Head->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Ex_Up->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Ex_Down->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Ex_Wep->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Sp->SetColor(TEXT_EXIST_COLOR);
            }
            else
            {
                m_pUI_Custom_Ability->SetDisp(false);
                m_pText_Custom_Ex_Head->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Ex_Up->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Ex_Down->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Ex_Wep->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Sp->SetColor(TEXT_NOT_EXIST_COLOR);
            }
        }
        else
        {
            // 非表示なら、各表示物も消す
            m_pUI_Custom_Atk->SetLeftToRightGauge(MAX_ATK, 0);
            m_pUI_Custom_Def->SetLeftToRightGauge(MAX_DEF, 0);
            m_pUI_Custom_Spd->SetLeftToRightGauge(MAX_SPD, 0);
            m_pUI_Custom_Wei->SetLeftToRightGauge(MAX_WEI, 0);
            m_pUI_Custom_Ability->SetDisp(false);
            m_pText_Custom_Ex_Head->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Ex_Up->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Ex_Down->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Ex_Wep->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Sp->SetColor(TEXT_NOT_EXIST_COLOR);
        }

        // アニメーションさせる
        CCharacter::Update();
        break;
    }

    case CManager::MODE_RESULT:
    {
        // リザルト画面でのアニメーション
        switch (m_rank)
        {
        case RANK_1:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            m_nCntAttackAnimTime++;
            if (m_nCntAttackAnimTime > PLAYER_VICTORY_WAIT_START_FRAME)
            {
                m_nCntAttackAnimTime = PLAYER_VICTORY_WAIT_START_FRAME;
                GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            }
            else if (m_nCntAttackAnimTime == PLAYER_VICTORY_VOICE_FRAME)
            {
                //switch (m_voiceSet)
                //{
                //case VOICE_SET_ROBO:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_ICARUS);
                //    break;
                //case VOICE_SET_WOMAN:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_KLEINOD);
                //    break;
                //case VOICE_SET_GHOST:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_KNIGHT);
                //    break;
                //case VOICE_SET_OOO:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_OOO);
                //    break;
                //case VOICE_SET_MAN:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_RANGER);
                //    break;
                //case VOICE_SET_BOY:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_X);
                //    break;
                //}
            }
            break;
        case RANK_2:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            break;
        case RANK_3:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            break;
        case RANK_4:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            break;
        }

        // アニメーションさせる
        CCharacter::Update();
        break;
    }
    }

}

//=============================================================================
// プレイヤーが持つUIの更新処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::UpdateGameUI(void)
{
    // SPゲージとパーセント数値を更新
    D3DXVECTOR3 spGaugeSize = m_pUI_SP->GetMemorySize();
    spGaugeSize.x *= m_fCurrentEnergy / m_fCurrentEnergyMax;
    spGaugeSize.y *= m_fCurrentEnergy / m_fCurrentEnergyMax;
    m_pUI_SP->SetSize(spGaugeSize);
    int nDispNumber = (int)((m_fCurrentEnergy / m_fCurrentEnergyMax) * 100.0f);
    m_pNumArray_SP->SetDispNumber(nDispNumber);

    // 必殺ゲージMAXエフェクト
    if (m_fCurrentEnergy >= m_fCurrentEnergyMax)
    {
        m_nCntCurrentEnergyMaxTime++;
        if (m_nCntCurrentEnergyMaxTime > PLAYER_SP_GAUGE_MAX_EFFECT_INTERVAL)
        {
            m_nCntCurrentEnergyMaxTime = 0;
            D3DXVECTOR3 bodyPos = GetPartsPos(PARTS_BODY);
            CEffect2D *pSp1 = CEffect2D::Create(CEffectData::TYPE_SP_MAX_1, ConvertScreenPos(bodyPos));
            pSp1->SetPlayer(this);
            CEffect2D *pSp2 = CEffect2D::Create(CEffectData::TYPE_SP_MAX_2, ConvertScreenPos(bodyPos));
            pSp2->SetPlayer(this);
        }
    }

    //// 即死のHPとボールの速さ関係なら、HPゲージを点滅
    //float fDamage = CGame::GetBall()->GetSpeed() * PLAYER_TAKE_DAMAGE_RATE_FROM_BALL;
    //D3DXCOLOR col = m_pUI_HP->GetCol();
    //if (m_fLife <= fDamage)
    //{
    //    if (col.a == 1.0f)
    //    {
    //        m_pUI_HP->SetCol(D3DXCOLOR(col.r, col.g, col.b, 0.0f));
    //    }
    //    else
    //    {
    //        m_pUI_HP->SetCol(D3DXCOLOR(col.r, col.g, col.b, 1.0f));
    //    }
    //}
    //else
    //{
    //    m_pUI_HP->SetCol(D3DXCOLOR(col.r, col.g, col.b, 1.0f));
    //}

    // 何Pかの表示の位置更新（しゃがみ、もしくはダウンか起き上がり中なら表示の位置を下げる）
    if (GetDisp())
    {
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
        float fSizeY = collisionSizeDefence.y;
        DAMAGE_STATE damageState = GetDamageState();
        if (damageState == DAMAGE_STATE_BIG || damageState == DAMAGE_STATE_STAND_UP)
        {
            fSizeY *= PLAYER_SQUAT_CUT_COLLISION_SIZE;
        }
        m_pUI_Playable->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, fSizeY + 50.0f, 0.0f));
        m_pUI_Playable->SetDisp(true);
    }
    else
    {
        m_pUI_Playable->SetDisp(false);
    }
}

//=============================================================================
// やられた時の挙動
// Author : 後藤慎之助
//=============================================================================
void CPlayer::DeadMove(void)
{
    // 硬直していないなら
    if (m_nCntStopTime <= 0)
    {
        // リスポーン時間を数える
        m_nCntRespawnTime++;

        // 位置を取得
        D3DXVECTOR3 pos = DEFAULT_VECTOR;
        pos = GetPos();

        // 移動量制御
        D3DXVECTOR3 move = GetMove();
        move.x *= PLAYER_CONTROL_MOVE_DEATH;

        // 移動量と位置を結びつける
        pos += move;

        // 重力
        move.y -= PLAYER_TAKE_DAMAGE_BLOWN_GRAVITY;

        // 見えないところで止めておく
        if (pos.y < PLAYER_DEATH_STOP_POS_Y)
        {
            pos.y = PLAYER_DEATH_STOP_POS_Y;
        }

        // 位置、移動量を反映
        SetPos(pos);
        SetMove(move);

        // 吹っ飛ばされモーション
        GetAnimation()->SetAnimation(ANIM_BLOWN);

        // アニメーション更新
        CCharacter::Update();

        // リスポーン
        if (m_nCntRespawnTime >= RESPAWN_FRAME)
        {
            Respawn();
        }
    }
    else
    {
        // 硬直時間をカウント
        m_nCntStopTime--;
    }
}

//=============================================================================
// 着地中にリセットする変数たち
// Author : 後藤慎之助
//=============================================================================
void CPlayer::ResetOnGround(void)
{
    m_nCntPressJump = 0;
    m_bUsedSecondJump = false;
    m_nCntStartGlide = 0;
}

//=============================================================================
// 攻撃周りでリセットする変数たち
// Author : 後藤慎之助
//=============================================================================
void CPlayer::ResetAttack(void)
{
    m_nCntAttackTime = 0;
    m_nCntAttackAnimTime = 0;
    m_attackState = ATTACK_STATE_NONE;
    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    m_bUsingGuard = false;
    SetTakeKnockBack(true);
}

//=============================================================================
// リスポーン処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Respawn(void)
{
    // リスポーン
    CFortress *pFortress = CGame::GetFortress();
    D3DXVECTOR3 respawnPos = pFortress->GetPlayerSpawnPos(m_nIdxControlAndColor);
    SetPos(respawnPos);
    SetRot(pFortress->GetRot());
    SetDisp(true);
    SetUpLife(GetMaxLife());

    // 既存のリセット関数
    ResetOnGround();
    ResetAttack();

    // メンバ変数のリセット
    SetMove(DEFAULT_VECTOR);
    m_nCntLandingTime = 0;
    m_bGroundOld = false;
    m_nCntStopTime = 0;
    m_nCntRespawnTime = 0;

    SetTakeDamageTime(0);
    SetDamageState(DAMAGE_STATE_NONE);

    // リスポーンエフェクト発生
    CEffect3D::Emit(CEffectData::TYPE_RESPAWN_0, respawnPos, respawnPos);
    CEffect3D::Emit(CEffectData::TYPE_RESPAWN_1, respawnPos, respawnPos);

    m_fCurrentEnergy = 0.0f;
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助、池田悠希（クリッピングマスク対応）
//=============================================================================
void CPlayer::Draw(void)
{
    //// 必殺技を撃っているときは、表示を消す
    //if (m_pUI_Playable)
    //{
    //    if (CGame::GetCurrentSpShot())
    //    {
    //        m_pUI_Playable->SetDisp(false);
    //    }
    //    else
    //    {
    //        m_pUI_Playable->SetDisp(true);
    //    }
    //}

    // 表示するなら、描画
    if (GetDisp())
    {
        // クリッピングマスク
        LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
        if (m_pClipingMusk)
        {
            m_pClipingMusk->Draw();
            //ステンシルの設定
            pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
            pDevice->SetRenderState(D3DRS_STENCILREF, m_pClipingMusk->GetReferenceValue() + 1);
            pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
            pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

            pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
            pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
        }

        // キャラクター
        CCharacter::Draw();

        // クリッピングマスクの後処理
        if (m_pClipingMusk)
        {
            //ステンシル無効化
            pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        }
    }
    else
    {
        // マネキンモードでないなら
        if (!m_bMannequin)
        {
            // やられた時の描画
            CCharacter::DeathDraw();
        }
    }
}

//=============================================================================
// インスタンス生成
// Author : 後藤慎之助
//=============================================================================
CPlayer * CPlayer::CreateInGame(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxCreate, int nIdxControlAndColor,
    AI_LEVEL AIlevel, int role, bool bUseKeyboard)
{
    // メモリ確保
    CPlayer *pPlayer = NULL;
    pPlayer = new CPlayer;

    // 親元の情報を設定
    pPlayer->CCharacter::SetPos(pos);
    pPlayer->CCharacter::SetRot(rot);
    pPlayer->CCharacter::SetRotDest(rot);
    pPlayer->CCharacter::SetHPDisp(nIdxControlAndColor);

    // 読み込む種類の設定
    pPlayer->m_nIdxControlAndColor = nIdxControlAndColor;
    pPlayer->m_role = role;

    // 初期化
    pPlayer->Init(pos, DEFAULT_SCALE);

    // 結びつけるメンバ変数の初期化
    pPlayer->m_nIdxCreate = nIdxCreate;
    pPlayer->m_AIlevel = AIlevel;
    pPlayer->m_bUseKeyboard = bUseKeyboard;
    if (pPlayer->m_AIlevel != AI_LEVEL_NONE)
    {
        pPlayer->m_pAI = CAi::Create(pPlayer);
    }
    pPlayer->SetUseControllerEffectByTakeDamage(pPlayer->GetUseControllerEffect());

    // UIを生成
    D3DXCOLOR playableCol = DEFAULT_COLOR;
    D3DXCOLOR spGagueCol = DEFAULT_COLOR;
    int nTexTypePlayable = 0;
    int nTexTypePlayer = 0;
    switch (pPlayer->m_nIdxControlAndColor)
    {
    case PLAYER_1:
        playableCol = PLAYER_COLOR_1;
        spGagueCol = D3DXCOLOR(0.768f, 0.470f, 0.470f, 1.0f);
        nTexTypePlayable = 21;
        nTexTypePlayer = 78;
        break;
    case PLAYER_2:
        playableCol = PLAYER_COLOR_2;
        spGagueCol = D3DXCOLOR(0.501f, 0.607f, 0.737f, 1.0f);
        nTexTypePlayable = 22;
        nTexTypePlayer = 79;
        break;
    case PLAYER_3:
        playableCol = PLAYER_COLOR_3;
        spGagueCol = D3DXCOLOR(0.513f, 0.654f, 0.509f, 1.0f);
        nTexTypePlayable = 23;
        nTexTypePlayer = 80;
        break;
    case PLAYER_4:
        playableCol = PLAYER_COLOR_4;
        spGagueCol = D3DXCOLOR(0.760f, 0.623f, 0.478f, 1.0f);
        nTexTypePlayable = 24;
        nTexTypePlayer = 81;
        break;
    }
    switch (pPlayer->m_AIlevel)
    {
    case AI_LEVEL_1:
        nTexTypePlayable = 25;
        break;
    case AI_LEVEL_2:
        nTexTypePlayable = 27;
        break;
    case AI_LEVEL_3:
        nTexTypePlayable = 28;
        break;
    }
    // HPゲージ（キャラクターに移行しました）
    const float UI_SIZE_X = 294.0f; // ここの値を、UIの大体の横幅に合わせる
    const float SPACE_SIZE = (SCREEN_WIDTH - (UI_SIZE_X * CGame::GetNumAllPlayer())) / (CGame::GetNumAllPlayer() + 1);
    const float FIRST_UI_POS_X = SPACE_SIZE + (UI_SIZE_X / 2.0f);
    const float NEXT_UI_POS_X = UI_SIZE_X + SPACE_SIZE;
    float fDigitPosX = FIRST_UI_POS_X + (NEXT_UI_POS_X * (float)pPlayer->m_nIdxCreate);

    // 必殺ゲージ
    CUI::Create(76, D3DXVECTOR3(fDigitPosX - 80.0f, 60.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0, DEFAULT_COLOR);
    pPlayer->m_pUI_SP = CUI::Create(77, D3DXVECTOR3(fDigitPosX - 80.0f, 60.0f, 0.0f), D3DXVECTOR3(85.0f, 85.0f, 0.0f), 0, spGagueCol);
    CUI::Create(86, D3DXVECTOR3(fDigitPosX - 57.5f, 60.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 0, DEFAULT_COLOR);
    pPlayer->m_pNumArray_SP = CNumberArray::Create(12, D3DXVECTOR3(fDigitPosX - 87.5f, 60.0f, 0.0f), 15.0f,
        DEFAULT_COLOR, 0, false);

    // Player表示
    CUI::Create(nTexTypePlayer, D3DXVECTOR3(fDigitPosX + 10.0f, 50.0f, 0.0f), D3DXVECTOR3(82.5f, 54.0f, 0.0f), 0, DEFAULT_COLOR);

    // プレイアブル表示
    pPlayer->m_pUI_Playable = CUI::Create(nTexTypePlayable, DEFAULT_VECTOR, D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0, playableCol);

    // 光の盾生成
    pPlayer->m_pLightGuard = CModelEffect::Create(30, DEFAULT_VECTOR, DEFAULT_VECTOR,
        TANK_GUARD_COLOR);

    // 回復魔方陣生成
    pPlayer->m_pHealingCircle = CBullet::Create(CBullet::TYPE_HEALER_SKY, DEFAULT_VECTOR, DEFAULT_VECTOR, OBJTYPE_PLAYER);

    return pPlayer;
}

//=============================================================================
// カスタマイズ画面での生成
// Author : 後藤慎之助
//=============================================================================
CPlayer * CPlayer::CreateInCustom(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxControlAndColor, bool bDisp)
{
    // メモリ確保
    CPlayer *pPlayer = NULL;
    pPlayer = new CPlayer;

    // 親元の情報を設定
    pPlayer->CCharacter::SetPos(pos);
    pPlayer->CCharacter::SetRot(rot);

    // 読み込む種類の設定
    pPlayer->m_nIdxControlAndColor = nIdxControlAndColor;

    // UIを生成
    D3DXVECTOR3 startPos = D3DXVECTOR3(205.0f, 293.5f, 0.0f);
    D3DXVECTOR3 clipingPos = DEFAULT_VECTOR;
    const D3DXVECTOR3 gaugeSize = D3DXVECTOR3(210.0f, 22.0f, 0.0f);
    const D3DXVECTOR3 abilitySize = D3DXVECTOR3(297.0f, 155.0f, 0.0f);
    D3DXVECTOR3 abilityPos = D3DXVECTOR3(167.0f, 200.5f, 0.0f);
    switch (pPlayer->m_nIdxControlAndColor)
    {
    case PLAYER_1:
        clipingPos = D3DXVECTOR3(167.0f, 390.0f, 0.0f);
        break;
    case PLAYER_2:
        startPos.x += 315.0f;
        abilityPos.x += 315.0f;
        clipingPos = D3DXVECTOR3(482.0f, 390.0f, 0.0f);
        break;
    case PLAYER_3:
        startPos.x += 315.0f * PLAYER_3;
        abilityPos.x += 315.0f * PLAYER_3;
        clipingPos = D3DXVECTOR3(797.0f, 390.0f, 0.0f);
        break;
    case PLAYER_4:
        startPos.x += 315.0f * PLAYER_4;
        abilityPos.x += 315.0f * PLAYER_4;
        clipingPos = D3DXVECTOR3(1112.0f, 390.0f, 0.0f);
        break;
    }
    pPlayer->m_pUI_Custom_Ability = CUI::Create(73, abilityPos, abilitySize, 0, DEFAULT_COLOR);
    float fDigitPosY = 0.0f;
    const float DIGIT_UI_VALUE = 31.5f;
    pPlayer->m_pUI_Custom_Def = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_DEF_COLOR);
    pPlayer->m_pUI_Custom_Def->SetActionInfo(0, CUI::ACTION_GAUGE, false); // ゲージに変える
    fDigitPosY += DIGIT_UI_VALUE;

    pPlayer->m_pUI_Custom_Atk = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_ATK_COLOR);
    pPlayer->m_pUI_Custom_Atk->SetActionInfo(0, CUI::ACTION_GAUGE, false); // ゲージに変える
    fDigitPosY += DIGIT_UI_VALUE;

    pPlayer->m_pUI_Custom_Spd = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_SPD_COLOR);
    pPlayer->m_pUI_Custom_Spd->SetActionInfo(0, CUI::ACTION_GAUGE, false); // ゲージに変える
    fDigitPosY += DIGIT_UI_VALUE;

    pPlayer->m_pUI_Custom_Wei = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_WEI_COLOR);
    pPlayer->m_pUI_Custom_Wei->SetActionInfo(0, CUI::ACTION_GAUGE, false); // ゲージに変える

                                                                           // テキストを生成
    startPos += D3DXVECTOR3(-105.0f, -155.0f, 0.0f); // UIのステータスバーから、アビリティのテキストへ位置を合わせる
    fDigitPosY = 0.0f;
    const float DIGIT_TEXT_VALUE = 26.0f;
    const int textSize = 20;
    pPlayer->m_pText_Custom_Ex_Head = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "なし",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Ex_Up = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "なし",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Ex_Down = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "なし",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Ex_Wep = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "なし",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Sp = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "なし",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);

    // クリッピングを生成
    pPlayer->ApplyMusk(clipingPos, D3DXVECTOR3(298.0f, 625.0f, 0.0f));

    // 初期化
    pPlayer->Init(pos, DEFAULT_SCALE);

    // 結びつけるメンバ変数の初期化
    pPlayer->SetDisp(bDisp);

    // マネキンモードに
    pPlayer->m_bMannequin = true;

    return pPlayer;
}

//=============================================================================
// リザルト画面での生成
// Author : 後藤慎之助
//=============================================================================
CPlayer * CPlayer::CreateInResult(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxControlAndColor, RANK rank)
{
    // メモリ確保
    CPlayer *pPlayer = NULL;
    pPlayer = new CPlayer;

    // 親元の情報を設定
    pPlayer->CCharacter::SetPos(pos);
    pPlayer->CCharacter::SetRot(rot);

    // 読み込む種類の設定
    pPlayer->m_nIdxControlAndColor = nIdxControlAndColor;

    // 初期化
    pPlayer->Init(pos, DEFAULT_SCALE);

    // 結びつけるメンバ変数の初期化
    pPlayer->m_rank = rank;
    if (pPlayer->m_rank != RANK_1)
    {
        //// 1位以外は、武器を描画しない
        //pPlayer->SetDrawWeapon(false);
    }

    // マネキンモードに
    pPlayer->m_bMannequin = true;

    return pPlayer;
}

//=============================================================================
// 行動
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Movement(float fSpeed)
{
    // 位置、移動量、負傷状態を取得
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 move = DEFAULT_VECTOR;
    DAMAGE_STATE damageState = GetDamageState();
    pos = GetPos();
    move = GetMove();

    // 1F前の位置を記憶
    SetPosOld(pos);

    // 1F前の移動量を記憶
    SetMoveOld(move);

    // 横と奥行きの移動量制御
    ControlMove(move.x, m_bGround);
    ControlMove(move.z, m_bGround);

    // モーションをまずは待機にする
    GetAnimation()->SetAnimation(m_waitMotion);

    // プレイヤー移動処理
    Control(fSpeed, move);

    // 移動量と位置を結びつける
    pos += move;

    // 地面より上なら
    if (pos.y > 0.0f)
    {
        // 重力
        float fGravity = PLAYER_BASE_MINIMUM_GRAVITY + (m_fWei * PLAYER_ADD_BASE_GRAVITY_RATE);
        if (damageState == DAMAGE_STATE_BLOWN)
        {
            // 吹っ飛ばされ中は固定値
            fGravity = PLAYER_TAKE_DAMAGE_BLOWN_GRAVITY;
        }
        move.y -= fGravity;

        // 地面にいない
        m_bGround = false;
    }
    else
    {
        // 地面にいるなら、重力をかけないでジャンプ可能、急降下のチェックも復活、二段ジャンプも復活
        pos.y = 0.0f;
        move.y = 0.0f;
        m_bGround = true;
    }

    //====================================================
    // 攻撃処理
    AttackUpdate(pos, move);

    // 攻撃の生成
    AttackGenerator();

    // ジャンプ
    Jump(move);

    // 移動モーションの管理
    MoveMotion();

    // 攻撃モーションにするかどうか
    AttackMotion();
    //====================================================

    //====================================================
    // 防御処理
    // 負傷中の更新
    DamageUpdate(pos, move);

    // 負傷モーションにするかどうか
    DamageMotion();
    //====================================================

    // 回転制御
    if (m_controlInput.bPressR2 && m_bGround)
    {
        // 向き固定
        D3DXVECTOR3 rot = GetRot();
        SetRotDestY(rot.y);
    }
    else
    {
        RotControl();
    }

    // マップ制限
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    D3DXVECTOR3 myCubeSize = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
    D3DXVECTOR3 posOld = GetPosOld();
    CGame::MapLimit(pos, posOld, myCubeSize);

    // 位置、移動量を反映
    SetPos(pos);
    SetMove(move);

    // 1F前、ジャンプできたかどうかを記録
    m_bGroundOld = m_bGround;

    // 移動要塞にエナジーを送る処理
    SendEnergyForFortress();

#ifdef COLLISION_TEST
    bool bIsInvincible = GetInvincible();
    if (!bIsInvincible)
    {
        D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CDebug::Create(pos, size, CDebug::TYPE_MOMENT, 65);
    }
#endif // COLLISION_TEST
}

//=============================================================================
// 移動系モーションの管理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::MoveMotion(void)
{
    // 着地モーションにするかどうか
    if (!m_bGroundOld && m_bGround)
    {
        // 着地の砂煙（当たり判定の分、砂煙が広がる）
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
        CEffect3D::Emit(CEffectData::TYPE_LANDING_FUGITIVE_DUST, GetPos(), GetPos());

        // 着地時間を設定
        m_nCntLandingTime = PLAYER_LANDING_TIME;
    }
    if (m_nCntLandingTime > 0)
    {
        // カウントダウン
        m_nCntLandingTime--;

        // モーションを着地にする
        GetAnimation()->SetAnimation(ANIM_LANDING);
    }

    // 滑空のカウンタ
    if (m_nCntStartGlide > 0)
    {
        m_nCntStartGlide--;
    }

    // ジャンプモーションにするかどうか
    if (!m_bGround)
    {
        // 滑空アニメーションのカウンタが0以下なら滑空
        if (m_nCntStartGlide <= 0)
        {
            GetAnimation()->SetAnimation(ANIM_GLIDE);
        }
        else
        {
            // 二段ジャンプを使かったかどうか
            if (m_bUsedSecondJump)
            {
                GetAnimation()->SetAnimation(ANIM_SECOND_JUMP);
            }
            else
            {
                GetAnimation()->SetAnimation(ANIM_JUMP);
            }
        }
    }
}

//=============================================================================
// プレイヤーの移動制御
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Control(float fSpeed, D3DXVECTOR3& move)
{
    // 向き
    D3DXVECTOR3 rot = GetRot();

    // 地上で攻撃中以外なら（主に地上スイングでは動けない）
    if (!m_bGround || m_attackState == ATTACK_STATE_NONE)
    {
        // 負傷していない状態かつ、着地中でもないなら
        if (GetDamageState() == DAMAGE_STATE_NONE && m_nCntLandingTime <= 0)
        {
            // スティックが倒れているなら移動
            if (m_controlInput.bTiltedLeftStick)
            {
                if (m_bGround)
                {
                    //// 砂煙の発生
                    //if (fabsf(m_moveOld.x) <= PLAYER_SET_WALK_SMOKE_VALUE)
                    //{
                    //    CEffect3D::Emit(CEffectData::TYPE_WALK_SMOKE_LEFT, GetPos(), GetPos());
                    //}

                    // 移動量に代入
                    move.x = sinf(m_controlInput.fLeftStickAngle)*fSpeed;
                    move.z = cosf(m_controlInput.fLeftStickAngle)*fSpeed;

                    // モーションを歩きにする
                    GetAnimation()->SetAnimation(m_walkMotion);

                    //キャラの向きを変える
                    SetRotDestY(m_controlInput.fPlayerAngle);
                }
                else
                {
                    // 空中移動は、徐々に加算
                    move.x += sinf(m_controlInput.fLeftStickAngle)*fSpeed / PLAYER_CONTROL_MOVE_ADD_RATE_IN_AIR;
                    move.z += cosf(m_controlInput.fLeftStickAngle)*fSpeed / PLAYER_CONTROL_MOVE_ADD_RATE_IN_AIR;
                }
            }

            // 最大速度を超えないようにする
            if (move.x > fSpeed)
            {
                move.x = fSpeed;
            }
            else if (move.x < -fSpeed)
            {
                move.x = -fSpeed;
            }
            if (move.z > fSpeed)
            {
                move.z = fSpeed;
            }
            else if (move.z < -fSpeed)
            {
                move.z = -fSpeed;
            }
        }
    }
}

//=============================================================================
// ジャンプの処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::Jump(D3DXVECTOR3& move)
{
    // 防御当たり判定の大きさ、負傷状態を取得
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    DAMAGE_STATE damageState = GetDamageState();

    // Aプレス
    if (m_controlInput.bPressA)
    {
        // 負傷していない状態なら（攻撃中でも距離は伸ばせる）
        if (damageState == DAMAGE_STATE_NONE)
        {
            // ジャンプのカウンタが0より大きく、加算カウンタ中なら
            if (m_nCntPressJump > 0 && m_nCntPressJump <= PLAYER_JUMP_ADD_FRAME)
            {
                // ジャンプのカウンタ加算
                m_nCntPressJump++;

                // ジャンプ量加算
                move.y += PLAYER_BASE_MINIMUM_GRAVITY + (m_fWei * PLAYER_ADD_BASE_GRAVITY_RATE);
            }
            else if (m_nCntPressJump > PLAYER_JUMP_ADD_FRAME && m_nCntPressJump <= PLAYER_JUMP_KEEP_FRAME)
            {
                // 滞空
                if (move.y <= 0.0f)
                {
                    // ジャンプのカウンタ加算
                    m_nCntPressJump++;

                    move.y = 0.0f;
                }
            }
        }
    }
    else
    {
        // ジャンプのカウンタをリセット
        m_nCntPressJump = 0;
    }

    // Aトリガー（ジャンプ生成のイメージ）
    if (m_controlInput.bTriggerA)
    {
        // 負傷していない状態かつ、攻撃状態がなしなら
        if (damageState == DAMAGE_STATE_NONE && m_attackState == ATTACK_STATE_NONE)
        {
            // 地面にいるなら
            if (m_bGround)
            {
                // 向きによって、砂埃の向きを変える
                if (GetRot().y == PLAYER_ROT_LEFT)
                {
                    // ジャンプの砂煙
                    CEffect3D::Emit(CEffectData::TYPE_JUMP_FUGITIVE_DUST, GetPos(), GetPos());

                }
                else
                {
                    // ジャンプの砂煙
                    CEffect3D::Emit(CEffectData::TYPE_JUMP_FUGITIVE_DUST, GetPos(), GetPos());

                }

                // ジャンプ音
                CManager::SoundPlay(CSound::LABEL_SE_JUMP);

                // ジャンプの初期量
                move.y = PLAYER_JUMP_FIRST_RATE;

                // 滑空までのカウンタを設定
                m_nCntStartGlide = PLAYER_FIRST_JUMP_MOTION_TO_GLIDE;

                // 地面にいないことに
                m_bGround = false;

                // 念のため着地時間をリセット
                m_nCntLandingTime = 0;

                // ジャンプのカウンタ加算
                m_nCntPressJump++;
            }
            else
            {
                // 地面にいなく、二段ジャンプをしていないなら
                if (!m_bUsedSecondJump)
                {
                    // 多段ジャンプの空気の輪と砂煙（当たり判定の半分の大きさ）
                    CEffect3D::Emit(CEffectData::TYPE_SECOND_JUMP_AIR_RING, GetPos(), GetPos(), collisionSizeDefence.x * 0.5f);
                    CEffect3D::Emit(CEffectData::TYPE_SECOND_JUMP_SMOKE, GetPos(), GetPos());

                    // ジャンプ音
                    CManager::SoundPlay(CSound::LABEL_SE_JUMP);

                    //// 1Fだけ向きを変えることができる
                    //RotControl();

                    // ジャンプの初期量
                    move.y = PLAYER_JUMP_FIRST_RATE * PLAYER_NEXT_JUMP_DOWN_RATE;

                    // 滑空までのカウンタを設定
                    m_nCntStartGlide = PLAYER_NEXT_JUMP_MOTION_TO_GLIDE;

                    // 二段ジャンプを使ったフラグをtrueに
                    m_bUsedSecondJump = true;

                    // 念のため着地時間をリセット
                    m_nCntLandingTime = 0;

                    // ジャンプのカウンタ加算
                    m_nCntPressJump++;
                }
            }
        }
    }
}

//=============================================================================
// 負傷の更新処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::DamageUpdate(D3DXVECTOR3 pos, D3DXVECTOR3& move)
{
    // 負傷状態、負傷時間を取得
    DAMAGE_STATE damageState = GetDamageState();
    int nTakeDamageTime = GetTakeDamageTime();

    switch (damageState)
    {
    case DAMAGE_STATE_BLOWN:
        // 吹っ飛ばされからダウンへの遷移
        if (m_bGround)
        {
            // 地面にいてかつ、速度が落ちているなら
            if (fabsf(move.x) < KNOCK_BACK_STOP_BORDER)
            {
                move.x = 0.0f;
                damageState = DAMAGE_STATE_BIG;
                nTakeDamageTime = TAKE_DAMAGE_BIG_FRAME;
            }
        }
        else
        {
            // 空中の速度を最低限保持する
            if (fabsf(move.x) < KNOCK_BACK_STOP_BORDER)
            {
                if (move.x > 0.0f)
                {
                    move.x = KNOCK_BACK_STOP_BORDER;
                }
                else
                {
                    move.x = -KNOCK_BACK_STOP_BORDER;
                }
            }
        }
        break;
    case DAMAGE_STATE_BIG:
        // 起き上がり可能時間なら
        if (nTakeDamageTime <= PLAYER_TAKE_DAMAGE_START_QUICK_STAND_UP)
        {
            // 即起き上がりor吸収起き上がりアピール
            if (m_controlInput.bTiltedLeftStick)
            {
                damageState = DAMAGE_STATE_STAND_UP;
                nTakeDamageTime = PLAYER_TAKE_DAMAGE_STAND_UP_FRAME;
            }
            else if (m_controlInput.bTriggerX)
            {
                // 吸収エフェクト
                D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
                CEffect3D::Emit(CEffectData::TYPE_ABSORB, pos + D3DXVECTOR3(0.0f, collisionSizeDefence.y / 2.0f, 0.0f),
                    pos + D3DXVECTOR3(0.0f, collisionSizeDefence.y / 2.0f, 0.0f), collisionSizeDefence.x);

                // ダメージ状態のリセット
                damageState = DAMAGE_STATE_NONE;
                nTakeDamageTime = 0;

                //// 共通起き上がり攻撃をいれる場所
                //m_attackState = ATTACK_STATE_ABSORB;
                //m_nCntAttackTime = ATTACK_ABSORB_WHOLE_FRAME;
                //Absorb(pos);
            }
        }
        break;
    }

    // 負傷状態、負傷時間を更新
    SetDamageState(damageState);
    SetTakeDamageTime(nTakeDamageTime);
}

//=============================================================================
// 負傷モーションの管理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::DamageMotion(void)
{
    // 負傷状態に応じて、モーションを決める
    DAMAGE_STATE damageState = GetDamageState();
    switch (damageState)
    {
    case DAMAGE_STATE_SMALL:
        GetAnimation()->SetAnimation(ANIM_DAMAGE_SMALL);
        break;
    case DAMAGE_STATE_BIG:
        GetAnimation()->SetAnimation(ANIM_DAMAGE_BIG);
        break;
    case DAMAGE_STATE_STAND_UP:
        GetAnimation()->SetAnimation(ANIM_STAND_UP);
        break;
    case DAMAGE_STATE_BLOWN:
        GetAnimation()->SetAnimation(ANIM_BLOWN);
        break;
    }
}

//=============================================================================
// 毎ラウンドリセットするステータス
// Author : 後藤慎之助
//=============================================================================
void CPlayer::ResetStatusEveryRound(void)
{
    //// 生存しているなら
    //if (m_bDisp)
    //{
    //    // ラウンドリジェネ
    //    if (IS_BITON(m_exFlag, EX_FLAG_ROUND_HEAL))
    //    {
    //        // 最大HPなら、エフェクトも回復もない
    //        if (m_fLife != m_fDef)
    //        {
    //            // 回復
    //            const float HEAL_VALUE = 0.0011f;
    //            m_fLife += m_fDef * HEAL_VALUE;

    //            // 回復の上限
    //            if (m_fLife > m_fDef)
    //            {
    //                m_fLife = m_fDef;
    //            }
    //        }
    //    }
    //}

    //// 必殺ゲージ
    //if (IS_BITOFF(m_exFlag, EX_FLAG_SAVE_SP_GAUGE))
    //{
    //    m_fSpGaugeCurrent = 0.0f;
    //}

    //// バリア状態をリセット
    //if (m_bSpBarrier)
    //{
    //    m_bSpBarrier = false;
    //}
}

//=============================================================================
// エナジーを得る処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::GainEnergy(const float fEnergy)
{
    // エナジー加算
    m_fCurrentEnergy += fEnergy;
    if (m_fCurrentEnergy > m_fCurrentEnergyMax)
    {
        m_fCurrentEnergy = m_fCurrentEnergyMax;
    }
}

//=============================================================================
// コントローラの振動を使用するかどうか
// Author : 後藤慎之助
//=============================================================================
bool CPlayer::GetUseControllerEffect(void)
{
    bool bUseControllerEffect = false;

    // AIでないかつ、キーボード操作でないなら、振動を使う
    if (m_AIlevel == AI_LEVEL_NONE && !m_bUseKeyboard)
    {
        bUseControllerEffect = true;
    }

    // いずれオプションで強制OFFできるようにここに書く

    return bUseControllerEffect;
}

//=============================================================================
// クリッピングマスクを適用
// Author : 池田悠希
//=============================================================================
void CPlayer::ApplyMusk(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumTexture)
{
    if (!m_pClipingMusk)
    {
        m_pClipingMusk = CClipingMusk::Create(pos, size, nNumTexture);
    }
}

//=============================================================================
// テクスチャなしクリッピングマスクを適用
// Author : 池田悠希
//=============================================================================
void CPlayer::ApplyMusk(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    if (!m_pClipingMusk)
    {
        m_pClipingMusk = CClipingMusk::Create(pos, size);
    }
}

//=============================================================================
// 移動要塞にエナジーを送る処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::SendEnergyForFortress(void)
{
    // エナジーがないなら、関数を抜ける
    if (m_fCurrentEnergy <= 0.0f)
    {
        return;
    }

    // 移動要塞が存在するなら
    CFortress*pFortress = CGame::GetFortress();
    if (pFortress)
    {
        if (pFortress->GetDisp())
        {
            // 当たっているなら
            if (IsCollisionCylinder(GetPos(), GetCollisionSizeDefence(), pFortress->GetPos(), D3DXVECTOR2(2000.0f,1000.0f)))
            {
                // 攻撃フェーズ中以外かつ、エナジーがあるなら送る
                if (!pFortress->GetAttackPhase() && m_fCurrentEnergy > 0.0f)
                {
                    // エナジーボール生成
                    CBullet *pBullet = CBullet::Create(CBullet::TYPE_ENERGY_BALL, GetPartsPos(PARTS_BODY), DEFAULT_VECTOR, OBJTYPE_PLAYER);
                    pBullet->SetWhoContribution(m_nIdxCreate);
                    pBullet->SetDamage(m_fCurrentEnergy);   // ダメージ量をチャージ量にする

                    // 貢献度も加算
                    GainContribution((int)m_fCurrentEnergy);
                    m_fCurrentEnergy = 0.0f;
                }
            }
        }
    }
}