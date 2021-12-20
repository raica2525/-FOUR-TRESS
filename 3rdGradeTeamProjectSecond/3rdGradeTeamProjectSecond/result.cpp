//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �㓡�T�V��
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "game.h"
#include "debug.h"
#include "camera.h"
#include "effect2d.h"
#include "effectData.h"
#include "number_array.h"

//========================================
// �}�N����`
//========================================

//=============================================================================
// ���U���g�̃R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CResult::CResult()
{

}

//=============================================================================
// ���U���g�̃f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CResult::Init(void)
{
    // UI�𐶐�
    CUI::Place(CUI::SET_RESULT);

    // �v���x��\��
    float fDigitY = 0.0f;
    for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
    {
        CGame::INFO_IN_RESULT infoInResult = CGame::GetInfoInResult(nCntPlayer);
        CNumberArray::Create(12, D3DXVECTOR3(640.0f, 175.0f + fDigitY, 0.0f), NUMBER_SIZE_X_RESULT_CONTRIBUTION, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), infoInResult.nContributionPoint, false);

        fDigitY += 100.0f;
    }

    //// �v���C���[����
    //for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
    //{
    //    switch (nCntPlayer)
    //    {
    //    case CPlayer::RANK_1:
    //        CPlayer::CreateInResult(D3DXVECTOR3(250.0f, 200.0f, -1200.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_1);
    //        break;
    //    case CPlayer::RANK_2:
    //        CPlayer::CreateInResult(D3DXVECTOR3(-640.0f, 100.0f, -600.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_2);
    //        break;
    //    case CPlayer::RANK_3:
    //        CPlayer::CreateInResult(D3DXVECTOR3(-325.0f, 25.0f, -310.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_3);
    //        break;
    //    case CPlayer::RANK_4:
    //        CPlayer::CreateInResult(D3DXVECTOR3(125.0f, -40.0f, -100.0f), DEFAULT_VECTOR, CGame::GetPlayerRank(nCntPlayer), CPlayer::RANK_4);
    //        break;
    //    }
    //}

    // �J�����̃��b�N�I���ꏊ��ς���
    CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_CUSTOM);

    // BGM���Đ�
    CManager::SoundPlay(CSound::LABEL_BGM_RESULT);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CResult::Uninit(void)
{
    // BGM���~
    CManager::SoundStop(CSound::LABEL_BGM_RESULT);
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CResult::Update(void)
{
    // �ϐ��錾
    const float ANGLE_ADJUST = 90.0f;   // ���v�ł���0��0�x�̎��ɍ��킹��i2D�|���S���̒��_��Z�Ŏw�肵�Ă��邩��j
    const float POS_Y_ADJUST = 50.0f;
    const int RAND_X = 1380;
    const float BASE_ANGLE = 67.5f;
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    CEffectData::TYPE effectType = CEffectData::TYPE_KAMI;

    // �ʒu�����߂�
    pos.y = -POS_Y_ADJUST;
    pos.x = float(rand() % RAND_X);
    fAngle = D3DXToRadian(180.0f) + BASE_ANGLE - ANGLE_ADJUST;

    // �����ᐶ��
    CEffect2D *pKami = CEffect2D::Create(effectType, pos, fAngle);
    float fRed = (float)GetRandNum(100, 0) / 100.0f;
    float fGreen = (float)GetRandNum(100, 0) / 100.0f;
    float fBlue = (float)GetRandNum(100, 0) / 100.0f;
    pKami->CEffect2D::SetCol(D3DXCOLOR(fRed, fGreen, fBlue, 1.0f));

    // �G���^�[�A�܂��͉����{�^������������
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	bool bPressedAnyButtons = false;
	for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
	{
		if (pInputJoypad->GetJoypadTrigger(nCount, XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_Y | XINPUT_GAMEPAD_START, CInputJoypad::BEHAVIOR_OR))
		{
			bPressedAnyButtons = true;
			break;
		}
	}
    if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || bPressedAnyButtons)
    {
        // ���Ƀ^�C�g����ʂɈڍs
        CManager::SoundPlay(CSound::LABEL_SE_OK);
        CFade::SetFade(CManager::MODE_TITLE);
    }
}