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
        BindModelData(57);
        break;
    case TYPE_NORMAL_GATE:
        m_bBreak = true;
        BindModelData(1);
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

    // 使用フラグがなくなったら消滅
    if (!m_bUse)
    {
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
void CBlock::TakeDamage(bool bBreakGoalGate)
{
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
                // リザルトに移行
                CFade::SetFade(CManager::MODE_RESULT);
                m_bUse = false;
            }
        }
        else if (m_type == TYPE_NORMAL_GATE)
        {
            if (bBreakGoalGate)
            {
                m_bUse = false;
            }
        }
        else
        {
            m_bUse = false;
        }
    }
}