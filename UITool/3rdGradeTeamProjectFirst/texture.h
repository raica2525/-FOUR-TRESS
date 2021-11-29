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
#define MAX_TEXTURE (256) // テクスチャの最大数

//=============================================================================
// テクスチャクラス
//=============================================================================
class CTexture
{
    static CTexture* m_pInstance;// オブジェクトへのポインタ

public:
	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

    // テクスチャ情報（外部ファイル内で未設定のものが多いので、明示的に初期化する）
    typedef struct
    {
        LPDIRECT3DTEXTURE9 pTexture;
        int nParagraph;
        int nPattern;
        int nSpeed;
        bool bRepeat;
    }Info;   

    HRESULT Init(void);
    void Uninit(void);

    // Get関数
    Info* GetInfo(const int nNum);	// テクスチャ情報
    static int GetnNumTexture(void) {
        return m_nNumTexture; }
private:
    Info m_aInfo[MAX_TEXTURE];	// テクスチャ情報
    static int m_nNumTexture;// テクスチャの数
};
#endif