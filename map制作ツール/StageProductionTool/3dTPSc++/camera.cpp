//===============================================
//
// �������� (light.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "camera.h"

#include "CreateStage.h"
#include "block.h"
#include "effect3d.h"
#include "game.h"
#include "input.h"
#include "library.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
D3DXVECTOR3 CCamera::m_posRDest        = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CCamera::m_posVDest        = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CCamera::CAMERA_STATE CCamera::m_state = CCamera::CAMERA_NORMAL;

D3DXVECTOR3 CCamera::m_posR = D3DXVECTOR3(0, 0, 0);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
    D3DXMatrixIdentity(&m_mtxView);
    D3DXMatrixIdentity(&m_mtxProjection);
    m_pos         = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_state       = CAMERA_NORMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
    InitMouse();

    POINT Point;
    GetCursorPos(&Point);

    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    m_posV           = D3DXVECTOR3(0.0f, 30.0f, -30.0f);    //�ʒu
    m_posR           = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //�����_
    m_vecU           = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_StartMousePos  = D3DXVECTOR3(Point.x, Point.y, 0.0f);
    m_AmountMovement = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_state          = CAMERA_NORMAL;

    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 2000.0f);
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
	if (CCreateStage::GetPauseJudge() == false) {
		//�}�E�X�̍��W�擾
		POINT Point;
		GetCursorPos(&Point);
		D3DXVECTOR3 MousePos = D3DXVECTOR3(Point.x, Point.y, 0);
		//�L�[�{�[�h�̊m�ۂ������������擾
		CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
		//  �J�����ʒu�C������
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		//�}�E�X�z�C�[���̏����擾
		m_MouseWheel = GetMouseWheel();

		// �}�E�X�̈ړ��ʂ��v�Z
		m_AmountMovement.y += (m_StartMousePos.y - MousePos.y) * CAMERA_SENSITIVITY;
		m_AmountMovement.x += (MousePos.x - m_StartMousePos.x) * CAMERA_SENSITIVITY;

		// ��E�����������Ȃ��悤�ɒ���
		if (m_AmountMovement.y >= 89) {
			m_AmountMovement.y = 89;
		}
		if (m_AmountMovement.y <= -89) {
			m_AmountMovement.y = -89;
		}

		// ���R���g���[����������Ă��Ȃ��ꍇ
		if (!pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
			// �O���b�W���g�p���Ă��Ȃ��ꍇ
			if (CCreateStage::GetGreaseJudge() == false) {
				if (pInputKeyboard->GetKeyboardPress(DIK_W)) {
					m_posV.x += sinf(D3DXToRadian(m_AmountMovement.x)) * 30.0f;
					m_posV.z += cosf(D3DXToRadian(m_AmountMovement.x)) * 30.0f;
				}
				if (pInputKeyboard->GetKeyboardPress(DIK_S)) {
					m_posV.x -= sinf(D3DXToRadian(m_AmountMovement.x)) * 30.0f;
					m_posV.z -= cosf(D3DXToRadian(m_AmountMovement.x)) * 30.0f;
				}
				if (pInputKeyboard->GetKeyboardPress(DIK_A)) {
					m_posV.x -= sinf(D3DXToRadian(m_AmountMovement.x + 90)) * 30.0f;
					m_posV.z -= cosf(D3DXToRadian(m_AmountMovement.x + 90)) * 30.0f;
				}
				if (pInputKeyboard->GetKeyboardPress(DIK_D)) {
					m_posV.x += sinf(D3DXToRadian(m_AmountMovement.x + 90)) * 30.0f;
					m_posV.z += cosf(D3DXToRadian(m_AmountMovement.x + 90)) * 30.0f;
				}
			}
			// �O���b�W���g�p���Ă���ꍇ
			if (CCreateStage::GetGreaseJudge() == true) {
				if (pInputKeyboard->GetKeyboardTrigger(DIK_W)) {
					m_posV.x += sinf(D3DXToRadian(m_AmountMovement.x)) * GREASE_NUM;
					m_posV.z += cosf(D3DXToRadian(m_AmountMovement.x)) * GREASE_NUM;
				}
				if (pInputKeyboard->GetKeyboardTrigger(DIK_S)) {
					m_posV.x -= sinf(D3DXToRadian(m_AmountMovement.x)) * GREASE_NUM;
					m_posV.z -= cosf(D3DXToRadian(m_AmountMovement.x)) * GREASE_NUM;
				}
				if (pInputKeyboard->GetKeyboardTrigger(DIK_A)) {
					m_posV.x -= sinf(D3DXToRadian(m_AmountMovement.x + 90)) * GREASE_NUM;
					m_posV.z -= cosf(D3DXToRadian(m_AmountMovement.x + 90)) * GREASE_NUM;
				}
				if (pInputKeyboard->GetKeyboardTrigger(DIK_D)) {
					m_posV.x += sinf(D3DXToRadian(m_AmountMovement.x + 90)) * GREASE_NUM;
					m_posV.z += cosf(D3DXToRadian(m_AmountMovement.x + 90)) * GREASE_NUM;
				}
			}
			// �X�y�[�X/���V�t�g�ŃJ������Y�����㉺������
			if (pInputKeyboard->GetKeyboardPress(DIK_SPACE)) {
				m_posV.y += 35.0f;
			}
			if (pInputKeyboard->GetKeyboardPress(DIK_LSHIFT)) {
				m_posV.y -= 35.0f;
			}
		}

		// �G���^�[�L�[�������ꂽ�ꍇ
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN)) {
			// �J������������
			Init();
		}

		//�z�C�[�����g�p����
		if (m_MouseWheel.zDelta >= 120) {
			m_posV.y += 70.0f;
		}
		if (m_MouseWheel.zDelta <= -120) {
			m_posV.y -= 70.0f;
		}

		// �����_���v�Z
		m_posR.x = m_posV.x + sinf(D3DXToRadian(m_AmountMovement.x)) * DISTANCE;
		m_posR.y = m_posV.y + tanf(D3DXToRadian(m_AmountMovement.y)) * DISTANCE;
		m_posR.z = m_posV.z + cosf(D3DXToRadian(m_AmountMovement.x)) * DISTANCE;

		D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

		D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(90), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 50000.0f);
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

		InitMouse();
	}
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CCamera *CCamera::Create(void)
{
    CCamera *pCamera = NULL;
    pCamera          = new CCamera;
    pCamera->Init();
    pCamera->m_nType = 0;
    return pCamera;
}

//=============================================================================
// �����_�ύX����
//=============================================================================
void CCamera::SetCameraLookAt(D3DXVECTOR3 pos)
{
    m_posRDest = D3DXVECTOR3(pos.x, pos.y, pos.z);
}

//=============================================================================
// �}�E�X�̍��W���E�B���h�E�̒��S�Ɉړ�������
//=============================================================================
void CCamera::InitMouse(void)
{
    HWND hDesktop = GetDesktopWindow();

    WINDOWINFO windowInfo;
    LONG pos_x, pos_y;
    windowInfo.cbSize = sizeof(WINDOWINFO);

    GetWindowInfo(hDesktop, &windowInfo);
    pos_x = windowInfo.rcWindow.left;
    pos_y = windowInfo.rcWindow.top;
    SetCursorPos(SCREEN_WIDTH / 2 + pos_x, SCREEN_HEIGHT / 2 + pos_y);
}
