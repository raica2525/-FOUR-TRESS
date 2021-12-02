//======================================================================================
//
// �A�C�e������ (item.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "item.h"
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

//========================================
// �}�N����`
//========================================
#define ITEM_LAUNCH_VALUE D3DXVECTOR3(0.0f, 25.0f, 0.0f)
#define ITEM_GRAVITY 1.0f
#define ITEM_GRAVITY_MAX -15.0f
#define ITEM_SPEED_UP_VALUE 1.0f
#define ITEM_SPEED_MAX 60.0f
#define ITEM_LIFE 600
#define ITEM_FLASH_START_FRAME (ITEM_LIFE - 420)
#define ITEM_CLOSE_PLAYER_DISTANCE 1000.0f
#define ITEM_ROT_SPEED D3DXToRadian(2.0f)

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CItem::CItem() :CScene3D(CScene::OBJTYPE_ITEM)
{
    m_type = TYPE_DENTI_5;
    m_collisionSize = D3DXVECTOR2(0.0f, 0.0f);
    m_move = ITEM_LAUNCH_VALUE;
    m_fSpeed = 0.0f;

    m_posOld = DEFAULT_VECTOR;
    m_nLife = ITEM_LIFE;
    m_fGetEnergy = 0.0f;

    m_bUseDraw = true;
    m_pEffect3d_Shadow = NULL;
    m_bGround = false;
    m_pTargetPlayer = NULL;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �����ݒ�
    switch (m_type)
    {
    case TYPE_DENTI_5:
        m_collisionSize = D3DXVECTOR2(200.0f, 200.0f);
        BindModelData(52);
        break;
    case TYPE_DENTI_3:
        m_collisionSize = D3DXVECTOR2(300.0f, 300.0f);
        BindModelData(53);
        break;
    case TYPE_DENTI_1:
        m_collisionSize = D3DXVECTOR2(400.0f, 400.0f);
        BindModelData(54);
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
void CItem::Uninit(void)
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
void CItem::Update(void)
{
    // �ʒu�A�傫�����擾
    D3DXVECTOR3 myPos = GetPos();

    // 1F�O�̈ʒu�����т���
    m_posOld = myPos;

    // ���n���Ă��Ȃ��Ȃ�
    if (!m_bGround)
    {
        // �d�͔���
        if (myPos.y > 0.0f)
        {
            m_move.y -= ITEM_GRAVITY;

            if (m_move.y < ITEM_GRAVITY_MAX)
            {
                m_move.y = ITEM_GRAVITY_MAX;
            }
        }
        else
        {
            myPos.y = 0.0f;
            m_move.y = 0.0f;
            m_bGround = true;
        }
    }
    else
    {
        // �v���C���[�̕���Ǐ]�i�v���C���[�̃|�C���^���Ȃ��Ȃ�A�v���C���[��T���j
        if (m_pTargetPlayer)
        {
            if (m_pTargetPlayer->GetDisp())
            {
                MoveTowardPlayer(myPos);
            }
            else
            {
                SearchPlayer(myPos);
            }
        }
        else
        {
            SearchPlayer(myPos);
        }
    }

    // �ʒu�Ɉړ��ʂ𔽉f
    myPos += m_move;

    // �����蔻��
    Collision(myPos);

    // �ʒu��ݒ�
    SetPos(myPos);

    // ��]
    D3DXVECTOR3 rot = GetRot();
    rot.y += ITEM_ROT_SPEED;
    if (rot.y > D3DX_PI)
    {
        rot.y -= D3DX_PI * 2.0f;
    }
    else if (rot.y < -D3DX_PI)
    {
        rot.y += D3DX_PI * 2.0f;
    }
    SetRot(rot);

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSize.x, m_collisionSize.y, m_collisionSize.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST

    // �e�̈ʒu���X�V
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(myPos.x, SHADOW_POS_Y, myPos.z));
    }

    // ���C�t���Ȃ��Ȃ肩������A�_��
    if (m_nLife < ITEM_FLASH_START_FRAME)
    {
        if (m_nLife % 2 == 0)
        {
            m_bUseDraw = !m_bUseDraw;
        }
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
void CItem::Draw(void)
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
CItem * CItem::Create(int type, D3DXVECTOR3 pos, float fEnergy)
{
    // �������m��
    CItem *pItem = NULL;
    pItem = new CItem;

    // ��Ɍ��т��Ă���
    pItem->m_type = type;
    pItem->m_fGetEnergy = fEnergy;

    // ������
    // �ʒu��0���傫���悤�ɂ���
    if (pos.y <= 0.0f)
    {
        pos.y = 1.0f;
    }
    pItem->Init(pos, DEFAULT_SCALE);

    return pItem;
}

//=============================================================================
// �v���C���[�Ɍ����킹�鏈��
// Author : �㓡�T�V��
//=============================================================================
void CItem::MoveTowardPlayer(D3DXVECTOR3 myPos)
{
    // �ړ����x�����X�ɑ��߂�
    m_fSpeed += ITEM_SPEED_UP_VALUE;
    if (m_fSpeed > ITEM_SPEED_MAX)
    {
        m_fSpeed = ITEM_SPEED_MAX;
    }

    // �ϐ��錾
    D3DXVECTOR3 targetPos = m_pTargetPlayer->GetPos();
    float fAngle = 0.0f;

    // �p�x�����߂�
    fAngle = atan2f((myPos.x - targetPos.x), (myPos.z - targetPos.z));

    // ���ړ��̒l�����߂�
    m_move.x = -sinf(fAngle) * m_fSpeed;
    m_move.z = -cosf(fAngle) * m_fSpeed;

    // �����𑪂�
    float fDistance = sqrtf(
        powf((targetPos.x - myPos.x), 2.0f) +
        powf((targetPos.z - myPos.z), 2.0f));

    // �����̍��𑪂�
    float fHeight = fabsf((targetPos.y) - myPos.y);

    // �c�̊p�x�����߂�
    float fAngleY = atan2(fDistance, fHeight);

    // �c�̈ړ��ʂ����߂�
    m_move.y = cosf(fAngleY) * m_fSpeed;

    // �^�[�Q�b�g�̈ʒu�̂ق����A���g�̈ʒu���Ⴂ�Ȃ�
    if (targetPos.y < myPos.y)
    {
        // Y���̈ړ��p�x���t�ɂ���
        m_move.y *= -1;
    }
}

//=============================================================================
// �v���C���[��T������
// Author : �㓡�T�V��
//=============================================================================
void CItem::SearchPlayer(D3DXVECTOR3 myPos)
{
    // �܂��A�ړ��ʂƃX�s�[�h���Ȃ���
    m_move = DEFAULT_VECTOR;
    m_fSpeed = 0.0f;

    // �v���C���[��T��
    float fKeepDistance = 99999.9f; // �L�[�v���Ă��鋗��
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_PLAYER);
    CPlayer *pKeepPlayer = NULL;
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
            if (pPlayer->GetDisp())
            {
                // �v���C���[�̈ʒu
                D3DXVECTOR3 playerPos = pPlayer->GetPos();

                // �����v�Z
                float fCurrentDistance = sqrtf(
                    powf((myPos.x - playerPos.x), 2.0f) +
                    powf((myPos.z - playerPos.z), 2.0f));

                // ���������L�[�v���Ă�����̂��߂��Ȃ�A�L�[�v����
                if (fKeepDistance > fCurrentDistance)
                {
                    fKeepDistance = fCurrentDistance;
                    pKeepPlayer = pPlayer;
                }
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }

    // �L�[�v���Ă��鋗�����A�߂��Ƃ݂Ȃ��l�Ȃ�
    if (fKeepDistance <= ITEM_CLOSE_PLAYER_DISTANCE)
    {
        // �v���C���[�����т���
        m_pTargetPlayer = pKeepPlayer;
    }
    else
    {
        // �߂��L���������Ȃ��Ȃ�A���n�t���O�������i�󒆂ŃL���������ꂽ���ɁA�A�C�e����������x�n�ʂɗ��Ƃ����߁j
        m_bGround = false;
    }
}

//=============================================================================
// �Փˏ���
// Author : �㓡�T�V��
//=============================================================================
void CItem::Collision(D3DXVECTOR3 myPos)
{
    // �v���C���[�Ƃ̓����蔻��
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
            if (IsCollisionCylinder(myPos, m_collisionSize, pPlayer->GetPos(), pPlayer->GetCollisionSizeDefence()))
            {
                // �v���C���[�̃G�i�W�[���Z
                pPlayer->GainEnergy(m_fGetEnergy);

                // 1�l�����Փ˂��Ȃ����߁A�֐��𔲂���
                m_nLife = NOT_EXIST;
                return;
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }
}
