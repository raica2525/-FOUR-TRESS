//====================================================================
//
// エフェクトデータ管理 (effectData.h)
// Author : 伊藤陽梧
//
//====================================================================
#ifndef _EFFECT_DATA_H_
#define _EFFECT_DATA_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_PI (628)					// 円の表現の際に使う値
#define EFFECT_FLOATING_POINT (100.0f)	// エフェクトの浮動小数点

// ブロック等に当たった際、板ポリのエフェクトを置くための回転量（ブロックの中から見ているので注意）
#define LAY_ROT_TOP D3DXVECTOR3(D3DXToRadian(-90.0f), 0.0f, 0.0f)	// 天井
#define LAY_ROT_LEFT D3DXVECTOR3(0.0f, D3DXToRadian(270.0f), 0.0f)	// 左壁
#define LAY_ROT_BOT D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f)	// 地面
#define LAY_ROT_RIGHT D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f)	// 右壁

//================================================
// クラス宣言
//================================================

// エフェクトデータの管理クラス
class CEffectData
{
public:
    CEffectData();
    ~CEffectData();

	typedef enum
	{
		TYPE_0 = 0,
		TYPE_1,				
		TYPE_2,		
		TYPE_3,
		TYPE_4,
		TYPE_5,
		TYPE_6,
		TYPE_7,
		TYPE_8,
		TYPE_9,
		TYPE_MAX
	}TYPE;  // 生成するエフェクトの種類

	typedef enum
	{
		PLANE_XY = 0,   // XY平面
		PLANE_XZ,       // XZ平面
	}PLANE;  // 平面の情報

	typedef struct
	{
		int nTexType;					// 使うテクスチャの種類
		int nNumOnce;					// 同時発生数
		int plane;						// 平面

		bool bOnCircleEdge;				// 円の縁から放出するかどうか
		bool bEmitVectorInside;			// 放出方向を内側にするかどうか
		int nScatterAngle;				// 飛散角度（0〜314）
		int nScatterWidth;				// 飛散幅（0〜314）

		int nSpeedMax;					// 最大速度
		int nSpeedMin;					// 最小速度
		int nAuxiliaryAxisSpeedMax;		// 補助軸の最大速度（2D→3Dで、立体感を出すためのもの）
		int nAuxiliaryAxisSpeedMin;		// 補助軸の最小速度（2D→3Dで、立体感を出すためのもの）
		float fEmitRadius;				// 半径の大きさ

		float fAcceleration;			// 加速度（1.0基準）
		float fGravity;					// 重力
		float fGravityLimit;			// 重力制限

		int nLayRot;					// ポリゴンそのものを横にするかどうか（1,2ならビルボード解除）
		bool bRotEqualMoveAngle;		// 回転を移動の向きに合わせるか
		int nRotSpeedMax;				// 最大回転速度
		int nRotSpeedMin;				// 最小回転速度

		D3DXCOLOR col;					// 色
		D3DXCOLOR colChangeRate;		// 色変化割合
		float fFadeOutRate;				// α値を下げていく割合（色変化割合でも可能だが、明示的に用意した）
		int nCntFadeOutLock;			// α値の変化をロックするカウンタ

		int nSizeMax;					// 最大大きさ
		int nSizeMin;					// 最小大きさ
		D3DXVECTOR3 sizeChangeRate;		// 拡大/縮小割合
		int nCntSizeChangeLock;			// 大きさをロックするカウンタ
		bool bSizeChangeStartOrFinish;	// 大きさを変えるのが始まるか、終わるのか

		bool bUseAdditiveSynthesis;		// 加算合成にするかどうか
		bool bUseZBuffer;				// Zバッファをつかうかどうか
		int nAlphaTestBorder;			// αテストのボーダー
	}CreateInfo;    // 生成情報

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理

	HRESULT UploadEffectInfo(const bool *bUpload);

	CreateInfo* GetCreateInfo(const int nNum);
	void SetCreateInfo(const int nNum);
private:
	CreateInfo m_aCreateInfo[TYPE_MAX];	// 生成情報
};

#endif