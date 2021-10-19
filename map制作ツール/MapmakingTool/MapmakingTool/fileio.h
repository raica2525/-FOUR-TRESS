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
	static HRESULT Load(char* dest, size_t destSize ,char* filePath);
	static HRESULT Save(char* src, char* filePath);

private:
	CFileIO();		//コンストラクタ
};

#endif

