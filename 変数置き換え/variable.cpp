#define _CRT_SECURE_NO_WARNINGS

//===============================================
//
// �V�[����̃I�u�W�F�N�g���� (variable.cpp)
// Author : �����N�m
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "variable.h"

//========================
//�}�N����`
//========================

//========================================
// �V�[����̃I�u�W�F�N�g�̃f�t�H���g�R���X�g���N�^
//========================================
CVariable::CVariable()
{
	ZeroMemory(&VariableName, sizeof(VariableName));
}

//========================================
// �V�[����̃I�u�W�F�N�g�̃f�X�g���N�^
//========================================
CVariable::~CVariable()
{

}

void CVariable::Uninit(void) {
	VariableName.clear();
}

int CVariable::GetNumber(char* cName) {
	for (int nCount = 0; nCount < VariableName.size(); nCount++) {
		if (VariableName[nCount].cName == cName) {
			return nCount;
		}
	}

	return -1;
}