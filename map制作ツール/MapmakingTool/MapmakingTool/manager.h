//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRenderer;
class CCamera;
class CImGuiManager;
class CModelData;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager
{
public:
	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);	//�������֐�
	void Uninit(void);						//�I���֐�
	void Update(void);						//�X�V�֐�
	void Draw(void);						//�`��֐�
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CImGuiManager* GetImGuiManager(void) { return m_pImGuiManager; }
	static CModelData* GetModelData(void) { return m_pModelData; }
	static void LoadFile(void);
	static void UnloadFiles(void);

private:
	static CImGuiManager* m_pImGuiManager;
	static CRenderer* m_pRenderer;			//�����_���̃|�C���^
	static CCamera* m_pCamera;
	static CModelData* m_pModelData;
};

#endif

