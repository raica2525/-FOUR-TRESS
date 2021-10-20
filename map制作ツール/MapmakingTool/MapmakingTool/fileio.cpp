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

char CFileIO::m_currentFilePath[MAX_FILEPATH_LENGTH]= {};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CFileIO::Load(char* dest, size_t destSize, char* filePath)
{
	FILE* fp = fopen(filePath,"r");
	if (fp == NULL)
	{
		return E_FAIL;
	}
	fscanf(fp, "%s", dest);
	if (strlen(dest) >= destSize)
	{
		assert(false);
	}
	fclose(fp);
	strcpy(m_currentFilePath, filePath);
	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�[�u
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CFileIO::Save(char* src, char* filePath)
{
	FILE* fp = fopen(filePath, "w");
	if (fp == NULL)
	{
		return E_FAIL;
	}
	fprintf(fp, "%s", src);
	int len = strlen(src);
	fclose(fp);
	strcpy(m_currentFilePath, filePath);
	return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �_�C�A���O���J��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CFileIO::OpenDialog(HWND hWnd, DIALOG dialog)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	char SavePath[MAX_FILEPATH_LENGTH];
	char FileName[MAX_FILEPATH_LENGTH];
	FileName[0] = '\0';
	GetCurrentDirectory(512, SavePath);
	strcat(SavePath, "\\Save");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrInitialDir = SavePath;
	ofn.lpstrFile = FileName;
	ofn.nMaxFile = 256;
	ofn.lpstrDefExt = "json";
	ofn.lpstrFilter = "JSON�t�@�C��(*.json)\0*.json\0" "�e�L�X�g�t�@�C��(*.txt)\0*.txt\0" "���ׂẴt�@�C��(*.*)\0*.*\0";
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	switch (dialog)
	{
	case DIALOG_LOAD:
		GetOpenFileName(&ofn);
		char str[1024];
		Load(str, 1024, FileName);
		break;
	case DIALOG_SAVE:
		GetSaveFileName(&ofn);
		Save(FileName, FileName);
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
		//TODO: �ۑ�������̂��ł����������������ɂ���
		CFileIO::Save(m_currentFilePath, m_currentFilePath);
	}
}