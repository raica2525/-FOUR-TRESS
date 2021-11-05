#define _CRT_SECURE_NO_WARNINGS

//===============================================
//
// シーン上のオブジェクト処理 (variable.cpp)
// Author : 東村哲士
//
//===============================================

//========================
// インクルードファイル
//========================
#include "variable.h"

//========================
//マクロ定義
//========================

//========================================
// シーン上のオブジェクトのデフォルトコンストラクタ
//========================================
CVariable::CVariable()
{
	ZeroMemory(&VariableName, sizeof(VariableName));
}

//========================================
// シーン上のオブジェクトのデストラクタ
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