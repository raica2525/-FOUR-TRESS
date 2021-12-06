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
#define ARMY_WHOLE_FRAME 80
#define ARMY_FIRE_FRAME 60
#define ARMY_WAIT_COUNT 30
#define ARMY_FOLLOW_FRAME 60

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
    m_fDiscoveryPlayerDistance = DEFAULT_DISCOVERY_PLAYER_DISTANCE;
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
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 150.0f));
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
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 150.0f));
        m_fSpeed = 5.0f;
        fHP = 200.0f;
        m_fChargeValue = 5.0f;
        m_walkMotion = KAMIKAZE_ANIM_WALK;
        m_attackMotion = KAMIKAZE_ANIM_ATTACK;
        m_deathMotion = KAMIKAZE_ANIM_DEATH;
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
        SetCollisionSizeDefence(D3DXVECTOR2(400.0f, 200.0f));
        m_fSpeed = 0.0f;
        fHP = 450.0f;
        m_fChargeValue = 10.0f;
        SetUseKnockBack(false);
        SetTurnSpeed(1.0f);
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(CANNON_PARTS_MAX);
        CCharacter::BindParts(CANNON_PARTS_BODY, 51);
        CCharacter::BindParts(CANNON_PARTS_FIRE_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_cannon.txt");
        CCharacter::SetDontUseAnimation();
        break;
    case TYPE_COMMANDER:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 200.0f));
        m_fSpeed = 0.0f;
        fHP = 850.0f;
        m_fChargeValue = 20.0f;
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
        D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
        CBullet::Create(CBullet::TYPE_ARMY_ATTACK, GetPos(), moveAngle, m_fStrength);
    }
    else if (m_nCntTime == ARMY_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, ARMY_WAIT_COUNT);
    }
}