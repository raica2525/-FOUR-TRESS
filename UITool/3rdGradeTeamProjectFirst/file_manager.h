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
    // メンバ関数(public)
    ~CFile_Manager();
    static CFile_Manager* Create(void);// オブジェクトの生成
    
private:
    // メンバ関数(private)
    void writing(void);// ファイルの書き込み

    void OutputUISet(void);

    // メンバ変数(private)
    FILE *m_pFile;// 書き込むファイルへのポインタ
};
#endif // !_FILE_OUTPUT_H_
