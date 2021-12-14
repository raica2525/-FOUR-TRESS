//======================================================================================
//
// エネミーの種類派生処理 (enemy_type.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "effect3d.h"
#include "modelEffect.h"
#include "bullet.h"

//========================================
// マクロ定義
//========================================
#define DEFAULT_PATROL_DISTANCE 2500                    // デフォルトの巡回距離
#define DEFAULT_DISCOVERY_PLAYER_DISTANCE 2000.0f       // デフォルトの発見距離
#define DEFAULT_ENEMY_TURN_SPEED 5.0f                   // デフォルトの振り向き速度
#define DEFAULT_FOLLOW_WHOLE_FRAME 60                   // デフォルトの追従フレーム（メンバ変数には置いていない）
#define DEFAULT_FOLLOW_WAIT_FRAME 30                    // デフォルトの追従後の待機フレーム（メンバ変数には置いていない）

//===========================
// アーミー
//===========================
#define ARMY_WHOLE_FRAME 80     // 全体フレーム
#define ARMY_FIRE_FRAME 60      // 発射フレーム
#define ARMY_WAIT_COUNT 35      // 攻撃後の待機フレーム（初期30）

//===========================
// カミカゼ
//===========================
#define KAMIKAZE_ATK_SPEED 10.0f // 攻撃中のスピード
#define KAMIKAZE_WHOLE_FRAME 180 // 全体フレーム
#define KAMIKAZE_TARGET_FRAME 2  // ターゲットを決めるフレーム

//===========================
// キャノン
//===========================
#define CANNON_WHOLE_FRAME 180       // 全体フレーム
#define CANNON_FIRE_START_FRAME 60   // 発射開始フレーム
#define CANNON_FIRE_INTERVAL_FRAME 6 // 発射間隔フレーム
#define CANNON_FIRE_END_FRAME 120    // 発射終了フレーム
#define CANNON_WAIT_COUNT 30         // 攻撃後の待機フレーム

//===========================
// コマンダー
//===========================
#define COMMANDER_WHOLE_FRAME 50     // 全体フレーム
#define COMMANDER_FIRE_FRAME 30      // 発射フレーム
#define COMMANDER_WAIT_COUNT 60      // 攻撃後の待機フレーム
#define COMMANDER_ONCE_SPAWN 5       // 一度の生成個数
#define COMMANDER_SPAWN_ANGLE_Y D3DXToRadian(80.0f) // 生成角度Y

//=============================================================================
// 種類ごとの初期設定
// Author : 後藤慎之助
//=============================================================================
void CEnemy::SetupInfoByType(void)
{
    // 基本設定
    CCharacter::SetHPDisp(CCharacter::HP_DISP_FOLLOW);  // HP表示は基本追従
    float fHP = 0.0f;
    m_nPatrolDistance = DEFAULT_PATROL_DISTANCE;
    m_fDiscoveryTargetDistance = DEFAULT_DISCOVERY_PLAYER_DISTANCE;     // 主に攻撃周りの検知で使う
    SetTurnSpeed(DEFAULT_ENEMY_TURN_SPEED);

    switch (m_type)
    {
    case TYPE_SPIDER:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 100.0f));
        m_fSpeed = 5.0f;
        fHP = 500.0f;
        m_fChargeValue = 3.0f;
        m_walkMotion = SPIDER_ANIM_WALK;
        m_attackMotion = SPIDER_ANIM_ATTACK;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(SPIDER_PARTS_MAX);
        CCharacter::BindParts(SPIDER_PARTS_BODY, 18);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH, 19);
        CCharacter::BindParts(SPIDER_PARTS_FANG_LEFT, 20);
        CCharacter::BindParts(SPIDER_PARTS_FANG_RIGHT, 21);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_0, 22);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_1, 23);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_2, 24);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_3, 25);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_0, 26);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_1, 27);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_2, 28);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_3, 29);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH_CUBE, 30);
        CCharacter::LoadModelData("./data/ANIMATION/motion_spider.txt");
        break;
    case TYPE_ARMY:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 300.0f));
        m_fSpeed = 5.0f;
        fHP = 280.0f;
        m_fChargeValue = 3.0f;
        m_walkMotion = ARMY_ANIM_WALK;
        m_attackMotion = ARMY_ANIM_ATTACK;
        m_deathMotion = ARMY_ANIM_DEATH;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(ARMY_PARTS_MAX);
        CCharacter::BindParts(ARMY_PARTS_BODY, 43);
        CCharacter::BindParts(ARMY_PARTS_RHAND, 44);
        CCharacter::BindParts(ARMY_PARTS_LHAND, 45);
        CCharacter::LoadModelData("./data/ANIMATION/motion_army.txt");
        break;
    case TYPE_KAMIKAZE:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 325.0f));
        m_fSpeed = 5.0f;
        fHP = 200.0f;
        m_fChargeValue = 5.0f;
        m_walkMotion = KAMIKAZE_ANIM_WALK;
        m_attackMotion = KAMIKAZE_ANIM_ATTACK;
        m_deathMotion = KAMIKAZE_ANIM_DEATH;
        m_targetTrend = TARGET_TREND_FORTRESS;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(KAMIKAZE_PARTS_MAX);
        CCharacter::BindParts(KAMIKAZE_PARTS_BODY, 46);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARML, 47);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARMR, 48);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB, 49);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_kamikaze.txt");
        break;
    case TYPE_CANNON:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(400.0f, 400.0f));
        m_fSpeed = 0.0f;
        fHP = 450.0f;
        m_fChargeValue = 10.0f;
        SetUseKnockBack(false);
        SetTurnSpeed(1.2f);
        m_targetTrend = TARGET_TREND_PLAYER_AND_FORTRESS;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(CANNON_PARTS_MAX);
        CCharacter::BindParts(CANNON_PARTS_BODY, 51);
        CCharacter::BindParts(CANNON_PARTS_FIRE_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_cannon.txt");
        CCharacter::SetDontUseAnimation();
        break;
    case TYPE_COMMANDER:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(600.0f, 400.0f));
        m_fSpeed = 0.0f;
        fHP = 850.0f;
        m_fChargeValue = 20.0f;
        m_attackMotion = COMMANDER_ANIM_SPAWN_ENEMY;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(COMMANDER_PARTS_MAX);
        CCharacter::BindParts(COMMANDER_PARTS_BODY, 58);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL1, 59);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL2, 60);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL3, 61);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL4, 62);
        CCharacter::BindParts(COMMANDER_PARTS_PETAL5, 63);
        CCharacter::BindParts(COMMANDER_PARTS_SPAWN_POS, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_commander.txt");
        break;
    }

    // 強さを反映
    //m_fSpeed *= m_fStrength;  // 移動速度も速くなるのは違和感？
    fHP *= m_fStrength;

    // HPを反映
    SetUpLife(fHP);
}

//=============================================================================
// 共通の攻撃（ターゲットを追従）
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AtkCommonFollow(D3DXVECTOR3 &myPos)
{
    // 位置に移動量を結びつける
    myPos += m_moveAngle * m_fSpeed;

    // 向きを調整
    RotControl();

    if (m_nCntTime >= DEFAULT_FOLLOW_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, DEFAULT_FOLLOW_WAIT_FRAME);
    }
}

//=============================================================================
// アーミーの攻撃
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AtkArmy(D3DXVECTOR3& myPos)
{
    if (m_nCntTime == ARMY_FIRE_FRAME)
    {
        // 発射フレーム
        D3DXVECTOR3 collisionSize = GetCollisionSizeDefence();
        D3DXVECTOR3 firePos = myPos + D3DXVECTOR3(0.0f, collisionSize.y / 2.0f, 0.0f);
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_ARMY_ATTACK, firePos, moveAngle, OBJTYPE_ENEMY, m_fStrength);
    }
    else if (m_nCntTime == ARMY_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, ARMY_WAIT_COUNT);
    }
}

//=============================================================================
// カミカゼの攻撃
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AtkKamikaze(D3DXVECTOR3 &myPos)
{
    // 位置に移動量を結びつける
    myPos += m_moveAngle * KAMIKAZE_ATK_SPEED;

    // 向きを調整
    RotControl();

    if (m_nCntTime >= KAMIKAZE_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, DEFAULT_FOLLOW_WAIT_FRAME);

    }
    else if (m_nCntTime == KAMIKAZE_TARGET_FRAME)
    {
        if (m_pTarget)
        {
            // 現在の位置と、目的地までの移動角度/向きを求める
            D3DXVECTOR3 targetPos = m_pTarget->GetPos();
            float fDestAngle = atan2((myPos.x - targetPos.x), (myPos.z - targetPos.z));
            m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
            SetRotDestY(fDestAngle);

        }
    }
}

//=============================================================================
// キャノンの攻撃
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AtkCannon(D3DXVECTOR3& myPos)
{
    if (m_nCntTime >= CANNON_FIRE_START_FRAME && m_nCntTime <= CANNON_FIRE_END_FRAME)
    {
        // 発射フレーム
        if (m_nCntTime % CANNON_FIRE_INTERVAL_FRAME == 0)
        {
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
            CBullet::Create(CBullet::TYPE_CANNON_ATTACK, GetPartsPos(CANNON_PARTS_FIRE_CUBE), moveAngle, OBJTYPE_ENEMY, m_fStrength);
        }
    }
    else if (m_nCntTime == CANNON_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, CANNON_WAIT_COUNT);
    }
}

//=============================================================================
// コマンダーの攻撃
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AtkCommander(D3DXVECTOR3 &myPos)
{
    if (m_nCntTime == COMMANDER_FIRE_FRAME)
    {
        // 発射
        for (int nCnt = 0; nCnt < COMMANDER_ONCE_SPAWN; nCnt++)
        {
            float fAngle = float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT - float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT;
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(fAngle), COMMANDER_SPAWN_ANGLE_Y, -cosf(fAngle));
            CBullet::Create(CBullet::TYPE_COMMANDER_ATTACK, GetPartsPos(COMMANDER_PARTS_SPAWN_POS), moveAngle, OBJTYPE_ENEMY, m_fStrength);
        }
    }
    else if (m_nCntTime == COMMANDER_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, COMMANDER_WAIT_COUNT);
    }
}