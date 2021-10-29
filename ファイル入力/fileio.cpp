//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	fileio.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "fileio.h"
#include "json.h"
#include <fstream>
#include "mapManager.h"
std::string CFileIO::m_currentFilePath= {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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

	m_currentFilePath = filePath;
	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�[�u
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CFileIO::Save(std::string src, std::string filePath)
{
	std::ofstream ofs(filePath);
	if (!ofs)
	{
		return E_FAIL;
	}
	ofs << src << std::endl;
	m_currentFilePath = filePath;
	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �_�C�A���O���J��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CFileIO::OpenDialog(HWND hWnd, DIALOG dialog)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	char savePath[1024];
	char fileName[1024];
	savePath[0] = '\0';
	fileName[0] = '\0';
	GetCurrentDirectory(512, savePath);
	strcat(savePath, "\\Save");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrInitialDir = savePath;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 256;
	ofn.lpstrDefExt = "json";
	ofn.lpstrFilter = "JSON�t�@�C��(*.json)\0*.json\0" "�e�L�X�g�t�@�C��(*.txt)\0*.txt\0" "���ׂẴt�@�C��(*.*)\0*.*\0";
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	std::string str;
	switch (dialog)
	{
	case DIALOG_LOAD:
		GetOpenFileName(&ofn);
		Load(&str, fileName);
		CManager::GetMapManager()->CreateMapObjectFromJsonObject(CJson::FromJson(str));
		break;
	case DIALOG_SAVE:
		GetSaveFileName(&ofn);
		Save(fileName, fileName);
		break;
	default:
		assert(false);
		break;
	}
}

void CFileIO::OverWrite(HWND hWnd)
{
	//���ݍ�ƒ��̃t�@�C��������Ώ㏑���A�Ȃ���ΐV�K�ۑ�
	if (m_currentFilePath[0] == '\0')
	{
		CFileIO::OpenDialog(hWnd, CFileIO::DIALOG_SAVE);
	}
	else
	{
		//TODO �ۑ�������̂��ł����������������ɂ���
		CFileIO::Save(m_currentFilePath, m_currentFilePath);
	}
}