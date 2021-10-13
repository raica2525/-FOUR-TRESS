#ifndef UI_H
#define UI_H

#include "main.h"
#include "manager.h"
#include "scene2d.h"
#include "block.h"
#include "enemy.h"
#include "input.h"

class CUi : public CScene2D {
public:
	// 種類
	typedef enum
	{
		TYPE_1,
		TYPE_2,
		TYPE_3,
		TYPE_4,
		TYPE_5,
		TYPE_6,
		TYPE_7,
		TYPE_8,
		TYPE_9,
		TYPE_10,
		TYPE_11,
		TYPE_12,
		TYPE_13,
		TYPE_14,
		TYPE_15,
		TYPE_16,
		TYPE_17,
		TYPE_18,
		TYPE_19,
		TYPE_20,
		TYPE_21,
		TYPE_22,
		TYPE_23,
		TYPE_24,
		TYPE_25,
		TYPE_26,
		TYPE_27,
		TYPE_28,
		TYPE_29,
		TYPE_30,
		TYPE_31,
		TYPE_32,
		TYPE_33,
		TYPE_34,
		TYPE_35,
		TYPE_36,
		TYPE_37,
		TYPE_38,
		TYPE_39,
		TYPE_40,
		TYPE_MAX            // 種類の最大数
	}TYPE;

	CUi();
	~CUi();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void LoadTexture(void);
	static CUi *Create(D3DXVECTOR3 pos);
	void UseInversion(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[3][TYPE_MAX];    // 読み込むテクスチャ(0 : ブロック, 1 : 敵, 2 : その他)

	CInputKeyboard* m_pInputKeyboard;                          // キーボードのポインタ
	bool m_bUse;
};

#endif