//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	imguimanager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _IMGUIMANAGER_H_
#define _IMGUIMANAGER_H_

#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CImGuiWindow;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CImGuiManager
{
public:

	enum IMWINDOW
	{
		IMWINDOW_OBJ_INFO = 0,
		IMWINDOW_MAP_INFO,
		IMWINDOW_DEBUG_INFO,
		IMWINDOW_MAX,
	};

	CImGuiManager();		//�R���X�g���N�^
	~CImGuiManager();		//�f�X�g���N�^

	void Init(HWND hWnd);	//�������֐�
	void Uninit(void);		//�I���֐�
	void Update(void);		//�X�V�֐�
	void Draw(void);		//�`��֐�
	CImGuiWindow* GetImGuiWindow(IMWINDOW imWindow) { return m_pImGuiWindow[imWindow]; };
	bool GetShowStructure(void) { return m_bShowStructures; };
	bool GetShowCollisions(void) { return m_bShowCollisions; };
	void GetStr(char* _Dest) { strcpy(_Dest, m_str); };

	void SetShowStructures(bool bShowStructures) { m_bShowStructures = bShowStructures; };
	void SetShowCollisions(bool bShowCollisions) { m_bShowCollisions = bShowCollisions; };
	void SetStr(char* str) { strcpy(m_str, str); };
private:
	bool m_bShowStructures;
	bool m_bShowCollisions;
	bool m_bShowEnemys;
	char m_str[1024];
	CImGuiWindow* m_pImGuiWindow[IMWINDOW_MAX];
};

#endif

