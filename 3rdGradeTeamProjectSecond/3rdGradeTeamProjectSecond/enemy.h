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
#include "player.h"
#include "effectData.h"

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

    // ターゲット傾向
    typedef enum
    {
        TARGET_TREND_PLAYER = 0,            // プレイヤーを狙う
        TARGET_TREND_FORTRESS,              // 移動要塞を狙う
        TARGET_TREND_PLAYER_AND_FORTRESS,   // プレイヤーと移動要塞を狙う
    }TARGET_TREND;

    // 敵の種類
    typedef enum
    {
        TYPE_SPIDER = 0,    // 蜘蛛
        TYPE_ARMY,          // アーミー
        TYPE_KAMIKAZE,      // カミカゼ
        TYPE_CANNON,        // キャノン
        TYPE_COMMANDER,     // コマンダー
		TYPE_SHINIGAMI,     // シニガミ
        TYPE_PENPEN,        // ペンペン
		TYPE_KIWI,
    }TYPE;

    // 基本状態
    typedef enum
    {
        BASE_STATE_WAIT = 0,    // 待機
        BASE_STATE_PATROL,      // 巡回
        BASE_STATE_ATTACK,      // 攻撃
        BASE_STATE_DAMAGE,      // ダメージ
        BASE_STATE_PARALYSIS,   // 麻痺
        BASE_STATE_DEATH,       // 死亡
    }BASE_STATE;

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

	//=========================
	// シニガミ
	//=========================
	typedef enum
	{
		SHINIGAMI_ANIM_IDLE = 0,      // 待機
		SHINIGAMI_ANIM_WALK,          // 歩き
		SHINIGAMI_ANIM_DAMAGE,        // ダメージ
        SHINIGAMI_ANIM_ATTACK,        // 攻撃
		SHINIGAMI_ANIM_DEATH,         // 死亡
		SHINIGAMI_ANIM_MAX,           // 最大数
	}SHINIGAMI_ANIMATION;
	typedef enum
	{
		SHINIGAMI_PARTS_BODY = 0,
		SHINIGAMI_PARTS_WEP,
		SHINIGAMI_PARTS_MAX,
	}SHINIGAMI_PARTS;

    //=========================
    // ペンペン
    //=========================
    typedef enum
    {
        PENPEN_ANIM_IDLE = 0,      // 待機
        PENPEN_ANIM_WALK,          // 歩き
        PENPEN_ANIM_ATTACK,        // 攻撃
        PENPEN_ANIM_DAMAGE,        // ダメージ
        PENPEN_ANIM_DEATH,         // 死亡
        PENPEN_ANIM_MAX,           // 最大数
    }PENPEN_ANIMATION;
    typedef enum
    {
        PENPEN_PARTS_BODY = 0,
        PENPEN_PARTS_CUTTER_R,
        PENPEN_PARTS_CUTTER_L,
        PENPEN_PARTS_MAX,
    }PENPEN_PARTS;
	
	//=========================
	// キウイ
	//=========================
	typedef enum
	{
		KIWI_ANIM_IDLE = 0,      // 待機
		KIWI_ANIM_WALK,          // 歩き
		KIWI_ANIM_DAMAGE,        // ダメージ
		KIWI_ANIM_DEATH,         // 死亡
		KIWI_ANIM_RUN,           // 走り
		KIWI_ANIM_MAX,           // 最大数
	}KIWI_ANIMATION;
	typedef enum
	{
		KIWI_PARTS_BODY = 0,
		KIWI_PARTS_WING_R,
		KIWI_PARTS_WING_L,
		KIWI_PARTS_FOOT_R,
		KIWI_PARTS_FOOT_L,
		KIWI_PARTS_MAX,
	}KIWI_PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // 初期化処理
    void Uninit(void);                                                                  // 終了処理
    void Update(void);                                                                  // 更新処理
    void Draw(void);                                                                    // 描画処理
    static CEnemy *Create(int type, D3DXVECTOR3 pos, float fStrength = 1.0f,
        int appearState = APPEAR_STATE_EXIST, float fChargeValue = NOT_EXIST_F, float fSearchDistanceForAppear = 2000.0f);// 生成処理

    void DiscoveryTarget(CCharacter *pTarget);                                          // ターゲット発見処理

    //=============================
    // セッター
    //=============================
    void SetBaseState(BASE_STATE nextBaseState, int nNextStateEndFrame = NOT_EXIST);    // 基本状態を変える処理
    void SetWhoContribution(int nWho) { m_nWhoContribution = nWho; }

    //=============================
    // ゲッター
    //=============================
    int GetAppearState(void) { return m_appearState; }

private:
    int m_type;                              // 種類
    float m_fSpeed;                          // 速さ
    float m_fStrength;                       // 強さ(基本1.0倍)
    float m_fChargeValue;                    // チャージ量

    int m_nCntTime;                          // 時間を数える
    bool m_bSquashedByFortress;              // 要塞に踏みつぶされるかどうか

    int m_appearState;                       // 出現状態
    bool m_bDeath;                           // やられているかどうか
    BASE_STATE m_baseState;                  // 基本状態

    int m_walkMotion;                        // 歩きモーション
    int m_attackMotion;                      // 攻撃モーション
    int m_damageMotion;                      // ダメージモーション
    int m_deathMotion;                       // 死亡モーション

    float m_fSearchDistanceForAppear;        // 出現のための検知距離
    D3DXVECTOR3 m_patrolCentralPos;          // 巡回の中心位置
    D3DXVECTOR3 m_moveAngle;                 // 移動角度
    int m_nPatrolDistance;                   // 巡回距離
    int m_nCurrentStateEndFrame;             // 現在の状態が終わるフレーム数

    bool m_bWarning;                         // 警戒中かどうか
    float m_fDiscoveryTargetDistance;        // ターゲット発見距離
    CCharacter *m_pTarget;                   // 標的のキャラクター
    int m_setAnimationThisFrame;             // このフレーム内で、設定するアニメーション番号

    bool m_bUseCommonAtkFollow;              // 追従攻撃を使用するかどうか
    TARGET_TREND m_targetTrend;              // ターゲット傾向
    int m_nAddScore;                         // 加算スコア
    int m_nWhoContribution;                  // 誰の貢献か
    int m_nDeathContributionPoint;           // 死亡した際に、プレイヤーに入る貢献度

    CEffectData::IntervalEffect m_Effect;    // 一定間隔で発生させるエフェクト（カミカゼの火花など）

    bool m_bDeathBySquashed;                 // 踏みつぶされて死んだか
    bool m_bAtkStartFlag;                    // 攻撃が不定間隔のものに使う、攻撃開始フラグ
    CModelEffect *m_pModelEffect;            // 汎用のモデルエフェクト（ペンペンの回転攻撃の刃など）

    //=============================
    // 種類ごとの処理
    //=============================
    void SetupInfoByType(void);
    void AtkCommonFollow(D3DXVECTOR3& myPos);
    void AtkArmy(D3DXVECTOR3& myPos);
    void AtkKamikaze(D3DXVECTOR3& myPos);
    void AtkCannon(D3DXVECTOR3& myPos);
    void AtkCommander(D3DXVECTOR3& myPos);
	void AtkShinigami(D3DXVECTOR3& myPos);
    void AtkPenpen(D3DXVECTOR3& myPos);
	void AtkKiwi(D3DXVECTOR3& myPos);

    //=============================
    // このクラス内でのみ使う処理
    //=============================
    void Appear(void);
    void SquashedByFortress(D3DXVECTOR3 myPos);
    void DeathOneFrame(D3DXVECTOR3 myPos);
    void RePatrol(void);

    //=============================
    // AI系
    //=============================
    void WaitAI(D3DXVECTOR3& myPos);
    void PatrolAI(D3DXVECTOR3& myPos);
    void AttackAI(D3DXVECTOR3& myPos);
    void DamageAI(void);
};

#endif