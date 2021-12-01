//======================================================================================
//
// �ړ��v�Ǐ��� (fortress.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "fortress.h"
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
#include "bullet.h"

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CFortress::CFortress() :CCharacter(OBJTYPE::OBJTYPE_FORTRESS)
{
    m_fSpeed = 0.0f;

    m_bSearchRoad = true;
    m_moveAngle = DEFAULT_VECTOR;
    m_pTargetRoad = NULL;
    m_bNowWhoRiding = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CFortress::~CFortress()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CFortress::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �����ݒ�
    SetCollisionSizeDefence(D3DXVECTOR2(950.0f, 450.0f));
    m_fSpeed = 2.5f;
    SetUpLife(1000.0f);
    SetUseKnockBack(false);
    // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
    CCharacter::SetPartNum(PARTS_MAX);
    CCharacter::BindParts(PARTS_BODY, 55);
    CCharacter::BindParts(PARTS_CANNON_CENTER, 50);
    CCharacter::BindParts(PARTS_SEAT, 50);
    CCharacter::BindParts(PARTS_FIRE_POS, 50);
    CCharacter::SetDontUseAnimation();
    CCharacter::LoadModelData("./data/ANIMATION/motion_fortress.txt");
    CCharacter::SetDontUseAnimation();

    // �L�����N�^�[�ɔ��f
    CCharacter::Init(pos, DEFAULT_SCALE);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CFortress::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CFortress::Update(void)
{
    // �������Ԃ�����Ȃ�A�J�E���^��������
    CntDownTakeDamageTime();

    // �ʒu���擾
    D3DXVECTOR3 myPos = GetPos();
    
    // ����T���Ă��邩�ǂ���
    SearchRoad(myPos);

    // �ړ�
    myPos += m_moveAngle * m_fSpeed;

    // �ʒu��ݒ�
    SetPos(myPos);

    // �����𒲐�
    RotControl();

    // �A�j���[�V����������
    CCharacter::Update();

#ifdef COLLISION_TEST
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CFortress::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// ��������
// Author : �㓡�T�V��
//=============================================================================
CFortress * CFortress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // �������m��
    CFortress *pFortress = NULL;
    pFortress = new CFortress;

    // ��Ɍ��т��Ă���
    pFortress->CCharacter::SetPos(pos);
    pFortress->CCharacter::SetRot(rot);

    // ������
    pFortress->Init(pos, DEFAULT_SCALE);

    return pFortress;
}

//=============================================================================
// ����T������
// Author : �㓡�T�V��
//=============================================================================
void CFortress::SearchRoad(D3DXVECTOR3 myPos)
{
    if (m_bSearchRoad)
    {
        // ����T��
        float fKeepDistance = 99999.9f; // ����
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ROAD);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ROAD); nCntScene++)
        {
            // ���g������Ȃ�
            if (pScene)
            {
                // ���̃V�[�����L��
                CScene*pNextScene = pScene->GetNextScene();

                // ���ɃL���X�g
                CRoad *pRoad = (CRoad*)pScene;

                // �ʉ߂��Ă��Ȃ��Ȃ�
                if (!pRoad->GetPast())
                {
                    // ���̈ʒu
                    D3DXVECTOR3 roadPos = pRoad->GetPos();

                    // �����v�Z
                    float fCurrentDistance = sqrtf(
                        powf((myPos.x - roadPos.x), 2.0f) +
                        powf((myPos.z - roadPos.z), 2.0f));

                    // ���������L�[�v���Ă�����̂��߂��Ȃ�A�ړ��̌������X�V
                    if (fKeepDistance > fCurrentDistance)
                    {
                        fKeepDistance = fCurrentDistance;
                        m_pTargetRoad = pRoad;
                        float fAngleToRoad = GetAngleToTargetXZ(myPos, roadPos);
                        SetRotDestY(GetAngleToTargetXZ(roadPos, myPos));
                        m_moveAngle = D3DXVECTOR3(sinf(fAngleToRoad), 0.0f, cosf(fAngleToRoad));
                    }
                }

                // ���̃V�[���ɂ���
                pScene = pNextScene;
            }
        }

        // ���T���I��
        m_bSearchRoad = false;
    }
    else
    {
        // �ړI�̈ʒu�ɒB�����Ȃ�A���̓���T��
        if (m_pTargetRoad)
        {
            D3DXVECTOR3 targetRoadPos = m_pTargetRoad->GetPos();
            float fDistanceToTargetRoad = sqrtf(
                powf((myPos.x - targetRoadPos.x), 2.0f) +
                powf((myPos.z - targetRoadPos.z), 2.0f));
            const float SEARCH_NEXT_ROAD_DISTANCE = 25.0f;
            if (fDistanceToTargetRoad < SEARCH_NEXT_ROAD_DISTANCE)
            {
                m_bSearchRoad = true;
                m_pTargetRoad->SetPast(true);   // ����ʂ�߂������Ƃɂ���
            }
        }
    }
}
