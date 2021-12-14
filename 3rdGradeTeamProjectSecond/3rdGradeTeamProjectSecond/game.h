//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 後藤慎之助
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "mode.h"
#include "player.h"
#include "library.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPause;
class CUI;
class CEffect2D;
class CNumberArray;
class CText;
class CFortress;

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame : public CMode
{
public:

    // ゲームの種類
    typedef enum
    {
        TYPE_TRAINING = 0,     // トレーニング
        TYPE_ARENA,            // 闘技場
        TYPE_MINI,             // ミニゲーム
        TYPE_MAX			   // 状態の最大数
    }TYPE;

    // ゲームの状態（仮）
    typedef enum
    {
        STATE_ROUND_START = 0,     // 開始
        STATE_BUTTLE,              // バトル中
        STATE_BLOW_MOMENT,         // 一撃の瞬間
        STATE_FINISH,              // 決着
        STATE_PAUSE_MENU,	       // ポーズメニュー
        STATE_MAX			       // 状態の最大数
    }STATE;

    CGame();
    ~CGame();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);

    void ManageState(void);     // ゲーム状態の管理
    void RoundStart(void);      // ラウンド開始
    void InButtle(void);        // バトル中
    void BlowMoment(void);      // 一撃の瞬間
    void BlowMomentMakeSureReset(void);   // 一撃の瞬間時、念のためリセットするもの
    void JudgmentFinish(void);  // 勝敗判定

    /*========================================================
    // セッター
    //======================================================*/
    static void SetNextGameInDebug(TYPE gameType, int nNumPlayer, bool bUseKeyboard = false)
    {
        m_type = gameType;  m_nNumAllPlayer = nNumPlayer; m_bUseKeyboard = bUseKeyboard;
    }   // デバッグメニューで、次のゲームを設定
    static void SetNextGameInCustom(TYPE gameType, int nNumPlayer)
    {
        m_type = gameType;  m_nNumAllPlayer = nNumPlayer;
    }   // カスタマイズ画面で、次のゲームを設定
    static void SetIdxPlayer(int nNum, int nIdxPlayer) { m_anMemoryIdxPlayer[nNum] = nIdxPlayer; }  // プレイヤーのインデックス
    static void SetAILevel(int nNum, CPlayer::AI_LEVEL level) { m_aMemoryAILevel[nNum] = level; }   // AIレベル
    static void SetRole(int nNum, int role) { m_anMemoryRole[nNum] = role; }   // 役割
    static void SetQuitPause(void) { m_state = STATE_BUTTLE; m_bStopObjUpdate = false; }    // ポーズ状態をやめる
    static void SetUseKeyboard(bool bUseKeyboard) { m_bUseKeyboard = bUseKeyboard; }
    static void SetSpPlayer(CPlayer *pPlayer) { m_bCurrentSpShot = true; m_pSpPlayer = pPlayer; }
    static void SetCurrentSpShot(bool bStopUpdate) { m_bCurrentSpShot = bStopUpdate; }

    /*========================================================
    // ゲッター
    //======================================================*/
    static STATE GetState(void) { return m_state; }                                 // ゲームの状態を取得
    static CPlayer* GetPlayer(const int nNum) { return m_apPlayer[nNum]; }          // プレイヤーを取得
    static int GetNumAllPlayer(void) { return m_nNumAllPlayer; }                    // 全体プレイヤー人数を取得
    static TYPE GetType(void) { return m_type; }                                    // ゲーム種類を取得
    static bool GetStopObjUpdate(void) { return m_bStopObjUpdate; }                 // オブジェクトのアップデートを止めるかどうか
    static CEffect2D* GetNega(void) { return m_pEffect2d_Nega; }                    // 反転合成のエフェクトを取得
    static CEffect2D* GetPosi(void) { return m_pEffect2d_Posi; }                    // 反転合成を戻すためのエフェクトを取得
    static bool GetUseKeyboard(void) { return m_bUseKeyboard; }                     // キーボードを使うかどうか取得
    static CPlayer*GetSpPlayer(void) { return m_pSpPlayer; }
    static bool GetCurrentSpShot(void) { return m_bCurrentSpShot; }
    static CText *GetSpText(void) { return m_pSpText; }
    static CFortress *GetFortress(void) { return m_pFortress; }

    /*========================================================
    // 便利な関数
    //======================================================*/
    static float GetAngleToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer = NOT_EXIST);    // 一番近いプレイヤーへの角度を求める
    static D3DXVECTOR3 GetPosToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer = NOT_EXIST);// 一番近いプレイヤーの位置を求める
    static CCharacter *GetDistanceAndPointerToClosestPlayer(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer = NOT_EXIST);
    static CPlayer *GetDistanceAndPointerToClosestPlayer_Player(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer = NOT_EXIST);
    static CCharacter *GetDistanceAndPointerToClosestPlayerOrFortress(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer = NOT_EXIST);
    static CCharacter *GetDistanceAndPointerToClosestFortress(D3DXVECTOR3 myPos, float &fKeepDistance);
    static void SetBallGauge(int nMax, int nNow);                                   // ボール発射ゲージ
    static int GetCharacterIdx(void) 
    { 
        m_nCharacterIdx++;
        if (m_nCharacterIdx >= CHARACTER_IDX_MAX)
        {
            m_nCharacterIdx = CHARACTER_IDX_MIN_IN_RESET;
        }
        return m_nCharacterIdx;
    }
    static HIT_SURFACE MapLimit(D3DXVECTOR3 &pos, D3DXVECTOR3 posOld, D3DXVECTOR3 myCubeSize); // マップ制限
    static D3DXVECTOR3 GetPosToClosestEnemy(D3DXVECTOR3 myPos);// 一番近い敵の位置を求める

private:

    static bool m_bStopObjUpdate;                          // オブジェクトのアップデートを止めるかどうか
    static CPlayer *m_apPlayer[MAX_PLAYER];                // プレイヤーのポインタ
    static CPause *m_pPause;                               // ポーズのポインタ
    static CEffect2D *m_pEffect2d_Nega;                    // 反転合成へのポインタ
    static CEffect2D *m_pEffect2d_Posi;                    // 反転合成を戻すためのポインタ

    static TYPE m_type;                                    // ゲーム種類
    static int m_nNumAllPlayer;                            // 全体プレイヤー人数
    static bool m_bUseKeyboard;                            // キーボードを使うかどうか
    static int m_anMemoryIdxPlayer[MAX_PLAYER];            // プレイヤーのインデックスを記憶
    static CPlayer::AI_LEVEL m_aMemoryAILevel[MAX_PLAYER]; // AIレベルを記憶
    static int m_anMemoryRole[MAX_PLAYER];                 // 役割を記憶
    static STATE m_state;                                  // 状態

    static CPlayer *m_pSpPlayer;                           // ストライクシュートプレイヤーのポインタ
    static bool m_bCurrentSpShot;                          // 現在ストライクシュートを撃っているかどうか
    static CText *m_pSpText;                               // ストライクシュートの名前

    int m_nCntGameTime;                                    // ゲーム時間のカウンタ
    bool m_bFirestRound;                                   // 最初のラウンドかどうか

    static CFortress *m_pFortress;                         // 移動要塞のポインタ
    static int m_nCharacterIdx;                            // キャラクターのインデックス
};

#endif