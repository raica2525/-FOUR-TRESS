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
#include "effectData.h"

//========================================
// マクロ定義
//========================================
#define DEFAULT_PATROL_DISTANCE 2000        // デフォルトの巡回距離
#define DEFAULT_DISCOVERY_DISTANCE 2000.0f  // デフォルトの発見距離
#define DEFAULT_ENEMY_TURN_SPEED 5.0f       // デフォルトの振り向き速度
#define DEFAULT_FOLLOW_WHOLE_FRAME 60       // デフォルトの追従フレーム（メンバ変数には置いていない）
#define DEFAULT_FOLLOW_WAIT_FRAME 30        // デフォルトの追従後の待機フレーム（メンバ変数には置いていない）

//===========================
// アーミー
//===========================
#define ARMY_WHOLE_FRAME 80                 // 全体フレーム
#define ARMY_FIRE_FRAME 60                  // 発射フレーム
#define ARMY_WAIT_COUNT 35                  // 攻撃後の待機フレーム（初期30）
#define ARMY_DISCOVERY_DISTANCE 2000.0f     // 検知距離

//===========================
// カミカゼ
//===========================
#define KAMIKAZE_WHOLE_FRAME 180            // 全体フレーム
#define KAMIKAZE_TARGET_FRAME 2             // ターゲットを決めるフレーム
#define KAMIKAZE_WAIT_COUNT 25              // 攻撃後の待機フレーム
#define KAMIKAZE_DISCOVERY_DISTANCE 2500.0f // 検知距離
#define KAMIKAZE_ATK_SPEED 10.0f            // 攻撃中のスピード

//===========================
// キャノン
//===========================
#define CANNON_WHOLE_FRAME 180              // 全体フレーム
#define CANNON_FIRE_START_FRAME 60          // 発射開始フレーム
#define CANNON_FIRE_INTERVAL_FRAME 6        // 発射間隔フレーム
#define CANNON_FIRE_END_FRAME 120           // 発射終了フレーム
#define CANNON_WAIT_COUNT 30                // 攻撃後の待機フレーム
#define CANNON_DISCOVERY_DISTANCE 2500.0f   // 検知距離
#define CANNON_TURN_SPEED 1.2f              // 回転速度

//===========================
// コマンダー
//===========================
#define COMMANDER_WHOLE_FRAME 50            // 全体フレーム
#define COMMANDER_FIRE_FRAME 30             // 発射フレーム
#define COMMANDER_WAIT_COUNT 60             // 攻撃後の待機フレーム
#define COMMANDER_ONCE_SPAWN 3              // 一度の生成個数
#define COMMANDER_SPAWN_ANGLE_Y D3DXToRadian(80.0f) // 生成角度Y
#define COMMANDER_DISCOVERY_DISTANCE 1750.0f// 検知距離

//===========================
// シニガミ
//===========================
#define SHINIGAMI_WHOLE_FRAME 95			    // 全体フレーム	
#define SHINIGAMI_FIRE_FRAME 50				    // 発射フレーム
#define SHINIGAMI_FIRE_START_DISTANCE 850.0f    // 攻撃開始距離
#define SHINIGAMI_WAIT_COUNT 90                 // 攻撃後の待機フレーム
#define SHINIGAMI_DISCOVERY_DISTANCE 2500.0f    // 検知距離
#define SHINIGAMI_TURN_SPEED 1.5f               // 回転速度

//===========================
// ペンペン
//===========================
#define PENPEN_WHOLE_FRAME 150                // 全体フレーム
#define PENPEN_START_FRAME 30                 // 攻撃開始フレーム
#define PENPEN_INTERVAL_FRAME 5               // 発生間隔フレーム
#define PENPEN_WAIT_COUNT 50                  // 攻撃後の待機フレーム
#define PENPEN_DISCOVERY_DISTANCE 1750.0f     // 検知距離
#define PENPEN_ATK_SPEED 8.75f                // 攻撃中のスピード
#define PENPEN_CUTTER_ROT_SPEED D3DXToRadian(15.0f) // カッターの回転速度

//===========================
// キウイ
//===========================
#define KIWI_WHOLE_FRAME 40                 // 全体フレーム
#define KIWI_DISCOVERY_DISTANCE 2000.0f     // 検知距離
#define KIWI_RUN_DISTANCE 2500.0f           // 逃げきったと判断する距離
#define KIWI_WAIT_COUNT 1                   // 逃げ切った後の待機フレーム
#define KIWI_ATK_SPEED 10.0f                // 攻撃中のスピード

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
        m_nAddScore = 9999;
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
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 350.0f));
        m_fSpeed = 5.0f;
        fHP = 280.0f;
        m_fChargeValue = 3.0f;
        m_walkMotion = ARMY_ANIM_WALK;
        m_attackMotion = ARMY_ANIM_ATTACK;
        m_deathMotion = ARMY_ANIM_DEATH;
        m_damageMotion = ARMY_ANIM_DAMAGE;
        m_nAddScore = 50;
        m_fDiscoveryTargetDistance = ARMY_DISCOVERY_DISTANCE;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(ARMY_PARTS_MAX);
        CCharacter::BindParts(ARMY_PARTS_BODY, 43);
        CCharacter::BindParts(ARMY_PARTS_RHAND, 44);
        CCharacter::BindParts(ARMY_PARTS_LHAND, 45);
        CCharacter::LoadModelData("./data/ANIMATION/motion_army.txt");
        break;
    case TYPE_KAMIKAZE:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 350.0f));
        m_fSpeed = 5.0f;
        fHP = 200.0f;
        m_fChargeValue = 5.0f;
        m_walkMotion = KAMIKAZE_ANIM_WALK;
        m_attackMotion = KAMIKAZE_ANIM_ATTACK;
        m_deathMotion = KAMIKAZE_ANIM_DEATH;
        m_damageMotion = KAMIKAZE_ANIM_DAMAGE;
        m_targetTrend = TARGET_TREND_FORTRESS;
        m_nAddScore = 100;
        m_fDiscoveryTargetDistance = KAMIKAZE_DISCOVERY_DISTANCE;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(KAMIKAZE_PARTS_MAX);
        CCharacter::BindParts(KAMIKAZE_PARTS_BODY, 46);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARML, 47);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARMR, 48);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB, 49);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_kamikaze.txt");
        m_Effect.type = CEffectData::TYPE_SPARK;
        m_Effect.interval = 5;
        m_Effect.nCntTrail = 0;
        break;
    case TYPE_CANNON:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(400.0f, 400.0f));
        m_fSpeed = 0.0f;
        fHP = 450.0f;
        m_fChargeValue = 10.0f;
        SetTakeKnockBack(false);
        SetTurnSpeed(CANNON_TURN_SPEED);
        m_targetTrend = TARGET_TREND_PLAYER_AND_FORTRESS;
        m_nAddScore = 300;
        m_fDiscoveryTargetDistance = CANNON_DISCOVERY_DISTANCE;
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
        m_nAddScore = 400;
        m_fDiscoveryTargetDistance = COMMANDER_DISCOVERY_DISTANCE;
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
	case TYPE_SHINIGAMI:
		// 固有の情報
		SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 500.0f)); //後で変える
		m_fSpeed = 5.0f;
		fHP = 1260.0f;
		m_fChargeValue = 44.0f;
		m_walkMotion = SHINIGAMI_ANIM_WALK;
		m_attackMotion = SHINIGAMI_ANIM_ATTACK;
		m_deathMotion = SHINIGAMI_ANIM_DEATH;
        m_damageMotion = SHINIGAMI_ANIM_DAMAGE;
        SetTurnSpeed(SHINIGAMI_TURN_SPEED);
		m_targetTrend = TARGET_TREND_PLAYER;
		m_nAddScore = 3000;
		m_bSquashedByFortress = false;
		m_fDiscoveryTargetDistance = SHINIGAMI_DISCOVERY_DISTANCE;
		// パーツ数を設定、モデルをバインド、アニメーションをバインド
		CCharacter::SetPartNum(SHINIGAMI_PARTS_MAX);
		CCharacter::BindParts(SHINIGAMI_PARTS_BODY, 56);
		CCharacter::BindParts(SHINIGAMI_PARTS_WEP, 57);
		CCharacter::LoadModelData("./data/ANIMATION/motion_shinigami.txt");
		break;
    case TYPE_PENPEN:
        // 固有の情報
        SetCollisionSizeDefence(D3DXVECTOR2(350.0f, 350.0f));
        m_fSpeed = 5.0f;
        fHP = 100.0f;
        m_fChargeValue = 3.0f;
        m_walkMotion = PENPEN_ANIM_WALK;
        m_attackMotion = PENPEN_ANIM_ATTACK;
        m_deathMotion = PENPEN_ANIM_DEATH;
        m_damageMotion = PENPEN_ANIM_DAMAGE;
        m_nAddScore = 50;
        m_fDiscoveryTargetDistance = PENPEN_DISCOVERY_DISTANCE;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド（ペンペンは、専用のモデルも）
        m_pModelEffect = CModelEffect::Create(39, DEFAULT_VECTOR, DEFAULT_VECTOR, DEFAULT_COLOR);
        m_pModelEffect->SetUseDraw(false);
        CCharacter::SetPartNum(PENPEN_PARTS_MAX);
        CCharacter::BindParts(PENPEN_PARTS_BODY, 36);
        CCharacter::BindParts(PENPEN_PARTS_CUTTER_R, 37);
        CCharacter::BindParts(PENPEN_PARTS_CUTTER_L, 38);
        CCharacter::LoadModelData("./data/ANIMATION/motion_penpen.txt");
        break;
	case TYPE_KIWI:
		SetCollisionSizeDefence(D3DXVECTOR2(350.0f, 350.0f));
		m_fSpeed = 5.0f;
		fHP = 100.0f;
		m_fChargeValue = 1.0f;
		m_walkMotion = KIWI_ANIM_WALK;
		m_deathMotion = KIWI_ANIM_DEATH;
		m_damageMotion = KIWI_ANIM_DAMAGE;
        m_attackMotion = KIWI_ANIM_RUN;
		m_nAddScore = 10000;
		m_fDiscoveryTargetDistance = KIWI_DISCOVERY_DISTANCE;
		CCharacter::SetPartNum(KIWI_PARTS_MAX);
		CCharacter::BindParts(KIWI_PARTS_BODY, 70);
		CCharacter::BindParts(KIWI_PARTS_WING_R, 71);
		CCharacter::BindParts(KIWI_PARTS_WING_L, 72);
		CCharacter::BindParts(KIWI_PARTS_FOOT_R, 73);
		CCharacter::BindParts(KIWI_PARTS_FOOT_L, 74);
		CCharacter::LoadModelData("./data/ANIMATION/motion_kiwi.txt");
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
    // 爆弾から火花を出す
    if (m_Effect.type != NOT_EXIST)
    {
        m_Effect.nCntTrail++;
        if (m_Effect.nCntTrail >= m_Effect.interval)
        {
            m_Effect.nCntTrail = 0;
            CEffect3D::Emit(m_Effect.type, GetPartsPos(KAMIKAZE_PARTS_BOMB_CUBE), GetPartsPos(KAMIKAZE_PARTS_BOMB_CUBE));
        }
    }

    // 位置に移動量を結びつける
    myPos += m_moveAngle * KAMIKAZE_ATK_SPEED;

    // 向きを調整
    RotControl();

    if (m_nCntTime >= KAMIKAZE_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, KAMIKAZE_WAIT_COUNT);

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
        // 胞子音
        CManager::SoundPlay(CSound::LABEL_SE_ATTACK_COMMANDER);

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

//=============================================================================
// シニガミの攻撃
// Author : 池田悠希、後藤慎之助
//=============================================================================
void CEnemy::AtkShinigami(D3DXVECTOR3 &myPos)
{
    // 攻撃開始フラグが立っているなら、攻撃
    if (m_bAtkStartFlag)
    {
        if (m_nCntTime == SHINIGAMI_FIRE_FRAME)
        {
            // 変数宣言
            D3DXVECTOR3 enemyRot = CCharacter::GetRot();                      // 敵の向いている向き
            D3DXVECTOR3 slidePos = DEFAULT_VECTOR;                            // ずらす位置
            D3DXVECTOR3 attackPos = DEFAULT_VECTOR;                           // 攻撃発生位置
            D3DXVECTOR2 collisionSizeDefence = CCharacter::GetCollisionSizeDefence();

            // 攻撃発生位置をずらす
            slidePos.x = collisionSizeDefence.x * -sinf(enemyRot.y);
            slidePos.z = collisionSizeDefence.x * -cosf(enemyRot.y);

            // 攻撃発生位置を決める
            attackPos = myPos + slidePos;

            // 攻撃用の弾を出す（シニガミの攻撃は9999ダメージ固定）
            CBullet::Create(CBullet::TYPE_SHINIGAMI_ATTACK, attackPos, DEFAULT_VECTOR, OBJTYPE_ENEMY);
        }
        else if (m_nCntTime == SHINIGAMI_WHOLE_FRAME)
        {
            // 待機AIに
            SetBaseState(BASE_STATE_WAIT, SHINIGAMI_WAIT_COUNT);
        }
    }
    else
    {
        // 攻撃開始フラグが立っていないなら、ターゲットに向けて移動中
        m_setAnimationThisFrame = m_walkMotion;

        // カウンタを止めておく
        m_nCntTime = 0;

        // 一定範囲内に入るまで追従、入ったら攻撃し待機へ
        if (m_pTarget)
        {
            // ターゲットが生存しているなら（生存していないなら、待機へ）
            if (m_pTarget->GetDisp())
            {
                // 位置に移動量を結びつける
                myPos += m_moveAngle * m_fSpeed;

                // 向きを調整
                RotControl();

                // 現在の位置と、目的地までの移動角度/向きを求める
                D3DXVECTOR3 targetPos = m_pTarget->GetPos();
                float fDestAngle = atan2((myPos.x - targetPos.x), (myPos.z - targetPos.z));
                m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
                SetRotDestY(fDestAngle);

                // 距離が近いなら、攻撃を開始
                float fDistance = GetDistanceXZ(myPos, targetPos);
                if (fDistance <= SHINIGAMI_FIRE_START_DISTANCE)
                {
                    m_bAtkStartFlag = true;
                }
            }
            else
            {
                // 待機AIに
                SetBaseState(BASE_STATE_WAIT, SHINIGAMI_WAIT_COUNT);
            }
        }
        else
        {
            // 待機AIに
            SetBaseState(BASE_STATE_WAIT, SHINIGAMI_WAIT_COUNT);
        }
    }
}

//=============================================================================
// ペンペンの攻撃
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AtkPenpen(D3DXVECTOR3 &myPos)
{
    if (m_nCntTime >= PENPEN_WHOLE_FRAME)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, PENPEN_WAIT_COUNT);
    }
    else if (m_nCntTime == PENPEN_START_FRAME)
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
    else if (m_nCntTime < PENPEN_WHOLE_FRAME && m_nCntTime > PENPEN_START_FRAME)
    {
        // 自身の当たり判定を拡大
        SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 350.0f));

        // 位置に移動量を結びつける
        myPos += m_moveAngle * PENPEN_ATK_SPEED;

        // 向きを調整
        RotControl();

        // 刃を回転、見えるようにも
        D3DXVECTOR3 cutterRot = m_pModelEffect->GetRot();
        cutterRot.y += PENPEN_CUTTER_ROT_SPEED;
        if (cutterRot.y > D3DX_PI)
        {
            cutterRot.y -= D3DX_PI * 2.0f;
        }
        else if (cutterRot.y < -D3DX_PI)
        {
            cutterRot.y += D3DX_PI * 2.0f;
        }
        m_pModelEffect->SetRot(cutterRot);
        m_pModelEffect->SetUseDraw(true);
        m_pModelEffect->SetPos(myPos + D3DXVECTOR3(0.0f, 200.0f, 0.0f));
        SetPartsDisp(PENPEN_PARTS_CUTTER_R, false);
        SetPartsDisp(PENPEN_PARTS_CUTTER_L, false);

        // 攻撃発生
        if (m_nCntTime % PENPEN_INTERVAL_FRAME == 0)
        {
            CBullet::Create(CBullet::TYPE_PENPEN_ATTACK, myPos, DEFAULT_VECTOR, OBJTYPE_ENEMY, m_fStrength);
        }
    }
}

//=============================================================================
// キウイの攻撃(逃げる)
// Author : 池田悠希
//=============================================================================
void CEnemy::AtkKiwi(D3DXVECTOR3 &myPos)
{
	if (m_pTarget)
	{
		if (m_nCntTime >= KIWI_WHOLE_FRAME && D3DXVec3Length(&(m_pTarget->GetPos() - myPos)) > KIWI_RUN_DISTANCE)
		{
			// 待機AIに
			SetBaseState(BASE_STATE_WAIT, KIWI_WAIT_COUNT);
		}
		else
		{
			// 現在の位置と、目的地までの移動角度/向きを求める
			D3DXVECTOR3 targetPos = m_pTarget->GetPos();
			float fDestAngle = atan2((myPos.x - targetPos.x), (myPos.z - targetPos.z));
			m_moveAngle = D3DXVECTOR3(sinf(fDestAngle), 0.0f, cosf(fDestAngle));
			SetRotDestY(atan2((targetPos.x - myPos.x), (targetPos.z - myPos.z)));
			myPos += m_moveAngle * KIWI_ATK_SPEED;
			float fKeepDistance;
			m_pTarget = CGame::GetDistanceAndPointerToClosestPlayer(myPos, fKeepDistance);
			// 向きを調整
			RotControl();
		}
	}
	else
	{
		SetBaseState(BASE_STATE_WAIT, KIWI_WAIT_COUNT);
	}
}
