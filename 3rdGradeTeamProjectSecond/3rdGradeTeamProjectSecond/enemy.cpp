//======================================================================================
//
// エネミー処理 (enemy.cpp)
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
#include "debug.h"
#include "bullet.h"
#include "fortress.h"
#include "item.h"

//========================================
// マクロ定義
//========================================
// 基本死亡時貢献度
#define DEFAULT_DEATH_CONTRIBUTION 1

// 出現処理周り
#define APPEAR_WAIT_FRAME 30    // 何フレームに一回検知するかの待機フレーム

// 発射までのチャージ時間
#define CHARGE_FIRE_FRAME 90

// 巡回が終わるカウンタ
#define PATROL_COUNT_MAX 180
#define PATROL_COUNT_MIN 60

// 待機が終わるカウンタ
#define WAIT_COUNT_AFTER_PATROL 30
#define WAIT_COUNT_AFTER_DISCOVERY 20
#define WAIT_COUNT_AFTER_DAMAGE 25

// チャージ量に応じた、落とす電池の見た目の変化
#define CHARGE_VALUE_DENTI_3 10.0f
#define CHARGE_VALUE_DENTI_1 50.0f

// ダメージを受けた際のフレーム
#define DAMAGE_FRAME 30
#define DEATH_FRAME 50

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CEnemy::CEnemy() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_SPIDER;
    m_fSpeed = 0.0f;
    m_fStrength = 1.0f;
    m_fChargeValue = NOT_EXIST_F;

    m_nCntTime = 0;
    m_bSquashedByFortress = true;

    m_appearState = APPEAR_STATE_EXIST;
    m_bDeath = false;
    m_baseState = BASE_STATE_WAIT;

    m_walkMotion = 0;
    m_attackMotion = 0;
    m_damageMotion = 0;
    m_deathMotion = 0;

    m_fSearchDistanceForAppear = 0.0f;
    m_patrolCentralPos = DEFAULT_VECTOR;
    m_moveAngle = DEFAULT_VECTOR;
    m_nPatrolDistance = 0;
    m_nCurrentStateEndFrame = 0;

    m_bWarning = false;
    m_fDiscoveryTargetDistance = 0.0f;
    m_pTarget = NULL;
    m_setAnimationThisFrame = 0;

    m_bUseCommonAtkFollow = false;
    m_targetTrend = TARGET_TREND_PLAYER;
    m_nAddScore = 1;
    m_nWhoContribution = NOT_EXIST;
    m_nDeathContributionPoint = DEFAULT_DEATH_CONTRIBUTION;

    m_Effect.type = NOT_EXIST;
    m_Effect.interval = 1;
    m_Effect.nCntTrail = 0;
 
    m_bDeathBySquashed = false;
    m_bAtkStartFlag = false;
    m_pModelEffect = NULL;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 種類ごとの初期設定
    SetupInfoByType();

    // キャラクターに反映
    CCharacter::Init(pos, DEFAULT_SCALE);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Uninit(void)
{
    // モデルエフェクトを使っていたものは、消すフラグを立てる（アルファ値が0を下回ったら消す処理を代用）
    if (m_pModelEffect)
    {
        m_pModelEffect->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f));
    }

    CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Update(void)
{
    // ダメージによって攻撃をリセットするフラグが立っているなら
    if (GetResetAttackByDamage())
    {
        SetBaseState(BASE_STATE_DAMAGE, DAMAGE_FRAME);
        SetResetAttackByDamage(false);
    }

    // 負傷時間があるなら、カウンタを下げる
    CntDownTakeDamageTime();

    // 出現していないなら、出現処理
    if (m_appearState != APPEAR_STATE_EXIST)
    {
        Appear();
    }
    else
    {
        // モーションをまずは待機にする
        m_setAnimationThisFrame = 0;

        // 位置、移動量、負傷状態を取得
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
        D3DXVECTOR3 myPos = DEFAULT_VECTOR;
        D3DXVECTOR3 move = DEFAULT_VECTOR;
        myPos = GetPos();
        move = GetMove();

        // 1F前の位置を記憶
        SetPosOld(myPos);

        // 1F前の移動量を記憶
        SetMoveOld(move);

        // 横と奥行きの移動量制御
        ControlMove(move.x);
        ControlMove(move.z);

        // 移動量と位置を結びつける
        myPos += move;

        // AI処理
        switch (m_baseState)
        {
        case BASE_STATE_WAIT:
            WaitAI(myPos);
            break;
        case BASE_STATE_PATROL:
            PatrolAI(myPos);
            break;
        case BASE_STATE_ATTACK:
            AttackAI(myPos);
            break;
        case BASE_STATE_DAMAGE:
            DamageAI();
            break;
        case BASE_STATE_DEATH:
            m_nCntTime++;
            m_setAnimationThisFrame = m_deathMotion;
            break;
        }

        // 移動要塞に踏みつぶされるかどうか
        SquashedByFortress(myPos);

        // マップ制限
        D3DXVECTOR3 myCubeSize = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CGame::MapLimit(myPos, GetPosOld(), myCubeSize);

        // 位置、移動量を反映
        SetPos(myPos);
        SetMove(move);

        // アニメーションさせる
        if (GetAnimation())
        {
            GetAnimation()->SetAnimation(m_setAnimationThisFrame);
        }
        CCharacter::Update();

#ifdef COLLISION_TEST
        D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 65);
#endif // COLLISION_TEST

        // ライフがなくなったら消す
        float fLife = GetLife();
        if (fLife <= 0.0f)
        {
            // 体力の下限
            fLife = 0.0f;

            // 移動要塞に踏みつぶされなくなる
            m_bSquashedByFortress = false;

            // 死亡モーションがないなら
            if (m_deathMotion == 0)
            {
                // 即座に消す
                DeathOneFrame(myPos);
            }
            else
            {
                // 移動要塞に踏みつぶされたなら
                if (m_bDeathBySquashed)
                {
                    // 即座に消す
                    DeathOneFrame(myPos);
                }
                else
                {
                    // 死亡状態演出
                    m_baseState = BASE_STATE_DEATH;

                    // 一定カウンタで、消す
                    if (m_nCntTime >= DEATH_FRAME)
                    {
                        DeathOneFrame(myPos);
                    }
                }
            }
        }
    }
}

//=============================================================================
// 死亡時1Fだけ通る処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::DeathOneFrame(D3DXVECTOR3 myPos)
{
    // ラストヒットがプレイヤーなら、アイテムを出しスコアも加算
    OBJTYPE lastHit = GetLastHit();
    if (lastHit == OBJTYPE_PLAYER)
    {
        // アイテム
        CItem::TYPE dentiType = CItem::TYPE_DENTI_5;
        if (m_fChargeValue >= CHARGE_VALUE_DENTI_3 && m_fChargeValue < CHARGE_VALUE_DENTI_1)
        {
            dentiType = CItem::TYPE_DENTI_3;
        }
        else if (m_fChargeValue >= CHARGE_VALUE_DENTI_1)
        {
            dentiType = CItem::TYPE_DENTI_1;
        }
        // 最低保証
        if (m_fChargeValue < 1.0f)
        {
            m_fChargeValue = 1.0f;
        }
        CItem::Create(dentiType, myPos, m_fChargeValue);
        CEffect3D::Emit(CEffectData::TYPE_ENEMY_DESTROYING, myPos, myPos);

        // スコア加算
        CGame::AddScore(m_nAddScore);

        // 貢献者のポイント加算
        if (m_nWhoContribution != NOT_EXIST)
        {
            CGame::GetPlayer(m_nWhoContribution)->GainContribution(m_nDeathContributionPoint);
        }
    }
    else
    {
        // カミカゼの場合、プレイヤー以外にやられたら爆発を生み出す
        if (m_type == TYPE_KAMIKAZE)
        {
            // カミカゼ爆発音
            CManager::SoundPlay(CSound::LABEL_SE_EXPLOSION_KAMIKAZE);
            CBullet::Create(CBullet::TYPE_KAMIKAZE_EX, myPos, DEFAULT_VECTOR, OBJTYPE_ENEMY, m_fStrength);
            CEffect3D::Emit(CEffectData::TYPE_EXPLOSION_0, myPos, myPos);
            CEffect3D::Emit(CEffectData::TYPE_EXPLOSION_1, myPos, myPos);
            CEffect3D::Emit(CEffectData::TYPE_EXPLOSION_2, myPos, myPos);
        }
        else
        {// カミカゼ以外は通常のエフェクトを出す
            CEffect3D::Emit(CEffectData::TYPE_ENEMY_DESTROYING, myPos, myPos);
        }
    }

    // 終了処理
    Uninit();
}

//=============================================================================
// 再巡回処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::RePatrol(void)
{
    // プレイヤーが全員やられているなら、移動要塞を狙う（ほぼ詰み）
    if (!CGame::GetDispAnyPlayer())
    {
        m_bWarning = true;
        m_pTarget = (CCharacter*)CGame::GetFortress();
        SetBaseState(BASE_STATE_ATTACK);
    }
    else
    {
        m_bWarning = false;
        SetBaseState(BASE_STATE_PATROL);
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Draw(void)
{
    // 出現しているなら描画
    if (m_appearState == APPEAR_STATE_EXIST)
    {
        CCharacter::Draw();
    }
}

//=============================================================================
// 生成処理
// Author : 後藤慎之助
//=============================================================================
CEnemy *CEnemy::Create(int type, D3DXVECTOR3 pos, float fStrength, int appearState, float fChargeValue, float fSearchDistanceForAppear)
{
    // メモリ確保
    CEnemy *pEnemy = NULL;
    pEnemy = new CEnemy;

    // 先に引数を結びつけておく
    pEnemy->m_type = type;
    pEnemy->CCharacter::SetPos(pos);
    pEnemy->m_fStrength = fStrength;
    pEnemy->m_appearState = appearState;
    pEnemy->m_fSearchDistanceForAppear = fSearchDistanceForAppear;
    pEnemy->m_patrolCentralPos = pos;

    // 仮に向きを正面に
    pEnemy->CCharacter::SetRot(DEFAULT_VECTOR);

    // 初期化
    pEnemy->Init(pos, DEFAULT_SCALE);

    // 出現していないなら、無敵にしておく
    if (pEnemy->m_appearState != APPEAR_STATE_EXIST)
    {
        pEnemy->SetInvincible(true);
    }

    // チャージ量をデフォルト以外の値にしているなら、それを優先
    if (fChargeValue != NOT_EXIST_F)
    {
        pEnemy->m_fChargeValue = fChargeValue;
    }

    return pEnemy;
}

//=============================================================================
// ターゲット発見処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::DiscoveryTarget(CCharacter *pTarget)
{
    // 警戒中でなかったら
    if (!m_bWarning)
    {
        // 待機状態にする
        SetBaseState(BASE_STATE_WAIT, WAIT_COUNT_AFTER_DISCOVERY);
    }

    // 警戒中に
    m_bWarning = true;

    // ターゲットを結びつける
    if (pTarget)
    {
        m_pTarget = pTarget;
    }

    // ここで、ビックリマーク的なものを出す

}

//=============================================================================
// 出現処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Appear(void)
{
    // 数フレームに一回の処理にする
    m_nCntTime++;
    if (m_nCntTime < APPEAR_WAIT_FRAME)
    {
        return;
    }
    m_nCntTime = 0;

    // 位置を取得
    D3DXVECTOR3 myPos = GetPos();
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;

    // 出現状態によって場合分け
    switch (m_appearState)
    {
    case APPEAR_STATE_WAIT_FORTRESS:
    {
        // 移動要塞を取得
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            targetPos = pFortress->GetPos();
        }
    }
    break;
    case APPEAR_STATE_WAIT_PLAYER:
    {
        // プレイヤーを取得
        float fKeepDistance = 999999.9f;        // 距離
        bool bIsKeepDistanceChanged = false;    // 距離が更新されたかどうか
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_PLAYER);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_PLAYER); nCntScene++)
        {
            // 中身があるなら
            if (pScene)
            {
                // 次のシーンを記憶
                CScene*pNextScene = pScene->GetNextScene();

                // プレイヤーにキャスト
                CPlayer *pPlayer = (CPlayer*)pScene;

                // プレイヤーが表示されているなら
                if (pPlayer->GetDisp())
                {
                    // プレイヤーの位置
                    D3DXVECTOR3 playerPos = pPlayer->GetPos();

                    // 距離計算
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - playerPos.x), 2.0f) +
                        powf((myPos.z - playerPos.z), 2.0f));

                    // 距離が今キープしているものより近いなら、向きを更新
                    if (fKeepDistance > fCurrentDistance)
                    {
                        fKeepDistance = fCurrentDistance;
                        targetPos = playerPos;
                        bIsKeepDistanceChanged = true;
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }

        // 距離が更新されていないなら、関数を抜ける
        if (!bIsKeepDistanceChanged)
        {
            return;
        }
    }
    break;
    default:
        return;
        break;
    }

    // 検知距離に入ったら、向きをターゲットに変えて出現（ここで無敵解除）
    if (IsInsideCircleXZ(myPos, targetPos, m_fSearchDistanceForAppear))
    {
        float fAngleToTarget = GetAngleToTargetXZ(targetPos, myPos);
        SetRotDestY(fAngleToTarget);
        SetRotY(fAngleToTarget);
        m_appearState = APPEAR_STATE_EXIST;
        SetInvincible(false);
        // 敵出現エフェクト
        CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_0, GetPos(), GetPos());
        CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_1, GetPos(), GetPos());
    }
}

//=============================================================================
// 移動要塞に踏みつぶされるかどうかの処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::SquashedByFortress(D3DXVECTOR3 myPos)
{
    if (m_bSquashedByFortress)
    {
        // 移動要塞を取得
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            // 当たっているなら
            D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
            if (IsCollisionCylinder(myPos, collisionSizeDefence, pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
            {
                // HP0に
                TakeDamage(FORTRESS_CRUSH_DAMAGE, myPos, pFortress->GetPos(), OBJTYPE_FORTRESS);

                // 移動要塞に踏みつぶされた
                m_bDeathBySquashed = true;
            }
        }
    }
}

//=============================================================================
// 基本状態設定 処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::SetBaseState(BASE_STATE nextBaseState, int nNextStateEndFrame)
{
    // 死亡状態からは、いかなる状態にもならない
    if (m_baseState != BASE_STATE_DEATH)
    {
        // 状態にかかわるメンバ変数を再設定
        m_baseState = nextBaseState;
        m_nCntTime = 0;
        m_bUseCommonAtkFollow = false;
        m_bAtkStartFlag = false;

        // 自分の種類によって、再設定するもの
        if (m_type == TYPE_PENPEN)
        {
            m_pModelEffect->SetUseDraw(false);
            SetCollisionSizeDefence(D3DXVECTOR2(350.0f, 350.0f));
            SetPartsDisp(PENPEN_PARTS_CUTTER_R, true);
            SetPartsDisp(PENPEN_PARTS_CUTTER_L, true);
        }

        // 次の状態によって、取得するもの
        switch (nextBaseState)
        {
        case BASE_STATE_ATTACK:
        {
            // 警戒中なら、対象との距離が離れているときに追従にする
            if (m_bWarning)
            {
                // ターゲットとの距離が遠いなら、追従
                if (m_pTarget)
                {
                    D3DXVECTOR3 myPos = GetPos();
                    D3DXVECTOR3 targetPos = m_pTarget->GetPos();
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - targetPos.x), 2.0f) +
                        powf((myPos.z - targetPos.z), 2.0f));
                    if (fCurrentDistance > m_fDiscoveryTargetDistance)
                    {
                        // 現在の位置と、目的地までの移動角度/向きを求める
                        float fDestAngle = atan2((myPos.x - targetPos.x), (myPos.z - targetPos.z));
                        m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
                        SetRotDestY(fDestAngle);
                        m_bUseCommonAtkFollow = true;   // 共通の攻撃フラグを立てる
                    }
                }
            }
        }
        break;
        case BASE_STATE_PATROL:
        {
            // 次の目的地を決める
            D3DXVECTOR3 destPos = DEFAULT_VECTOR;
            destPos.x = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.x;
            destPos.z = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.z;

            // 現在の位置と、目的地までの移動角度/向きを求める
            D3DXVECTOR3 myPos = GetPos();
            float fDestAngle = atan2((myPos.x - destPos.x), (myPos.z - destPos.z));
            m_moveAngle = D3DXVECTOR3(-sinf(fDestAngle), 0.0f, -cosf(fDestAngle));
            SetRotDestY(fDestAngle);

            // 巡回時間を得る
            m_nCurrentStateEndFrame = GetRandNum(PATROL_COUNT_MAX, PATROL_COUNT_MIN);
        }
        break;
        }

        // 次の状態の終了時間を得る
        if (nNextStateEndFrame != NOT_EXIST)
        {
            m_nCurrentStateEndFrame = nNextStateEndFrame;
        }
    }
}

//=============================================================================
// 待機AI処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::WaitAI(D3DXVECTOR3& myPos)
{
    // カウンタを加算
    m_nCntTime++;

    // 警戒中なら、向きをターゲットに追従
    if (m_bWarning)
    {
        if (m_pTarget)
        {
            if (m_pTarget->GetDisp())
            {
                SetRotDestY(GetAngleToTargetXZ(m_pTarget->GetPos(), myPos));
                RotControl();
            }
            else
            {
                // ターゲットがやられたなら、即座に警戒を解いて再巡回
                RePatrol();
            }
        }
    }

    // 待機が終わるカウンタなら
    if (m_nCntTime >= m_nCurrentStateEndFrame)
    {
        // 警戒中なら
        if (m_bWarning)
        {
            // 攻撃状態に
            SetBaseState(BASE_STATE_ATTACK);
        }
        else
        {
            // 巡回状態に
            SetBaseState(BASE_STATE_PATROL);
        }
    }
}

//=============================================================================
// 巡回AI処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::PatrolAI(D3DXVECTOR3& myPos)
{
    // カウンタを加算
    m_nCntTime++;

    // 巡回が終わるカウンタなら
    if (m_nCntTime >= m_nCurrentStateEndFrame)
    {
        // 待機AIに
        SetBaseState(BASE_STATE_WAIT, WAIT_COUNT_AFTER_PATROL);
        return;
    }

    // 位置に移動量を結びつける
    myPos += m_moveAngle * m_fSpeed;

    // ターゲット発見処理
    float fKeepDistance = 0.0f;
    CCharacter *pTarget = NULL;
    switch (m_targetTrend)
    {
    case TARGET_TREND_PLAYER:
        pTarget = CGame::GetDistanceAndPointerToClosestPlayer(myPos, fKeepDistance);
        break;
    case TARGET_TREND_FORTRESS:
        pTarget = CGame::GetDistanceAndPointerToClosestFortress(myPos, fKeepDistance);
        break;
    case TARGET_TREND_PLAYER_AND_FORTRESS:
        pTarget = CGame::GetDistanceAndPointerToClosestPlayerOrFortress(myPos, fKeepDistance);
        break;
    }

    // ターゲットとの距離が発見距離より小さいなら、発見処理へ
    if (fKeepDistance <= m_fDiscoveryTargetDistance)
    {
        if (pTarget)
        {
            DiscoveryTarget(pTarget);
        }
    }

    // 歩行モーションに
    m_setAnimationThisFrame = m_walkMotion;

    // 向きを調整
    RotControl();
}

//=============================================================================
// 攻撃AI処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::AttackAI(D3DXVECTOR3 &myPos)
{
    // カウンタ加算
    m_nCntTime++;

    // 追従するなら
    if (m_bUseCommonAtkFollow)
    {
        AtkCommonFollow(myPos);

        // 移動モーションに
        m_setAnimationThisFrame = m_walkMotion;
    }
    else
    {
        // 攻撃モーションに（種類ごとの処理で、攻撃モーション以外に変える場合があるので、先に設定）
        m_setAnimationThisFrame = m_attackMotion;

        // 種類ごとの処理
        switch (m_type)
        {
        case TYPE_ARMY:
            AtkArmy(myPos);
            break;
        case TYPE_KAMIKAZE:
            AtkKamikaze(myPos);
            break;
        case TYPE_CANNON:
            AtkCannon(myPos);
            break;
        case TYPE_COMMANDER:
            AtkCommander(myPos);
            break;
		case TYPE_SHINIGAMI:
			AtkShinigami(myPos);
            break;
        case TYPE_PENPEN:
            AtkPenpen(myPos);
            break;
        }
    }
}

//=============================================================================
// ダメージAI処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::DamageAI(void)
{
    // カウンタを加算
    m_nCntTime++;

    // ダメージモーションが終わるカウンタなら
    if (m_nCntTime >= m_nCurrentStateEndFrame)
    {
        // ターゲットがいるなら攻撃AIに
        if (m_pTarget)
        {
            SetBaseState(BASE_STATE_ATTACK, WAIT_COUNT_AFTER_DAMAGE);
        }
        else
        {
            // ターゲットがいないなら巡回へ
            RePatrol();
        }
    }

    // ダメージモーションに
    m_setAnimationThisFrame = m_damageMotion;
}