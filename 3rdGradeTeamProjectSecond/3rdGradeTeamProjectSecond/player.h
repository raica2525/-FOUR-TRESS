//======================================================================================
//
// プレイヤー処理 (player.h)
// Author : 後藤慎之助、池田悠希（リザルトやカスタマイズのクリッピングマスク対応）
//
//======================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "character.h"
#include "model.h"
#include "cliping_musk.h"

//================================================
// マクロ定義
//================================================

// プレイヤーの移動周り
#define PLAYER_ROT_RIGHT D3DXToRadian(270.0f)
#define PLAYER_ROT_LEFT D3DXToRadian(90.0f)
#define PLAYER_BASE_MINIMUM_SPEED 7.25f                     // 基本最小速度
#define PLAYER_ADD_BASE_SPEED_RATE 0.01f                    // 基本速度に足す割合
#define PLAYER_BASE_MINIMUM_GRAVITY 0.7f                    // 基本最小重力
#define PLAYER_ADD_BASE_GRAVITY_RATE 0.0008f                // 基本重力に足す割合
#define PLAYER_DIVE_SPEED_RATE 2.0f                         // 急降下の速度上昇割合
#define PLAYER_JUMP_FIRST_RATE 23.5f                        // ジャンプの最初の強さ割合
#define PLAYER_NEXT_JUMP_DOWN_RATE 0.8f                     // 次のジャンプがどれほど下がるかの割合
#define PLAYER_JUMP_ADD_FRAME 14                            // ジャンプを加算できるフレーム数
#define PLAYER_JUMP_KEEP_FRAME (8 + PLAYER_JUMP_ADD_FRAME)  // ジャンプをキープできるフレーム数
#define PLAYER_FIRST_JUMP_MOTION_TO_GLIDE 25                // 最初のジャンプモーションが滑空になるまでのフレーム数
#define PLAYER_NEXT_JUMP_MOTION_TO_GLIDE 16                 // 次のジャンプモーションが滑空になるまでのフレーム数
#define PLAYER_CONTROL_MOVE_ON_GROUND 0.85f                 // 地上での移動量制御
#define PLAYER_CONTROL_MOVE_IN_AIR 0.95f                    // 空中での移動量制御
#define PLAYER_CONTROL_MOVE_TAKE_DAMAGE 0.975f              // 負傷中の移動量制御
#define PLAYER_CONTROL_MOVE_SQUAT 0.965f                    // しゃがみ中の移動量制御
#define PLAYER_CONTROL_MOVE_DEATH 0.98f                     // 死亡中の移動量制御
#define PLAYER_CONTROL_MOVE_ADD_RATE_IN_AIR 4               // 空中での移動量加算割合
#define PLAYER_LANDING_TIME 5                               // 着地フレーム
#define PLAYER_ATTACK_ANIM_MIN_FRAME 10                     // 最低保証の攻撃アニメーション再生（ヒットストップ時、変な格好で止めないため）（各攻撃フレームより短く）
#define PLAYER_SQUAT_CUT_COLLISION_SIZE 0.6f                // しゃがみが当たり判定を削る割合
#define STICK_SQUAT_RIGHT(angle) angle > D3DXToRadian(135.0f) && angle <= D3DXToRadian(170.0f)  // しゃがみながら向きを変える右
#define STICK_SQUAT_LEFT(angle) angle < D3DXToRadian(-135.0f) && angle >= D3DXToRadian(-170.0f)  // しゃがみながら向きを変える左
#define PLAYER_DEATH_STOP_POS_Y -99999.9f                   // 死亡時に止めておく高さ
#define PLAYER_DEATH_STOP_FRAME 45                          // 死亡時に、止まるフレーム数
#define PLAYER_SET_WALK_SMOKE_VALUE 6.0f                    // プレイヤーが砂煙を発生させる値
#define PLAYER_WEAPON_LOOK_FRAME 250                        // カスタマイズ画面で武器を見るフレーム数
#define PLAYER_VICTORY_WAIT_START_FRAME 120                 // リザルト画面で待機状態になるフレーム数
#define PLAYER_SP_GAUGE_MAX_EFFECT_INTERVAL 30              // SPゲージエフェクトのインターバル
#define PLAYER_VICTORY_VOICE_FRAME 60                       // 勝利ボイスフレーム
#define PLAYER_SP_WHOLE_FRAME 120                           // 必殺技全体フレーム

// プレイヤーの防御周り
#define PLAYER_MAX_STOCK 6                                  // ストックの最大数
#define PLAYER_TAKE_DAMAGE_RATE_FROM_BALL 10.0f             // ボールからダメージを受けるとき、速度にかける割合
#define PLAYER_TAKE_DAMAGE_BLOWN_GRAVITY 0.5f               // 吹っ飛ばされ中にかかる重力
#define PLAYER_TAKE_DAMAGE_STAND_UP_FRAME 18                // 起き上がりのフレーム数
#define PLAYER_TAKE_DAMAGE_STAND_UP_INVINCIBLE_FRAME (PLAYER_TAKE_DAMAGE_STAND_UP_FRAME - 13) // 起き上がり中の無敵フレーム
#define PLAYER_TAKE_DAMAGE_START_QUICK_STAND_UP (TAKE_DAMAGE_BIG_FRAME - 60) // 即座に起き上がるのが可能になるフレーム
#define PLAYER_TAKE_DAMAGE_SMALL_EFFECT_FRAME 30            // 負傷小コントローラの振動フレーム数
#define PLAYER_TAKE_DAMAGE_BIG_EFFECT_FRAME 60              // 負傷大コントローラの振動フレーム数
#define PLAYER_TAKE_DAMAGE_DEATH_EFFECT_FRAME 90            // 負傷死亡コントローラの振動フレーム数

//// プレイヤーの攻撃周り(全て右向き想定)
////==========================
//// スイング
////==========================
//// 威力
//#define ATTACK_SWING_BASE_POWER 1.0f
//#define ATTACK_SWING_ADD_BASE_POWER_RATE 0.001f
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_SWING_WHOLE_FRAME 21
//#define ATTACK_SWING_END_FRAME (ATTACK_SWING_WHOLE_FRAME - 11)
//// その他
//#define ATTACK_SWING_CHARGE_MAX_FRAME_NORMAL 35            // チャージ最大フレーム数（通常）
//#define ATTACK_SWING_CHARGE_MAX_FRAME_FAST 20              // チャージ最大フレーム数（溜め短縮）
//#define ATTACK_SWING_CHARGE_EMIT_EFFECT_FRAME 10           // チャージエフェクト発生フレーム
//#define ATTACK_SWING_CHARGE_ATTACK_RATE 0.03f              // チャージ時間によるパワー増加割合 (最大チャージはスマッシュと同じ)
//#define STICK_SWING_UP(angle) angle < D3DXToRadian(75.0f) && angle > D3DXToRadian(-75.0f)
//#define STICK_SWING_DOWN(angle) angle >= D3DXToRadian(105.0f) && angle <= D3DXToRadian(180.0f) || angle <= D3DXToRadian(-105.0f) && angle > D3DXToRadian(-180.0f)
//#define STICK_SWING_HORIZON(angle) angle >= D3DXToRadian(75.0f) && angle < D3DXToRadian(105.0f) || angle <= D3DXToRadian(-75.0f) && angle > D3DXToRadian(-105.0f)
//
////==========================
//// スマッシュ
////==========================
//// 威力
//#define ATTACK_SMASH_BASE_POWER 0.2f                // スマッシュの場合、ボールの現在の速さにかける値に変わる
//#define ATTACK_SMASH_ADD_BASE_POWER_RATE 0.00035f
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_SMASH_WHOLE_FRAME 25
//#define ATTACK_SMASH_END_FRAME (ATTACK_SMASH_WHOLE_FRAME - 11)
//// その他（打つ瞬間に、空中でも方向転換ができる）
//#define ATTACK_SMASH_SPEED_RATE 0.1f                // 現在のボールの速さにかける割合
//
////==========================
//// スパイク
////==========================
//// 威力
//#define ATTACK_SPIKE_BASE_POWER 1.0f
//#define ATTACK_SPIKE_ADD_BASE_POWER_RATE 0.001f
//// 当たり判定の大きさ
//#define ATTACK_SPIKE_SIZE_RATE_X 1.5f
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_SPIKE_WHOLE_FRAME 21
//#define ATTACK_SPIKE_END_FRAME (ATTACK_SPIKE_WHOLE_FRAME - 11)
//// その他
//#define STICK_SPIKE_RIGHT(angle) angle >= D3DXToRadian(15.0f) && angle <= D3DXToRadian(165.0f)
//#define STICK_SPIKE_LEFT(angle) angle <= D3DXToRadian(-15.0f) && angle >= D3DXToRadian(-165.0f)
//#define STICK_SPIKE_VERTICAL(angle) angle < D3DXToRadian(15.0f) && angle > D3DXToRadian(-15.0f) || angle > D3DXToRadian(165.0f) && angle <= D3DXToRadian(180.0f) || angle < D3DXToRadian(-165.0f) && angle > D3DXToRadian(-180.0f)
//
////==========================
//// キャッチの構え
////==========================
//// 位置スライド
//#define ATTACK_CATCH_READY_SLIDE_POS_X_RATE 0.65f
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_CATCH_READY_WHOLE_FRAME 21
//#define ATTACK_CATCH_READY_END_FRAME (ATTACK_SWING_WHOLE_FRAME - 11)
//// その他
//#define ATTACK_CATCH_READY_EFFECT_FRAME 15  // コントローラの振動フレーム数
//
////==========================
//// 投げ
////==========================
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_THROW_WHOLE_FRAME 55
//#define ATTACK_THROW_END_FRAME (ATTACK_THROW_WHOLE_FRAME - 35)
//// その他
//#define ATTACK_THROW_SLOW_SPEED_RATE 0.2f   // 投げ中、どれくらいゆっくりにするか（通常速度でも面白そう）
//
////==========================
//// バント
////==========================
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_BUNT_WHOLE_FRAME 21
//#define ATTACK_BUNT_END_FRAME (ATTACK_BUNT_WHOLE_FRAME - 11)
//// その他
//#define ATTACK_BUNT_ANGLE 15.0f
//
////==========================
//// 吸収
////==========================
//// 当たり判定の大きさ
//#define ATTACK_ABSORB_SIZE_RATE 1.75f
//// 全体フレーム、攻撃終了フレーム
//#define ATTACK_ABSORB_WHOLE_FRAME 80
//#define ATTACK_ABSORB_END_FRAME (ATTACK_ABSORB_WHOLE_FRAME - 20)
//
////==========================
//// 必殺技
////==========================
//// 必殺技ゲージ上昇量（キャッチ時はさらに倍率が上がる）
//#define ATTACK_SP_GAUGE_BASE_GAIN 40.0f
//#define ATTACK_SP_GAUGE_ADD_BASE_GAIN_RATE 0.08f
//#define ATTACK_SP_GAUGE_EX_ADD_RATE 1.5f
//// 各必殺技の細かい値は、各関数内で定義してある

//================================================
// 前方宣言
//================================================
class CAi;
class CUI;
class CText;
class CNumberArray;
class CModelEffect;
class CBullet;

//================================================
// クラス宣言
//================================================

// プレイヤークラス
class CPlayer : public CCharacter
{
public:
    CPlayer();
    ~CPlayer();

    // アニメーションの種類
    typedef enum
    {
        ANIM_IDLE = 0,       // 待機
        ANIM_MOVE,           // 移動
        ANIM_JUMP,           // ジャンプ
        ANIM_LANDING,        // 着地
        ANIM_WARRIOR_GROUND1,// ウォーリアー地上1
        ANIM_HUNTER_GROUND,  // ハンター地上
        ANIM_CARRIER_SKY,    // キャリアー空中
        ANIM_WARRIOR_GROUND2,// ウォーリアー地上2
        ANIM_SIT_DOWN,       // 座る
        ANIM_HUNTER_SKY,     // ハンター空中
        ANIM_WARRIOR_SKY,    // ウォーリアー空中
        ANIM_GLIDE,          // 滑空
        ANIM_SECOND_JUMP,    // 2段ジャンプ
        ANIM_CARRIER_IDLE,   // キャリアー待機
        ANIM_DAMAGE_SMALL,   // のけぞり
        ANIM_DAMAGE_BIG,     // ダウン
        ANIM_STAND_UP,       // 起き上がり
        ANIM_CARRIER_DUSH,   // キャリアー走り
        ANIM_BLOWN,          // 吹き飛ばされ
        ANIM_CARRIER_GROUND, // キャリアー地上
        ANIM_CUSTOM_IDLE,    // カスタマイズ画面での待機
        ANIM_WEAPON_LOOK,    // カスタマイズ画面での武器を見る
        ANIM_TANK_GROUND1,   // タンク地上1
        ANIM_TANK_SKY,       // タンク空中
        ANIM_TANK_GROUND2,   // タンク地上2
        ANIM_HEALER_GROUND,  // ヒーラー地上
        ANIM_HEALER_SKY,     // ヒーラー空中
        ANIM_MAX,
    }ANIMATION;

    // モデルの各パーツ
    typedef enum
    {
        PARTS_HIP = 0,
        PARTS_BODY,
        PARTS_HEAD,
        PARTS_RSHOULDER,
        PARTS_RARM,
        PARTS_RHAND,
        PARTS_LSHOULDER,
        PARTS_LARM,
        PARTS_LHAND,
        PARTS_RTHIGH,
        PARTS_RLEG,
        PARTS_RFOOT,
        PARTS_LTHIGH,
        PARTS_LLEG,
        PARTS_LFOOT,
        PARTS_WEP,
        PARTS_MAX,
    }PARTS;

    // モデルのカスタマイズパーツ
    typedef enum
    {
        CUSTOM_PARTS_HEAD = 0,   // 頭
        CUSTOM_PARTS_UP,         // 上半身
        CUSTOM_PARTS_DOWN,       // 下半身
        CUSTOM_PARTS_WEP,        // 武器
        CUSTOM_PARTS_MAX         // カスタマイズパーツの最大数
    }CUSTOM_PARTS;

    // 攻撃状態
    typedef enum
    {
        ATTACK_STATE_NONE = 0,         // なし
        ATTACK_STATE_COMMON_STAND_UP,  // 共通起き上がり攻撃
        ATTACK_STATE_WARRIOR_GROUND1,  // ウォーリアー地上1
        ATTACK_STATE_WARRIOR_GROUND2,  // ウォーリアー地上2
        ATTACK_STATE_WARRIOR_SKY,      // ウォーリアー空中
        ATTACK_STATE_HUNTER_GROUND,    // ハンター地上
        ATTACK_STATE_HUNTER_SKY,       // ハンター空中
        ATTACK_STATE_CARRIER_GROUND1,  // キャリアー地上1
        ATTACK_STATE_CARRIER_GROUND2,  // キャリアー地上2
        ATTACK_STATE_CARRIER_SKY,      // キャリアー空中
        ATTACK_STATE_TANK_GROUND1,     // タンク地上1
        ATTACK_STATE_TANK_GROUND2,     // タンク地上2
        ATTACK_STATE_TANK_SKY,         // タンク空中
        ATTACK_STATE_HEALER_GROUND,    // ヒーラー地上
        ATTACK_STATE_HEALER_SKY,       // ヒーラー空中
        ATTACK_STATE_SIT_DOWN,         // 座る
    }ATTACK_STATE;

    typedef struct
    {
        bool bTiltedLeftStick;          // 左スティックが傾いたかどうか
        float fLeftStickAngle;          // 左スティック角度
        bool bTiltedRightStick;         // 右スティックが傾いたかどうか
        float fRightStickAngle;         // 右スティック角度
        float fPlayerAngle;             // プレイヤー角度
        bool bTriggerA;                 // Aボタントリガー
        bool bPressA;                   // Aボタンプレス
        bool bTriggerX;                 // Xボタントリガー
        bool bPressX;                   // Xボタンプレス
        bool bReleaseX;                 // Xボタンリリース
        bool bPressR2;                  // R2ボタンプレス
        bool bTriggerB;                 // Bボタントリガー
    }ControlInput;    // 入力制御

    // AI
    typedef enum
    {
        AI_LEVEL_NONE = 0,    // AIなし
        AI_LEVEL_1,           // よわい
        AI_LEVEL_2,           // ふつう
        AI_LEVEL_3            // つよい
    }AI_LEVEL;

    // ボイスセット
    typedef enum
    {
        VOICE_SET_ROBO = 0,   // ロボ
        VOICE_SET_WOMAN,      // 女性
        VOICE_SET_GHOST,      // ゴースト
        VOICE_SET_OOO,        // オーズ
        VOICE_SET_MAN,        // 男性
        VOICE_SET_BOY,        // 少年
    }VOICE_SET;

    // 特殊能力（アビリティ）のフラグ
    typedef enum
    {
        EX_FLAG_NONE = 0,                      // なし
        EX_FLAG_THREE_JUMP = 0x001 << 1,       // 三段ジャンプ
        EX_FLAG_FAST_CHARGE = 0x001 << 2,      // 溜め短縮
        EX_FLAG_DONT_CATCH = 0x001 << 3,       // キャッチ使用不可
        EX_FLAG_FIRST_HIT_GUARD = 0x001 << 4,  // ファーストヒットガード
        EX_FLAG_TRAIL_GREEN = 0x001 << 5,      // 武器軌跡色:緑
        EX_FLAG_TRAIL_PURPLE = 0x001 << 6,     // 武器軌跡色:紫
        EX_FLAG_SAVE_SP_GAUGE = 0x001 << 7,    // 必殺ゲージ保持
        EX_FLAG_ROUND_HEAL = 0x001 << 8,       // ラウンドリジェネ
    }EX_FLAG;

    // 必殺技（SPショット）の種類
    typedef enum
    {
        SP_SHOT_HEAL = 0,       // ヒール（回復）
        SP_SHOT_DECOY,          // ぶんしんボール
        SP_SHOT_WALL_THROUGH,   // ウォールスルー（壁ループ）
        SP_SHOT_BARRIER			// バリア
    }SP_SHOT;

    // 順位
    typedef enum
    {
        RANK_1 = 0,
        RANK_2,
        RANK_3,
        RANK_4
    }RANK;

    // 役割
    typedef enum
    {
        ROLE_WARRIOR = 0,// ウォーリアー
        ROLE_HUNTER,     // ハンター
        ROLE_CARRIER,    // キャリアー
        ROLE_TANK,       // タンク
        ROLE_HEALER,     // ヒーラー
        ROLE_MAX
    }ROLE;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void LoadCustom(void);                                                              // カスタマイズ読み込み
    void Uninit(void);                                                                  // 終了処理
    void Input(void);                                                                   // 入力処理
    void Update(void);                                                                  // 更新処理
    void UpdateMannequin(void);                                                         // マネキンモード更新処理
    void UpdateGameUI(void);                                                            // ゲームUIの更新処理
    void DeadMove(void);                                                                // やられた時の挙動
    void ResetOnGround(void);                                                           // 着地時にリセットする変数
    void ResetAttack(void);                                                             // 攻撃周りでリセットする変数
    void Respawn(void);                                                                 // リスポーン
    void Draw(void);                                                                    // 描画処理
    static CPlayer *CreateInGame(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxCreate, int nIdxControlAndColor,
        AI_LEVEL AIlevel, int role, bool bUseKeyboard = false);   // ゲーム内での生成処理
    static CPlayer *CreateInCustom(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxControlAndColor, bool bDisp); // カスタマイズ画面での生成
    static CPlayer *CreateInResult(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxControlAndColor, RANK rank);  // リザルト画面での生成    

    void Movement(float fSpeed);                                                        // 行動
    void MoveMotion(void);                                                              // 移動モーションの管理
    void Control(float fSpeed, D3DXVECTOR3& move);                                      // 制御
    void Jump(D3DXVECTOR3& move);                                                       // ジャンプ
    void DamageUpdate(D3DXVECTOR3 pos, D3DXVECTOR3& move);                              // 負傷更新処理
    void DamageMotion(void);                                                            // 負傷モーションの管理

    void ApplyMusk(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumTexture);					// クリッピングマスク適用 //池田追加
    void ApplyMusk(D3DXVECTOR3 pos, D3DXVECTOR3 size);									// テクスチャなしクリッピングマスク適用 //池田追加

    bool TakeDamage_TankUsingGuard(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, bool bUseKnockBack = true, int effectType = 20);

    /*========================================================
    // カスタマイズの文字列周り
    //======================================================*/
    static void CustomPartsName(char* pName, int nPartsType);
    void CustomExName(char* pName, int exFlag);
    void CustomSpName(char* pName);

    /*========================================================
    // セッター
    //======================================================*/
    void ResetStatusEveryRound(void);   // 毎ラウンドリセットするステータス
    void SetDispAbility(bool bDisp) { m_bDispAbility = bDisp; }
    void SetCustomWeaponLook(void) { if (m_nCntAttackAnimTime <= 0)m_nCntAttackAnimTime = PLAYER_WEAPON_LOOK_FRAME; }
    void SetRank(RANK rank) { m_rank = rank; }
    void GainEnergy(const float fEnergy);
    void GainContribution(const int nContribution) { m_nContributionPoint += nContribution; }

    /*========================================================
    // ゲッター
    //======================================================*/
    float GetAtk(void) { return m_fAtk; }
    float GetDef(void) { return m_fDef; }
    float GetSpd(void) { return m_fSpd; }
    float GetWei(void) { return m_fWei; }
    ControlInput *GetControlInput(void) { return &m_controlInput; }
    int GetIdxCreate(void) { return m_nIdxCreate; }
    int GetIdxControlAndColor(void) { return m_nIdxControlAndColor; }
    bool GetGround(void) { return m_bGround; }
    int GetPressJumpTime(void) { return m_nCntPressJump; }
    AI_LEVEL GetAILevel(void) { return m_AIlevel; }
    int GetCustomPartsNum(int nParts) { return m_anNumCustomParts[nParts]; }
    bool GetUseControllerEffect(void);       // コントローラの振動を使用するかどうか
    bool GetDispAbility(void) { return m_bDispAbility; }
    int GetRole(void) { return m_role; }
    bool GetUsingGuard(void) { return m_bUsingGuard; }
    ATTACK_STATE GetAttackState(void) { return m_attackState; }
    float GetCurrentEnergy(void) { return m_fCurrentEnergy; }
    float GetCurrentEnergyMax(void) { return m_fCurrentEnergyMax; }
    int GetContributionPoint(void) { return m_nContributionPoint; }

private:
    bool m_bMannequin;                       // マネキンかどうか
    ControlInput m_controlInput;             // 入力管理
    bool m_bUseKeyboard;                     // キーボードを使うかどうか
    AI_LEVEL m_AIlevel;                      // AIレベル
    CAi *m_pAI;                              // AIへのポインタ
    CUI *m_pUI_SP;                           // SPゲージへのポインタ
    CUI *m_pUI_Playable;                     // プレイヤー表示へのポインタ
    CNumberArray *m_pNumArray_SP;            // SPパーセントへのポインタ
    CUI *m_pUI_Custom_Atk;                   // カスタマイズ画面_攻撃ゲージ
    CUI *m_pUI_Custom_Def;                   // カスタマイズ画面_防御ゲージ
    CUI *m_pUI_Custom_Spd;                   // カスタマイズ画面_速さゲージ
    CUI *m_pUI_Custom_Wei;                   // カスタマイズ画面_重さゲージ
    CUI *m_pUI_Custom_Ability;               // カスタマイズ画面_アビリティ
    CText *m_pText_Custom_Ex_Head;           // カスタマイズ画面_特殊能力名_頭
    CText *m_pText_Custom_Ex_Up;             // カスタマイズ画面_特殊能力名_胴
    CText *m_pText_Custom_Ex_Down;           // カスタマイズ画面_特殊能力名_脚
    CText *m_pText_Custom_Ex_Wep;            // カスタマイズ画面_特殊能力名_武器
    CText *m_pText_Custom_Sp;                // カスタマイズ画面_必殺技名
    bool m_bDispAbility;                     // カスタマイズ画面で詳細を表示するかどうか

    int m_nIdxCreate;                        // 生成のインデックス
    int m_nIdxControlAndColor;               // コントロールとカラーのインデックス

    int m_exFlag;                            // 特殊能力フラグ
    bool m_bGround;                          // 地面にいるかどうか

    int m_nCntLandingTime;                   // 着地時間
    bool m_bGroundOld;                       // 1F前、地面にいたかどうか

    int m_anNumCustomParts[CUSTOM_PARTS_MAX];// カスタマイズパーツの番号
    float m_fAtk;                            // 攻撃
    float m_fDef;                            // 防御（最大HPにもなる）
    float m_fSpd;                            // 速さ
    float m_fWei;                            // 重さ
    float m_afParam[PARAM_DATA_MAX];         // 汎用データ
    int m_nModelPosDefUp;                    // モデルの初期位置データ（上半身）
    int m_nModelPosDefDown;                  // モデルの初期位置データ（下半身）

    int m_nCntPressJump;                     // ジャンプを押した時間
    bool m_bUsedSecondJump;                  // 二段ジャンプを使ったかどうか
    int m_nCntStartGlide;                    // 滑空が始まるまでのカウンタ

    bool m_abUseAvoidMultipleHits[CHARACTER_IDX_MAX]; // 多段ヒット回避を使うかどうか
    int m_nCntAttackAnimTime;                // 攻撃アニメーションの最低保証

    int m_spShot;                            // 必殺技

    CClipingMusk* m_pClipingMusk;			 // クリッピングマスク
    RANK m_rank;                             // 順位
    D3DXVECTOR3 m_hipPosOld;                 // 1F前の腰の位置

    int m_nCntCurrentEnergyMaxTime;          // 必殺ゲージMAX時間
    int m_voiceSet;                          // ボイスセット

    //===================================    
    // 特殊能力対応周り                      
    //===================================    

    //===================================    
    // Secondで追加したメンバ変数
    //===================================
    int m_role;                 // 役割
    ATTACK_STATE m_attackState; // 攻撃状態
    int m_nCntStopTime;         // 硬直時間のカウンタ
    int m_nCntAttackTime;       // 攻撃時間をカウント
    float m_fCurrentEnergy;     // 現在のエナジー量
    float m_fCurrentEnergyMax;  // エナジーの最大量
    int m_waitMotion;           // 待機モーション
    int m_walkMotion;           // 移動モーション
    bool m_bUsingGuard;         // ガードを使用中かどうか
    int m_nCntGuards;           // ガード回数
    CModelEffect *m_pLightGuard;// 光の盾モデル
    CBullet *m_pHealingCircle;  // 回復魔方陣
    int m_nCntRespawnTime;      // リスポーン時間を数える
    int m_nContributionPoint;   // 貢献度
    bool m_bGetOffFortressInThisFrame;  // ゴリ押し
    bool m_bBurstAttack;        // 連続攻撃
    CUI *m_pUI_Wait;                     // リスポーン待機表示へのポインタ
    CNumberArray *m_pNumArray_Wait;      // リスポーン待機カウントへのポインタ
    int m_nCntAFK;              // 放置のカウンタ
    bool m_bPlayerEntry;             // プレイヤーエントリーかどうか

    //===================================
    // このクラス内でのみ使う処理
    //===================================    
    void AttackUpdate(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);  // 攻撃更新処理
    void AttackGenerator(void);                 // 攻撃発生処理
    void AttackMotion(void);                    // 攻撃モーションの管理
    bool IsHitCloseRangeAttack(D3DXVECTOR3 playerPos, D3DXVECTOR3 attackPos, D3DXVECTOR2 attackSize, float fPower, int flag = 0, int hitEffect = DEFAULT_HIT_EFFECT_NUM);   // 攻撃の当たり判定
    void RideFortress(void);                    // 移動要塞に乗り込む処理
    void SendEnergyForFortress(void);   // 移動要塞にエナジーを送る処理

    //===================================    
    // 攻撃系
    //===================================
    void AtkSitDown(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);
    void AtkWarriorGround1(D3DXVECTOR3& playerPos);
    void AtkWarriorGround2(D3DXVECTOR3& playerPos);
    void AtkWarriorSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);
    void AtkHunterGround(D3DXVECTOR3& playerPos);
    void AtkHunterSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);
    void AtkCarrierGround1(D3DXVECTOR3& playerPos);
    void AtkCarrierGround2(D3DXVECTOR3& playerPos);
    void AtkCarrierSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);
    void AtkTankGround1(D3DXVECTOR3& playerPos);
    void AtkTankGround2(D3DXVECTOR3& playerPos);
    void AtkTankSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);
    void AtkHealerGround(D3DXVECTOR3& playerPos);
    void AtkHealerSky(D3DXVECTOR3& playerPos, D3DXVECTOR3& move);
};

#endif