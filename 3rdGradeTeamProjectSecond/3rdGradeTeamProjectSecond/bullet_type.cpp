//======================================================================================
//
// 弾の種類派生処理 (bullet_type.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "effect3d.h"
#include "modelEffect.h"

//========================================
// マクロ定義（特徴的な処理をするもののみ）
//========================================
//===========================
// コマンダーの弾
//===========================
#define COMMANDER_ATTACK_GRAVITY_VALUE -0.1f
#define COMMANDER_ATTACK_GRAVITY_LIMIT -10.0f

//===========================
// ハンターの空中攻撃
//===========================
#define HUNTER_SKY_HOMING_START_FRAME 30
#define HUNTER_SKY_HOMING_SPEED 60.0f
// 汎用パラメータの内訳
typedef enum
{
    PARAM_HUNTER_SKY_TARGET_POS_X = 0,
    PARAM_HUNTER_SKY_TARGET_POS_Y,
    PARAM_HUNTER_SKY_TARGET_POS_Z,
}PARAM_HUNTER_SKY;

//=============================================================================
// 種類ごとの初期設定
// Author : 後藤慎之助
//=============================================================================
void CBullet::SetupInfoByType(float fStrength, const D3DXVECTOR3 pos)
{
    // 影を生成するかどうか
    bool bUseShadow = true;

    switch (m_type)
    {
    case TYPE_ARMY_ATTACK:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 50.0f;
        m_bUseDraw = true;  // 仮
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_RAILGUN_LV2:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(500.0f, 500.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 180;
        m_fDamage = 5000.0f;
        m_bUseDraw = true;  // 仮
        m_bHitErase = false;// 貫通
        m_bBreakGoalGate = true;    // ゴールゲートを壊せる
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_RAILGUN_LV3:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 10000.0f;
        m_bUseDraw = true;  // 仮
        m_bHitErase = false;// 貫通
        m_bBreakGoalGate = true;    // ゴールゲートを壊せる
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_KAMIKAZE_EX:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 60;
        m_fDamage = 300.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通
        bUseShadow = false; // 影を使用しない
        break;
    case TYPE_CANNON_ATTACK:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(75.0f, 75.0f);
        m_fSpeed = 25.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 15.0f;
        m_bUseDraw = true;
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_COMMANDER_ATTACK:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(75.0f, 75.0f);
        m_fSpeed = 5.0f;
        m_nLife = 999;
        m_bUseDraw = true;
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK);   // ブロックで反射は、ブロックで消えなくするのとワンセット
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_HUNTER_GROUND:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 50.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK);
        m_nLife = 45;
        m_fDamage = 70.0f;
        m_bUseDraw = true;
        m_bHitErase = false;// 貫通（要調整）
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_HUNTER_SKY:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 40.0f;
        m_bUseDraw = true;
        m_bHitErase = false;// 貫通
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_CARRIER_SKY:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(2000.0f, 500.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_PULL_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 30;
        m_fDamage = 0.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通
        bUseShadow = false; // 影を使用しない
        break;
    case TYPE_TANK_GROUND_LV1:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(150.0f, 150.0f);
        m_fSpeed = 40.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 50.0f;
        m_bUseDraw = true;
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_TANK_GROUND_LV2:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(200.0f, 200.0f);
        m_fSpeed = 45.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 150.0f;
        m_bUseDraw = true;
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_TANK_GROUND_LV3:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(250.0f, 250.0f);
        m_fSpeed = 50.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 0.0f;
        m_bUseDraw = true;
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_TANK_GROUND_EX:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(1250.0f, 1250.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 60;
        m_fDamage = 450.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通
        bUseShadow = false; // 影を使用しない
        break;
    }

    // 強さを反映
    //m_fSpeed *= fStrength;    // 移動速度も速くなるのは違和感？
    m_fDamage *= fStrength;

    // 影生成
    if (bUseShadow)
    {
        m_pEffect3d_Shadow = CEffect3D::Create(CEffectData::TYPE_SHADOW, D3DXVECTOR3(pos.x, SHADOW_POS_Y, pos.z));
        m_pEffect3d_Shadow->SetSize(D3DXVECTOR3(m_collisionSize.x, m_collisionSize.x, 0.0f));
        m_pEffect3d_Shadow->SetDisp(false); // バレット側で描画を管理するため
    }
}

//=============================================================================
// コマンダーの弾の移動処理
// Author : 後藤慎之助
//=============================================================================
void CBullet::CommanderAttackMove(D3DXVECTOR3 &myPos)
{
    // カウンタ加算
    m_nCntTime++;

    // 重力を使うなら
    float fGravity = COMMANDER_ATTACK_GRAVITY_VALUE * m_nCntTime;
    if (fGravity < COMMANDER_ATTACK_GRAVITY_LIMIT)
    {
        fGravity = COMMANDER_ATTACK_GRAVITY_LIMIT;
    }
    myPos += m_moveAngle * m_fSpeed + D3DXVECTOR3(0.0f, fGravity, 0.0f);
}

//=============================================================================
// ハンターの空中攻撃弾の移動処理
// Author : 後藤慎之助
//=============================================================================
void CBullet::HunterSkyMove(D3DXVECTOR3 &myPos)
{
    // カウンタ加算
    m_nCntTime++;

    // ホーミング処理
    if (m_nCntTime == HUNTER_SKY_HOMING_START_FRAME)
    {
        // 速度を加速
        m_fSpeed = HUNTER_SKY_HOMING_SPEED;

        // 横の角度を決める
        float fAngleXZ = atan2f((myPos.x - m_afParam[PARAM_HUNTER_SKY_TARGET_POS_X]), (myPos.z - m_afParam[PARAM_HUNTER_SKY_TARGET_POS_Z]));

        // 縦の角度を決める
        float fDistance = sqrtf(
            powf((m_afParam[PARAM_HUNTER_SKY_TARGET_POS_X] - myPos.x), 2.0f) +
            powf((m_afParam[PARAM_HUNTER_SKY_TARGET_POS_Z] - myPos.z), 2.0f));
        float fHeight = fabsf(m_afParam[PARAM_HUNTER_SKY_TARGET_POS_Y] - myPos.y);
        float fAngleY = atan2(fDistance, fHeight);

        // 移動の角度に反映
        m_moveAngle.x = -sinf(fAngleXZ);
        m_moveAngle.y = -cosf(fAngleY);
        m_moveAngle.z = -cosf(fAngleXZ);
    }

    // 移動
    myPos += m_moveAngle * m_fSpeed;
}