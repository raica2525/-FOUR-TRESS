//=============================================================================
//
// エフェクト3D処理 [effect3d.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "effectData.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// エフェクト3Dクラス定義
//=============================================================================
class CEffect3D :public CBillboard
{
public:

    CEffect3D(CScene::OBJTYPE objtype);
    ~CEffect3D();
    HRESULT Init(void);
    void Update(void);
    void Draw(void);
    void Uninit(void);
    static CEffect3D* Emit(const int nType, D3DXVECTOR3 pos, float fEmitRadius = 0.0f);
    static CEffect3D * Create(const int nType, D3DXVECTOR3 pos, float fScatterAngle = 0.0f);

private:
	//================================
	// メンバ関数
	//================================
	void MoveCalculation(const int nType, const float fScatterAngle);
	void UpdateMove(D3DXVECTOR3 &pos);
	void UpdateSize(D3DXVECTOR3 &size);
	void UpdateColor(void);
	void UpdateAngle(float &fAngle);

	//================================
	// メンバ変数
	//================================
	int m_nTexType;					// 使うテクスチャの種類

	D3DXVECTOR3 m_move;				// 移動量
	float m_fAcceleration;			// 加速度（1.0基準）
	float m_fGravity;				// 重力
	float m_fGravityLimit;			// 重力制限

	float m_fRotSpeed;				// 回転速度

	D3DXCOLOR m_col;				// 色
	D3DXCOLOR m_colChangeRate;		// 色変化割合
	float m_fFadeOutRate;			// α値を下げていく割合（色変化割合でも可能だが、明示的に用意した）
	int m_nCntFadeOutLock;			// α値をロックするカウンタ

	D3DXVECTOR3 m_sizeChangeRate;	// 拡大/縮小割合
	int m_nCntSizeChangeLock;		// 大きさをロックするカウンタ
	bool m_bSizeChangeStartOrFinish;// 大きさ変更を開始するか終了するか（ロックのカウンタと併用）

	bool m_bUseAdditiveSynthesis;	// 加算合成にするかどうか
	bool m_bUseZBuffer;				// Zバッファをつかうかどうか

	int m_nCntAnimTime;				// アニメーション用カウンタ
	bool m_bOneRoundAnim;			// アニメーションが一周したかどうか
	int m_nAnimPattern;				// テクスチャ情報保持用
	int m_nAnimSpeed;				// テクスチャ情報保持用
	bool m_bRepeat;					// テクスチャ情報保持用


	int m_nLife;					// 寿命（ツール上のみ）
};
#endif
