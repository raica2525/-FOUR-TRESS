//===============================================
//
// �G�t�F�N�g�c�[������ (effecttool.cpp)
// Author : �ɓ��z��
//
//===============================================

//===============================================
// �C���N���[�h�t�@�C��
//===============================================
#include "effecttool.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "renderer.h"
#include "manager.h"
#include "effect3d.h"
#include "effectData.h"
#include "camera.h"
#include "mouse.h"
#include "grid.h"
#include <array>

//================================================
// �}�N����`
//================================================
#define SPEED_MAX (2000)				// ���x�̍ő�l
#define ACCELERATION_MAX (1.0f)			// �����x�̍ő�l
#define GRAVITY_MAX (100.0f)			// �d�͂̍ő�l
#define COLCHANGERATE_MAX (1.0f)		// �F�ω������̍ő�l
#define FADEOUTRATE_MAX (1.0f)			// �t�F�[�h�A�E�g�̊����̍ő�l
#define EFFECT_SIZE_MAX (50000)			// �T�C�Y�̍ő�l
#define EFFECT_SIZE_MIN (0)				// �T�C�Y�̍ŏ��l
#define SIZECHANGERATE_MAX (2000.0f)	// �T�C�Y�̊g��/�k�������ő�l
#define SIZECHANGERATE_MIN (-2000.0f)	// �T�C�Y�̊g��/�k�������ŏ��l
#define ALPHATEST_MAX (255)				// �A���t�@�e�X�g�̍ő�l
#define IMGUI_BAR_WIDTH_INIT (215.0f)	// IMGUI�̃o�[�̉����̏����l
#define IMGUI_BAR_WIDTH_MAX (1000.0f)	// IMGUI�̃o�[�̉����̍ő�l
#define CREATE_FLAME_MAX (240.0f)		// ��������t���[���̍ő�l
#define INT_ZERO (0)					// int�̏����l
#define FLOAT_ZERO (0.0f)				// float�̏����l

//===============================================
// �R���X�g���N�^
//===============================================
CEffectTool::CEffectTool()
{
	m_EffectInfo = InitEffectInfo();					// �G�t�F�N�g�̏��̏�����
	m_nEffectNum = 0;									// �G�t�F�N�g�̃^�C�v
	m_fCreateFlame = 0.0f;								// �G�t�F�N�g�𐶐����鎞��
	m_fCountFlame = 0.0f;								// �G�t�F�N�g�𐶐����鎞�Ԃ̃J�E���g
	m_fBarWidth = IMGUI_BAR_WIDTH_INIT;					// IMGUI�̃o�[�̉���
	memset(m_bCreate, false, sizeof(m_bCreate));		// �������邩���Ȃ���
	m_bRandamCreate = false;								// �����_���Ő��������邩
	memset(m_RandomRangePos, false, sizeof(m_RandomRangePos));	// �����_���Ȕ͈͂Ő�������Ƃ��̍��W
}

//===============================================
// �f�X�g���N�^
//===============================================
CEffectTool::~CEffectTool()
{

}

//===============================================
// ����������
//===============================================
HRESULT CEffectTool::Init(HWND hWnd)
{
	// �G�t�F�N�g�̃f�[�^����l���Z�b�g
	SetEffectInfo(m_nEffectNum);

	// imgui�̃Z�b�g�A�b�v
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// �t�H���g�̓ǂݍ���
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("Data/fonts/meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	// imgui�̃X�^�C��
	ImGui::StyleColorsClassic();

	// imgui�̏���������
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEffectTool::Uninit(void)
{		
	m_EffectInfo = InitEffectInfo();					// �G�t�F�N�g�̏��̏�����

	m_nEffectNum = 0;									// �G�t�F�N�g�̃^�C�v
	m_fCreateFlame = 0.0f;								// �G�t�F�N�g�𐶐����鎞��
	m_fCountFlame = 0.0f;								// �G�t�F�N�g�𐶐����鎞�Ԃ̃J�E���g
	m_fBarWidth = 0.0f;									// IMGUI�̃o�[�̉���
	memset(m_bCreate, false, sizeof(m_bCreate));		// �������邩���Ȃ���
	m_bRandamCreate = false;								// �����_���Ő��������邩
	memset(m_RandomRangePos, false, sizeof(m_RandomRangePos));	// �����_���Ȕ͈͂Ő�������Ƃ��̍��W

	// imgui�̃V���b�g�_�E��
	ImGui_ImplDX9_Shutdown();
}

//===============================================
// �X�V����
//===============================================
void CEffectTool::Update(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �G�t�F�N�g�pImgui�̍X�V����
	UpdateEffectImgui();

	// �I�v�V�����pImgui�̍X�V����
	UpdateOptionImgui();

	ImGui::EndFrame(); //�X�V�����̏I����
}

//===============================================
// �`�揈��
//===============================================
void CEffectTool::Draw(void)
{
	// imgui�̕`�揈��
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//===============================================
// �G�t�F�N�g�c�[���̏�����C�ɏ��������鏈��
//===============================================
CEffectTool::EffectInfo CEffectTool::InitEffectInfo(void)
{
	EffectInfo Effectinfo;
	memset(Effectinfo.pos, NULL, sizeof(Effectinfo.pos));							// ���W

	Effectinfo.nTexType = 0;														// �g���e�N�X�`���̎��
	Effectinfo.nNumOnce = 0;														// ����������
	Effectinfo.nPlane = 0;															// ����

	Effectinfo.bOnCircleEdge = false;												// �~����ɂ��邩�ǂ����i�ő���o���a�����ƂɁj
	Effectinfo.bEmitVectorInside = false;											// ���o����������ɂ��邩�ǂ���
	Effectinfo.nScatterAngle = 0;													// ��U�p�x�i0�`314�j
	Effectinfo.nScatterWidth = 0;													// ��U���i0�`314�j
	Effectinfo.fEmitRadius = 0.0f;													// ���a�̑傫��

	Effectinfo.nSpeedMax = 0;														// �ő呬�x
	Effectinfo.nSpeedMin = 0;														// �ŏ����x
	Effectinfo.nAuxiliaryAxisSpeedMax = 0;											// �ő�⏕���i2D��3D�ŁA���̊����o�����߂̂��́j
	Effectinfo.nAuxiliaryAxisSpeedMin = 0;											// �ŏ��⏕���i2D��3D�ŁA���̊����o�����߂̂��́j

	Effectinfo.fAcceleration = 0.0f;												// �����x(1.0�ő�)
	Effectinfo.fGravity = 0.0f;														// �d��
	Effectinfo.fGravityLimit = 0.0f;												// �d�͐���

	Effectinfo.nLayRot = 0;															// �|���S�����̂��̂����ɂ��邩�ǂ����itrue�Ȃ�r���{�[�h�����j
	Effectinfo.nRotSpeedMax = 0;													// �ő��]���x
	Effectinfo.nRotSpeedMin = 0;													// �ŏ���]���x

	memset(&Effectinfo.col, NULL, sizeof(Effectinfo.col));							// �F
	memset(&Effectinfo.colChangeRate, NULL, sizeof(Effectinfo.colChangeRate));		// �F�ω�����
	Effectinfo.fFadeOutRate = 0.0f;													// �t�F�[�h�A�E�g�̊���
	Effectinfo.nCntFadeOutLock = 0;													// ���l�̕ω������b�N����J�E���^

	Effectinfo.nSizeMax = 0;														// �ő�傫��
	Effectinfo.nSizeMin = 0;														// �ŏ��傫��
	memset(Effectinfo.fSizeChangeRate, NULL, sizeof(Effectinfo.fSizeChangeRate));	// �g��/�k������	
	Effectinfo.nCntSizeChangeLock = 0;												// �傫�������b�N����J�E���^
	Effectinfo.bSizeChangeStartOrFinish = false;									// �傫����ς���̂��n�܂邩�A�I���̂�

	Effectinfo.bUseAdditiveSynthesis = false;										// ���Z�������邩�ǂ���
	Effectinfo.bUseZBuffer = false;													// Z�o�b�t�@���g����
	Effectinfo.nAlphaTestBorder = 0;												// ���e�X�g�̃{�[�_�[

	return Effectinfo;
}

//===============================================
// �G�t�F�N�g�pImgui�̍X�V����
//===============================================
void CEffectTool::UpdateEffectImgui(void)
{
	int nEffectType = m_nEffectNum;

	// �o�[�̉���
	ImGui::PushItemWidth(m_fBarWidth);

	// �G�t�F�N�g�̏����f�[�^����󂯎��
	SetEffectInfo(m_nEffectNum);

	// �E�B���h�E���o���ʒu�̐ݒ�
	ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 300), ImGuiCond_Once);
	ImGui::Begin(u8"�G�t�F�N�g�c�[��");

	// ���W�Ɋւ���ݒ�
	ImguiEffectPos();

	// �G�t�F�N�g�Ɋւ���ݒ�
	ImguiEffectOption();

	// �ړ��Ɋւ���ݒ�
	ImguiEffectMove();

	// ��]�Ɋւ���ݒ�
	ImguiEffectRot();

	// �F�Ɋւ���ݒ�
	ImguiEffectCol();

	// �T�C�Y�Ɋւ���ݒ�
	ImguiEffectSize();

	// �`��Ɋւ���ݒ�
	ImguiEffectDraw();

	// �G�t�F�N�g�̐����Ɋւ���ݒ�
	ImguiEffectCreate();

	// �G�t�F�N�g�̐���
	EffectCreate();
	CCamera * pCamera = CManager::GetCamera();

	ImGui::Text(u8"CameraDistance�F%.1f", pCamera->GetDistance());
	ImGui::Text(u8"CameraPhi�F%.3f", pCamera->GetPhi());
	ImGui::Text(u8"CameraTheta�F%.3f", pCamera->GetTheta());


	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	// �G�t�F�N�g�̃^�C�v���ύX����Ă���
	if (nEffectType != m_nEffectNum)
	{
		// �G�t�F�N�g�̏����f�[�^����󂯎��
		SetEffectInfo(m_nEffectNum);
	}

	// �X�V�����l���f�[�^�ɃZ�b�g����
	CManager::GetEffectData()->SetCreateInfo(m_nEffectNum);
}

//===============================================
// �I�v�V�����pImgui�̍X�V����
//===============================================
void CEffectTool::UpdateOptionImgui(void)
{
	// �E�B���h�E���o���ʒu�̐ݒ�
	ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 + 100), ImGuiCond_Once);
	ImGui::Begin(u8"�I�v�V����");

	// �O���b�h�̐ݒ�
	if (ImGui::CollapsingHeader("grid"))
	{
		CScene* pScene = CScene::GetTopScene(CScene::OBJTYPE_GRID);
		for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_GRID); nCntScene++)
		{
			// ���g������Ȃ�
			if (pScene != NULL)
			{
				// ���̃V�[����ۑ�
				CScene*pNextScene = pScene->GetNextScene();

				// �O���b�h�ɃL���X�g
				CGrid *pGrid = (CGrid*)pScene;
				
				ImGui::DragFloat(u8"�O���b�h�̑傫��", &pGrid->GetSize(), 1.0f, -1000.0f, 1000.0f);	// �O���b�h�̃T�C�Y
				ImGui::SameLine(); HelpText(u8"��ӂ̑傫��");

				ImGui::Checkbox(u8"ZX�̕\��", &pGrid->GetbShowLine(0));							// ZX�̐��̕\��
				ImGui::Checkbox(u8"XY�̕\��", &pGrid->GetbShowLine(1));							// XY�̐��̕\��
				ImGui::Checkbox(u8"YZ�̕\��", &pGrid->GetbShowLine(2));							// YZ�̐��̕\��

				// ���̃V�[���ɂ���
				pScene = pNextScene;
			}
			else
			{
				// ���g���Ȃ��Ȃ�A�����ŏ������I����
				break;
			}
		}

	}

	// �}�E�X�̐ݒ�
	if (ImGui::CollapsingHeader("mouse"))
	{
		// �}�E�X�̃|�C���^
		CMouse* pMouse = CManager::GetMouse();
		ImGui::DragFloat(u8"�}�E�X�̊��x", &pMouse->GetMouseSensi(), 0.001f, 0.0f, 1.0f);			// �}�E�X�̊��x
		ImGui::DragFloat(u8"�}�E�X�z�C�[���̊��x", &pMouse->GetWheelSensi(), 0.001f, 0.0f, 1.0f);	// �}�E�X�z�C�[���̊��x

	}

	// �J�����Ɋւ���ݒ�
	ImguiEffectCamera();

	ImGui::End();
}

//===============================================
// ���W�Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectPos(void)
{
	// ���W�Ɋւ���ݒ�
	if (ImGui::CollapsingHeader("pos"))
	{
		ImGui::DragFloat3("Pos", m_EffectInfo.pos, 1.0f, -1000.0f, 1000.0f);			// ���W
		ImGui::DragFloat3("RandomRangePos", m_RandomRangePos, 1.0f, -1000.0f, 1000.0f);	// �����_���ŏo���͈�
		ImGui::SameLine(); HelpText(u8"�����_���ŃG�t�F�N�g�𔭐�������͈�");
		ImGui::Checkbox(u8"�����_���ŏo����", &m_bRandamCreate);							// �����_���ŏo����
		ImGui::SameLine(); HelpText(u8"RandomRangePos�Őݒ肵���͈͓��Ń����_���ɏo��悤�ɂȂ�");
	}
}

//===============================================
// �G�t�F�N�g�Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectOption(void)
{
	if (ImGui::CollapsingHeader("effectoption"))
	{
		// ���{����͍�肽���������ǖ�����������
		//ImGui::InputText(u8"�G�t�F�N�g�̖��O", m_Text, sizeof(m_Text));

		// �^�C�v�̐؂�ւ�
		ImGui::SliderInt(u8"�G�t�F�N�g�̔ԍ�", &m_nEffectNum, INT_ZERO, CEffectData::TYPE::TYPE_MAX - 1);
		ImGui::SameLine(); HelpText(u8"0�`9�܂ł̒l��ύX�������G�t�F�N�g�̔ԍ�");

		// �e�N�X�`���̑I��
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { m_EffectInfo.nTexType--; }
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { m_EffectInfo.nTexType++; }
		// 0�ȉ��ɂȂ�Ȃ��悤��
		if (m_EffectInfo.nTexType < INT_ZERO)
		{
			m_EffectInfo.nTexType = INT_ZERO;
		}
		ImGui::SameLine();
		ImGui::Text("%d", m_EffectInfo.nTexType);
		ImGui::SameLine();
		ImGui::Text(u8"�e�N�X�`���̎��");
		ImGui::SameLine(); HelpText(u8"�e�L�X�g����ǂݍ��񂾃e�N�X�`���̔ԍ�");

		// ������
		ImGui::InputInt(u8"������", &m_EffectInfo.nNumOnce);
		ImGui::SameLine(); HelpText(u8"��x�ɏo����");

		// ��������1���͏��Ȃ��Ȃ�Ȃ�
		if (m_EffectInfo.nNumOnce < 1)
		{
			m_EffectInfo.nNumOnce = 1;
		}

		ImGui::SliderInt(u8"����", &m_EffectInfo.nPlane, INT_ZERO, 1);									// ���ʂ̐؂�ւ�
		ImGui::SameLine(); HelpText(u8"0=XY���ʁA1=XZ����");
		ImGui::Checkbox(u8"�~����ɂ��邩�ǂ���", &m_EffectInfo.bOnCircleEdge);							// �~����ɂ��邩�ǂ����i�ő���o���a�����ƂɁj
		ImGui::SameLine(); HelpText(u8"���a�̑傫�����Q�Ƃ��ĉ~�`��ɃG�t�F�N�g���o����");
		ImGui::Checkbox(u8"���o����������ɂ��邩�ǂ���", &m_EffectInfo.bEmitVectorInside);				// ���o����������ɂ��邩�ǂ���
		ImGui::SameLine(); HelpText(u8"���S�Ɍ������ăG�t�F�N�g���o��悤�ɂȂ�");
		ImGui::DragInt(u8"��U�p�x�i0�`628�j", &m_EffectInfo.nScatterAngle, 1, INT_ZERO, EFFECT_PI);	// ��U�p�x�i0�`628�j
		ImGui::SameLine(); HelpText(u8"��΂��p�x");
		ImGui::DragInt(u8"��U���i0�`628�j", &m_EffectInfo.nScatterWidth, 1, INT_ZERO, EFFECT_PI);		// ��U���i0�`628�j
		ImGui::SameLine(); HelpText(u8"��΂���");
		ImGui::DragFloat(u8"���a�̑傫��", &m_EffectInfo.fEmitRadius, 1.0f, FLOAT_ZERO, 10000.0f);		// ���a�̑傫��
		ImGui::SameLine(); HelpText(u8"���a���Ń����_���ŏo����");
	}
}

//===============================================
// �ړ��Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectMove(void)
{
	if (ImGui::CollapsingHeader("move"))
	{
		ImGui::DragInt(u8"�ő呬�x", &m_EffectInfo.nSpeedMax, 1, m_EffectInfo.nSpeedMin, SPEED_MAX);								// �ő呬�x
		ImGui::SameLine(); HelpText(u8"�ő�̑��x");
		ImGui::DragInt(u8"�ŏ����x", &m_EffectInfo.nSpeedMin, 1, -SPEED_MAX, m_EffectInfo.nSpeedMax);								// �ŏ����x
		ImGui::SameLine(); HelpText(u8"�ŏ��̑��x");
		ImGui::DragInt(u8"�ő�⏕��", &m_EffectInfo.nAuxiliaryAxisSpeedMax, 1, m_EffectInfo.nAuxiliaryAxisSpeedMin, SPEED_MAX);	// �ő�⏕���i2D��3D�ŁA���̊����o�����߂̂��́j
		ImGui::SameLine(); HelpText(u8"2D����3D�ɗ��̊����o���������\n����XY�Ȃ�Z�����ɁA����XZ�Ȃ�Y������");
		ImGui::DragInt(u8"�ŏ��⏕��", &m_EffectInfo.nAuxiliaryAxisSpeedMin, 1, -SPEED_MAX, m_EffectInfo.nAuxiliaryAxisSpeedMax);	// �ŏ��⏕���i2D��3D�ŁA���̊����o�����߂̂��́j
		ImGui::SameLine(); HelpText(u8"2D����3D�ɗ��̊����o���������\n����XY�Ȃ�Z�����ɁA����XZ�Ȃ�Y������");
		ImGui::DragFloat(u8"�����x(1.0�ő�)", &m_EffectInfo.fAcceleration, 0.001f, FLOAT_ZERO, ACCELERATION_MAX);					// �����x(1.0�ő�)
		ImGui::SameLine(); HelpText(u8"1.0����A�ω������邱�Ƃňړ��Ƀ����n�����t�����");
		ImGui::DragFloat(u8"�d��", &m_EffectInfo.fGravity, 0.01f, FLOAT_ZERO, GRAVITY_MAX);											// �d��
		ImGui::SameLine(); HelpText(u8"�d�͂̑傫��");
		ImGui::DragFloat(u8"�d�͐���", &m_EffectInfo.fGravityLimit, 0.01f, FLOAT_ZERO, GRAVITY_MAX);								// �d�͐���
		ImGui::SameLine(); HelpText(u8"�d�͂̑傫�����ݒ肵���l���傫���Ȃ�Ȃ��悤�ɂ���");
	}
}

//===============================================
// ��]�Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectRot(void)
{
	if (ImGui::CollapsingHeader("rot"))
	{
		ImGui::SliderInt(u8"�|���S�����ǂ̕����ɌŒ肷�邩", &m_EffectInfo.nLayRot, INT_ZERO, 4);					// �|���S�����̂��̂��ǂ̕����ɌŒ肷�邩�i1,2,3,4�Ȃ�r���{�[�h�����j
		ImGui::SameLine(); HelpText(u8"0�ȊO�ɂ����ꍇ�|���S���̌������Œ肷��\n1=������A2=�E�����A3=�������A4=������");
		ImGui::Checkbox(u8"��]���ړ��̌����ɍ��킹�邩", &m_EffectInfo.bRotEqualMoveAngle);						// ��]���ړ��̌����ɍ��킹�邩
		ImGui::SameLine(); HelpText(u8"��]���ړ������������ɂ��Ĕ�Ԃ悤�ɂȂ�");
		ImGui::DragInt(u8"�ő��]���x", &m_EffectInfo.nRotSpeedMax, 1, m_EffectInfo.nRotSpeedMin, EFFECT_PI * 2);	// �ő��]���x
		ImGui::SameLine(); HelpText(u8"�ő�̉�]���x");
		ImGui::DragInt(u8"�ŏ���]���x", &m_EffectInfo.nRotSpeedMin, 1, INT_ZERO, m_EffectInfo.nRotSpeedMax);		// �ŏ���]���x
		ImGui::SameLine(); HelpText(u8"�ŏ��̉�]���x");
	}
}

//===============================================
// �F�Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectCol(void)
{
	if (ImGui::CollapsingHeader("col"))
	{
		ImGui::ColorEdit4(u8"�F", m_EffectInfo.col, ImGuiColorEditFlags_Float);											// �F
		ImGui::SameLine(); HelpText(u8"�G�t�F�N�g�̐F");
		ImGui::DragFloat4(u8"�F�ω�����", m_EffectInfo.colChangeRate, 0.001f, -COLCHANGERATE_MAX, COLCHANGERATE_MAX);	// �F�ω�����
		ImGui::SameLine(); HelpText(u8"�ݒ肵���F�̒l�����Z���Ă���");
		ImGui::DragFloat(u8"�t�F�[�h�A�E�g�̊���", &m_EffectInfo.fFadeOutRate, 0.001f, FLOAT_ZERO, FADEOUTRATE_MAX);	// �t�F�[�h�A�E�g�̊���
		ImGui::SameLine(); HelpText(u8"�A���t�@�l�������Ă���");
		ImGui::DragInt(u8"�A���t�@�l�����b�N����J�E���^", &m_EffectInfo.nCntFadeOutLock, 1, INT_ZERO, 1000);			// ���l�̕ω������b�N����J�E���^
		ImGui::SameLine(); HelpText(u8"�ݒ肵���t���[�����߂�����ɃA���t�@�l��������悤�ɂȂ�");
	}
}

//===============================================
// �T�C�Y�Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectSize(void)
{
	if (ImGui::CollapsingHeader("size"))
	{
		ImGui::DragInt(u8"�ő�̑傫��", &m_EffectInfo.nSizeMax, 1, m_EffectInfo.nSizeMin, EFFECT_SIZE_MAX);				// �ő�̑傫��
		ImGui::SameLine(); HelpText(u8"�|���S���̍ő�̑傫��");
		ImGui::DragInt(u8"�ŏ��̑傫��", &m_EffectInfo.nSizeMin, 1, EFFECT_SIZE_MIN, m_EffectInfo.nSizeMax);				// �ŏ��̑傫��
		ImGui::SameLine(); HelpText(u8"�|���S���̍ŏ��̑傫��");
		ImGui::DragFloat3(u8"�g��/�k������", m_EffectInfo.fSizeChangeRate, 0.01f, SIZECHANGERATE_MIN, SIZECHANGERATE_MAX);	// �g��/�k������
		ImGui::SameLine(); HelpText(u8"�ݒ肵���l���T�C�Y�ɉ��Z���Ă���");
		ImGui::DragInt(u8"�傫�������b�N����J�E���^", &m_EffectInfo.nCntSizeChangeLock, 1, EFFECT_SIZE_MIN, 1000);			// �傫�������b�N����J�E���^
		ImGui::SameLine(); HelpText(u8"�ݒ肵���t���[���̌�ɑ傫���̕ω����~�߂���A�I�������ɑ傫�����ς��悤�ɂȂ�");
		ImGui::Checkbox(u8"�傫����ς���̂�", &m_EffectInfo.bSizeChangeStartOrFinish);									// �傫����ς���̂��n�܂肩�A�I��肩
		ImGui::SameLine(); HelpText(u8"�傫����ς���̂��ŏ�����Ȃ�`�F�b�N\n�t���[�����߂����ォ��ς������Ȃ�`�F�b�N���O��");
	}
}

//===============================================
// �`��Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectDraw(void)
{
	if (ImGui::CollapsingHeader("draw"))
	{
		ImGui::Checkbox(u8"���Z�������邩�ǂ���", &m_EffectInfo.bUseAdditiveSynthesis);								// ���Z�������邩�ǂ���
		ImGui::Checkbox(u8"Z�o�b�t�@���g����", &m_EffectInfo.bUseZBuffer);											// Z�o�b�t�@���g����
		ImGui::DragInt(u8"�A���t�@�e�X�g�̃{�[�_�[", &m_EffectInfo.nAlphaTestBorder, 1, INT_ZERO, ALPHATEST_MAX);	// ���e�X�g�̃{�[�_�[
	}
}

//===============================================
// �G�t�F�N�g�̐����Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectCreate(void)
{
	if (ImGui::CollapsingHeader("create"))
	{
		ImGui::DragFloat(u8"��������t���[��", &m_fCreateFlame, 1.0f, FLOAT_ZERO, CREATE_FLAME_MAX);	// ��������t���[��
		ImGui::SameLine(); HelpText(u8"�ݒ肵���t���[���ŃG�t�F�N�g���o��悤�ɂȂ�(�ő�l240)");

		// �G�t�F�N�g�𐶐����邩�ǂ���(for����ł��Ȃ���������Ȃɂ��������@�͂Ȃ����񂩂˂�)
		ImGui::Checkbox(u8"�G�t�F�N�g0", &m_bCreate[0]);
		ImGui::Checkbox(u8"�G�t�F�N�g1", &m_bCreate[1]);
		ImGui::Checkbox(u8"�G�t�F�N�g2", &m_bCreate[2]);
		ImGui::Checkbox(u8"�G�t�F�N�g3", &m_bCreate[3]);
		ImGui::Checkbox(u8"�G�t�F�N�g4", &m_bCreate[4]);
		ImGui::Checkbox(u8"�G�t�F�N�g5", &m_bCreate[5]);
		ImGui::Checkbox(u8"�G�t�F�N�g6", &m_bCreate[6]);
		ImGui::Checkbox(u8"�G�t�F�N�g7", &m_bCreate[7]);
		ImGui::Checkbox(u8"�G�t�F�N�g8", &m_bCreate[8]);
		ImGui::Checkbox(u8"�G�t�F�N�g9", &m_bCreate[9]);

		if (ImGui::Button("upload"))
		{
			CManager::GetEffectData()->UploadEffectInfo(m_bCreate);
		}
		ImGui::SameLine(); HelpText(u8"�`�F�b�N��t�����G�t�F�N�g�̏���effectinfo.txt�ɃA�b�v���[�h����");

		ImGui::SameLine();
		if (ImGui::Button("reload"))
		{
			// �G�t�F�N�g�f�[�^�̃����[�h
			CEffectData* pEffectData = CManager::GetEffectData();
			pEffectData->Init();
			SetEffectInfo(m_nEffectNum);
		}
		ImGui::SameLine(); HelpText(u8"effect.txt�̏��������[�h����");
	}
}

//===============================================
// �J�����Ɋւ���ݒ�
//===============================================
void CEffectTool::ImguiEffectCamera(void)
{
	if (ImGui::CollapsingHeader("camera"))
	{
		if (ImGui::Button("CameraReset"))
		{
			// �J�����̃��Z�b�g
			CManager::GetCamera()->ResetGameCamera();
		}
		ImGui::SameLine(); HelpText(u8"�J�����������ʒu�ɖ߂�");
	}
}

//===============================================
// �G�t�F�N�g�̐���
//===============================================
void CEffectTool::EffectCreate(void)
{
	// �J�E���g���ő�l�𒴂�����
	if (m_fCountFlame > CREATE_FLAME_MAX)
	{
		m_fCountFlame = INT_ZERO;
	}
	else
	{
		// �J�E���g�̉��Z
		m_fCountFlame++;
	}


	// �ݒ肵���t���[���ƃJ�E���g����v������
	if (m_fCreateFlame == m_fCountFlame)
	{
		// �G�t�F�N�g�̐��������擾
		CEffectData *pEffectData = CManager::GetEffectData();

		// �͈͂��烉���_���ɍ��W�����߂�
		D3DXVECTOR3 Randompos = D3DXVECTOR3((float)(rand() % (int)(m_RandomRangePos.x + 1.0f)),
											(float)(rand() % (int)(m_RandomRangePos.y + 1.0f)),
											(float)(rand() % (int)(m_RandomRangePos.z + 1.0f)))
											- m_RandomRangePos / 2.0f;

		for (int nCount = 0; nCount < CEffectData::TYPE::TYPE_MAX; nCount++)
		{
			if (m_bCreate[nCount])
			{
				// �����_���Ŕ��������邩
				if (m_bRandamCreate)
				{
					// �G�t�F�N�g����
					CEffect3D::Emit(nCount, Randompos, pEffectData->GetCreateInfo(nCount)->fEmitRadius);
				}
				else
				{
					// �G�t�F�N�g����
					CEffect3D::Emit(nCount, m_EffectInfo.pos, pEffectData->GetCreateInfo(nCount)->fEmitRadius);
				}
			}
		}
		// �J�E���g�̏�����
		m_fCountFlame = INT_ZERO;
	}
}

//===============================================
// ���ӏ����̏���
//===============================================
void CEffectTool::HelpText(const char* cText)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(cText);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

//===============================================
// �G�t�F�N�g���Z�b�g����
//===============================================
void CEffectTool::SetEffectInfo(int nEffectType)
{
	// �G�t�F�N�g�̐��������擾
	CEffectData *pEffectData = CManager::GetEffectData();
	CEffectData::CreateInfo *pCreateInfo = pEffectData->GetCreateInfo(nEffectType);

	m_EffectInfo.nTexType = pCreateInfo->nTexType;								// �g���e�N�X�`���̎��
	m_EffectInfo.nNumOnce = pCreateInfo->nNumOnce;								// ����������
	m_EffectInfo.nPlane = pCreateInfo->plane;									// ����

	m_EffectInfo.bOnCircleEdge = pCreateInfo->bOnCircleEdge;					// �~����ɂ��邩�ǂ���
	m_EffectInfo.bEmitVectorInside = pCreateInfo->bEmitVectorInside;			// ���o����������ɂ��邩�ǂ���
	m_EffectInfo.nScatterAngle = pCreateInfo->nScatterAngle;					// ��U�p�x�i0�`314�j
	m_EffectInfo.nScatterWidth = pCreateInfo->nScatterWidth;					// ��U���i0�`314�j
	m_EffectInfo.fEmitRadius = pCreateInfo->fEmitRadius;						// ���a�̑傫��

	m_EffectInfo.nSpeedMax = pCreateInfo->nSpeedMax;							// �ő呬�x
	m_EffectInfo.nSpeedMin = pCreateInfo->nSpeedMin;							// �ŏ����x
	m_EffectInfo.nAuxiliaryAxisSpeedMax = pCreateInfo->nAuxiliaryAxisSpeedMax;	// �ő�⏕���i2D��3D�ŁA���̊����o�����߂̂��́j
	m_EffectInfo.nAuxiliaryAxisSpeedMin = pCreateInfo->nAuxiliaryAxisSpeedMin;	// �ŏ��⏕���i2D��3D�ŁA���̊����o�����߂̂��́j

	m_EffectInfo.fAcceleration = pCreateInfo->fAcceleration;					// �����x(1.0�ő�)
	m_EffectInfo.fGravity = pCreateInfo->fGravity;								// �d��
	m_EffectInfo.fGravityLimit = pCreateInfo->fGravityLimit;					// �d�͐���

	m_EffectInfo.nLayRot = pCreateInfo->nLayRot;								// �|���S�����̂��̂����ɂ��邩�ǂ����itrue�Ȃ�r���{�[�h�����j
	m_EffectInfo.bRotEqualMoveAngle = pCreateInfo->bRotEqualMoveAngle;			// ��]���ړ��̌����ɍ��킹�邩
	m_EffectInfo.nRotSpeedMax = pCreateInfo->nRotSpeedMax;						// �ő��]���x
	m_EffectInfo.nRotSpeedMin = pCreateInfo->nRotSpeedMin;						// �ŏ���]���x
																					
	m_EffectInfo.col = pCreateInfo->col;										// �F

	m_EffectInfo.colChangeRate = pCreateInfo->colChangeRate;					// �F�ω�����
	m_EffectInfo.fFadeOutRate = pCreateInfo->fFadeOutRate;						// �t�F�[�h�A�E�g�̊���
	m_EffectInfo.nCntFadeOutLock = pCreateInfo->nCntFadeOutLock;				// ���l�̕ω������b�N����J�E���^

	m_EffectInfo.nSizeMax = pCreateInfo->nSizeMax;									// �ő�傫��
	m_EffectInfo.nSizeMin = pCreateInfo->nSizeMin;									// �ŏ��傫��
	m_EffectInfo.fSizeChangeRate = pCreateInfo->sizeChangeRate;						// �g��/�k������
	m_EffectInfo.nCntSizeChangeLock = pCreateInfo->nCntSizeChangeLock;				// �傫�������b�N����J�E���^
	m_EffectInfo.bSizeChangeStartOrFinish = pCreateInfo->bSizeChangeStartOrFinish;	// �傫����ς���̂��n�܂肩�A�I��肩

	m_EffectInfo.bUseAdditiveSynthesis = pCreateInfo->bUseAdditiveSynthesis;	// ���Z�������邩�ǂ���
	m_EffectInfo.bUseZBuffer = pCreateInfo->bUseZBuffer;						// Z�o�b�t�@���g����
	m_EffectInfo.nAlphaTestBorder = pCreateInfo->nAlphaTestBorder;				// ���e�X�g�̃{�[�_�[
}

//===============================================
// �G�t�F�N�g���擾����
//===============================================
CEffectTool::EffectInfo * CEffectTool::GetEffectInfo(int nEffectType)
{
	return &m_EffectInfo;
}
