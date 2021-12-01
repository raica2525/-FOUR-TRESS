//==============================================================================================================================
//
// �J�������� (camera.cpp)
// Author : �ɓ��z��
//
//==============================================================================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	m_posRDest = DEFAULT_VECTOR;
	m_posVDest = DEFAULT_VECTOR;
	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_fDistance = CAMERA_DISTANCE;

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fPhi = CAMERA_INIT_PHI;
	m_fTheta = CAMERA_INIT_THETA;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �Q�[���J�ڎ��̃J�����̃��Z�b�g
//=============================================================================
void CCamera::ResetGameCamera(void)
{
	m_posRDest = DEFAULT_VECTOR;
	m_posVDest = DEFAULT_VECTOR;
	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_fDistance = CAMERA_DISTANCE;

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fPhi = CAMERA_INIT_PHI;
	m_fTheta = CAMERA_INIT_THETA;

	// �ʒu�̖ړI�n���X�V(���ʍ��W�̌���)
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fPhi) * cosf(m_fTheta);
	m_posV.y = m_posR.y + m_fDistance * cosf(m_fPhi);
	m_posV.z = m_posR.z + m_fDistance * sinf(m_fPhi) * sinf(m_fTheta);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �J�����̃��Z�b�g
	ResetGameCamera();

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, CAMERA_VIEW_FOV, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//  �J�����ʒu�C������
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �E�N���b�N���Ă���Ȃ王�_�ړ�
	if (CManager::GetMouse()->GetMousePress(1) == true)
	{
		// �J�����Ǝ��g�̋���(�}�E�X�̃z�C�[���ŋ����̒���)
		m_fDistance -= CManager::GetMouse()->GetMouseWheel();

		// �}�E�X�̈ړ��ʂ��v�Z
		m_fTheta -= CManager::GetMouse()->GetMouseMove().x;
		m_fPhi -= CManager::GetMouse()->GetMouseMove().y;
	}

	// �J�����̋����Ǝ��_�ړ������]���Ȃ��悤��
	if (m_fDistance < 0.0f)
	{
		m_fDistance = 0.0001f;
	}
	if (m_fPhi < 0.0f)
	{
		m_fPhi = 0.0001f;
	}
	else if(m_fPhi >= D3DX_PI)
	{
		m_fPhi = D3DX_PI - 0.0001f;
	}

	// ���]�ȏサ�Ȃ��悤��
	if (m_fTheta < -D3DX_PI)
	{
		m_fTheta += D3DX_PI * 2.0f;
	}
	else if (m_fTheta > D3DX_PI)
	{
		m_fTheta -= D3DX_PI * 2.0f;
	}

	// �ʒu�̖ړI�n���X�V(���ʍ��W�̌���)
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fPhi) * cosf(m_fTheta);
	m_posV.y = m_posR.y + m_fDistance * cosf(m_fPhi);
	m_posV.z = m_posR.z + m_fDistance * sinf(m_fPhi) * sinf(m_fTheta);

	//// �J�����̈ʒu�ƒ����_���X�V
	//m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
	//m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, CAMERA_VIEW_FOV, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, CAMERA_VIEW_RANGE);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CCamera * CCamera::Create(void)
{
    CCamera *pCamera = NULL;
    pCamera = new CCamera;
    pCamera->Init();
    return pCamera;
}