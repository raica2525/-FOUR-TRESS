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
        BindModelData(57);
        break;
    case TYPE_NORMAL_GATE:
        m_bBreak = true;
        BindModelData(1);
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

    // �g�p�t���O���Ȃ��Ȃ��������
    if (!m_bUse)
    {
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
void CBlock::TakeDamage(bool bBreakGoalGate)
{
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
                // ���U���g�Ɉڍs
                CFade::SetFade(CManager::MODE_RESULT);
                m_bUse = false;
            }
        }
        else if (m_type == TYPE_NORMAL_GATE)
        {
            if (bBreakGoalGate)
            {
                m_bUse = false;
            }
        }
        else
        {
            m_bUse = false;
        }
    }
}