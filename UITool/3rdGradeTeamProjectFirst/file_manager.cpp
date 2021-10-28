//=============================================================================
//
// ファイルの書き込みクラス [file_manager.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "file_manager.h"
#include "ui.h"
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OUTPUT_FILE_NAME "data/TXT/test.txt"    // 書き込むファイル名

//*****************************************************************************
// 静的メンバ関数
//*****************************************************************************
CFile_Manager* CFile_Manager::pInstance = nullptr;

//=============================================================================
// [CFile_Manager] コンストラクタ
//=============================================================================
CFile_Manager::CFile_Manager()
{

}

//=============================================================================
// [~CFile_Manager] デストラクタ
//=============================================================================
CFile_Manager::~CFile_Manager()
{
    pInstance = nullptr;
}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
 CFile_Manager* CFile_Manager::Create(void)
{
    if (!pInstance)
    {
        pInstance = new CFile_Manager;
        pInstance->writing();
    }
    return pInstance;
}


 //=============================================================================
 // [Read] ファイルの読み込み
 // 引数
 // 読み込むファイル名
 //=============================================================================
 void CFile_Manager::Read(char* fileName)
 {
     // ファイルポイント
     FILE *pFile = NULL;

     // 変数宣言
     char cReadText[1024];	// 文字として読み取り用
     char cHeadText[1024];	// 文字の判別用
     char cDie[1024];		// 使わない文字 
     int nBool = 0;          // intからboolへの橋渡し

         // ファイルを開く
         pFile = fopen(fileName, "r");

     assert(pFile);

     // 開けたら
     if (pFile != NULL)
     {
         // SCRIPTの文字が見つかるまで
         while (strcmp(cHeadText, "SCRIPT") != 0)
         {
             // テキストからcReadText分文字を受け取る
             fgets(cReadText, sizeof(cReadText), pFile);

             // cReedTextをcHeadTextに格納
             sscanf(cReadText, "%s", &cHeadText);
         }

         // cHeadTextがSCRIPTの時
         if (strcmp(cHeadText, "SCRIPT") == 0)
         {
             // cHeadTextがEND_SCRIPTになるまで
             while (strcmp(cHeadText, "END_SCRIPT") != 0)
             {
                 fgets(cReadText, sizeof(cReadText), pFile);
                 sscanf(cReadText, "%s", &cHeadText);

                 // cHeadTextがUISETの時
                 if (strcmp(cHeadText, "UISET") == 0)
                 {
                     // 生成時に結びつけるもの
                     int nTexType = 0;                                   // 画像番号
                     int nAccessNum = NOT_EXIST;                         // アクセスナンバー
                     D3DXVECTOR3 pos = DEFAULT_VECTOR;                   // 位置
                     D3DXVECTOR3 size = DEFAULT_VECTOR;                  // 大きさ
                     D3DXVECTOR3 collisionPos = DEFAULT_VECTOR;          // 当たり判定の位置
                     D3DXVECTOR3 collisionSize = DEFAULT_VECTOR;         // 当たり判定の大きさ
                     int nRot = 0;                                       // 角度
                     D3DXCOLOR col = DEFAULT_COLOR;                      // 色
                     bool bAddBrend = false;                             // 加算合成
                     bool bUseZBuffer = false;                           // 3Dモデルの後ろに出すかどうか
                     bool bFrontText = false;                            // テキストよりも手前かどうか
                     int nAlphaTestBorder = DEFAULT_ALPHATEST_BORDER_2D; // アルファテストのボーダー
                     bool bShaveTex = false;                             // 端の1ピクセル削るかどうか
                     bool bDisp = true;                                  // 表示するかどうか
                     int nIndexAction = 0;                               // アクションのインデックス    
                     CUI::ActionInfo aActionInfo[MAX_ACTION] = {};            // アクションの情報
                     memset(aActionInfo, 0, sizeof(aActionInfo));
                     memset(aActionInfo->afParam, 0, sizeof(aActionInfo->afParam));

                     // cHeadTextがEND_UISETになるまで
                     while (strcmp(cHeadText, "END_UISET") != 0)
                     {
                         fgets(cReadText, sizeof(cReadText), pFile);
                         sscanf(cReadText, "%s", &cHeadText);

                         if (strcmp(cHeadText, "TYPE") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nTexType);

                             // 不正な値は全てデフォルトを呼び出す
                             if (nTexType < 0 || nTexType >= MAX_TEXTURE)
                             {
                                 nTexType = 0;
                             }
                         }
                         else if (strcmp(cHeadText, "ACCESS_NUM") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nAccessNum);

                             // 不正な値は全てデフォルトを呼び出す
                             if (nAccessNum < 0 || nAccessNum >= MAX_ACCESS_NUM)
                             {
                                 nAccessNum = NOT_EXIST;
                             }
                         }
                         else if (strcmp(cHeadText, "NO_DRAW") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 1)
                             {
                                 bDisp = false;
                             }
                         }
                         else if (strcmp(cHeadText, "POS") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &pos.x, &pos.y);
                         }
                         else if (strcmp(cHeadText, "SIZE") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &size.x, &size.y);
                         }
                         else if (strcmp(cHeadText, "COLLISION_POS") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &collisionPos.x, &collisionPos.y);
                         }
                         else if (strcmp(cHeadText, "COLLISION_SIZE") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &collisionSize.x, &collisionSize.y);
                         }
                         else if (strcmp(cHeadText, "ROT") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRot);
                         }
                         else if (strcmp(cHeadText, "COL") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie, &col.r, &col.g, &col.b, &col.a);
                         }
                         else if (strcmp(cHeadText, "ADD_BLEND") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bAddBrend = false;
                             }
                             else
                             {
                                 bAddBrend = true;
                             }
                         }
                         else if (strcmp(cHeadText, "USE_ZBUFFER") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bUseZBuffer = false;
                             }
                             else
                             {
                                 bUseZBuffer = true;
                             }
                         }
                         else if (strcmp(cHeadText, "FRONT_TEXT") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bFrontText = false;
                             }
                             else
                             {
                                 bFrontText = true;
                             }
                         }
                         else if (strcmp(cHeadText, "ALPHA_TEST_BORDER") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nAlphaTestBorder);
                         }
                         else if (strcmp(cHeadText, "SHAVE_TEX") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bShaveTex = false;
                             }
                             else
                             {
                                 bShaveTex = true;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION0") == 0)
                         {
                             nIndexAction = 0;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // 不正な値は全てデフォルトを呼び出す
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION1") == 0)
                         {
                             nIndexAction = 1;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // 不正な値は全てデフォルトを呼び出す
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION2") == 0)
                         {
                             nIndexAction = 2;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // 不正な値は全てデフォルトを呼び出す
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION3") == 0)
                         {
                             nIndexAction = 3;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // 不正な値は全てデフォルトを呼び出す
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "LOCK") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 aActionInfo[nIndexAction].bLock = false;
                             }
                             else
                             {
                                 aActionInfo[nIndexAction].bLock = true;
                             }
                         }
                         else if (strcmp(cHeadText, "PARAM0") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[0]);
                         }
                         else if (strcmp(cHeadText, "PARAM1") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[1]);
                         }
                         else if (strcmp(cHeadText, "PARAM2") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[2]);
                         }
                         else if (strcmp(cHeadText, "PARAM3") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[3]);
                         }
                         else if (strcmp(cHeadText, "PARAM4") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[4]);
                         }
                         else if (strcmp(cHeadText, "PARAM5") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[5]);
                         }
                         else if (strcmp(cHeadText, "PARAM6") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[6]);
                         }
                         else if (strcmp(cHeadText, "PARAM7") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[7]);
                         }
                     }

                     // 生成（アクションの情報も結びつける）
                     CUI* pUI = CUI::Create(nTexType, pos, size, nRot, col, bFrontText, bAddBrend, nAlphaTestBorder, bUseZBuffer, collisionPos, collisionSize);
                     for (int nCnt = 0; nCnt < MAX_ACTION; nCnt++)
                     {
                         pUI->SetActionInfo(nCnt, aActionInfo[nCnt].action, aActionInfo[nCnt].bLock,
                             aActionInfo[nCnt].afParam[0], aActionInfo[nCnt].afParam[1], aActionInfo[nCnt].afParam[2], aActionInfo[nCnt].afParam[3],
                             aActionInfo[nCnt].afParam[4], aActionInfo[nCnt].afParam[5], aActionInfo[nCnt].afParam[6], aActionInfo[nCnt].afParam[7]);

                     }

                     // アクセス権を取得する
                     if (nAccessNum > NOT_EXIST && nAccessNum < MAX_ACCESS_NUM)
                     {
                         pUI->SetAccessUI(nAccessNum);
                     }

                     // 端の1ピクセルを削るかどうか
                     if (bShaveTex)
                     {
                         pUI->SetShaveTex();
                     }

                     // 表示するかどうかを設定
                     pUI->SetDisp(bDisp);

                     CUI::SetUI(pUI);
#ifdef _DEBUG
                     pUI->SetReloadUI();
#endif
                 }
             }
         }
         // ファイルを閉じる
         fclose(pFile);
     }
     // 開けなかったら
     else
     {
         printf("開けれませんでした\n");
     }
 }

 //=============================================================================
 // [writing] ファイルの書き込み
 //=============================================================================
 void CFile_Manager::writing(void)
 {
     std::ofstream pfile(OUTPUT_FILE_NAME);

     pfile << "SCRIPT			# この行は絶対消さないこと！\n" << std::endl;

     std::string str;
     for (int nCnt = 0; nCnt < 3; nCnt++)
     {
         CUI* pUI = CUI::GetUI(nCnt);// UIのインスタンス取得

                                           // UIの情報を文字列で取得
         if (pUI != NULL)
         {
             str = pUI->fileString();
             pfile << "UISET" << std::endl << str  << "END_UISET" << std::endl << std::endl;
         }
     }

     pfile << std::endl << "END_SCRIPT		# この行は絶対消さないこと！\n" << std::endl;

 }