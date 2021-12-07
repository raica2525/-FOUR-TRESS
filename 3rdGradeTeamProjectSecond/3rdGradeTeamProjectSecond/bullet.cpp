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
#include "block.h"

//========================================
// �}�N����`
//========================================

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
    m_bBreakGoalGate = false;
    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));

    m_fGravityValue = 0.0f;
    m_fGravityLimit = 0.0f;
    m_fStrength = 0.0f;
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
    if (m_fGravityValue == 0.0f)
    {
        myPos += m_moveAngle * m_fSpeed;
    }
    else
    {
        // �d�͂��g���Ȃ�
        float fGravity = m_fGravityValue * m_nCntTime;
        if (fGravity < m_fGravityLimit)
        {
            fGravity = m_fGravityLimit;
        }
        myPos += m_moveAngle * m_fSpeed + D3DXVECTOR3(0.0f, fGravity, 0.0f);
    }

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
    pBullet->m_fStrength = fStrength;

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
void CBullet::Collision(D3DXVECTOR3 &bulletPos)
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

                // �C���f�b�N�X���擾
                int nIdx = pPlayer->GetIdx();
                if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
                {
                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                    continue;
                }

                // ���i�q�b�g���p�t���O��false�Ȃ�
                if (!m_abUseAvoidMultipleHits[nIdx])
                {
                    // �������Ă���Ȃ�
                    if (IsCollisionCylinder(bulletPos, m_collisionSize, pPlayer->GetPos(), pPlayer->GetCollisionSizeDefence()))
                    {
                        // ���i�q�b�g���p�̃t���O��true��
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // �_���[�W
                        bool bDamaged = pPlayer->TakeDamage(m_fDamage, bulletPos, m_posOld);
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = NOT_EXIST;
                        }
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
            // �C���f�b�N�X���擾
            int nIdx = pFortress->GetIdx();

            // ���i�q�b�g���p�t���O��false�Ȃ�
            if (!m_abUseAvoidMultipleHits[nIdx])
            {
                // �������Ă���Ȃ�
                if (IsCollisionCylinder(bulletPos, m_collisionSize, pFortress->GetPos(), pFortress->GetCollisionSizeDefence()))
                {
                    // ���i�q�b�g���p�̃t���O��true��
                    m_abUseAvoidMultipleHits[nIdx] = true;

                    // �_���[�W
                    bool bDamaged = pFortress->TakeDamage(m_fDamage, bulletPos, m_posOld);
                    if (bDamaged && m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
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

                // �C���f�b�N�X���擾
                int nIdx = pEnemy->GetIdx();
                if (nIdx < 0 || nIdx >= CHARACTER_IDX_MAX)
                {
                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                    continue;
                }

                // ���i�q�b�g���p�t���O��false�Ȃ�
                if (!m_abUseAvoidMultipleHits[nIdx])
                {
                    // �������Ă���Ȃ�
                    if (IsCollisionCylinder(bulletPos, m_collisionSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                    {
                        // ���i�q�b�g���p�̃t���O��true��
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // �_���[�W
                        bool bDamaged = pEnemy->TakeDamage(m_fDamage, bulletPos, m_posOld);
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = NOT_EXIST;
                        }
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }
    }

    // �u���b�N�Ƃ̓����蔻��
    if (IS_BITOFF(m_collisionFlag, COLLISION_FLAG_OFF_BLOCK))
    {
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // �u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock*)pScene;

                // �������Ă���Ȃ�
                D3DXVECTOR3 myCubeSize = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
                if (IsCollisionRectangle3D(&bulletPos, &pBlock->GetPos(),
                    &myCubeSize, &pBlock->GetCollisionSize()))
                {
                    // �_���[�W
                    pBlock->TakeDamage(m_bBreakGoalGate);
                    if (m_bHitErase)
                    {
                        m_nLife = NOT_EXIST;
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }
    }

    // �u���b�N�Ŕ��˂��邩�ǂ����̔���
    if (IS_BITON(m_collisionFlag, COLLISION_FLAG_REFLECT_BLOCK))
    {
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // �u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock*)pScene;

                // �������Ă���Ȃ�
                D3DXVECTOR3 myCubeSize = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
                HIT_SURFACE hitSurface = CGame::MapLimit(bulletPos, m_posOld, myCubeSize);

                // ����
                switch (hitSurface)
                {
                case HIT_SURFACE_LEFT:
                case HIT_SURFACE_RIGHT:
                    m_moveAngle.x *= -1.0f;
                    break;
                case HIT_SURFACE_BACK:
                case HIT_SURFACE_FRONT:
                    m_moveAngle.z *= -1.0f;
                    break;
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }
    }

    // �R�}���_�[�̍U���́A���ɐڂ����Ƃ��ɓG�𐶐����A����
    if (m_type == TYPE_COMMANDER_ATTACK)
    {
        if (bulletPos.y <= 0.0f)
        {
            bulletPos.y = 0.0f;
            m_nLife = NOT_EXIST;
            CEnemy::Create(CEnemy::TYPE_ARMY, bulletPos);
        }
    }
}