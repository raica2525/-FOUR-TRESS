//======================================================================================
//
// ブロック処理 (block.h)
// Author : 後藤慎之助
//
//======================================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene3d.h"

//================================================
// マクロ定義
//================================================

//================================================
// 前方宣言
//================================================
class CModelEffect;

//================================================
// クラス宣言
//================================================

// ブロッククラス
class CBlock : public CScene3D
{
public:
    CBlock();
    ~CBlock();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CBlock *Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 collisionSize, D3DXVECTOR3 rot);        // 生成処理

    bool TakeDamage(bool bBreakGoalGate);

    // ブロックの種類
    typedef enum
    {
        TYPE_FRAME = 0,   // 枠
        TYPE_GOAL_GATE,   // ゴールの門
        TYPE_NORMAL_GATE, // ノーマルゲート
    }TYPE;

    //=============================
    // ゲッター
    //=============================
    D3DXVECTOR3 GetCollisionSize(void) { return m_collisionSize; }

    //=============================
    // セッター
    //=============================

private:
    int m_type;                     // 種類
    D3DXVECTOR3 m_collisionSize;    // 衝突サイズ

    bool m_bBreak;                  // 壊れるかどうか
    bool m_bUse;                    // 使用するかどうか

    CModelEffect*m_pModelEffect;    // モデルエフェクト（ゴールゲートの回転するキューブなど）

    //=============================
    // このクラス内でのみ使う処理
    //=============================
};

#endif