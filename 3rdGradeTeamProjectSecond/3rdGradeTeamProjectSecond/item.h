//======================================================================================
//
// アイテム処理 (item.h)
// Author : 後藤慎之助
//
//======================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

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
class CEffect3D;
class CPlayer;

//================================================
// クラス宣言
//================================================

// アイテムクラス
class CItem : public CScene3D
{
public:
    CItem();
    ~CItem();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);    // 初期化処理
    void Uninit(void);                                  // 終了処理
    void Update(void);                                  // 更新処理
    void Draw(void);                                    // 描画処理
    static CItem *Create(int type, D3DXVECTOR3 pos, float fEnergy = 0.0f);    // 生成処理

    // アイテムの種類                                                                                                                                               // アイテムの種類
    typedef enum
    {
        TYPE_DENTI_5 = 0,   // 単5電池
        TYPE_DENTI_3,       // 単3電池
        TYPE_DENTI_1,       // 単1電池
    }TYPE;

    //=============================
    // ゲッター
    //=============================
    D3DXVECTOR2 GetCollisionSize(void) { return m_collisionSize; }
    float GetEnergy(void) { return m_fGetEnergy; }

    //=============================
    // セッター
    //=============================

private:
    int m_type;                     // 種類
    D3DXVECTOR2 m_collisionSize;    // 衝突サイズ
    D3DXVECTOR3 m_move;             // 移動量
    float m_fSpeed;                 // 速度

    D3DXVECTOR3 m_posOld;           // 1F前の位置
    int m_nLife;                    // 寿命
    float m_fGetEnergy;             // 獲得エナジー

    bool m_bUseDraw;                // 描画するかどうか
    CEffect3D *m_pEffect3d_Shadow;  // 影へのポインタ
    bool m_bGround;                 // 地面に着地したかどうか（着地したら、プレイヤーが吸収できる）
    CPlayer *m_pTargetPlayer;       // ターゲットのプレイヤーのポインタ

    bool m_bUseCollision;           // 衝突判定を使うかどうか

    //=============================
    // このクラス内でのみ使う処理
    //=============================
    void MoveTowardPlayer(D3DXVECTOR3 myPos);
    void SearchPlayer(D3DXVECTOR3 myPos);
    void Collision(D3DXVECTOR3 myPos);
};

#endif