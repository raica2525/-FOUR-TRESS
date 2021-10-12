//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene3d.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CModel;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I�u�W�F�N�g�N���X
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CScene3d : public CScene
{
public:
	CScene3d();
	virtual ~CScene3d();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void)	= 0;
	virtual void Draw(void)		= 0;

	void SetPos(D3DXVECTOR3 pos)	{ m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot)	{ m_rot = rot; }
	void SetSize(D3DXVECTOR3 size)	{ m_size = size; }
	D3DXVECTOR3 GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 GetRot(void)		{ return m_rot; }
	D3DXVECTOR3 GetSize(void)		{ return m_size; }
private:
	D3DXVECTOR3	m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// ��]���
	D3DXVECTOR3 m_size;								// �T�C�Y
};

#endif