//======================================================================================
//
// �e�̎�ޔh������ (bullet_type.cpp)
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

//=============================================================================
// ��ނ��Ƃ̏����ݒ�
// Author : �㓡�T�V��
//=============================================================================
void CBullet::SetupInfoByType(float fStrength)
{
    switch (m_type)
    {
    case TYPE_ARMY_ATTACK:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 100.0f;
        m_bUseDraw = true;  // ��
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    }

    // �����𔽉f
    m_fSpeed *= fStrength;
    m_fDamage *= fStrength;
}