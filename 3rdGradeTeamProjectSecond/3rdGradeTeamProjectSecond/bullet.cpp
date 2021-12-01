//======================================================================================
//
// �e���� (bullet.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "bullet.h"
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

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CBullet::CBullet() :CScene3D(CScene::OBJTYPE_BULLET)
{
    m_type = TYPE_ARMY_ATTACK;
    m_collisionSize = D3DXVECTOR2(0.0f, 0.0f);
    m_moveAngle = DEFAULT_VECTOR;
    m_fSpeed = 0.0f;
    m_collisionFlag = COLLISION_FLAG_NONE;

    m_posOld = DEFAULT_VECTOR;
    m_nLife = 0;
    m_fDamage = 0;

    m_bUseCntTime = false;
    m_nCntTime = 0;
    m_bUseDraw = false;

    m_bHitErase = true;
    m_pEffect3d_Shadow = NULL;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
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
void CBullet::Uninit(void)
{
    // �e������
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetDontUse();
    }

    CScene3D::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CBullet::Update(void)
{
    // ���Ԍo�߂𗘗p����e�Ȃ�
    if (m_bUseCntTime)
    {
        m_nCntTime++;
    }

    // �ʒu�A�傫�����擾
    D3DXVECTOR3 myPos = GetPos();

    // 1F�O�̈ʒu�����т���
    m_posOld = myPos;

    // �ړ��ʂ��ʒu�Ɍ��т���
    myPos += m_moveAngle * m_fSpeed;

    // �����蔻���ݒ�
    Collision(myPos);

    // �ʒu��ݒ�
    SetPos(myPos);

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 119);
#endif // COLLISION_TEST

    // �e�̈ʒu���X�V
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(myPos.x, SHADOW_POS_Y, myPos.z));
    }

    // ���C�t���Ȃ��Ȃ����A�܂��͎g�p�t���O���Ȃ��Ȃ�����A����
    m_nLife--;
    if (m_nLife <= 0)
    {
        Uninit();
    }
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CBullet::Draw(void)
{
    // �e
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->CBillboard::Draw();
    }

    // �`�悷��Ȃ�
    if (m_bUseDraw)
    {
        CScene3D::Draw();
    }
}

//=============================================================================
// ��������
// Author : �㓡�T�V��
//=============================================================================
CBullet * CBullet::Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, float fStrength, D3DXVECTOR3 rot)
{
    // �������m��
    CBullet *pBullet = NULL;
    pBullet = new CBullet;

    // ��Ɍ��т��Ă���
    pBullet->m_type = type;
    pBullet->SetRot(rot);

    // ������
    pBullet->SetupInfoByType(fStrength, pos);
    pBullet->Init(pos, DEFAULT_SCALE);

    // ���������т��Ă���
    pBullet->m_moveAngle = moveAngle;

    return pBullet;
}

//=============================================================================
// �Փˏ���
// Author : �㓡�T�V��
//=============================================================================
void CBullet::Collision(D3DXVECTOR3 bulletPos)
{
    // �v���C���[�A�ړ��v�ǂƂ̓����蔻��
    if (IS_BITON(m_collisionFlag, COLLISION_FLAG_PLAYER))
    {
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_PLAYER);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_PLAYER); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // �v���C���[�ɃL���X�g
                CPlayer *pPlayer = (CPlayer*)pScene;

                // �������Ă���Ȃ�
                if (IsCollisionCylinder(bulletPos, m_collisionSize, pPlayer->GetPos(), pPlayer->GetCollisionSizeDefence()))
                {
                    // �_���[�W
                    bool bDamaged = pPlayer->TakeDamage(m_fDamage, bulletPos, m_posOld);
                    if (bDamaged && m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }

        // �ړ��v�ǂ��擾
        CFortress *pFortress = CGame::GetFortress();
        if (pFortress)
        {
            // �������Ă���Ȃ�
            if (IsCollisionCylinder(bulletPos, m_collisionSize, pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
            {
                // �_���[�W
                bool bDamaged = pFortress->TakeDamage(m_fDamage, bulletPos, m_posOld);
                if (bDamaged && m_bHitErase)
                {
                    m_nLife = NOT_EXIST;
                }
            }
        }
    }

    // �G�Ƃ̓����蔻��
    if (IS_BITON(m_collisionFlag, COLLISION_FLAG_ENEMY))
    {
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // �G�ɃL���X�g
                CEnemy *pEnemy = (CEnemy*)pScene;

                // �������Ă���Ȃ�
                if (IsCollisionCylinder(bulletPos, m_collisionSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                {
                    // �_���[�W
                    bool bDamaged = pEnemy->TakeDamage(m_fDamage, bulletPos, m_posOld);
                    if (bDamaged && m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }
    }
}
