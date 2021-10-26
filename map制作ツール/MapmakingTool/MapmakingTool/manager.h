//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CRenderer;
class CCamera;
class CImGuiManager;
class CBuilding;
class CEenemy;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CManager
{
public:
	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

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

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);	//初期化関数
	void Uninit(void);											//終了関数
	void Update(void);											//更新関数
	void Draw(void);											//描画関数
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CImGuiManager* GetImGuiManager(void) { return m_pImGuiManager; }
	static void LoadFile(void);
	static void UnloadFiles(void);

private:
	static CImGuiManager* m_pImGuiManager;
	static CRenderer* m_pRenderer;			//レンダラのポインタ
	static CCamera* m_pCamera;

};

#endif