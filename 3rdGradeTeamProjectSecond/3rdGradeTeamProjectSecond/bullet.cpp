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
#define HIT_NOT_EXIST -99

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

    m_nCntTime = 0;
    m_bUseDraw = false;

    m_bHitErase = true;
    m_pEffect3d_Shadow = NULL;
    m_bBreakGoalGate = false;
    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    m_fStrength = 0.0f;

    memset(m_afParam, 0, sizeof(m_afParam));
    m_whoShot = OBJTYPE_NONE;
    m_fHealValue = 0.0f;
    m_bUseUpdate = true;
    m_bUseUninit = true;
    m_bUseKnockBack = true;

    m_Effect.type = NOT_EXIST;
    m_Effect.interval = 1;
    m_Effect.nCntTrail = 0;
  
    m_nWhoContribution = NOT_EXIST;
    m_nHitContributionPoint = 0;
    m_nIdxHitEffect = DEFAULT_HIT_EFFECT_NUM;
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
    // �X�V�������g��Ȃ��Ȃ�A�֐��𔲂���
    if (!m_bUseUpdate)
    {
        return;
    }

    // �ʒu�A�傫�����擾
    D3DXVECTOR3 myPos = GetPos();

    // 1F�O�̈ʒu�����т���
    m_posOld = myPos;

    // ��ނ��Ƃ̏���
    bool bUseCollisionThisFrame = true;
    switch (m_type)
    {
    case TYPE_COMMANDER_ATTACK:
        CommanderAttackMove(myPos);
        break;
    case TYPE_HUNTER_GROUND:
        HunterGroundMove(myPos);
        break;
    case TYPE_HUNTER_SKY:
        HunterSkyMove(myPos);
        break;
    case TYPE_HEALER_SKY:
        bUseCollisionThisFrame = HealerSkyUseCollision();
        break;
    default:
        // �ړ��ʂ��ʒu�ɔ��f
        myPos += m_moveAngle * m_fSpeed;
        break;
    }

    // �����蔻���ݒ�
    if (bUseCollisionThisFrame)
    {
        Collision(myPos);
    }

    // �ʒu��ݒ�
    SetPos(myPos);

    // �e�̈ʒu���X�V
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(myPos.x, SHADOW_POS_Y, myPos.z));
    }

    // �O�ՃG�t�F�N�g����
    if (m_Effect.type != NOT_EXIST)
    {
        m_Effect.nCntTrail++;
        if (m_Effect.nCntTrail >= m_Effect.interval)
        {
            m_Effect.nCntTrail = 0;
            CEffect3D::Create(m_Effect.type, myPos);
        }
    }

    // ���C�t���Ȃ��Ȃ����A�܂��͎g�p�t���O���Ȃ��Ȃ�����A����
    if (m_bUseUninit)
    {
        m_nLife--;
        if (m_nLife <= 0)
        {
            Uninit();
        }
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
CBullet * CBullet::Create(int type, D3DXVECTOR3 pos, D3DXVECTOR3 moveAngle, OBJTYPE whoShot, float fStrength, D3DXVECTOR3 rot)
{
    // �������m��
    CBullet *pBullet = NULL;
    pBullet = new CBullet;

    // ��Ɍ��т��Ă���
    pBullet->m_type = type;
    pBullet->SetRot(rot);
    pBullet->m_fStrength = fStrength;
    pBullet->m_whoShot = whoShot;
    pBullet->m_posOld = pos;

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
    // ���[���K���͒n�𔇂�
    D3DXVECTOR3 collisionPos = bulletPos;
    if (m_type == TYPE_RAILGUN_LV2 || m_type == TYPE_RAILGUN_LV3)
    {
        collisionPos.y = 0.0f;
    }

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

                // �\�����Ă��邩�ǂ���
                if (!pPlayer->GetDisp())
                {
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

                        // �_���[�W�����������ǂ���
                        bool bDamaged = false;

                        // �񕜂���Ȃ�
                        if (IS_BITON(m_collisionFlag, COLLISION_FLAG_HEAL_PLAYER))
                        {
                            // ������͉񕜂ł��Ȃ�
                            if (m_nWhoContribution == pPlayer->GetIdxCreate())
                            {
                                continue;
                            }

                            // �񕜂͖��G�̗L���ɂ�����炸����
                            bDamaged = true;
                            if (pPlayer->Healing(m_fHealValue))
                            {
                                // �������l�̍v���x���オ��
                                if (m_nWhoContribution != NOT_EXIST)
                                {
                                    CGame::GetPlayer(m_nWhoContribution)->GainContribution(m_nHitContributionPoint);
                                }
                            }
                        }
                        else
                        {
                            // �_���[�W���󂯂�Ȃ�A�K�[�h���Ă��邩�ǂ���
                            if (pPlayer->GetUsingGuard())
                            {
                                bDamaged = pPlayer->TakeDamage_TankUsingGuard(m_fDamage, bulletPos, m_posOld, m_bUseKnockBack, m_nIdxHitEffect);
                            }
                            else
                            {
                                bDamaged = pPlayer->TakeDamage(m_fDamage, bulletPos, m_posOld, m_whoShot, m_bUseKnockBack, m_nIdxHitEffect);
                            }
                        }

                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = HIT_NOT_EXIST;
                        }
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }

        // �v���C���[���񕜂����Ȃ��Ȃ�A�ړ��v�ǂ��擾�i����ړ��v�ǎ���̃t���O��������Ȃ�A�v���P�j
        if (IS_BITOFF(m_collisionFlag, COLLISION_FLAG_HEAL_PLAYER))
        {
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
                        bool bDamaged = pFortress->TakeDamage(m_fDamage, bulletPos, m_posOld, m_whoShot, m_bUseKnockBack, m_nIdxHitEffect);
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = HIT_NOT_EXIST;
                        }
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

                // �o�����Ă��Ȃ��Ȃ�A����
                if (pEnemy->GetAppearState() != CEnemy::APPEAR_STATE_EXIST)
                {
                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                    continue;
                }

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
                    if (IsCollisionCylinder(collisionPos, m_collisionSize, pEnemy->GetPos(), pEnemy->GetCollisionSizeDefence()))
                    {
                        // ���i�q�b�g���p�̃t���O��true��
                        m_abUseAvoidMultipleHits[nIdx] = true;

                        // �_���[�W����������
                        bool bDamaged = false;
                        if (IS_BITON(m_collisionFlag, COLLISION_FLAG_PULL_ENEMY))
                        {
                            bDamaged = pEnemy->PullToCenter(bulletPos);
                        }
                        else if (IS_BITON(m_collisionFlag, COLLISION_FLAG_HEAL_ENEMY))
                        {
                            // �񕜂͖��G�̗L���ɂ�����炸����
                            bDamaged = true;
                            pEnemy->Healing(m_fHealValue);
                        }
                        else
                        {
                            bDamaged = pEnemy->TakeDamage(m_fDamage, bulletPos, m_posOld, m_whoShot, m_bUseKnockBack, m_nIdxHitEffect);
                            if (bDamaged)
                            {
                                // �v�������l��ݒ�
                                pEnemy->SetWhoContribution(m_nWhoContribution);
                            }
                        }
                        // �����e�Ȃ����
                        if (bDamaged && m_bHitErase)
                        {
                            m_nLife = HIT_NOT_EXIST;
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
                    if (pBlock->TakeDamage(m_bBreakGoalGate))
                    {
                        // �������l�̍v���x���オ��
                        if (m_nWhoContribution != NOT_EXIST)
                        {
                            CGame::GetPlayer(m_nWhoContribution)->GainContribution(m_nHitContributionPoint);
                        }
                    }
                    m_nLife = HIT_NOT_EXIST;    // �u���b�N�͊ђʏo���Ȃ�
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
                    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
                    break;
                case HIT_SURFACE_BACK:
                case HIT_SURFACE_FRONT:
                    m_moveAngle.z *= -1.0f;
                    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
                    break;
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }
    }

    // ���ɓ������������
    if (bulletPos.y < 0.0f)
    {
        bulletPos.y = 0.0f;
        m_nLife = HIT_NOT_EXIST;

        // �R�}���_�[�̒e�Ȃ�A�G�𐶐�
        if (m_type == TYPE_COMMANDER_ATTACK)
        {
            // �G�o���G�t�F�N�g
            CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_0, GetPos(), GetPos());
            CEffect3D::Emit(CEffectData::TYPE_ENEMY_POP_1, GetPos(), GetPos());

            CEnemy::Create(CEnemy::TYPE_ARMY, bulletPos);
        }
    }

    // ���������Ȃ�
    if (m_nLife == HIT_NOT_EXIST)
    {
        // �^���N�̒n��U��Lv3�Ȃ甚��
        if (m_type == TYPE_TANK_GROUND_LV3)
        {
            CBullet *pBullet = CBullet::Create(CBullet::TYPE_TANK_GROUND_EX, bulletPos, DEFAULT_VECTOR, m_whoShot);
            pBullet->SetWhoContribution(m_nWhoContribution);
        }
    }

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
    CDebug::Create(bulletPos, size, CDebug::TYPE_MOMENT, 66);
#endif // COLLISION_TEST
}