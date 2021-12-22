//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �㓡�T�V��
//
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "debug.h"
#include "effect2d.h"
#include "effectData.h"
#include "ranking2.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �����L���O�̃R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// �����L���O�̃f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CRanking::Init(void)
{
    // UI�𐶐�
    CUI::Place(CUI::SET_RANKING);

    // �����L���O�𐶐�
    CRanking2::Create(RANKING2_FIRST_POS, RANKING2_CREATE_SCORE_SIZE);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CRanking::Uninit(void)
{
    // BGM���~
    CManager::SoundStop(CSound::LABEL_BGM_RESULT);
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CRanking::Update(void)
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
        // �^�C�g����ʂɈڍs
        CManager::SoundPlay(CSound::LABEL_SE_OK);
        CFade::SetFade(CManager::MODE_TITLE);
    }
}
