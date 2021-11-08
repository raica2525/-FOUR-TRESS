//======================================================================================
//
// エネミー処理 (enemy.h)
// Author : 後藤慎之助
//
//======================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "character.h"
#include "model.h"

//================================================
// マクロ定義
//================================================

//================================================
// 前方宣言
//================================================

//================================================
// クラス宣言
//================================================

// エネミークラス
class CEnemy : public CCharacter
{
public:
    CEnemy();
    ~CEnemy();

    // 敵の種類
    typedef enum
    {
        TYPE_SPIDER = 0,           // 蜘蛛
    }TYPE;

    // 蜘蛛のアニメーション
    typedef enum
    {
        SPIDER_ANIM_IDLE = 0,      // 待機
        SPIDER_ANIM_WALK,          // 歩き
        SPIDER_ANIM_TAUNT,         // 挑発
        SPIDER_ANIM_ATTACK,        // 攻撃
        SPIDER_ANIM_JUMP,          // ジャンプ
        SPIDER_ANIM_MAX,           // 最大数
    }SPIDER_ANIMATION;

    // 蜘蛛のパーツ
    typedef enum
    {
        SPIDER_PARTS_BODY = 0,
        SPIDER_PARTS_STOMACH,
        SPIDER_PARTS_FANG_RIGHT,
        SPIDER_PARTS_FANG_LEFT,
        SPIDER_PARTS_LEG_RIGHT_0,
        SPIDER_PARTS_LEG_RIGHT_1,
        SPIDER_PARTS_LEG_RIGHT_2,
        SPIDER_PARTS_LEG_RIGHT_3,
        SPIDER_PARTS_LEG_LEFT_0,
        SPIDER_PARTS_LEG_LEFT_1,
        SPIDER_PARTS_LEG_LEFT_2,
        SPIDER_PARTS_LEG_LEFT_3,
        SPIDER_PARTS_STOMACH_CUBE, // 腹から発生させる当たり判定の位置
        SPIDER_PARTS_MAX,
    }SPIDER_PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CEnemy *Create(int type, D3DXVECTOR3 pos, float fStrength = 1.0f, D3DXVECTOR3 rot = DEFAULT_VECTOR);                  // 生成処理

    //=============================
    // ゲッター
    //=============================
    D3DXVECTOR2 GetCollisionSizeDeffence(void) { return m_collisionSizeDeffence; }

    //=============================
    // セッター
    //=============================

private:
    int m_type;                              // 種類
    D3DXVECTOR2 m_collisionSizeDeffence;     // 防御衝突サイズ
    float m_fSpeed;                          // 速さ
    float m_fStrength;                       // 強さ(基本1.0倍)
    float m_fLife;                           // 体力

    int m_nCntTime;                          // 時間を数える

    //=============================
    // 種類ごとの処理
    //=============================
    void SetupInfoByType(void);
};

#endif