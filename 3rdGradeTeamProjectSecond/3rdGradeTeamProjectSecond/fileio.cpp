//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	fileio.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "fileio.h"
#include <fstream>
#include "mapmanager.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CFileIO::Load(std::string* dest, std::string filePath)
{
	dest->clear();
	std::ifstream ifs(filePath);
	if (!ifs)
	{
		return E_FAIL;
	}

	std::string buffer;
	while (!ifs.eof())
	{
		std::getline(ifs, buffer);
		*dest += buffer;
	}
	ifs.close();
	return S_OK;
}