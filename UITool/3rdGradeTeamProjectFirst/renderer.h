//====================================================================
//
// 描画処理 (renderer.h)
// Author : 後藤慎之助、池田悠希（マルチパスレンダリングでスクリーン全体のテクスチャを作成）
//
//====================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//================================================
//前方宣言
//================================================
class CEdit;// 工藤追加

//================================================
// クラス宣言
//================================================

// レンダリングクラス
class CRenderer
{
public:
    CRenderer();
    ~CRenderer();
    HRESULT Init(HWND hWnd, bool bWindow);
    void Uninit(void);
    void Update(void);    // オブジェクトのインスタンスがないと、関数が呼べないため持ってくる
    void SpUpdate(void);  // ストライクシュート時の更新
    void Draw(void);      // オブジェクトのインスタンスがないと、関数が呼べないため持ってくる
    LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
    LPDIRECT3DTEXTURE9 GetScreenTexture(void) { return m_pScreenTexture; }
#ifdef _DEBUG
    static void SwitchDispFont(void) { m_bDispFont = !m_bDispFont; }
    static bool GetDispFont(void) { return m_bDispFont; }
#endif

private:
    LPDIRECT3D9				m_pD3D;			    // Direct3Dオブジェクト
    LPDIRECT3DDEVICE9		m_pD3DDevice;	    // Deviceオブジェクト(描画に必要)

    LPDIRECT3DTEXTURE9		m_pScreenTexture;   // スクリーンのテクスチャ
    static CEdit*m_pUI;                         // UIクラスのポインタ（工藤追加）
#ifdef _DEBUG
    void DrawDebugData(void);
    void GameDebugData(void);
    LPD3DXFONT				m_pFont;        // フォントへのポインタ
    static bool             m_bDispFont;    // フォントを表示するかどうか
#endif
};

#endif