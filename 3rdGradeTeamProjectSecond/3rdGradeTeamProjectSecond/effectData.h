//====================================================================
//
// エフェクトデータ管理 (effectData.h)
// Author : 後藤慎之助
//
//====================================================================
#ifndef _EFFECT_DATA_H_
#define _EFFECT_DATA_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define EFFECT_PI 314                   // 円の表現の際に使う値（これをエフェクトの浮動小数点で割る）
#define EFFECT_FLOATING_POINT 100.0f    // エフェクトの浮動小数点

// ブロック等に当たった際、板ポリのエフェクトを置くための回転量（ブロックの中から見ているので注意）
#define LAY_ROT_TOP D3DXVECTOR3(D3DXToRadian(-90.0f), 0.0f, 0.0f)    // 天井
#define LAY_ROT_LEFT D3DXVECTOR3(0.0f, D3DXToRadian(270.0f), 0.0f)  // 左壁
#define LAY_ROT_BOT D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f)    // 地面
#define LAY_ROT_RIGHT D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f)  // 右壁
#define LAY_ROT_BACK D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f)
#define LAY_ROT_FRONT D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0001f))

#define MAX_EFFECT_TYPE 64

//================================================
// クラス宣言
//================================================

// エフェクトデータの管理クラス
class CEffectData
{
public:
    CEffectData();
    ~CEffectData();

    typedef enum
    {
        TYPE_HEAL = 0,              // 回復
        TYPE_HEART,                 // ハート弾
        TYPE_THRUST,                // ヒットエフェクト(突き、弓)
        TYPE_NEGA,                  // 反転合成
        TYPE_SLASH,                 // ヒットエフェクト（斬撃）
        TYPE_LIGHTNING_0,           // 電撃弾_0
        TYPE_LIGHTNING_1,           // 電撃弾_1
        TYPE_SECOND_JUMP_AIR_RING,  // 二段ジャンプの空気の輪
        TYPE_SECOND_JUMP_SMOKE,     // 二段ジャンプの砂煙
        TYPE_LIGHTNING_RANGE,       // 電撃(範囲)
        TYPE_SMOKE,                 // 煙
        TYPE_GET,                   // アイテム取得
        TYPE_EXPLOSION_0,           // [12] 爆発_0
        TYPE_EXPLOSION_1,           // [13] 爆発_1
        TYPE_EXPLOSION_2,           // [14] 爆発_2
        TYPE_ENEMY_POP_0,           // [15] 敵出現_0
        TYPE_ENEMY_POP_1,           // [16] 敵出現_1
        TYPE_ENEMY_DESTROYING,      // [17] 敵やられ
        TYPE_WIND_0,                // [18] 風_0
        TYPE_WIND_1,                // [19] 風_1
        TYPE_HIT_BALL,              // ボールが当たった時
        TYPE_ROAR_0,                // [21] 咆哮_0
        TYPE_ROAR_1,                // [22] 咆哮_1
        TYPE_ROAR_2,                // [23] 咆哮_2
        TYPE_ARROW,                 // [24] 矢のエフェクト
        TYPE_KIRA,                  // カーソルクリック時のキラキラ
        TYPE_SHADOW,                // 影
        TYPE_MAGIC_CIRCLE_0,        // [27] 魔法陣_0
        TYPE_MAGIC_CIRCLE_1,        // [28] 魔法陣_1
        TYPE_MAGIC_CIRCLE_2,        // [29] 魔法陣_2
        TYPE_IMPACT_WAVE_0,         // [30] ウォーリアージャンプ攻撃0
        TYPE_IMPACT_WAVE_1,         // [31] ウォーリアージャンプ攻撃1
        TYPE_IMPACT_WAVE_2,         // [32] ウォーリアージャンプ攻撃2
        TYPE_DARKNESS_AURA_0,       // [33] 即死オーラ_0
        TYPE_DARKNESS_AURA_1,       // [34] 即死オーラ_1
        TYPE_LANDING_FUGITIVE_DUST,              // [35] 着地砂埃
        TYPE_JUMP_FUGITIVE_DUST,             // [36] ジャンプ砂埃
        TYPE_SPARK,        // [37] 火花
        TYPE_WALL_HIT_SHOCK,        // 壁バウンド衝撃波
        TYPE_ABSORB,                // 立ち上がり吸収
        TYPE_READY_TO_FIGHT1,       // 準備完了1
        TYPE_READY_TO_FIGHT2,       // 準備完了2
        TYPE_READY_TO_FIGHT3,       // 準備完了3
        TYPE_READY_TO_FIGHT4,       // 準備完了4
        TYPE_CHARGE_SWING_LEFT,     // チャージスイングエフェクト左
        TYPE_CHARGE_SWING_RIGHT,    // チャージスイングエフェクト右
        TYPE_CHARGE_LIGHT,          // チャージ時の光
        TYPE_BARRIER,               // バリア
        TYPE_SP_MAX_1,              // 必殺ゲージMAX1
        TYPE_SP_MAX_2,              // 必殺ゲージMAX2
        TYPE_KAMI,                  // 紙吹雪
        TYPE_SS_1,                  // ストライクシュート1
        TYPE_SS_2,                  // ストライクシュート2
        TYPE_SS_3,                  // ストライクシュート3
        TYPE_SS_BG,                 // ストライクシュート背景
        TYPE_SS_TEXT,               // ストライクシュート文字
    }TYPE;  // 生成するエフェクトの種類

    typedef enum
    {
        PLANE_XY = 0,   // XY平面
        PLANE_XZ,       // XZ平面
    }PLANE;  // 平面の情報

    typedef struct
    {
        int nTexType;                 // 使うテクスチャの種類
        int nNumOnce;                 // 同時発生数
        int plane;                    // 平面

        bool bOnCircleEdge;           // 円の縁から放出するかどうか
        bool bEmitVectorInside;       // 放出方向を内側にするかどうか
        int nScatterAngle;            // 飛散角度（0～314）
        int nScatterWidth;            // 飛散幅（0～314）
        int nSpeedMax;                // 最大速度
        int nSpeedMin;                // 最小速度
        int nAuxiliaryAxisSpeedMax;   // 補助軸の最大速度（2D→3Dで、立体感を出すためのもの）
        int nAuxiliaryAxisSpeedMin;   // 補助軸の最小速度（2D→3Dで、立体感を出すためのもの）

        float fAcceleration;          // 加速度（1.0基準）
        float fGravity;               // 重力
        float fGravityLimit;          // 重力制限

        int nLayRot;                  // ポリゴンそのものを横にするかどうか（1下、2左、3上、4右）
        bool bRotEqualMoveAngle;      // 回転を移動の向きに合わせるか
        int nRotSpeedMax;             // 最大回転速度
        int nRotSpeedMin;             // 最小回転速度

        D3DXCOLOR col;                // 色
        D3DXCOLOR colChangeRate;      // 色変化割合
        float fFadeOutRate;           // α値を下げていく割合（色変化割合でも可能だが、明示的に用意した）
        int nCntFadeOutLock;          // α値をロックするカウンタ

        int nSizeMax;                 // 最大大きさ
        int nSizeMin;                 // 最小大きさ
        D3DXVECTOR3 sizeChangeRate;   // 拡大/縮小割合
        int nCntSizeChangeLock;       // 大きさをロックするカウンタ
        bool bSizeChangeStartOrFinish;// 大きさを変えるのが始まるか、終わるのか
        float fEmitRadius;            // 放出半径

        bool bUseAdditiveSynthesis;   // 加算合成にするかどうか
        bool bUseZBuffer;             // Zバッファをつかうかどうか
        int nAlphaTestBorder;         // αテストのボーダー
    }CreateInfo;    // 生成情報

    HRESULT Init(void);
    void Uninit(void);

    CreateInfo* GetCreateInfo(const int nNum);

private:
    CreateInfo m_aCreateInfo[MAX_EFFECT_TYPE];    // 生成情報
};

#endif