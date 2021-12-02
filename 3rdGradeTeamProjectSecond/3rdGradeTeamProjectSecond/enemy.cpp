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

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CEnemy::CEnemy() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_SPIDER;
    m_fSpeed = 0.0f;
    m_fStrength = 1.0f;

    m_nCntTime = 0;
    m_bSquashedByFortress = true;
    m_bDetectPlayer = false;

    m_appearState = APPEAR_STATE_EXIST;
    m_bDeath = false;
    m_nIdx = 0;

    m_walkMotion = 0;
    m_attackMotion = 0;
    m_damageMotion = 0;
    m_deathMotion = 0;
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
    CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Update(void)
{
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
        if (GetAnimation())
        {
            GetAnimation()->SetAnimation(0);
        }

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

        // 仮の処理
        CPlayer *pPlayer = CGame::GetPlayer(0);
        if (pPlayer)
        {
            // プレイヤーの位置
            D3DXVECTOR3 playerPos = pPlayer->GetPos();

            // 距離計算
            const float SEARCH_DISTANCE = 1000.0f;
            if (IsInsideCircleXZ(myPos, playerPos, SEARCH_DISTANCE))
            {
                SetRotDestY(GetAngleToTargetXZ(playerPos, myPos));

                RotControl();

                m_nCntTime++;

                if (m_nCntTime >= 75)
                {
                    m_nCntTime = 0;
                    D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
                    //CBullet::Create(CBullet::TYPE_ARMY_ATTACK, GetPos(), moveAngle, m_fStrength);
                }
            }
        }

        // 移動要塞に踏みつぶされるかどうか
        SquashedByFortress(myPos);

        // 位置、移動量を反映
        SetPos(myPos);
        SetMove(move);

        // アニメーションさせる
        CCharacter::Update();

#ifdef COLLISION_TEST
        D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST

        // ライフがなくなったら消す
        float fLife = GetLife();
        if (fLife <= 0.0f)
        {
            CItem::Create(CItem::TYPE_DENTI_3, myPos, 5.0f);
            Uninit();
        }
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
CEnemy * CEnemy::Create(int type, D3DXVECTOR3 pos, float fStrength, int appearState)
{
    // メモリ確保
    CEnemy *pEnemy = NULL;
    pEnemy = new CEnemy;

    // 先に引数を結びつけておく
    pEnemy->m_type = type;
    pEnemy->CCharacter::SetPos(pos);
    pEnemy->m_fStrength = fStrength;
    pEnemy->m_appearState = appearState;

    // 仮に向きを正面に
    pEnemy->CCharacter::SetRot(DEFAULT_VECTOR);

    // 初期化
    pEnemy->Init(pos, DEFAULT_SCALE);

    // インデックスを取得
    pEnemy->m_nIdx = CGame::GetEnemyIdx();

    // 出現していないなら、無敵にしておく
    if (pEnemy->m_appearState != APPEAR_STATE_EXIST)
    {
        pEnemy->SetInvincible(true);
    }

    return pEnemy;
}

//=============================================================================
// 出現処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Appear(void)
{
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
        float fKeepDistance = 99999.9f;         // 距離
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
    const float SEARCH_DISTANCE = 2000.0f;
    if (IsInsideCircleXZ(myPos, targetPos, SEARCH_DISTANCE))
    {
        float fAngleToTarget = GetAngleToTargetXZ(targetPos, myPos);
        SetRotDestY(fAngleToTarget);
        SetRotY(fAngleToTarget);
        m_appearState = APPEAR_STATE_EXIST;
        SetInvincible(false);
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
                TakeDamage(FORTRESS_CRUSH_DAMAGE, myPos, pFortress->GetPos());
            }
        }
    }
}