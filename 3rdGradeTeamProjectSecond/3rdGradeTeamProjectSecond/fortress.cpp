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

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CFortress::CFortress() :CCharacter(OBJTYPE::OBJTYPE_FORTRESS)
{
    m_collisionSizeDeffence = D3DXVECTOR2(0.0f, 0.0f);
    m_fSpeed = 0.0f;
    m_fLife = 0.0f;

    m_bSearchRoad = true;
    m_moveAngle = DEFAULT_VECTOR;
    m_pTargetRoad = NULL;
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
    m_collisionSizeDeffence = D3DXVECTOR2(950.0f, 450.0f);
    m_fSpeed = 2.5f;
    m_fLife = 1000.0f;
    // パーツ数を設定、モデルをバインド、アニメーションをバインド
    CCharacter::SetPartNum(PARTS_MAX);
    CCharacter::BindParts(PARTS_FIGHTER, 33);
    CCharacter::BindParts(PARTS_RIGHT_WING_0, 34);
    CCharacter::BindParts(PARTS_RIGHT_WING_1, 35);
    CCharacter::BindParts(PARTS_RIGHT_WING_2, 36);
    CCharacter::BindParts(PARTS_RIGHT_WING_3, 37);
    CCharacter::BindParts(PARTS_LEFT_WING_0, 38);
    CCharacter::BindParts(PARTS_LEFT_WING_1, 39);
    CCharacter::BindParts(PARTS_LEFT_WING_2, 40);
    CCharacter::BindParts(PARTS_LEFT_WING_3, 41);
    CCharacter::LoadModelData("./data/ANIMATION/motion_UFO.txt");

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
    // 位置を取得
    D3DXVECTOR3 myPos = GetPos();
    
    // 道を探しているかどうか
    SearchRoad(myPos);

    // 移動
    myPos += m_moveAngle * m_fSpeed;

    // 位置を設定
    SetPos(myPos);

    // 向きを調整
    RotControl();

    // アニメーションさせる
    CCharacter::Update();

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSizeDeffence.x, m_collisionSizeDeffence.y, m_collisionSizeDeffence.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// 生成処理
// Author : 後藤慎之助
//=============================================================================
CFortress * CFortress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
// 道を探す処理
// Author : 後藤慎之助
//=============================================================================
void CFortress::SearchRoad(D3DXVECTOR3 myPos)
{
    if (m_bSearchRoad)
    {
        // 道を探す
        float fKeepDistance = 99999.9f; // 距離
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
                        powf((myPos.x - roadPos.x), 2) +
                        powf((myPos.z - roadPos.z), 2));

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
                powf((myPos.x - targetRoadPos.x), 2) +
                powf((myPos.z - targetRoadPos.z), 2));
            const float SEARCH_NEXT_ROAD_DISTANCE = 25.0f;
            if (fDistanceToTargetRoad < SEARCH_NEXT_ROAD_DISTANCE)
            {
                m_bSearchRoad = true;
                m_pTargetRoad->SetPast(true);
            }
        }
    }
}
