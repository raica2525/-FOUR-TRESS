//====================================================================
//
// ランキング2処理 (ranking2.h)
// Author : 後藤慎之助
//
//====================================================================
#ifndef _RANKING2_H_
#define _RANKING2_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene.h"

//================================================
// 前方宣言(不完全なクラスは、cppの方でヘッダを呼び出す)
//================================================
class CNumber;

//================================================
// マクロ定義
//================================================
#define RANKING2_FIRST_POS D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 665.0f, 0.0f)   // ランキング2の最初の位置
#define RANKING2_CREATE_SCORE_SIZE D3DXVECTOR3(200.0f, 40.0f, 0.0f)   // ランキング2の一つの大きさ
#define MAX_RANKING2_NUMBER 48                                                   // ランキング2の数字の最大数(自分のスコアと、8桁*5位まで)

#define RANKING2_SCORE_MAX (6)   //5位まで(内部で6つの値を計算するため6)

//================================================
// クラス宣言
//================================================

// ランキング2のクラス
class CRanking2 : public CScene
{
public:
    CRanking2();
    ~CRanking2();
    static CRanking2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void ReleaseNumber(int nCntNumber);   // 数字情報開放
    void Update(void);
    void Draw(void);

    void SetNumber(int nPlayScore, int nStartIndex);    // スコアをナンバーに渡して表示する関数
    void ReadScore(void);                               // 外部ファイルからスコアを読み込む
    bool RankIn(int nScore);                            // ランクインしたかどうか

    void FadeInNumber(int nCnt);                        // フェードインする数字
    int SwapScoreNumberIndex(int nIndex);               // スコアの数字のインデックスを入れ替える

private:
    static CNumber *m_apNumber[MAX_RANKING2_NUMBER];  // 数字情報
    int m_nCntTime;                                  // 時間を数える
    int m_aRankingScore[RANKING2_SCORE_MAX];		     // 比較するスコア
    int m_aRank[RANKING2_SCORE_MAX];                  // ランク付けするため
    float m_aAlpha[MAX_RANKING2_NUMBER];              // 各数字のα値
};

#endif