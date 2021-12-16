//======================================================================================
//
// アイテム処理 (item.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "item.h"
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
#include "enemy.h"
#include "fortress.h"

//========================================
// マクロ定義
//========================================
#define ITEM_LAUNCH_VALUE D3DXVECTOR3(0.0f, 25.0f, 0.0f)    // 打ち上げ量
#define ITEM_GRAVITY 1.0f                                   // 重力
#define ITEM_GRAVITY_MAX -15.0f                             // 重力制限
#define ITEM_SPEED_UP_VALUE 1.25f                           // 加速量
#define ITEM_SPEED_MAX 75.0f                                // 加速の最大量
#define ITEM_LIFE 600                                       // 表示時間
#define ITEM_FLASH_START_FRAME (ITEM_LIFE - 420)            // 点滅開始フレーム
#define ITEM_USE_COLLISION_FRAME (ITEM_LIFE - 10)           // 衝突判定を持たせるまでのフレーム
#define ITEM_CLOSE_DISTANCE_DEFAULT 1000.0f                 // 近いとみなす距離(デフォルト)
#define ITEM_CLOSE_DISTANCE_CARRIER 2000.0f                 // 近いとみなす距離(キャリアー)
#define ITEM_ROT_SPEED D3DXToRadian(2.0f)                   // 回転速度

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CItem::CItem() :CScene3D(CScene::OBJTYPE_ITEM)
{
    m_type = TYPE_DENTI_5;
    m_collisionSize = D3DXVECTOR2(0.0f, 0.0f);
    m_move = ITEM_LAUNCH_VALUE;
    m_fSpeed = 0.0f;

    m_posOld = DEFAULT_VECTOR;
    m_nLife = ITEM_LIFE;
    m_fGetEnergy = 0.0f;

    m_bUseDraw = true;
    m_pEffect3d_Shadow = NULL;
    m_bGround = false;
    m_pTarget = NULL;

    m_bUseCollision = false;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 初期設定
    switch (m_type)
    {
    case TYPE_DENTI_5:
        m_collisionSize = D3DXVECTOR2(200.0f, 200.0f);
        BindModelData(52);
        break;
    case TYPE_DENTI_3:
        m_collisionSize = D3DXVECTOR2(300.0f, 300.0f);
        BindModelData(53);
        break;
    case TYPE_DENTI_1:
        m_collisionSize = D3DXVECTOR2(400.0f, 400.0f);
        BindModelData(54);
        break;
    }

    // 初期化
    CScene3D::Init(pos, size);

    // スケールを設定
    SetScale(size);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CItem::Uninit(void)
{
    // 影を消す
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetDontUse();
    }

    CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CItem::Update(void)
{
    // 位置、大きさを取得
    D3DXVECTOR3 myPos = GetPos();

    // 1F前の位置を結びつける
    m_posOld = myPos;

    // 着地していないなら
    if (!m_bGround)
    {
        // 重力発生
        if (myPos.y > 0.0f)
        {
            m_move.y -= ITEM_GRAVITY;

            if (m_move.y < ITEM_GRAVITY_MAX)
            {
                m_move.y = ITEM_GRAVITY_MAX;
            }
        }
        else
        {
            myPos.y = 0.0f;
            m_move.y = 0.0f;
            m_bGround = true;
        }
    }
    else
    {
        // プレイヤーの方を追従（プレイヤーのポインタがないなら、プレイヤーを探す）
        if (m_pTarget)
        {
            if (m_pTarget->GetDisp())
            {
                MoveTowardPlayer(myPos);
            }
            else
            {
                SearchPlayer(myPos);
            }
        }
        else
        {
            SearchPlayer(myPos);
        }
    }

    // 位置に移動量を反映
    myPos += m_move;

    // 当たり判定
    if (m_bUseCollision)
    {
        Collision(myPos);
    }

    // 位置を設定
    SetPos(myPos);

    // 回転
    D3DXVECTOR3 rot = GetRot();
    rot.y += ITEM_ROT_SPEED;
    if (rot.y > D3DX_PI)
    {
        rot.y -= D3DX_PI * 2.0f;
    }
    else if (rot.y < -D3DX_PI)
    {
        rot.y += D3DX_PI * 2.0f;
    }
    SetRot(rot);

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST

    // 影の位置を更新
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(myPos.x, SHADOW_POS_Y, myPos.z));
    }

    // ライフがなくなりかけたら、点滅
    if (m_nLife < ITEM_FLASH_START_FRAME)
    {
        if (m_nLife % 2 == 0)
        {
            m_bUseDraw = !m_bUseDraw;
        }
    }
    else if (m_nLife == ITEM_USE_COLLISION_FRAME)
    {
        m_bUseCollision = true;
    }

    // ライフがなくなった、または使用フラグがなくなったら、消滅
    m_nLife--;
    if (m_nLife <= 0)
    {
        Uninit();
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CItem::Draw(void)
{
    // 影
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->CBillboard::Draw();
    }

    // 描画するなら
    if (m_bUseDraw)
    {
        CScene3D::Draw();
    }
}

//=============================================================================
// 生成処理
// Author : 後藤慎之助
//=============================================================================
CItem * CItem::Create(int type, D3DXVECTOR3 pos, float fEnergy)
{
    // メモリ確保
    CItem *pItem = NULL;
    pItem = new CItem;

    // 先に結びつけておく
    pItem->m_type = type;
    pItem->m_fGetEnergy = fEnergy;

    // 初期化
    // 位置が0より大きいようにする
    if (pos.y <= 0.0f)
    {
        pos.y = 1.0f;
    }
    pItem->Init(pos, DEFAULT_SCALE);

    return pItem;
}

//=============================================================================
// プレイヤーに向かわせる処理
// Author : 後藤慎之助
//=============================================================================
void CItem::MoveTowardPlayer(D3DXVECTOR3 myPos)
{
    // 移動速度を徐々に速める
    m_fSpeed += ITEM_SPEED_UP_VALUE;
    if (m_fSpeed > ITEM_SPEED_MAX)
    {
        m_fSpeed = ITEM_SPEED_MAX;
    }

    // 変数宣言
    D3DXVECTOR3 targetPos = m_pTarget->GetPos();
    float fAngle = 0.0f;

    // 角度を求める
    fAngle = atan2f((myPos.x - targetPos.x), (myPos.z - targetPos.z));

    // 横移動の値を決める
    m_move.x = -sinf(fAngle) * m_fSpeed;
    m_move.z = -cosf(fAngle) * m_fSpeed;

    // 距離を測る
    float fDistance = sqrtf(
        powf((targetPos.x - myPos.x), 2.0f) +
        powf((targetPos.z - myPos.z), 2.0f));

    // 高さの差を測る
    float fHeight = fabsf((targetPos.y) - myPos.y);

    // 縦の角度を決める
    float fAngleY = atan2(fDistance, fHeight);

    // 縦の移動量を決める
    m_move.y = cosf(fAngleY) * m_fSpeed;

    // ターゲットの位置のほうが、自身の位置より低いなら
    if (targetPos.y < myPos.y)
    {
        // Y軸の移動角度を逆にする
        m_move.y *= -1;
    }
}

//=============================================================================
// プレイヤーを探す処理
// Author : 後藤慎之助
//=============================================================================
void CItem::SearchPlayer(D3DXVECTOR3 myPos)
{
    // まず、移動量とスピードをなくす
    m_move = DEFAULT_VECTOR;
    m_fSpeed = 0.0f;

    // プレイヤーを探す
    float fKeepDistance = 0.0f;
    CPlayer *pKeepPlayer = CGame::GetDistanceAndPointerToClosestPlayer_Player(myPos, fKeepDistance);

    // プレイヤーがキャリアーなら、検知距離が伸びる
    float fDiscoveryPlayerDistance = ITEM_CLOSE_DISTANCE_DEFAULT;
    if (pKeepPlayer)
    {
        if (pKeepPlayer->GetRole() == CPlayer::ROLE_CARRIER)
        {
            fDiscoveryPlayerDistance = ITEM_CLOSE_DISTANCE_CARRIER;
        }
    }

    // キープしている距離が、近いとみなす値なら
    if (fKeepDistance <= fDiscoveryPlayerDistance)
    {
        // プレイヤーを結びつける
        if (pKeepPlayer)
        {
            m_pTarget = pKeepPlayer;
        }
    }
    else
    {
        // 近いキャラがいないなら、着地フラグを消す（空中でキャラがやられた時に、アイテムをもう一度地面に落とすため）
        m_bGround = false;
    }
}

//=============================================================================
// 衝突処理
// Author : 後藤慎之助
//=============================================================================
void CItem::Collision(D3DXVECTOR3 myPos)
{
    // プレイヤーとの当たり判定
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
          
            // 表示しているかどうか
            if (!pPlayer->GetDisp())
            {
                continue;
            }

            // 現在のエナジー量が、そのプレイヤーの最大数に達しているなら次のプレイヤーへ

          
            // プレイヤーの位置を取得
            D3DXVECTOR3 playerPos= pPlayer->GetPos();

            // 当たっているなら
            if (IsCollisionCylinder(myPos, m_collisionSize, playerPos, pPlayer->GetCollisionSizeDefence()))
            {

                // プレイヤーのエナジー加算
                pPlayer->GainEnergy(m_fGetEnergy);

                // 1人しか衝突しないため、関数を抜ける
                m_nLife = NOT_EXIST;

                // プレイヤーの位置にエフェクト発生
                CEffect3D::Emit(CEffectData::TYPE_GET, playerPos, playerPos);
                CEffect3D::Emit(CEffectData::TYPE_GET, playerPos, playerPos);

                return;
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
    }
}
