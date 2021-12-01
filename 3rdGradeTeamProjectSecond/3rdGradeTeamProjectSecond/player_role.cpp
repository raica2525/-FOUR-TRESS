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

//========================================
// マクロ定義
//========================================
//==========================
// ウォーリアー地上1
//==========================
// 基本ダメージ
#define WARRIOR_GROUND1_BASE_DAMAGE 100.0f
// 得られる必殺ゲージ量
#define WARRIOR_GROUND1_GAIN_SP_GAUGE 100.0f
// 当たり判定周り
#define WARRIOR_GROUND1_EMIT_DISTANCE 500.0f
#define WARRIOR_GROUND1_RADIUS 350.0f
#define WARRIOR_GROUND1_HEIGHT 150.0f
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define WARRIOR_GROUND1_WHOLE_FRAME 30
#define WARRIOR_GROUND1_START_FRAME (WARRIOR_GROUND1_WHOLE_FRAME - 5)
#define WARRIOR_GROUND1_END_FRAME (WARRIOR_GROUND1_WHOLE_FRAME - 15)
// 硬直フレーム
#define WARRIOR_GROUND1_STOP_FRAME 3
// その他
#define WARRIOR_GROUND1_DUSH_SPEED 20.0f
#define WARRIOR_GROUND1_COMBO_FRAME (WARRIOR_GROUND1_WHOLE_FRAME - 10)

//==========================
// ウォーリアー地上2
//==========================
// 基本ダメージ
#define WARRIOR_GROUND2_BASE_DAMAGE 1000.0f
// 得られる必殺ゲージ量
#define WARRIOR_GROUND2_GAIN_SP_GAUGE 100.0f
// 当たり判定の大きさ
#define WARRIOR_GROUND2_EMIT_DISTANCE 500.0f
#define WARRIOR_GROUND2_RADIUS 350.0f
#define WARRIOR_GROUND2_HEIGHT 150.0f
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define WARRIOR_GROUND2_WHOLE_FRAME 30
#define WARRIOR_GROUND2_START_FRAME (WARRIOR_GROUND2_WHOLE_FRAME - 5)
#define WARRIOR_GROUND2_END_FRAME (WARRIOR_GROUND2_WHOLE_FRAME - 15)
// 硬直フレーム
#define WARRIOR_GROUND2_STOP_FRAME 3
// その他
#define WARRIOR_GROUND2_DUSH_SPEED 20.0f
#define WARRIOR_GROUND2_COMBO_FRAME (WARRIOR_GROUND2_WHOLE_FRAME - 10)

//==========================
// ウォーリアー空中
//==========================
// 基本ダメージ
#define WARRIOR_SKY_BASE_DAMAGE 500.0f
// 得られる必殺ゲージ量
#define WARRIOR_SKY_GAIN_SP_GAUGE 100.0f
// 全体フレーム、攻撃発生フレーム
#define WARRIOR_SKY_WHOLE_FRAME 9999
#define WARRIOR_SKY_START_FRAME (WARRIOR_SKY_WHOLE_FRAME - 20)
// その他
#define WARRIOR_SKY_UP_VALUE 20.0f
#define WARRIOR_SKY_CHANCE_FRAME 30

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
        case ATTACK_STATE_SIT_DOWN:
            AtkSitDown(playerPos, move);
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
                    m_nCntAttackTime = WARRIOR_GROUND1_WHOLE_FRAME;
                    m_fNextGainSpGauge = WARRIOR_GROUND1_GAIN_SP_GAUGE;
                    m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
                    break;
                case ROLE_HUNTER:
                    m_attackState = ATTACK_STATE_HUNTER_GROUND;
                    break;
                case ROLE_CARRIER:
                    m_attackState = ATTACK_STATE_CARRIER_GROUND;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_GROUND;
                    break;
                }
            }
            else if (m_controlInput.bTriggerY)
            {
                // 必殺技等を使うならここに書く
            }
            else if (m_controlInput.bTriggerB)
            {
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
                    m_fNextGainSpGauge = WARRIOR_SKY_GAIN_SP_GAUGE;
                    m_attackState = ATTACK_STATE_WARRIOR_SKY;
                    break;
                case ROLE_HUNTER:
                    m_attackState = ATTACK_STATE_HUNTER_SKY;
                    break;
                case ROLE_CARRIER:
                    m_attackState = ATTACK_STATE_CARRIER_SKY;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_SKY;
                    break;
                }
            }
            else if (m_controlInput.bTriggerY)
            {
                // 必殺技等を使うならここに書く
            }
            else if (m_controlInput.bTriggerB)
            {
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
    case ATTACK_STATE_SIT_DOWN:
        GetAnimation()->SetAnimation(ANIM_SIT_DOWN);
        break;
    }
}

//=============================================================================
// 近接攻撃が当たったかどうかのチェック
// Author : 後藤慎之助
//=============================================================================
bool CPlayer::IsHitCloseRangeAttack(D3DXVECTOR3 playerPos, D3DXVECTOR3 attackPos, D3DXVECTOR2 attackSize, float fPower, int flag)
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

            // 敵のインデックスを取得
            int nIdx = pEnemy->GetIdx();
            if (nIdx < 0 || nIdx >= ENEMY_IDX_MAX)
            {
                return false;
            }

            // 多段ヒット回避用フラグがfalseなら
            if (!m_abUseAvoidMultipleHits[nIdx])
            {
                // 当たっているなら
                if (IsCollisionCylinder(attackPos, attackSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                {
                    // 敵にダメージが入ったら
                    if (pEnemy->TakeDamage(fPower, attackPos, playerPos))
                    {
                        // 当たった
                        bHit = true;

                        // 多段ヒット回避用のフラグをtrueに
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // Spゲージ上昇
                        GainSpGauge();
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

//=============================================================================
// ウォーリアー地上攻撃1
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkWarriorGround1(D3DXVECTOR3& playerPos)
{
    // 攻撃発生フレームと終了フレームを考慮
    if (m_nCntAttackTime <= WARRIOR_GROUND1_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND1_END_FRAME)
    {
        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // プレイヤーの向いている向き
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
        float fFinalPower = 0.0f;                                          // 最終的な攻撃力
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND1_EMIT_DISTANCE;  // 攻撃発生距離
        const float ATTACK_RADIUS = WARRIOR_GROUND1_RADIUS;                // 攻撃の大きさ
        const float ATTACK_HEIGHT = WARRIOR_GROUND1_HEIGHT;                // 攻撃の高さ
        const float BASE_DAMAGE = WARRIOR_GROUND1_BASE_DAMAGE;             // 基本ダメージ

        // 攻撃発生位置をずらす
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // 攻撃発生位置を決める
        attackPos = playerPos + slidePos;

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        // 前進
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND1_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND1_DUSH_SPEED;

        // 当たったかどうか
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND1_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= WARRIOR_GROUND1_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND2_WHOLE_FRAME;
            m_fNextGainSpGauge = WARRIOR_GROUND2_GAIN_SP_GAUGE;
            m_attackState = ATTACK_STATE_WARRIOR_GROUND2;
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
    if (m_nCntAttackTime <= WARRIOR_GROUND2_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND2_END_FRAME)
    {
        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // プレイヤーの向いている向き
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
        float fFinalPower = 0.0f;                                          // 最終的な攻撃力
        const float ATTACK_EMIT_DISTANCE = WARRIOR_GROUND2_EMIT_DISTANCE;  // 攻撃発生距離
        const float ATTACK_RADIUS = WARRIOR_GROUND2_RADIUS;                // 攻撃の大きさ
        const float ATTACK_HEIGHT = WARRIOR_GROUND2_HEIGHT;                // 攻撃の高さ
        const float BASE_DAMAGE = WARRIOR_GROUND2_BASE_DAMAGE;             // 基本ダメージ

                                                                           // 攻撃発生位置をずらす
        slidePos.x = ATTACK_EMIT_DISTANCE * -sinf(playerRot.y);
        slidePos.z = ATTACK_EMIT_DISTANCE * -cosf(playerRot.y);

        // 攻撃発生位置を決める
        attackPos = playerPos + slidePos;

        // 攻撃力を考慮
        fFinalPower = BASE_DAMAGE;

        // 前進
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND2_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND2_DUSH_SPEED;

        // 当たったかどうか
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND2_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= WARRIOR_GROUND2_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND1_WHOLE_FRAME;
            m_fNextGainSpGauge = WARRIOR_GROUND1_GAIN_SP_GAUGE;
            m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
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
            m_nCntAttackTime = WARRIOR_SKY_CHANCE_FRAME;
        }
        else
        {
            // 防御当たり判定の大きさを取得
            D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();

            // 変数宣言
            D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // プレイヤーの向いている向き
            D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
            D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
            float fFinalPower = 0.0f;                                          // 最終的な攻撃力
            const float ATTACK_EMIT_DISTANCE = collisionSizeDefence.y * 1.5f;  // 攻撃発生距離
            const float ATTACK_RADIUS = 500.0f;                                // 攻撃の大きさ
            const float ATTACK_HEIGHT = 200.0f;                                // 攻撃の高さ
            const float BASE_DAMAGE = WARRIOR_SKY_BASE_DAMAGE;             // 基本ダメージ

                                                                           // 攻撃発生位置をずらす
            slidePos.y -= ATTACK_EMIT_DISTANCE;

            // 攻撃発生位置を決める
            attackPos = playerPos + slidePos;

            // 攻撃力を考慮
            fFinalPower = BASE_DAMAGE;

            // 落下
            move.y -= WARRIOR_SKY_UP_VALUE;


            // 当たったかどうか
            IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower);

#ifdef COLLISION_TEST
            CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
        }
    }
    else if (m_nCntAttackTime > WARRIOR_SKY_START_FRAME)
    {
        playerPos.y += WARRIOR_SKY_UP_VALUE;
        move.y = WARRIOR_SKY_UP_VALUE;
    }
}

//=============================================================================
// 移動要塞に座って攻撃する処理
// Author : 後藤慎之助
//=============================================================================
void CPlayer::AtkSitDown(D3DXVECTOR3 &playerPos, D3DXVECTOR3& move)
{
    // 移動要塞を取得
    CFortress *pFortress = CGame::GetFortress();
    if (pFortress)
    {
        // 自身の位置を、座席にする
        playerPos = pFortress->GetPartsPos(CFortress::PARTS_SEAT);

        // 移動量を念のためリセットする
        move = DEFAULT_VECTOR;

        // 向きを合わせる
        SetRot(pFortress->GetRot());
    }

    // 降りる処理
    if (m_controlInput.bTriggerB)
    {
        ResetAttack();

        // 移動要塞側のフラグを戻す
        if (pFortress)
        {
            pFortress->SetNowWhoRiding(false);
        }
    }
}