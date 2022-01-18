//===============================================
//
// モデルエフェクトの処理 (modelEffect.cpp)
// Author : 後藤慎之助
//
//===============================================

//========================
// インクルードファイル
//========================
#include "modelEffect.h"
#include "library.h"

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CModelEffect::CModelEffect() :CScene3D(CScene::OBJTYPE_MODEL_EFFECT)
{
    m_nModelType = 0;
    m_col = SCENE3D_EMISSIVE_COLOR;
    m_colChangeRate = DEFAULT_COLOR_NONE;
    m_bUseLight = true;

    m_bUseDraw = true;
    m_bUseAdditiveSynthesis = false;

    m_bShootUp = false;
    m_move = DEFAULT_VECTOR;
    m_rotMove = DEFAULT_VECTOR;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CModelEffect::~CModelEffect()
{

}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CModelEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 初期化
    CScene3D::Init(pos, size);

    // スケールを設定
    SetScale(size);

    // モデルデータをバインド
    BindModelData(m_nModelType);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CModelEffect::Uninit(void)
{
    CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CModelEffect::Update(void)
{
    m_col += m_colChangeRate;

    // 打ち上げ処理
    if (m_bShootUp)
    {
        D3DXVECTOR3 pos = GetPos();
        D3DXVECTOR3 rot = GetRot();
        pos += m_move;
        if (pos.y <= 0.0f)
        {
            pos.y = 0.0f;
            m_move = DEFAULT_VECTOR;
            m_rotMove = DEFAULT_VECTOR;
        }
        else
        {
            rot += m_rotMove;
            m_move.y -= 1.1f;
        }

        // 設定
        SetPos(pos);
        SetRot(rot);
    }

    if (m_col.a < 0.0f)
    {
        Uninit();
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CModelEffect::Draw(void)
{
    if (m_bUseDraw)
    {
        if (m_bUseAdditiveSynthesis)
        {
            CScene3D::SetAdditiveSynthesis();
        }

        CScene3D::Draw(true, m_bUseLight, m_col);
    }
}

//=============================================================================
// インスタンス生成処理
// Author : 後藤慎之助
//=============================================================================
CModelEffect * CModelEffect::Create(int nModelType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXCOLOR colChangeRate, bool bUseLight)
{
    // ポインタを用意
    CModelEffect *pModelEffect = NULL;

    // メモリ確保
    pModelEffect = new CModelEffect;

    // 先に結びつけておく
    pModelEffect->m_nModelType = nModelType;
    pModelEffect->SetRot(rot);

    // 初期化
    pModelEffect->Init(pos, DEFAULT_SCALE);

    // 引数を結びつけておく
    pModelEffect->m_col = col;
    pModelEffect->m_colChangeRate = colChangeRate;
    pModelEffect->m_bUseLight = bUseLight;

    return pModelEffect;
}

//=============================================================================
// 打ち上げ処理の設定
// Author : 後藤慎之助
//=============================================================================
void CModelEffect::SetShootUp(D3DXVECTOR2 slidePos)
{
    m_bShootUp = true;
    m_colChangeRate = D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.005f);

    // 位置をずらす
    D3DXVECTOR3 myPos = GetPos();
    float fPosX = float(GetRandNum((int)slidePos.x, 0)) - float(GetRandNum((int)slidePos.x, 0));
    float fPosZ = float(GetRandNum((int)slidePos.y, 0)) - float(GetRandNum((int)slidePos.y, 0));
    myPos += D3DXVECTOR3(fPosX, 0.0f, fPosZ);
    SetPos(myPos);

    // 移動量を出す
    float fSpeed = float(GetRandNum(5000, 4000)) / 100.0f;
    m_move = D3DXVECTOR3(0.0f, fSpeed, 0.0f);

    // 回転の速さを決める
    float fRotSpeedX = float(GetRandNum(1500, 500)) / 100.0f - float(GetRandNum(1500, 500)) / 100.0f;
    float fRotSpeedY = float(GetRandNum(1500, 500)) / 100.0f - float(GetRandNum(1500, 500)) / 100.0f;
    float fRotSpeedZ = float(GetRandNum(1500, 500)) / 100.0f - float(GetRandNum(1500, 500)) / 100.0f;
    m_rotMove = D3DXVECTOR3(D3DXToRadian(fRotSpeedX), D3DXToRadian(fRotSpeedY), D3DXToRadian(fRotSpeedZ));
}