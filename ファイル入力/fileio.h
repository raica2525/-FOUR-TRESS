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

	static HRESULT Load(std::string* dest, std::string filePath);
	static HRESULT Save(std::string src, std::string filePath);
	static void OverWrite(HWND hWnd);
	static void OpenDialog(HWND hWnd, DIALOG dialog);
private:
	CFileIO();		//コンストラクタ
	static std::string m_currentFilePath;
	static std::string m_fileName;
	
};

#endif

