//====================================================================
//
// 道の処理 (road.h)
// Author : 後藤慎之助
//
//====================================================================
#ifndef _ROAD_H_
#define _ROAD_H_

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

// 道クラス
class CRoad : public CScene3D
{
public:

    // カラーフェーズ
    typedef enum
    {
        COLOR_PHASE_G_DOWN = 0,
        COLOR_PHASE_G_UP,
    }COLOR_PHASE;

    CRoad();
    ~CRoad();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CRoad *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR);

    //=============================
    // ゲッター
    //=============================
    bool GetPast(void) { return m_bPast; }

    //=============================
    // セッター
    //=============================
    void SetPast(bool bPast) { m_bPast = bPast; }

private:
    D3DXCOLOR m_col;        // 色
    COLOR_PHASE m_colPhase; // カラーフェーズ
    bool m_bPast;           // 通り過ぎたかどうか
};

#endif