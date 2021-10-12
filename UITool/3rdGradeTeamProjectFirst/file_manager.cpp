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
 // [writing] ファイルの書き込み
 //=============================================================================
 void CFile_Manager::writing(void)
 {
     std::ofstream pfile(OUTPUT_FILE_NAME);

     pfile << "SCRIPT			# この行は絶対消さないこと！\n" << std::endl;

     std::string str;
     for (int nCnt = 0; nCnt < MAX_ACCESS_NUM; nCnt++)
     {
         CUI* pUI = CUI::GetAccessUI(nCnt);// UIのインスタンス取得

                                           // UIの情報を文字列で取得
         if (pUI != NULL)
         {
             str = pUI->fileString();
             pfile << str << std::endl;
         }
     }

     pfile << "END_SCRIPT		# この行は絶対消さないこと！\n" << std::endl;

 }
 
 //=============================================================================
 // [ManagerUISet] ファイルの書き込み
 //=============================================================================
 void CFile_Manager::OutputUISet(void)
 {
     std::ofstream pfile(OUTPUT_FILE_NAME);
     std::string str;
     for (int nCnt = 0; nCnt < MAX_ACCESS_NUM; nCnt++)
     {
         CUI* pUI = CUI::GetAccessUI(nCnt);// UIのインスタンス取得

         // UIの情報を文字列で取得
         if (pUI!=NULL)
             str = pUI->fileString();
             pfile << str << std::endl;
     }
 }
