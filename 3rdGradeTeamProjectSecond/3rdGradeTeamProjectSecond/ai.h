//====================================================================
//
// AI処理 (ai.h)
// Author : 後藤慎之助
//
//====================================================================
#ifndef _AI_H_
#define _AI_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "player.h"

//================================================
// クラス宣言
//================================================

// AIクラス
class CAi
{
public:
    CAi();
    ~CAi();

    // ボタンの入力情報
    typedef struct
    {
        bool bButtonA;
        bool bButtonX;
        bool bButtonB;
        bool bButtonR2;
    }ButtonState;

    // 心がけていること
    typedef enum
    {
        CORE_THINKING = 0, // 考え中
        CORE_ASSAULT,      // 強襲（ガン攻め）
        CORE_AVOID,        // 避ける（ガン逃げ）
        CORE_WAIT,         // 待つ（ガン待ち）
        CORE_MAX
    }CORE;

    void Update(void);						    // 更新処理
    static CAi * Create(CPlayer *pPlayer);		// インスタンス生成処理
    void Thinking(void);                        // 考え中
    void AnotherAction(void);                   // 考える以外の行動中
    void GetThinkingTime(void);                 // 考え時間を得る
    void GetAssaultTime(void);                  // 強襲時間を得る
    void GetAvoidTime(void);                    // 避ける時間を得る
    void GetWaitTime(void);                     // 待つ時間を得る
    void DontMove(bool bUseTurn);               // 移動しない
    bool IsFacingEnemy(void);                   // エネミーの方を向いているか
    void RushToTarget(void);                    // ターゲットに詰め寄る
    void RunAwayFromBall(void);                 // ボールから逃げる
    bool JumpBecauseEnemyBulletClose(void);     // 敵の弾が近いからジャンプする
    bool JumpBecauseBallMoveDown(void);         // ボールが下がってきているからジャンプする
    bool DecideAttack(void);                    // 決めきる攻撃をするかどうか
    void GetAttackAngle(void);                  // 攻撃時にどの方向にスティックを倒すか

    void GetTargetPos(void);                    // ターゲットの位置を決める
    void GetAttackRange(void);                  // 攻撃の射程を得る

private:
    CPlayer *m_pPlayer;
    ButtonState m_buttonStateOld;   // 1F前のボタン入力情報

    CORE m_core;                    // 現在何を心がけているか
    int m_nCntActionTime;           // 行動のカウンタ

    D3DXVECTOR3 m_targetPos;        // 標的の位置
    int m_nCntSearchTarget;         // 標的を探すためのカウンタ
    float m_fAttackRange;           // 攻撃の射程
};

#endif