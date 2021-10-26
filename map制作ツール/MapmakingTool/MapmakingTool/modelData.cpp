//=============================================================================
//
// ���f���f�[�^�̏��� [modelData.cpp]
// Author : �㓡�T�V��
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "modelData.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MODEL_DATA_FILENAME ("data/TXT/modelData.txt")	    // ���f���f�[�^��ǂݍ��ރt�@�C���̖��O

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CModelData::CModelData()
{
	memset(m_aModelData, 0, sizeof(m_aModelData));
	memset(m_aModelData->apTexMat, 0, sizeof(m_aModelData->apTexMat));

	memset(m_aModelPosDef, 0, sizeof(m_aModelPosDef));
	memset(m_aModelPosDef->nIndex, 0, sizeof(m_aModelPosDef->nIndex));
	memset(m_aModelPosDef->nParent, 0, sizeof(m_aModelPosDef->nParent));
	memset(m_aModelPosDef->pos, 0, sizeof(m_aModelPosDef->pos));
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CModelData::~CModelData()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CModelData::Init(void)
{
	// �t�@�C���|�C���g
	FILE *pFile = NULL;

	// �ϐ��錾
	char cReadText[2048];	               // �����Ƃ��ēǂݎ��p
	char cHeadText[2048];	               // �����̔��ʗp
	char cDie[2048];		               // �g��Ȃ�����
	int nNumType = 0;                      // �^�C�v�̃i���o�[
	char cLoadModelName[256];              // �ǂݍ��ݎ��̃��f����

										   // ���f����ǂݍ��ނ��߂̃f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//======================================================================================
	// ���f���f�[�^�t�@�C�����J��
	pFile = fopen(MODEL_DATA_FILENAME, "r");

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

				// cHeadText��MODEL_DATASET�̎�
				if (strcmp(cHeadText, "MODEL_DATASET") == 0)
				{
					// cHeadText��END_MODEL_DATASET�ɂȂ�܂�
					while (strcmp(cHeadText, "END_MODEL_DATASET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nNumType);
						}
						else if (strcmp(cHeadText, "NAME") == 0)
						{
							sscanf(cReadText, "%s %s %s", &cDie, &cDie, &cLoadModelName);

							// ���f���f�[�^�̓ǂݍ���
							D3DXLoadMeshFromX(LPCSTR(cLoadModelName), D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&m_aModelData[nNumType].pBuffMat, NULL, &m_aModelData[nNumType].nNumMat, &m_aModelData[nNumType].pMesh);

							// �}�e���A���̃|�C���^���擾
							D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_aModelData[nNumType].pBuffMat->GetBufferPointer();

							// �}�e���A���̃e�N�X�`�������т���
							for (int nCntMat = 0; nCntMat < (int)m_aModelData[nNumType].nNumMat; nCntMat++)
							{
								D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_aModelData[nNumType].apTexMat[nCntMat]);
							}
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
// Author : �㓡�T�V��
//=============================================================================
void CModelData::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_MODEL_DATA; nCount++)
	{
		// �}�e���A���̃e�N�X�`���̔j��
		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			if (m_aModelData[nCount].apTexMat[nCntMat] != NULL)
			{
				m_aModelData[nCount].apTexMat[nCntMat]->Release();
				m_aModelData[nCount].apTexMat[nCntMat] = NULL;
			}
		}

		// ���b�V���̔j��
		if (m_aModelData[nCount].pMesh != NULL)
		{
			m_aModelData[nCount].pMesh->Release();
			m_aModelData[nCount].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (m_aModelData[nCount].pBuffMat != NULL)
		{
			m_aModelData[nCount].pBuffMat->Release();
			m_aModelData[nCount].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// ���f���f�[�^���̎󂯎��̏���
// Author : �㓡�T�V��
//=============================================================================
CModelData::ModelData* CModelData::GetModelData(const int nNum)
{
	if (nNum < MAX_MODEL_DATA && nNum >= 0)
	{
		if (&m_aModelData[nNum] != NULL)
		{
			return &m_aModelData[nNum];
		}
	}

	return NULL;
}