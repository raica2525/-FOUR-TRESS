//======================================================================================
//
// 弾処理 (bullet.h)
// Author : 後藤慎之助
//
//======================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

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

//================================================
// クラス宣言
//================================================

// 弾クラス
class CBullet : public CScene3D
{
public:
    CBullet();
    ~CBullet();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CBullet *Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, float fStrength = 1.0f, D3DXVECTOR3 rot = DEFAULT_VECTOR);           // 生成処理

    // 弾の種類
    typedef enum
    {
        TYPE_ARMY_ATTACK = 0,   // アーミーの攻撃
        TYPE_THUNDER,           // 雷
        TYPE_RAILGUN_LV2,       // 電磁砲lv2
        TYPE_RAILGUN_LV3,       // 電磁砲lv3
    }TYPE;

    // 何に当たるかのフラグ
    typedef enum
    {
        COLLISION_FLAG_NONE = 0,                      // なし
        COLLISION_FLAG_ENEMY = 0x001 << 0,            // 敵に当たる
        COLLISION_FLAG_PLAYER = 0x001 << 1,           // プレイヤーに当たる
        COLLISION_FLAG_OFF_BLOCK = 0x001 << 2,        // ブロックに当たらない
    }COLLISION_FLAG;

    //=============================
    // ゲッター
    //=============================
    D3DXVECTOR2 GetCollisionSize(void) { return m_collisionSize; }

    //=============================
    // セッター
    //=============================

private:
    int m_type;                     // 種類
    D3DXVECTOR2 m_collisionSize;    // 衝突サイズ
    D3DXVECTOR3 m_moveAngle;        // 移動の角度
    float m_fSpeed;                 // 速さ
    int m_collisionFlag;            // 当たり判定のフラグ

    D3DXVECTOR3 m_posOld;           // 1F前の位置
    int m_nLife;                    // 寿命
    float m_fDamage;                // ダメージ

    bool m_bUseCntTime;             // 時間経過で変化の起きる弾かどうか
    int m_nCntTime;                 // 生成されてからの時間を数える
    bool m_bUseDraw;                // 描画するかどうか

    bool m_bHitErase;               // 当たった時に消すかどうか
    CEffect3D *m_pEffect3d_Shadow;  // 影へのポインタ
    bool m_bBreakGoalGate;          // ゴールゲートを壊すかどうか

    //=============================
    // 種類ごとの処理
    //=============================
    void SetupInfoByType(float fStrength, const D3DXVECTOR3 pos);

    //=============================
    // このクラス内でのみ使う処理
    //=============================
    void Collision(D3DXVECTOR3 bulletPos);
};

#endif