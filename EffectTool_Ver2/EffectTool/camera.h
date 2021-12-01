//========================================================================================================================
//
// �J�������� [camera.h]
// Author : �ɓ��z��
//
//========================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//================================================
// �}�N����`
//================================================
#define CAMERA_DISTANCE (750.0f)
#define CAMERA_VIEW_RANGE (25000.0f)			// ����
#define CAMERA_VIEW_FOV D3DXToRadian(45.0f)		// ����p
#define CAMERA_INIT_PHI (D3DXToRadian(90.0f))	// �t�@�C�̏����l
#define CAMERA_INIT_THETA (D3DXToRadian(-90.0f))	// �V�[�^�̏����l

//================================================
// �J�����N���X�錾
//================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	CCamera *Create(void);		// ��������
	void ResetGameCamera(void);	// �J�����̃��Z�b�g

	float GetDistance(void) { return m_fDistance; }	// �����̎擾
	float GetPhi(void) { return m_fPhi; }			// �t�@�C�̎擾
	float GetTheta(void) { return m_fTheta; }		// �V�[�^�̎擾

private:
	D3DXVECTOR3	m_posRDest;			// �J�����̒����_�i�ړI�l�j
	D3DXVECTOR3	m_posVDest;			// �J�����̍��W�i�ړI�l�j
	D3DXVECTOR3	m_posV;				// �J�����̍��W
	D3DXVECTOR3	m_posR;				// �����_
	D3DXVECTOR3	m_vecU;				// ������̃x�N�g��
	D3DXMATRIX	m_mtxProjection;	// �v���W�F�N�V�����}�g���N�X
	D3DXMATRIX	m_mtxView;			// �r���[�}�g���N�X
	float		m_fDistance;		// ����
	float		m_fPhi;				// �t�@�C
	float		m_fTheta;			// �V�[�^
};

#endif