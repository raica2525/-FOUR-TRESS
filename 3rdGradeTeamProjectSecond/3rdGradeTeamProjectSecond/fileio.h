//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	fileio.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "main.h"
#include "picojson.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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
	static HRESULT Save(std::string src, std::string filePath,bool bSavePath = true);
	static void OverWrite(HWND hWnd);
	static void OpenDialog(HWND hWnd, DIALOG dialog);
	static void OpenAddTextureDialog(HWND hWnd);
	static void OpenAddModelDialog(HWND hWnd);
	static void ClearCurrentPath(void) { m_currentFilePath.clear(); }
private:
	CFileIO();		//�R���X�g���N�^
	static std::string m_currentFilePath;
	static std::string m_fileName;
	static const int MAX_FILE_NAME = 256;
	static const char SAVE_FOLDER_NAME[];
	static picojson::object CreateMapData(void);
	
};

#endif

