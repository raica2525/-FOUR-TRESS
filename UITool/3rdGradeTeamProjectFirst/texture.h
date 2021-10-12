//=============================================================================
//
// テクスチャのデータの処理 [texture.h]
// Author : 後藤慎之助
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
        int nParagraph;
        int nPattern;
        int nSpeed;
        bool bRepeat;
    }Info;    // テクスチャ情報（外部ファイル内で未設定のものが多いので、明示的に初期化する）

    HRESULT Init(void);
    void Uninit(void);

    Info* GetInfo(const int nNum);	// テクスチャ情報

private:
    Info m_aInfo[MAX_TEXTURE];	// テクスチャ情報
};
#endif