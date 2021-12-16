//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	fileio.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "main.h"
#include "picojson.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CFileIO
{
public:
	static HRESULT Load(std::string* dest, std::string filePath);
private:
	CFileIO();		//コンストラクタ
};

#endif

