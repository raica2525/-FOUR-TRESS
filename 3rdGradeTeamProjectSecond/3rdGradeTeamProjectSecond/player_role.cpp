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

//========================================
// マクロ定義
//========================================
//==========================
// ウォーリアー地上
//==========================
// 基本ダメージ
#define WARRIOR_GROUND_BASE_DAMAGE 100.0f
// 当たり判定周り
#define WARRIOR_GROUND_EMIT_DISTANCE 350.0f
#define WARRIOR_GROUND_RADIUS 450.0f
#define WARRIOR_GROUND_HEIGHT 200.0f
// 全体フレーム、攻撃発生フレーム、攻撃終了フレーム
#define WARRIOR_GROUND_WHOLE_FRAME 30
#define WARRIOR_GROUND_START_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 10)
#define WARRIOR_GROUND_END_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 20)
// 硬直フレーム
#define WARRIOR_GROUND_STOP_FRAME 5
// その他
#define WARRIOR_GROUND_DUSH_SPEED 20.0f
#define WARRIOR_GROUND_COMBO_FRAME (WARRIOR_GROUND_WHOLE_FRAME - 15)

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
#define WARRIOR_SKY_START_FRAME (WARRIOR_SKY_WHOLE_FRAME - 20)
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
#define HUNTER_SKY_WHOLE_FRAME 45
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
                    m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
                    m_attackState = ATTACK_STATE_WARRIOR_GROUND1;
                    break;
                case ROLE_CARRIER:
                    m_attackState = ATTACK_STATE_CARRIER_GROUND;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_GROUND;
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
                    m_attackState = ATTACK_STATE_CARRIER_SKY;
                    break;
                case ROLE_TANK:
                    m_attackState = ATTACK_STATE_TANK_SKY;
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
            if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
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
    if (m_nCntAttackTime <= WARRIOR_GROUND_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND_END_FRAME)
    {
        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // プレイヤーの向いている向き
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
        float fFinalPower = 0.0f;                                          // 最終的な攻撃力
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

        // 前進
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;

        // 当たったかどうか
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= WARRIOR_GROUND_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
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
    if (m_nCntAttackTime <= WARRIOR_GROUND_START_FRAME &&
        m_nCntAttackTime >= WARRIOR_GROUND_END_FRAME)
    {
        // 変数宣言
        D3DXVECTOR3 playerRot = CCharacter::GetRot();                      // プレイヤーの向いている向き
        D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                             // ずらす位置
        D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                            // 攻撃発生位置
        float fFinalPower = 0.0f;                                          // 最終的な攻撃力
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

        // 前進
        D3DXVECTOR3 rot = GetRot();
        playerPos.x += -sinf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;
        playerPos.z += -cosf(rot.y)*WARRIOR_GROUND_DUSH_SPEED;

        // 当たったかどうか
        if (IsHitCloseRangeAttack(playerPos, attackPos, D3DXVECTOR2(ATTACK_RADIUS, ATTACK_HEIGHT), fFinalPower))
        {
            m_nCntStopTime = WARRIOR_GROUND_STOP_FRAME;
        }

#ifdef COLLISION_TEST
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
    }

    // 連続攻撃の判定
    if (m_nCntAttackTime <= WARRIOR_GROUND_COMBO_FRAME)
    {
        if (m_controlInput.bTriggerX)
        {
            ResetAttack();
            m_nCntAttackTime = WARRIOR_GROUND_WHOLE_FRAME;
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
        CDebug::Create(attackPos, D3DXVECTOR3(ATTACK_RADIUS, ATTACK_HEIGHT, ATTACK_RADIUS), CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST
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

    // 電力消費攻撃
    if (m_controlInput.bTriggerX)
    {
        if (pFortress)
        {
            pFortress->SetAttackPhase(true);
        }
    }
    else if (m_controlInput.bTriggerB)
    {
        // 攻撃フェーズ中は降りられない
        if (pFortress)
        {
            if (!pFortress->GetAttackPhase())
            {
                // 降りる処理（攻撃周りをリセット）
                ResetAttack();

                // 移動要塞側の座っているフラグを戻す
                pFortress->SetNowWhoRiding(false);
            }
        }
        else
        {
            // 移動要塞がないなら、強制で降りる
            ResetAttack();
        }
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
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_HUNTER_GROUND, GetPartsPos(PARTS_WEP), moveAngle);
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
        // 一度に複数の矢を、均等に放つ
        for (int nCnt = 0; nCnt < HUNTER_SKY_ONCE_SHOT; nCnt++)
        {
            float fDigitAngle = (float)(nCnt + 1) * (D3DXToRadian(180.0f) / (float)(HUNTER_SKY_ONCE_SHOT + 1));
            float fAngleXZ = GetRot().y + fDigitAngle - D3DXToRadian(90.0f);
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(fAngleXZ), HUNTER_SKY_ANGLE_Y, -cosf(fAngleXZ));
            CBullet*pBullet = CBullet::Create(CBullet::TYPE_HUNTER_SKY, GetPartsPos(PARTS_WEP), moveAngle);
            D3DXVECTOR3 targetPos = D3DXVECTOR3(m_afParam[PARAM_HUNTER_TARGET_POS_X], m_afParam[PARAM_HUNTER_TARGET_POS_Y], m_afParam[PARAM_HUNTER_TARGET_POS_Z]);
            pBullet->SetTargetPos(targetPos);
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
            D3DXVECTOR3 targetPos = CGame::GetPosToClosestEnemy(playerPos);
            m_afParam[PARAM_HUNTER_TARGET_POS_X] = targetPos.x;
            m_afParam[PARAM_HUNTER_TARGET_POS_Y] = targetPos.y;
            m_afParam[PARAM_HUNTER_TARGET_POS_Z] = targetPos.z;
            // キャラの向きをターゲットの方へ
            SetRotDestY(GetAngleToTargetXZ(targetPos, playerPos));
        }
    }
}