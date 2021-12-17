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

    m_fChargeValue = 0.0f;
    m_bAttackPhase = false;
    m_nCntTime = 0;

    m_bDisp = true;
    m_nWhoAttackPhase = 0;
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
    SetCollisionSizeDefence(D3DXVECTOR2(950.0f, 450.0f));
    m_fSpeed = 3.5f;
    SetUpLife(1000.0f);
    SetTakeKnockBack(false);
    // パーツ数を設定、モデルをバインド、アニメーションをバインド
    CCharacter::SetPartNum(PARTS_MAX);
    CCharacter::BindParts(PARTS_BODY, 55);
    CCharacter::BindParts(PARTS_CANNON_CENTER, 50);
    CCharacter::BindParts(PARTS_SEAT, 50);
    CCharacter::BindParts(PARTS_FIRE_POS, 50);
    CCharacter::SetDontUseAnimation();
    CCharacter::LoadModelData("./data/ANIMATION/motion_fortress.txt");
    CCharacter::SetDontUseAnimation();

    // キャラクターに反映
    CCharacter::Init(pos, DEFAULT_SCALE);

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
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST

    // ライフがなくなったら
    if (GetLife() <= 0.0f)
    {
        SetLife(0.0f);

        // トレーニングでないなら
        if (CGame::GetType() != CGame::TYPE_TRAINING)
        {
            // ここで、ゴールゲートを破壊できているなら、勝ち判定を優先

            // 仮に非表示に
            m_bDisp = false;

            // 仮にリザルトに移行
            CFade::SetFade(CManager::MODE_RESULT);
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
                pBullet = CBullet::Create(CBullet::TYPE_THUNDER, GetPos(), DEFAULT_VECTOR, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV1;
            }
            else if (m_fChargeValue >= CHARGE_VALUE_LV2 && m_fChargeValue < CHARGE_VALUE_LV3)
            {
                pBullet = CBullet::Create(CBullet::TYPE_RAILGUN_LV2, firePos, moveAngle, OBJTYPE_FORTRESS);
                nContributionPoint = CHARGE_POINT_LV2;
            }
            else if (m_fChargeValue >= CHARGE_VALUE_LV3)
            {
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
