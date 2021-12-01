//====================================================================
//
// エフェクトツールの処理 (effecttool.h)
// Author : 伊藤　陽梧
//
//====================================================================
#ifndef _EFFECTTOOL_H_
#define _EFFECTTOOL_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//================================================
// マクロ定義
//================================================
#define EFFECT_TYPE (10)

//================================================
// エフェクトツールクラス
//================================================
class CEffectTool
{
public:

	CEffectTool();
	~CEffectTool();

	typedef struct
	{
		D3DXVECTOR3 pos;				// 座標

		int nTexType;					// 使うテクスチャの種類
		int nNumOnce;					// 同時発生数
		int nPlane;						// 平面

		bool bOnCircleEdge;				// 円周上にするかどうか
		bool bEmitVectorInside;			// 放出方向を内側にするかどうか
		int nScatterAngle;				// 飛散角度（0～314）
		int nScatterWidth;				// 飛散幅（0～314）
		float fEmitRadius;				// 半径の大きさ

		int nSpeedMax;					// 最大速度
		int nSpeedMin;					// 最小速度
		int nAuxiliaryAxisSpeedMax;		// 最大補助軸（2D→3Dで、立体感を出すためのもの）
		int nAuxiliaryAxisSpeedMin;		// 最小補助軸（2D→3Dで、立体感を出すためのもの）

		float fAcceleration;			// 加速度(1.0最大)
		float fGravity;					// 重力
		float fGravityLimit;			// 重力制限

		int nLayRot;					// ポリゴンそのものを横にするかどうか（1,2ならビルボード解除）
		bool bRotEqualMoveAngle;		// 回転を移動の向きに合わせるか
		int nRotSpeedMax;				// 最大回転速度
		int nRotSpeedMin;				// 最小回転速度

		D3DXCOLOR col;					// 色
		D3DXCOLOR colChangeRate;		// 色変化割合
		float fFadeOutRate;				// フェードアウトの割合
		int nCntFadeOutLock;			// α値をロックするカウンタ

		int nSizeMax;					// 最大大きさ
		int nSizeMin;					// 最小大きさ
		D3DXVECTOR3 fSizeChangeRate;	// 拡大/縮小割合
		int nCntSizeChangeLock;			// 大きさをロックするカウンタ
		bool bSizeChangeStartOrFinish;	// 大きさを変えるのが始まるか、終わるのか

		bool bUseAdditiveSynthesis;		// 加算合成するかどうか
		bool bUseZBuffer;				// Zバッファを使うか
		int nAlphaTestBorder;			// αテストのボーダー
	}EffectInfo;	// エフェクトの情報

	HRESULT Init(HWND hWnd);	// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void SetEffectInfo(int nEffectType);		// エフェクト情報セット処理
	EffectInfo* GetEffectInfo(int nEffectType);	// エフェクト情報取得処理
private:
	//====================
	// メンバ関数
	//====================
	EffectInfo InitEffectInfo(void);	// エフェクトツールの情報を一気に初期化する処理

	void UpdateEffectImgui(void);	// エフェクト用Imguiの更新処理
	void UpdateOptionImgui(void);	// オプション用Imguiの更新処理

	// Imguiの項目ごとの処理
	void ImguiEffectPos(void);		// 座標に関する設定
	void ImguiEffectOption(void);	// エフェクトに関する設定
	void ImguiEffectMove(void);		// 移動に関する設定
	void ImguiEffectRot(void);		// 回転に関する設定
	void ImguiEffectCol(void);		// 色に関する設定
	void ImguiEffectSize(void);		// サイズに関する設定
	void ImguiEffectDraw(void);		// 描画に関する設定
	void ImguiEffectCreate(void);	// エフェクトの生成に関する設定
	void ImguiEffectCamera(void);	// カメラに関する設定
	void EffectCreate(void);		// エフェクトの生成

	void HelpText(const char* cText);	// 注意書きの処理

	//====================
	// メンバ変数
	//====================
	EffectInfo m_EffectInfo;		// エフェクトの情報
	int m_nEffectNum;				// エフェクトの番号
	float m_fCreateFlame;			// 生成するフレーム
	float m_fCountFlame;			// カウント
	float m_fBarWidth;				// バーの横幅
	bool m_bCreate[EFFECT_TYPE];	// 各エフェクトの生成するかしないか
	bool m_bRandamCreate;			// ランダムで生成させるか
	bool m_bShowImguiWindow[2];		// Imguiのウィンドウをつけるか消すか
	D3DXVECTOR3 m_RandomRangePos;	// ランダムな座標で生成するときの範囲
};

#endif