//===============================================
//
// �G�t�F�N�g�f�[�^�Ǘ� (effectData.cpp)
// Author : �ɓ��z��
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// �C���N���[�h�t�@�C��
//========================
#include "effectData.h"
#include "effecttool.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_DATA_FILENAME ("data/TXT/effect.txt")
#define EFFECT_DATA_OUTPUT_FILENAME ("data/TXT/effectinfo.txt")

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffectData::CEffectData()
{
    memset(m_aCreateInfo, 0, sizeof(m_aCreateInfo));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffectData::~CEffectData()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffectData::Init(void)
{
    // �t�@�C���|�C���g
    FILE *pFile = NULL;

    // �ϐ��錾
    char cReadText[256];	               // �����Ƃ��ēǂݎ��p
    char cHeadText[256];	               // �����̔��ʗp
    char cDie[256];		                   // �g��Ȃ�����
    int nNumType = 0;                      // �^�C�v�̃i���o�[
    int nBool = 0;                         // int����bool�ւ̋��n��

    //======================================================================================
    // ���f���f�[�^�t�@�C�����J��
    pFile = fopen(EFFECT_DATA_FILENAME, "r");

    // �J������
    if (pFile != NULL)
    {
        // SCRIPT�̕�����������܂�
        while (strcmp(cHeadText, "SCRIPT") != 0)
        {
            // �e�L�X�g����cReadText���������󂯎��
            fgets(cReadText, sizeof(cReadText), pFile);

            // cReedText��cHeadText�Ɋi�[
            sscanf(cReadText, "%s", &cHeadText);
        }

        // cHeadText��SCRIPT�̎�
        if (strcmp(cHeadText, "SCRIPT") == 0)
        {
            // cHeadText��END_SCRIPT�ɂȂ�܂�
            while (strcmp(cHeadText, "END_SCRIPT") != 0)
            {
                fgets(cReadText, sizeof(cReadText), pFile);
                sscanf(cReadText, "%s", &cHeadText);

                // cHeadText��EFFECT_DATASET�̎�
                if (strcmp(cHeadText, "EFFECT_DATASET") == 0)
                {
                    // cHeadText��END_EFFECT_DATASET�ɂȂ�܂�
                    while (strcmp(cHeadText, "END_EFFECT_DATASET") != 0)
                    {
                        fgets(cReadText, sizeof(cReadText), pFile);
                        sscanf(cReadText, "%s", &cHeadText);

                        if (strcmp(cHeadText, "TYPE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nNumType);
                        }
                        else if (strcmp(cHeadText, "TEX_TYPE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nTexType);
                        }
                        else if (strcmp(cHeadText, "ONCE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nNumOnce);
                        }
                        else if (strcmp(cHeadText, "PLANE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].plane);
                        }
                        else if (strcmp(cHeadText, "ON_CIRCLE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                            if (nBool == 0)
                            {
                                m_aCreateInfo[nNumType].bOnCircleEdge = false;
                            }
                            else
                            {
                                m_aCreateInfo[nNumType].bOnCircleEdge = true;
                            }
                        }
                        else if (strcmp(cHeadText, "EMIT_INSIDE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                            if (nBool == 0)
                            {
                                m_aCreateInfo[nNumType].bEmitVectorInside = false;
                            }
                            else
                            {
                                m_aCreateInfo[nNumType].bEmitVectorInside = true;
                            }
                        }
						else if (strcmp(cHeadText, "SCATTER_ANGLE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nScatterAngle);
						}
                        else if (strcmp(cHeadText, "SCATTER_WIDTH") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nScatterWidth);
                        }
                        else if (strcmp(cHeadText, "SPEED_MAX") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nSpeedMax);
                        }
                        else if (strcmp(cHeadText, "SPEED_MIN") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nSpeedMin);
                        }
                        else if (strcmp(cHeadText, "SPEED_AA_MAX") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nAuxiliaryAxisSpeedMax);
                        }
                        else if (strcmp(cHeadText, "SPEED_AA_MIN") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nAuxiliaryAxisSpeedMin);
                        }
                        else if (strcmp(cHeadText, "ACCEL") == 0)
                        {
                            sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nNumType].fAcceleration);
                        }
                        else if (strcmp(cHeadText, "GRAVITY") == 0)
                        {
                            sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nNumType].fGravity);
                        }
						else if (strcmp(cHeadText, "GRAVITY_LIMIT") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nNumType].fGravityLimit);
						}
                        else if (strcmp(cHeadText, "ROT_LAY") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nLayRot);
                        }
                        else if (strcmp(cHeadText, "ROT_EQUAL_MOVE") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                            if (nBool == 0)
                            {
                                m_aCreateInfo[nNumType].bRotEqualMoveAngle = false;
                            }
                            else
                            {
                                m_aCreateInfo[nNumType].bRotEqualMoveAngle = true;
                            }
                        }
                        else if (strcmp(cHeadText, "ROT_SPEED_MAX") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nRotSpeedMax);
                        }
                        else if (strcmp(cHeadText, "ROT_SPEED_MIN") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nRotSpeedMin);
                        }
                        else if (strcmp(cHeadText, "COL") == 0)
                        {
                            sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie, 
                                &m_aCreateInfo[nNumType].col.r,
                                &m_aCreateInfo[nNumType].col.g,
                                &m_aCreateInfo[nNumType].col.b,
                                &m_aCreateInfo[nNumType].col.a);
                        }
                        else if (strcmp(cHeadText, "COL_CHANGE") == 0)
                        {
                            sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie,
                                &m_aCreateInfo[nNumType].colChangeRate.r,
                                &m_aCreateInfo[nNumType].colChangeRate.g,
                                &m_aCreateInfo[nNumType].colChangeRate.b,
                                &m_aCreateInfo[nNumType].colChangeRate.a);
                        }
                        else if (strcmp(cHeadText, "FADE_OUT_RATE") == 0)
                        {
                            sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nNumType].fFadeOutRate);
                        }
						else if (strcmp(cHeadText, "FADE_OUT_LOCK_TIME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nCntFadeOutLock);
						}
                        else if (strcmp(cHeadText, "SIZE_MAX") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nSizeMax);
                        }
                        else if (strcmp(cHeadText, "SIZE_MIN") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nSizeMin);
                        }
                        else if (strcmp(cHeadText, "SIZE_CHANGE") == 0)
                        {
                            sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
                                &m_aCreateInfo[nNumType].sizeChangeRate.x,
                                &m_aCreateInfo[nNumType].sizeChangeRate.y,
                                &m_aCreateInfo[nNumType].sizeChangeRate.z);
                        }
						else if (strcmp(cHeadText, "SIZE_CHANGE_START_OR_FINISH") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

							if (nBool == 0)
							{
								m_aCreateInfo[nNumType].bSizeChangeStartOrFinish = false;
							}
							else
							{
								m_aCreateInfo[nNumType].bSizeChangeStartOrFinish = true;
							}
						}
						else if (strcmp(cHeadText, "EMITRADIUS") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nNumType].fEmitRadius);
						}
						else if (strcmp(cHeadText, "EMITRADIUS") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aCreateInfo[nNumType].fEmitRadius);
						}
                        else if (strcmp(cHeadText, "ADD_BLEND") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                            if (nBool == 0)
                            {
                                m_aCreateInfo[nNumType].bUseAdditiveSynthesis = false;
                            }
                            else
                            {
                                m_aCreateInfo[nNumType].bUseAdditiveSynthesis = true;
                            }
                        }
                        else if (strcmp(cHeadText, "USE_ZBUFFER") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                            if (nBool == 0)
                            {
                                m_aCreateInfo[nNumType].bUseZBuffer = false;
                            }
                            else
                            {
                                m_aCreateInfo[nNumType].bUseZBuffer = true;
                            }
                        }
                        else if (strcmp(cHeadText, "ALPHA_TEST_BORDER") == 0)
                        {
                            sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aCreateInfo[nNumType].nAlphaTestBorder);
                        }
                    }
                }
            }
        }
        // �t�@�C�������
        fclose(pFile);
    }
    // �J���Ȃ�������
    else
    {
        printf("�J����܂���ł���\n");

        return E_FAIL;
    }
    //======================================================================================

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffectData::Uninit(void)
{

}

//=============================================================================
// �G�t�F�N�g�̏��o�͏���
// nNum : �o�͂���G�t�F�N�g�̔ԍ�
//=============================================================================
HRESULT CEffectData::UploadEffectInfo(const bool *bUpload)
{
	// �t�@�C���|�C���g
	FILE *pFile = NULL;

	// �ϐ��錾
	int nNumType = 0;                      // �^�C�v�̃i���o�[
	int nBool = 0;                         // int����bool�ւ̋��n��

	// �t�@�C�����J��
	pFile = fopen(EFFECT_DATA_OUTPUT_FILENAME, "w");

	// �J������
	if (pFile != NULL)
	{
		for (int nEffectCount = 0; nEffectCount < TYPE_MAX; nEffectCount++)
		{
			if (bUpload[nEffectCount] == true)
			{
				fprintf(pFile, "SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI\n");
				fprintf(pFile, "\n");
				fprintf(pFile, "#------------------------------------------------------------------------------\n");
				fprintf(pFile, "# �G�t�F�N�g�̏��iF4�Ń����[�h�\�j\n");
				fprintf(pFile, "#------------------------------------------------------------------------------\n");
				fprintf(pFile, "\n");

				fprintf(pFile, "#-------------------------------------------------------------\n");
				fprintf(pFile, "# [%d] �i�G�t�F�N�g���j\n", nEffectCount);
				fprintf(pFile, "#-------------------------------------------------------------\n");

				fprintf(pFile, "EFFECT_DATASET\n");

				fprintf(pFile, "	TYPE = %d\n", nEffectCount);
				fprintf(pFile, "	TEX_TYPE = %d\n", m_aCreateInfo[nEffectCount].nTexType);
				fprintf(pFile, "	ONCE = %d\n", m_aCreateInfo[nEffectCount].nNumOnce);
				fprintf(pFile, "	PLANE = %d\n", m_aCreateInfo[nEffectCount].plane);
				fprintf(pFile, "	ON_CIRCLE = %d\n", m_aCreateInfo[nEffectCount].bOnCircleEdge);
				fprintf(pFile, "	EMIT_INSIDE = %d\n", m_aCreateInfo[nEffectCount].bEmitVectorInside);
				fprintf(pFile, "	SCATTER_ANGLE = %d\n", m_aCreateInfo[nEffectCount].nScatterAngle);
				fprintf(pFile, "	SCATTER_WIDTH = %d\n", m_aCreateInfo[nEffectCount].nScatterWidth);

				fprintf(pFile, "	SPEED_MAX = %d\n", m_aCreateInfo[nEffectCount].nSpeedMax);
				fprintf(pFile, "	SPEED_MIN = %d\n", m_aCreateInfo[nEffectCount].nSpeedMin);
				fprintf(pFile, "	SPEED_AA_MAX = %d\n", m_aCreateInfo[nEffectCount].nAuxiliaryAxisSpeedMax);
				fprintf(pFile, "	SPEED_AA_MIN = %d\n", m_aCreateInfo[nEffectCount].nAuxiliaryAxisSpeedMin);
				fprintf(pFile, "	ACCEL = %.3f\n", m_aCreateInfo[nEffectCount].fAcceleration);
				fprintf(pFile, "	GRAVITY = %.3f\n", m_aCreateInfo[nEffectCount].fGravity);
				fprintf(pFile, "	GRAVITYLIMIT = %.3f\n", m_aCreateInfo[nEffectCount].fGravityLimit);


				fprintf(pFile, "	ROT_LAY = %d\n", m_aCreateInfo[nEffectCount].nLayRot);
				fprintf(pFile, "	ROT_EQUAL_MOVE = %d	\n", m_aCreateInfo[nEffectCount].bRotEqualMoveAngle);
				fprintf(pFile, "	ROT_SPEED_MAX = %d\n", m_aCreateInfo[nEffectCount].nRotSpeedMax);
				fprintf(pFile, "	ROT_SPEED_MIN = %d\n", m_aCreateInfo[nEffectCount].nRotSpeedMin);
				fprintf(pFile, "	COL = %.3f %.3f %.3f %.3f\n", m_aCreateInfo[nEffectCount].col.r,
					m_aCreateInfo[nEffectCount].col.g,
					m_aCreateInfo[nEffectCount].col.b,
					m_aCreateInfo[nEffectCount].col.a);
				fprintf(pFile, "	COL_CHANGE = %.3f %.3f %.3f %.3f\n", m_aCreateInfo[nEffectCount].colChangeRate.r,
					m_aCreateInfo[nEffectCount].colChangeRate.g,
					m_aCreateInfo[nEffectCount].colChangeRate.b,
					m_aCreateInfo[nEffectCount].colChangeRate.a);
				fprintf(pFile, "	FADE_OUT_RATE = %.3f\n", m_aCreateInfo[nEffectCount].fFadeOutRate);
				fprintf(pFile, "	FADE_OUT_LOCK_COUNT = %d\n", m_aCreateInfo[nEffectCount].nCntFadeOutLock);

				fprintf(pFile, "	SIZE_MAX = %d\n", m_aCreateInfo[nEffectCount].nSizeMax);
				fprintf(pFile, "	SIZE_MIN = %d\n", m_aCreateInfo[nEffectCount].nSizeMin);
				fprintf(pFile, "	SIZE_CHANGE = %.1f %.1f %.1f\n", m_aCreateInfo[nEffectCount].sizeChangeRate.x,
					m_aCreateInfo[nEffectCount].sizeChangeRate.y,
					m_aCreateInfo[nEffectCount].sizeChangeRate.z);
				fprintf(pFile, "	EMITRADIUS = %.0f\n", m_aCreateInfo[nEffectCount].fEmitRadius);

				fprintf(pFile, "	ADD_BLEND = %d\n", m_aCreateInfo[nEffectCount].bUseAdditiveSynthesis);
				fprintf(pFile, "	USE_ZBUFFER = %d\n", m_aCreateInfo[nEffectCount].bUseZBuffer);
				fprintf(pFile, "	ALPHA_TEST_BORDER = %d\n", m_aCreateInfo[nEffectCount].nAlphaTestBorder);

				fprintf(pFile, "END_EFFECT_DATASET\n");

				fprintf(pFile, "\n\n\n");
				fprintf(pFile, "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI\n");
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	// �J���Ȃ�������
	else
	{
		printf("�J����܂���ł���\n");

		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�������擾����
//=============================================================================
CEffectData::CreateInfo * CEffectData::GetCreateInfo(const int nNum)
{
    if (nNum < TYPE_MAX && nNum >= 0)
    {
        if (&m_aCreateInfo[nNum] != NULL)
        {
            return &m_aCreateInfo[nNum];
        }
    }

    return NULL;
}

//=============================================================================
// �G�t�F�N�g�������Z�b�g
//=============================================================================
void CEffectData::SetCreateInfo(const int nNum)
{
	CEffectTool *pEffectTool = CManager::GetEffectTool();
	CEffectTool::EffectInfo *pEffectInfo = pEffectTool->GetEffectInfo(nNum);

	m_aCreateInfo[nNum].nTexType = pEffectInfo->nTexType;								// �g���e�N�X�`���̎��
	m_aCreateInfo[nNum].nNumOnce = pEffectInfo->nNumOnce;								// ����������
	m_aCreateInfo[nNum].plane = pEffectInfo->nPlane;									// ����

	m_aCreateInfo[nNum].bOnCircleEdge = pEffectInfo->bOnCircleEdge;						// �~�̉�������o���邩�ǂ���
	m_aCreateInfo[nNum].bEmitVectorInside = pEffectInfo->bEmitVectorInside;				// ���o����������ɂ��邩�ǂ���
	m_aCreateInfo[nNum].nScatterAngle = pEffectInfo->nScatterAngle;						// ��U�p�x�i0�`314�j
	m_aCreateInfo[nNum].nScatterWidth = pEffectInfo->nScatterWidth;						// ��U���i0�`314�j
	m_aCreateInfo[nNum].fEmitRadius = pEffectInfo->fEmitRadius;							// ���a�̑傫��

	m_aCreateInfo[nNum].nSpeedMax = pEffectInfo->nSpeedMax;								// �ő呬�x
	m_aCreateInfo[nNum].nSpeedMin = pEffectInfo->nSpeedMin;								// �ŏ����x
	m_aCreateInfo[nNum].nAuxiliaryAxisSpeedMax = pEffectInfo->nAuxiliaryAxisSpeedMax;	// �⏕���̍ő呬�x�i2D��3D�ŁA���̊����o�����߂̂��́j
	m_aCreateInfo[nNum].nAuxiliaryAxisSpeedMin = pEffectInfo->nAuxiliaryAxisSpeedMin;	// �⏕���̍ŏ����x�i2D��3D�ŁA���̊����o�����߂̂��́j

	m_aCreateInfo[nNum].fAcceleration = pEffectInfo->fAcceleration;						// �����x�i1.0��j
	m_aCreateInfo[nNum].fGravity = pEffectInfo->fGravity;								// �d��
	m_aCreateInfo[nNum].fGravityLimit = pEffectInfo->fGravityLimit;						// �d�͐���

	m_aCreateInfo[nNum].nLayRot = pEffectInfo->nLayRot;									// �|���S�����̂��̂����ɂ��邩�ǂ����itrue�Ȃ�r���{�[�h�����j
	m_aCreateInfo[nNum].bRotEqualMoveAngle = pEffectInfo->bRotEqualMoveAngle;			// ��]���ړ��̌����ɍ��킹�邩
	m_aCreateInfo[nNum].nRotSpeedMax = pEffectInfo->nRotSpeedMax;						// �ő��]���x
	m_aCreateInfo[nNum].nRotSpeedMin = pEffectInfo->nRotSpeedMin;						// �ŏ���]���x

	m_aCreateInfo[nNum].col = pEffectInfo->col;											// �F
	m_aCreateInfo[nNum].colChangeRate = pEffectInfo->colChangeRate;						// �F�ω�����										
	m_aCreateInfo[nNum].fFadeOutRate = pEffectInfo->fFadeOutRate;						// ���l�������Ă��������i�F�ω������ł��\�����A�����I�ɗp�ӂ����j
	m_aCreateInfo[nNum].nCntFadeOutLock = pEffectInfo->nCntFadeOutLock;					// ���l�̕ω������b�N����J�E���^

	m_aCreateInfo[nNum].nSizeMax = pEffectInfo->nSizeMax;									// �ő�傫��
	m_aCreateInfo[nNum].nSizeMin = pEffectInfo->nSizeMin;									// �ŏ��傫��
	m_aCreateInfo[nNum].sizeChangeRate = pEffectInfo->fSizeChangeRate;						// �g��/�k������										
	m_aCreateInfo[nNum].nCntSizeChangeLock = pEffectInfo->nCntSizeChangeLock;				// �傫�������b�N����J�E���^
	m_aCreateInfo[nNum].bSizeChangeStartOrFinish = pEffectInfo->bSizeChangeStartOrFinish;	// �傫����ς���̂��n�܂邩�A�I���̂�

	m_aCreateInfo[nNum].bUseAdditiveSynthesis = pEffectInfo->bUseAdditiveSynthesis;		// ���Z�����ɂ��邩�ǂ���
	m_aCreateInfo[nNum].bUseZBuffer = pEffectInfo->bUseZBuffer;							// Z�o�b�t�@���������ǂ���
	m_aCreateInfo[nNum].nAlphaTestBorder = pEffectInfo->nAlphaTestBorder;				// ���e�X�g�̃{�[�_�[
}																																												