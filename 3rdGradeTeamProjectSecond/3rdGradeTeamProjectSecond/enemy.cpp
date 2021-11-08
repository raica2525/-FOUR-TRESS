//======================================================================================
//
// �G�l�~�[���� (enemy.cpp)
// Author : �㓡�T�V��
//
//======================================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "enemy.h"
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
CEnemy::CEnemy() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_SPIDER;
    m_collisionSizeDeffence = D3DXVECTOR2(0.0f, 0.0f);
    m_fSpeed = 0.0f;
    m_fStrength = 1.0f;
    m_fLife = 0.0f;

    m_nCntTime = 0;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ��ނ��Ƃ̏����ݒ�
    SetupInfoByType();

    // �L�����N�^�[�ɔ��f
    CCharacter::Init(pos, DEFAULT_SCALE);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Update(void)
{
    D3DXVECTOR3 myPos = GetPos();

    // ���̏���
    CPlayer *pPlayer = CGame::GetPlayer(0);
    if (pPlayer)
    {
        // ���̈ʒu
        D3DXVECTOR3 playerPos = pPlayer->GetPos();

        // �����v�Z
        float fDistance = sqrtf(
            powf((myPos.x - playerPos.x), 2) +
            powf((myPos.z - playerPos.z), 2));
        const float SEARCH_DISTANCE = 1000.0f;
        if (fDistance < SEARCH_DISTANCE)
        {
            SetRotDestY(GetAngleToTargetXZ(playerPos, myPos));

            RotControl();

            m_nCntTime++;

            if (m_nCntTime >= 75)
            {
                m_nCntTime = 0;
                D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
                CBullet::Create(CBullet::TYPE_ARMY_ATTACK, GetPos(), moveAngle);
            }
        }
    }

    // �A�j���[�V����������
    CCharacter::Update();

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSizeDeffence.x, m_collisionSizeDeffence.y, m_collisionSizeDeffence.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// ��������
// Author : �㓡�T�V��
//=============================================================================
CEnemy * CEnemy::Create(int type, D3DXVECTOR3 pos, float fStrength, D3DXVECTOR3 rot)
{
    // �������m��
    CEnemy *pEnemy = NULL;
    pEnemy = new CEnemy;

    // ��Ɍ��т��Ă���
    pEnemy->m_type = type;
    pEnemy->m_fStrength = fStrength;
    pEnemy->CCharacter::SetPos(pos);
    pEnemy->CCharacter::SetRot(rot);

    // ������
    pEnemy->Init(pos, DEFAULT_SCALE);

    return pEnemy;
}