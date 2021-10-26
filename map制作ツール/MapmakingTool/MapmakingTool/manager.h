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
class CBuilding;
class CEenemy;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager
{
public:
	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	struct BUILDING
	{
		std::string name;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 size;
		D3DCOLOR col;
		int nModelNum;
		int nCollisionIndex;
	};

	struct Collision
	{
		int index;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;

	};

	struct STAGE_DATA
	{
		std::vector<CBuilding> buildings;
		std::vector<CEenemy> enemys;
		std::vector<Collision> collisions;
	};

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);	//�������֐�
	void Uninit(void);											//�I���֐�
	void Update(void);											//�X�V�֐�
	void Draw(void);											//�`��֐�
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CImGuiManager* GetImGuiManager(void) { return m_pImGuiManager; }
	static void LoadFile(void);
	static void UnloadFiles(void);

private:
	static CImGuiManager* m_pImGuiManager;
	static CRenderer* m_pRenderer;			//�����_���̃|�C���^
	static CCamera* m_pCamera;

};

#endif