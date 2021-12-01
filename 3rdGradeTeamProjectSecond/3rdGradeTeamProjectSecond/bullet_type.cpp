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
void CBullet::SetupInfoByType(float fStrength, const D3DXVECTOR3 pos)
{
    // �e�𐶐����邩�ǂ���
    bool bUseShadow = true;

    switch (m_type)
    {
    case TYPE_ARMY_ATTACK:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 500.0f;
        m_bUseDraw = true;  // ��
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_RAILGUN_LV2:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(500.0f, 500.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 180;
        m_fDamage = 5000.0f;
        m_bUseDraw = true;  // ��
        m_bHitErase = false;// �ђ�
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    case TYPE_RAILGUN_LV3:
        // �ŗL�̏��
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 10000.0f;
        m_bUseDraw = true;  // ��
        m_bHitErase = false;// �ђ�
        // ���f�����o�C���h
        BindModelData(32);  // ���Ƀ{�[��
        break;
    }

    // �����𔽉f
    //m_fSpeed *= fStrength;    // �ړ����x�������Ȃ�͈̂�a���H
    m_fDamage *= fStrength;

    // �e����
    if (bUseShadow)
    {
        m_pEffect3d_Shadow = CEffect3D::Create(CEffectData::TYPE_SHADOW, D3DXVECTOR3(pos.x, SHADOW_POS_Y, pos.z));
        m_pEffect3d_Shadow->SetSize(D3DXVECTOR3(m_collisionSize.x, m_collisionSize.x, 0.0f));
        m_pEffect3d_Shadow->SetDisp(false); // �o���b�g���ŕ`����Ǘ����邽��
    }
}