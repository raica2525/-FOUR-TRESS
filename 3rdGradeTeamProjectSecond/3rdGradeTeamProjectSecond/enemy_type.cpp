//======================================================================================
//
// �G�l�~�[�̎�ޔh������ (enemy_type.cpp)
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

//=============================================================================
// ��ނ��Ƃ̏����ݒ�
// Author : �㓡�T�V��
//=============================================================================
void CEnemy::SetupInfoByType(void)
{
    // HP�\���͊�{�Ǐ]
    CCharacter::SetHPDisp(CCharacter::HP_DISP_FOLLOW);
    float fHP = 0.0f;

    switch (m_type)
    {
    case TYPE_SPIDER:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(500.0f, 100.0f));
        m_fSpeed = 5.0f;
        fHP = 500.0f;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(SPIDER_PARTS_MAX);
        CCharacter::BindParts(SPIDER_PARTS_BODY, 18);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH, 19);
        CCharacter::BindParts(SPIDER_PARTS_FANG_LEFT, 20);
        CCharacter::BindParts(SPIDER_PARTS_FANG_RIGHT, 21);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_0, 22);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_1, 23);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_2, 24);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_3, 25);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_0, 26);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_1, 27);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_2, 28);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_3, 29);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH_CUBE, 30);
        CCharacter::LoadModelData("./data/ANIMATION/motion_spider.txt");
        break;
    case TYPE_ARMY:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 150.0f));
        m_fSpeed = 5.0f;
        fHP = 500.0f;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(ARMY_PARTS_MAX);
        CCharacter::BindParts(ARMY_PARTS_BODY, 43);
        CCharacter::BindParts(ARMY_PARTS_RHAND, 44);
        CCharacter::BindParts(ARMY_PARTS_LHAND, 45);
        CCharacter::LoadModelData("./data/ANIMATION/motion_army.txt");
        break;
    case TYPE_KAMIKAZE:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(300.0f, 150.0f));
        m_fSpeed = 5.0f;
        fHP = 500.0f;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(KAMIKAZE_PARTS_MAX);
        CCharacter::BindParts(KAMIKAZE_PARTS_BODY, 46);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARML, 47);
        CCharacter::BindParts(KAMIKAZE_PARTS_ARMR, 48);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB, 49);
        CCharacter::BindParts(KAMIKAZE_PARTS_BOMB_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_kamikaze.txt");
        break;
    case TYPE_CANNON:
        // �ŗL�̏��
        SetCollisionSizeDefence(D3DXVECTOR2(400.0f, 200.0f));
        m_fSpeed = 5.0f;
        fHP = 500.0f;
        // �p�[�c����ݒ�A���f�����o�C���h�A�A�j���[�V�������o�C���h
        CCharacter::SetPartNum(CANNON_PARTS_MAX);
        CCharacter::BindParts(CANNON_PARTS_BODY, 51);
        CCharacter::BindParts(CANNON_PARTS_FIRE_CUBE, 50);
        CCharacter::LoadModelData("./data/ANIMATION/motion_cannon.txt");
        CCharacter::SetDontUseAnimation();
        break;
    }

    // �����𔽉f
    //m_fSpeed *= m_fStrength;  // �ړ����x�������Ȃ�͈̂�a���H
    fHP *= m_fStrength;

    // HP�𔽉f
    SetUpLife(fHP);
}