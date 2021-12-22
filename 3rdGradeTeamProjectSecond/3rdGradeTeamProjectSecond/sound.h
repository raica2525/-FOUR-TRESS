//====================================================================
//
// サウンド処理 (sound.h)
// Author : 池田悠希
//
//====================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//================================================
// クラス宣言
//================================================

// サウンドのクラス
class CSound
{
public:
    typedef enum
    {
        // SE
        LABEL_SE_SWISH = 0,     // 素振り音
        LABEL_SE_KO,            // KO音
        LABEL_SE_DAMAGE,        // ダメージ音
        LABEL_SE_OFFSET,        // 相殺音
        LABEL_SE_JUMP,          // ジャンプ音
        LABEL_SE_SELECT,		// 決定音
        LABEL_SE_CUSTOM,		// カスタマイズ変更音
        LABEL_SE_CANCEL,		// キャンセル音
        LABEL_SE_ENTRY,			// エントリー音
        LABEL_SE_READY,			// READYボタン出現音
        LABEL_SE_HEAL,			// 回復音
        LABEL_SE_INFO,			// 詳細が出る時の音
        LABEL_SE_CURSOLON,		// ボタンにカーソルが乗った時の音
        LABEL_BGM_TITLE,		// タイトルBGM
        LABEL_BGM_MENU,			// メニュー&カスタマイズBGM
        LABEL_BGM_BATTLE00,		// バトルBGM00
        LABEL_BGM_BATTLE01,		// バトルBGM01
        LABEL_BGM_BATTLE02,		// バトルBGM02
        LABEL_SE_OK,
        LABEL_BGM_RESULT,		// リザルトBGM
        LABEL_SE_FINISH,		// フィニッシュSE
        LABEL_SE_BOW_SOUND_EFFECT, // 弓効果音by.マサラ
        LABEL_SE_ELECTROMAGNETIC_CANNON_Lv1, // 電磁砲Lv1by.マサラ
        LABEL_SE_ELECTROMAGNETIC_CANNON_Lv2, // 電磁砲Lv2by.マサラ
        LABEL_SE_CHARGE_ELECTROMAGNETIC_CANNON, // 電磁砲チャージby.マサラ
        LABEL_SE_OPEN_POSE, // ポーズを開くby.マサラ
        LABEL_SE_CLAUSE_POSE, // ポーズを閉じるby.マサラ
        LABEL_SE_GET_ITEM, // アイテム取得by.マサラ
        LABEL_SE_SHIELD, // シールドby.マサラ
        LABEL_SE_JUMP_ATTACK_SWORD, // ジャンプ技(剣)by.マサラ
        LABEL_SE_JUMP_ATTACK_BOW, // ジャンプ技(弓)by.マサラ
        LABEL_SE_JUMP_ATTACK_NAIL, // ジャンプ技(爪)by.マサラ
        LABEL_SE_JUMP_ATTACK_SHIELD, // ジャンプ技(盾)by.マサラ
        LABEL_SE_JUMP_ATTACK_HEALER, // ジャンプ技(回復)by.マサラ
        LABEL_SE_HIGH_SPEED_MOVE, // 高速移動by.マサラ
        LABEL_SE_ATTACK_NAIL, // 爪攻撃by.マサラ
        LABEL_SE_EXPLOSION_KAMIKAZE, // カミカゼ爆発by.マサラ
        LABEL_SE_ATTACK_COMMANDER, // コマンダー攻撃by.マサラ
        LABEL_MAX,
    } LABEL;

    typedef enum
    {
        CATEGORY_SE = 0,
        CATEGORY_BGM,
        CATEGORY_MAX
    } CATEGORY;

    CSound();
    ~CSound();
    HRESULT Init(HWND hWnd);
    void Uninit(void);
    HRESULT Play(LABEL label, float fPitch = 1.0f);
    void Stop(LABEL label);
    void StopAll(void);
    void SetVolume(LABEL label, int nVolume);				// 音量設定用関数
    void SetCategoryVolume(CATEGORY category, int nVolume); // カテゴリごとの音量設定用関数
private:
    typedef struct
    {
        char *pFilename;	// ファイル名
        int nCntLoop;		// ループカウント (-1でループ、0でループなし)
        CATEGORY category;	// 種類分け
    }PARAM;
    HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

    IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
    IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
    IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// ソースボイス
    BYTE *m_apDataAudio[LABEL_MAX];					    // オーディオデータ
    DWORD m_aSizeAudio[LABEL_MAX];					    // オーディオデータサイズ
    static PARAM m_aParam[LABEL_MAX];                   // 各音素材のパラメータ
    int m_anVolume[CATEGORY_MAX];						// 各種別の音量
};

#endif