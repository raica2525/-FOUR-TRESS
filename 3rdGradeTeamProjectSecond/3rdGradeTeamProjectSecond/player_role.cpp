//======================================================================================
//
// プレイヤーの役割ごとの処理 (player_role.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "player.h"
#include "debug.h"
#include "enemy.h"
#include "animation.h"
#include "fortress.h"
#include "game.h"
#include "bullet.h"
#include "item.h"
#include "modelEffect.h"
#include "wave.h"
#include "manager.h"
#include "camera.h"

//========================================
// マクロ定義
//========================================

// 近距離攻撃のフラグ
typedef enum
{
    CLOSE_ATTACK_FLAG_NONE = 0,             // なし
    CLOSE_ATTACK_FLAG_TAUNT = 0x001 << 1,   // 挑発
}CLOSE_ATTACK_FLAG;

//==========================
// ウォーリアー地上
//==========================
// 基本ダメージ
#define WARRIOR_GROUND_BASE_DAMAGE 100.0f
// 当たり判定周り
#define WARRIOR_GROUND_EMIT_DISTANCE 375.0f
#define WARRIOR_GROUND_RADIUS 500.0f
#define WARRIOR_GROUND_HEIGHT 350.0f
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define WARRIOR_GROUND_WHOLE_FRAME 25
#define WARRIOR_GROUND_START_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 10)
#define WARRIOR_GROUND_END_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 20)
// 硬直フレーム
#define WARRIOR_GROUND_STOP_FRAME 5
// その他
#define WARRIOR_GROUND_DUSH_SPEED 25.0f
#define WARRIOR_GROUND_COMBO_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 10)
#define WARRIOR_GROUND_SLIDE_SPEED 10.0f

//==========================
// ウォーリアー空中
//==========================
// 基本ダメージ
#define WARRIOR_SKY_BASE_DAMAGE 300.0f
// 当たり判定周り
#define WARRIOR_SKY_EMIT_DISTANCE -500.0f
#define WARRIOR_SKY_RADIUS 750.0f
#define WARRIOR_SKY_HEIGHT 500.0f
// 全体フレーム、攻撃発生フレーム
#define WARRIOR_SKY_WHOLE_FRAME 9999
#define WARRIOR_SKY_START_FRAME (WARRIOR_SKY_WHOLE_FRAME - 23)
// その他
#define WARRIOR_SKY_UP_VALUE 20.0f
#define WARRIOR_SKY_CHANCE_FRAME 30

//==========================
// ハンター地上
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define HUNTER_GROUND_WHOLE_FRAME 20
#define HUNTER_GROUND_FIRE_FRAME (HUNTER_GROUND_WHOLE_FRAME - 10)

//==========================
// ハンター空中
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define HUNTER_SKY_WHOLE_FRAME 50
#define HUNTER_SKY_FIRE_FRAME (HUNTER_SKY_WHOLE_FRAME - 35)
// その他
#define HUNTER_SKY_MOVE_LIMIT 0.5f
#define HUNTER_SKY_ONCE_SHOT 4
#define HUNTER_SKY_ANGLE_Y D3DXToRadian(50.0f)
#define HUNTER_SKY_TARGETING_FRAME (HUNTER_SKY_WHOLE_FRAME - 1)
// 汎用パラメータの内訳
typedef enum
{
    PARAM_HUNTER_TARGET_POS_X = 0,
    PARAM_HUNTER_TARGET_POS_Y,
    PARAM_HUNTER_TARGET_POS_Z,
}PARAM_HUNTER;

//==========================
// キャリアー地上
//==========================
// 基本ダメージ
#define CARRIER_GROUND_BASE_DAMAGE 70.0f
// 当たり判定周り
#define CARRIER_GROUND_RADIUS 450.0f
#define CARRIER_GROUND_HEIGHT 300.0f
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define CARRIER_GROUND_WHOLE_FRAME 70
#define CARRIER_GROUND_START_FRAME (CARRIER_GROUND_WHOLE_FRAME - 30)
#define CARRIER_GROUND_END_FRAME (CARRIER_GROUND_WHOLE_FRAME - 40)
// その他
#define CARRIER_GROUND_DUSH_SPEED 150.0f
#define CARRIER_GROUND_CREATE_ENERGY 1.0f
#define CARRIER_GROUND_CREATE_AFTERIMAGE_FRAME 2
#define CARRIER_GROUND_AFTERIMAGE_COLOR D3DXCOLOR(0.694f, 0.298f, 1.0f, 1.0f)
#define CARRIER_GROUND_AFTERIMAGE_COLOR_CHANGE_RATE D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.04f)
#define CARRIER_GROUND_COMBO_FRAME (CARRIER_GROUND_WHOLE_FRAME - 50)
#define CARRIER_GROUND_SECOND_ATTACK_WHOLE_FRAME 40

//==========================
// キャリアー空中
//==========================
// 基本ダメージ
#define CARRIER_SKY_BASE_DAMAGE 150.0f
// 当たり判定周り
#define CARRIER_SKY_EMIT_DISTANCE -200.0f
#define CARRIER_SKY_RADIUS 700.0f
#define CARRIER_SKY_HEIGHT 450.0f
// 全体フレーム、攻撃発生フレーム
#define CARRIER_SKY_WHOLE_FRAME 9999
#define CARRIER_SKY_START_ATTACK_FRAME (CARRIER_SKY_WHOLE_FRAME - 35)
#define CARRIER_SKY_START_WIND_FRAME (CARRIER_SKY_WHOLE_FRAME - 15)
// その他
#define CARRIER_SKY_UP_VALUE 20.0f
#define CARRIER_SKY_CHANCE_FRAME 35

//==========================
// タンク地上1_盾構え
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define TANK_GROUND1_WHOLE_FRAME 380
#define TANK_GROUND1_CREATE_SHIELD_FRAME (TANK_GROUND1_WHOLE_FRAME - 20)
// その他
#define TANK_GROUND1_WALK_SPEED 8.5f
#define TANK_GROUND1_LV2 3
#define TANK_GROUND1_LV3 10
// 汎用パラメータの内訳
typedef enum
{
    PARAM_TANK_GUARD_WIDTH = 0,
}PARAM_TANK;

//==========================
// タンク地上2_爆発弾
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define TANK_GROUND2_WHOLE_FRAME 40
#define TANK_GROUND2_FIRE_FRAME (TANK_GROUND2_WHOLE_FRAME - 20)

//==========================
// タンク空中
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define TANK_SKY_WHOLE_FRAME 80
#define TANK_SKY_START_FRAME (TANK_SKY_WHOLE_FRAME - 20)
#define TANK_SKY_END_FRAME (TANK_SKY_WHOLE_FRAME - 60)
// 当たり判定周り
#define TANK_SKY_RADIUS 7500.0f
#define TANK_SKY_HEIGHT 500.0f
// その他
#define TANK_SKY_FALL_VALUE -15.0f

//==========================
// ヒーラー地上
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define HEALER_GROUND_WHOLE_FRAME 50
#define HEALER_GROUND_FIRE_FRAME (HEALER_GROUND_WHOLE_FRAME - 25)
// その他
#define HEALER_GROUND_BASE_DAMAGE 40.0f
#define HEALER_GROUND_ADD_DAMAGE_RATE 1.0f
#define HEALER_GROUND_BASE_HEALING 20.0f
#define HEALER_GROUND_ADD_HEALING_RATE 0.5f

//==========================
// ヒーラー空中
//==========================
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define HEALER_SKY_WHOLE_FRAME 90
#define HEALER_SKY_START_FRAME (HEALER_SKY_WHOLE_FRAME - 40)
#define HEALER_SKY_END_FRAME (HEALER_SKY_WHOLE_FRAME - 70)
// 当たり判定周り
#define HEALER_SKY_EMIT_DISTANCE 1000.0f
#define HEALER_SKY_MOVE_LIMIT 0.25f
// その他
#define HEALER_SKY_BASE_DAMAGE 30.0f
#define HEALER_SKY_ADD_DAMAGE_RATE 0.75f
#define HEALER_SKY_BASE_HEALING 15.0f
#define HEALER_SKY_ADD_HEALING_RATE 0.375f

//=============================================================================
// 攻撃更新処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AttackUpdate(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // 負傷していないなら
    if (GetDamageState() == DAMAGE_STATE_NONE)
    {
        // 使う技によって処理が異なる
        switch (m_attackState)
        {
        case ATTACK_STATE_WARRIOR_GROUND1:
            AtkWarriorGround1(playerPos);
            break;
        case ATTACK_STATE_WARRIOR_GROUND2:
            AtkWarriorGround2(playerPos);
            break;
        case ATTACK_STATE_WARRIOR_SKY:
            AtkWarriorSky(playerPos, move);
            break;
        case ATTACK_STATE_HUNTER_GROUND:
            AtkHunterGround(playerPos);
            break;
        case ATTACK_STATE_HUNTER_SKY:
            AtkHunterSky(playerPos, move);
            break;
        case ATTACK_STATE_CARRIER_GROUND1:
            AtkCarrierGround1(playerPos);
            break;
        case ATTACK_STATE_CARRIER_GROUND2:
            AtkCarrierGround2(playerPos);
            break;
        case ATTACK_STATE_CARRIER_SKY:
            AtkCarrierSky(playerPos, move);
            break;
        case ATTACK_STATE_TANK_GROUND1:
            AtkTankGround1(playerPos);
            break;
        case ATTACK_STATE_TANK_GROUND2:
            AtkTankGround2(playerPos);
            break;
        case ATTACK_STATE_TANK_SKY:
            AtkTankSky(playerPos, move);
            break;
        case ATTACK_STATE_SIT_DOWN:
            AtkSitDown(playerPos, move);
            break;
        case ATTACK_STATE_HEALER_GROUND:
            AtkHealerGround(playerPos);
            break;
        case ATTACK_STATE_HEALER_SKY:
            AtkHealerSky(playerPos, move);
            break;
        }
    }
}

//=============================================================================
// 攻撃発生処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AttackGenerator(void)
{
    // 負傷していない状態かつ、攻撃中でないなら
    if (GetDamageState() == DAMAGE_STATE_NONE && m_attackState == ATTACK_STATE_NONE)
    {
        // 地上にいるなら
        if (m_bGround)
        {
            // 通常攻撃ボタンを押したら、各役割によって使う攻撃を変える
            if (m_controlInput.bTriggerX)
            {
                switch (m_role)
                {
                case ROLE_WARRIOR:
                    m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
                    break;
                case ROLE_CARRIER:
                    m_nCntAttackTime = CARRIER_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_CARRIER_GROUND1;
                    break;
                case ROLE_TANK:
                    m_nCntAttackTime = TANK_GROUND1_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_TANK_GROUND1;
                    break;
                case ROLE_HEALER:
                    m_nCntAttackTime = HEALER_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HEALER_GROUND;
                    break;
                }
            }
            else if (m_controlInput.bPressX)
            {
                // 連続攻撃系
                switch (m_role)
                {
                case ROLE_HUNTER:
                    m_nCntAttackTime = HUNTER_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HUNTER_GROUND;
                    break;
                }
            }
            else if (m_controlInput.bTriggerB)
            {
                // 移動要塞に乗る
                RideFortress();
            }
        }
        else
        {
            // 通常攻撃ボタンを押したら、各役割によって使う攻撃を変える
            if (m_controlInput.bTriggerX)
            {
                switch (m_role)
                {
                case ROLE_WARRIOR:
                    m_nCntAttackTime = WARRIOR_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_WARRIOR_SKY;
                    break;
                case ROLE_HUNTER:
                    m_nCntAttackTime = HUNTER_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HUNTER_SKY;
                    break;
                case ROLE_CARRIER:
                    m_nCntAttackTime = CARRIER_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_CARRIER_SKY;
                    break;
                case ROLE_TANK:
                    m_nCntAttackTime = TANK_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_TANK_SKY;
                    break;
                case ROLE_HEALER:
                    m_nCntAttackTime = HEALER_SKY_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_HEALER_SKY;
                    break;
                }
            }
            else if (m_controlInput.bTriggerB)
            {
                // 移動要塞に乗る
                RideFortress();
            }
        }
    }
}

//=============================================================================
// 攻撃モーションの管理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AttackMotion(void)
{
    // 攻撃状態に応じて、モーションを決める
    switch (m_attackState)
    {
    case ATTACK_STATE_WARRIOR_GROUND1:
        GetAnimation()->SetAnimation(ANIM_WARRIOR_GROUND1);
        break;
    case ATTACK_STATE_WARRIOR_GROUND2:
        GetAnimation()->SetAnimation(ANIM_WARRIOR_GROUND2);
        break;
    case ATTACK_STATE_WARRIOR_SKY:
        GetAnimation()->SetAnimation(ANIM_WARRIOR_SKY);
        break;
    case ATTACK_STATE_HUNTER_GROUND:
        GetAnimation()->SetAnimation(ANIM_HUNTER_GROUND);
        break;
    case ATTACK_STATE_HUNTER_SKY:
        GetAnimation()->SetAnimation(ANIM_HUNTER_SKY);
        break;
    case ATTACK_STATE_CARRIER_GROUND1:
        GetAnimation()->SetAnimation(ANIM_CARRIER_GROUND);
        break;
    case ATTACK_STATE_CARRIER_GROUND2:
        GetAnimation()->SetAnimation(ANIM_CARRIER_GROUND);
        break;
    case ATTACK_STATE_CARRIER_SKY:
        GetAnimation()->SetAnimation(ANIM_CARRIER_SKY);
        break;
    case ATTACK_STATE_TANK_GROUND1:
        GetAnimation()->SetAnimation(ANIM_TANK_GROUND1);
        break;
    case ATTACK_STATE_TANK_GROUND2:
        GetAnimation()->SetAnimation(ANIM_TANK_GROUND2);
        break;
    case ATTACK_STATE_TANK_SKY:
        GetAnimation()->SetAnimation(ANIM_TANK_SKY);
        break;
    case ATTACK_STATE_HEALER_GROUND:
        GetAnimation()->SetAnimation(ANIM_HEALER_GROUND);
        break;
    case ATTACK_STATE_HEALER_SKY:
        GetAnimation()->SetAnimation(ANIM_HEALER_SKY);
        break;
    case ATTACK_STATE_SIT_DOWN:
        GetAnimation()->SetAnimation(ANIM_SIT_DOWN);
        break;
    }
}

//=============================================================================
// 近接攻撃が当たったかどうかのチェック
// Author : 後藤慎之助
//=============================================================================
bool CPlayer::IsHitCloseRangeAttack(D3DXVECTOR3 playerPos, D3DXVECTOR3 attackPos, D3DXVECTOR2 attackSize, float fPower, int flag, int hitEffect)
{
    // 防御当たり判定の大きさを取得
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

    // 当たったかどうか
    bool bHit = false;

    // 敵との当たり判定
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

            // 出現していないなら、次へ
            if (pEnemy->GetAppearState() != CEnemy::APPEAR_STATE_EXIST)
            {
                // 次のシーンにする
                pScene = pNextScene;
                continue;
            }

            // 敵のインデックスを取得
            int nIdx = pEnemy->GetIdx();
            if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
            {
                continue;
            }

            // 多段ヒット回避用フラグがfalseなら
            if (!m_abUseAvoidMultipleHits[nIdx])
            {
                // 当たっているなら
                if (IsCollisionCylinder(attackPos, attackSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                {
                    // 挑発フラグがあるなら
                    if (IS_BITON(flag, CLOSE_ATTACK_FLAG_TAUNT))
                    {
                        // 挑発状態にする
                        pEnemy->DiscoveryTarget((CCharacter*)this);

                        // 当たった
                        bHit = true;

                        // 多段ヒット回避用のフラグをtrueに
                        m_abUseAvoidMultipleHits[nIdx] = true;
                    }
                    else
                    {
                        // 敵にダメージが入ったら
                        if (pEnemy->TakeDamage(fPower, attackPos, playerPos, OBJTYPE_PLAYER, true, hitEffect))
                        {
                            // 貢献した人を設定
                            pEnemy->SetWhoContribution(m_nIdxCreate);

                            // 当たった
                            bHit = true;

                            // 多段ヒット回避用のフラグをtrueに
                            m_abUseAvoidMultipleHits[nIdx] = true;
                        }
                    }
                }
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
    }

    return bHit;
}

//=============================================================================
// 移動要塞に乗る処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::RideFortress(void)
{
    if (!m_bGetOffFortressInThisFrame)
    {
        // 移動要塞を取得
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            // 誰も座っていないなら
            if (!pFortress->GetNowWhoRiding())
            {
                // 当たっているなら
                if (IsCollisionCylinder(GetPos(), GetCollisionSizeDefence(), pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
                {
                    // 座る（攻撃時間を設定しないことで、一定時間で攻撃をリセットするフラグを立たせない）
                    m_attackState = ATTACK_STATE_SIT_DOWN;
                    pFortress->SetNowWhoRiding(true);
                }
            }
        }
    }
}

//=============================================================================
// 移動要塞に座って攻撃する処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkSitDown(D3DXVECTOR3 &playerPos, D3DXVECTOR3& move)
{
    // この攻撃中は無敵
    SetInvincible(true);

    // 武器は見えない
    SetPartsDisp(PARTS_WEP, false);

    // 移動要塞を取得
    CFortress *pFortress = CGame::GetFortress();
    if (pFortress)
    {
        if (pFortress->GetDisp())
        {
            // 自身の位置を、座席にする
            playerPos = pFortress->GetPartsPos(CFortress::PARTS_SEAT);

            // 移動量を念のためリセットする
            move = DEFAULT_VECTOR;

            // 向きを合わせる
            SetRotDest(pFortress->GetRot());
            SetRot(pFortress->GetRot());
        }
        else
        {
            // 移動要塞がないなら、強制で降りる
            ResetAttack();
            m_bGetOffFortressInThisFrame = true;
            return;
        }
    }

    // 電力消費攻撃
    if (m_controlInput.bTriggerX)
    {
        if (pFortress)
        {
            pFortress->SetAttackPhase(true, m_nIdxCreate);
        }
    }
    else if (m_controlInput.bTriggerB)
    {
        // 攻撃フェーズ中は降りられない
        if (!pFortress->GetAttackPhase())
        {
            // 降りる処理（攻撃周りをリセット）
            ResetAttack();
            m_bGetOffFortressInThisFrame = true;

            // 移動要塞側の座っているフラグを戻す
            pFortress->SetNowWhoRiding(false);
        }
    }
}

//=============================================================================
// ウォーリアー地上攻撃1
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkWarriorGround1(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= WARRIOR_GROUND_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND_END_FRAME)
    {
        // 素振り音
        CManager::SoundPlay(CSound::LABEL_SE_SWISH);

        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // プレイヤーの向いている向き
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                            // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                           // 攻撃発生位置
        float fFinalPower = 0.0f;                                         // 最終的な攻撃力
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND_EMIT_DISTANCE;  // 攻撃発生距離
        const float ATTACK_RADIUS = WARRIOR_GROUND_RADIUS;                // 攻撃の大きさ
        const float ATTACK_HEIGHT = WARRIOR_GROUND_HEIGHT;                // 攻撃の高さ
        const float BASE_DAMAGE = WARRIOR_GROUND_BASE_DAMAGE;             // 基本ダメージ

        // 攻撃発生位置をずらす
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // 攻撃発生位置を決める
        attackPos = playerPos + slidePos;

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        //// 移動できる
        //if (m_controlInput.bTiltedLeftStick)
        //{
        //    playerPos.x += sinf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
        //    playerPos.z += cosf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
        //}

        // 前進
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;

        // 当たったかどうか（ヒットエフェクトは、ここの引数に）
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower, 0, CEffectData::TYPE_THRUST))
        {
            m_nCntStopTime = WARRIOR_GROUND_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime == 1)
    {
        if (m_bBurstAttack)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_WARRIOR_GROUND2;

            // 向きを即座に変えれる
            if (!m_controlInput.bPressR2)
            {
                SetRotY(m_controlInput.fPlayerAngle);
                SetRotDestY(m_controlInput.fPlayerAngle);
            }
        }
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= WARRIOR_GROUND_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            // 連続攻撃のフラグを立てる
            m_bBurstAttack = true;
        }
    }
}

//=============================================================================
// ウォーリアー地上攻撃2
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkWarriorGround2(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= WARRIOR_GROUND_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND_END_FRAME)
    {
        // 素振り音
        CManager::SoundPlay(CSound::LABEL_SE_SWISH);

        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // プレイヤーの向いている向き
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                            // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                           // 攻撃発生位置
        float fFinalPower = 0.0f;                                         // 最終的な攻撃力
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND_EMIT_DISTANCE;  // 攻撃発生距離
        const float ATTACK_RADIUS = WARRIOR_GROUND_RADIUS;                // 攻撃の大きさ
        const float ATTACK_HEIGHT = WARRIOR_GROUND_HEIGHT;                // 攻撃の高さ
        const float BASE_DAMAGE = WARRIOR_GROUND_BASE_DAMAGE;             // 基本ダメージ

        // 攻撃発生位置をずらす
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // 攻撃発生位置を決める
        attackPos = playerPos + slidePos;

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        //// 移動できる
        //if (m_controlInput.bTiltedLeftStick)
        //{
        //    playerPos.x += sinf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
        //    playerPos.z += cosf(m_controlInput.fLeftStickAngle)*WARRIOR_GROUND_SLIDE_SPEED;
        //}

        // 前進
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;

        // 当たったかどうか（ヒットエフェクトは、ここの引数に）
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower, 0, CEffectData::TYPE_THRUST))
        {
            m_nCntStopTime = WARRIOR_GROUND_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime == 1)
    {
        if (m_bBurstAttack)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_SKY_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_WARRIOR_SKY;

            // 向きを即座に変えれる
            if (!m_controlInput.bPressR2)
            {
                SetRotY(m_controlInput.fPlayerAngle);
                SetRotDestY(m_controlInput.fPlayerAngle);
            }
        }
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= WARRIOR_GROUND_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            // 連続攻撃のフラグを立てる
            m_bBurstAttack = true;
        }
    }
}

//=============================================================================
// ウォーリアー空中攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkWarriorSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= WARRIOR_SKY_START_FRAME &&
        m_nCntAttackTime > WARRIOR_SKY_CHANCE_FRAME)
    {
        // 着地したら、隙が発生し、攻撃は終了
        if (m_bGround)
        {
            // カメラの振動
            CManager::GetCamera()->CCamera::SetShake(250.0f);

            // 着地音
            CManager::SoundPlay(CSound::LABEL_SE_JUMP_ATTACK_SWORD);

            m_nCntAttackTime = WARRIOR_SKY_CHANCE_FRAME;

            // 空中攻撃のエフェクト
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_0, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_0, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_1, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_2, playerPos, playerPos);

        }
        // 防御当たり判定の大きさを取得
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

        // 変数宣言
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
        float fFinalPower = 0.0f;                                          // 最終的な攻撃力
        const float ATTACK_EMIT_DISTANCE = WARRIOR_SKY_EMIT_DISTANCE;      // 攻撃発生距離
        const float ATTACK_RADIUS = WARRIOR_SKY_RADIUS;                    // 攻撃の大きさ
        const float ATTACK_HEIGHT = WARRIOR_SKY_HEIGHT;                    // 攻撃の高さ
        const float BASE_DAMAGE = WARRIOR_SKY_BASE_DAMAGE;                 // 基本ダメージ

        // 攻撃発生位置をずらす
        slidePos.y += ATTACK_EMIT_DISTANCE;

        // 攻撃発生位置を決める
        attackPos = playerPos + slidePos;

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        // 落下
        move.y -= WARRIOR_SKY_UP_VALUE;

        // 当たったかどうか
        IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower);

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > WARRIOR_SKY_START_FRAME)
    {
        playerPos.y += WARRIOR_SKY_UP_VALUE;
        move.y = WARRIOR_SKY_UP_VALUE;
    }
}

//=============================================================================
// ハンター地上攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkHunterGround(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレーム
    if (m_nCntAttackTime == HUNTER_GROUND_FIRE_FRAME)
    {
        // 射撃音
        CManager::SoundPlay(CSound::LABEL_SE_BOW_SOUND_EFFECT);

        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet *pBullet = CBullet::Create(CBullet::TYPE_HUNTER_GROUND, GetPartsPos(PARTS_WEP), moveAngle, OBJTYPE_PLAYER);
        pBullet->SetWhoContribution(m_nIdxCreate);
    }
    else if (m_nCntAttackTime > HUNTER_GROUND_FIRE_FRAME)
    {
        // キャラの向きを変える猶予フレーム
        SetRotDestY(m_controlInput.fPlayerAngle);
    }
}

//=============================================================================
// ハンター空中攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkHunterSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // 攻撃発生フレーム
    if (m_nCntAttackTime == HUNTER_SKY_FIRE_FRAME)
    {
        // 3射撃音
        CManager::SoundPlay(CSound::LABEL_SE_JUMP_ATTACK_BOW);

        // 一度に複数の矢を、均等に放つ
        for (int nCnt = 0; nCnt < HUNTER_SKY_ONCE_SHOT; nCnt++)
        {
            float fDigitAngle = (float)(nCnt + 1) * (D3DXToRadian(180.0f) / (float)(HUNTER_SKY_ONCE_SHOT + 1));
            float fAngleXZ = GetRot().y + fDigitAngle - D3DXToRadian(90.0f);
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(fAngleXZ), HUNTER_SKY_ANGLE_Y, -cosf(fAngleXZ));
            CBullet*pBullet = CBullet::Create(CBullet::TYPE_HUNTER_SKY, GetPartsPos(PARTS_WEP), moveAngle, OBJTYPE_PLAYER);
            D3DXVECTOR3 targetPos = D3DXVECTOR3(m_afParam[PARAM_HUNTER_TARGET_POS_X], m_afParam[PARAM_HUNTER_TARGET_POS_Y], m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
            pBullet->SetParam(0, m_afParam[PARAM_HUNTER_TARGET_POS_X]);
            pBullet->SetParam(1, m_afParam[PARAM_HUNTER_TARGET_POS_Y]);
            pBullet->SetParam(2, m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
            pBullet->SetWhoContribution(m_nIdxCreate);
        }
    }
    else if (m_nCntAttackTime > HUNTER_SKY_FIRE_FRAME)
    {
        // 移動制限
        move.x *= HUNTER_SKY_MOVE_LIMIT;
        move.z *= HUNTER_SKY_MOVE_LIMIT;
        move.y = 0.0f;

        // ターゲットの位置を決めるフレーム
        if (m_nCntAttackTime == HUNTER_SKY_TARGETING_FRAME)
        {
            // 位置を保存
            D3DXVECTOR3 targetPos = CGame::GetPosToClosestEnemy(playerPos, GetRot());
            m_afParam[PARAM_HUNTER_TARGET_POS_X] = targetPos.x;
            m_afParam[PARAM_HUNTER_TARGET_POS_Y] = targetPos.y;
            m_afParam[PARAM_HUNTER_TARGET_POS_Z] = targetPos.z;
            // キャラの向きをターゲットの方へ
            SetRotDestY(GetAngleToTargetXZ(targetPos, playerPos));
        }
    }
}

//=============================================================================
// キャリアー地上攻撃1
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkCarrierGround1(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= CARRIER_GROUND_START_FRAME &&
        m_nCntAttackTime >= CARRIER_GROUND_END_FRAME)
    {
        if (m_nCntAttackTime == CARRIER_GROUND_START_FRAME)
        {
            // 高速移動音
            CManager::SoundPlay(CSound::LABEL_SE_HIGH_SPEED_MOVE);
        }

        // この攻撃中は無敵
        SetInvincible(true);

        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // プレイヤーの向いている向き
        float fFinalPower = 0.0f;                                         // 最終的な攻撃力
        const float ATTACK_RADIUS = CARRIER_GROUND_RADIUS;                // 攻撃の大きさ
        const float ATTACK_HEIGHT = CARRIER_GROUND_HEIGHT;                // 攻撃の高さ
        const float BASE_DAMAGE = CARRIER_GROUND_BASE_DAMAGE;             // 基本ダメージ
        D3DXVECTOR3 posOld = GetPosOld();

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        // 前進
        playerPos.x += -sinf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;

        // 残像を残す
        if (m_nCntAttackTime % CARRIER_GROUND_CREATE_AFTERIMAGE_FRAME == 0)
        {
            CModelEffect*pAfterimage = CModelEffect::Create(27, posOld, playerRot, CARRIER_GROUND_AFTERIMAGE_COLOR, CARRIER_GROUND_AFTERIMAGE_COLOR_CHANGE_RATE, true);
            pAfterimage->SetAdditiveSynthesis();
        }

        // 当たったかどうか
        if (IsHitCloseRangeAttack(playerPos, playerPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            CItem::Create(CItem::TYPE_DENTI_5, posOld, CARRIER_GROUND_CREATE_ENERGY);
        }

#ifdef COLLISION_TEST
        CDebug::Create(playerPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > CARRIER_GROUND_START_FRAME)
    {
        // キャラの向きを変える猶予フレーム
        SetRotDestY(m_controlInput.fPlayerAngle);
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= CARRIER_GROUND_COMBO_FRAME)
    {
        // 左スティックが傾いているなら連撃
        if (m_controlInput.bTiltedLeftStick)
        {
            ResetAttack();
            m_nCntAttackTime = CARRIER_GROUND_SECOND_ATTACK_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_CARRIER_GROUND2;

            // 向きを即座に変えれる
            if (!m_controlInput.bPressR2)
            {
                SetRotY(m_controlInput.fPlayerAngle);
                SetRotDestY(m_controlInput.fPlayerAngle);
            }
        }
    }
}

//=============================================================================
// キャリアー地上攻撃2
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkCarrierGround2(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime >= CARRIER_GROUND_END_FRAME)
    {
        if (m_nCntAttackTime == CARRIER_GROUND_START_FRAME)
        {
            // 高速移動音
            CManager::SoundPlay(CSound::LABEL_SE_HIGH_SPEED_MOVE);
        }

        // この攻撃中は無敵
        SetInvincible(true);

        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                     // プレイヤーの向いている向き
        float fFinalPower = 0.0f;                                         // 最終的な攻撃力
        const float ATTACK_RADIUS = CARRIER_GROUND_RADIUS;                // 攻撃の大きさ
        const float ATTACK_HEIGHT = CARRIER_GROUND_HEIGHT;                // 攻撃の高さ
        const float BASE_DAMAGE = CARRIER_GROUND_BASE_DAMAGE;             // 基本ダメージ
        D3DXVECTOR3 posOld = GetPosOld();

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        // 前進
        playerPos.x += -sinf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(playerRot.y)*CARRIER_GROUND_DUSH_SPEED;

        // 残像を残す
        if (m_nCntAttackTime % CARRIER_GROUND_CREATE_AFTERIMAGE_FRAME == 0)
        {
            CModelEffect*pAfterimage = CModelEffect::Create(27, posOld, playerRot, CARRIER_GROUND_AFTERIMAGE_COLOR, CARRIER_GROUND_AFTERIMAGE_COLOR_CHANGE_RATE, true);
            pAfterimage->SetAdditiveSynthesis();
        }

        // 当たったかどうか
        if (IsHitCloseRangeAttack(playerPos, playerPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            CItem::Create(CItem::TYPE_DENTI_5, posOld, CARRIER_GROUND_CREATE_ENERGY);
        }

#ifdef COLLISION_TEST
        CDebug::Create(playerPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
}

//=============================================================================
// キャリアー空中攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkCarrierSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= CARRIER_SKY_START_ATTACK_FRAME &&
        m_nCntAttackTime > CARRIER_SKY_CHANCE_FRAME)
    {
        // 着地したら、隙が発生し、攻撃は終了
        if (m_bGround)
        {
            // カメラの振動
            CManager::GetCamera()->CCamera::SetShake(250.0f);

            // 着地音
            CManager::SoundPlay(CSound::LABEL_SE_JUMP_ATTACK_NAIL);

            m_nCntAttackTime = CARRIER_SKY_CHANCE_FRAME;

            // 空中攻撃のエフェクト
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_0, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_0, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_1, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_IMPACT_WAVE_2, playerPos, playerPos);
        }
        // 防御当たり判定の大きさを取得
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

        // 変数宣言
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
        float fFinalPower = 0.0f;                                          // 最終的な攻撃力
        const float ATTACK_EMIT_DISTANCE = CARRIER_SKY_EMIT_DISTANCE;      // 攻撃発生距離
        const float ATTACK_RADIUS = CARRIER_SKY_RADIUS;                    // 攻撃の大きさ
        const float ATTACK_HEIGHT = CARRIER_SKY_HEIGHT;                    // 攻撃の高さ
        const float BASE_DAMAGE = CARRIER_SKY_BASE_DAMAGE;                 // 基本ダメージ

        // 攻撃発生位置をずらす
        slidePos.y += ATTACK_EMIT_DISTANCE;

        // 攻撃発生位置を決める
        attackPos = playerPos + slidePos;

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        // 落下
        move.y -= CARRIER_SKY_UP_VALUE;

        // 当たったかどうか
        IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower);

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > CARRIER_SKY_START_ATTACK_FRAME)
    {
        playerPos.y += CARRIER_SKY_UP_VALUE;
        move.y = CARRIER_SKY_UP_VALUE;
        move.x = 0.0f;
        move.z = 0.0f;

        // 敵を引き寄せる弾を生成
        if (m_nCntAttackTime == CARRIER_SKY_START_WIND_FRAME)
        {
            D3DXVECTOR3 windPos = D3DXVECTOR3(playerPos.x, 1.0f, playerPos.z);

            // キャリアーにつけるエフェクト
            CEffect3D::Emit(CEffectData::TYPE_WIND_0, windPos, windPos);
            CEffect3D::Emit(CEffectData::TYPE_WIND_1, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_WIND_1, playerPos, playerPos);

            // 引き寄せる風のエフェクト
            CEffect3D::Emit(CEffectData::TYPE_ATTRACT_WIND_0, windPos, windPos);
            CEffect3D::Emit(CEffectData::TYPE_ATTRACT_WIND_1, windPos, windPos);
            CEffect3D::Emit(CEffectData::TYPE_ATTRACT_WIND_1,{ windPos.x,windPos.y+100,windPos.z}, windPos);
            CEffect3D::Emit(CEffectData::TYPE_ATTRACT_WIND_1, { windPos.x,windPos.y + 200,windPos.z }, windPos);

            CBullet*pBullet = CBullet::Create(CBullet::TYPE_CARRIER_SKY, windPos, DEFAULT_VECTOR, OBJTYPE_PLAYER);
            pBullet->SetWhoContribution(m_nIdxCreate);
        }
    }
}

//=============================================================================
// タンク地上攻撃1_盾構え
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkTankGround1(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= TANK_GROUND1_CREATE_SHIELD_FRAME && m_nCntAttackTime > 1)
    {
        if (m_nCntAttackTime == TANK_GROUND1_CREATE_SHIELD_FRAME)
        {
            // シールド構え音
            CManager::SoundPlay(CSound::LABEL_SE_SHIELD);
        }

        // スーパーアーマー
        SetTakeKnockBack(false);

        // ガード中
        m_bUsingGuard = true;

        // 移動できる
        if (m_controlInput.bTiltedLeftStick)
        {
            playerPos.x += sinf(m_controlInput.fLeftStickAngle)*TANK_GROUND1_WALK_SPEED;
            playerPos.z += cosf(m_controlInput.fLeftStickAngle)*TANK_GROUND1_WALK_SPEED;
        }

        // 通常攻撃でキャンセル可能
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = TANK_GROUND2_WHOLE_FRAME;
            m_attackState = ATTACK_STATE_TANK_GROUND2;
        }
    }
    else if (m_nCntAttackTime == 1)
    {
        ResetAttack();
        m_nCntAttackTime = TANK_GROUND2_WHOLE_FRAME;
        m_attackState = ATTACK_STATE_TANK_GROUND2;
    }
}

//=============================================================================
// タンク地上攻撃2_爆発弾
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkTankGround2(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレーム
    if (m_nCntAttackTime == TANK_GROUND2_FIRE_FRAME)
    {
        // この攻撃中は無敵
        SetInvincible(true);

        // 発射角度、位置を取得
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        D3DXVECTOR3 collisionSize = GetCollisionSizeDefence();
        D3DXVECTOR3 firePos = playerPos + D3DXVECTOR3(0.0f, collisionSize.y / 2.0f, 0.0f);

        // ガード回数に応じて、発射するタイプを変える
        CBullet *pBullet = NULL;
        if (m_nCntGuards < TANK_GROUND1_LV2)
        {
            pBullet = CBullet::Create(CBullet::TYPE_TANK_GROUND_LV1, firePos, moveAngle, OBJTYPE_PLAYER);
        }
        else if (m_nCntGuards >= TANK_GROUND1_LV2 && m_nCntGuards < TANK_GROUND1_LV3)
        {
            pBullet = CBullet::Create(CBullet::TYPE_TANK_GROUND_LV2, firePos, moveAngle, OBJTYPE_PLAYER);
        }
        else if (m_nCntGuards >= TANK_GROUND1_LV3)
        {
            pBullet = CBullet::Create(CBullet::TYPE_TANK_GROUND_LV3, firePos, moveAngle, OBJTYPE_PLAYER);
        }
        if (pBullet)
        {
            pBullet->SetWhoContribution(m_nIdxCreate);
        }

        // 撃てたなら、ガード回数をリセット
        m_nCntGuards = 0;
    }
    else if (m_nCntAttackTime > TANK_GROUND2_FIRE_FRAME)
    {
        // 撃つまでは無敵
        SetInvincible(true);
    }
}

//=============================================================================
// タンクがガード中にダメージを受ける処理
// Author : 後藤慎之助
//=============================================================================
bool CPlayer::TakeDamage_TankUsingGuard(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, bool bUseKnockBack, int effectType)
{
    // 位置からダメージへの向きを取得
    D3DXVECTOR3 myPos = GetPos();
    float fAngleToDamagePos = D3DXToDegree(GetAngleToTargetXZ(damageOldPos, myPos));  // ダメージへの角度
    if (fAngleToDamagePos < 0.0f)
    {
        fAngleToDamagePos += 360.0f;
    }

    // 自機の向きを取得
    D3DXVECTOR3 myRot = GetRot();
    float fPlayerAngle = D3DXToDegree(myRot.y);
    if (fPlayerAngle < 0.0f)
    {
        fPlayerAngle += 360.0f;
    }

    // ダメージ向きがガード範囲内におさまっているなら
    if (fAngleToDamagePos <= fPlayerAngle + (m_afParam[PARAM_TANK_GUARD_WIDTH] / 2.0f)&&
        fAngleToDamagePos >= fPlayerAngle - (m_afParam[PARAM_TANK_GUARD_WIDTH] / 2.0f))
    {
        // ガード回数加算（2回に一回のガードで貢献度を得る）
        m_nCntGuards++;
        if (m_nCntGuards % 2 == 0)
        {
            GainContribution(1);
        }
        if (m_nCntGuards > TANK_GROUND1_LV3)
        {
            m_nCntGuards = TANK_GROUND1_LV3;
        }

        // ガード成功音
        CManager::SoundPlay(CSound::LABEL_SE_OFFSET);

        // ガードエフェクト発生
        CEffect3D::Emit(CEffectData::TYPE_WALL_HIT_SHOCK, damagePos, damageOldPos);
        // ガード成功したため、関数を抜ける
        return true;
    }

    // ダメージを受ける
    return TakeDamage(fDamage, damagePos, damageOldPos, OBJTYPE_ENEMY, bUseKnockBack, effectType);
}

//=============================================================================
// タンク空中攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkTankSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= TANK_SKY_START_FRAME &&
        m_nCntAttackTime >= TANK_SKY_END_FRAME)
    {
        // 挑発エフェクト
        if (m_nCntAttackTime == TANK_SKY_START_FRAME)
        {
            // カメラの振動
            CManager::GetCamera()->CCamera::SetShake(300.0f);

            // 咆哮音
            CManager::SoundPlay(CSound::LABEL_SE_JUMP_ATTACK_SHIELD);

            CWave::Create(playerPos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

            CEffect3D::Emit(CEffectData::TYPE_ROAR_0, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_ROAR_1, playerPos, playerPos);
            CEffect3D::Emit(CEffectData::TYPE_ROAR_2, playerPos, playerPos);
        }

        // 縦の移動量は一定
        move.y = TANK_SKY_FALL_VALUE;

        // 変数宣言
        const float ATTACK_RADIUS = TANK_SKY_RADIUS;    // 攻撃の大きさ
        const float ATTACK_HEIGHT = TANK_SKY_HEIGHT;    // 攻撃の高さ
        int flag = 0;                                   // 近接攻撃のフラグ
        D3DXVECTOR3 tauntPos = D3DXVECTOR3(playerPos.x, 0.0f, playerPos.z);

        // 挑発の当たり判定
        BITON(flag, CLOSE_ATTACK_FLAG_TAUNT);
        IsHitCloseRangeAttack(tauntPos, tauntPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), 0.0f, flag);

#ifdef COLLISION_TEST
        CDebug::Create(tauntPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
    }
    else if (m_nCntAttackTime > CARRIER_GROUND_START_FRAME)
    {
        // 移動できない
        move = DEFAULT_VECTOR;
    }
}

//=============================================================================
// ヒーラー地上攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkHealerGround(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレーム
    if (m_nCntAttackTime == HEALER_GROUND_FIRE_FRAME)
    {
        // 発射角度、位置を取得
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        D3DXVECTOR3 collisionSize = GetCollisionSizeDefence();
        D3DXVECTOR3 firePos = playerPos + D3DXVECTOR3(0.0f, collisionSize.y / 2.0f, 0.0f);
        CBullet *pBullet = CBullet::Create(CBullet::TYPE_HEALER_GROUND, firePos, moveAngle, OBJTYPE_PLAYER);
        if (pBullet)
        {
            // 現在のエナジー量に応じて、ダメージを設定する
            float fDamage = HEALER_GROUND_BASE_DAMAGE + (m_fCurrentEnergy * HEALER_GROUND_ADD_DAMAGE_RATE);
            pBullet->SetDamage(fDamage);
            float fHealing = HEALER_GROUND_BASE_HEALING + (m_fCurrentEnergy * HEALER_GROUND_ADD_HEALING_RATE);
            pBullet->SetHealValue(fHealing);
            pBullet->SetWhoContribution(m_nIdxCreate);
        }
    }
    else if (m_nCntAttackTime > HEALER_GROUND_FIRE_FRAME)
    {
        // キャラの向きを変える猶予フレーム
        SetRotDestY(m_controlInput.fPlayerAngle);
    }
}

//=============================================================================
// ヒーラー空中攻撃
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkHealerSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= HEALER_SKY_START_FRAME &&
        m_nCntAttackTime >= HEALER_SKY_END_FRAME)
    {
        // 移動できない
        move = DEFAULT_VECTOR;

        // 回復魔方陣をアクティブ化
        if (m_nCntAttackTime == HEALER_SKY_START_FRAME)
        {
            // ヒーラーのボイス
            CManager::SoundPlay(CSound::LABEL_SE_JUMP_ATTACK_HEALER);

            // 変数宣言
            D3DXVECTOR3 playerRot = CCharacter::GetRot();                 // プレイヤーの向いている向き
            D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                        // ずらす位置
            D3DXVECTOR3 bulletPos = DEFAULT_VECTOR;                       // 攻撃発生位置
            const float ATTACK_EMIT_DISTANCE = HEALER_SKY_EMIT_DISTANCE;  // 攻撃発生距離

            // 攻撃発生位置をずらす
            slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
            slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

            // 攻撃発生位置を決める
            bulletPos = D3DXVECTOR3(playerPos.x, 0.0f, playerPos.z) + slidePos;

            // ガードエフェクト発生
            CEffect3D::Emit(CEffectData::TYPE_MAGIC_CIRCLE_0, bulletPos, bulletPos);
            CEffect3D::Emit(CEffectData::TYPE_MAGIC_CIRCLE_2, bulletPos, bulletPos);
            // 現在のエナジー量に応じて、ダメージを設定する
            float fDamage = HEALER_SKY_BASE_DAMAGE + (m_fCurrentEnergy * HEALER_SKY_ADD_DAMAGE_RATE);
            float fHealing = HEALER_SKY_BASE_HEALING + (m_fCurrentEnergy * HEALER_SKY_ADD_HEALING_RATE);

            // 値を反映
            if (m_pHealingCircle)
            {
                m_pHealingCircle->SetPos(bulletPos);
                m_pHealingCircle->SetDamage(fDamage);
                m_pHealingCircle->SetHealValue(fHealing);
                m_pHealingCircle->SetCntTime(0);        // カウンタをリセット
                m_pHealingCircle->SetUseUpdate(true);   // 更新フラグをリセット
            }
        }
    }
    else if (m_nCntAttackTime > HEALER_SKY_START_FRAME)
    {
        // 移動制限
        move.x *= HEALER_SKY_MOVE_LIMIT;
        move.z *= HEALER_SKY_MOVE_LIMIT;
        move.y = 0.0f;
    }
}