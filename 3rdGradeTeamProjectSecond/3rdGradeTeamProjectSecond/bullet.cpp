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
#include "block.h"

//========================================
// マクロ定義
//========================================

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
    m_bBreakGoalGate = false;
    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));

    m_fGravityValue = 0.0f;
    m_fGravityLimit = 0.0f;
    m_fStrength = 0.0f;
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
    if (m_fGravityValue == 0.0f)
    {
        myPos += m_moveAngle * m_fSpeed;
    }
    else
    {
        // 重力を使うなら
        float fGravity = m_fGravityValue * m_nCntTime;
        if (fGravity < m_fGravityLimit)
        {
            fGravity = m_fGravityLimit;
        }
        myPos += m_moveAngle * m_fSpeed + D3DXVECTOR3(0.0f, fGravity, 0.0f);
    }

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
    pBullet->m_fStrength = fStrength;

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
void CBullet::Collision(D3DXVECTOR3 &bulletPos)
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

                // インデックスを取得
                int nIdx = pPlayer->GetIdx();
                if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
                {
                    // 次のシーンにする
                    pScene = pNextScene;
                    continue;
                }

                // 多段ヒット回避用フラグがfalseなら
                if (!m_abUseAvoidMultipleHits[nIdx])
                {
                    // 当たっているなら
                    if (IsCollisionCylinder(bulletPos, m_collisionSize, pPlayer->GetPos(), pPlayer->GetCollisionSizeDefence()))
                    {
                        // 多段ヒット回避用のフラグをtrueに
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // ダメージ
                        bool bDamaged = pPlayer->TakeDamage(m_fDamage, bulletPos, m_posOld);
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = NOT_EXIST;
                        }
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
            // インデックスを取得
            int nIdx = pFortress->GetIdx();

            // 多段ヒット回避用フラグがfalseなら
            if (!m_abUseAvoidMultipleHits[nIdx])
            {
                // 当たっているなら
                if (IsCollisionCylinder(bulletPos, m_collisionSize, pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
                {
                    // 多段ヒット回避用のフラグをtrueに
                    m_abUseAvoidMultipleHits[nIdx] = true;

                    // ダメージ
                    bool bDamaged = pFortress->TakeDamage(m_fDamage, bulletPos, m_posOld);
                    if (bDamaged && m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
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

                // インデックスを取得
                int nIdx = pEnemy->GetIdx();
                if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
                {
                    // 次のシーンにする
                    pScene = pNextScene;
                    continue;
                }

                // 多段ヒット回避用フラグがfalseなら
                if (!m_abUseAvoidMultipleHits[nIdx])
                {
                    // 当たっているなら
                    if (IsCollisionCylinder(bulletPos, m_collisionSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                    {
                        // 多段ヒット回避用のフラグをtrueに
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // ダメージ
                        bool bDamaged = pEnemy->TakeDamage(m_fDamage, bulletPos, m_posOld);
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = NOT_EXIST;
                        }
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }
    }

    // ブロックとの当たり判定
    if (IS_BITOFF(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK))
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
                D3DXVECTOR3 myCubeSize = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
                if (IsCollisionRectangle3D(&bulletPos, &pBlock->GetPos(),
                    &myCubeSize, &pBlock->GetCollisionSize()))
                {
                    // ダメージ
                    pBlock->TakeDamage(m_bBreakGoalGate);
                    if (m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }
    }

    // ブロックで反射するかどうかの判定
    if (IS_BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK))
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
                D3DXVECTOR3 myCubeSize = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
                HIT_SURFACE hitSurface = CGame::MapLimit(bulletPos, m_posOld, myCubeSize);

                // 反射
                switch (hitSurface)
                {
                case HIT_SURFACE_LEFT:
                case HIT_SURFACE_RIGHT:
                    m_moveAngle.x *= -1.0f;
                    break;
                case HIT_SURFACE_BACK:
                case HIT_SURFACE_FRONT:
                    m_moveAngle.z *= -1.0f;
                    break;
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }
    }

    // コマンダーの攻撃は、床に接したときに敵を生成し、消す
    if (m_type == TYPE_COMMANDER_ATTACK)
    {
        if (bulletPos.y <= 0.0f)
        {
            bulletPos.y = 0.0f;
            m_nLife = NOT_EXIST;
            CEnemy::Create(CEnemy::TYPE_ARMY, bulletPos);
        }
    }
}