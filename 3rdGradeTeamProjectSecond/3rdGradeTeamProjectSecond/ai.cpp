//===============================================
//
// AI処理 (ai.cpp)
// Author : 後藤慎之助
//
//===============================================

//========================
// インクルードファイル
//========================
#include "ai.h"
#include "game.h"
#include "library.h"
#include "fortress.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// 弾を近いとみなす値
#define BULLET_CLOSE_VALUE 750.0f

// 攻撃の射程
#define ATTACK_RANGE_WARRIOR 750.0f
#define ATTACK_RANGE_HUNTER 3000.0f
#define ATTACK_RANGE_CARRIER 1250.0f
#define ATTACK_RANGE_TANK 1500.0f
#define ATTACK_RANGE_HEALER 2500.0f

// 標的取得間隔
#define TARGETTING_INTERVAL_AI_LEVEL_1_MAX 30
#define TARGETTING_INTERVAL_AI_LEVEL_1_MIN 20
#define TARGETTING_INTERVAL_AI_LEVEL_2_MAX 20
#define TARGETTING_INTERVAL_AI_LEVEL_2_MIN 10
#define TARGETTING_INTERVAL_AI_LEVEL_3_MAX 10
#define TARGETTING_INTERVAL_AI_LEVEL_3_MIN 5

// 考え時間
#define THINKING_TIME_AI_LEVEL_1_MAX 45
#define THINKING_TIME_AI_LEVEL_1_MIN 30
#define THINKING_TIME_AI_LEVEL_2_MAX 20
#define THINKING_TIME_AI_LEVEL_2_MIN 10
#define THINKING_TIME_AI_LEVEL_3_MAX 5
#define THINKING_TIME_AI_LEVEL_3_MIN 1

// コアの優先順位
#define CORE_PRIORITY_1 60
#define CORE_PRIORITY_2 30
#define CORE_PRIORITY_3 10

// 強襲時間
#define ASSAULT_TIME_AI_LEVEL_1_MAX 60
#define ASSAULT_TIME_AI_LEVEL_1_MIN 30
#define ASSAULT_TIME_AI_LEVEL_2_MAX 150
#define ASSAULT_TIME_AI_LEVEL_2_MIN 90
#define ASSAULT_TIME_AI_LEVEL_3_MAX 180
#define ASSAULT_TIME_AI_LEVEL_3_MIN 120

// 避ける時間
#define AVOID_TIME_AI_LEVEL_1_MAX 30
#define AVOID_TIME_AI_LEVEL_1_MIN 15
#define AVOID_TIME_AI_LEVEL_2_MAX 40
#define AVOID_TIME_AI_LEVEL_2_MIN 25
#define AVOID_TIME_AI_LEVEL_3_MAX 35
#define AVOID_TIME_AI_LEVEL_3_MIN 20

// 待つ時間
#define WAIT_TIME_AI_LEVEL_1_MAX 30
#define WAIT_TIME_AI_LEVEL_1_MIN 15
#define WAIT_TIME_AI_LEVEL_2_MAX 40
#define WAIT_TIME_AI_LEVEL_2_MIN 25
#define WAIT_TIME_AI_LEVEL_3_MAX 35
#define WAIT_TIME_AI_LEVEL_3_MIN 20

// 攻撃時に狙った攻撃ができるかどうか（100分の何）
#define ATTACK_TARGET_AI_LEVEL_1 30
#define ATTACK_TARGET_AI_LEVEL_2 75
#define ATTACK_TARGET_AI_LEVEL_3 95

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CAi::CAi()
{
    m_buttonStateOld.bButtonA = false;
    m_buttonStateOld.bButtonX = false;
    m_buttonStateOld.bButtonB = false;
    m_buttonStateOld.bButtonR2 = false;
    m_pPlayer = NULL;

    m_core = CORE_THINKING;
    m_nCntActionTime = 0;

    m_targetPos = DEFAULT_VECTOR;
    m_nCntSearchTarget = 0;
    m_fAttackRange = 0.0f;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CAi::~CAi()
{
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CAi::Update(void)
{
    // ターゲット位置を決める処理
    if (m_nCntSearchTarget <= 0)
    {
        GetTargetPos();
    }
    else
    {
        m_nCntSearchTarget--;
    }

    // 変数宣言
    bool bCurrentButtonA = false;         // 現在のAボタン
    bool bCurrentButtonX = false;         // 現在のXボタン
    bool bCurrentButtonB = false;         // 現在のBボタン
    bool bCurrentButtonR2 = false;        // 現在のR2ボタン

    // 追加
    RushToTarget();
    bCurrentButtonA = JumpBecauseEnemyBulletClose();
    bCurrentButtonX = DecideAttack();

    //// コアごとに場合分け
    //switch (m_core)
    //{
    //case CORE_THINKING:
    //    Thinking();
    //    DontMove(false);
    //    break;
    //case CORE_ASSAULT:
    //    AnotherAction();
    //    RushToBall();
    //    bCurrentButtonA = JumpBecauseBallUp();
    //    switch (m_pPlayer->GetAILevel())
    //    {
    //    case CPlayer::AI_LEVEL_1:
    //    case CPlayer::AI_LEVEL_2:
    //        bCurrentButtonX = DecideAttack();
    //        break;
    //    case CPlayer::AI_LEVEL_3:
    //        bCurrentButtonX = DecideAttack();
    //        break;
    //    }
    //    break;
    //case CORE_AVOID:
    //    AnotherAction();
    //    RunAwayFromBall();
    //    bCurrentButtonA = JumpBecauseBallMoveDown();
    //    bCurrentButtonX = DecideAttack();
    //    break;
    //case CORE_WAIT:
    //    AnotherAction();
    //    DontMove(true);
    //    bCurrentButtonX = DecideAttack();
    //    break;
    //}

    //==============================================================
    // コントローラの操作に置き換える
    // Aボタントリガー
    if (bCurrentButtonA && !m_buttonStateOld.bButtonA)
    {
        m_pPlayer->GetControlInput()->bTriggerA = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bTriggerA = false;
    }

    // Aボタンプレス
    if (bCurrentButtonA && m_buttonStateOld.bButtonA)
    {
        m_pPlayer->GetControlInput()->bPressA = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bPressA = false;
    }

    // Xボタントリガー
    if (bCurrentButtonX && !m_buttonStateOld.bButtonX)
    {
        m_pPlayer->GetControlInput()->bTriggerX = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bTriggerX = false;
    }

    // Xボタンプレス
    if (bCurrentButtonX && m_buttonStateOld.bButtonX)
    {
        m_pPlayer->GetControlInput()->bPressX = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bPressX = false;
    }

    // Xボタンリリース
    if (!bCurrentButtonX && m_buttonStateOld.bButtonX)
    {
        m_pPlayer->GetControlInput()->bReleaseX = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bReleaseX = false;
    }

    // Bボタントリガー
    if (bCurrentButtonB && !m_buttonStateOld.bButtonB)
    {
        m_pPlayer->GetControlInput()->bTriggerB = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bTriggerB = false;
    }

    // R2ボタンプレス
    if (bCurrentButtonR2 && m_buttonStateOld.bButtonR2)
    {
        m_pPlayer->GetControlInput()->bPressR2 = true;
    }
    else
    {
        m_pPlayer->GetControlInput()->bPressR2 = false;
    }
    //==============================================================

    // 1F前の情報として記憶しておく
    m_buttonStateOld.bButtonA = bCurrentButtonA;
    m_buttonStateOld.bButtonX = bCurrentButtonX;
    m_buttonStateOld.bButtonB = bCurrentButtonB;
    m_buttonStateOld.bButtonR2 = bCurrentButtonR2;
}

//=============================================================================
// インスタンス生成処理
// Author : 後藤慎之助
//=============================================================================
CAi * CAi::Create(CPlayer *pPlayer)
{
    // インスタンスの生成
    CAi *pAI;
    pAI = new CAi;

    pAI->m_pPlayer = pPlayer;
    pAI->GetThinkingTime();

    pAI->GetAttackAngle();

    return pAI;
}

//=============================================================================
// 考え中の処理
// Author : 後藤慎之助
//=============================================================================
void CAi::Thinking(void)
{
    // 時間を数える
    m_nCntActionTime--;

    // 一定カウンタで、次のコアを決める
    if (m_nCntActionTime < 0)
    {
        m_nCntActionTime = 0;

        // ランダムに数字を決める
        int nRandNum = GetRandNum(100, 1);

        // 何の攻撃が採用されたか、AIレベルによって決める
        if (nRandNum >= 1 && nRandNum <= CORE_PRIORITY_1)
        {
            switch (m_pPlayer->GetAILevel())
            {
            case CPlayer::AI_LEVEL_1:
                GetAvoidTime();
                break;
            case CPlayer::AI_LEVEL_2:
                GetWaitTime();
                break;
            case CPlayer::AI_LEVEL_3:
                //// 現在のプレイヤー人数によって場合分け
                //if (CGame::GetNumCurrentDispPlayer() > 2)
                //{
                //    GetAvoidTime();
                //}
                //else
                //{
                //    GetAssaultTime();
                //}
                GetAssaultTime();
                break;
            }
        }
        else if (nRandNum > CORE_PRIORITY_1 && nRandNum <= CORE_PRIORITY_1 + CORE_PRIORITY_2)
        {
            switch (m_pPlayer->GetAILevel())
            {
            case CPlayer::AI_LEVEL_1:
                GetAssaultTime();
                break;
            case CPlayer::AI_LEVEL_2:
                GetAssaultTime();
                break;
            case CPlayer::AI_LEVEL_3:
                GetWaitTime();
                break;
            }
        }
        else if (nRandNum > CORE_PRIORITY_1 + CORE_PRIORITY_2
            && nRandNum <= CORE_PRIORITY_1 + CORE_PRIORITY_2 + CORE_PRIORITY_3)
        {
            switch (m_pPlayer->GetAILevel())
            {
            case CPlayer::AI_LEVEL_1:
                GetWaitTime();
                break;
            case CPlayer::AI_LEVEL_2:
                GetAvoidTime();
                break;
            case CPlayer::AI_LEVEL_3:
                //// 現在のプレイヤー人数によって場合分け
                //if (CGame::GetNumCurrentDispPlayer() > 2)
                //{
                //    GetAssaultTime();
                //}
                //else
                //{
                //    GetAvoidTime();
                //}
                GetAvoidTime();
                break;
            }
        }
    }
}

//=============================================================================
// 考える以外の行動中
// Author : 後藤慎之助
//=============================================================================
void CAi::AnotherAction(void)
{
    // 時間を数える
    m_nCntActionTime--;

    // 一定カウンタで、一回考える
    if (m_nCntActionTime < 0)
    {
        GetThinkingTime();
    }
}

//=============================================================================
// 考え時間を得る処理
// Author : 後藤慎之助
//=============================================================================
void CAi::GetThinkingTime(void)
{
    // コアを考え中に
    m_core = CORE_THINKING;

    // レベルに応じて考え時間を得る
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(THINKING_TIME_AI_LEVEL_1_MAX, THINKING_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(THINKING_TIME_AI_LEVEL_2_MAX, THINKING_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(THINKING_TIME_AI_LEVEL_3_MAX, THINKING_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// 強襲時間を得る処理
// Author : 後藤慎之助
//=============================================================================
void CAi::GetAssaultTime(void)
{
    // コアを強襲に
    m_core = CORE_ASSAULT;

    // レベルに応じて考え時間を得る
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(ASSAULT_TIME_AI_LEVEL_1_MAX, ASSAULT_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(ASSAULT_TIME_AI_LEVEL_2_MAX, ASSAULT_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(ASSAULT_TIME_AI_LEVEL_3_MAX, ASSAULT_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// 避ける時間を得る処理
// Author : 後藤慎之助
//=============================================================================
void CAi::GetAvoidTime(void)
{
    // コアを避けに
    m_core = CORE_AVOID;

    // レベルに応じて考え時間を得る
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(AVOID_TIME_AI_LEVEL_1_MAX, AVOID_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(AVOID_TIME_AI_LEVEL_2_MAX, AVOID_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(AVOID_TIME_AI_LEVEL_3_MAX, AVOID_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// 待つ時間を得る処理
// Author : 後藤慎之助
//=============================================================================
void CAi::GetWaitTime(void)
{
    // コアを待機中に
    m_core = CORE_WAIT;

    // レベルに応じて考え時間を得る
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntActionTime = GetRandNum(WAIT_TIME_AI_LEVEL_1_MAX, WAIT_TIME_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntActionTime = GetRandNum(WAIT_TIME_AI_LEVEL_2_MAX, WAIT_TIME_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntActionTime = GetRandNum(WAIT_TIME_AI_LEVEL_3_MAX, WAIT_TIME_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// 移動しない処理
// Author : 後藤慎之助
//=============================================================================
void CAi::DontMove(bool bUseTurn)
{
    //m_pPlayer->GetControlInput()->bTiltedLeftStick = false;

    //// 移動しない程度に敵を振り向くなら
    //if (bUseTurn)
    //{
    //    // 敵のほうを向いていないならそちらを向く
    //    if (!IsFacingBall())
    //    {
    //        // ボールを取得
    //        CBall* pBall = CGame::GetBall();
    //        float fAngle = GetAngleToTarget3D2D(m_pPlayer->GetPos(), pBall->GetPos());

    //        m_pPlayer->GetControlInput()->bTiltedLeftStick = true;
    //        m_pPlayer->GetControlInput()->fLeftStickAngle = fAngle;
    //    }
    //}
}

//=============================================================================
// 敵の方を向いているか
// Author : 後藤慎之助
//=============================================================================
bool CAi::IsFacingEnemy(void)
{
    //// ボールを取得
    //CBall* pBall = CGame::GetBall();

    //// ボールのほうを向いていない
    //if (pBall->GetPos().x > m_pPlayer->GetPos().x && m_pPlayer->GetRot().y == PLAYER_ROT_LEFT ||
    //    pBall->GetPos().x < m_pPlayer->GetPos().x && m_pPlayer->GetRot().y == PLAYER_ROT_RIGHT)
    //{
    //    return false;
    //}

    // ボールの方を向いている
    return true;
}

//=============================================================================
// ターゲットに詰め寄る処理
// Author : 後藤慎之助
//=============================================================================
void CAi::RushToTarget(void)
{
    // ターゲットへの角度を取得
    float fAngle = GetAngleToTargetXZ(m_pPlayer->GetPos(), m_targetPos);
    float fPlayerAngle = GetAngleToTargetXZ(m_targetPos, m_pPlayer->GetPos());

    m_pPlayer->GetControlInput()->bTiltedLeftStick = true;
    m_pPlayer->GetControlInput()->fLeftStickAngle = fAngle;
    m_pPlayer->GetControlInput()->fPlayerAngle = fPlayerAngle;
}

//=============================================================================
// ボールから逃げる処理
// Author : 後藤慎之助
//=============================================================================
void CAi::RunAwayFromBall(void)
{
    //// ボールを取得
    //CBall* pBall = CGame::GetBall();
    //float fAngle = GetAngleToTarget3D2D(pBall->GetPos(), m_pPlayer->GetPos());

    //// 右か左に角度調整
    //if (fAngle > D3DXToRadian(0.0f) && fAngle <= D3DXToRadian(180.0f))
    //{
    //    fAngle = D3DXToRadian(90.0f);
    //}
    //else
    //{
    //    fAngle = D3DXToRadian(-90.0f);
    //}

    //// ステージの横幅の約半分まで離れたら、強制的に考える（レベル3は待ちにする）
    //float fDistance = GetDistance2D(m_pPlayer->GetPos(), CGame::GetBall()->GetPos());
    //if (fDistance >= CGame::GetMapLimit().fWidth - BALL_COLLISION_SIZE_SIDE)
    //{
    //    if (m_pPlayer->GetAILevel() == CPlayer::AI_LEVEL_3)
    //    {
    //        // 乱戦時は待ったほうが強い
    //        GetWaitTime();

    //        // 向いている方向に入力させる
    //        if (m_pPlayer->GetRot().y == PLAYER_ROT_LEFT)
    //        {
    //            fAngle = D3DXToRadian(-90.0f);
    //        }
    //        else if (m_pPlayer->GetRot().y == PLAYER_ROT_RIGHT)
    //        {
    //            fAngle = D3DXToRadian(90.0f);
    //        }
    //    }
    //    else
    //    {
    //        GetThinkingTime();
    //    }
    //}

    //// プレイヤーの入力に反映
    //m_pPlayer->GetControlInput()->bTiltedLeftStick = true;
    //m_pPlayer->GetControlInput()->fLeftStickAngle = fAngle;
}

//=============================================================================
// 敵の弾が近いからジャンプする処理
// Author : 後藤慎之助
//=============================================================================
bool CAi::JumpBecauseEnemyBulletClose(void)
{
    // ジャンプするかどうか
    bool bUseJump = false;

    // 敵の弾が近いならジャンプ
    if (CGame::GetDistanceToClosestEnemyBullet(m_pPlayer->GetPos()) < BULLET_CLOSE_VALUE)
    {
        bUseJump = true;
    }

    // 地上にいて、ジャンプボタンを長押ししようとしているなら、長押し解除
    if (m_pPlayer->GetGround() && m_buttonStateOld.bButtonA)
    {
        return false;
    }

    // 空中にいて、滞空が終了したなら、長押し解除
    if (m_pPlayer->GetPressJumpTime() > PLAYER_JUMP_KEEP_FRAME)
    {
        return false;
    }

    return bUseJump;
}

//=============================================================================
// ボールが下に移動してきているからジャンプする処理
// Author : 後藤慎之助
//=============================================================================
bool CAi::JumpBecauseBallMoveDown(void)
{
    // ジャンプするかどうか
    bool bUseJump = false;

    //// ボールを取得
    //CBall* pBall = CGame::GetBall();

    //// ボールが下に動いてるから
    //if (pBall->GetPosOld().y > pBall->GetPos().y)
    //{
    //    bUseJump = true;
    //}

    //// 地上にいて、ジャンプボタンを長押ししようとしているなら、長押し解除
    //if (m_pPlayer->GetGround() && m_buttonStateOld.bButtonA)
    //{
    //    return false;
    //}

    //// 空中にいて、滞空が終了したなら、長押し解除
    //if (m_pPlayer->GetPressJumpTime() > PLAYER_JUMP_KEEP_FRAME)
    //{
    //    return false;
    //}

    //// ボールが配置されていないなら、ジャンプしない
    //if (!pBall->GetDisp())
    //{
    //    return false;
    //}

    return bUseJump;
}

//=============================================================================
// 決めきる攻撃をするかどうかの処理
// Author : 後藤慎之助
//=============================================================================
bool CAi::DecideAttack(void)
{
    // 基本的な攻撃をするかどうか
    bool bUseDecideAttack = false;

    // 攻撃をすると判断する距離
    if (GetDistanceXZ(m_pPlayer->GetPos(), m_targetPos) <= m_fAttackRange)
    {
        bUseDecideAttack = true;
    }

    // ハンター以外は、キープレスでの攻撃がない（タンクは要変更）
    if (m_pPlayer->GetRole() != CPlayer::ROLE_HUNTER)
    {
        if (m_buttonStateOld.bButtonX)
        {
            return false;
        }
    }

    return bUseDecideAttack;
}

//=============================================================================
// 攻撃時にどの方向にスティックを倒すを倒すか
// Author : 後藤慎之助
//=============================================================================
void CAi::GetAttackAngle(void)
{
    //// スティックを倒すのは確定
    //m_pPlayer->GetControlInput()->bTiltedLeftStick = true;

    //// ランダムに数字を決める
    //int nRandNum = GetRandNum(100, 1);
    //int nBorderNum = 0;

    //switch (m_pPlayer->GetAILevel())
    //{
    //case CPlayer::AI_LEVEL_1:
    //    nBorderNum = ATTACK_TARGET_AI_LEVEL_1;
    //    break;
    //case CPlayer::AI_LEVEL_2:
    //    nBorderNum = ATTACK_TARGET_AI_LEVEL_2;
    //    break;
    //case CPlayer::AI_LEVEL_3:
    //    nBorderNum = ATTACK_TARGET_AI_LEVEL_3;
    //    break;
    //}

    //// 境界の値の範囲内なら、近くの敵を狙った角度に倒す（レベル3だけ精度がアップ）
    //float fAttackAngle = 0.0f;
    //CBall* pBall = CGame::GetBall();
    //if (nRandNum >= 1 && nRandNum <= nBorderNum)
    //{
    //    switch (m_pPlayer->GetAILevel())
    //    {
    //    case CPlayer::AI_LEVEL_1:
    //    case CPlayer::AI_LEVEL_2:
    //        fAttackAngle = CGame::GetAngleToClosestPlayer(m_pPlayer->GetIdxCreate(), m_pPlayer->GetPos());   //（自分と対象プレイヤーの角度）
    //        break;
    //    case CPlayer::AI_LEVEL_3:
    //        // 打ち始めなら、空中と地上で攻撃を使い分ける
    //        if (m_pPlayer->GetStopTime() == 0)
    //        {
    //            if (m_pPlayer->GetGround())
    //            {
    //                // スイング（上入力でなる）
    //                fAttackAngle = D3DXToRadian(0.0f);
    //            }
    //            else
    //            {
    //                // 空中なら、ボールとの位置関係で使う攻撃を変える
    //                if (pBall->GetPos().y > m_pPlayer->GetPos().y + m_pPlayer->GetCollisionSizeDeffence().y)
    //                {
    //                    // スマッシュ（向きも合わせる）
    //                    if (pBall->GetPos().x > m_pPlayer->GetPos().x)
    //                    {
    //                        fAttackAngle = D3DXToRadian(90.0f);
    //                    }
    //                    else
    //                    {
    //                        fAttackAngle = D3DXToRadian(-90.0f);
    //                    }
    //                }
    //                else if (pBall->GetPos().y < m_pPlayer->GetPos().y)
    //                {
    //                    // スパイク
    //                    fAttackAngle = D3DXToRadian(180.0f);
    //                }
    //                else
    //                {
    //                    // スイング（上入力でなる）
    //                    fAttackAngle = D3DXToRadian(0.0f);
    //                }
    //            }
    //        }
    //        else if (m_pPlayer->GetStopTime() == 1)
    //        {
    //            // 飛ばすときは、近くの敵を狙う（ボールと対象プレイヤーの角度）
    //            fAttackAngle = GetAngleToTarget3D2D(pBall->GetPos(),
    //                CGame::GetPosToClosestPlayer(m_pPlayer->GetIdxCreate(), m_pPlayer->GetPos()));
    //        }
    //        break;
    //    }
    //}
    //else
    //{
    //    // 範囲外なら、適当にスティックを倒す
    //    fAttackAngle = float(rand() % 314) / 100 - float(rand() % 314) / 100;
    //}

    //// 得た攻撃角度を結びつける
    //m_pPlayer->GetControlInput()->fLeftStickAngle = fAttackAngle;
}

//=============================================================================
// 標的の位置取得
// Author : 後藤慎之助
//=============================================================================
void CAi::GetTargetPos(void)
{
    // 何を標的とみなすかによって、得る位置が変わる
    if (m_pPlayer->GetCurrentEnergy() >= m_pPlayer->GetCurrentEnergyMax())
    {
        // エナジー量が最大に達していたら、移動要塞を狙う
        m_targetPos = CGame::GetFortress()->GetPos();
        m_fAttackRange = 0.0f;
    }
    else
    {
        // 近くの敵
        m_targetPos = CGame::GetPosToClosestEnemy(m_pPlayer->GetPos());

        if (m_targetPos == DEFAULT_VECTOR)
        {
            // 敵がいないときは、移動要塞を狙う
            m_targetPos = CGame::GetFortress()->GetPos();
            m_fAttackRange = -100.0f;
        }
        else
        {
            GetAttackRange();
        }
    }

    // 次の標的取得時間を得る
    switch (m_pPlayer->GetAILevel())
    {
    case CPlayer::AI_LEVEL_1:
        m_nCntSearchTarget = GetRandNum(TARGETTING_INTERVAL_AI_LEVEL_1_MAX, TARGETTING_INTERVAL_AI_LEVEL_1_MIN);
        break;
    case CPlayer::AI_LEVEL_2:
        m_nCntSearchTarget = GetRandNum(TARGETTING_INTERVAL_AI_LEVEL_2_MAX, TARGETTING_INTERVAL_AI_LEVEL_2_MIN);
        break;
    case CPlayer::AI_LEVEL_3:
        m_nCntSearchTarget = GetRandNum(TARGETTING_INTERVAL_AI_LEVEL_3_MAX, TARGETTING_INTERVAL_AI_LEVEL_3_MIN);
        break;
    }
}

//=============================================================================
// 攻撃の射程の取得
// Author : 後藤慎之助
//=============================================================================
void CAi::GetAttackRange(void)
{
    switch (m_pPlayer->GetRole())
    {
    case CPlayer::ROLE_WARRIOR:
        m_fAttackRange = ATTACK_RANGE_WARRIOR;
        break;
    case CPlayer::ROLE_HUNTER:
        m_fAttackRange = ATTACK_RANGE_HUNTER;
        break;
    case CPlayer::ROLE_CARRIER:
        m_fAttackRange = ATTACK_RANGE_CARRIER;
        break;
    case CPlayer::ROLE_TANK:
        m_fAttackRange = ATTACK_RANGE_TANK;
        break;
    case CPlayer::ROLE_HEALER:
        m_fAttackRange = ATTACK_RANGE_HEALER;
        break;
    }
}