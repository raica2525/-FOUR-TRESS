//======================================================================================
//
// �u���b�N���� (block.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "effect3d.h"
#include "modelEffect.h"
#include "debug.h"
#include "enemy.h"
#include "fortress.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CBlock::CBlock() :CScene3D(CScene::OBJTYPE_BLOCK)
{
    m_type = TYPE_FRAME;
    m_collisionSize = DEFAULT_VECTOR;
    
    m_bBreak = false;
    m_bUse = true;

    m_pModelEffect = NULL;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ŗL�̏������߂�
    switch (m_type)
    {
    case TYPE_FRAME:
        m_bBreak = false;
        BindModelData(1);
        break;
    case TYPE_GOAL_GATE:
        m_bBreak = true;
        BindModelData(34);
        m_pModelEffect = CModelEffect::Create(33, pos + D3DXVECTOR3(0.0f, 900.0f, 0.0f));
        break;
    case TYPE_NORMAL_GATE:
        m_bBreak = true;
        BindModelData(35);
        break;
    }

    // ������
    CScene3D::Init(pos, size);

    // �X�P�[����ݒ�
    SetScale(size);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CBlock::Uninit(void)
{
    // ���f���G�t�F�N�g���g���Ă������̂́A�����t���O�𗧂Ă�i�A���t�@�l��0���������������������p�j
    if (m_pModelEffect)
    {
        m_pModelEffect->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f));
    }

    CScene3D::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CBlock::Update(void)
{
#ifdef COLLISION_TEST
    CDebug::Create(GetPos(), m_collisionSize, CDebug::TYPE_MOMENT, 1);
#endif // COLLISION_TEST

    // ��ނɂ���Ă̏���
    switch (m_type)
    {
    case TYPE_GOAL_GATE:
    {
        D3DXVECTOR3 rot = m_pModelEffect->GetRot();
        rot.y += D3DXToRadian(1.0f);
        if (rot.y > D3DX_PI)
        {
            rot.y -= D3DX_PI * 2.0f;
        }
        else if (rot.y < -D3DX_PI)
        {
            rot.y += D3DX_PI * 2.0f;
        }
        rot.x += D3DXToRadian(1.0f);
        if (rot.x > D3DX_PI)
        {
            rot.x -= D3DX_PI * 2.0f;
        }
        else if (rot.x < -D3DX_PI)
        {
            rot.x += D3DX_PI * 2.0f;
        }
        m_pModelEffect->SetRot(rot);
        break;
    }
    }

    // �g�p�t���O���Ȃ��Ȃ��������
    if (!m_bUse)
    {
        // ��ނɂ���Ă̏���
        switch (m_type)
        {
        case TYPE_NORMAL_GATE:
        {
            D3DXVECTOR3 pos = GetPos();
            for (int nCnt = 0; nCnt < 10; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(75, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            for (int nCnt = 0; nCnt < 5; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(76, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            for (int nCnt = 0; nCnt < 15; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(77, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            break;
        }
        case TYPE_GOAL_GATE:
        {
            D3DXVECTOR3 pos = GetPos();
            for (int nCnt = 0; nCnt < 5; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(78, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            for (int nCnt = 0; nCnt < 15; nCnt++)
            {
                CModelEffect *pModel = CModelEffect::Create(77, pos);
                pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            }
            CModelEffect *pModel = CModelEffect::Create(33, pos);
            pModel->SetShootUp(D3DXVECTOR2(m_collisionSize.x, m_collisionSize.z));
            break;
        }
        }

        Uninit();
    }
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CBlock::Draw(void)
{
    CScene3D::Draw();
}

//=============================================================================
// ��������
// Author : �㓡�T�V��
//=============================================================================
CBlock *CBlock::Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 collisionSize, D3DXVECTOR3 rot)
{
    // �������m��
    CBlock *pBlock = NULL;
    pBlock = new CBlock;

    // ��Ɍ��т��Ă���
    pBlock->m_type = type;
    pBlock->SetRot(rot);

    // ������
    pBlock->Init(pos, DEFAULT_SCALE);

    // ���������т��Ă���
    pBlock->m_collisionSize = collisionSize;

    return pBlock;
}

//=============================================================================
// �_���[�W���󂯂鏈���i�����̊֐��S�������������A�u�Q�[�g��j��ł���͓̂d���C�̂݁v�j
// Author : �㓡�T�V��
//=============================================================================
bool CBlock::TakeDamage(bool bBreakGoalGate)
{
    bool bBreak = false;

    // ����u���b�N�Ȃ�
    if (m_bBreak)
    {
        // �S�[���Q�[�g�Ȃ�A�S�[���Q�[�g��j��ł���U���ł̂ݔj�󂳂��
        if (m_type == TYPE_GOAL_GATE)
        {
            // �����ɁA�ړ��v�ǂ�����Ă����ۂ�return����������
            // �����m�̍ۂɔj��ł��Ȃ��悤��

            if (bBreakGoalGate)
            {
                // ������Ԃ�
                CGame::SetFinish(true);
                m_bUse = false;
                bBreak = true;
            }
        }
        else if (m_type == TYPE_NORMAL_GATE)
        {
            if (bBreakGoalGate)
            {
                m_bUse = false;
                bBreak = true;
            }
        }
        else
        {
            m_bUse = false;
            bBreak = true;
        }
    }

    return bBreak;
}