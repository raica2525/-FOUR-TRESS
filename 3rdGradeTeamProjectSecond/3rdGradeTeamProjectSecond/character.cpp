//===============================================
//
// �L�����N�^�[���� (character.cpp)
// Author : �㓡�T�V��
//
//===============================================
#define _CRT_SECURE_NO_WARNINGS

//========================
// �C���N���[�h�t�@�C��
//========================
#include "character.h"
#include "animation.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "animation.h"
#include "scene3d.h"
#include "library.h"
#include "game.h"
#include "player.h"
#include "modelData.h"
#include "camera.h"
#include "effect3d.h"
#include "ui.h"
#include "wave.h"
#include "number_array.h"
#include "block.h"

//========================================
// �}�N����`
//========================================
#define PULL_TO_CENTER_VALUE 0.1f
#define PULL_TO_CENTER_VALUE_LIMIT 25.0f

//========================================
// �ÓI�����o�ϐ��錾
//========================================

//=============================================================================
// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CCharacter::CCharacter(OBJTYPE objtype) :CScene(objtype)
{
    m_posOld = DEFAULT_VECTOR;

    m_pos = DEFAULT_VECTOR;
    m_rot = DEFAULT_VECTOR;
    m_nPartsNum = 0;
    memset(m_apModel, 0, sizeof(m_apModel));
    memset(m_aPosDefault, 0, sizeof(m_aPosDefault));
    memset(m_anIndexParent, 0, sizeof(m_anIndexParent));
    memset(m_aPartsType, 0, sizeof(m_aPartsType));

    m_pAnimation = NULL;
    m_cAnimFilePass = NULL;

    m_bUseAnimation = true;
    m_rotDest = DEFAULT_VECTOR;
    m_pEffect3d_Shadow = NULL;
    m_collisionSizeDefence = D3DXVECTOR2(0.0f, 0.0f);

    m_fLife = 0.0f;
    m_fLife_red = 0.0f;
    m_fMaxLife = 0.0f;
    m_nCntStopRedLifeTime = 0;
    m_pUI_HP = NULL;
    m_pUI_HP_red = NULL;
    m_pUI_HP_bg = NULL;
    m_HPDisp = HP_DISP_NONE;

    m_move = DEFAULT_VECTOR;
    m_moveOld = DEFAULT_VECTOR;
    m_bUseControllerEffectByTakeDamage = false;
    m_fTurnSpeed = DEFAULT_TURN_SPEED;

    m_bResetAttackByDamage = false;
    m_bDisp = true;
    m_nIdx = 0;

    m_bIsInvincible = false;
    m_nCntTakeDamageTime = 0;
    m_damageState = DAMAGE_STATE_NONE;
    m_bUseWhiteDraw = false;
    m_nCntWhiteDrawTime = 0;
    m_bTakeKnockBack = true;
    m_bTakeWind = false;
    m_lastHit = OBJTYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CCharacter::~CCharacter()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ʒu�����т���
    m_pos = pos;
    m_posOld = pos;

    // ���f�����p�[�c���������m�ۂ��A������
    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        // �������Ă��Ȃ��Ȃ琶��
        if (!m_apModel[nCount])
        {
            m_apModel[nCount] = new CModel;
            m_apModel[nCount]->Init(DEFAULT_VECTOR, DEFAULT_VECTOR);
            m_apModel[nCount]->SetScale(size);
            m_apModel[nCount]->SetPos(m_aPosDefault[nCount]);
        }

        // �J�X�^�}�C�Y�p�ŁA�������Ă��Ă��ǂݍ���
        m_apModel[nCount]->BindModelData(m_aPartsType[nCount]);

        // �A�j���[�V�����𐶐����Ă���Ȃ�
        if (m_pAnimation)
        {
            m_pAnimation->SetAnimPosReset(nCount);
        }
    }

    // �A�j���[�V�����̃��[�h�i�g�����A�������Ă��Ȃ��Ȃ�j
    if (m_bUseAnimation)
    {
        if (!m_pAnimation)
        {
            m_pAnimation = CAnimation::Create(this, m_nPartsNum, m_cAnimFilePass);
        }
    }

    // �Q�[���Ȃ�e�AHP�\���𐶐�
    if (CManager::GetMode() == CManager::MODE_GAME)
    {
        if (!m_pEffect3d_Shadow)
        {
            m_pEffect3d_Shadow = CEffect3D::Create(CEffectData::TYPE_SHADOW, D3DXVECTOR3(pos.x, SHADOW_POS_Y, pos.z));
            m_pEffect3d_Shadow->SetSize(D3DXVECTOR3(m_collisionSizeDefence.x, m_collisionSizeDefence.x, 0.0f));
            m_pEffect3d_Shadow->SetDisp(false); // �L�����N�^�[���ŕ`����Ǘ����邽��
        }

        if (!m_pUI_HP && !m_pUI_HP_red)
        {
            CreateHPGauge();
        }
    }

    // �L�����N�^�[�̃C���f�b�N�X���擾
    m_nIdx = CGame::GetCharacterIdx();

    return S_OK;
}

//=============================================================================
// HP�\����������
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::CreateHPGauge(void)
{
    switch (m_HPDisp)
    {
    case HP_DISP_PLAYER_1:
    case HP_DISP_PLAYER_2:
    case HP_DISP_PLAYER_3:
    case HP_DISP_PLAYER_4:
    {
        const float UI_SIZE_X = 294.0f; // �����̒l���AUI�̑�̂̉����ɍ��킹��
        const float UI_FRAME_SIZE_X = 220.0f;
        const float UI_FRAME_SIZE_Y = 28.0f;
        const float UI_BAR_SIZE_X = 204.0f;
        const float UI_BAR_SIZE_Y = 20.0f;
        const float SPACE_SIZE = (SCREEN_WIDTH - (UI_SIZE_X * CGame::GetNumAllPlayer())) / (CGame::GetNumAllPlayer() + 1);
        const float FIRST_UI_POS_X = SPACE_SIZE + (UI_SIZE_X / 2.0f);
        const float NEXT_UI_POS_X = UI_SIZE_X + SPACE_SIZE;
        float fDigitPosX = FIRST_UI_POS_X + (NEXT_UI_POS_X * (float)m_HPDisp);
        m_pUI_HP_bg = CUI::Create(17, D3DXVECTOR3(fDigitPosX + 50.0f, 80.0f, 0.0f), D3DXVECTOR3(UI_FRAME_SIZE_X, UI_FRAME_SIZE_Y, 0.0f), 0, DEFAULT_COLOR);
        m_pUI_HP_red = CUI::Create(88, D3DXVECTOR3(fDigitPosX + 50.0f, 80.0f, 0.0f), D3DXVECTOR3(UI_BAR_SIZE_X, UI_BAR_SIZE_Y, 0.0f), 0, DEFAULT_COLOR);
        m_pUI_HP_red->SetActionInfo(0, CUI::ACTION_GAUGE, false);
        m_pUI_HP = CUI::Create(18, D3DXVECTOR3(fDigitPosX + 50.0f, 80.0f, 0.0f), D3DXVECTOR3(UI_BAR_SIZE_X, UI_BAR_SIZE_Y, 0.0f), 0, DEFAULT_COLOR);
        m_pUI_HP->SetActionInfo(0, CUI::ACTION_GAUGE, false);
    }
    break;
    case HP_DISP_FOLLOW:
    {
        const D3DXVECTOR3 firstPos = D3DXVECTOR3(-1000.0f, 0.0f, 0.0f);
        const D3DXVECTOR3 bgSize = D3DXVECTOR3(110.0f, 14.0f, 0.0f);
        const D3DXVECTOR3 barSize = D3DXVECTOR3(102.0f, 10.0f, 0.0f);
        m_pUI_HP_bg = CUI::Create(17, firstPos, bgSize, 0, DEFAULT_COLOR);
        m_pUI_HP_bg->SetDisp(false);
        m_pUI_HP_red = CUI::Create(88, firstPos, barSize, 0, DEFAULT_COLOR);
        m_pUI_HP_red->SetActionInfo(0, CUI::ACTION_GAUGE, false);
        m_pUI_HP_red->SetDisp(false);
        m_pUI_HP = CUI::Create(18, firstPos, barSize, 0, DEFAULT_COLOR);
        m_pUI_HP->SetActionInfo(0, CUI::ACTION_GAUGE, false);
        m_pUI_HP->SetDisp(false);
    }
    break;
    }
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::Uninit(void)
{
    // �e������
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetDontUse();
    }

    // HP�\��������
    if (m_pUI_HP)
    {
        m_pUI_HP->SetDontUse();
    }
    if (m_pUI_HP_bg)
    {
        m_pUI_HP_bg->SetDontUse();
    }
    if (m_pUI_HP_red)
    {
        m_pUI_HP_red->SetDontUse();
    }

    // ���f�����p�[�c���A�I�����A�������J��
    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        // ���g������Ȃ�
        if (m_apModel[nCount] != NULL)
        {
            // �I������
            m_apModel[nCount]->Uninit();

            // �������J��
            delete m_apModel[nCount];
            m_apModel[nCount] = NULL;
        }
    }

    // �A�j���[�V���������I�����A�������J��
    if (m_pAnimation != NULL)
    {
        // �I������
        m_pAnimation->Uninit();

        // �������J��
        delete m_pAnimation;
        m_pAnimation = NULL;
    }

    Release();
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::Update(void)
{
    // HP�\�����X�V
    if (m_pUI_HP && m_pUI_HP_red)
    {
        // �ԃQ�[�W�̃J�E���g�_�E��
        if (m_nCntStopRedLifeTime > 0)
        {
            m_nCntStopRedLifeTime--;
        }

        // HP�Q�[�W�A�ԃQ�[�W���X�V
        m_pUI_HP->SetLeftToRightGauge(m_fMaxLife, m_fLife);
        if (m_fLife_red > m_fLife && m_nCntStopRedLifeTime <= 0)
        {
            // �ԃQ�[�W��~���Ԃ��I����Ă���A�X�V����
            const float LIFE_DOWN_SPD = 6.0f;
            m_fLife_red -= LIFE_DOWN_SPD;
        }

        // �ԃQ�[�W�́A���݂̗̑͂������Ȃ�
        if (m_fLife_red < m_fLife)
        {
            m_fLife_red = m_fLife;
        }
        m_pUI_HP_red->SetLeftToRightGauge(m_fMaxLife, m_fLife_red);

        // �Ǐ]����Ȃ�
        if (m_HPDisp == HP_DISP_FOLLOW)
        {
            m_pUI_HP_bg->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, m_collisionSizeDefence.y, 0.0f));
            m_pUI_HP_red->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, m_collisionSizeDefence.y, 0.0f));
            m_pUI_HP->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, m_collisionSizeDefence.y, 0.0f));
        }
    }

    // �e�̈ʒu���X�V
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(m_pos.x, SHADOW_POS_Y, m_pos.z));
    }

    // �A�j���[�V�������g���t���O��true�Ȃ�A�j���[�V����������
    if (m_bUseAnimation)
    {
        if (m_pAnimation)
        {
            m_pAnimation->Update();
        }
    }
}

//=============================================================================
// �`�揈��
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::Draw(void)
{
    // �e
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->CBillboard::Draw();
    }

    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        if (nCount == 0)
        {
            // �S�Ă̐e�́A�L�����N�^�[�̈ʒu���̂��̂�n��
            m_apModel[nCount]->Draw(m_pos, m_rot, m_bUseWhiteDraw);
        }
        else
        {
            m_apModel[nCount]->Draw(m_apModel[m_anIndexParent[nCount]], m_bUseWhiteDraw);
        }
    }
}

//=============================================================================
// ���ꂽ���̕`��
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::DeathDraw(void)
{
    // �����̈ꌂ���ȊO�Ȃ�
    if (CManager::GetCamera()->CCamera::GetState() != CCamera::STATE_FINISH_EACH)
    {
        // Z�o�b�t�@�𖳌���
        LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
        pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    }

    // �e�p�[�c���A�������邽�߂�true
    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        if (nCount == 0)
        {
            m_apModel[nCount]->Draw(m_pos, m_rot, true);
        }
        else
        {
            m_apModel[nCount]->Draw(m_apModel[m_anIndexParent[nCount]], true);
        }
    }

    // �����̈ꌂ���ȊO�Ȃ�
    if (CManager::GetCamera()->CCamera::GetState() != CCamera::STATE_FINISH_EACH)
    {
        // Z�o�b�t�@��L����
        LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
        pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    }
}

//=============================================================================
// ���f���f�[�^�i���W,�e�q�֌W�j�ǂݍ��ݏ����i�e�L�X�g�t�@�C�����璼�ړǂݍ��ގ��Ɏg���֐��j
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::LoadModelData(char* cFilePass)
{
    // ���O���L��
    m_cAnimFilePass = cFilePass;

    // �t�@�C���|�C���g
    FILE *pFile = NULL;

    // �ϐ��錾
    int  nCntLoad = 0;
    char cReedText[2048];	// �����Ƃ��ēǂݎ��p
    char cHeadText[2048];	//
    char cDie[2048];
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 rot = DEFAULT_VECTOR;

    // �t�@�C���J
    pFile = fopen(cFilePass, "r");

    // �J����
    if (pFile != NULL)
    {
        while (strcmp(cHeadText, "CHARACTERSET") != 0)
        {
            fgets(cReedText, sizeof(cReedText), pFile);
            sscanf(cReedText, "%s", &cHeadText);
        }

        if (strcmp(cHeadText, "CHARACTERSET") == 0)
        {
            while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
            {

                fgets(cReedText, sizeof(cReedText), pFile);
                sscanf(cReedText, "%s", &cHeadText);

                if (strcmp(cHeadText, "\n") == 0)
                {
                }
                else if (strcmp(cHeadText, "PARTSSET") == 0)
                {
                    while (strcmp(cHeadText, "END_PARTSSET") != 0)
                    {

                        fgets(cReedText, sizeof(cReedText), pFile);
                        sscanf(cReedText, "%s", &cHeadText);

                        if (strcmp(cHeadText, "INDEX") == 0)
                        {
                            int nNum;
                            sscanf(cReedText, "%s %s %d", &cDie, &cDie, &nNum);
                        }

                        if (strcmp(cHeadText, "PARENT") == 0)
                        {
                            sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_anIndexParent[nCntLoad]);
                        }

                        if (strcmp(cHeadText, "POS") == 0)
                        {
                            sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);

                            m_aPosDefault[nCntLoad] = pos;
                        }

                        if (strcmp(cHeadText, "ROT") == 0)
                        {
                            sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &rot.x, &rot.y, &rot.z);
                        }
                    }
                    nCntLoad++;
                }
            }
        }
        // �t�@�C����
        fclose(pFile);
    }
    else
    {
        printf("�J����܂���ł���\n");
    }
}

//=============================================================================
// ���f���f�[�^�i���W,�e�q�֌W�j�ǂݍ��ݏ����i���f���̏����ʒu�f�[�^����ǂݍ��ނƂ��Ɏg���֐��j
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::LoadModelData(int nModelPosDefUp, int nModelPosDefDown)
{
    // ���f���̏����ʒu�f�[�^���󂯎��
    CModelData *pModelData = CManager::GetModelData();

    // �㔼�g�Ɖ����g�𕪂���
    CModelData::ModelPosDef *pModelPosDefUp = pModelData->GetPosDef(nModelPosDefUp);
    CModelData::ModelPosDef *pModelPosDefDown = pModelData->GetPosDef(nModelPosDefDown);

    // �㔼�g
    for (int nCnt = 0; nCnt < MAX_MODEL_PARTS_SET; nCnt++)
    {
        m_anIndexParent[pModelPosDefUp->nIndex[nCnt]] = pModelPosDefUp->nParent[nCnt];
        m_aPosDefault[pModelPosDefUp->nIndex[nCnt]] = pModelPosDefUp->pos[nCnt];
    }

    // �����g
    for (int nCnt = 0; nCnt < MAX_MODEL_PARTS_SET; nCnt++)
    {
        m_anIndexParent[pModelPosDefDown->nIndex[nCnt]] = pModelPosDefDown->nParent[nCnt];
        m_aPosDefault[pModelPosDefDown->nIndex[nCnt]] = pModelPosDefDown->pos[nCnt];
    }
}

//=============================================================================
// ������������
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::RotControl(void)
{
    // ��]�̐���
    if (m_rot.y > D3DX_PI)
    {
        m_rot.y -= D3DX_PI * 2.0f;
    }
    else if (m_rot.y < -D3DX_PI)
    {
        m_rot.y += D3DX_PI * 2.0f;
    }

    // �ړI�̊p�x�̉�]�𐧌�
    float fRotMin = m_rotDest.y - m_rot.y;
    if (fRotMin > D3DX_PI)
    {
        m_rotDest.y -= D3DX_PI * 2.0f;
    }
    else if (fRotMin < -D3DX_PI)
    {
        m_rotDest.y += D3DX_PI * 2.0f;
    }

    // �ړI�̒l�ɋ߂Â���
    if (fabsf(fRotMin) >= 0.0f)
    {
        m_rot.y += (m_rotDest.y - m_rot.y) * m_fTurnSpeed;
    }
}

//=============================================================================
// �_���[�W���󂯂鏈��
// Author : �㓡�T�V��
//=============================================================================
bool CCharacter::TakeDamage(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, OBJTYPE lastHit, bool bUseKnockBack, int effectType)
{
    // ���G�łȂ��Ȃ�
    if (!m_bIsInvincible)
    {
        // �̗͂��c���Ă���Ȃ�A�Ō�ɍU�����Ă����l���X�V
        if (m_fLife > 0.0f)
        {
            m_lastHit = lastHit;
        }

        // HP��\��
        SetUIHPDisp(true);

        // �ԃQ�[�W�d�����Ԃ�ݒ�
        if (m_nCntStopRedLifeTime <= 0)
        {
            const int STOP_RED_TIME = 60;
            m_nCntStopRedLifeTime = STOP_RED_TIME;
        }

        // ���`�掞�Ԃ�ݒ�
        const int WHITE_DRAW_TIME = 8;
        m_nCntWhiteDrawTime = WHITE_DRAW_TIME;

        // �ϐ��錾
        D3DXVECTOR3 myPos = GetPos();                   // �ʒu���擾
        float fKnockbackValue = 0.0f;                   // �m�b�N�o�b�N��
        DAMAGE_STATE damageState = DAMAGE_STATE_NONE;   // �_���[�W���
        int nCntTakeDamageTime = 0;                     // �_���[�W���󂯂����̃J�E���^

        // ������Ԃ��A�󂯂�_���[�W���画��
        int nEffectFrame = PLAYER_TAKE_DAMAGE_SMALL_EFFECT_FRAME;   // �U���t���[��
        if (fDamage < TAKE_DAMAGE_BORDER_DAMAGE)
        {
            // ������
            damageState = DAMAGE_STATE_SMALL;
            fKnockbackValue = KNOCK_BACK_SMALL;
            nCntTakeDamageTime = TAKE_DAMAGE_SMALL_FRAME;
        }
        else
        {
            // ������΂����Ԃ́A�ړ��ʂ��Ȃ��Ȃ��Ēn�ʂɂ��܂ő���
            damageState = DAMAGE_STATE_BLOWN;
            fKnockbackValue = KNOCK_BACK_BIG;

            // �傫���U��
            nEffectFrame = PLAYER_TAKE_DAMAGE_BIG_EFFECT_FRAME;
        }

        // �_���[�W���󂯂�
        m_fLife -= fDamage;

        // �_���[�W�\�L�ƃG�t�F�N�g��\��
        if (fDamage > 0.0f)
        {
            D3DXVECTOR3 dispDamagePos = ConvertScreenPos(myPos);
            CNumberArray::Create(12, dispDamagePos, NUMBER_SIZE_X_DAMAGE, D3DXCOLOR(0.933f, 0.427f, 0.513f, 1.0f), (int)fDamage, false, true);

            // �����_���[�W�̈ʒu�ƁA1F�O�̃_���[�W�̈ʒu�������Ȃ�A�_���[�W�̈ʒu���L�����N�^�[�̈ʒu�ɂ���
            D3DXVECTOR3 hitEffectPos = damagePos;
            if (damagePos == damageOldPos)
            {
                D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
                hitEffectPos = myPos + D3DXVECTOR3(0.0f, collisionSizeDefence.y * 0.5f, 0.0f);
            }
            CEffect3D::Emit(effectType, hitEffectPos, damageOldPos);
        }

        // �̗͂��Ȃ��Ȃ�����
        if (m_fLife <= 0.0f)
        {
            // ���S���̐U��
            nEffectFrame = PLAYER_TAKE_DAMAGE_DEATH_EFFECT_FRAME;

            // ���S�\����
            m_fLife = 0.0f;

            // ���S�p�m�b�N�o�b�N
            fKnockbackValue = KNOCK_BACK_DEATH;

            // �\����؂�
            m_bDisp = false;
        }
        else
        {
            // �������Ă���Ȃ�A�_���[�W���i�q�b�g�����A�q�b�g�G�t�F�N�g�̂悤�ɕ�����̂�����j
            CManager::SoundPlay(CSound::LABEL_SE_DAMAGE);
        }

        // �m�b�N�o�b�N������U�����A�m�b�N�o�b�N�𗘗p�����ԂȂ�
        if (bUseKnockBack && m_bTakeKnockBack)
        {
            // �_���[�W��Ԃ��X�V
            m_damageState = damageState;
            m_nCntTakeDamageTime = nCntTakeDamageTime;

            // �U����Ԃ����Z�b�g
            m_bResetAttackByDamage = true;

            // �U���̕��������A�m�b�N�o�b�N������
            float fAngleToDamagePos = GetAngleToTargetXZ(damageOldPos, myPos);
            SetRot(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            SetRotDest(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            m_move.x = sinf(fAngleToDamagePos) * fKnockbackValue;
            m_move.z = cosf(fAngleToDamagePos) * fKnockbackValue;
        }

        // �R���g���[���̐U��
        if (m_bUseControllerEffectByTakeDamage)
        {
            CManager::GetInputJoypad()->StartEffect(m_HPDisp, nEffectFrame);
        }
    }

    // �_���[�W�����������ǂ���
    bool bHit = !m_bIsInvincible;
    return bHit;
}

//=============================================================================
// ���S�Ɉ����񂹂鏈��
// Author : �㓡�T�V��
//=============================================================================
bool CCharacter::PullToCenter(D3DXVECTOR3 centerPos)
{
    // ���G�łȂ��Ȃ�
    if (!m_bIsInvincible)
    {
        // �m�b�N�o�b�N�𗘗p�����ԂȂ�
        if (m_bTakeKnockBack)
        {
            // �����󂯂��t���O��true��
            m_bTakeWind = true;

            // �ϐ��錾
            D3DXVECTOR3 myPos = GetPos();           // �ʒu���擾
            float fKnockbackValue = 0.0f;           // �m�b�N�o�b�N��

            // �����ɉ����ăm�b�N�o�b�N�ʂ�ς���
            float fDistance = sqrtf(
                powf((centerPos.x - myPos.x), 2.0f) +
                powf((centerPos.z - myPos.z), 2.0f));
            fKnockbackValue = fDistance * PULL_TO_CENTER_VALUE;

            // �m�b�N�o�b�N�ʐ���
            if (fDistance > PULL_TO_CENTER_VALUE_LIMIT)
            {
                fDistance = PULL_TO_CENTER_VALUE_LIMIT;
            }

            // �U����Ԃ����Z�b�g
            m_bResetAttackByDamage = true;

            // �U���̕��͌������A�m�b�N�o�b�N������
            float fAngleToDamagePos = GetAngleToTargetXZ(myPos, centerPos);
            //SetRot(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            //SetRotDest(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            m_move.x = sinf(fAngleToDamagePos) * fKnockbackValue;
            m_move.z = cosf(fAngleToDamagePos) * fKnockbackValue;
        }
    }

    // �����񂹂�ꂽ���ǂ���
    bool bHit = !m_bIsInvincible;
    return bHit;
}

//=============================================================================
// �񕜏���
// Author : �㓡�T�V��
//=============================================================================
bool CCharacter::Healing(float fHealValue)
{
    // �\������Ă��Ȃ��Ȃ�A�֐��𔲂���
    if (!m_bDisp)
    {
        return false;
    }

    // ���łɍő�l�Ȃ�A�񕜎��s
    if (m_fLife >= m_fMaxLife)
    {
        return false;
    }

    // �ő�l��蒴���Ȃ��悤�ɉ�
    m_fLife += fHealValue;
    if (m_fLife > m_fMaxLife)
    {
        m_fLife = m_fMaxLife;
    }

    // ���g�̈ʒu����񕜃G�t�F�N�g�𔭐�

    // �񕜐���
    return true;
}

//=============================================================================
// �_���[�W���󂯂Ă��鎞�Ԃ𐔂��鏈���i�O��̖��c�Ńv���C���[�ł����g���ĂȂ������L��j
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::CntDownTakeDamageTime(void)
{
    // ������ԊǗ�
    if (m_nCntTakeDamageTime > 0)
    {
        m_nCntTakeDamageTime--;

        // �����I�����ɏ�Ԃ�߂�
        if (m_nCntTakeDamageTime == 0)
        {
            m_bTakeWind = false;

            // �_�E������̋N���オ��ȊO�́A�_���[�W��Ԃ�����
            if (m_damageState != DAMAGE_STATE_BIG)
            {
                m_damageState = DAMAGE_STATE_NONE;
            }
            else
            {
                m_damageState = DAMAGE_STATE_STAND_UP;
                m_nCntTakeDamageTime = PLAYER_TAKE_DAMAGE_STAND_UP_FRAME;
            }
        }
    }

    // ���`�掞�Ԃ̊Ǘ�
    if (m_nCntWhiteDrawTime > 0)
    {
        m_nCntWhiteDrawTime--;
        m_bUseWhiteDraw = true;
    }
    else
    {
        m_bUseWhiteDraw = false;
    }
}

//=============================================================================
// �ړ��ʂ̐��䏈��
// Author : �㓡�T�V��
//=============================================================================
void CCharacter::ControlMove(float& fMove, bool bGround)
{
    if (fMove != 0.0f)
    {
        // ����̊������A�󋵂ɂ���ĕς���
        float fControlMoveRate = PLAYER_CONTROL_MOVE_ON_GROUND;

        // �������Ă��Ȃ��Ȃ�
        if (GetDamageState() == DAMAGE_STATE_NONE)
        {
            // �󒆂Ȃ�
            if (!bGround)
            {
                fControlMoveRate = PLAYER_CONTROL_MOVE_IN_AIR;
            }
        }
        else
        {
            // �����󂯂Ă���Ȃ�A�n��Ɠ���
            if (m_bTakeWind)
            {
                fControlMoveRate = PLAYER_CONTROL_MOVE_ON_GROUND;
            }
            else
            {
                fControlMoveRate = PLAYER_CONTROL_MOVE_TAKE_DAMAGE;
            }
        }

        // �ړ��ʐ���
        fMove *= fControlMoveRate;
    }
}