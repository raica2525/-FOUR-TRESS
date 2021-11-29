//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : �㓡�T�V��
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "game.h"
#include "debug.h"
#include "effect2d.h"
#include "file_manager.h"

//=============================================================================
// �^�C�g���̃R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CTitle::CTitle()
{
    m_nCntTime = 0;
    m_bEmitWingEffect = true;
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CTitle::Init(void)
{
    // �}�E�X�J�[�\���̕\��(�O�̂���)
    ShowCursor(TRUE);

    // �t�@�C���̓ǂݍ���
    CFile_Manager::GetInstance()->CFile_Manager::Read();

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CTitle::Uninit(void)
{

}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CTitle::Update(void)
{

}

//=============================================================================
// ��ʂ̏ォ���ɉ����o������
// Author : �㓡�T�V��
//=============================================================================
void CTitle::EmitFire(FIRE_POS firePos)
{
    // �ϐ��錾
    const float ANGLE_ADJUST = 90.0f;   // ���v�ł���0��0�x�̎��ɍ��킹��i2D�|���S���̒��_��Z�Ŏw�肵�Ă��邩��j
    const float POS_Y_ADJUST = 50.0f;
    const int RAND_X = 1380;
    const float BASE_ANGLE = 67.5f;
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    CEffectData::TYPE effectType = CEffectData::TYPE_TITLE_FIRE_RED;

    // �ʒu�ƌ����ƐF�����߂�
    switch (firePos)
    {
    case FIRE_POS_UP:
        pos.y = -POS_Y_ADJUST;
        pos.x = float(rand() % RAND_X);
        fAngle = D3DXToRadian(180.0f) + BASE_ANGLE - ANGLE_ADJUST;
        effectType = CEffectData::TYPE_TITLE_FIRE_BLUE;
        break;
    case FIRE_POS_DOWN:
        pos.y = SCREEN_HEIGHT + POS_Y_ADJUST;
        pos.x = float(rand() % RAND_X) - float(RAND_X - SCREEN_WIDTH);
        fAngle = BASE_ANGLE - ANGLE_ADJUST;
        effectType = CEffectData::TYPE_TITLE_FIRE_RED;
        break;
    }

    // ������
    CEffect2D::Create(effectType, pos, fAngle);
}
