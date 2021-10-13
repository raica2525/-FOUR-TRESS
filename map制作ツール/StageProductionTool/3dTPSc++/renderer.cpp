//===============================================
//
// �`�揈�� (renderer.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "fade.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "block.h"
#include "enemy.h"
#include "effect3d.h"
#include "CreateStage.h"

//========================================
// �����_�����O�̃f�t�H���g�R���X�g���N�^
//========================================
CRenderer::CRenderer()
{
	m_nSaveMapJudgeTime = 120;
	m_nBlockSaveDateJudgeTime = 120;
    m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
    m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	m_pFont = NULL; // �t�H���g�̃|�C���^
}

//========================================
// �����_�����O�̃f�X�g���N�^
//========================================
CRenderer::~CRenderer()
{

}

//========================================
// �����_�����O�̏���������
//========================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
    D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;
    D3DMATERIAL9 material;

    // Direct3D�I�u�W�F�N�g�̍쐬
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (m_pD3D == NULL)
    {
        return E_FAIL;
    }

    // ���݂̃f�B�X�v���C���[�h���擾
    if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    // �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
    ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
    d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
    d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
    d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
    d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
    d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

                                                                // �f�o�C�X�̐���
                                                                // �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
                                                                // �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp, &m_pD3DDevice)))
    {
        // ��L�̐ݒ肪���s������
        // �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
        if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp, &m_pD3DDevice)))
        {
            // ��L�̐ݒ肪���s������
            // �`��ƒ��_������CPU�ōs�Ȃ�
            if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
                D3DDEVTYPE_REF, hWnd,
                D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                &d3dpp, &m_pD3DDevice)))
            {
                // �������s
                return E_FAIL;
            }
        }
    }

    // �����_�[�X�e�[�g�̐ݒ�
    m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);          // �J�����O������
    m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);                  // Z�o�b�t�@���g�p
    m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);         // ���u�����h���s��
    m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    // ���\�[�X�J���[�̎w��
    m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// ���f�X�e�B�l�[�V�����J���[
    m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);                 // �J�������g�p����
    m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);            // �A���r�G���g�̐ݒ�

                                                                        // �T���v���[�X�e�[�g�̐ݒ�
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);   // �e�N�X�`��U�l�̌J��Ԃ��ݒ�
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);   // �e�N�X�`��V�l�̌J��Ԃ��ݒ�
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);    // �e�N�X�`���g�厞�̕�Ԑݒ�
    m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);    // �e�N�X�`���k�����̕�Ԑݒ�

                                                                            // �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // �A���t�@�u�����f�B���O����
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // �ŏ��̃A���t�@����(�����l)
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT); // 2�Ԗڂ̃A���t�@����(�����l)

                                                                            // �}�e���A���̐ݒ�
    ZeroMemory(&material, sizeof(D3DMATERIAL9));
    material.Ambient.r = 1.0f;
    material.Ambient.g = 1.0f;
    material.Ambient.b = 1.0f;
    material.Ambient.a = 1.0f;
    m_pD3DDevice->SetMaterial(&material);

    // �f�o�b�O���\���p�t�H���g�̐���
    D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	D3DXCreateFont(m_pD3DDevice, 40, 40, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pPauseFont);

    return S_OK;
}

//========================================
// �����_�����O�̏I������
//========================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
    // �f�o�b�O���\���p�t�H���g�̔j��
    if (m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
#endif

    // �f�o�C�X�̔j��
    if (m_pD3DDevice != NULL)
    {
        m_pD3DDevice->Release();
        m_pD3DDevice = NULL;
    }

    // Direct3D�I�u�W�F�N�g�̔j��
    if (m_pD3D != NULL)
    {
        m_pD3D->Release();
        m_pD3D = NULL;
    }
}

//========================================
// �����_�����O�̍X�V����
//========================================
void CRenderer::Update(void)
{
    // �S�ẴI�u�W�F�N�g���X�V
    CScene::UpdateAll();
}

//========================================
// �����_�����O�̕`�揈��
//========================================
void CRenderer::Draw(void)
{
    // �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
    m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(249, 102, 71, 255), 1.0f, 0);

    // Direct3D�ɂ��`��̊J�n
    if (SUCCEEDED(m_pD3DDevice->BeginScene()))
    {
        // �S�ẴI�u�W�F�N�g��`��
        CScene::DrawAll();

#ifdef _DEBUG
        // FPS�\��
        DrawFPS();
#endif
		DrawPosRAndSelectType();
		DrawBlockPos();
		DrawEnemyPos();
		DrawCursorPos();
		DrawFixedSshaft();
		DrawGreaseJudge();
		DrawSeveMapJudge();
		DrawCopyDate();
		DrawCreateObjectType();
		DrawPauseJudge();
		DrawObjectSaveDate();

        // Direct3D�ɂ��`��̏I��
        m_pD3DDevice->EndScene();
    }

    // �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
    m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
// FPS�`�揈��
//========================================
#ifdef _DEBUG
void CRenderer::DrawFPS(void)
{
    RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    char str[BYTE];

    wsprintf(str, "FPS:%d\n", GetFPS());

    // �e�L�X�g�`��
    m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

void CRenderer::DrawPosRAndSelectType(void) {
	RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
#ifndef _DEBUG
	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
#endif
	char str[BYTE];

	if (CCreateStage::GetCreateObject() == CCreateStage::CREATEOBJECT_STAGE) {
		wsprintf(str, "posR.x:%d posR.y:%d posR.z:%d SelectName:%s\n", (int)CCamera::GetCameraposR().x, 0, (int)CCamera::GetCameraposR().z, CBlock::GetBlockData(CCreateStage::GetBlockType()).DrawName);
	}
	if (CCreateStage::GetCreateObject() == CCreateStage::CREATEOBJECT_ENEMY) {
		wsprintf(str, "posR.x:%d posR.y:%d posR.z:%d SelectName:%s\n", (int)CCamera::GetCameraposR().x, 0, (int)CCamera::GetCameraposR().z, CEnemy::GetEnemyData(CCreateStage::GetEnemyType()).DrawName);
	}

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

void CRenderer::DrawBlockPos(void) {
	if (CBlock::GetSelectBlock() != NULL) {
		char str[BYTE];

		RECT rect = { 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT };

		wsprintf(str, "BlockPos.x:%d BlockPos.y:%d BlockPos.z:%d BlockType:%d BlockNuber:%d\n", (int)CBlock::GetSelectBlock()->GetPos().x, (int)CBlock::GetSelectBlock()->GetPos().y, (int)CBlock::GetSelectBlock()->GetPos().z, (int)CBlock::GetSelectBlock()->GetType(), CBlock::GetSelectBlock()->GetNumber());

#ifndef _DEBUG
		rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };

		wsprintf(str, "BlockPos.x:%d BlockPos.y:%d BlockPos.z:%d BlockType:%d BlockNuber:%d\n", (int)CBlock::GetSelectBlock()->GetPos().x, (int)CBlock::GetSelectBlock()->GetPos().y, (int)CBlock::GetSelectBlock()->GetPos().z, (int)CBlock::GetSelectBlock()->GetType(), CBlock::GetSelectBlock()->GetNumber());
#endif

		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

void CRenderer::DrawEnemyPos(void) {
	if (CEnemy::GetSelectEnemy() != NULL) {
		char str[BYTE];

		RECT rect = { 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT };

		wsprintf(str, "EnemyPos.x:%d EnemyPos.y:%d EnemyPos.z:%d EnemyType:%d EnemyNumber:%d\n", (int)CEnemy::GetSelectEnemy()->GetPos().x, (int)CEnemy::GetSelectEnemy()->GetPos().y, (int)CEnemy::GetSelectEnemy()->GetPos().z, (int)CEnemy::GetSelectEnemy()->GetType(), CEnemy::GetSelectEnemy()->GetNumber());

#ifndef _DEBUG
		rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };

		wsprintf(str, "EnemyPos.x:%d EnemyPos.y:%d EnemyPos.z:%d EnemyType:%d EnemyNumber:%d\n", (int)CEnemy::GetSelectEnemy()->GetPos().x, (int)CEnemy::GetSelectEnemy()->GetPos().y, (int)CEnemy::GetSelectEnemy()->GetPos().z, (int)CEnemy::GetSelectEnemy()->GetType(), CEnemy::GetSelectEnemy()->GetNumber());

#endif

		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

void CRenderer::DrawCursorPos(void) {
	RECT rect = { 0, 60, SCREEN_WIDTH, SCREEN_HEIGHT };
#ifndef _DEBUG
	rect = { 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT };
#endif
	char str[BYTE];

	wsprintf(str, "Cursor.x:%d Cursor.y:%d Cursor.z:%d\n", (int)CEffect3D::GetPos().x, (int)CEffect3D::GetPos().y, (int)CEffect3D::GetPos().z);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

void CRenderer::DrawCopyDate(void) {
	if (CCreateStage::GetCopynType() >= 0) {
		RECT rect = { 0, 80, SCREEN_WIDTH, SCREEN_HEIGHT };
#ifndef _DEBUG
		rect = { 0, 60, SCREEN_WIDTH, SCREEN_HEIGHT };
#endif
		char str001[BYTE];
		char str002[BYTE];

		switch (CCreateStage::GetCreateObject()) {
		case CCreateStage::CREATEOBJECT_STAGE:
			wsprintf(str002, "Stage\n");

			wsprintf(str001, "Copypos.y:%d CopyRot.x:%d CopyRot.y:%d CopyRot.z:%d CopynName:%s ObjectType:%s\n", (int)CCreateStage::GetCopyPos().y, (int)D3DXToDegree(CCreateStage::GetCopyPosR().x), (int)D3DXToDegree(CCreateStage::GetCopyPosR().y), (int)D3DXToDegree(CCreateStage::GetCopyPosR().z), CBlock::GetBlockData(CCreateStage::GetCopyType()).DrawName, str002);
			break;
		case CCreateStage::CREATEOBJECT_ENEMY:
			wsprintf(str002, "Enemy\n");

			wsprintf(str001, "Copypos.y:%d CopyRot.x:%d CopyRot.y:%d CopyRot.z:%d CopynName:%s ObjectType:%s\n", (int)CCreateStage::GetCopyPos().y, (int)D3DXToDegree(CCreateStage::GetCopyPosR().x), (int)D3DXToDegree(CCreateStage::GetCopyPosR().y), (int)D3DXToDegree(CCreateStage::GetCopyPosR().z), CEnemy::GetEnemyData(CCreateStage::GetCopyType()).DrawName, str002);
			break;
		}

		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str001, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

void CRenderer::DrawFixedSshaft(void) {
	RECT rect = { 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
#ifndef _DEBUG
	rect = { 0, 80, SCREEN_WIDTH, SCREEN_HEIGHT };
#endif
	char str[BYTE];

	wsprintf(str, "x���Œ�:%s, z���Œ�:%s", CCreateStage::GetFixedSshaft(0) ? "true" : "false", CCreateStage::GetFixedSshaft(1) ? "true" : "false");

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

void CRenderer::DrawGreaseJudge(void) {
	RECT rect = { 0, 120, SCREEN_WIDTH, SCREEN_HEIGHT };
#ifndef _DEBUG
	rect = { 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
#endif
	char str[BYTE];

	wsprintf(str, "�O���b�h:%s", CCreateStage::GetGreaseJudge() ? "true" : "false");

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

void CRenderer::DrawSeveMapJudge(void) {
	if (m_nSaveMapJudgeTime >= 0) {
		if (CCreateStage::GetPushedControlS() == true) {
			RECT rect = { 0, 140, SCREEN_WIDTH, SCREEN_HEIGHT };
#ifndef _DEBUG
			rect = { 0, 120, SCREEN_WIDTH, SCREEN_HEIGHT };
#endif
			char str[256];

			if (CCreateStage::GetSaveJudge() != true) {
				wsprintf(str, "%s", "�e�L�X�g�t�@�C�����J���Ȃ����A\n�I�u�W�F�N�g���ݒu����Ă��܂���");
			}
			if (CCreateStage::GetSaveJudge() == true) {
				wsprintf(str, "%s", "�e�L�X�g�t�@�C���ւ̏o�͂ɐ������܂���");
			}

			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			m_nSaveMapJudgeTime--;

			if (m_nSaveMapJudgeTime <= 0) {
				m_nSaveMapJudgeTime = 120;
				CCreateStage::SetSaveJudge(false);
				CCreateStage::SetPushedControlS(false);
			}
		}
	}
}

void CRenderer::DrawObjectSaveDate(void) {
	if (m_nBlockSaveDateJudgeTime >= 0) {
		if (CCreateStage::GetWriteSaveDetaJudge() == true) {
			RECT rect = { 0, 140, SCREEN_WIDTH, SCREEN_HEIGHT };
			if (CCreateStage::GetSaveJudge() == true) {
				rect = { 0, 160, SCREEN_WIDTH, SCREEN_HEIGHT };
			}
			else {
				rect = { 0, 140, SCREEN_WIDTH, SCREEN_HEIGHT };
			}
#ifndef _DEBUG
			if (CCreateStage::GetSaveJudge() == true) {
				rect = { 0, 140, SCREEN_WIDTH, SCREEN_HEIGHT };
			}
			else {
				rect = { 0, 120, SCREEN_WIDTH, SCREEN_HEIGHT };
			}
#endif

			char str[256];

			wsprintf(str, "%s", "�ύX���e��debug.txt�ɏo�͂��܂���");

			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			m_nBlockSaveDateJudgeTime--;

			if (m_nBlockSaveDateJudgeTime <= 0) {
				m_nBlockSaveDateJudgeTime = 120;
				CCreateStage::SetWriteSaveDataJudge(false);
			}
		}
	}
}

void CRenderer::DrawCreateObjectType(void) {
	RECT rect = { SCREEN_WIDTH / 2 - 20, 20, SCREEN_WIDTH, SCREEN_HEIGHT };

	char str[BYTE];

	switch (CCreateStage::GetCreateObject()) {
	case CCreateStage::CREATEOBJECT_STAGE:
		wsprintf(str, "StageCreateNow\n");
		break;
	case CCreateStage::CREATEOBJECT_ENEMY:
		wsprintf(str, "EnemyCreateNow\n");
		break;
	}

	if (str != NULL) {
		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

void CRenderer::DrawPauseJudge(void) {
	RECT rect = { SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 20, SCREEN_WIDTH, SCREEN_HEIGHT };

	char str[BYTE];

	if (CCreateStage::GetPauseJudge() == true) {
		wsprintf(str, "Pause Now\n");

		// �e�L�X�g�`��
		m_pPauseFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}