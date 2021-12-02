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

    // 敵の出現状況
    typedef enum
    {
        APPEAR_STATE_EXIST = 0,       // 出現している
        APPEAR_STATE_WAIT_FORTRESS,   // 移動要塞接近時、出現
        APPEAR_STATE_WAIT_PLAYER,     // プレイヤー接近時、出現
    }APPEAR_STATE;

    // 敵の種類
    typedef enum
    {
        TYPE_SPIDER = 0,    // 蜘蛛
        TYPE_ARMY,          // アーミー
        TYPE_KAMIKAZE,      // カミカゼ
        TYPE_CANNON,        // キャノン
        TYPE_COMMANDER,     // コマンダー
    }TYPE;

    //=========================
    // 蜘蛛
    //=========================
    typedef enum
    {
        SPIDER_ANIM_IDLE = 0,      // 待機
        SPIDER_ANIM_WALK,          // 歩き
        SPIDER_ANIM_TAUNT,         // 挑発
        SPIDER_ANIM_ATTACK,        // 攻撃
        SPIDER_ANIM_JUMP,          // ジャンプ
        SPIDER_ANIM_MAX,           // 最大数
    }SPIDER_ANIMATION;
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

    //=========================
    // アーミー
    //=========================
    typedef enum
    {
        ARMY_ANIM_IDLE = 0,      // 待機
        ARMY_ANIM_WALK,          // 歩き
        ARMY_ANIM_ATTACK,        // 攻撃
        ARMY_ANIM_DAMAGE,        // ダメージ
        ARMY_ANIM_DEATH,         // 死亡
        ARMY_ANIM_MAX,           // 最大数
    }ARMY_ANIMATION;
    typedef enum
    {
        ARMY_PARTS_BODY = 0,
        ARMY_PARTS_RHAND,
        ARMY_PARTS_LHAND,
        ARMY_PARTS_MAX,
    }ARMY_PARTS;

    //=========================
    // カミカゼ
    //=========================
    typedef enum
    {
        KAMIKAZE_ANIM_IDLE = 0,      // 待機
        KAMIKAZE_ANIM_WALK,          // 歩き
        KAMIKAZE_ANIM_ATTACK,        // 攻撃
        KAMIKAZE_ANIM_DAMAGE,        // ダメージ
        KAMIKAZE_ANIM_DEATH,         // 死亡
        KAMIKAZE_ANIM_MAX,           // 最大数
    }KAMIKAZE_ANIMATION;
    typedef enum
    {
        KAMIKAZE_PARTS_BODY = 0,
        KAMIKAZE_PARTS_ARML,
        KAMIKAZE_PARTS_ARMR,
        KAMIKAZE_PARTS_BOMB,
        KAMIKAZE_PARTS_BOMB_CUBE,
        KAMIKAZE_PARTS_MAX,
    }KAMIKAZE_PARTS;

    //=========================
    // キャノン
    //=========================
    typedef enum
    {
        CANNON_PARTS_BODY = 0,
        CANNON_PARTS_FIRE_CUBE,
        CANNON_PARTS_MAX,
    }CANNON_PARTS;

    //=========================
    // コマンダー
    //=========================
    typedef enum
    {
        COMMANDER_ANIM_IDLE = 0,      // 待機
        COMMANDER_ANIM_SPAWN_ENEMY,   // 敵生成
    }COMMANDER_ANIMATION;
    typedef enum
    {
        COMMANDER_PARTS_BODY = 0,
        COMMANDER_PARTS_PETAL1,
        COMMANDER_PARTS_PETAL2,
        COMMANDER_PARTS_PETAL3,
        COMMANDER_PARTS_PETAL4,
        COMMANDER_PARTS_PETAL5,
        COMMANDER_PARTS_SPAWN_POS,
        COMMANDER_PARTS_MAX,
    }COMMANDER_PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CEnemy *Create(int type, D3DXVECTOR3 pos, float fStrength = 1.0f,
        int appearState = APPEAR_STATE_EXIST);                  // 生成処理

    //=============================
    // セッター
    //=============================

    //=============================
    // ゲッター
    //=============================
    int GetIdx(void) { return m_nIdx; }

private:
    int m_type;                              // 種類
    float m_fSpeed;                          // 速さ
    float m_fStrength;                       // 強さ(基本1.0倍)

    int m_nCntTime;                          // 時間を数える
    bool m_bSquashedByFortress;              // 要塞に踏みつぶされるかどうか
    bool m_bDetectPlayer;                    // プレイヤーを見つけているかどうか

    int m_appearState;                       // 出現状態
    bool m_bDeath;                           // やられているかどうか
    int m_nIdx;                              // 生成のインデックス

    int m_walkMotion;                        // 歩きモーション
    int m_attackMotion;                      // 攻撃モーション
    int m_damageMotion;                      // ダメージモーション
    int m_deathMotion;                       // 死亡モーション

    //=============================
    // 種類ごとの処理
    //=============================
    void SetupInfoByType(void);

    //=============================
    // このクラス内でのみ使う処理
    //=============================
    void Appear(void);
    void SquashedByFortress(D3DXVECTOR3 myPos);
};

#endif