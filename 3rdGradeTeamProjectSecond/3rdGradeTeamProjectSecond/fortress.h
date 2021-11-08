//======================================================================================
//
// 移動要塞処理 (fortress.h)
// Author : 後藤慎之助
//
//======================================================================================
#ifndef _FORTRESS_H_
#define _FORTRESS_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "character.h"
#include "model.h"
#include "road.h"

//================================================
// マクロ定義
//================================================

//================================================
// 前方宣言
//================================================

//================================================
// クラス宣言
//================================================

// 移動要塞クラス
class CFortress : public CCharacter
{
public:
    CFortress();
    ~CFortress();

    // 列挙型宣言(モーション)
    typedef enum
    {
        ANIM_IDLE = 0,      // 待機
        ANIM_WARN,          // 威嚇
        ANIM_MAX,           // 最大数
    }ANIMATION;

    // 列挙型宣言
    typedef enum
    {
        PARTS_FIGHTER = 0,
        PARTS_RIGHT_WING_0,
        PARTS_RIGHT_WING_1,
        PARTS_RIGHT_WING_2,
        PARTS_RIGHT_WING_3,
        PARTS_LEFT_WING_0,
        PARTS_LEFT_WING_1,
        PARTS_LEFT_WING_2,
        PARTS_LEFT_WING_3,
        PARTS_MAX,
    }PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CFortress *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR);        // 生成処理

    //=============================
    // ゲッター
    //=============================
    D3DXVECTOR2 GetCollisionSizeDeffence(void) { return m_collisionSizeDeffence; }

    //=============================
    // セッター
    //=============================

private:
    D3DXVECTOR2 m_collisionSizeDeffence;     // 防御衝突サイズ
    float m_fSpeed;                          // 速さ
    float m_fLife;                           // 体力

    bool m_bSearchRoad;                      // 道を探しているかどうか
    D3DXVECTOR3 m_moveAngle;                 // 移動の向き
    CRoad* m_pTargetRoad;                    // 目標の道

    //=============================
    // このクラス内でのみ使う処理
    //=============================
    void SearchRoad(D3DXVECTOR3 myPos);
};

#endif