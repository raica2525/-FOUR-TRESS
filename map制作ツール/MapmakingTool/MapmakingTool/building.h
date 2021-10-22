//====================================================================
//
// �����̏��� (building.h)
// Author : �����N�m
//
//====================================================================
#ifndef _BUILDING_H_
#define _BUILDING_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene3d.h"

//================================================
// �O���錾
//================================================

class CBuilding : public CScene3D 
{
public:
	CBuilding();
	~CBuilding();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	static CBuilding *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
};

#endif