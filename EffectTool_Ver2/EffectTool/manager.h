//====================================================================
//
// 生成の管理処理 (manager.h)
// Author : 伊藤陽梧
//
//====================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//================================================
// 前方宣言(不完全なクラスは、cppの方でヘッダを呼び出す)
//================================================
class CRenderer;
class CMouse;
class CMode;
class CCamera;
class CLight;
class CTexture;
class CEffectData;
class CEffectTool;

//================================================
// クラス宣言
//================================================

// マネージャークラス
class CManager
{
public:

    // モードの種類
    typedef enum
    {
        MODE_NONE = 0,
		MODE_TOOL,
        MODE_MAX
    }MODE;

    CManager();
    ~CManager();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CRenderer *GetRenderer(void) { return m_pRenderer; }
    static CMouse* GetMouse(void) { return m_pMouse; }
    static CCamera *GetCamera(void) { return m_pCamera; }
    static CTexture *GetTexture(void) { return m_pTexture; }
    static CEffectData *GetEffectData(void) { return m_pEffectData; }
	static CEffectTool *GetEffectTool(void) { return m_pEffectTool; }
    static MODE GetMode(void);
    static void SetMode(MODE mode);

    static void SetScore(int nScore) { m_nScore = nScore; }
    static int GetScore(void) { return m_nScore; }

private:
    static CRenderer *m_pRenderer;              // レンダラーのポインタ
    static CMouse* m_pMouse;                    // マウスのポインタ
    static CMode *m_pMode;                      // モードのポインタ
    static CCamera *m_pCamera;                  // カメラのポインタ
    static CLight *m_pLight;                    // ライトのポインタ
    static CTexture *m_pTexture;                // テクスチャのポインタ
    static CEffectData *m_pEffectData;          // エフェクトデータ管理へのポインタ
	static CEffectTool *m_pEffectTool;          // エフェクトツールのポインタ

    static int m_nScore;                        // スコア
};

#endif