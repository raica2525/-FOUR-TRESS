//=============================================================================
//
// 光源処理 [light.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//================================================
// ライトクラス宣言
//================================================
class CLight
{
public:
    CLight();
    ~CLight();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    CLight *Create(void);
private:
    D3DLIGHT9 m_Light;
};

#endif