//===============================================
//
// ���f���G�t�F�N�g�̏��� (modelEffect.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "modelEffect.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CModelEffect::CModelEffect() :CScene3D(CScene::OBJTYPE_MODEL_EFFECT)
{
    m_nModelType = 0;
    m_col = SCENE3D_EMISSIVE_COLOR;
    m_colChangeRate = DEFAULT_COLOR_NONE;
    m_bUseLight = true;

    m_bUseDraw = true;
    m_bUseAdditiveSynthesis = false;

    m_bShootUp = false;
    m_move = DEFAULT_VECTOR;
    m_rotMove = DEFAULT_VECTOR;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CModelEffect::~CModelEffect()
{

}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CModelEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene3D::Init(pos, size);

    // �X�P�[����ݒ�
    SetScale(size);

    // ���f���f�[�^���o�C���h
    BindModelData(m_nModelType);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CModelEffect::Uninit(void)
{
    CScene3D::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CModelEffect::Update(void)
{
    m_col += m_colChangeRate;

    // �ł��グ����
    if (m_bShootUp)
    {
        D3DXVECTOR3 pos = GetPos();
        D3DXVECTOR3 rot = GetRot();
        pos += m_move;
        if (pos.y <= 0.0f)
        {
            pos.y = 0.0f;
            m_move = DEFAULT_VECTOR;
            m_rotMove = DEFAULT_VECTOR;
        }
        else
        {
            rot += m_rotMove;
            m_move.y -= 1.1f;
        }

        // �ݒ�
        SetPos(pos);
        SetRot(rot);
    }

    if (m_col.a < 0.0f)
    {
        Uninit();
    }
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CModelEffect::Draw(void)
{
    if (m_bUseDraw)
    {
        if (m_bUseAdditiveSynthesis)
        {
            CScene3D::SetAdditiveSynthesis();
        }

        CScene3D::Draw(true, m_bUseLight, m_col);
    }
}

//=============================================================================
// �C���X�^���X��������
// Author : �㓡�T�V��
//=============================================================================
CModelEffect * CModelEffect::Create(int nModelType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXCOLOR colChangeRate, bool bUseLight)
{
    // �|�C���^��p��
    CModelEffect *pModelEffect = NULL;

    // �������m��
    pModelEffect = new CModelEffect;

    // ��Ɍ��т��Ă���
    pModelEffect->m_nModelType = nModelType;
    pModelEffect->SetRot(rot);

    // ������
    pModelEffect->Init(pos, DEFAULT_SCALE);

    // ���������т��Ă���
    pModelEffect->m_col = col;
    pModelEffect->m_colChangeRate = colChangeRate;
    pModelEffect->m_bUseLight = bUseLight;

    return pModelEffect;
}

//=============================================================================
// �ł��グ�����̐ݒ�
// Author : �㓡�T�V��
//=============================================================================
void CModelEffect::SetShootUp(D3DXVECTOR2 slidePos)
{
    m_bShootUp = true;
    m_colChangeRate = D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.005f);

    // �ʒu�����炷
    D3DXVECTOR3 myPos = GetPos();
    float fPosX = float(GetRandNum((int)slidePos.x, 0)) - float(GetRandNum((int)slidePos.x, 0));
    float fPosZ = float(GetRandNum((int)slidePos.y, 0)) - float(GetRandNum((int)slidePos.y, 0));
    myPos += D3DXVECTOR3(fPosX, 0.0f, fPosZ);
    SetPos(myPos);

    // �ړ��ʂ��o��
    float fSpeed = float(GetRandNum(5000, 4000)) / 100.0f;
    m_move = D3DXVECTOR3(0.0f, fSpeed, 0.0f);

    // ��]�̑��������߂�
    float fRotSpeedX = float(GetRandNum(1500, 500)) / 100.0f - float(GetRandNum(1500, 500)) / 100.0f;
    float fRotSpeedY = float(GetRandNum(1500, 500)) / 100.0f - float(GetRandNum(1500, 500)) / 100.0f;
    float fRotSpeedZ = float(GetRandNum(1500, 500)) / 100.0f - float(GetRandNum(1500, 500)) / 100.0f;
    m_rotMove = D3DXVECTOR3(D3DXToRadian(fRotSpeedX), D3DXToRadian(fRotSpeedY), D3DXToRadian(fRotSpeedZ));
}