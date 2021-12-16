//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	fileio.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "manager.h"
#include "fileio.h"
#include "json.h"
#include <fstream>
#include "mapmanager.h"
#include "building.h"
#include "enemy.h"
#include "texturemanager.h"
#include "modelManager.h"
std::string CFileIO::m_currentFilePath= {};
const char CFileIO::SAVE_FOLDER_NAME[] = "\\Save";
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セーブ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CFileIO::Save(std::string src, std::string filePath, bool bSavePath)
{
	std::ofstream ofs(filePath);
	if (!ofs)
	{
		return E_FAIL;
	}
	ofs << src << std::endl;
	if (bSavePath)
	{
		m_currentFilePath = filePath;
	}
	ofs.close();
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// ダイアログを開く
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CFileIO::OpenDialog(HWND hWnd, DIALOG dialog)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	char savePath[MAX_PATH];
	char fileName[MAX_FILE_NAME];
	savePath[0] = '\0';
	fileName[0] = '\0';
	GetCurrentDirectory(MAX_PATH - strlen(SAVE_FOLDER_NAME), savePath);
	strcat(savePath, SAVE_FOLDER_NAME);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrInitialDir = savePath;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_FILE_NAME;
	ofn.lpstrDefExt = "json";
	ofn.lpstrFilter = "JSONファイル(*.json)\0*.json\0" "テキストファイル(*.txt)\0*.txt\0" "すべてのファイル(*.*)\0*.*\0";
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	std::string str;
	switch (dialog)
	{
	case DIALOG_LOAD:
		if (!GetOpenFileName(&ofn))
		{
			break;
		}
		SetCurrentDirectory(CManager::GetAppPath().c_str());
		Load(&str, fileName);
		if (SUCCEEDED(CManager::GetMapManager()->CreateMapFromJson(CJson::FromJson(str))))
		{
			m_currentFilePath = fileName;
		}
		break;
	case DIALOG_SAVE:
	{
		if (!GetSaveFileName(&ofn))
		{
			break;
		}
		SetCurrentDirectory(CManager::GetAppPath().c_str());
		Save(CJson::ToJson(CreateMapData()), fileName);
		break;
	}
	default:
		assert(false);
		break;
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// テクスチャ追加
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CFileIO::OpenAddTextureDialog(HWND hWnd)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	char savePath[MAX_PATH];
	char fileName[MAX_FILE_NAME];
	savePath[0] = '\0';
	fileName[0] = '\0';
	GetCurrentDirectory(MAX_PATH - strlen(SAVE_FOLDER_NAME), savePath);
	strcat(savePath, SAVE_FOLDER_NAME);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrInitialDir = savePath;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_FILE_NAME;
	ofn.lpstrDefExt = "png";
	ofn.lpstrTitle = "テクスチャを追加";
	ofn.lpstrFilter = "画像ファイル(*.png;*.jpg;*.jpeg)\0*.png;*.jpg;*.jpeg\0" "すべてのファイル(*.*)\0*.*\0";
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	std::string str;
	if (!GetOpenFileName(&ofn))
	{
		return;
	}
	std::string fileNameBuff = fileName;
	char* cp;
	char* cpBuff;
	cp = strtok(fileName,"\\");
	while (1)
	{
		cpBuff = cp;
		cp = strtok(NULL, "\\");
		if (cp == NULL)
		{
			break;
		}
	}
	CManager::GetTextureManager()->AddTexture(cpBuff, CTextureManager::Load(fileNameBuff));
	
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// モデル追加
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CFileIO::OpenAddModelDialog(HWND hWnd)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	char savePath[MAX_PATH];
	char fileName[MAX_FILE_NAME];
	savePath[0] = '\0';
	fileName[0] = '\0';
	GetCurrentDirectory(MAX_PATH - strlen(SAVE_FOLDER_NAME), savePath);
	strcat(savePath, SAVE_FOLDER_NAME);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrInitialDir = savePath;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_FILE_NAME;
	ofn.lpstrDefExt = "x";
	ofn.lpstrTitle = "モデルを追加";
	ofn.lpstrFilter = "モデルファイル(*.x)\0*.x\0" "すべてのファイル(*.*)\0*.*\0";
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	std::string str;
	if (!GetOpenFileName(&ofn))
	{
		return;
	}
	SetCurrentDirectory(CManager::GetAppPath().c_str());
	std::string fileNameBuff = fileName;
	char* cp;
	char* cpBuff;
	cp = strtok(fileName, "\\");
	while (1)
	{
		cpBuff = cp;
		cp = strtok(NULL, "\\");
		if (cp == NULL)
		{
			break;
		}
	}
	CManager::GetModelManager()->Load(cpBuff,fileNameBuff);
}

void CFileIO::OverWrite(HWND hWnd)
{
	//現在作業中のファイルがあれば上書き、なければ新規保存
	if (m_currentFilePath.empty())
	{
		OpenDialog(hWnd, DIALOG_SAVE);
	}
	else
	{
		Save(CJson::ToJson(CreateMapData()), m_currentFilePath);
	}
}

picojson::object CFileIO::CreateMapData(void)
{
	picojson::object allDatas;
	CMapManager* pMapManager = CManager::GetMapManager();
	allDatas.insert(std::make_pair("buildings", picojson::value(pMapManager->ObjectListToArray<CBuilding>())));
	allDatas.insert(std::make_pair("enemys", picojson::value(pMapManager->ObjectListToArray<CEnemy>())));
	allDatas.insert(std::make_pair("collisions", picojson::value(pMapManager->ObjectListToArray<CCollision>())));
	allDatas.insert(std::make_pair("blocks", picojson::value(pMapManager->BuildingCollisionSetToArray())));
	allDatas.insert(std::make_pair("grounds", picojson::value(pMapManager->ObjectListToArray<CGround>())));
	allDatas.insert(std::make_pair("spawn", picojson::value(pMapManager->SpawnDataToJsonObject())));

	return allDatas;
}

