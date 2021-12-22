//=============================================================================
//
// �e�N�X�`���̃f�[�^�̏��� [texture.cpp]
// Author : �㓡�T�V��
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "json.h"
#include "fileio.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_FILENAME ("data/TXT/texture.txt")	// �e�N�X�`����ǂݍ��ރt�@�C���̖��O
#define MAP_TEXTURE_FILENAME ("data/TXT/textures.json")	// �}�b�v�Ŏg���e�N�X�`����ǂݍ��ރt�@�C���̖��O

//=============================================================================
// �R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CTexture::CTexture()
{
    // �O���t�@�C�����Ŗ��ݒ�̂��̂��������߁A�����I�ɏ�����
    for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
    {
        m_aInfo[nCount].pTexture = NULL;
        m_aInfo[nCount].nParagraph = 1; // 1�i����
        m_aInfo[nCount].nPattern = 0;
        m_aInfo[nCount].nSpeed = 0;
        m_aInfo[nCount].bRepeat = false;
    }

    m_nCntLoadTextureByTxt = 0;
}

//=============================================================================
// �f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// ����������
// Author : �㓡�T�V�� �r�c�I��
//=============================================================================
HRESULT CTexture::Init(void)
{
	LoadTextureFromTxt(TEXTURE_FILENAME);
	LoadTextureFromJson(MAP_TEXTURE_FILENAME);
	return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CTexture::Uninit(void)
{
    for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
    {
        if (m_aInfo[nCount].pTexture != NULL)
        {
            m_aInfo[nCount].pTexture->Release();
            m_aInfo[nCount].pTexture = NULL;
        }
    }
}

//=============================================================================
// �e�N�X�`�����̎󂯎��̏���
// Author : �㓡�T�V��
//=============================================================================
CTexture::Info* CTexture::GetInfo(const int nNum)
{
    if (nNum < MAX_TEXTURE && nNum >= 0)
    {
        if (&m_aInfo[nNum] != NULL)
        {
            return &m_aInfo[nNum];
        }
    }

    return NULL;
}

//=============================================================================
// �e�L�X�g�t�@�C������e�N�X�`������ǂݍ���
// Author : �㓡�T�V���@�r�c�I��
//=============================================================================
HRESULT CTexture::LoadTextureFromTxt(std::string path)
{
	FILE *pFile = NULL;

	// �ϐ��錾
	char cReadText[2048];	// �����Ƃ��ēǂݎ��p
	char cHeadText[2048];	// �����̔��ʗp
	char cDie[2048];		// �g��Ȃ�����
	int nNumType = 0;       // �^�C�v�̃i���o�[
	char cLoadName[256];    // �ǂݍ��ݎ��̖��O
	int nBool = 0;          // int����bool�ւ̋��n��

							// �t�@�C�����J��
	pFile = fopen(TEXTURE_FILENAME, "r");

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

				// cHeadText��TEXTURESET�̎�
				if (strcmp(cHeadText, "TEXTURESET") == 0)
				{
					// cHeadText��END_TEXTURESET�ɂȂ�܂�
					while (strcmp(cHeadText, "END_TEXTURESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nNumType);
							if (nNumType > m_nCntLoadTextureByTxt)
							{
								m_nCntLoadTextureByTxt = nNumType;    // �ǂݍ��񂾒��ň�ԑ傫��Type���擾����
							}
						}
						else if (strcmp(cHeadText, "NAME") == 0)
						{
							sscanf(cReadText, "%s %s %s", &cDie, &cDie, &cLoadName);

							//�e�N�X�`���̓ǂݍ���
							LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
							D3DXCreateTextureFromFile(pDevice, cLoadName, &m_aInfo[nNumType].pTexture);
						}
						else if (strcmp(cHeadText, "PARAGRAPH") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aInfo[nNumType].nParagraph);
						}
						else if (strcmp(cHeadText, "PATTERN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aInfo[nNumType].nPattern);
						}
						else if (strcmp(cHeadText, "SPEED") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aInfo[nNumType].nSpeed);
						}
						else if (strcmp(cHeadText, "REPEAT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

							if (nBool == 0)
							{
								m_aInfo[nNumType].bRepeat = false;
							}
							else
							{
								m_aInfo[nNumType].bRepeat = true;
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

	return S_OK;
}

//=============================================================================
// JSON�t�@�C������e�N�X�`������ǂݍ���
// Author : �r�c�I��
//=============================================================================
HRESULT CTexture::LoadTextureFromJson(std::string path)
{
	std::string str;
	// �t�@�C����ǂݍ���
	CFileIO::Load(&str, path);
	// �t�@�C������ǂݍ��񂾕������json�I�u�W�F�N�g�ɕϊ�
	picojson::object picoobj = CJson::FromJson(str);
	//�t�@�C���`���̊m�F
	if (picoobj["textures"].is<picojson::null>())
	{
		return E_FAIL;
	}

	int nIndex = GetCntLoadTextureByTxt() + 1;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	picojson::array arr = picoobj["textures"].get<picojson::array>();

	//���ׂẴI�u�W�F�N�g���Q�[���I�u�W�F�N�g�ɕϊ�
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++, nIndex++)
	{
		std::string fileName = it->get<std::string>();
		D3DXCreateTextureFromFile(pDevice, fileName.c_str(), &m_aInfo[nIndex].pTexture);

		//�p�X���疼�O���擾
		char cstr[MAX_PATH];
		sprintf(cstr, fileName.c_str());
		char* cp;
		char* cpBuff;
		cp = strtok(cstr, "\\");
		while (1)
		{
			cpBuff = cp;
			cp = strtok(NULL, "\\");
			if (cp == NULL)
			{
				break;
			}
		}

		// ���O�Ɣԍ������т���
		m_nameIndexMap.insert(std::make_pair(cpBuff, nIndex));
	}
	return S_OK;
}