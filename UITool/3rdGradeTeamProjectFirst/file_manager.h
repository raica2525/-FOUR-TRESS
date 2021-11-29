//=============================================================================
//
// �t�@�C���}�l�[�W���[�w�b�_ [file_manager.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_
#include "main.h"
#include <stdio.h>
#include <fstream>
#include <string>

//*****************************************************************************
// �N���X����
//*****************************************************************************
class CFile_Manager
{
    static CFile_Manager* pInstance;// �C���X�^���X�ւ̃|�C���^
    CFile_Manager();

public:

    // �Z�b�g
    typedef enum
    {
        SET_NONE = 0,
        SET_TITLE,
        SET_MANUAL,
        SET_CUSTOM,
        SET_GAME,
        SET_RESULT,
        SET_MENU,
        SET_MAX
    }SET;

    // �����o�֐�(public)
    ~CFile_Manager();
    static CFile_Manager* Create(void);// �I�u�W�F�N�g�̐���
    
    void Read(char* fileName = "data/TXT/test.txt");

    void ReadFile(char* fileName = "data/TXT/test.txt");
    std::string Split(std::string str, char del);// ������̕���
    void ReadUIName(std::ifstream file, std::string label);
    void ParseFlloat3(std::string line,char del,float x,float y,float z);

    // Get�֐�
    static CFile_Manager* GetInstance(void) { return pInstance; }

private:
    // �����o�֐�(private)
    void writing(void);// �t�@�C���̏�������

    // �����o�ϐ�(private)
    FILE *m_pFile;// �������ރt�@�C���ւ̃|�C���^
};
#endif // !_FILE_OUTPUT_H_
