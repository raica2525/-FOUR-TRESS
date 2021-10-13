//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �㓡�T�V��
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "manager.h"
#include "camera.h"
#include "fade.h"
#include "block.h"
#include "input.h"
#include "scene.h"
#include "library.h"
#include "effect3d.h"
#include "field.h"
#include "CreateStage.h"

//========================================
// �}�N����`
//========================================

// �X�e�[�W�̃u���b�N��
#define MAX_BLOCK 256

// �X�^�[�g�ŃQ�[����Ԃ̊Ǘ�
#define START_ATTACK 210    // ��U�̍U���J�n

// �A�j���[�V�����ŃQ�[����Ԃ̊Ǘ�
#define ANIM_SET_CAMERA 2   // �J�����Z�b�g
#define ANIM_START 60       // �A�j���[�V�����X�^�[�g
#define ANIM_DAMAGE 150     // �_���[�W�v�Z�A���o
#define ANIM_END 240        // �A�j���[�V�����I��

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CCharacter *CGame::m_pCharacter = {};

bool CGame::m_bFinishBattle = false;

CGame::STATE CGame::m_state = STATE_CREATESTAGE;

CGame::STAGEDATE m_aStageDate[MAX_BLOCK] = {};

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{
    m_nCntGameTime = 0;
    m_nCntFinishGame = 0;

    m_pCharacter = NULL;

    // �ÓI�����o�ϐ���������
    m_bFinishBattle = false;
    m_state = STATE_CREATESTAGE;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
    // �u���b�N
	CCreateStage::LoadStage();
	// �G
	CCreateStage::LoadEnemy();

    // �t�B�[���h�̐���
    CField::Create();

    // �J�����̃��b�N�I���ꏊ
    CCamera::SetCameraLookAt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void) {

}