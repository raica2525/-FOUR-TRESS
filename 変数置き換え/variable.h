//====================================================================
//
// �V�[����̃I�u�W�F�N�g���� (variable.h)
// Author : �����N�m
//
//====================================================================
#ifndef _VARIABLE_H_
#define _VARIABLE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "keyboard.h"
#include <vector>
#include <algorithm>

//================================================
// �}�N����`
//================================================
#define NULL_NUM (-431602080)
#define TO_STRING(VariableName) # VariableName

//================================================
// �N���X�錾
//================================================

// �I�u�W�F�N�g�̃N���X
class CVariable
{
public:
	typedef struct {
		char* cName;
		float fValue;
	}VARIABLE;

	CVariable();
	~CVariable();
	void Uninit(void);

	void SetVariable(int nNumber, float fValue) { VariableName[nNumber].fValue = fValue; }
	void VariablePushback(VARIABLE Variable) { VariableName.push_back(Variable); }
	VARIABLE GetVariable(int nNumber) { return VariableName[nNumber]; }
	int GetNumber(char* cName);

private:
	std::vector<VARIABLE> VariableName;
};

//==========================================================
// �}�O���֐�
//==========================================================
#define DEBUG_VARIABLE(VariableName, fNum, fReference) \
do { \
static CVariable* pVariable = new CVariable; CVariable::VARIABLE Variable; HANDLE hClip; char Str[256]; float fNumber = fNum; int nNumber; float fValue = fNum; \
if (pVariable->GetNumber(VariableName) <= -1) { Variable.cName = VariableName; Variable.fValue = fNum; pVariable->VariablePushback(Variable); } \
 \
ZeroMemory(Str, sizeof(Str)); \
nNumber = pVariable->GetNumber(VariableName); \
Variable = pVariable->GetVariable(nNumber); \
if (Variable.fValue != NULL_NUM) { fValue = Variable.fValue; } \
 \
if (pKeyboard->GetKeyboardPress(DIK_LCONTROL) && pKeyboard->GetKeyboardTrigger(DIK_V)) { \
OpenClipboard(NULL); \
hClip = GetClipboardData(CF_TEXT); \
if (hClip != NULL && strstr((char*)GlobalLock(hClip), VariableName)) { sscanf((char*)GlobalLock(hClip), "%s = %f", Str, &fNumber); fValue = fNumber; GlobalUnlock(hClip); } \
CloseClipboard(); \
 }\
pVariable->SetVariable(nNumber, fValue); \
fReference = fValue; \
} while(0)

#endif