//======================================================================================
//
// 移動要塞処理 (fortress.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "fortress.h"
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
#include "block.h"
#include "fade.h"
#include "camera.h"

//========================================
// マクロ定義
//========================================
// 必要チャージ量
#define CHARGE_VALUE_LV1 50.0f
#define CHARGE_VALUE_LV2 100.0f
#define CHARGE_VALUE_LV3 150.0f

// 発射までのチャージ時間
#define CHARGE_FIRE_FRAME_LV1 30
#define CHARGE_FIRE_FRAME_LV2 60
#define CHARGE_FIRE_FRAME_LV3 90

// 貢献度
#define CHARGE_POINT_LV1 5
#define CHARGE_POINT_LV2 10
#define CHARGE_POINT_LV3 15

// 体力周り
#define MAX_LIFE 3000.0f
#define SMOKE_EFFECT_LIFE 1000.0f

// タイヤの回転
#define TIRE_ROT_SPEED D3DXToRadian(1.0f)

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CFortress::CFortress() :CCharacter(OBJTYPE::OBJTYPE_FORTRESS)
{
    m_fSpeed = 0.0f;

    m_bSearchRoad = true;
    m_moveAngle = DEFAULT_VECTOR;
    m_pTargetRoad = NULL;
    m_bNowWhoRiding = false;

    m_fChargeValue = 150.0f;
    m_bAttackPhase = false;
    m_nCntTime = 0;

    m_bDisp = true;
    m_nWhoAttackPhase = 0;

    // エフェクト
    for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
    {
        m_Effect[nCnt].type = NOT_EXIST;
        m_Effect[nCnt].interval = 1;
        m_Effect[nCnt].nCntTrail = 0;
    }
    m_fTireRotAngle = 0.0f;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CFortress::~CFortress()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CFortress::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 初期設定
    SetCollisionSizeDefence(D3DXVECTOR2(1450.0f, 1000.0f));
    m_fSpeed = 4.0f;    // 要変更
    SetUpLife(MAX_LIFE);
    SetTakeKnockBack(false);

    // パーツ数を設定、モデルをバインド、アニメーションをバインド
    CCharacter::SetPartNum(PARTS_MAX);
    CCharacter::BindParts(PARTS_BODY, 55);
    CCharacter::BindParts(PARTS_CANNON_CENTER, 50);
    CCharacter::BindParts(PARTS_SEAT, 50);
    CCharacter::BindParts(PARTS_FIRE_POS, 50);
    CCharacter::BindParts(PARTS_TIRE_1, 64);
    CCharacter::BindParts(PARTS_TIRE_2, 64);
    CCharacter::BindParts(PARTS_TIRE_3, 64);
    CCharacter::BindParts(PARTS_TIRE_4, 64);
    CCharacter::SetDontUseAnimation();
    CCharacter::LoadModelData("./data/ANIMATION/motion_fortress.txt");

    // キャラクターに反映
    CCharacter::Init(pos, DEFAULT_SCALE);

    // エフェクトの設定
    // 煙
    m_Effect[EFFECT_SMOKE].type = CEffectData::TYPE_SMOKE;                  // エフェクトの種類
    m_Effect[EFFECT_SMOKE].interval = 18;                                   // エフェクトの発生感覚
    m_Effect[EFFECT_LIGHTNING].type = CEffectData::TYPE_LIGHTNING_RANGE;    // エフェクトの種類
    m_Effect[EFFECT_LIGHTNING].interval = 20;                                // エフェクトの発生感覚
    m_Effect[EFFECT_LIGHTNING_CHARGE_0].interval = 30;                                  // エフェクトの発生感覚
    m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV1;    // チャージ時の電気エフェクト(Lvによって変更)
    m_Effect[EFFECT_LIGHTNING_CHARGE_1].type = CEffectData::TYPE_LIGHTNING_CHARGE_2;    // チャージLv2以降の光のエフェクト
    // 電磁砲準備
    m_Effect[EFFECT_LIGHTNING_SETUP].type = CEffectData::TYPE_LIGHTNING_SETUP;          // エフェクトの種類
    m_Effect[EFFECT_LIGHTNING_SETUP].interval = 20;                                     // エフェクトの発生感覚

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::Update(void)
{
    // 負傷時間があるなら、カウンタを下げる
    CntDownTakeDamageTime();

    // 位置を取得
    D3DXVECTOR3 myPos = GetPos();

    // 道を探しているかどうか
    SearchRoad(myPos);

    // 移動（攻撃フェーズ中は移動できない）
    if (!m_bAttackPhase)
    {
        myPos += m_moveAngle * m_fSpeed;
    }

    // 位置を設定
    SetPos(myPos);

    // タイヤの回転
    m_fTireRotAngle -= TIRE_ROT_SPEED;
    if (m_fTireRotAngle > D3DX_PI)
    {
        m_fTireRotAngle -= D3DX_PI * 2.0f;
    }
    else if (m_fTireRotAngle < -D3DX_PI)
    {
        m_fTireRotAngle += D3DX_PI * 2.0f;
    }
    SetPartRotX(PARTS_TIRE_1, m_fTireRotAngle);
    SetPartRotX(PARTS_TIRE_2, m_fTireRotAngle);
    SetPartRotX(PARTS_TIRE_3, m_fTireRotAngle);
    SetPartRotX(PARTS_TIRE_4, m_fTireRotAngle);

    // 壁に当たったかどうか
    if (!CollisionWall(myPos))
    {
        // 攻撃フェーズの処理
        AttackPhase();
    }

    // 向きを調整
    RotControl();

    // アニメーションさせる
    CCharacter::Update();

#ifdef COLLISION_TEST
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 65);
#endif // COLLISION_TEST

    if (m_fChargeValue >= CHARGE_VALUE_LV1
        &&m_fChargeValue < CHARGE_VALUE_LV2)//電磁法が打てる状態のとき電撃エフェクト発生(Lv.1)
    {
        if (m_Effect[EFFECT_LIGHTNING].type != NOT_EXIST)
        {
            m_Effect[EFFECT_LIGHTNING].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING].nCntTrail >= m_Effect[EFFECT_LIGHTNING].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//砲台の位置を取得

                m_Effect[EFFECT_LIGHTNING].nCntTrail = 0;
                
                m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV1;// エフェクトをLv1のものに変更
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_0].type, lightningPos, lightningPos);
            }
        }
    }
    if (m_fChargeValue >= CHARGE_VALUE_LV2
        &&m_fChargeValue < CHARGE_VALUE_LV3)//電磁法が打てる状態のとき電撃エフェクト発生(Lv.2)
    {
        if (m_Effect[EFFECT_LIGHTNING].type != NOT_EXIST)
        {
            m_Effect[EFFECT_LIGHTNING].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING].nCntTrail >= m_Effect[EFFECT_LIGHTNING].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//砲台の位置を取得

                m_Effect[EFFECT_LIGHTNING].nCntTrail = 0;
                m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV2;// エフェクトをLv2のものに変更
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_0].type, lightningPos, lightningPos);
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_1].type, lightningPos, lightningPos);
            }
        }
    }
    if (m_fChargeValue >= CHARGE_VALUE_LV3)//電磁法が打てる状態のとき電撃エフェクト発生(Lv.3)
    {
        if (m_Effect[EFFECT_LIGHTNING].type != NOT_EXIST)
        {
            m_Effect[EFFECT_LIGHTNING].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING].nCntTrail >= m_Effect[EFFECT_LIGHTNING].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//砲台の位置を取得

                m_Effect[EFFECT_LIGHTNING].nCntTrail = 0;
                m_Effect[EFFECT_LIGHTNING_CHARGE_0].type = CEffectData::TYPE_LIGHTNING_CHARGE_LV3;// エフェクトをLv3のものに変更
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_0].type, lightningPos, lightningPos);
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_CHARGE_1].type, lightningPos, lightningPos);
            }
        }
    }
float fLife = GetLife();// 移動要塞の体力取得

    // ライフがなくなったら
    if (fLife <= 0.0f)
    {
        SetLife(0.0f);

        // トレーニングでないなら
        if (CGame::GetType() != CGame::TYPE_TRAINING)
        {
            // ここで、ゴールゲートを破壊できているなら、勝ち判定を優先

            // 仮に非表示に
            m_bDisp = false;

            // 敗北状態に
            CGame::SetFinish(false);
        }
        else
        {
            // トレーニングではやられない
            SetLife(MAX_LIFE);
            SetDisp(true);
        }
    }
    
    // HPが低いときに煙を発生させる
    if (fLife <= SMOKE_EFFECT_LIFE)
    {
        if (m_Effect[EFFECT_SMOKE].type != NOT_EXIST)
        {
            m_Effect[EFFECT_SMOKE].nCntTrail++;
            if (m_Effect[EFFECT_SMOKE].nCntTrail >= m_Effect[EFFECT_SMOKE].interval)
            {
                m_Effect[EFFECT_SMOKE].nCntTrail = 0;
                D3DXVECTOR3 smokePos = myPos + D3DXVECTOR3(0.0f, GetCollisionSizeDefence().y, 0.0f);
                CEffect3D::Emit(m_Effect[EFFECT_SMOKE].type, smokePos, smokePos);
            }
        }
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::Draw(void)
{
    if (m_bDisp)
    {
        CCharacter::Draw();
    }
}

//=============================================================================
// 生成処理
// Author : 後藤慎之助
//=============================================================================
CFortress *CFortress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // メモリ確保
    CFortress *pFortress = NULL;
    pFortress = new CFortress;

    // 先に結びつけておく
    pFortress->CCharacter::SetPos(pos);
    pFortress->CCharacter::SetRot(rot);

    // 初期化
    pFortress->Init(pos, DEFAULT_SCALE);

    return pFortress;
}

//=============================================================================
// 攻撃リセット処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::ResetAttack(void)
{
    m_nCntTime = 0;
    m_fChargeValue = 0.0f;
    m_bAttackPhase = false;
}

//=============================================================================
// チャージ量加算
// Author : 後藤慎之助
//=============================================================================
void CFortress::AddChargeValue(const float fChargeValue)
{
    m_fChargeValue += fChargeValue;
    if (m_fChargeValue > CHARGE_VALUE_LV3)
    {
        m_fChargeValue = CHARGE_VALUE_LV3;
    }
}

//=============================================================================
// プレイヤーのリスポーン位置を返す処理
// Author : 後藤慎之助
//=============================================================================
D3DXVECTOR3 CFortress::GetPlayerSpawnPos(int nIndex)
{
    D3DXVECTOR3 returnPos = GetPos();
    D3DXVECTOR3 addPos = DEFAULT_VECTOR;

    switch (nIndex)
    {
    case PLAYER_1:
        addPos = D3DXVECTOR3(-850.0f, RESPAWN_HEIGHT, 850.0f);
        break;
    case PLAYER_2:
        addPos = D3DXVECTOR3(850.0f, RESPAWN_HEIGHT, 850.0f);
        break;
    case PLAYER_3:
        addPos = D3DXVECTOR3(-850.0f, RESPAWN_HEIGHT, -850.0f);
        break;
    case PLAYER_4:
        addPos = D3DXVECTOR3(850.0f, RESPAWN_HEIGHT, -850.0f);
        break;
    }

    returnPos += addPos;

    return returnPos;
}

//=============================================================================
// 道を探す処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::SearchRoad(D3DXVECTOR3 myPos)
{
    if (m_bSearchRoad)
    {
        // 道を探す
        float fKeepDistance = 999999.9f; // 距離
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ROAD);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ROAD); nCntScene++)
        {
            // 中身があるなら
            if (pScene)
            {
                // 次のシーンを記憶
                CScene*pNextScene = pScene->GetNextScene();

                // 道にキャスト
                CRoad *pRoad = (CRoad*)pScene;

                // 通過していないなら
                if (!pRoad->GetPast())
                {
                    // 道の位置
                    D3DXVECTOR3 roadPos = pRoad->GetPos();

                    // 距離計算
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - roadPos.x), 2.0f) +
                        powf((myPos.z - roadPos.z), 2.0f));

                    // 距離が今キープしているものより近いなら、移動の向きを更新
                    if (fKeepDistance > fCurrentDistance)
                    {
                        fKeepDistance = fCurrentDistance;
                        m_pTargetRoad = pRoad;
                        float fAngleToRoad = GetAngleToTargetXZ(myPos, roadPos);
                        SetRotDestY(GetAngleToTargetXZ(roadPos, myPos));
                        m_moveAngle = D3DXVECTOR3(sinf(fAngleToRoad), 0.0f, cosf(fAngleToRoad));
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }

        // 道探し終了
        m_bSearchRoad = false;
    }
    else
    {
        // 目的の位置に達したなら、次の道を探す
        if (m_pTargetRoad)
        {
            D3DXVECTOR3 targetRoadPos = m_pTargetRoad->GetPos();
            float fDistanceToTargetRoad = sqrtf(
                powf((myPos.x - targetRoadPos.x), 2.0f) +
                powf((myPos.z - targetRoadPos.z), 2.0f));
            const float SEARCH_NEXT_ROAD_DISTANCE = 25.0f;
            if (fDistanceToTargetRoad < SEARCH_NEXT_ROAD_DISTANCE)
            {
                m_bSearchRoad = true;
                m_pTargetRoad->SetPast(true);   // 道を通り過ぎたことにする
            }
        }
    }
}

//=============================================================================
// 攻撃フェーズの処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::AttackPhase(void)
{
    // 攻撃フェーズになっているなら
    if (m_bAttackPhase)
    {
        // もしチャージ量がLv1にすら達していないなら、関数を抜ける
        if (m_fChargeValue < CHARGE_VALUE_LV1)
        {
            // ここでまだチャージされていない旨を表示するUIを生成

            m_bAttackPhase = false;
            return;
        }

        // カウンタを加算
        m_nCntTime++;

        // チャージ音
        if (m_nCntTime == 1)
        {
            CManager::SoundPlay(CSound::LABEL_SE_CHARGE_ELECTROMAGNETIC_CANNON);
        }

        // チャージまでかかる時間
        int nCntMaxTime = 0;
        if (m_fChargeValue >= CHARGE_VALUE_LV1 && m_fChargeValue < CHARGE_VALUE_LV2)
        {
            nCntMaxTime = CHARGE_FIRE_FRAME_LV1;
        }
        else if (m_fChargeValue >= CHARGE_VALUE_LV2 && m_fChargeValue < CHARGE_VALUE_LV3)
        {
            nCntMaxTime = CHARGE_FIRE_FRAME_LV2;
        }
        else if (m_fChargeValue >= CHARGE_VALUE_LV3)
        {
            nCntMaxTime = CHARGE_FIRE_FRAME_LV3;
        }

        // 一定カウンタで、攻撃
        if (m_nCntTime >= nCntMaxTime)
        {
            // チャージ状況に応じて変える
            D3DXVECTOR3 firePos = GetPartsPos(PARTS_FIRE_POS);
            D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
            CBullet *pBullet = NULL;
            int nContributionPoint = 0;
            if (m_fChargeValue >= CHARGE_VALUE_LV1 && m_fChargeValue < CHARGE_VALUE_LV2)
            {
                // カメラの振動
                CManager::GetCamera()->CCamera::SetShake(400.0f);
                CManager::SoundPlay(CSound::LABEL_SE_ELECTROMAGNETIC_CANNON_Lv1);
                pBullet = CBullet::Create(CBullet::TYPE_THUNDER, GetPos(), DEFAULT_VECTOR, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV1;
            }
            else if (m_fChargeValue >= CHARGE_VALUE_LV2 && m_fChargeValue < CHARGE_VALUE_LV3)
            {
                // カメラの振動
                CManager::GetCamera()->CCamera::SetShake(500.0f);
                CManager::SoundPlay(CSound::LABEL_SE_ELECTROMAGNETIC_CANNON_Lv2);
                pBullet = CBullet::Create(CBullet::TYPE_RAILGUN_LV2, firePos, moveAngle, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV2;
            }
            else if (m_fChargeValue >= CHARGE_VALUE_LV3)
            {
                // カメラの振動
                CManager::GetCamera()->CCamera::SetShake(600.0f);
                CManager::SoundPlay(CSound::LABEL_SE_ELECTROMAGNETIC_CANNON_Lv2);
                pBullet = CBullet::Create(CBullet::TYPE_RAILGUN_LV3, firePos, moveAngle, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV3;
            }
            if (pBullet)
            {
                pBullet->SetWhoContribution(m_nWhoAttackPhase);
            }

            // 貢献度を撃っただけでも上げる
            CGame::GetPlayer(m_nWhoAttackPhase)->GainContribution(nContributionPoint);

            // 攻撃状態をリセット
            ResetAttack();
        }
        else
        {
            // 攻撃準備エフェクトを発生
            m_Effect[EFFECT_LIGHTNING_SETUP].nCntTrail++;
            if (m_Effect[EFFECT_LIGHTNING_SETUP].nCntTrail >= m_Effect[EFFECT_LIGHTNING_SETUP].interval)
            {
                D3DXVECTOR3 lightningPos = GetPartsPos(PARTS_CANNON_CENTER);//砲台の位置を取得
                CEffect3D::Emit(m_Effect[EFFECT_LIGHTNING_SETUP].type, lightningPos, lightningPos);
            }
        }
    }
}

//=============================================================================
// 壁に当たったかどうかの処理
// Author : 後藤慎之助
//=============================================================================
bool CFortress::CollisionWall(D3DXVECTOR3 myPos)
{
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
    {
        // 中身があるなら
        if (pScene)
        {
            // 次のシーンを記憶
            CScene*pNextScene = pScene->GetNextScene();

            // ブロックにキャスト
            CBlock *pBlock = (CBlock*)pScene;

            // 当たっているなら
            D3DXVECTOR2 collisionSize = GetCollisionSizeDefence();
            D3DXVECTOR3 myCubeSize = D3DXVECTOR3(collisionSize.x, collisionSize.y, collisionSize.x);
            D3DXVECTOR3 blockPos = pBlock->GetPos();
            if (IsCollisionRectangle3D(&myPos, &blockPos,
                &myCubeSize, &pBlock->GetCollisionSize()))
            {
                // 致死ダメージ
                TakeDamage(FORTRESS_CRUSH_DAMAGE, myPos, blockPos, OBJTYPE_BLOCK);
                return true;
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
    }

    return false;
}
