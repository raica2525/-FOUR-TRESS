//=============================================================================
//
// テクスチャのデータの処理 [texture.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEXTURE (256) 

//=============================================================================
// テクスチャクラス
//=============================================================================
class CTexture
{
public:
	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

    typedef struct
    {
        LPDIRECT3DTEXTURE9 pTexture;
        int nPattern;
        int nSpeed;
		bool bRepeat;
    }Info;    // テクスチャ情報

    HRESULT Init(void);
    void Uninit(void);

    Info* GetInfo(const int nNum);	// テクスチャ情報

private:
    Info m_aInfo[MAX_TEXTURE];	// テクスチャ情報
};
#endif