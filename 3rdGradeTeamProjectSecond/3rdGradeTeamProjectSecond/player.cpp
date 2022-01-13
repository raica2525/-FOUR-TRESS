//======================================================================================
//
// �v���C���[���� (player.cpp)
// Author : �㓡�T�V���A�r�c�I��i���U���g��J�X�^�}�C�Y�̃N���b�s���O�}�X�N�Ή��j
//
//======================================================================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// �C���N���[�h�t�@�C��
//========================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "library.h"
#include "camera.h"
#include "character.h"
#include "debug.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "ai.h"
#include "wave.h"
#include "effect3d.h"
#include "ui.h"
#include "effect2d.h"
#include "number_array.h"
#include "text.h"
#include "cliping_musk.h"
#include "modelEffect.h"
#include "number_array.h"
#include "enemy.h"
#include "fortress.h"
#include "bullet.h"

//========================================
// �}�N����`
//========================================
#define CUSTOM_ATK_COLOR D3DXCOLOR(0.874f, 0.329f, 0.094f, 1.0f)
#define CUSTOM_DEF_COLOR D3DXCOLOR(0.203f, 0.768f, 0.196f, 1.0f)
#define CUSTOM_SPD_COLOR D3DXCOLOR(0.156f, 0.56f, 0.854f, 1.0f)
#define CUSTOM_WEI_COLOR D3DXCOLOR(1.0f, 0.501f, 0.0f, 1.0f)

// �ő�ʁi�̂̂܂܁j
#define MAX_ATK 2250.0f
#define MAX_DEF 2000.0f
#define MAX_SPD 2700.0f
#define MAX_WEI 4100.0f

// �����^�уG�i�W�[��
#define CARRY_ENERGY_DEFAULT 50.0f
#define CARRY_ENERGY_CARRIER 80.0f 

// ���X�|�[������
#define RESPAWN_FRAME 600

//=======================
// �E�H�[���A�[
//=======================
#define WARRIOR_LIFE 500.0f
#define WARRIOR_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define WARRIOR_SPD 840.0f
#define WARRIOR_WEI 3060.0f

//=======================
// �n���^�[
//=======================
#define HUNTER_LIFE 290.0f
#define HUNTER_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define HUNTER_SPD 940.0f
#define HUNTER_WEI 3060.0f

//=======================
// �L�����A�[
//=======================
#define CARRIER_LIFE 370.0f
#define CARRIER_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define CARRIER_SPD 1040.0f
#define CARRIER_WEI 3060.0f

//=======================
// �^���N
//=======================
#define TANK_LIFE 850.0f
#define TANK_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define TANK_COLLISION_SIZE_GUARD D3DXVECTOR2(500.0f, 450.0f)
#define TANK_SPD 740.0f
#define TANK_WEI 3360.0f
#define TANK_GUARD_WIDTH 180.0f
#define TANK_GUARD_DISTANCE 100.0f
#define TANK_GUARD_COLOR D3DXCOLOR(1.0f,0.933f,0.0f,1.0f)

//=======================
// �q�[���[
//=======================
#define HEALER_LIFE 350.0f
#define HEALER_COLLISION_SIZE D3DXVECTOR2(300.0f, 450.0f)
#define HEALER_SPD 790.0f
#define HEALER_WEI 3060.0f

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CPlayer::CPlayer() :CCharacter(OBJTYPE::OBJTYPE_PLAYER)
{
    m_bMannequin = false;
    m_controlInput.bTiltedLeftStick = false;
    m_controlInput.fLeftStickAngle = 0.0f;
    m_controlInput.bTiltedRightStick = false;
    m_controlInput.fRightStickAngle = 0.0f;
    m_controlInput.fPlayerAngle = 0.0f;
    m_controlInput.bTriggerA = false;
    m_controlInput.bPressA = false;
    m_controlInput.bTriggerX = false;
    m_controlInput.bPressX = false;
    m_controlInput.bReleaseX = false;
    m_controlInput.bPressR2 = false;
    m_controlInput.bTriggerB = false;
    m_bUseKeyboard = false;
    m_AIlevel = AI_LEVEL_NONE;
    m_pAI = NULL;
    m_pUI_SP = NULL;
    m_pUI_Playable = NULL;
    m_pNumArray_SP = NULL;
    m_pUI_Custom_Atk = NULL;
    m_pUI_Custom_Def = NULL;
    m_pUI_Custom_Spd = NULL;
    m_pUI_Custom_Wei = NULL;
    m_pUI_Custom_Ability = NULL;
    m_pText_Custom_Ex_Head = NULL;
    m_pText_Custom_Ex_Up = NULL;
    m_pText_Custom_Ex_Down = NULL;
    m_pText_Custom_Ex_Wep = NULL;
    m_pText_Custom_Sp = NULL;
    m_bDispAbility = false;

    m_nIdxCreate = PLAYER_1;
    m_nIdxControlAndColor = PLAYER_1;

    m_exFlag = EX_FLAG_NONE;
    m_bGround = true;

    m_nCntLandingTime = 0;
    m_bGroundOld = true;

    memset(m_anNumCustomParts, 0, sizeof(m_anNumCustomParts));
    m_fAtk = 0.0f;
    m_fDef = 0.0f;
    m_fSpd = 0.0f;
    m_fWei = 0.0f;
    memset(m_afParam, 0, sizeof(m_afParam));
    m_nModelPosDefUp = 0;
    m_nModelPosDefDown = 0;

    m_nCntPressJump = 0;
    m_bUsedSecondJump = false;
    m_nCntStartGlide = 0;

    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    m_nCntAttackAnimTime = 0;

    m_spShot = SP_SHOT_HEAL;
    m_fCurrentEnergy = 0.0f;
    m_fCurrentEnergyMax = 0.0f;

    m_pClipingMusk = NULL;
    m_rank = RANK_1;
    m_hipPosOld = DEFAULT_VECTOR;

    m_nCntCurrentEnergyMaxTime = 0;
    m_voiceSet = VOICE_SET_ROBO;

    //===================================
    // ����\�͑Ή�����
    //===================================

    //===================================    
    // Second�Œǉ����������o�ϐ�
    //===================================
    m_role = ROLE_WARRIOR;
    m_attackState = ATTACK_STATE_NONE;
    m_nCntStopTime = 0;
    m_nCntAttackTime = 0;
    m_fCurrentEnergy = 0.0f;
    m_waitMotion = ANIM_IDLE;
    m_walkMotion = ANIM_MOVE;
    m_bUsingGuard = false;
    m_nCntGuards = 0;
    m_pLightGuard = NULL;
    m_pHealingCircle = NULL;
    m_nCntRespawnTime = 0;
    m_nContributionPoint = 0;
    m_bGetOffFortressInThisFrame = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �p�[�c����ݒ�
    CCharacter::SetPartNum(PARTS_MAX);

    // �A�j���[�V������ǂݍ���
    //CCharacter::LoadModelData("./data/ANIMATION/motion_player.txt");  // ���W�E�e�q�֌W�̓ǂݍ��݂ƁA�A�j���[�V�����̓ǂݍ��݂𕪂���
    //CCharacter::SetAnimFilePass("./data/ANIMATION/motion_player.txt");// ����̃Q�[���̓J�X�^�}�C�Y���Ȃ����߁ALoadCustom���ɈڏZ

    // �v���C�A�u���L�����̐ݒ��ǂݍ���
    LoadCustom();

    return S_OK;
}

//=============================================================================
// �J�X�^�}�C�Y�ǂݍ��ݏ���
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::LoadCustom(void)
{
    // �t�@�C���|�C���^
    FILE *pFile = NULL;

    // �p�[�c���X�g������擾
    CModelData *pModelData = CManager::GetModelData();

    // �ϐ��錾
    int nPartsListType = 0;                // �p�[�c���X�g���̎��
    int nExNumber = 0;                     // ����\�͔ԍ�

                                           // ��`
    const int PARTS_LIST_HEAD = 0;         // �p�[�c���X�g_��
    const int PARTS_LIST_UP = 1;           // �p�[�c���X�g_�㔼�g
    const int PARTS_LIST_DOWN = 2;         // �p�[�c���X�g_�����g
    const int PARTS_LIST_WEP = 3;          // �p�[�c���X�g_����

    // ���f�����郁���o�ϐ�����񏉊���
    m_fAtk = 0.0f;
    m_fDef = 0.0f;
    m_fSpd = 0.0f;
    m_fWei = 0.0f;
    m_exFlag = EX_FLAG_NONE;
    D3DXVECTOR2 collisionSizeDefence = D3DXVECTOR2(0.0f, 0.0f);
    //memset(m_afParam, 0, sizeof(m_afParam));

    //// �J�X�^�}�C�Y�f�[�^�̃t�@�C�����J��
    //switch (m_nIdxControlAndColor)
    //{
    //case PLAYER_1:
    //    pFile = fopen("data/TXT/custom1.txt", "r");
    //    break;
    //case PLAYER_2:
    //    pFile = fopen("data/TXT/custom2.txt", "r");
    //    break;
    //case PLAYER_3:
    //    pFile = fopen("data/TXT/custom3.txt", "r");
    //    break;
    //case PLAYER_4:
    //    pFile = fopen("data/TXT/custom4.txt", "r");
    //    break;
    //}

    //// �J������
    //if (pFile != NULL)
    //{
    //    for (int nCntPartsList = 0; nCntPartsList < MAX_PARTS; nCntPartsList++)
    //    {
    //        // �ǂݍ���
    //        fscanf(pFile, "%d", &nPartsListType);

    //        // ��{4�\��
    //        m_fAtk += pModelData->GetPartsList(nPartsListType)->fAtk * pModelData->GetPartsRate(nCntPartsList)->fAtkRate;
    //        m_fDef += pModelData->GetPartsList(nPartsListType)->fDef * pModelData->GetPartsRate(nCntPartsList)->fDefRate;
    //        m_fSpd += pModelData->GetPartsList(nPartsListType)->fSpd * pModelData->GetPartsRate(nCntPartsList)->fSpdRate;
    //        m_fWei += pModelData->GetPartsList(nPartsListType)->fWei * pModelData->GetPartsRate(nCntPartsList)->fWeiRate;

    //        // ����\��
    //        int customPartsExFlag = 0;  // �J�X�^�}�C�Y��ʂŎg���A�p�[�c���̓���\��
    //        nExNumber = pModelData->GetPartsList(nPartsListType)->nEx0;
    //        BITON(m_exFlag, 0x001 << nExNumber);
    //        BITON(customPartsExFlag, 0x001 << nExNumber);
    //        nExNumber = pModelData->GetPartsList(nPartsListType)->nEx1;
    //        BITON(m_exFlag, 0x001 << nExNumber);
    //        BITON(customPartsExFlag, 0x001 << nExNumber);

    //        // �e�p�[�c���X�g����A�ו��̃p�[�c������
    //        if (nCntPartsList == PARTS_LIST_HEAD)
    //        {
    //            // �J�X�^�}�C�Y��ʂœ���\�͕\�����X�V
    //            if (m_pText_Custom_Ex_Head)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Head->SetText(cExName);
    //            }

    //            // ���f�����o�C���h
    //            BindParts(PARTS_HEAD, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);

    //            // �J�X�^�}�C�Y�p�[�c�ԍ����擾
    //            m_anNumCustomParts[CUSTOM_PARTS_HEAD] = nPartsListType;

    //            // �X�C���O�̌������A�⏕�l����⏕�l��
    //            m_afParam[PARAM_SWING_UP] = pModelData->GetPartsList(nPartsListType)->afParam[1];
    //            m_afParam[PARAM_SWING_DOWN] = pModelData->GetPartsList(nPartsListType)->afParam[2];
    //            m_afParam[PARAM_SMASH] = pModelData->GetPartsList(nPartsListType)->afParam[3];
    //            m_afParam[PARAM_SPIKE_RIGHT] = pModelData->GetPartsList(nPartsListType)->afParam[4];
    //            m_afParam[PARAM_SPIKE_LEFT] = pModelData->GetPartsList(nPartsListType)->afParam[5];

    //            // �{�C�X�Z�b�g�̔ԍ���ێ�
    //            m_voiceSet = (int)pModelData->GetPartsList(nPartsListType)->afParam[6];

    //            // �h�䓖���蔻��̍X�V
    //            if (collisionSizeDefence.x < pModelData->GetPartsList(nPartsListType)->fWidth)
    //            {
    //                collisionSizeDefence.x = pModelData->GetPartsList(nPartsListType)->fWidth;
    //            }
    //            collisionSizeDefence.y += pModelData->GetPartsList(nPartsListType)->fHeight;
    //        }
    //        else if (nCntPartsList == PARTS_LIST_UP)
    //        {
    //            // �J�X�^�}�C�Y��ʂœ���\�͕\�����X�V
    //            if (m_pText_Custom_Ex_Up)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Up->SetText(cExName);
    //            }

    //            // ���f�����o�C���h
    //            BindParts(PARTS_BODY, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);
    //            BindParts(PARTS_RSHOULDER, (int)pModelData->GetPartsList(nPartsListType)->afParam[1]);
    //            BindParts(PARTS_RARM, (int)pModelData->GetPartsList(nPartsListType)->afParam[2]);
    //            BindParts(PARTS_RHAND, (int)pModelData->GetPartsList(nPartsListType)->afParam[3]);
    //            BindParts(PARTS_LSHOULDER, (int)pModelData->GetPartsList(nPartsListType)->afParam[4]);
    //            BindParts(PARTS_LARM, (int)pModelData->GetPartsList(nPartsListType)->afParam[5]);
    //            BindParts(PARTS_LHAND, (int)pModelData->GetPartsList(nPartsListType)->afParam[6]);

    //            // �J�X�^�}�C�Y�p�[�c�ԍ����擾
    //            m_anNumCustomParts[CUSTOM_PARTS_UP] = nPartsListType;

    //            // �㔼�g�̏����ʒu�f�[�^
    //            m_nModelPosDefUp = (int)pModelData->GetPartsList(nPartsListType)->afParam[7];

    //            // �h�䓖���蔻��̍X�V
    //            if (collisionSizeDefence.x < pModelData->GetPartsList(nPartsListType)->fWidth)
    //            {
    //                collisionSizeDefence.x = pModelData->GetPartsList(nPartsListType)->fWidth;
    //            }
    //            collisionSizeDefence.y += pModelData->GetPartsList(nPartsListType)->fHeight;
    //        }
    //        else if (nCntPartsList == PARTS_LIST_DOWN)
    //        {
    //            // �J�X�^�}�C�Y��ʂœ���\�͕\�����X�V
    //            if (m_pText_Custom_Ex_Down)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Down->SetText(cExName);
    //            }

    //            // ���f�����o�C���h
    //            BindParts(PARTS_HIP, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);
    //            BindParts(PARTS_RTHIGH, (int)pModelData->GetPartsList(nPartsListType)->afParam[1]);
    //            BindParts(PARTS_RLEG, (int)pModelData->GetPartsList(nPartsListType)->afParam[2]);
    //            BindParts(PARTS_RFOOT, (int)pModelData->GetPartsList(nPartsListType)->afParam[3]);
    //            BindParts(PARTS_LTHIGH, (int)pModelData->GetPartsList(nPartsListType)->afParam[4]);
    //            BindParts(PARTS_LLEG, (int)pModelData->GetPartsList(nPartsListType)->afParam[5]);
    //            BindParts(PARTS_LFOOT, (int)pModelData->GetPartsList(nPartsListType)->afParam[6]);

    //            // �J�X�^�}�C�Y�p�[�c�ԍ����擾
    //            m_anNumCustomParts[CUSTOM_PARTS_DOWN] = nPartsListType;

    //            // �����g�̏����ʒu�f�[�^
    //            m_nModelPosDefDown = (int)pModelData->GetPartsList(nPartsListType)->afParam[7];

    //            // �h�䓖���蔻��̍X�V
    //            if (collisionSizeDefence.x < pModelData->GetPartsList(nPartsListType)->fWidth)
    //            {
    //                collisionSizeDefence.x = pModelData->GetPartsList(nPartsListType)->fWidth;
    //            }
    //            collisionSizeDefence.y += pModelData->GetPartsList(nPartsListType)->fHeight;
    //        }
    //        else if (nCntPartsList == PARTS_LIST_WEP)
    //        {
    //            // �J�X�^�}�C�Y��ʂœ���\�͕\�����X�V
    //            if (m_pText_Custom_Ex_Wep)
    //            {
    //                char cExName[256];
    //                CustomExName(cExName, customPartsExFlag);
    //                m_pText_Custom_Ex_Wep->SetText(cExName);
    //            }

    //            // ���f�����o�C���h
    //            BindParts(PARTS_WEP, (int)pModelData->GetPartsList(nPartsListType)->afParam[0]);
    //            m_nNumWep = (int)pModelData->GetPartsList(nPartsListType)->afParam[0];

    //            // �J�X�^�}�C�Y�p�[�c�ԍ����擾
    //            m_anNumCustomParts[CUSTOM_PARTS_WEP] = nPartsListType;

    //            // �K�E�Z�ƁA���̃Q�[�W��
    //            m_spShot = (int)pModelData->GetPartsList(nPartsListType)->afParam[1];
    //            m_fSpGaugeMax = pModelData->GetPartsList(nPartsListType)->afParam[2];

    //            // �K�E�Z�̕⏕�l��⏕�l��
    //            m_afParam[PARAM_5_WEAPON_SP] = pModelData->GetPartsList(nPartsListType)->afParam[5];
    //            m_afParam[PARAM_6_WEAPON_SP] = pModelData->GetPartsList(nPartsListType)->afParam[6];
    //            m_afParam[PARAM_7_WEAPON_SP] = pModelData->GetPartsList(nPartsListType)->afParam[7];
    //        }
    //    }
    //    // �t�@�C�������
    //    fclose(pFile);
    //}

    // �J�X�^�}�C�Y��ʂŕK�E�Z�\�����X�V
    if (m_pText_Custom_Sp)
    {
        char cSpName[256];
        CustomSpName(cSpName);
        m_pText_Custom_Sp->SetText(cSpName);
    }

    // �K���Ȑݒ�
    m_spShot = 1;

    // �ő厝���^�уG�i�W�[��
    switch (m_role)
    {
    case ROLE_CARRIER:
        m_fCurrentEnergyMax = CARRY_ENERGY_CARRIER;
        break;
    default:
        m_fCurrentEnergyMax = CARRY_ENERGY_DEFAULT;
        break;
    }

    // ���ʂ̐ݒ�
    BindParts(PARTS_BODY, 3);
    BindParts(PARTS_RSHOULDER, 5);
    BindParts(PARTS_RARM, 6);
    BindParts(PARTS_RHAND, 7);
    BindParts(PARTS_LSHOULDER, 8);
    BindParts(PARTS_LARM, 9);
    BindParts(PARTS_LHAND, 10);
    BindParts(PARTS_HIP, 2);
    BindParts(PARTS_RTHIGH, 11);
    BindParts(PARTS_RLEG, 12);
    BindParts(PARTS_RFOOT, 13);
    BindParts(PARTS_LTHIGH, 14);
    BindParts(PARTS_LLEG, 15);
    BindParts(PARTS_LFOOT, 16);

    // �e��E�ňقȂ�ݒ�
    float fLife = 1.0f;
    switch (m_role)
    {
    case ROLE_WARRIOR:
        BindParts(PARTS_HEAD, 4);
        BindParts(PARTS_WEP, 17);
        fLife = WARRIOR_LIFE;
        collisionSizeDefence = WARRIOR_COLLISION_SIZE;
        m_fSpd = WARRIOR_SPD;
        m_fWei = WARRIOR_WEI;
        break;
    case ROLE_HUNTER:
        BindParts(PARTS_HEAD, 18);
        BindParts(PARTS_WEP, 19);
        fLife = HUNTER_LIFE;
        collisionSizeDefence = HUNTER_COLLISION_SIZE;
        m_fSpd = HUNTER_SPD;
        m_fWei = HUNTER_WEI;
        break;
    case ROLE_CARRIER:
        BindParts(PARTS_HEAD, 20);
        BindParts(PARTS_WEP, 50);
        BindParts(PARTS_RHAND, 21);
        BindParts(PARTS_LHAND, 22);
        BindParts(PARTS_RFOOT, 23);
        BindParts(PARTS_LFOOT, 24);
        fLife = CARRIER_LIFE;
        collisionSizeDefence = CARRIER_COLLISION_SIZE;
        m_fSpd = CARRIER_SPD;
        m_fWei = CARRIER_WEI;
        m_waitMotion = ANIM_CARRIER_IDLE;
        m_walkMotion = ANIM_CARRIER_DUSH;
        break;
    case ROLE_TANK:
        BindParts(PARTS_HEAD, 25);
        BindParts(PARTS_WEP, 26);
        fLife = TANK_LIFE;
        collisionSizeDefence = TANK_COLLISION_SIZE;
        m_fSpd = TANK_SPD;
        m_fWei = TANK_WEI;
        m_afParam[0] = TANK_GUARD_WIDTH;
        break;
    case ROLE_HEALER:
        BindParts(PARTS_HEAD, 28);
        BindParts(PARTS_WEP, 29);
        fLife = HEALER_LIFE;
        collisionSizeDefence = HEALER_COLLISION_SIZE;
        m_fSpd = HEALER_SPD;
        m_fWei = HEALER_WEI;
        break;
    }
    SetUpLife(fLife);

    // �L�����N�^�[�ɔ��f
    CCharacter::SetCollisionSizeDefence(collisionSizeDefence);
    CCharacter::LoadModelData("./data/ANIMATION/motion_player.txt");
    CCharacter::Init(CCharacter::GetPos(), DEFAULT_SCALE);
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Uninit(void)
{
    // AI�����������J��
    if (m_pAI != NULL)
    {
        // �������J��
        delete m_pAI;
        m_pAI = NULL;
    }

    // �N���b�s���O�̏����J��
    if (m_pClipingMusk != NULL)
    {
        m_pClipingMusk->Uninit();
        delete m_pClipingMusk;
        m_pClipingMusk = NULL;
    }

    CCharacter::Uninit();
}

//=============================================================================
// ���͏���
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Input(void)
{
    // �R���g���[��or�L�[�{�[�h����i1P�̏ꍇ�AEnter�őJ�ڂ����Ȃ�L�[�{�[�h����ɕς���j
    if (m_bUseKeyboard)
    {
        // �L�[�{�[�h���擾
        CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

        // �{�^�������擾
        m_controlInput.bTriggerA = pInputKeyboard->GetKeyboardTrigger(DIK_SPACE);
        m_controlInput.bPressA = pInputKeyboard->GetKeyboardPress(DIK_SPACE);
        m_controlInput.bTriggerX = pInputKeyboard->GetKeyboardTrigger(DIK_RETURN);
        m_controlInput.bPressX = pInputKeyboard->GetKeyboardPress(DIK_RETURN);
        m_controlInput.bReleaseX = pInputKeyboard->GetKeyboardRelease(DIK_RETURN);
        m_controlInput.bPressR2 = pInputKeyboard->GetKeyboardPress(DIK_UP);
        m_controlInput.bTriggerB = pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT);

        // ���X�e�B�b�N���X���Ă��邩�ǂ���
        if (pInputKeyboard->GetKeyboardPress(DIK_W) ||
            pInputKeyboard->GetKeyboardPress(DIK_A) ||
            pInputKeyboard->GetKeyboardPress(DIK_S) ||
            pInputKeyboard->GetKeyboardPress(DIK_D))
        {
            m_controlInput.bTiltedLeftStick = true;

            // �p�x�����߂�
            if (pInputKeyboard->GetKeyboardPress(DIK_A))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(-45.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(135.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_S))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(-135.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(45.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_D))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(-90.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(90.0f);
                }
            }
            else if (pInputKeyboard->GetKeyboardPress(DIK_D))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(45.0f);
                    m_controlInput.fPlayerAngle = -D3DXToRadian(135.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_S))
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(135.0f);
                    m_controlInput.fPlayerAngle = -D3DXToRadian(45.0f);
                }
                else if (pInputKeyboard->GetKeyboardPress(DIK_A))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(90.0f);
                    m_controlInput.fPlayerAngle = -D3DXToRadian(90.0f);
                }
            }
            else if (pInputKeyboard->GetKeyboardPress(DIK_W))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_S))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(0.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(180.0f);
                }
            }
            else if (pInputKeyboard->GetKeyboardPress(DIK_S))
            {
                if (pInputKeyboard->GetKeyboardPress(DIK_W))
                {
                    m_controlInput.bTiltedLeftStick = false;
                }
                else
                {
                    m_controlInput.fLeftStickAngle = D3DXToRadian(180.0f);
                    m_controlInput.fPlayerAngle = D3DXToRadian(0.0f);
                }
            }
        }
        else
        {
            m_controlInput.bTiltedLeftStick = false;
        }
    }
    else
    {
        // �R���g���[�����擾
        CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

        // �{�^�������擾
        m_controlInput.bTriggerA = pInputJoypad->GetJoypadTrigger(m_nIdxControlAndColor, XINPUT_GAMEPAD_A);
        m_controlInput.bPressA = pInputJoypad->GetButtonState(m_nIdxControlAndColor, XINPUT_GAMEPAD_A);
        m_controlInput.bTriggerX = pInputJoypad->GetJoypadTrigger(m_nIdxControlAndColor, XINPUT_GAMEPAD_X);
        m_controlInput.bPressX = pInputJoypad->GetButtonState(m_nIdxControlAndColor, XINPUT_GAMEPAD_X);
        m_controlInput.bReleaseX = pInputJoypad->GetJoypadRelease(m_nIdxControlAndColor, XINPUT_GAMEPAD_X);
        m_controlInput.bPressR2 = pInputJoypad->GetTriggerState(m_nIdxControlAndColor, CInputJoypad::RIGHT);
        m_controlInput.bTriggerB = pInputJoypad->GetJoypadTrigger(m_nIdxControlAndColor, XINPUT_GAMEPAD_B);

		D3DXVECTOR2 stickValue[CInputJoypad::LR_MAX];
		for (int nCount = 0; nCount < CInputJoypad::LR_MAX; nCount++)
		{
			stickValue[nCount] = pInputJoypad->GetStickValue(m_nIdxControlAndColor, (CInputJoypad::LR)nCount);
		}

        // ���X�e�B�b�N���X���Ă��邩�ǂ���
        if (stickValue[CInputJoypad::LEFT].x || stickValue[CInputJoypad::LEFT].y)
        {
            m_controlInput.bTiltedLeftStick = true;

            // �p�x�����߂�
			m_controlInput.fLeftStickAngle = atan2f(stickValue[CInputJoypad::LEFT].x, stickValue[CInputJoypad::LEFT].y);
			m_controlInput.fPlayerAngle = atan2f(stickValue[CInputJoypad::LEFT].x*-1, stickValue[CInputJoypad::LEFT].y * -1);
        }
        else
        {
            m_controlInput.bTiltedLeftStick = false;
        }

        // �E�X�e�B�b�N���X���Ă��邩�ǂ���
        if (stickValue[CInputJoypad::RIGHT].x || stickValue[CInputJoypad::RIGHT].y)
        {
            m_controlInput.bTiltedRightStick = true;

            // �p�x�����߂�
            m_controlInput.fRightStickAngle = atan2(stickValue[CInputJoypad::RIGHT].x, stickValue[CInputJoypad::RIGHT].y);
        }
        else
        {
            m_controlInput.bTiltedRightStick = false;
        }
    }
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Update(void)
{
    // �S������
    m_bGetOffFortressInThisFrame = false;

    // 1F�O�̍��̈ʒu���L��
    m_hipPosOld = GetPartsPos(PARTS_HIP);

    // �_���[�W�ɂ���čU�������Z�b�g����t���O�������Ă���Ȃ�
    if (GetResetAttackByDamage())
    {
        m_nCntGuards = 0;   // �U�����󂯂����̂݁A�^���N�̃K�[�h�񐔂̓��Z�b�g�����
        ResetAttack();
        SetResetAttackByDamage(false);
        if (GetLife() <= 0.0f)
        {
            m_nCntStopTime = PLAYER_DEATH_STOP_FRAME;
        }
    }

    // �������Ă��Ȃ�or�N���オ�蒆�́A���G
    DAMAGE_STATE damageState = GetDamageState();
    if (damageState == DAMAGE_STATE_NONE || damageState == DAMAGE_STATE_STAND_UP && GetTakeDamageTime() <= PLAYER_TAKE_DAMAGE_STAND_UP_INVINCIBLE_FRAME)
    {
        SetInvincible(false);
    }
    else
    {
        SetInvincible(true);
    }

    // �}�l�L�����[�h�łȂ��Ȃ�
    if (!m_bMannequin)
    {
        // �\�����Ă���Ȃ�
        if (GetDisp())
        {
            // AI�łȂ��Ȃ�
            if (!m_pAI)
            {
                // ���͏���
                Input();
            }
            else
            {
                // AI�X�V����
                m_pAI->Update();
            }

            // �d�����Ă��Ȃ��Ȃ�
            if (m_nCntStopTime <= 0)
            {
                // �������Ԃ�����Ȃ�A�J�E���^��������
                CntDownTakeDamageTime();

                // �U���̃N�[���^�C��
                if (m_nCntAttackTime > 0)
                {
                    // �U�����̓J�E���g�_�E��
                    m_nCntAttackTime--;

                    // �U���I�����Ƀ����o�ϐ���߂�
                    if (m_nCntAttackTime == 0)
                    {
                        ResetAttack();
                    }
                }

                // �A�^�b�N�A�j���[�V�����J�E���^
                if (m_nCntAttackAnimTime > 0)
                {
                    // �J�E���g�_�E��
                    m_nCntAttackAnimTime--;
                }

                // ���n���Ă���Ȃ�A�F�X�t���O�����Z�b�g
                if (m_bGround)
                {
                    ResetOnGround();
                }

                // �s��
                float fSpeed = PLAYER_BASE_MINIMUM_SPEED + (m_fSpd * PLAYER_ADD_BASE_SPEED_RATE); // �Œ�ۏ؂̑��x�ɁA�p�����[�^���𑫂�
                Movement(fSpeed);

                // �A�j���[�V����������
                CCharacter::Update();
            }
            else
            {
                // �d�����Ԃ��J�E���g
                m_nCntStopTime--;
            }
        }
        else
        {
            // ���ꂽ���̋���
            DeadMove();
        }

        // �Q�[��UI�̍X�V
        UpdateGameUI();
    }
    else
    {
        // �}�l�L�����[�h�̍X�V
        UpdateMannequin();
    }

    // ������΂���G�t�F�N�g�́A��ʓ��Ő�����΂���Ă���Ȃ�o��
    if (GetDamageState() == DAMAGE_STATE_BLOWN)
    {
        if (m_nCntStopTime <= 0)
        {
            D3DXVECTOR3 hipPos = GetPartsPos(PARTS_HIP);
            if (hipPos.y > -500.0f) // ��ʊO�Ή�
            {
                //CEffect3D::Emit(CEffectData::TYPE_BLOWN, hipPos, m_hipPosOld);
            }
        }
    }

    // �̗͂�0�ɂȂ�����
    if (GetLife() <= 0.0f && GetDisp())
    {
        // KO���i�e���̏����́A�e���̃N���X���ŏ����j
        CManager::SoundPlay(CSound::LABEL_SE_KO);

        m_fCurrentEnergy = 0.0f;
        SetDisp(false);
    }

    // ���𐶐����Ă��邩�ǂ���
    if (m_pLightGuard)
    {
        // �����g���Ă���Ȃ�
        if (m_bUsingGuard)
        {
            // �����蔻���ς���
            SetCollisionSizeDefence(TANK_COLLISION_SIZE_GUARD);

            // �ϐ��錾
            D3DXVECTOR3 playerRot = CCharacter::GetRot();   // �v���C���[�̌����Ă������
            D3DXVECTOR3 slidePos = DEFAULT_VECTOR;          // ���炷�ʒu
            D3DXVECTOR3 shieldPos = DEFAULT_VECTOR;         // ���̈ʒu

            // �����ʒu�����炷
            slidePos.x = TANK_GUARD_DISTANCE * -sinf(playerRot.y);
            slidePos.z = TANK_GUARD_DISTANCE * -cosf(playerRot.y);

            // ���̈ʒu�����߂�
            shieldPos = GetPos() + slidePos;

            // �`���[�W�ʂɉ����āA�F��ς���
            D3DXCOLOR color = TANK_GUARD_COLOR;
            float gDownValue = 0.0933f * (float)m_nCntGuards;
            color.g -= gDownValue;

            // �\���𔽉f
            m_pLightGuard->SetUseDraw(true);
            m_pLightGuard->SetRot(playerRot);
            m_pLightGuard->SetPos(shieldPos);
            m_pLightGuard->SetColor(color);
        }
        else
        {
            SetCollisionSizeDefence(TANK_COLLISION_SIZE);
            m_pLightGuard->SetUseDraw(false);
            m_pLightGuard->SetColor(TANK_GUARD_COLOR);
        }
    }
}

//=============================================================================
// �}�l�L�����[�h�̍X�V����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::UpdateMannequin(void)
{
    CManager::MODE mode = CManager::GetMode();

    switch (mode)
    {
    case CManager::MODE_CUSTOM:
    {
        // �J�X�^�}�C�Y��ʂł̑ҋ@
        GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);

        // �����ς�����A���������
        if (m_nCntAttackAnimTime > 0)
        {
            // ���������
            m_nCntAttackAnimTime--;
            GetAnimation()->SetAnimation(ANIM_WEAPON_LOOK);
        }

        // �\�����Ȃ�
        if (GetDisp())
        {
            // ���͏���
            Input();

            // 1P�́A�L�[�{�[�h�ŉE�X�e�B�b�N�̉�]���ł���
            if (m_nIdxControlAndColor == PLAYER_1)
            {
                CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
                if (pInputKeyboard->GetKeyboardPress(DIK_UP) ||
                    pInputKeyboard->GetKeyboardPress(DIK_LEFT) ||
                    pInputKeyboard->GetKeyboardPress(DIK_DOWN) ||
                    pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
                {
                    m_controlInput.bTiltedRightStick = true;

                    // �p�x�����߂�
                    if (pInputKeyboard->GetKeyboardPress(DIK_LEFT))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(-45.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(-135.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(-90.0f);
                        }
                    }
                    else if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(45.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(135.0f);
                        }
                        else if (pInputKeyboard->GetKeyboardPress(DIK_LEFT))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(90.0f);
                        }
                    }
                    else if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                    }
                    else if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
                    {
                        if (pInputKeyboard->GetKeyboardPress(DIK_UP))
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(0.0f);
                        }
                        else
                        {
                            m_controlInput.fRightStickAngle = D3DXToRadian(180.0f);
                        }
                    }
                }
            }

            // �E�X�e�B�b�N���|��Ă���Ȃ������ς���
            D3DXVECTOR3 rot = GetRot();
            const float ROT_SPEED = 3.0f;
            if (m_controlInput.bTiltedRightStick)
            {
                // �E��]
                if (STICK_RIGHT(m_controlInput.fRightStickAngle))
                {
                    rot.y -= D3DXToRadian(ROT_SPEED);
                }
                else if (STICK_LEFT(m_controlInput.fRightStickAngle))
                {
                    // ����]
                    rot.y += D3DXToRadian(ROT_SPEED);
                }
            }

            // ��]�̐���
            if (rot.y > D3DXToRadian(180.0f) || rot.y < D3DXToRadian(-180.0f))
            {
                rot.y *= -1;
            }

            // ��]�̐ݒ�
            SetRot(rot);

            // �J�X�^�}�C�Y��ʂ�UI�̍X�V
            m_pUI_Custom_Atk->SetLeftToRightGauge(MAX_ATK, m_fAtk);
            m_pUI_Custom_Def->SetLeftToRightGauge(MAX_DEF, m_fDef);
            m_pUI_Custom_Spd->SetLeftToRightGauge(MAX_SPD, m_fSpd);
            m_pUI_Custom_Wei->SetLeftToRightGauge(MAX_WEI, m_fWei);
            if (m_bDispAbility)
            {
                m_pUI_Custom_Ability->SetDisp(true);
                m_pText_Custom_Ex_Head->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Ex_Up->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Ex_Down->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Ex_Wep->SetColor(TEXT_EXIST_COLOR);
                m_pText_Custom_Sp->SetColor(TEXT_EXIST_COLOR);
            }
            else
            {
                m_pUI_Custom_Ability->SetDisp(false);
                m_pText_Custom_Ex_Head->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Ex_Up->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Ex_Down->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Ex_Wep->SetColor(TEXT_NOT_EXIST_COLOR);
                m_pText_Custom_Sp->SetColor(TEXT_NOT_EXIST_COLOR);
            }
        }
        else
        {
            // ��\���Ȃ�A�e�\����������
            m_pUI_Custom_Atk->SetLeftToRightGauge(MAX_ATK, 0);
            m_pUI_Custom_Def->SetLeftToRightGauge(MAX_DEF, 0);
            m_pUI_Custom_Spd->SetLeftToRightGauge(MAX_SPD, 0);
            m_pUI_Custom_Wei->SetLeftToRightGauge(MAX_WEI, 0);
            m_pUI_Custom_Ability->SetDisp(false);
            m_pText_Custom_Ex_Head->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Ex_Up->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Ex_Down->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Ex_Wep->SetColor(TEXT_NOT_EXIST_COLOR);
            m_pText_Custom_Sp->SetColor(TEXT_NOT_EXIST_COLOR);
        }

        // �A�j���[�V����������
        CCharacter::Update();
        break;
    }

    case CManager::MODE_RESULT:
    {
        // ���U���g��ʂł̃A�j���[�V����
        switch (m_rank)
        {
        case RANK_1:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            m_nCntAttackAnimTime++;
            if (m_nCntAttackAnimTime > PLAYER_VICTORY_WAIT_START_FRAME)
            {
                m_nCntAttackAnimTime = PLAYER_VICTORY_WAIT_START_FRAME;
                GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            }
            else if (m_nCntAttackAnimTime == PLAYER_VICTORY_VOICE_FRAME)
            {
                //switch (m_voiceSet)
                //{
                //case VOICE_SET_ROBO:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_ICARUS);
                //    break;
                //case VOICE_SET_WOMAN:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_KLEINOD);
                //    break;
                //case VOICE_SET_GHOST:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_KNIGHT);
                //    break;
                //case VOICE_SET_OOO:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_OOO);
                //    break;
                //case VOICE_SET_MAN:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_RANGER);
                //    break;
                //case VOICE_SET_BOY:
                //    CManager::SoundPlay(CSound::LABEL_VOICE_WIN_X);
                //    break;
                //}
            }
            break;
        case RANK_2:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            break;
        case RANK_3:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            break;
        case RANK_4:
            GetAnimation()->SetAnimation(ANIM_CUSTOM_IDLE);
            break;
        }

        // �A�j���[�V����������
        CCharacter::Update();
        break;
    }
    }

}

//=============================================================================
// �v���C���[������UI�̍X�V����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::UpdateGameUI(void)
{
    // SP�Q�[�W�ƃp�[�Z���g���l���X�V
    D3DXVECTOR3 spGaugeSize = m_pUI_SP->GetMemorySize();
    spGaugeSize.x *= m_fCurrentEnergy / m_fCurrentEnergyMax;
    spGaugeSize.y *= m_fCurrentEnergy / m_fCurrentEnergyMax;
    m_pUI_SP->SetSize(spGaugeSize);
    int nDispNumber = (int)((m_fCurrentEnergy / m_fCurrentEnergyMax) * 100.0f);
    m_pNumArray_SP->SetDispNumber(nDispNumber);

    // �K�E�Q�[�WMAX�G�t�F�N�g
    if (m_fCurrentEnergy >= m_fCurrentEnergyMax)
    {
        m_nCntCurrentEnergyMaxTime++;
        if (m_nCntCurrentEnergyMaxTime > PLAYER_SP_GAUGE_MAX_EFFECT_INTERVAL)
        {
            m_nCntCurrentEnergyMaxTime = 0;
            D3DXVECTOR3 bodyPos = GetPartsPos(PARTS_BODY);
            CEffect2D *pSp1 = CEffect2D::Create(CEffectData::TYPE_SP_MAX_1, ConvertScreenPos(bodyPos));
            pSp1->SetPlayer(this);
            CEffect2D *pSp2 = CEffect2D::Create(CEffectData::TYPE_SP_MAX_2, ConvertScreenPos(bodyPos));
            pSp2->SetPlayer(this);
        }
    }

    //// ������HP�ƃ{�[���̑����֌W�Ȃ�AHP�Q�[�W��_��
    //float fDamage = CGame::GetBall()->GetSpeed() * PLAYER_TAKE_DAMAGE_RATE_FROM_BALL;
    //D3DXCOLOR col = m_pUI_HP->GetCol();
    //if (m_fLife <= fDamage)
    //{
    //    if (col.a == 1.0f)
    //    {
    //        m_pUI_HP->SetCol(D3DXCOLOR(col.r, col.g, col.b, 0.0f));
    //    }
    //    else
    //    {
    //        m_pUI_HP->SetCol(D3DXCOLOR(col.r, col.g, col.b, 1.0f));
    //    }
    //}
    //else
    //{
    //    m_pUI_HP->SetCol(D3DXCOLOR(col.r, col.g, col.b, 1.0f));
    //}

    // ��P���̕\���̈ʒu�X�V�i���Ⴊ�݁A�������̓_�E�����N���オ�蒆�Ȃ�\���̈ʒu��������j
    if (GetDisp())
    {
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
        float fSizeY = collisionSizeDefence.y;
        DAMAGE_STATE damageState = GetDamageState();
        if (damageState == DAMAGE_STATE_BIG || damageState == DAMAGE_STATE_STAND_UP)
        {
            fSizeY *= PLAYER_SQUAT_CUT_COLLISION_SIZE;
        }
        m_pUI_Playable->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, fSizeY + 50.0f, 0.0f));
        m_pUI_Playable->SetDisp(true);
    }
    else
    {
        m_pUI_Playable->SetDisp(false);
    }
}

//=============================================================================
// ���ꂽ���̋���
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::DeadMove(void)
{
    // �d�����Ă��Ȃ��Ȃ�
    if (m_nCntStopTime <= 0)
    {
        // ���X�|�[�����Ԃ𐔂���
        m_nCntRespawnTime++;

        // �ʒu���擾
        D3DXVECTOR3 pos = DEFAULT_VECTOR;
        pos = GetPos();

        // �ړ��ʐ���
        D3DXVECTOR3 move = GetMove();
        move.x *= PLAYER_CONTROL_MOVE_DEATH;

        // �ړ��ʂƈʒu�����т���
        pos += move;

        // �d��
        move.y -= PLAYER_TAKE_DAMAGE_BLOWN_GRAVITY;

        // �����Ȃ��Ƃ���Ŏ~�߂Ă���
        if (pos.y < PLAYER_DEATH_STOP_POS_Y)
        {
            pos.y = PLAYER_DEATH_STOP_POS_Y;
        }

        // �ʒu�A�ړ��ʂ𔽉f
        SetPos(pos);
        SetMove(move);

        // ������΂��ꃂ�[�V����
        GetAnimation()->SetAnimation(ANIM_BLOWN);

        // �A�j���[�V�����X�V
        CCharacter::Update();

        // ���X�|�[��
        if (m_nCntRespawnTime >= RESPAWN_FRAME)
        {
            Respawn();
        }
    }
    else
    {
        // �d�����Ԃ��J�E���g
        m_nCntStopTime--;
    }
}

//=============================================================================
// ���n���Ƀ��Z�b�g����ϐ�����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::ResetOnGround(void)
{
    m_nCntPressJump = 0;
    m_bUsedSecondJump = false;
    m_nCntStartGlide = 0;
}

//=============================================================================
// �U������Ń��Z�b�g����ϐ�����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::ResetAttack(void)
{
    m_nCntAttackTime = 0;
    m_nCntAttackAnimTime = 0;
    m_attackState = ATTACK_STATE_NONE;
    memset(m_abUseAvoidMultipleHits, false, sizeof(m_abUseAvoidMultipleHits));
    m_bUsingGuard = false;
    SetTakeKnockBack(true);
}

//=============================================================================
// ���X�|�[������
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Respawn(void)
{
    // ���X�|�[��
    CFortress *pFortress = CGame::GetFortress();
    D3DXVECTOR3 respawnPos = pFortress->GetPlayerSpawnPos(m_nIdxControlAndColor);
    SetPos(respawnPos);
    SetRot(pFortress->GetRot());
    SetDisp(true);
    SetUpLife(GetMaxLife());

    // �����̃��Z�b�g�֐�
    ResetOnGround();
    ResetAttack();

    // �����o�ϐ��̃��Z�b�g
    SetMove(DEFAULT_VECTOR);
    m_nCntLandingTime = 0;
    m_bGroundOld = false;
    m_nCntStopTime = 0;
    m_nCntRespawnTime = 0;

    SetTakeDamageTime(0);
    SetDamageState(DAMAGE_STATE_NONE);

    // ���X�|�[���G�t�F�N�g����
    CEffect3D::Emit(CEffectData::TYPE_RESPAWN_0, respawnPos, respawnPos);
    CEffect3D::Emit(CEffectData::TYPE_RESPAWN_1, respawnPos, respawnPos);

    m_fCurrentEnergy = 0.0f;
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V���A�r�c�I��i�N���b�s���O�}�X�N�Ή��j
//=============================================================================
void CPlayer::Draw(void)
{
    //// �K�E�Z�������Ă���Ƃ��́A�\��������
    //if (m_pUI_Playable)
    //{
    //    if (CGame::GetCurrentSpShot())
    //    {
    //        m_pUI_Playable->SetDisp(false);
    //    }
    //    else
    //    {
    //        m_pUI_Playable->SetDisp(true);
    //    }
    //}

    // �\������Ȃ�A�`��
    if (GetDisp())
    {
        // �N���b�s���O�}�X�N
        LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
        if (m_pClipingMusk)
        {
            m_pClipingMusk->Draw();
            //�X�e���V���̐ݒ�
            pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
            pDevice->SetRenderState(D3DRS_STENCILREF, m_pClipingMusk->GetReferenceValue() + 1);
            pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
            pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

            pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
            pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
        }

        // �L�����N�^�[
        CCharacter::Draw();

        // �N���b�s���O�}�X�N�̌㏈��
        if (m_pClipingMusk)
        {
            //�X�e���V��������
            pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        }
    }
    else
    {
        // �}�l�L�����[�h�łȂ��Ȃ�
        if (!m_bMannequin)
        {
            // ���ꂽ���̕`��
            CCharacter::DeathDraw();
        }
    }
}

//=============================================================================
// �C���X�^���X����
// Author : �㓡�T�V��
//=============================================================================
CPlayer * CPlayer::CreateInGame(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxCreate, int nIdxControlAndColor,
    AI_LEVEL AIlevel, int role, bool bUseKeyboard)
{
    // �������m��
    CPlayer *pPlayer = NULL;
    pPlayer = new CPlayer;

    // �e���̏���ݒ�
    pPlayer->CCharacter::SetPos(pos);
    pPlayer->CCharacter::SetRot(rot);
    pPlayer->CCharacter::SetRotDest(rot);
    pPlayer->CCharacter::SetHPDisp(nIdxControlAndColor);

    // �ǂݍ��ގ�ނ̐ݒ�
    pPlayer->m_nIdxControlAndColor = nIdxControlAndColor;
    pPlayer->m_role = role;

    // ������
    pPlayer->Init(pos, DEFAULT_SCALE);

    // ���т��郁���o�ϐ��̏�����
    pPlayer->m_nIdxCreate = nIdxCreate;
    pPlayer->m_AIlevel = AIlevel;
    pPlayer->m_bUseKeyboard = bUseKeyboard;
    if (pPlayer->m_AIlevel != AI_LEVEL_NONE)
    {
        pPlayer->m_pAI = CAi::Create(pPlayer);
    }
    pPlayer->SetUseControllerEffectByTakeDamage(pPlayer->GetUseControllerEffect());

    // UI�𐶐�
    D3DXCOLOR playableCol = DEFAULT_COLOR;
    D3DXCOLOR spGagueCol = DEFAULT_COLOR;
    int nTexTypePlayable = 0;
    int nTexTypePlayer = 0;
    switch (pPlayer->m_nIdxControlAndColor)
    {
    case PLAYER_1:
        playableCol = PLAYER_COLOR_1;
        spGagueCol = D3DXCOLOR(0.768f, 0.470f, 0.470f, 1.0f);
        nTexTypePlayable = 21;
        nTexTypePlayer = 78;
        break;
    case PLAYER_2:
        playableCol = PLAYER_COLOR_2;
        spGagueCol = D3DXCOLOR(0.501f, 0.607f, 0.737f, 1.0f);
        nTexTypePlayable = 22;
        nTexTypePlayer = 79;
        break;
    case PLAYER_3:
        playableCol = PLAYER_COLOR_3;
        spGagueCol = D3DXCOLOR(0.513f, 0.654f, 0.509f, 1.0f);
        nTexTypePlayable = 23;
        nTexTypePlayer = 80;
        break;
    case PLAYER_4:
        playableCol = PLAYER_COLOR_4;
        spGagueCol = D3DXCOLOR(0.760f, 0.623f, 0.478f, 1.0f);
        nTexTypePlayable = 24;
        nTexTypePlayer = 81;
        break;
    }
    switch (pPlayer->m_AIlevel)
    {
    case AI_LEVEL_1:
        nTexTypePlayable = 25;
        break;
    case AI_LEVEL_2:
        nTexTypePlayable = 27;
        break;
    case AI_LEVEL_3:
        nTexTypePlayable = 28;
        break;
    }
    // HP�Q�[�W�i�L�����N�^�[�Ɉڍs���܂����j
    const float UI_SIZE_X = 294.0f; // �����̒l���AUI�̑�̂̉����ɍ��킹��
    const float SPACE_SIZE = (SCREEN_WIDTH - (UI_SIZE_X * CGame::GetNumAllPlayer())) / (CGame::GetNumAllPlayer() + 1);
    const float FIRST_UI_POS_X = SPACE_SIZE + (UI_SIZE_X / 2.0f);
    const float NEXT_UI_POS_X = UI_SIZE_X + SPACE_SIZE;
    float fDigitPosX = FIRST_UI_POS_X + (NEXT_UI_POS_X * (float)pPlayer->m_nIdxCreate);

    // �K�E�Q�[�W
    CUI::Create(76, D3DXVECTOR3(fDigitPosX - 80.0f, 60.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0, DEFAULT_COLOR);
    pPlayer->m_pUI_SP = CUI::Create(77, D3DXVECTOR3(fDigitPosX - 80.0f, 60.0f, 0.0f), D3DXVECTOR3(85.0f, 85.0f, 0.0f), 0, spGagueCol);
    CUI::Create(86, D3DXVECTOR3(fDigitPosX - 57.5f, 60.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 0, DEFAULT_COLOR);
    pPlayer->m_pNumArray_SP = CNumberArray::Create(12, D3DXVECTOR3(fDigitPosX - 87.5f, 60.0f, 0.0f), 15.0f,
        DEFAULT_COLOR, 0, false);

    // Player�\��
    CUI::Create(nTexTypePlayer, D3DXVECTOR3(fDigitPosX + 10.0f, 50.0f, 0.0f), D3DXVECTOR3(82.5f, 54.0f, 0.0f), 0, DEFAULT_COLOR);

    // �v���C�A�u���\��
    pPlayer->m_pUI_Playable = CUI::Create(nTexTypePlayable, DEFAULT_VECTOR, D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0, playableCol);

    // ���̏�����
    pPlayer->m_pLightGuard = CModelEffect::Create(30, DEFAULT_VECTOR, DEFAULT_VECTOR,
        TANK_GUARD_COLOR);

    // �񕜖����w����
    pPlayer->m_pHealingCircle = CBullet::Create(CBullet::TYPE_HEALER_SKY, DEFAULT_VECTOR, DEFAULT_VECTOR, OBJTYPE_PLAYER);

    return pPlayer;
}

//=============================================================================
// �J�X�^�}�C�Y��ʂł̐���
// Author : �㓡�T�V��
//=============================================================================
CPlayer * CPlayer::CreateInCustom(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxControlAndColor, bool bDisp)
{
    // �������m��
    CPlayer *pPlayer = NULL;
    pPlayer = new CPlayer;

    // �e���̏���ݒ�
    pPlayer->CCharacter::SetPos(pos);
    pPlayer->CCharacter::SetRot(rot);

    // �ǂݍ��ގ�ނ̐ݒ�
    pPlayer->m_nIdxControlAndColor = nIdxControlAndColor;

    // UI�𐶐�
    D3DXVECTOR3 startPos = D3DXVECTOR3(205.0f, 293.5f, 0.0f);
    D3DXVECTOR3 clipingPos = DEFAULT_VECTOR;
    const D3DXVECTOR3 gaugeSize = D3DXVECTOR3(210.0f, 22.0f, 0.0f);
    const D3DXVECTOR3 abilitySize = D3DXVECTOR3(297.0f, 155.0f, 0.0f);
    D3DXVECTOR3 abilityPos = D3DXVECTOR3(167.0f, 200.5f, 0.0f);
    switch (pPlayer->m_nIdxControlAndColor)
    {
    case PLAYER_1:
        clipingPos = D3DXVECTOR3(167.0f, 390.0f, 0.0f);
        break;
    case PLAYER_2:
        startPos.x += 315.0f;
        abilityPos.x += 315.0f;
        clipingPos = D3DXVECTOR3(482.0f, 390.0f, 0.0f);
        break;
    case PLAYER_3:
        startPos.x += 315.0f * PLAYER_3;
        abilityPos.x += 315.0f * PLAYER_3;
        clipingPos = D3DXVECTOR3(797.0f, 390.0f, 0.0f);
        break;
    case PLAYER_4:
        startPos.x += 315.0f * PLAYER_4;
        abilityPos.x += 315.0f * PLAYER_4;
        clipingPos = D3DXVECTOR3(1112.0f, 390.0f, 0.0f);
        break;
    }
    pPlayer->m_pUI_Custom_Ability = CUI::Create(73, abilityPos, abilitySize, 0, DEFAULT_COLOR);
    float fDigitPosY = 0.0f;
    const float DIGIT_UI_VALUE = 31.5f;
    pPlayer->m_pUI_Custom_Def = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_DEF_COLOR);
    pPlayer->m_pUI_Custom_Def->SetActionInfo(0, CUI::ACTION_GAUGE, false); // �Q�[�W�ɕς���
    fDigitPosY += DIGIT_UI_VALUE;

    pPlayer->m_pUI_Custom_Atk = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_ATK_COLOR);
    pPlayer->m_pUI_Custom_Atk->SetActionInfo(0, CUI::ACTION_GAUGE, false); // �Q�[�W�ɕς���
    fDigitPosY += DIGIT_UI_VALUE;

    pPlayer->m_pUI_Custom_Spd = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_SPD_COLOR);
    pPlayer->m_pUI_Custom_Spd->SetActionInfo(0, CUI::ACTION_GAUGE, false); // �Q�[�W�ɕς���
    fDigitPosY += DIGIT_UI_VALUE;

    pPlayer->m_pUI_Custom_Wei = CUI::Create(75, startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), gaugeSize, 0, CUSTOM_WEI_COLOR);
    pPlayer->m_pUI_Custom_Wei->SetActionInfo(0, CUI::ACTION_GAUGE, false); // �Q�[�W�ɕς���

                                                                           // �e�L�X�g�𐶐�
    startPos += D3DXVECTOR3(-105.0f, -155.0f, 0.0f); // UI�̃X�e�[�^�X�o�[����A�A�r���e�B�̃e�L�X�g�ֈʒu�����킹��
    fDigitPosY = 0.0f;
    const float DIGIT_TEXT_VALUE = 26.0f;
    const int textSize = 20;
    pPlayer->m_pText_Custom_Ex_Head = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "�Ȃ�",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Ex_Up = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "�Ȃ�",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Ex_Down = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "�Ȃ�",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Ex_Wep = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "�Ȃ�",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);
    fDigitPosY += DIGIT_TEXT_VALUE;

    pPlayer->m_pText_Custom_Sp = CText::Create(startPos + D3DXVECTOR3(0.0f, fDigitPosY, 0.0f), textSize, "�Ȃ�",
        CText::ALIGN_LEFT, "Reggae One", TEXT_NOT_EXIST_COLOR);

    // �N���b�s���O�𐶐�
    pPlayer->ApplyMusk(clipingPos, D3DXVECTOR3(298.0f, 625.0f, 0.0f));

    // ������
    pPlayer->Init(pos, DEFAULT_SCALE);

    // ���т��郁���o�ϐ��̏�����
    pPlayer->SetDisp(bDisp);

    // �}�l�L�����[�h��
    pPlayer->m_bMannequin = true;

    return pPlayer;
}

//=============================================================================
// ���U���g��ʂł̐���
// Author : �㓡�T�V��
//=============================================================================
CPlayer * CPlayer::CreateInResult(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdxControlAndColor, RANK rank)
{
    // �������m��
    CPlayer *pPlayer = NULL;
    pPlayer = new CPlayer;

    // �e���̏���ݒ�
    pPlayer->CCharacter::SetPos(pos);
    pPlayer->CCharacter::SetRot(rot);

    // �ǂݍ��ގ�ނ̐ݒ�
    pPlayer->m_nIdxControlAndColor = nIdxControlAndColor;

    // ������
    pPlayer->Init(pos, DEFAULT_SCALE);

    // ���т��郁���o�ϐ��̏�����
    pPlayer->m_rank = rank;
    if (pPlayer->m_rank != RANK_1)
    {
        //// 1�ʈȊO�́A�����`�悵�Ȃ�
        //pPlayer->SetDrawWeapon(false);
    }

    // �}�l�L�����[�h��
    pPlayer->m_bMannequin = true;

    return pPlayer;
}

//=============================================================================
// �s��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Movement(float fSpeed)
{
    // �ʒu�A�ړ��ʁA������Ԃ��擾
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 move = DEFAULT_VECTOR;
    DAMAGE_STATE damageState = GetDamageState();
    pos = GetPos();
    move = GetMove();

    // 1F�O�̈ʒu���L��
    SetPosOld(pos);

    // 1F�O�̈ړ��ʂ��L��
    SetMoveOld(move);

    // ���Ɖ��s���̈ړ��ʐ���
    ControlMove(move.x, m_bGround);
    ControlMove(move.z, m_bGround);

    // ���[�V�������܂��͑ҋ@�ɂ���
    GetAnimation()->SetAnimation(m_waitMotion);

    // �v���C���[�ړ�����
    Control(fSpeed, move);

    // �ړ��ʂƈʒu�����т���
    pos += move;

    // �n�ʂ���Ȃ�
    if (pos.y > 0.0f)
    {
        // �d��
        float fGravity = PLAYER_BASE_MINIMUM_GRAVITY + (m_fWei * PLAYER_ADD_BASE_GRAVITY_RATE);
        if (damageState == DAMAGE_STATE_BLOWN)
        {
            // ������΂��ꒆ�͌Œ�l
            fGravity = PLAYER_TAKE_DAMAGE_BLOWN_GRAVITY;
        }
        move.y -= fGravity;

        // �n�ʂɂ��Ȃ�
        m_bGround = false;
    }
    else
    {
        // �n�ʂɂ���Ȃ�A�d�͂������Ȃ��ŃW�����v�\�A�}�~���̃`�F�b�N�������A��i�W�����v������
        pos.y = 0.0f;
        move.y = 0.0f;
        m_bGround = true;
    }

    //====================================================
    // �U������
    AttackUpdate(pos, move);

    // �U���̐���
    AttackGenerator();

    // �W�����v
    Jump(move);

    // �ړ����[�V�����̊Ǘ�
    MoveMotion();

    // �U�����[�V�����ɂ��邩�ǂ���
    AttackMotion();
    //====================================================

    //====================================================
    // �h�䏈��
    // �������̍X�V
    DamageUpdate(pos, move);

    // �������[�V�����ɂ��邩�ǂ���
    DamageMotion();
    //====================================================

    // ��]����
    if (m_controlInput.bPressR2 && m_bGround)
    {
        // �����Œ�
        D3DXVECTOR3 rot = GetRot();
        SetRotDestY(rot.y);
    }
    else
    {
        RotControl();
    }

    // �}�b�v����
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    D3DXVECTOR3 myCubeSize = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
    D3DXVECTOR3 posOld = GetPosOld();
    CGame::MapLimit(pos, posOld, myCubeSize);

    // �ʒu�A�ړ��ʂ𔽉f
    SetPos(pos);
    SetMove(move);

    // 1F�O�A�W�����v�ł������ǂ������L�^
    m_bGroundOld = m_bGround;

    // �ړ��v�ǂɃG�i�W�[�𑗂鏈��
    SendEnergyForFortress();

#ifdef COLLISION_TEST
    bool bIsInvincible = GetInvincible();
    if (!bIsInvincible)
    {
        D3DXVECTOR3 size = D3DXVECTOR3(collisionSizeDefence.x, collisionSizeDefence.y, collisionSizeDefence.x);
        CDebug::Create(pos, size, CDebug::TYPE_MOMENT, 65);
    }
#endif // COLLISION_TEST
}

//=============================================================================
// �ړ��n���[�V�����̊Ǘ�
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::MoveMotion(void)
{
    // ���n���[�V�����ɂ��邩�ǂ���
    if (!m_bGroundOld && m_bGround)
    {
        // ���n�̍����i�����蔻��̕��A�������L����j
        D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
        CEffect3D::Emit(CEffectData::TYPE_LANDING_FUGITIVE_DUST, GetPos(), GetPos());

        // ���n���Ԃ�ݒ�
        m_nCntLandingTime = PLAYER_LANDING_TIME;
    }
    if (m_nCntLandingTime > 0)
    {
        // �J�E���g�_�E��
        m_nCntLandingTime--;

        // ���[�V�����𒅒n�ɂ���
        GetAnimation()->SetAnimation(ANIM_LANDING);
    }

    // ����̃J�E���^
    if (m_nCntStartGlide > 0)
    {
        m_nCntStartGlide--;
    }

    // �W�����v���[�V�����ɂ��邩�ǂ���
    if (!m_bGround)
    {
        // ����A�j���[�V�����̃J�E���^��0�ȉ��Ȃ犊��
        if (m_nCntStartGlide <= 0)
        {
            GetAnimation()->SetAnimation(ANIM_GLIDE);
        }
        else
        {
            // ��i�W�����v���g���������ǂ���
            if (m_bUsedSecondJump)
            {
                GetAnimation()->SetAnimation(ANIM_SECOND_JUMP);
            }
            else
            {
                GetAnimation()->SetAnimation(ANIM_JUMP);
            }
        }
    }
}

//=============================================================================
// �v���C���[�̈ړ�����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Control(float fSpeed, D3DXVECTOR3& move)
{
    // ����
    D3DXVECTOR3 rot = GetRot();

    // �n��ōU�����ȊO�Ȃ�i��ɒn��X�C���O�ł͓����Ȃ��j
    if (!m_bGround || m_attackState == ATTACK_STATE_NONE)
    {
        // �������Ă��Ȃ���Ԃ��A���n���ł��Ȃ��Ȃ�
        if (GetDamageState() == DAMAGE_STATE_NONE && m_nCntLandingTime <= 0)
        {
            // �X�e�B�b�N���|��Ă���Ȃ�ړ�
            if (m_controlInput.bTiltedLeftStick)
            {
                if (m_bGround)
                {
                    //// �����̔���
                    //if (fabsf(m_moveOld.x) <= PLAYER_SET_WALK_SMOKE_VALUE)
                    //{
                    //    CEffect3D::Emit(CEffectData::TYPE_WALK_SMOKE_LEFT, GetPos(), GetPos());
                    //}

                    // �ړ��ʂɑ��
                    move.x = sinf(m_controlInput.fLeftStickAngle)*fSpeed;
                    move.z = cosf(m_controlInput.fLeftStickAngle)*fSpeed;

                    // ���[�V����������ɂ���
                    GetAnimation()->SetAnimation(m_walkMotion);

                    //�L�����̌�����ς���
                    SetRotDestY(m_controlInput.fPlayerAngle);
                }
                else
                {
                    // �󒆈ړ��́A���X�ɉ��Z
                    move.x += sinf(m_controlInput.fLeftStickAngle)*fSpeed / PLAYER_CONTROL_MOVE_ADD_RATE_IN_AIR;
                    move.z += cosf(m_controlInput.fLeftStickAngle)*fSpeed / PLAYER_CONTROL_MOVE_ADD_RATE_IN_AIR;
                }
            }

            // �ő呬�x�𒴂��Ȃ��悤�ɂ���
            if (move.x > fSpeed)
            {
                move.x = fSpeed;
            }
            else if (move.x < -fSpeed)
            {
                move.x = -fSpeed;
            }
            if (move.z > fSpeed)
            {
                move.z = fSpeed;
            }
            else if (move.z < -fSpeed)
            {
                move.z = -fSpeed;
            }
        }
    }
}

//=============================================================================
// �W�����v�̏���
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::Jump(D3DXVECTOR3& move)
{
    // �h�䓖���蔻��̑傫���A������Ԃ��擾
    D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
    DAMAGE_STATE damageState = GetDamageState();

    // A�v���X
    if (m_controlInput.bPressA)
    {
        // �������Ă��Ȃ���ԂȂ�i�U�����ł������͐L�΂���j
        if (damageState == DAMAGE_STATE_NONE)
        {
            // �W�����v�̃J�E���^��0���傫���A���Z�J�E���^���Ȃ�
            if (m_nCntPressJump > 0 && m_nCntPressJump <= PLAYER_JUMP_ADD_FRAME)
            {
                // �W�����v�̃J�E���^���Z
                m_nCntPressJump++;

                // �W�����v�ʉ��Z
                move.y += PLAYER_BASE_MINIMUM_GRAVITY + (m_fWei * PLAYER_ADD_BASE_GRAVITY_RATE);
            }
            else if (m_nCntPressJump > PLAYER_JUMP_ADD_FRAME && m_nCntPressJump <= PLAYER_JUMP_KEEP_FRAME)
            {
                // �؋�
                if (move.y <= 0.0f)
                {
                    // �W�����v�̃J�E���^���Z
                    m_nCntPressJump++;

                    move.y = 0.0f;
                }
            }
        }
    }
    else
    {
        // �W�����v�̃J�E���^�����Z�b�g
        m_nCntPressJump = 0;
    }

    // A�g���K�[�i�W�����v�����̃C���[�W�j
    if (m_controlInput.bTriggerA)
    {
        // �������Ă��Ȃ���Ԃ��A�U����Ԃ��Ȃ��Ȃ�
        if (damageState == DAMAGE_STATE_NONE && m_attackState == ATTACK_STATE_NONE)
        {
            // �n�ʂɂ���Ȃ�
            if (m_bGround)
            {
                // �����ɂ���āA�����̌�����ς���
                if (GetRot().y == PLAYER_ROT_LEFT)
                {
                    // �W�����v�̍���
                    CEffect3D::Emit(CEffectData::TYPE_JUMP_FUGITIVE_DUST, GetPos(), GetPos());

                }
                else
                {
                    // �W�����v�̍���
                    CEffect3D::Emit(CEffectData::TYPE_JUMP_FUGITIVE_DUST, GetPos(), GetPos());

                }

                // �W�����v��
                CManager::SoundPlay(CSound::LABEL_SE_JUMP);

                // �W�����v�̏�����
                move.y = PLAYER_JUMP_FIRST_RATE;

                // ����܂ł̃J�E���^��ݒ�
                m_nCntStartGlide = PLAYER_FIRST_JUMP_MOTION_TO_GLIDE;

                // �n�ʂɂ��Ȃ����Ƃ�
                m_bGround = false;

                // �O�̂��ߒ��n���Ԃ����Z�b�g
                m_nCntLandingTime = 0;

                // �W�����v�̃J�E���^���Z
                m_nCntPressJump++;
            }
            else
            {
                // �n�ʂɂ��Ȃ��A��i�W�����v�����Ă��Ȃ��Ȃ�
                if (!m_bUsedSecondJump)
                {
                    // ���i�W�����v�̋�C�̗ւƍ����i�����蔻��̔����̑傫���j
                    CEffect3D::Emit(CEffectData::TYPE_SECOND_JUMP_AIR_RING, GetPos(), GetPos(), collisionSizeDefence.x * 0.5f);
                    CEffect3D::Emit(CEffectData::TYPE_SECOND_JUMP_SMOKE, GetPos(), GetPos());

                    // �W�����v��
                    CManager::SoundPlay(CSound::LABEL_SE_JUMP);

                    //// 1F����������ς��邱�Ƃ��ł���
                    //RotControl();

                    // �W�����v�̏�����
                    move.y = PLAYER_JUMP_FIRST_RATE * PLAYER_NEXT_JUMP_DOWN_RATE;

                    // ����܂ł̃J�E���^��ݒ�
                    m_nCntStartGlide = PLAYER_NEXT_JUMP_MOTION_TO_GLIDE;

                    // ��i�W�����v���g�����t���O��true��
                    m_bUsedSecondJump = true;

                    // �O�̂��ߒ��n���Ԃ����Z�b�g
                    m_nCntLandingTime = 0;

                    // �W�����v�̃J�E���^���Z
                    m_nCntPressJump++;
                }
            }
        }
    }
}

//=============================================================================
// �����̍X�V����
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::DamageUpdate(D3DXVECTOR3 pos, D3DXVECTOR3& move)
{
    // ������ԁA�������Ԃ��擾
    DAMAGE_STATE damageState = GetDamageState();
    int nTakeDamageTime = GetTakeDamageTime();

    switch (damageState)
    {
    case DAMAGE_STATE_BLOWN:
        // ������΂��ꂩ��_�E���ւ̑J��
        if (m_bGround)
        {
            // �n�ʂɂ��Ă��A���x�������Ă���Ȃ�
            if (fabsf(move.x) < KNOCK_BACK_STOP_BORDER)
            {
                move.x = 0.0f;
                damageState = DAMAGE_STATE_BIG;
                nTakeDamageTime = TAKE_DAMAGE_BIG_FRAME;
            }
        }
        else
        {
            // �󒆂̑��x���Œ���ێ�����
            if (fabsf(move.x) < KNOCK_BACK_STOP_BORDER)
            {
                if (move.x > 0.0f)
                {
                    move.x = KNOCK_BACK_STOP_BORDER;
                }
                else
                {
                    move.x = -KNOCK_BACK_STOP_BORDER;
                }
            }
        }
        break;
    case DAMAGE_STATE_BIG:
        // �N���オ��\���ԂȂ�
        if (nTakeDamageTime <= PLAYER_TAKE_DAMAGE_START_QUICK_STAND_UP)
        {
            // ���N���オ��or�z���N���オ��A�s�[��
            if (m_controlInput.bTiltedLeftStick)
            {
                damageState = DAMAGE_STATE_STAND_UP;
                nTakeDamageTime = PLAYER_TAKE_DAMAGE_STAND_UP_FRAME;
            }
            else if (m_controlInput.bTriggerX)
            {
                // �z���G�t�F�N�g
                D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
                CEffect3D::Emit(CEffectData::TYPE_ABSORB, pos + D3DXVECTOR3(0.0f, collisionSizeDefence.y / 2.0f, 0.0f),
                    pos + D3DXVECTOR3(0.0f, collisionSizeDefence.y / 2.0f, 0.0f), collisionSizeDefence.x);

                // �_���[�W��Ԃ̃��Z�b�g
                damageState = DAMAGE_STATE_NONE;
                nTakeDamageTime = 0;

                //// ���ʋN���オ��U���������ꏊ
                //m_attackState = ATTACK_STATE_ABSORB;
                //m_nCntAttackTime = ATTACK_ABSORB_WHOLE_FRAME;
                //Absorb(pos);
            }
        }
        break;
    }

    // ������ԁA�������Ԃ��X�V
    SetDamageState(damageState);
    SetTakeDamageTime(nTakeDamageTime);
}

//=============================================================================
// �������[�V�����̊Ǘ�
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::DamageMotion(void)
{
    // ������Ԃɉ����āA���[�V���������߂�
    DAMAGE_STATE damageState = GetDamageState();
    switch (damageState)
    {
    case DAMAGE_STATE_SMALL:
        GetAnimation()->SetAnimation(ANIM_DAMAGE_SMALL);
        break;
    case DAMAGE_STATE_BIG:
        GetAnimation()->SetAnimation(ANIM_DAMAGE_BIG);
        break;
    case DAMAGE_STATE_STAND_UP:
        GetAnimation()->SetAnimation(ANIM_STAND_UP);
        break;
    case DAMAGE_STATE_BLOWN:
        GetAnimation()->SetAnimation(ANIM_BLOWN);
        break;
    }
}

//=============================================================================
// �����E���h���Z�b�g����X�e�[�^�X
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::ResetStatusEveryRound(void)
{
    //// �������Ă���Ȃ�
    //if (m_bDisp)
    //{
    //    // ���E���h���W�F�l
    //    if (IS_BITON(m_exFlag, EX_FLAG_ROUND_HEAL))
    //    {
    //        // �ő�HP�Ȃ�A�G�t�F�N�g���񕜂��Ȃ�
    //        if (m_fLife != m_fDef)
    //        {
    //            // ��
    //            const float HEAL_VALUE = 0.0011f;
    //            m_fLife += m_fDef * HEAL_VALUE;

    //            // �񕜂̏��
    //            if (m_fLife > m_fDef)
    //            {
    //                m_fLife = m_fDef;
    //            }
    //        }
    //    }
    //}

    //// �K�E�Q�[�W
    //if (IS_BITOFF(m_exFlag, EX_FLAG_SAVE_SP_GAUGE))
    //{
    //    m_fSpGaugeCurrent = 0.0f;
    //}

    //// �o���A��Ԃ����Z�b�g
    //if (m_bSpBarrier)
    //{
    //    m_bSpBarrier = false;
    //}
}

//=============================================================================
// �G�i�W�[�𓾂鏈��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::GainEnergy(const float fEnergy)
{
    // �G�i�W�[���Z
    m_fCurrentEnergy += fEnergy;
    if (m_fCurrentEnergy > m_fCurrentEnergyMax)
    {
        m_fCurrentEnergy = m_fCurrentEnergyMax;
    }
}

//=============================================================================
// �R���g���[���̐U�����g�p���邩�ǂ���
// Author : �㓡�T�V��
//=============================================================================
bool CPlayer::GetUseControllerEffect(void)
{
    bool bUseControllerEffect = false;

    // AI�łȂ����A�L�[�{�[�h����łȂ��Ȃ�A�U�����g��
    if (m_AIlevel == AI_LEVEL_NONE && !m_bUseKeyboard)
    {
        bUseControllerEffect = true;
    }

    // ������I�v�V�����ŋ���OFF�ł���悤�ɂ����ɏ���

    return bUseControllerEffect;
}

//=============================================================================
// �N���b�s���O�}�X�N��K�p
// Author : �r�c�I��
//=============================================================================
void CPlayer::ApplyMusk(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumTexture)
{
    if (!m_pClipingMusk)
    {
        m_pClipingMusk = CClipingMusk::Create(pos, size, nNumTexture);
    }
}

//=============================================================================
// �e�N�X�`���Ȃ��N���b�s���O�}�X�N��K�p
// Author : �r�c�I��
//=============================================================================
void CPlayer::ApplyMusk(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    if (!m_pClipingMusk)
    {
        m_pClipingMusk = CClipingMusk::Create(pos, size);
    }
}

//=============================================================================
// �ړ��v�ǂɃG�i�W�[�𑗂鏈��
// Author : �㓡�T�V��
//=============================================================================
void CPlayer::SendEnergyForFortress(void)
{
    // �G�i�W�[���Ȃ��Ȃ�A�֐��𔲂���
    if (m_fCurrentEnergy <= 0.0f)
    {
        return;
    }

    // �ړ��v�ǂ����݂���Ȃ�
    CFortress*pFortress = CGame::GetFortress();
    if (pFortress)
    {
        if (pFortress->GetDisp())
        {
            // �������Ă���Ȃ�
            if (IsCollisionCylinder(GetPos(), GetCollisionSizeDefence(), pFortress->GetPos(), D3DXVECTOR2(2000.0f,1000.0f)))
            {
                // �U���t�F�[�Y���ȊO���A�G�i�W�[������Ȃ瑗��
                if (!pFortress->GetAttackPhase() && m_fCurrentEnergy > 0.0f)
                {
                    // �G�i�W�[�{�[������
                    CBullet *pBullet = CBullet::Create(CBullet::TYPE_ENERGY_BALL, GetPartsPos(PARTS_BODY), DEFAULT_VECTOR, OBJTYPE_PLAYER);
                    pBullet->SetWhoContribution(m_nIdxCreate);
                    pBullet->SetDamage(m_fCurrentEnergy);   // �_���[�W�ʂ��`���[�W�ʂɂ���

                    // �v���x�����Z
                    GainContribution((int)m_fCurrentEnergy);
                    m_fCurrentEnergy = 0.0f;
                }
            }
        }
    }
}