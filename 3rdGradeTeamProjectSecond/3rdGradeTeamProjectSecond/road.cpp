//===============================================
//
// 道の処理 (road.cpp)
// Author : 後藤慎之助
//
//===============================================

//========================
// インクルードファイル
//========================
#include "road.h"

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CRoad::CRoad() :CScene3D(CScene::OBJTYPE_ROAD)
{
    m_col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
    m_colPhase = COLOR_PHASE_G_DOWN;
    m_bPast = false;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CRoad::~CRoad()
{

}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CRoad::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 初期化
    CScene3D::Init(pos, size);

    // スケールを設定
    SetScale(size);

    // モデルデータをバインド
    BindModelData(42);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CRoad::Uninit(void)
{
    CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CRoad::Update(void)
{
    const float COLOR_CHANGE_RATE = 0.005f;
    switch (m_colPhase)
    {
    case COLOR_PHASE_G_DOWN:
        m_col.g -= COLOR_CHANGE_RATE;
        if (m_col.g <= 0.0f)
        {
            m_col.g = 0.0f;
            m_colPhase = COLOR_PHASE_G_UP;
        }
        break;
    case COLOR_PHASE_G_UP:
        m_col.g += COLOR_CHANGE_RATE;
        if (m_col.g >= 1.0f)
        {
            m_col.g = 1.0f;
            m_colPhase = COLOR_PHASE_G_DOWN;
        }
        break;
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CRoad::Draw(void)
{
    // 通過したら描画しない
    if (!m_bPast)
    {
        CScene3D::Draw(true, true, m_col);
    }
}

//=============================================================================
// インスタンス生成処理
// Author : 後藤慎之助
//=============================================================================
CRoad * CRoad::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // ポインタを用意
    CRoad *pRoad = NULL;

    // メモリ確保
    pRoad = new CRoad;

    // 先に結びつけておく
    pRoad->SetRot(rot);

    // 初期化
    pRoad->Init(pos, DEFAULT_SCALE);

    return pRoad;
}