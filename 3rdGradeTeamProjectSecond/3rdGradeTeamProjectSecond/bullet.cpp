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
#define HIT_NOT_EXIST -99

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

    m_nCntTime = 0;
    m_bUseDraw = false;

    m_bHitErase = true;
    m_pEffect3d_Shadow = NULL;
    m_bBreakGoalGate = false;
    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    m_fStrength = 0.0f;

    memset(m_afParam, 0, sizeof(m_afParam));
    m_whoShot = OBJTYPE_NONE;
    m_fHealValue = 0.0f;
    m_bUseUpdate = true;
    m_bUseUninit = true;
    m_bUseKnockBack = true;

    m_Effect.type = NOT_EXIST;
    m_Effect.interval = 1;
    m_Effect.nCntTrail = 0;
  
    m_nWhoContribution = NOT_EXIST;
    m_nHitContributionPoint = 0;
    m_nIdxHitEffect = DEFAULT_HIT_EFFECT_NUM;
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
    // 更新処理を使わないなら、関数を抜ける
    if (!m_bUseUpdate)
    {
        return;
    }

    // 位置、大きさを取得
    D3DXVECTOR3 myPos = GetPos();

    // 1F前の位置を結びつける
    m_posOld = myPos;

    // 種類ごとの処理
    bool bUseCollisionThisFrame = true;
    switch (m_type)
    {
    case TYPE_COMMANDER_ATTACK:
        CommanderAttackMove(myPos);
        break;
    case TYPE_HUNTER_GROUND:
        HunterGroundMove(myPos);
        break;
    case TYPE_HUNTER_SKY:
        HunterSkyMove(myPos);
        break;
    case TYPE_HEALER_SKY:
        bUseCollisionThisFrame = HealerSkyUseCollision();
        break;
    default:
        // 移動量を位置に反映
        myPos += m_moveAngle * m_fSpeed;
        break;
    }

    // 当たり判定を設定
    if (bUseCollisionThisFrame)
    {
        Collision(myPos);
    }

    // 位置を設定
    SetPos(myPos);

    // 影の位置を更新
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(myPos.x, SHADOW_POS_Y, myPos.z));
    }

    // 軌跡エフェクト発生
    if (m_Effect.type != NOT_EXIST)
    {
        m_Effect.nCntTrail++;
        if (m_Effect.nCntTrail >= m_Effect.interval)
        {
            m_Effect.nCntTrail = 0;
            CEffect3D::Create(m_Effect.type, myPos);
        }
    }

    // ライフがなくなった、または使用フラグがなくなったら、消滅
    if (m_bUseUninit)
    {
        m_nLife--;
        if (m_nLife <= 0)
        {
            Uninit();
        }
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
CBullet * CBullet::Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, OBJTYPE whoShot, float fStrength, D3DXVECTOR3 rot)
{
    // メモリ確保
    CBullet *pBullet = NULL;
    pBullet = new CBullet;

    // 先に結びつけておく
    pBullet->m_type = type;
    pBullet->SetRot(rot);
    pBullet->m_fStrength = fStrength;
    pBullet->m_whoShot = whoShot;
    pBullet->m_posOld = pos;

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
    // レールガンは地を這う
    D3DXVECTOR3 collisionPos = bulletPos;
    if (m_type == TYPE_RAILGUN_LV2 || m_type == TYPE_RAILGUN_LV3)
    {
        collisionPos.y = 0.0f;
    }

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

                // 表示しているかどうか
                if (!pPlayer->GetDisp())
                {
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

                        // ダメージが入ったかどうか
                        bool bDamaged = false;

                        // 回復するなら
                        if (IS_BITON(m_collisionFlag, COLLISION_FLAG_HEAL_PLAYER))
                        {
                            // 撃ち手は回復できない
                            if (m_nWhoContribution == pPlayer->GetIdxCreate())
                            {
                                continue;
                            }

                            // 回復は無敵の有無にかかわらず入る
                            bDamaged = true;
                            if (pPlayer->Healing(m_fHealValue))
                            {
                                // 撃った人の貢献度が上がる
                                if (m_nWhoContribution != NOT_EXIST)
                                {
                                    CGame::GetPlayer(m_nWhoContribution)->GainContribution(m_nHitContributionPoint);
                                }
                            }
                        }
                        else
                        {
                            // ダメージを受けるなら、ガードしているかどうか
                            if (pPlayer->GetUsingGuard())
                            {
                                bDamaged = pPlayer->TakeDamage_TankUsingGuard(m_fDamage, bulletPos, m_posOld, m_bUseKnockBack, m_nIdxHitEffect);
                            }
                            else
                            {
                                bDamaged = pPlayer->TakeDamage(m_fDamage, bulletPos, m_posOld, m_whoShot, m_bUseKnockBack, m_nIdxHitEffect);
                            }
                        }

                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = HIT_NOT_EXIST;
                        }
                    }
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }

        // プレイヤーを回復させないなら、移動要塞を取得（今後移動要塞周りのフラグが増えるなら、要改善）
        if (IS_BITOFF(m_collisionFlag, COLLISION_FLAG_HEAL_PLAYER))
        {
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
                        bool bDamaged = pFortress->TakeDamage(m_fDamage, bulletPos, m_posOld, m_whoShot, m_bUseKnockBack, m_nIdxHitEffect);
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = HIT_NOT_EXIST;
                        }
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

                // 出現していないなら、次へ
                if (pEnemy->GetAppearState() != CEnemy::APPEAR_STATE_EXIST)
                {
                    // 次のシーンにする
                    pScene = pNextScene;
                    continue;
                }

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
                    if (IsCollisionCylinder(collisionPos, m_collisionSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                    {
                        // 多段ヒット回避用のフラグをtrueに
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // ダメージか引っ張り
                        bool bDamaged = false;
                        if (IS_BITON(m_collisionFlag, COLLISION_FLAG_PULL_ENEMY))
                        {
                            bDamaged = pEnemy->PullToCenter(bulletPos);
                        }
                        else if (IS_BITON(m_collisionFlag, COLLISION_FLAG_HEAL_ENEMY))
                        {
                            // 回復は無敵の有無にかかわらず入る
                            bDamaged = true;
                            pEnemy->Healing(m_fHealValue);
                        }
                        else
                        {
                            bDamaged = pEnemy->TakeDamage(m_fDamage, bulletPos, m_posOld, m_whoShot, m_bUseKnockBack, m_nIdxHitEffect);
                            if (bDamaged)
                            {
                                // 貢献した人を設定
                                pEnemy->SetWhoContribution(m_nWhoContribution);
                            }
                        }
                        // 消す弾なら消す
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = HIT_NOT_EXIST;
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
                    if (pBlock->TakeDamage(m_bBreakGoalGate))
                    {
                        // 撃った人の貢献度が上がる
                        if (m_nWhoContribution != NOT_EXIST)
                        {
                            CGame::GetPlayer(m_nWhoContribution)->GainContribution(m_nHitContributionPoint);
                        }
                    }
                    m_nLife = HIT_NOT_EXIST;    // ブロックは貫通出来ない
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
                    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
                    break;
                case HIT_SURFACE_BACK:
                case HIT_SURFACE_FRONT:
                    m_moveAngle.z *= -1.0f;
                    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
                    break;
                }

                // 次のシーンにする
                pScene = pNextScene;
            }
        }
    }

    // 床に当たったら消す
    if (bulletPos.y < 0.0f)
    {
        bulletPos.y = 0.0f;
        m_nLife = HIT_NOT_EXIST;

        // コマンダーの弾なら、敵を生成
        if (m_type == TYPE_COMMANDER_ATTACK)
        {
            // 敵出現エフェクト
            CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_0, GetPos(), GetPos());
            CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_1, GetPos(), GetPos());

            CEnemy::Create(CEnemy::TYPE_ARMY, bulletPos);
        }
    }

    // 当たったなら
    if (m_nLife == HIT_NOT_EXIST)
    {
        // タンクの地上攻撃Lv3なら爆発
        if (m_type == TYPE_TANK_GROUND_LV3)
        {
            CBullet *pBullet = CBullet::Create(CBullet::TYPE_TANK_GROUND_EX, bulletPos, DEFAULT_VECTOR, m_whoShot);
            pBullet->SetWhoContribution(m_nWhoContribution);
        }
    }

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
    CDebug::Create(bulletPos, size, CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
}