//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	fileio.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CFileIO
{
public:

	enum DIALOG
	{
		DIALOG_LOAD = 0,
		DIALOG_SAVE,
		DIALOG_MAX
	};

	static HRESULT Load(char* dest, size_t destSize ,char* filePath);
	static HRESULT Save(char* src, char* filePath);
	static void OverWrite(HWND hWnd);
	static void OpenDialog(HWND hWnd, DIALOG dialog);
private:
	CFileIO();		//コンストラクタ
	static const int MAX_FILEPATH_LENGTH = 1024;
	static char m_currentFilePath[MAX_FILEPATH_LENGTH];
	static const char FILE_NAME[MAX_FILEPATH_LENGTH];
	
};

#endif

