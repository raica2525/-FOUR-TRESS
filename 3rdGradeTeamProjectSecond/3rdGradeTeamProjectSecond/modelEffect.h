//====================================================================
//
// モデルエフェクトの処理 (modelEffect.h)
// Author : 後藤慎之助
//
//====================================================================
#ifndef _MODEL_EFFECT_H_
#define _MODEL_EFFECT_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene3d.h"

//================================================
// 前方宣言
//================================================

//================================================
// マクロ定義
//================================================

//================================================
// クラス宣言
//================================================

// モデルエフェクトクラス
class CModelEffect : public CScene3D
{
public:

    CModelEffect();
    ~CModelEffect();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CModelEffect *Create(int nModelType, D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR, D3DXCOLOR col = DEFAULT_COLOR, D3DXCOLOR colChangeRate = DEFAULT_COLOR_NONE, bool bUseLight = true);

    //=======================
    // セッター
    //=======================
    void SetAdditive(void) { m_bUseAdditiveSynthesis = true; }
    void SetUseDraw(bool bUseDraw) { m_bUseDraw = bUseDraw; }
    void SetColor(D3DXCOLOR col) { m_col = col; }
    void SetShootUp(D3DXVECTOR2 slidePos);

    //=======================
    // ゲッター
    //=======================

private:
    int m_nModelType;             // 使うモデルの種類
    D3DXCOLOR m_col;              // 色
    D3DXCOLOR m_colChangeRate;    // 色変化割合
    bool m_bUseLight;             // ライトを使うかどうか

    bool m_bUseDraw;              // 描画するかどうか
    bool m_bUseAdditiveSynthesis; // 加算合成にするかどうか

    bool m_bShootUp;              // 打ち上げるかどうか
    D3DXVECTOR3 m_move;           // 移動量
    D3DXVECTOR3 m_rotMove;        // 向きの移動量
};

#endif