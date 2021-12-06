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
#define FORTRESS_CRUSH_DAMAGE 5000.0f

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

    // 列挙型宣言
    typedef enum
    {
        PARTS_BODY = 0,         // 車体
        PARTS_CANNON_CENTER,    // 砲台中心
        PARTS_SEAT,             // 座席
        PARTS_FIRE_POS,         // 発射位置
        PARTS_MAX,
    }PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CFortress *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR);        // 生成処理

    void ResetAttack(void);
    void AddChargeValue(const float fChargeValue);

    //=============================
    // セッター
    //=============================
    void SetNowWhoRiding(bool bRiding) { m_bNowWhoRiding = bRiding; }
    void SetAttackPhase(bool bAttackPhase) { m_bAttackPhase = bAttackPhase; }
    void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

    //=============================
    // ゲッター
    //=============================
    bool GetNowWhoRiding(void) { return m_bNowWhoRiding; }
    bool GetAttackPhase(void) { return m_bAttackPhase; }
    float GetChargeValue(void) { return m_fChargeValue; }

private:
    float m_fSpeed;             // 速さ

    bool m_bSearchRoad;         // 道を探しているかどうか
    D3DXVECTOR3 m_moveAngle;    // 移動の向き
    CRoad* m_pTargetRoad;       // 目標の道
    bool m_bNowWhoRiding;       // 誰か今乗っているかどうか

    float m_fChargeValue;       // チャージ量
    bool m_bAttackPhase;        // 攻撃フェーズかどうか
    int m_nCntTime;             // 時間をカウント

    bool m_bDisp;               // 表示しているかどうか

    //=============================
    // このクラス内でのみ使う処理
    //=============================
    void SearchRoad(D3DXVECTOR3 myPos);
    void AttackPhase(void);
    bool CollisionWall(D3DXVECTOR3 myPos);
};

#endif