//=============================================================================
//
// �t�@�C���̏������݃N���X [file_manager.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "file_manager.h"
#include "ui.h"
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OUTPUT_FILE_NAME "data/TXT/test.txt"    // �������ރt�@�C����

//*****************************************************************************
// �ÓI�����o�֐�
//*****************************************************************************
CFile_Manager* CFile_Manager::pInstance = nullptr;

//=============================================================================
// [CFile_Manager] �R���X�g���N�^
//=============================================================================
CFile_Manager::CFile_Manager()
{

}

//=============================================================================
// [~CFile_Manager] �f�X�g���N�^
//=============================================================================
CFile_Manager::~CFile_Manager()
{
    pInstance = nullptr;
}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
 CFile_Manager* CFile_Manager::Create(void)
{
    if (!pInstance)
    {
        pInstance = new CFile_Manager;
        pInstance->writing();
    }
    return pInstance;
}

 //=============================================================================
 // [Read] �t�@�C���̓ǂݍ���
 // ����
 // �ǂݍ��ރt�@�C����
 //=============================================================================
 void CFile_Manager::Read(char* fileName)
 {
     // �t�@�C���|�C���g
     FILE *pFile = NULL;

     // �ϐ��錾
     char cReadText[1024];	// �����Ƃ��ēǂݎ��p
     char cHeadText[1024];	// �����̔��ʗp
     char cDie[1024];		// �g��Ȃ����� 
     int nBool = 0;          // int����bool�ւ̋��n��

         // �t�@�C�����J��
         pFile = fopen(fileName, "r");

     assert(pFile);

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
                 // cHeadText��UISET�̎�
                 if (strcmp(cHeadText, "UISET") == 0)
                 {
                     // �������Ɍ��т������
                     int nTexType = 0;                                   // �摜�ԍ�
                     int nAccessNum = NOT_EXIST;                         // �A�N�Z�X�i���o�[
                     D3DXVECTOR3 pos = DEFAULT_VECTOR;                   // �ʒu
                     D3DXVECTOR3 size = DEFAULT_VECTOR;                  // �傫��
                     D3DXVECTOR3 collisionPos = DEFAULT_VECTOR;          // �����蔻��̈ʒu
                     D3DXVECTOR3 collisionSize = DEFAULT_VECTOR;         // �����蔻��̑傫��
                     int nRot = 0;                                       // �p�x
                     D3DXCOLOR col = DEFAULT_COLOR;                      // �F
                     bool bAddBrend = false;                             // ���Z����
                     bool bUseZBuffer = false;                           // 3D���f���̌��ɏo�����ǂ���
                     bool bFrontText = false;                            // �e�L�X�g������O���ǂ���
                     int nAlphaTestBorder = DEFAULT_ALPHATEST_BORDER_2D; // �A���t�@�e�X�g�̃{�[�_�[
                     bool bShaveTex = false;                             // �[��1�s�N�Z����邩�ǂ���
                     bool bDisp = true;                                  // �\�����邩�ǂ���
                     int nIndexAction = 0;                               // �A�N�V�����̃C���f�b�N�X    
                     CUI::ActionInfo aActionInfo[MAX_ACTION] = {};            // �A�N�V�����̏��
                     memset(aActionInfo, 0, sizeof(aActionInfo));
                     memset(aActionInfo->afParam, 0, sizeof(aActionInfo->afParam));

                     // cHeadText��END_UISET�ɂȂ�܂�
                     while (strcmp(cHeadText, "END_UISET") != 0)
                     {
                         fgets(cReadText, sizeof(cReadText), pFile);
                         sscanf(cReadText, "%s", &cHeadText);

                         if (strcmp(cHeadText, "TYPE") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nTexType);

                             // �s���Ȓl�͑S�ăf�t�H���g���Ăяo��
                             if (nTexType < 0 || nTexType >= MAX_TEXTURE)
                             {
                                 nTexType = 0;
                             }
                         }
                         else if (strcmp(cHeadText, "ACCESS_NUM") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nAccessNum);

                             // �s���Ȓl�͑S�ăf�t�H���g���Ăяo��
                             if (nAccessNum < 0 || nAccessNum >= MAX_ACCESS_NUM)
                             {
                                 nAccessNum = NOT_EXIST;
                             }
                         }
                         else if (strcmp(cHeadText, "NO_DRAW") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 1)
                             {
                                 bDisp = false;
                             }
                         }
                         else if (strcmp(cHeadText, "POS") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &pos.x, &pos.y);
                         }
                         else if (strcmp(cHeadText, "SIZE") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &size.x, &size.y);
                         }
                         else if (strcmp(cHeadText, "COLLISION_POS") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &collisionPos.x, &collisionPos.y);
                         }
                         else if (strcmp(cHeadText, "COLLISION_SIZE") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f", &cDie, &cDie, &collisionSize.x, &collisionSize.y);
                         }
                         else if (strcmp(cHeadText, "ROT") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRot);
                         }
                         else if (strcmp(cHeadText, "COL") == 0)
                         {
                             sscanf(cReadText, "%s %s %f %f %f %f", &cDie, &cDie, &col.r, &col.g, &col.b, &col.a);
                         }
                         else if (strcmp(cHeadText, "ADD_BLEND") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bAddBrend = false;
                             }
                             else
                             {
                                 bAddBrend = true;
                             }
                         }
                         else if (strcmp(cHeadText, "USE_ZBUFFER") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bUseZBuffer = false;
                             }
                             else
                             {
                                 bUseZBuffer = true;
                             }
                         }
                         else if (strcmp(cHeadText, "FRONT_TEXT") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bFrontText = false;
                             }
                             else
                             {
                                 bFrontText = true;
                             }
                         }
                         else if (strcmp(cHeadText, "ALPHA_TEST_BORDER") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nAlphaTestBorder);
                         }
                         else if (strcmp(cHeadText, "SHAVE_TEX") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 bShaveTex = false;
                             }
                             else
                             {
                                 bShaveTex = true;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION0") == 0)
                         {
                             nIndexAction = 0;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // �s���Ȓl�͑S�ăf�t�H���g���Ăяo��
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION1") == 0)
                         {
                             nIndexAction = 1;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // �s���Ȓl�͑S�ăf�t�H���g���Ăяo��
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION2") == 0)
                         {
                             nIndexAction = 2;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // �s���Ȓl�͑S�ăf�t�H���g���Ăяo��
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "ACTION3") == 0)
                         {
                             nIndexAction = 3;
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &aActionInfo[nIndexAction].action);

                             // �s���Ȓl�͑S�ăf�t�H���g���Ăяo��
                             if (aActionInfo[nIndexAction].action < CUI::ACTION_NONE || aActionInfo[nIndexAction].action >= CUI::ACTION_MAX)
                             {
                                 aActionInfo[nIndexAction].action = CUI::ACTION_NONE;
                             }
                         }
                         else if (strcmp(cHeadText, "LOCK") == 0)
                         {
                             sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBool);

                             if (nBool == 0)
                             {
                                 aActionInfo[nIndexAction].bLock = false;
                             }
                             else
                             {
                                 aActionInfo[nIndexAction].bLock = true;
                             }
                         }
                         else if (strcmp(cHeadText, "PARAM0") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[0]);
                         }
                         else if (strcmp(cHeadText, "PARAM1") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[1]);
                         }
                         else if (strcmp(cHeadText, "PARAM2") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[2]);
                         }
                         else if (strcmp(cHeadText, "PARAM3") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[3]);
                         }
                         else if (strcmp(cHeadText, "PARAM4") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[4]);
                         }
                         else if (strcmp(cHeadText, "PARAM5") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[5]);
                         }
                         else if (strcmp(cHeadText, "PARAM6") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[6]);
                         }
                         else if (strcmp(cHeadText, "PARAM7") == 0)
                         {
                             sscanf(cReadText, "%s %s %f", &cDie, &cDie, &aActionInfo[nIndexAction].afParam[7]);
                         }
                     }

                     // �����i�A�N�V�����̏������т���j
                     CUI* pUI = CUI::Create(nTexType, pos, size, nRot, col, bFrontText, bAddBrend, nAlphaTestBorder, bUseZBuffer, collisionPos, collisionSize);
                     for (int nCnt = 0; nCnt < MAX_ACTION; nCnt++)
                     {
                         pUI->SetActionInfo(nCnt, aActionInfo[nCnt].action, aActionInfo[nCnt].bLock,
                             aActionInfo[nCnt].afParam[0], aActionInfo[nCnt].afParam[1], aActionInfo[nCnt].afParam[2], aActionInfo[nCnt].afParam[3],
                             aActionInfo[nCnt].afParam[4], aActionInfo[nCnt].afParam[5], aActionInfo[nCnt].afParam[6], aActionInfo[nCnt].afParam[7]);

                     }

                     // �A�N�Z�X�����擾����
                     if (nAccessNum > NOT_EXIST && nAccessNum < MAX_ACCESS_NUM)
                     {
                         pUI->SetAccessUI(nAccessNum);
                     }

                     // �[��1�s�N�Z������邩�ǂ���
                     if (bShaveTex)
                     {
                         pUI->SetShaveTex();
                     }

                     // �\�����邩�ǂ�����ݒ�
                     pUI->SetDisp(bDisp);

                     // �R���e�i�ɒǉ�
                     CUI::SetUI(pUI);
#ifdef _DEBUG
                     pUI->SetReloadUI();
#endif
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
     }
 }

 //=============================================================================
 // [Read] �t�@�C���̓ǂݍ���
 // ����
 // �ǂݍ��ރt�@�C����
 //=============================================================================
 void CFile_Manager::ReadFile(char * fileName)
 {
     std::ifstream file(fileName);  // �ǂݍ��ރt�@�C��
     std::string line;              // �ۑ��p�ϐ�
     char del = ' ';// ��؂蕶��

     while (std::getline(file, line))// �t�@�C����1�s���ǂݍ���
     {

         int NamePos = line.find("]");// �������T��
         if (NamePos != std::string::npos)// ����������������
         {// ������𕪊����ďo��
             Split(line, del);
         }
     }
 }

 //==============================================================================
 // [split] ������̕���
 // ����
 //      str : ����������������
 //      del : ��؂蕶��(��������ʒu)
 // �Ԃ�l �������ꂽ������̍Ō�
 //==============================================================================
 std::string CFile_Manager::Split(std::string str, char del)
 {
     int first = 0;
     int last = str.find_first_of(del);

     std::vector<std::string> result;

     while (first<str.size())
     {
         std::string subStr(str, first, last - first);
         result.push_back(subStr);

         // �擪�Ƌ�؂蕶���̈ʒu�����炷
         first = last + 1;
         last = str.find_first_of(del, first);

         // ��؂蕶����������Ȃ�������
         if (last == std::string::npos)
         {
             last = str.size();
         }
     }

     return result[result.size() - 1];
 }

 //=============================================================================
 // [ReadUIName] UI���̓ǂݍ���
 //=============================================================================
 void CFile_Manager::ReadUIName(std::ifstream file , std::string label)
 {
     std::string line;

     char del = ' ';// ��؂蕶��

     while (std::getline(file, line))// �t�@�C����1�s���ǂݍ���
     {
         int NamePos = line.find(label);// �������T��
         if (NamePos != std::string::npos)// ����������������
         {// ������𕪊����ďo��

             std::cout << Split(line, del) << std::endl;

         }
     }
 }
 //=============================================================================
 // [ParseFlloat3] �t�@�C���̏�������
 //=============================================================================
 void CFile_Manager::ParseFlloat3(std::string line, char del, float x, float y, float z)
 {
 }

 //=============================================================================
 // [writing] �t�@�C���̏�������
 //=============================================================================
 void CFile_Manager::writing(void)
 {
     std::ofstream pfile(OUTPUT_FILE_NAME);

     pfile << "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n" << std::endl;

     std::string str;
     int i =CUI::GetUINum();
     for (int nCnt = 0; nCnt < CUI::GetUINum(); nCnt++)
     {
         CUI* pUI = CUI::GetUI(nCnt);// UI�̃C���X�^���X�擾

         // UI�̏��𕶎���Ŏ擾
         if (pUI != NULL)
         {
             str = pUI->fileString();
             pfile << "UISET" << std::endl << str  << "END_UISET" << std::endl << std::endl;
         }
     }

     pfile << std::endl << "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI\n" << std::endl;
 }