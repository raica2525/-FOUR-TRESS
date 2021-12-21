//===============================================
//
// ランキング2の処理 (ranking2.cpp)
// Author : 後藤慎之助
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// インクルードファイル
//========================
#include "ranking2.h"
#include "number.h"
#include "manager.h"
#include <stdio.h>
#include "game.h"

//========================================
// マクロ定義
//========================================
// 移植用
#define MAX_SCORE 8

#define MAX_RANKING2 5                                                       // 順位の最大数
#define YOUR_SCORE_SIZE_X 200.0f
#define YOUR_SCORE_SIZE D3DXVECTOR3(YOUR_SCORE_SIZE_X / MAX_SCORE, 40.0f, 0.0f)         // あなたのスコアの数字の大きさ
#define RANKING2_SCORE_SIZE_X 350.0f
#define RANKING2_SCORE_SIZE  D3DXVECTOR3(RANKING2_SCORE_SIZE_X / MAX_SCORE, 70.0f, 0.0f)  // ランキング2のスコアの数字の大きさ

#define DOWN_POS_Y 100.0f                                    // 下にずらす値
#define SLIDE D3DXVECTOR3(0.0f, -480.0f, 0.0f)              // 自分のスコアからずらす値

#define RANKIN_COLOR D3DXCOLOR(1.0f , 0.0f, 0.0f, 1.0f)     // ランクインしたときの色

// 各順位の、フェードイン
#define FADE_IN_5 60
#define FADE_IN_4 150
#define FADE_IN_3 255
#define FADE_IN_2 375
#define FADE_IN_1 495
#define STOP 1000               // カウンタのストップ
#define FADE_IN_START_NUMBER 8  // 自分のスコアの次の数字からフェードイン開始
#define FADE_IN_RATE 0.05f      // フェードイン割合

// 各数字の、フェードイン時のディレイ
#define DELAY_ALPHA 0.5f

//========================================
// 静的メンバ変数宣言
//========================================
CNumber *CRanking2::m_apNumber[MAX_RANKING2_NUMBER] = {};

//========================================
// ランキング2のコンストラクタ
//========================================
CRanking2::CRanking2() :CScene(OBJTYPE::OBJTYPE_UI_BACK_TEXT)
{
    m_nCntTime = 0;

    // 配列の初期化
    memset(m_aRankingScore, 0, sizeof(m_aRankingScore));
    memset(m_aRank, 0, sizeof(m_aRank));
    memset(m_aAlpha, 0, sizeof(m_aAlpha));
}

//========================================
// ランキング2のデストラクタ
//========================================
CRanking2::~CRanking2()
{

}

//========================================
// ランキング2の生成
//========================================
CRanking2* CRanking2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CRanking2 *pRanking = NULL;

    // メモリを確保
    // コンストラクタで各情報を紐づけ
    pRanking = new CRanking2;

    // 初期化
    pRanking->Init(pos, size);

    return pRanking;
}

//========================================
// ランキング2の初期化処理
//========================================
HRESULT CRanking2::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 自分のスコア
    // 大きい位から、それぞれCreate
    m_apNumber[0] = CNumber::Create(12,D3DXVECTOR3(pos.x - YOUR_SCORE_SIZE_X * (MAX_SCORE - 1) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[0] = 1.0f;

    m_apNumber[1] = CNumber::Create(12, D3DXVECTOR3(pos.x - YOUR_SCORE_SIZE_X * (MAX_SCORE - 3) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[1] = 1.0f;

    m_apNumber[2] = CNumber::Create(12, D3DXVECTOR3(pos.x - YOUR_SCORE_SIZE_X * (MAX_SCORE - 5) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[2] = 1.0f;

    m_apNumber[3] = CNumber::Create(12, D3DXVECTOR3(pos.x - YOUR_SCORE_SIZE_X * (MAX_SCORE - 7) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[3] = 1.0f;

    m_apNumber[4] = CNumber::Create(12, D3DXVECTOR3(pos.x + YOUR_SCORE_SIZE_X * (MAX_SCORE - 7) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[4] = 1.0f;

    m_apNumber[5] = CNumber::Create(12, D3DXVECTOR3(pos.x + YOUR_SCORE_SIZE_X * (MAX_SCORE - 5) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[5] = 1.0f;

    m_apNumber[6] = CNumber::Create(12, D3DXVECTOR3(pos.x + YOUR_SCORE_SIZE_X * (MAX_SCORE - 3) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[6] = 1.0f;

    m_apNumber[7] = CNumber::Create(12, D3DXVECTOR3(pos.x + YOUR_SCORE_SIZE_X * (MAX_SCORE - 1) / MAX_SCORE / 2, pos.y, 0.0f),
        YOUR_SCORE_SIZE, DEFAULT_COLOR, false);
    m_aAlpha[7] = 1.0f;

    // 自分のスコアを表示
    SetNumber(CGame::GetScore(), 0);

    // ランキング2取得
    ReadScore();

    // 変数宣言
    int nIndex = 8;             // m_apNumberのインデックス
    float fPosDownY = 0.0f;     // どれだけランキング2を下にずらすか
    bool bOnlyOnce = false;     // 色を変えるのは一回のみ(同じ点数でどちらも色が変わるのを回避)
    for (int nCnt = 0; nCnt < MAX_RANKING2; nCnt++)
    {
        // 変数宣言
        D3DXCOLOR color = DEFAULT_COLOR;    // 数字の色
        bool bRankIn = false;               // ランクインしたかどうか

                                            // ランクインしたかどうかを、各順位のスコアを送ることで取得
        bRankIn = RankIn(m_aRankingScore[nCnt]);

        // ランクインしたなら、色を変える
        if (bRankIn == true && bOnlyOnce == false)
        {
            // ランクインの色
            color = RANKIN_COLOR;

            // 一回のみのフラグをtrueに
            bOnlyOnce = true;
        }

        // 大きい位から、それぞれCreate
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x - RANKING2_SCORE_SIZE_X * (MAX_SCORE - 1) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x - RANKING2_SCORE_SIZE_X * (MAX_SCORE - 3) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x - RANKING2_SCORE_SIZE_X * (MAX_SCORE - 5) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x - RANKING2_SCORE_SIZE_X * (MAX_SCORE - 7) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x + RANKING2_SCORE_SIZE_X * (MAX_SCORE - 7) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x + RANKING2_SCORE_SIZE_X * (MAX_SCORE - 5) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x + RANKING2_SCORE_SIZE_X * (MAX_SCORE - 3) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;
        m_apNumber[nIndex] = CNumber::Create(12, D3DXVECTOR3(pos.x + RANKING2_SCORE_SIZE_X * (MAX_SCORE - 1) / MAX_SCORE / 2,
            pos.y + fPosDownY, 0.0f) + SLIDE,
            RANKING2_SCORE_SIZE, color, false);
        nIndex++;

        // 下にずらす値を加算
        fPosDownY += DOWN_POS_Y;

        // 番号を設定
        SetNumber(m_aRankingScore[nCnt], nIndex - MAX_SCORE);
    }

    return S_OK;
}

//========================================
// ランキング2の終了処理
//========================================
void CRanking2::Uninit(void)
{
    // ランキング2の数字の数分回す
    for (int nCntNumber = 0; nCntNumber < MAX_RANKING2_NUMBER; nCntNumber++)
    {
        // 中身があるなら
        if (m_apNumber[nCntNumber] != NULL)
        {
            // 数字情報の終了処理
            m_apNumber[nCntNumber]->Uninit();

            // 数字情報のメモリの開放
            ReleaseNumber(nCntNumber);
        }
    }

    // オブジェクトの破棄
    Release();
}

//========================================
// ランキング2クラスが持っている、数字の開放処理
//========================================
void CRanking2::ReleaseNumber(int nCntNumber)
{
    // メモリの開放
    delete m_apNumber[nCntNumber];
    m_apNumber[nCntNumber] = NULL;
}

//========================================
// ランキング2の更新処理
//========================================
void CRanking2::Update(void)
{
    // カウンタ加算
    m_nCntTime++;

    // カウンタストップ
    if (m_nCntTime > STOP)
    {
        m_nCntTime = STOP;
    }

    // 各数字の更新処理
    for (int nCntNumber = 0; nCntNumber < MAX_RANKING2_NUMBER; nCntNumber++)
    {
        // 変数宣言
        bool bUse = true;   // 使用中

                            // 中身があるなら
        if (m_apNumber[nCntNumber] != NULL)
        {
            // 各数字の更新処理
            bUse = m_apNumber[nCntNumber]->Update();

            // 数字のフェードイン処理
            FadeInNumber(nCntNumber);

            // 数字のα値更新
            m_apNumber[nCntNumber]->SetAlpha(m_aAlpha[nCntNumber]);

            // 未使用になったら
            if (bUse == false)
            {
                // 数字情報のメモリの開放
                ReleaseNumber(nCntNumber);
            }
        }
    }
}

//========================================
// ランキング2の描画処理
//========================================
void CRanking2::Draw(void)
{
    // ランキング2の数字の数分回す
    for (int nCntNumber = 0; nCntNumber < MAX_RANKING2_NUMBER; nCntNumber++)
    {
        // 中身があるなら
        if (m_apNumber[nCntNumber] != NULL)
        {
            m_apNumber[nCntNumber]->Draw();
        }
    }
}

//========================================
// 数字設定処理
//========================================
void CRanking2::SetNumber(int nPlayScore, int nStartIndex)
{
    // 変数宣言
    int nIndex;		        // 指数　(スコア表示用)
    int nRadix = 10;	    // 基数　(スコア表示用)

                            // 各桁について計算
    for (nIndex = 0; nIndex < MAX_SCORE; nIndex++)
    {
        int nScore = (int)powf((float)nRadix, MAX_SCORE - (float)nIndex);
        int nScore2 = (int)powf((float)nRadix, MAX_SCORE - (float)nIndex - 1);

        // 
        int nAnswer = nPlayScore % nScore / nScore2;

        // 番号を設定
        m_apNumber[nStartIndex]->SetNumber(nAnswer);

        // 受け取ったインデックスを進める
        nStartIndex++;
    }
}

//==============================================================
// 各ランキング2のスコアの読み込み
//==============================================================
void CRanking2::ReadScore(void)
{
    FILE *pFile = NULL; //ファイルポインタ

    //======================
    // スコア読み込み用
    //======================
    pFile = fopen("data/TXT/score.txt", "r");

    // ランキング2をファイルから取得
    if (pFile != NULL)
    {//ファイルオープン成功
        for (int nCntScore = 0; nCntScore < RANKING2_SCORE_MAX; nCntScore++)
        {
            fscanf(pFile, "%d", &m_aRankingScore[nCntScore]);
        }
        fclose(pFile);
    }

    // プレイスコアを記憶
    m_aRankingScore[RANKING2_SCORE_MAX - 1] = CGame::GetScore();

    //ランクソート
    for (int nCntScore = 0; nCntScore < RANKING2_SCORE_MAX; nCntScore++)
    {
        m_aRank[nCntScore] = 0;
        for (int nData = 0; nData < RANKING2_SCORE_MAX; nData++)
        {
            if (m_aRankingScore[nCntScore] < m_aRankingScore[nData])
            {
                m_aRank[nCntScore]++;
            }
        }
    }

    //======================
    // スコア入力用
    //======================
    pFile = fopen("data/TXT/score.txt", "w");

    //スコア入力処理
    if (pFile != NULL)
    {//ファイルオープン成功
        for (int nCntRank = 0; nCntRank < RANKING2_SCORE_MAX; nCntRank++)
        {
            for (int nCntScore = 0; nCntScore < RANKING2_SCORE_MAX; nCntScore++)
            {
                if (m_aRank[nCntScore] == nCntRank)
                {
                    fprintf(pFile, "%d\n", m_aRankingScore[nCntScore]);
                }
            }
        }
        fclose(pFile);
    }

    //======================
    // スコア読み込み用
    //======================
    pFile = fopen("data/TXT/score.txt", "r");

    //スコア出力処理
    if (pFile != NULL)
    {//ファイルオープン成功
        for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
        { //上位スコアの出力処理
            fscanf(pFile, "%d", &m_aRankingScore[nCntScore]);
        }
        fclose(pFile);
    }
}

//==============================================================
// ランクインしたかどうか
//==============================================================
bool CRanking2::RankIn(int nScore)
{
    // 変数宣言
    bool bRankIn = false;

    // 比較
    if (CGame::GetScore() == nScore)
    {
        bRankIn = true;
    }

    return bRankIn;
}

//==============================================================
// 数字のフェードイン
//==============================================================
void CRanking2::FadeInNumber(int nCnt)
{
    // フェードインする数字なら
    if (nCnt >= FADE_IN_START_NUMBER)
    {
        // 1位の最高桁から、5位の最低桁までを入れ替える
        int nSwapNumber = SwapScoreNumberIndex(nCnt);

        // 透明度が1未満なら
        if (m_aAlpha[nSwapNumber] < 1.0f)
        {
            // 変数宣言
            int nBorder = 100;    // 透明度を上げる、境界線(最初は、仮に100)

                                  // 時間が進むにつれ、ボーダーを下げていくイメージ
                                  // 5位
            if (m_nCntTime >= FADE_IN_5)
            {
                nBorder = 40;
            }
            // 4位
            if (m_nCntTime >= FADE_IN_4)
            {
                nBorder = 32;
            }
            // 3位
            if (m_nCntTime >= FADE_IN_3)
            {
                nBorder = 24;
            }
            // 2位
            if (m_nCntTime >= FADE_IN_2)
            {
                nBorder = 16;
            }
            // 1位
            if (m_nCntTime >= FADE_IN_1)
            {
                nBorder = 8;
            }

            // 透明度を上げるボーダー以上なら
            if (nSwapNumber >= nBorder)
            {
                // 最下位の最初の桁なら
                if (nSwapNumber == MAX_RANKING2_NUMBER - 1)
                {
                    // フェードイン
                    m_aAlpha[nSwapNumber] += FADE_IN_RATE;
                }
                // それ以外なら
                else
                {
                    // (右から数えて)ひとつ前の数字のα値が、一定以上なら
                    if (m_aAlpha[nSwapNumber + 1] >= DELAY_ALPHA)
                    {
                        // フェードイン
                        m_aAlpha[nSwapNumber] += FADE_IN_RATE;
                    }
                }
            }
        }
    }
}

//==============================================================
// スコアの数字のインデックスを入れ替える
//==============================================================
int CRanking2::SwapScoreNumberIndex(int nIndex)
{
    // 変数宣言
    int nReturnNum = 0; // 返す値

    for (int nCntNumber = 0; nCntNumber < MAX_RANKING2_NUMBER; nCntNumber++)
    {
        // 足し算の式
        int nFormula = nIndex + nCntNumber;

        // 足した値が、ランキング2の数字のインデックスの端と端を足した値なら（例: 8+47 = 55、9+46 = 55、10+45 = 55）
        if (nFormula == (FADE_IN_START_NUMBER + MAX_RANKING2_NUMBER - 1))
        {
            // 返す値は、数えていた数字になる
            nReturnNum = nCntNumber;

            // forを抜ける
            break;
        }
    }

    return nReturnNum;
}