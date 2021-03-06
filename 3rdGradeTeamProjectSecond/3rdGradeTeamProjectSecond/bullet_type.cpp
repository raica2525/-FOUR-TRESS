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
#include "effectData.h"
#include "fortress.h"

//========================================
// マクロ定義（特徴的な処理をするもののみ）
//========================================

#define COMMON_ROTATE_Z D3DXToRadian(15.0f)

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
    PARAM_HUNTER_SKY_TARGET_ANGLE_Y,
}PARAM_HUNTER_SKY;

//===========================
// ヒーラーの空中攻撃
//===========================
#define HEALER_SKY_WHOLE_FRAME 180
#define HEALER_SKY_INTERVAL 30

//===========================
// エナジーボール
//===========================
#define ENERGY_BALL_ACCEL_VALUE 1.1f
#define ENERGY_BALL_MAX_SPEED 17.5f

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
        m_bUseDraw = false;
        // モデルをバインド
        BindModelData(41);  // 仮にボール
        // エフェクト番号と発生間隔
        m_Effect[0].type = 60;
        m_Effect[0].interval = 5;
        // ヒットエフェクト番号
        m_nIdxHitEffect = 20;
        break;
    case TYPE_THUNDER:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(4000.0f, 1000.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 60;
        m_fDamage = 1000.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通
        bUseShadow = false; // 影を使用しない
                            // エフェクト番号と発生間隔
        m_Effect[0].type = 9;
        m_Effect[0].interval = 12;
        break;
    case TYPE_RAILGUN_LV2:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(500.0f, 500.0f);
        m_fSpeed = 17.5f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 180;
        m_fDamage = 7500.0f;
        m_bUseDraw = false;  // 仮
        m_bHitErase = false;// 貫通
        m_bBreakGoalGate = true;    // ゴールゲートを壊せる
        m_nHitContributionPoint = 16;   // 壊した時の貢献ポイント
                            // エフェクト番号と発生間隔
        m_Effect[0].type = 65;
        m_Effect[0].interval = 12;
        m_Effect[1].type = 59;
        m_Effect[1].interval = 12;
        break;
    case TYPE_RAILGUN_LV3:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 240;
        m_fDamage = 10000.0f;
        m_bUseDraw = false;  // 仮
        m_bHitErase = false;// 貫通
        m_bBreakGoalGate = true;    // ゴールゲートを壊せる
        m_nHitContributionPoint = 24;   // 壊した時の貢献ポイント
        // エフェクト番号と発生間隔
        m_Effect[0].type = 61;
        m_Effect[0].interval = 12;
        m_Effect[1].type = 59;
        m_Effect[1].interval = 12;
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
        m_bUseDraw = false;
        //m_bUseKnockBack = false;// ノックバックは利用しない
        // モデルをバインド
        BindModelData(67);
        break;
    case TYPE_COMMANDER_ATTACK:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(75.0f, 75.0f);
        m_fSpeed = 5.0f;
        m_nLife = 999;
        m_bUseDraw = false;
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK);   // ブロックで反射は、ブロックで消えなくするのとワンセット
        // エフェクト番号と発生間隔
        m_Effect[0].type = 46;
        m_Effect[0].interval = 5;
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
        m_bUseDraw = false; // 1F目は向きを変えるため切った
        m_bHitErase = false;// 貫通（要調整）
        // モデルをバインド
        BindModelData(40);  // 矢
        m_Effect[0].type = 24;
        m_Effect[0].interval = 3;
        break;
    case TYPE_HUNTER_SKY:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 50.0f;
        m_bUseDraw = false; // 1F目は向きを変えるため切った
        m_bHitErase = false;// 貫通
                            // モデルをバインド
        BindModelData(69);
        // エフェクト番号と発生間隔
        m_Effect[0].type = 24;
        m_Effect[0].interval = 5;
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
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通（要調整）
                            // モデルをバインド
        BindModelData(68);
        break;
    case TYPE_TANK_GROUND_LV2:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(200.0f, 200.0f);
        m_fSpeed = 45.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 150.0f;
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通（要調整）
                            // モデルをバインド
        BindModelData(68);
        break;
    case TYPE_TANK_GROUND_LV3:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(250.0f, 250.0f);
        m_fSpeed = 50.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 60;
        m_fDamage = 0.0f;
        m_bUseDraw = false;
        // モデルをバインド
        BindModelData(68);
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
    case TYPE_HEALER_GROUND:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(200.0f, 200.0f);
        m_fSpeed = 35.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_HEAL_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 65;
        m_fDamage = 0.0f;   // 生成時に、現在のチャージ量に応じたものに変える
        m_bUseDraw = false;
        m_bHitErase = false;// 貫通（要調整）
        m_nHitContributionPoint = 1;
        // エフェクト番号と発生間隔
        m_Effect[0].type = 1;
        m_Effect[0].interval = 5;
        break;
    case TYPE_HEALER_SKY:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_HEAL_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_bUseUninit = false;   // 消えない
        m_bUseUpdate = false;   // 更新処理は、プレイヤーが決める
        m_fDamage = 0.0f;       // 生成時に、現在のチャージ量に応じたものに変える
        m_bUseDraw = false;
        m_bHitErase = false;    // 貫通
        m_bUseKnockBack = false;// ノックバックは利用しない
        bUseShadow = false;     // 影を使用しない
        m_nHitContributionPoint = 1;
        break;

	case TYPE_SHINIGAMI_ATTACK:
		m_collisionSize = D3DXVECTOR2(525.0f, 500.0f);
		m_fSpeed = 0.0f;
		BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
		BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
		m_nLife = 15;
		m_fDamage = 9999.0f;       // 即死攻撃
		m_bUseDraw = false;
		m_bHitErase = false;    // 貫通
		bUseShadow = false;     // 影を使用しない
		break;

    case TYPE_PENPEN_ATTACK:
        m_collisionSize = D3DXVECTOR2(575.0f, 350.0f);
        m_fSpeed = 0.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 10;
        m_fDamage = 30.0f;
        m_bUseDraw = false;
        m_bHitErase = false;    // 貫通
        bUseShadow = false;     // 影を使用しない
        break;
    case TYPE_ENERGY_BALL:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 1.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_CHARGE_FORTRESS);
        BITON(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK);
        m_nLife = 999;
        m_fDamage = 0.0f;
        m_bUseDraw = false;
        m_bHitErase = true;
        bUseShadow = false; // 影を使用しない
                            // エフェクト番号と発生間隔
        m_Effect[0].type = CEffectData::TYPE_LIGHTNING_1;
        m_Effect[0].interval = 4;
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
// Z軸を回転しながら移動する弾の共通処理
// Author : 後藤慎之助
//=============================================================================
void CBullet::CommonRotateZ(D3DXVECTOR3 & myPos)
{
    // 移動
    myPos += m_moveAngle * m_fSpeed;

    // 向きを移動の向きに合わせる
    m_nCntTime++;
    if (m_nCntTime == 1)
    {
        m_bUseDraw = true;
        float fAngle = GetAngleToTargetXZ(myPos, m_posOld);
        SetRot(D3DXVECTOR3(0.0f, fAngle, 0.0f));
    }

    // 回転
    D3DXVECTOR3 rot = GetRot();
    rot.z += D3DXToRadian(COMMON_ROTATE_Z);
    SetRot(rot);
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
// ハンターの地上攻撃弾の移動処理
// Author : 後藤慎之助
//=============================================================================
void CBullet::HunterGroundMove(D3DXVECTOR3 &myPos)
{
    // 移動
    myPos += m_moveAngle * m_fSpeed;

    // 向きを移動の向きに合わせる
    m_nCntTime++;
    if (m_nCntTime >= 1)
    {
        m_bUseDraw = true;
        float fAngle = GetAngleToTargetXZ(myPos, m_posOld);
        SetRot(D3DXVECTOR3(0.0f, fAngle, 0.0f));
    }
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
        m_afParam[PARAM_HUNTER_SKY_TARGET_ANGLE_Y] = atan2(fDistance, fHeight);

        // 移動の角度に反映
        m_moveAngle.x = -sinf(fAngleXZ);
        m_moveAngle.y = -cosf(m_afParam[PARAM_HUNTER_SKY_TARGET_ANGLE_Y]);
        m_moveAngle.z = -cosf(fAngleXZ);
    }

    // 移動
    myPos += m_moveAngle * m_fSpeed;

    // 向きを移動の向きに合わせる
    if (m_nCntTime >= 1)
    {
        m_bUseDraw = true;
        float fAngle = GetAngleToTargetXZ(myPos, m_posOld);
        float fAngleY = D3DXToRadian(50.0f);
        if (m_posOld.y < myPos.y)
        {
            fAngleY = m_afParam[PARAM_HUNTER_SKY_TARGET_ANGLE_Y];
        }

        // Z回転
        D3DXVECTOR3 rot = GetRot();
        rot.z += D3DXToRadian(COMMON_ROTATE_Z);

        SetRot(D3DXVECTOR3(-fAngleY, fAngle, rot.z));
    }
}

//=============================================================================
// ヒーラーの空中攻撃処理
// Author : 後藤慎之助
//=============================================================================
bool CBullet::HealerSkyUseCollision(void)
{
    // カウンタ加算
    m_nCntTime++;

    // 当たり判定を使うかどうかの発生間隔
    bool bUseCollision = false;
    if (m_nCntTime % HEALER_SKY_INTERVAL == 0)
    {
        CEffect3D::Emit(CEffectData::TYPE_HEAL, GetPos(), GetPos());
        bUseCollision = true;
        memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    }

    // カウンタが発生時間の最大を超えたら、更新処理を止める
    if (m_nCntTime > HEALER_SKY_WHOLE_FRAME)
    {
        m_bUseUpdate = false;
    }

    return bUseCollision;
}

//=============================================================================
// エナジーボールの移動処理
// Author : 後藤慎之助
//=============================================================================
void CBullet::EnergyBallMove(D3DXVECTOR3 &myPos)
{
    // 移動量
    D3DXVECTOR3 move = DEFAULT_VECTOR;

    // 速度を加速させる
    m_fSpeed *= ENERGY_BALL_ACCEL_VALUE;
    if (m_fSpeed > ENERGY_BALL_MAX_SPEED)
    {
        m_fSpeed = ENERGY_BALL_MAX_SPEED;
    }

    // 移動要塞(ターゲット)の位置を取得
    D3DXVECTOR3 targetPos = CGame::GetFortress()->GetPos() + D3DXVECTOR3(0.0f, 700.0f, 0.0f);

    // 角度を求める
    float fAngle = atan2f((myPos.x - targetPos.x), (myPos.z - targetPos.z));

    // 横移動の移動量を決める
    move.x = -sinf(fAngle) * m_fSpeed;
    move.z = -cosf(fAngle) * m_fSpeed;

    // 高さを比べ、縦移動を調整
    float fDistanceY = 0.0f;
    float fAdjustment = 0.0f;
    if (myPos.y < targetPos.y)
    {
        fAdjustment = 1.0f;
        fDistanceY = targetPos.y - myPos.y;
    }
    else if (myPos.y > targetPos.y)
    {
        fAdjustment = -1.0f;
        fDistanceY = myPos.y - targetPos.y;
    }

    // 縦移動の角度を決める
    move.y = (fDistanceY / m_fSpeed) * fAdjustment;

    // 位置に移動量を加算
    myPos += move;
}