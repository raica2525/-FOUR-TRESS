//=============================================================================
//
// �t�@�C���}�l�[�W���[�w�b�_ [file_manager.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_
#include <stdio.h>
#include <fstream>


//*****************************************************************************
// �N���X����
//*****************************************************************************
class CFile_Manager
{
    static CFile_Manager* pInstance;// �C���X�^���X�ւ̃|�C���^
    CFile_Manager();

public:
    // �����o�֐�(public)
    ~CFile_Manager();
    static CFile_Manager* Create(void);// �I�u�W�F�N�g�̐���
    
private:
    // �����o�֐�(private)
    void writing(void);// �t�@�C���̏�������

    void OutputUISet(void);

    // �����o�ϐ�(private)
    FILE *m_pFile;// �������ރt�@�C���ւ̃|�C���^
};
#endif // !_FILE_OUTPUT_H_
