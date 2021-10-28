//=============================================================================
//
// ファイルマネージャーヘッダ [file_manager.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_
#include <stdio.h>
#include <fstream>


//*****************************************************************************
// クラス生成
//*****************************************************************************
class CFile_Manager
{
    static CFile_Manager* pInstance;// インスタンスへのポインタ
    CFile_Manager();

public:

    // セット
    typedef enum
    {
        SET_NONE = 0,
        SET_TITLE,
        SET_MANUAL,
        SET_CUSTOM,
        SET_GAME,
        SET_RESULT,
        SET_MENU,
        SET_MAX
    }SET;

    // メンバ関数(public)
    ~CFile_Manager();
    static CFile_Manager* Create(void);// オブジェクトの生成
    
    void Read(char* fileName = "data/TXT/test.txt");

    // Get関数
    static CFile_Manager* GetInstance(void) { return pInstance; }

private:
    // メンバ関数(private)
    void writing(void);// ファイルの書き込み

    // メンバ変数(private)
    FILE *m_pFile;// 書き込むファイルへのポインタ
};
#endif // !_FILE_OUTPUT_H_
