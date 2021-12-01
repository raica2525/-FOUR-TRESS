//======================================================================================
//
// 弾処理 (bullet.cpp)
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
#include "debug.h"
#include "enemy.h"
#include "fortress.h"

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CBullet::CBullet() :CScene3D(CScene::OBJTYPE_BULLET)
{
    m_type = TYPE_ARMY_ATTACK;
    m_collisionSize = D3DXVECTOR2(0.0f, 0.0f);
    m_moveAngle = DEFAULT_VECTOR;
    m_fSpeed = 0.0f;
    m_collisionFlag = COLLISION_FLAG_NONE;

    m_posOld = DEFAULT_VECTOR;
    m_nLife = 0;
    m_fDamage = 0;

    m_bUseCntTime = false;
    m_nCntTime = 0;
    m_bUseDraw = false;

    m_bHitErase = true;
    m_pEffect3d_Shadow = NULL;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
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
void CBullet::Uninit(void)
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
void CBullet::Update(void)
{
    // 時間経過を利用する弾なら
    if (m_bUseCntTime)
    {
        m_nCntTime++;
    }

    // 位置、大きさを取得
    D3DXVECTOR3 myPos = GetPos();

    // 1F前の位置を結びつける
    m_posOld = myPos;

    // 移動量を位置に結びつける
    myPos += m_moveAngle * m_fSpeed;

    // 当たり判定を設定
    Collision(myPos);

    // 位置を設定
    SetPos(myPos);

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST

    // 影の位置を更新
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(myPos.x, SHADOW_POS_Y, myPos.z));
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
void CBullet::Draw(void)
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
CBullet * CBullet::Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, float fStrength, D3DXVECTOR3 rot)
{
    // メモリ確保
    CBullet *pBullet = NULL;
    pBullet = new CBullet;

    // 先に結びつけておく
    pBullet->m_type = type;
    pBullet->SetRot(rot);

    // 初期化
    pBullet->SetupInfoByType(fStrength, pos);
    pBullet->Init(pos, DEFAULT_SCALE);

    // 引数を結びつけておく
    pBullet->m_moveAngle = moveAngle;

    return pBullet;
}

//=============================================================================
// 衝突処理
// Author : 後藤慎之助
//=============================================================================
void CBullet::Collision(D3DXVECTOR3 bulletPos)
{
    // プレイヤー、移動要塞との当たり判定
    if (IS_BITON(m_collisionFlag, COLLISION_FLAG_PLAYER))
    {
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

                // 当たっているなら
                if (IsCollisionCylinder(bulletPos, m_collisionSize, pPlayer->GetPos(), pPlayer->GetCollisionSizeDefence()))
                {
                    // ダメージ
                    bool bDamaged = pPlayer->TakeDamage(m_fDamage, bulletPos, m_posOld);
                    if (bDamaged && m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }

        // 移動要塞を取得
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            // 当たっているなら
            if (IsCollisionCylinder(bulletPos, m_collisionSize, pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
            {
                // ダメージ
                bool bDamaged = pFortress->TakeDamage(m_fDamage, bulletPos, m_posOld);
                if (bDamaged && m_bHitErase)
                {
                    m_nLife = NOT_EXIST;
                }
            }
        }
    }

    // 敵との当たり判定
    if (IS_BITON(m_collisionFlag, COLLISION_FLAG_ENEMY))
    {
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
        {
            // 中身があるなら
            if (pScene)
            {
                // 次のシーンを記憶
                CScene*pNextScene = pScene->GetNextScene();

                // 敵にキャスト
                CEnemy *pEnemy = (CEnemy*)pScene;

                // 当たっているなら
                if (IsCollisionCylinder(bulletPos, m_collisionSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                {
                    // ダメージ
                    bool bDamaged = pEnemy->TakeDamage(m_fDamage, bulletPos, m_posOld);
                    if (bDamaged && m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }
    }
}
