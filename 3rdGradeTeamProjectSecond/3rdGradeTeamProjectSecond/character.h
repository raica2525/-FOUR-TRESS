//==========================================================================================
//
// キャラクターの処理 (character.h)
// Author : 後藤慎之助
//
//==========================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene.h"
#include "model.h"
#include "ui.h"

//================================================
// マクロ定義
//================================================
#define CHARCTER_PARTS_MAX 18    // キャラクターのパーツの最大数

#define TAKE_DAMAGE_BORDER_DAMAGE 500.0f             // 小やられか大やられの境目ダメージ
#define TAKE_DAMAGE_SMALL_FRAME 30                   // 負傷小フレーム数
#define TAKE_DAMAGE_BIG_FRAME 180                    // 負傷大フレーム数
#define TAKE_DAMAGE_LUCKY_GUARD_FRAME 40             // 負傷ラッキーガードフレーム数
#define KNOCK_BACK_SMALL 10.0f                       // ノックバック量（負傷小）
#define KNOCK_BACK_BIG 22.5f                         // ノックバック量（負傷大）
#define KNOCK_BACK_LUCKY_GUARD 25.0f                 // ノックバック量（ラッキーガード）
#define KNOCK_BACK_DEATH_X 25.0f                     // ノックバック量（死亡時X）
#define KNOCK_BACK_DEATH_Y 12.5f                     // ノックバック量（死亡時Y）
#define KNOCK_BACK_STOP_BORDER 7.5f                  // ノックバックが止まったとみなす境界値

//================================================
// 前方宣言 
//================================================
class CModel;
class CAnimation;
class CEffect3D;
class CUI;

//================================================
// クラス宣言
//================================================

// キャラクタークラス
class CCharacter : public CScene
{
public:

    // 負傷状態
    typedef enum
    {
        DAMAGE_STATE_NONE = 0,      // なし
        DAMAGE_STATE_SMALL,         // のけぞり
        DAMAGE_STATE_BIG,           // ダウン
        DAMAGE_STATE_STAND_UP,      // 起き上がり
        DAMAGE_STATE_BLOWN,         // 吹っ飛ばされ
        DAMAGE_STATE_MAX,
    }DAMAGE_STATE;

    // HP表示の種類
    typedef enum
    {
        HP_DISP_NONE = -1,      // 表示なし
        HP_DISP_PLAYER_1,       // プレイヤー1
        HP_DISP_PLAYER_2,       // プレイヤー2
        HP_DISP_PLAYER_3,       // プレイヤー3
        HP_DISP_PLAYER_4,       // プレイヤー4
        HP_DISP_FOLLOW,         // 追従
    }HP_DISP;

    CCharacter(OBJTYPE objType);
    ~CCharacter();

    virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void CreateHPGauge(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    void DeathDraw(void);                                         // やられた時の描画
    void LoadModelData(char* cFilePass);                          // テキストファイルから直接読み込む時に使う関数
    void LoadModelData(int nModelPosDefUp, int nModelPosDefDown); // モデルの初期位置データから読み込むときに使う関数
    void RotControl(void);                                        // 向きを調整
    bool TakeDamage(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, int effectType = 20);   // ダメージを受ける
    void CntDownTakeDamageTime(void);                             // ダメージを受けた時間をカウント
    void ControlMove(float& fMove, bool bGround = true);          // 移動量制御

    /*========================================================
    // セッター
    //======================================================*/
    void SetPartPos(int index, D3DXVECTOR3 pos) { m_apModel[index]->SetPos(pos); }
    void SetPartRot(int index, D3DXVECTOR3 rot) { m_apModel[index]->SetRot(rot); }
    void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
    void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
    void SetRotY(const float fRotY) { m_rot.y = fRotY; }
    void SetPartNum(int nPartNum) { m_nPartsNum = nPartNum; }                       // パーツの最大数を設定
    void SetPosOld(const D3DXVECTOR3 posOld) { m_posOld = posOld; }
    void SetAnimFilePass(char* cFilePass) { m_cAnimFilePass = cFilePass; }
    void SetRotDest(const D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
    void SetRotDestY(const float fRotDestY) { m_rotDest.y = fRotDestY; }
    void SetCollisionSizeDefence(const D3DXVECTOR2 collisionSizeDeffence = D3DXVECTOR2(0.0f, 0.0f)) { m_collisionSizeDefence = collisionSizeDeffence; }
    void SetLife(float fLife) { m_fLife = fLife;}
    void SetUpLife(float fLife) { m_fLife = fLife; m_fLife_red = fLife; m_fMaxLife = fLife; }
    void SetHPDisp(int hpDisp) { m_HPDisp = hpDisp; }
    void SetUIHPDisp(bool bDisp)
    {
        if (m_pUI_HP_bg && m_pUI_HP_red && m_pUI_HP)
        {
            m_pUI_HP_bg->SetDisp(bDisp);
            m_pUI_HP_red->SetDisp(bDisp);
            m_pUI_HP->SetDisp(bDisp);
        }
    }
    void SetInvincible(bool bInvincible) { m_bIsInvincible = bInvincible; }
    void SetUseControllerEffectByTakeDamage(bool bUse) { m_bUseControllerEffectByTakeDamage = bUse; }
    void SetMove(D3DXVECTOR3 move) { m_move = move; }
    void SetTakeDamageTime(int nTime) { m_nCntTakeDamageTime = nTime; }
    void SetDamageState(DAMAGE_STATE damageState) { m_damageState = damageState; }
    void SetResetAttack(bool bReset) { m_bIsAttackReset = bReset; }
    void SetMoveOld(D3DXVECTOR3 moveOld) { m_moveOld = moveOld; }
    void SetUseKnockBack(bool bUse) { m_bUseKnockBack = bUse; }

    void BindParts(int nPartsIndex, int nPartsType) { m_aPartsType[nPartsIndex] = nPartsType; }

    /*========================================================
    // ゲッター
    //======================================================*/
    D3DXVECTOR3 GetDefaultPos(int index) { return m_aPosDefault[index]; }
    D3DXVECTOR3 GetPartsPos(int index) { return D3DXVECTOR3(m_apModel[index]->GetWorldMtx()._41, m_apModel[index]->GetWorldMtx()._42, m_apModel[index]->GetWorldMtx()._43); }
    D3DXVECTOR3 GetPartsRot(int index) { return m_apModel[index]->GetRot(); }
    CModel * GetParts(int index) { return m_apModel[index]; }
    D3DXVECTOR3 GetPos(void) { return m_pos; }
    D3DXVECTOR3 GetRot(void) { return m_rot; }
    CAnimation * GetAnimation(void) { return m_pAnimation; }
    D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
    D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }
    D3DXVECTOR2 GetCollisionSizeDefence(void) { return m_collisionSizeDefence; }
    float GetLife(void) { return m_fLife; }
    bool GetInvincible(void) { return m_bIsInvincible; }
    bool GetIsPlayer(void)
    {
        if (m_HPDisp == HP_DISP_PLAYER_1 || m_HPDisp == HP_DISP_PLAYER_2 ||
            m_HPDisp == HP_DISP_PLAYER_3 || m_HPDisp == HP_DISP_PLAYER_4)
        {
            return true;
        }
        return false;
    }
    DAMAGE_STATE GetDamageState(void) { return m_damageState; }
    D3DXVECTOR3 GetMove(void) { return m_move; }
    bool GetResetAttack(void) { return m_bIsAttackReset; }
    D3DXVECTOR3 GetMoveOld(void) { return m_moveOld; }
    int GetTakeDamageTime(void) { return m_nCntTakeDamageTime; }

    // アニメーションを使用しない場合のセッター
    void SetDontUseAnimation(void) { m_bUseAnimation = false; }

private:
    int                     m_aPartsType[CHARCTER_PARTS_MAX];           // パーツタイプ
    D3DXVECTOR3				m_aPosDefault[CHARCTER_PARTS_MAX];          // 初期位置
    int						m_anIndexParent[CHARCTER_PARTS_MAX];        // 親設定

    D3DXVECTOR3		m_pos;                                              // 全ての親の位置
    D3DXVECTOR3		m_rot;                                              // 全ての親の向き
    int				m_nPartsNum;                                        // パーツ数

    CModel			*m_apModel[CHARCTER_PARTS_MAX];                     // モデルへのポインタ
    CAnimation		*m_pAnimation;                                      // アニメーションへのポインタ

    D3DXVECTOR3		m_posOld;                                           // 1F前の位置

    char* m_cAnimFilePass;                                              // アニメーションファイルのパス

    bool m_bUseAnimation;												// アニメーションさせるかどうか
    D3DXVECTOR3 m_rotDest;                                              // 向き(目的値)
    CEffect3D *m_pEffect3d_Shadow;                                      // 影へのポインタ
    D3DXVECTOR2 m_collisionSizeDefence;                                 // 防御衝突サイズ（円柱）

    float m_fLife;                                                      // 体力
    float m_fLife_red;                                                  // 赤体力
    float m_fMaxLife;                                                   // 最大体力
    int m_nCntStopRedLifeTime;                                          // 赤ゲージ停止時間のカウンタ
    CUI *m_pUI_HP;                                                      // HPゲージへのポインタ
    CUI *m_pUI_HP_red;                                                  // 赤HPゲージへのポインタ
    CUI *m_pUI_HP_bg;                                                   // HPゲージ背景へのポインタ
    int m_HPDisp;                                                       // HP表示方法

    //==============================
    // 移動周り
    //==============================
    D3DXVECTOR3 m_move;                      // 移動量
    D3DXVECTOR3 m_moveOld;                   // 1F前の移動量
    bool m_bUseControllerEffectByTakeDamage; // コントローラーの振動を、ダメージを受けた時に使うか

    //==============================
    // 攻撃周り
    //==============================
    bool m_bIsAttackReset;                   // 攻撃をリセットするかどうか

    //==============================
    // 防御周り
    //==============================
    bool m_bIsInvincible;                    // 無敵かどうか
    int m_nCntTakeDamageTime;                // 攻撃を受けている時間
    DAMAGE_STATE m_damageState;              // 負傷状態
    bool m_bUseWhiteDraw;                    // 白描画を使用するかどうか
    int m_nCntWhiteDrawTime;                 // 白描画をするフレーム数
    bool m_bUseKnockBack;                    // ノックバックを使用するかどうか
};

#endif