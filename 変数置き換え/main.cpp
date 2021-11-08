#define _CRT_SECURE_NO_WARNINGS

//==========================================================
// インクルードファイル
//==========================================================
#include "main.h"
#include "variable.h"
#include "keyboard.h"

//==========================================================
// マクロ定義
//==========================================================

//==========================================================
// 変数宣言
//==========================================================
CVariable* pVariable;

void main(void) {
	pVariable = new CVariable;
	CInputKeyboard* pKeyboard = new CInputKeyboard;
	int nMasara = 0;
	int nRaica = 0;
	int nMocoyasu = 0;

	while (true) {
		DEBUG_VARIABLE("MASARA_NUM", 20.0f, nMasara);
		//DEBUG_VARIABLE("RAICA_NUM", 30.0f, nRaica);
		//DEBUG_VARIABLE("MOCOYASU_NUM", 70.0f, nMocoyasu);

		if (pKeyboard->GetKeyboardTrigger(DIK_P)) {
			printf("%s = %d", TO_STRING(nMasara), nMasara);
		}
	}
}