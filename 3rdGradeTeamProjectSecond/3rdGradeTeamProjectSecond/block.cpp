//======================================================================================
//
// ブロック処理 (block.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "block.h"
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
#include "fade.h"

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CBlock::CBlock() :CScene3D(CScene::OBJTYPE_BLOCK)
{
    m_type = TYPE_FRAME;
    m_collisionSize = DEFAULT_VECTOR;
    
    m_bBreak = false;
    m_bUse = true;

    m_pModelEffect = NULL;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 固有の情報を決める
    switch (m_type)
    {
    case TYPE_FRAME:
        m_bBreak = false;
        BindModelData(1);
        break;
    case TYPE_GOAL_GATE:
        m_bBreak = true;
        BindModelData(34);
        m_pModelEffect = CModelEffect::Create(33, pos + D3DXVECTOR3(0.0f, 900.0f, 0.0f));
        break;
    case TYPE_NORMAL_GATE:
        m_bBreak = true;
        BindModelData(35);
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
void CBlock::Uninit(void)
{
    // モデルエフェクトを使っていたものは、消すフラグを立てる（アルファ値が0を下回ったら消す処理を代用）
    if (m_pModelEffect)
    {
        m_pModelEffect->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f));
    }

    CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CBlock::Update(void)
{
#ifdef COLLISION_TEST
    CDebug::Create(GetPos(), m_collisionSize, CDebug::TYPE_MOMENT, 1);
#endif // COLLISION_TEST

    // 種類によっての処理
    switch (m_type)
    {
    case TYPE_GOAL_GATE:
    {
        D3DXVECTOR3 rot = m_pModelEffect->GetRot();
        rot.y += D3DXToRadian(1.0f);
        if (rot.y > D3DX_PI)
        {
            rot.y -= D3DX_PI * 2.0f;
        }
        else if (rot.y < -D3DX_PI)
        {
            rot.y += D3DX_PI * 2.0f;
        }
        rot.x += D3DXToRadian(1.0f);
        if (rot.x > D3DX_PI)
        {
            rot.x -= D3DX_PI * 2.0f;
        }
        else if (rot.x < -D3DX_PI)
        {
            rot.x += D3DX_PI * 2.0f;
        }
        m_pModelEffect->SetRot(rot);
        break;
    }
    }

    // 使用フラグがなくなったら消滅
    if (!m_bUse)
    {
        // 種類によっての処理
        switch (m_type)
        {
        case TYPE_NORMAL_GATE:
        {
            D3DXVECTOR3 pos = GetPos();
            for (int nCnt = 0; nCnt < 10; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(75, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            for (int nCnt = 0; nCnt < 5; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(76, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            for (int nCnt = 0; nCnt < 15; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(77, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            break;
        }
        case TYPE_GOAL_GATE:
        {
            D3DXVECTOR3 pos = GetPos();
            for (int nCnt = 0; nCnt < 5; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(78, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            for (int nCnt = 0; nCnt < 15; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(77, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            CModelEffect *pModel = CModelEffect::Create(33, pos);
            pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            break;
        }
        }

        Uninit();
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CBlock::Draw(void)
{
    CScene3D::Draw();
}

//=============================================================================
// 生成処理
// Author : 後藤慎之助
//=============================================================================
CBlock *CBlock::Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 collisionSize, D3DXVECTOR3 rot)
{
    // メモリ確保
    CBlock *pBlock = NULL;
    pBlock = new CBlock;

    // 先に結びつけておく
    pBlock->m_type = type;
    pBlock->SetRot(rot);

    // 初期化
    pBlock->Init(pos, DEFAULT_SCALE);

    // 引数を結びつけておく
    pBlock->m_collisionSize = collisionSize;

    return pBlock;
}

//=============================================================================
// ダメージを受ける処理（ここの関数ゴリ押しすぎた、「ゲートを破壊できるのは電磁砲のみ」）
// Author : 後藤慎之助
//=============================================================================
bool CBlock::TakeDamage(bool bBreakGoalGate)
{
    bool bBreak = false;

    // 壊れるブロックなら
    if (m_bBreak)
    {
        // ゴールゲートなら、ゴールゲートを破壊できる攻撃でのみ破壊される
        if (m_type == TYPE_GOAL_GATE)
        {
            // ここに、移動要塞がやられていた際のreturn処理を書く
            // 負け確の際に破壊できないように

            if (bBreakGoalGate)
            {
                // 勝利状態に
                CGame::SetFinish(true);
                m_bUse = false;
                bBreak = true;
            }
        }
        else if (m_type == TYPE_NORMAL_GATE)
        {
            if (bBreakGoalGate)
            {
                m_bUse = false;
                bBreak = true;
            }
        }
        else
        {
            m_bUse = false;
            bBreak = true;
        }
    }

    return bBreak;
}