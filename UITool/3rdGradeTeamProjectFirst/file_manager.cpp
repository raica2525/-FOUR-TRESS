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
 // [writing] �t�@�C���̏�������
 //=============================================================================
 void CFile_Manager::writing(void)
 {
     std::ofstream pfile(OUTPUT_FILE_NAME);

     pfile << "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n" << std::endl;

     std::string str;
     for (int nCnt = 0; nCnt < MAX_ACCESS_NUM; nCnt++)
     {
         CUI* pUI = CUI::GetAccessUI(nCnt);// UI�̃C���X�^���X�擾

                                           // UI�̏��𕶎���Ŏ擾
         if (pUI != NULL)
         {
             str = pUI->fileString();
             pfile << str << std::endl;
         }
     }

     pfile << "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI\n" << std::endl;

 }
 
 //=============================================================================
 // [ManagerUISet] �t�@�C���̏�������
 //=============================================================================
 void CFile_Manager::OutputUISet(void)
 {
     std::ofstream pfile(OUTPUT_FILE_NAME);
     std::string str;
     for (int nCnt = 0; nCnt < MAX_ACCESS_NUM; nCnt++)
     {
         CUI* pUI = CUI::GetAccessUI(nCnt);// UI�̃C���X�^���X�擾

         // UI�̏��𕶎���Ŏ擾
         if (pUI!=NULL)
             str = pUI->fileString();
             pfile << str << std::endl;
     }
 }
