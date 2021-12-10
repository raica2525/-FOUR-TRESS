//===============================================
//
// エフェクトツール処理 (effecttool.cpp)
// Author : 伊藤陽梧
//
//===============================================

//===============================================
// インクルードファイル
//===============================================
#include "effecttool.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "renderer.h"
#include "manager.h"
#include "effect3d.h"
#include "effectData.h"
#include "camera.h"
#include "mouse.h"
#include "grid.h"
#include <array>

//================================================
// マクロ定義
//================================================
#define SPEED_MAX (2000)				// 速度の最大値
#define ACCELERATION_MAX (10.0f)		// 加速度の最大値
#define GRAVITY_MAX (100.0f)			// 重力の最大値
#define COLCHANGERATE_MAX (1.0f)		// 色変化割合の最大値
#define FADEOUTRATE_MAX (1.0f)			// フェードアウトの割合の最大値
#define EFFECT_SIZE_MAX (50000)			// サイズの最大値
#define EFFECT_SIZE_MIN (0)				// サイズの最小値
#define SIZECHANGERATE_MAX (2000.0f)	// サイズの拡大/縮小割合最大値
#define SIZECHANGERATE_MIN (-2000.0f)	// サイズの拡大/縮小割合最小値
#define ALPHATEST_MAX (255)				// アルファテストの最大値
#define IMGUI_BAR_WIDTH_INIT (215.0f)	// IMGUIのバーの横幅の初期値
#define IMGUI_BAR_WIDTH_MAX (1000.0f)	// IMGUIのバーの横幅の最大値
#define CREATE_FLAME_MAX (240.0f)		// 生成するフレームの最大値
#define INT_ZERO (0)					// intの初期値
#define FLOAT_ZERO (0.0f)				// floatの初期値

//===============================================
// コンストラクタ
//===============================================
CEffectTool::CEffectTool()
{
	m_EffectInfo = InitEffectInfo();					// エフェクトの情報の初期化
	m_nEffectNum = 0;									// エフェクトのタイプ
	m_fCreateFlame = 0.0f;								// エフェクトを生成する時間
	m_fCountFlame = 0.0f;								// エフェクトを生成する時間のカウント
	m_fBarWidth = IMGUI_BAR_WIDTH_INIT;					// IMGUIのバーの横幅
	memset(m_bCreate, false, sizeof(m_bCreate));		// 生成するかしないか
	m_bRandamCreate = false;								// ランダムで生成させるか
	memset(m_RandomRangePos, false, sizeof(m_RandomRangePos));	// ランダムな範囲で生成するときの座標
}

//===============================================
// デストラクタ
//===============================================
CEffectTool::~CEffectTool()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CEffectTool::Init(HWND hWnd)
{
	// エフェクトのデータから値をセット
	SetEffectInfo(m_nEffectNum);

	// imguiのセットアップ
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// フォントの読み込み
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("Data/fonts/meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	// imguiのスタイル
	ImGui::StyleColorsClassic();

	// imguiの初期化処理
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CEffectTool::Uninit(void)
{		
	m_EffectInfo = InitEffectInfo();					// エフェクトの情報の初期化

	m_nEffectNum = 0;									// エフェクトのタイプ
	m_fCreateFlame = 0.0f;								// エフェクトを生成する時間
	m_fCountFlame = 0.0f;								// エフェクトを生成する時間のカウント
	m_fBarWidth = 0.0f;									// IMGUIのバーの横幅
	memset(m_bCreate, false, sizeof(m_bCreate));		// 生成するかしないか
	m_bRandamCreate = false;								// ランダムで生成させるか
	memset(m_RandomRangePos, false, sizeof(m_RandomRangePos));	// ランダムな範囲で生成するときの座標

	// imguiのシャットダウン
	ImGui_ImplDX9_Shutdown();
}

//===============================================
// 更新処理
//===============================================
void CEffectTool::Update(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// エフェクト用Imguiの更新処理
	UpdateEffectImgui();

	// オプション用Imguiの更新処理
	UpdateOptionImgui();

	ImGui::EndFrame(); //更新処理の終わりに
}

//===============================================
// 描画処理
//===============================================
void CEffectTool::Draw(void)
{
	// imguiの描画処理
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//===============================================
// エフェクトツールの情報を一気に初期化する処理
//===============================================
CEffectTool::EffectInfo CEffectTool::InitEffectInfo(void)
{
	EffectInfo Effectinfo;
	memset(Effectinfo.pos, NULL, sizeof(Effectinfo.pos));							// 座標

	Effectinfo.nTexType = 0;														// 使うテクスチャの種類
	Effectinfo.nNumOnce = 0;														// 同時発生数
	Effectinfo.nPlane = 0;															// 平面

	Effectinfo.bOnCircleEdge = false;												// 円周上にするかどうか（最大放出半径をもとに）
	Effectinfo.bEmitVectorInside = false;											// 放出方向を内側にするかどうか
	Effectinfo.nScatterAngle = 0;													// 飛散角度（0～314）
	Effectinfo.nScatterWidth = 0;													// 飛散幅（0～314）
	Effectinfo.fEmitRadius = 0.0f;													// 半径の大きさ

	Effectinfo.nSpeedMax = 0;														// 最大速度
	Effectinfo.nSpeedMin = 0;														// 最小速度
	Effectinfo.nAuxiliaryAxisSpeedMax = 0;											// 最大補助軸（2D→3Dで、立体感を出すためのもの）
	Effectinfo.nAuxiliaryAxisSpeedMin = 0;											// 最小補助軸（2D→3Dで、立体感を出すためのもの）

	Effectinfo.fAcceleration = 0.0f;												// 加速度(1.0最大)
	Effectinfo.fGravity = 0.0f;														// 重力
	Effectinfo.fGravityLimit = 0.0f;												// 重力制限

	Effectinfo.nLayRot = 0;															// ポリゴンそのものを横にするかどうか（trueならビルボード解除）
	Effectinfo.nRotSpeedMax = 0;													// 最大回転速度
	Effectinfo.nRotSpeedMin = 0;													// 最小回転速度

	memset(&Effectinfo.col, NULL, sizeof(Effectinfo.col));							// 色
	memset(&Effectinfo.colChangeRate, NULL, sizeof(Effectinfo.colChangeRate));		// 色変化割合
	Effectinfo.fFadeOutRate = 0.0f;													// フェードアウトの割合
	Effectinfo.nCntFadeOutLock = 0;													// α値の変化をロックするカウンタ

	Effectinfo.nSizeMax = 0;														// 最大大きさ
	Effectinfo.nSizeMin = 0;														// 最小大きさ
	memset(Effectinfo.fSizeChangeRate, NULL, sizeof(Effectinfo.fSizeChangeRate));	// 拡大/縮小割合	
	Effectinfo.nCntSizeChangeLock = 0;												// 大きさをロックするカウンタ
	Effectinfo.bSizeChangeStartOrFinish = false;									// 大きさを変えるのが始まるか、終わるのか

	Effectinfo.bUseAdditiveSynthesis = false;										// 加算合成するかどうか
	Effectinfo.bUseZBuffer = false;													// Zバッファを使うか
	Effectinfo.nAlphaTestBorder = 0;												// αテストのボーダー

	return Effectinfo;
}

//===============================================
// エフェクト用Imguiの更新処理
//===============================================
void CEffectTool::UpdateEffectImgui(void)
{
	int nEffectType = m_nEffectNum;

	// バーの横幅
	ImGui::PushItemWidth(m_fBarWidth);

	// エフェクトの情報をデータから受け取る
	SetEffectInfo(m_nEffectNum);

	// ウィンドウを出す位置の設定
	ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 300), ImGuiCond_Once);
	ImGui::Begin(u8"エフェクトツール");

	// 座標に関する設定
	ImguiEffectPos();

	// エフェクトに関する設定
	ImguiEffectOption();

	// 移動に関する設定
	ImguiEffectMove();

	// 回転に関する設定
	ImguiEffectRot();

	// 色に関する設定
	ImguiEffectCol();

	// サイズに関する設定
	ImguiEffectSize();

	// 描画に関する設定
	ImguiEffectDraw();

	// エフェクトの生成に関する設定
	ImguiEffectCreate();

	// エフェクトの生成
	EffectCreate();
	CCamera * pCamera = CManager::GetCamera();

	ImGui::Text(u8"CameraDistance：%.1f", pCamera->GetDistance());
	ImGui::Text(u8"CameraPhi：%.3f", pCamera->GetPhi());
	ImGui::Text(u8"CameraTheta：%.3f", pCamera->GetTheta());


	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	// エフェクトのタイプが変更されてたら
	if (nEffectType != m_nEffectNum)
	{
		// エフェクトの情報をデータから受け取る
		SetEffectInfo(m_nEffectNum);
	}

	// 更新した値をデータにセットする
	CManager::GetEffectData()->SetCreateInfo(m_nEffectNum);
}

//===============================================
// オプション用Imguiの更新処理
//===============================================
void CEffectTool::UpdateOptionImgui(void)
{
	// ウィンドウを出す位置の設定
	ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 + 100), ImGuiCond_Once);
	ImGui::Begin(u8"オプション");

	// グリッドの設定
	if (ImGui::CollapsingHeader("grid"))
	{
		CScene* pScene = CScene::GetTopScene(CScene::OBJTYPE_GRID);
		for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_GRID); nCntScene++)
		{
			// 中身があるなら
			if (pScene != NULL)
			{
				// 次のシーンを保存
				CScene*pNextScene = pScene->GetNextScene();

				// グリッドにキャスト
				CGrid *pGrid = (CGrid*)pScene;
				
				ImGui::DragFloat(u8"グリッドの大きさ", &pGrid->GetSize(), 1.0f, -1000.0f, 1000.0f);	// グリッドのサイズ
				ImGui::SameLine(); HelpText(u8"一辺の大きさ");

				ImGui::Checkbox(u8"ZXの表示", &pGrid->GetbShowLine(0));							// ZXの線の表示
				ImGui::Checkbox(u8"XYの表示", &pGrid->GetbShowLine(1));							// XYの線の表示
				ImGui::Checkbox(u8"YZの表示", &pGrid->GetbShowLine(2));							// YZの線の表示

				// 次のシーンにする
				pScene = pNextScene;
			}
			else
			{
				// 中身がないなら、そこで処理を終える
				break;
			}
		}

	}

	// マウスの設定
	if (ImGui::CollapsingHeader("mouse"))
	{
		// マウスのポインタ
		CMouse* pMouse = CManager::GetMouse();
		ImGui::DragFloat(u8"マウスの感度", &pMouse->GetMouseSensi(), 0.001f, 0.0f, 1.0f);			// マウスの感度
		ImGui::DragFloat(u8"マウスホイールの感度", &pMouse->GetWheelSensi(), 0.001f, 0.0f, 1.0f);	// マウスホイールの感度

	}

	// カメラに関する設定
	ImguiEffectCamera();

	ImGui::End();
}

//===============================================
// 座標に関する設定
//===============================================
void CEffectTool::ImguiEffectPos(void)
{
	// 座標に関する設定
	if (ImGui::CollapsingHeader("pos"))
	{
		ImGui::DragFloat3("Pos", m_EffectInfo.pos, 1.0f, -1000.0f, 1000.0f);			// 座標
		ImGui::DragFloat3("RandomRangePos", m_RandomRangePos, 1.0f, -1000.0f, 1000.0f);	// ランダムで出す範囲
		ImGui::SameLine(); HelpText(u8"ランダムでエフェクトを発生させる範囲");
		ImGui::Checkbox(u8"ランダムで出すか", &m_bRandamCreate);							// ランダムで出すか
		ImGui::SameLine(); HelpText(u8"RandomRangePosで設定した範囲内でランダムに出るようになる");
	}
}

//===============================================
// エフェクトに関する設定
//===============================================
void CEffectTool::ImguiEffectOption(void)
{
	if (ImGui::CollapsingHeader("effectoption"))
	{
		// 日本語入力作りたかったけど無理だったわ
		//ImGui::InputText(u8"エフェクトの名前", m_Text, sizeof(m_Text));

		// タイプの切り替え
		ImGui::SliderInt(u8"エフェクトの番号", &m_nEffectNum, INT_ZERO, CEffectData::TYPE::TYPE_MAX - 1);
		ImGui::SameLine(); HelpText(u8"0～9までの値を変更したいエフェクトの番号");

		// テクスチャの選択
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { m_EffectInfo.nTexType--; }
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { m_EffectInfo.nTexType++; }
		// 0以下にならないように
		if (m_EffectInfo.nTexType < INT_ZERO)
		{
			m_EffectInfo.nTexType = INT_ZERO;
		}
		ImGui::SameLine();
		ImGui::Text("%d", m_EffectInfo.nTexType);
		ImGui::SameLine();
		ImGui::Text(u8"テクスチャの種類");
		ImGui::SameLine(); HelpText(u8"テキストから読み込んだテクスチャの番号");

		// 発生数
		ImGui::InputInt(u8"発生数", &m_EffectInfo.nNumOnce);
		ImGui::SameLine(); HelpText(u8"一度に出す数");

		// 発生数は1よりは少なくならない
		if (m_EffectInfo.nNumOnce < 1)
		{
			m_EffectInfo.nNumOnce = 1;
		}

		ImGui::SliderInt(u8"平面", &m_EffectInfo.nPlane, INT_ZERO, 1);									// 平面の切り替え
		ImGui::SameLine(); HelpText(u8"0=XY平面、1=XZ平面");
		ImGui::Checkbox(u8"円周上にするかどうか", &m_EffectInfo.bOnCircleEdge);							// 円周上にするかどうか（最大放出半径をもとに）
		ImGui::SameLine(); HelpText(u8"半径の大きさを参照して円形状にエフェクトを出せる");
		ImGui::Checkbox(u8"放出方向を内側にするかどうか", &m_EffectInfo.bEmitVectorInside);				// 放出方向を内側にするかどうか
		ImGui::SameLine(); HelpText(u8"中心に向かってエフェクトが出るようになる");
		ImGui::DragInt(u8"飛散角度（0～628）", &m_EffectInfo.nScatterAngle, 1, INT_ZERO, EFFECT_PI);	// 飛散角度（0～628）
		ImGui::SameLine(); HelpText(u8"飛ばす角度");
		ImGui::DragInt(u8"飛散幅（0～628）", &m_EffectInfo.nScatterWidth, 1, INT_ZERO, EFFECT_PI);		// 飛散幅（0～628）
		ImGui::SameLine(); HelpText(u8"飛ばす幅");
		ImGui::DragFloat(u8"半径の大きさ", &m_EffectInfo.fEmitRadius, 1.0f, FLOAT_ZERO, 10000.0f);		// 半径の大きさ
		ImGui::SameLine(); HelpText(u8"半径内でランダムで出せる");
	}
}

//===============================================
// 移動に関する設定
//===============================================
void CEffectTool::ImguiEffectMove(void)
{
	if (ImGui::CollapsingHeader("move"))
	{
		ImGui::DragInt(u8"最大速度", &m_EffectInfo.nSpeedMax, 1, m_EffectInfo.nSpeedMin, SPEED_MAX);								// 最大速度
		ImGui::SameLine(); HelpText(u8"最大の速度");
		ImGui::DragInt(u8"最小速度", &m_EffectInfo.nSpeedMin, 1, -SPEED_MAX, m_EffectInfo.nSpeedMax);								// 最小速度
		ImGui::SameLine(); HelpText(u8"最小の速度");
		ImGui::DragInt(u8"最大補助軸", &m_EffectInfo.nAuxiliaryAxisSpeedMax, 1, m_EffectInfo.nAuxiliaryAxisSpeedMin, SPEED_MAX);	// 最大補助軸（2D→3Dで、立体感を出すためのもの）
		ImGui::SameLine(); HelpText(u8"2Dから3Dに立体感を出させるもの\n平面XYならZ方向に、平面XZならY方向に");
		ImGui::DragInt(u8"最小補助軸", &m_EffectInfo.nAuxiliaryAxisSpeedMin, 1, -SPEED_MAX, m_EffectInfo.nAuxiliaryAxisSpeedMax);	// 最小補助軸（2D→3Dで、立体感を出すためのもの）
		ImGui::SameLine(); HelpText(u8"2Dから3Dに立体感を出させるもの\n平面XYならZ方向に、平面XZならY方向に");
		ImGui::DragFloat(u8"加速度(1.0最大)", &m_EffectInfo.fAcceleration, 0.001f, FLOAT_ZERO, ACCELERATION_MAX);					// 加速度(1.0最大)
		ImGui::SameLine(); HelpText(u8"1.0が基準、変化させることで移動にメリハリが付けれる");
		ImGui::DragFloat(u8"重力", &m_EffectInfo.fGravity, 0.01f, FLOAT_ZERO, GRAVITY_MAX);											// 重力
		ImGui::SameLine(); HelpText(u8"重力の大きさ");
		ImGui::DragFloat(u8"重力制限", &m_EffectInfo.fGravityLimit, 0.01f, FLOAT_ZERO, GRAVITY_MAX);								// 重力制限
		ImGui::SameLine(); HelpText(u8"重力の大きさが設定した値より大きくならないようにする");
	}
}

//===============================================
// 回転に関する設定
//===============================================
void CEffectTool::ImguiEffectRot(void)
{
	if (ImGui::CollapsingHeader("rot"))
	{
		ImGui::SliderInt(u8"ポリゴンをどの方向に固定するか", &m_EffectInfo.nLayRot, INT_ZERO, 4);					// ポリゴンそのものをどの方向に固定するか（1,2,3,4ならビルボード解除）
		ImGui::SameLine(); HelpText(u8"0以外にした場合ポリゴンの向きを固定する\n1=上向き、2=右向き、3=下向き、4=左向き");
		ImGui::Checkbox(u8"回転を移動の向きに合わせるか", &m_EffectInfo.bRotEqualMoveAngle);						// 回転を移動の向きに合わせるか
		ImGui::SameLine(); HelpText(u8"回転が移動する方向を上にして飛ぶようになる");
		ImGui::DragInt(u8"最大回転速度", &m_EffectInfo.nRotSpeedMax, 1, m_EffectInfo.nRotSpeedMin, EFFECT_PI * 2);	// 最大回転速度
		ImGui::SameLine(); HelpText(u8"最大の回転速度");
		ImGui::DragInt(u8"最小回転速度", &m_EffectInfo.nRotSpeedMin, 1, INT_ZERO, m_EffectInfo.nRotSpeedMax);		// 最小回転速度
		ImGui::SameLine(); HelpText(u8"最小の回転速度");
	}
}

//===============================================
// 色に関する設定
//===============================================
void CEffectTool::ImguiEffectCol(void)
{
	if (ImGui::CollapsingHeader("col"))
	{
		ImGui::ColorEdit4(u8"色", m_EffectInfo.col, ImGuiColorEditFlags_Float);											// 色
		ImGui::SameLine(); HelpText(u8"エフェクトの色");
		ImGui::DragFloat4(u8"色変化割合", m_EffectInfo.colChangeRate, 0.001f, -COLCHANGERATE_MAX, COLCHANGERATE_MAX);	// 色変化割合
		ImGui::SameLine(); HelpText(u8"設定した色の値を加算していく");
		ImGui::DragFloat(u8"フェードアウトの割合", &m_EffectInfo.fFadeOutRate, 0.001f, FLOAT_ZERO, FADEOUTRATE_MAX);	// フェードアウトの割合
		ImGui::SameLine(); HelpText(u8"アルファ値を下げていく");
		ImGui::DragInt(u8"アルファ値をロックするカウンタ", &m_EffectInfo.nCntFadeOutLock, 1, INT_ZERO, 1000);			// α値の変化をロックするカウンタ
		ImGui::SameLine(); HelpText(u8"設定したフレームが過ぎた後にアルファ値が下がるようになる");
	}
}

//===============================================
// サイズに関する設定
//===============================================
void CEffectTool::ImguiEffectSize(void)
{
	if (ImGui::CollapsingHeader("size"))
	{
		ImGui::DragInt(u8"最大の大きさ", &m_EffectInfo.nSizeMax, 1, m_EffectInfo.nSizeMin, EFFECT_SIZE_MAX);				// 最大の大きさ
		ImGui::SameLine(); HelpText(u8"ポリゴンの最大の大きさ");
		ImGui::DragInt(u8"最小の大きさ", &m_EffectInfo.nSizeMin, 1, EFFECT_SIZE_MIN, m_EffectInfo.nSizeMax);				// 最小の大きさ
		ImGui::SameLine(); HelpText(u8"ポリゴンの最小の大きさ");
		ImGui::DragFloat3(u8"拡大/縮小割合", m_EffectInfo.fSizeChangeRate, 0.01f, SIZECHANGERATE_MIN, SIZECHANGERATE_MAX);	// 拡大/縮小割合
		ImGui::SameLine(); HelpText(u8"設定した値をサイズに加算していく");
		ImGui::DragInt(u8"大きさをロックするカウンタ", &m_EffectInfo.nCntSizeChangeLock, 1, EFFECT_SIZE_MIN, 1000);			// 大きさをロックするカウンタ
		ImGui::SameLine(); HelpText(u8"設定したフレームの後に大きさの変化を止めたり、終わった後に大きさが変わるようになる");
		ImGui::Checkbox(u8"大きさを変えるのか", &m_EffectInfo.bSizeChangeStartOrFinish);									// 大きさを変えるのが始まりか、終わりか
		ImGui::SameLine(); HelpText(u8"大きさを変えるのが最初からならチェック\nフレームが過ぎた後から変えたいならチェックを外す");
	}
}

//===============================================
// 描画に関する設定
//===============================================
void CEffectTool::ImguiEffectDraw(void)
{
	if (ImGui::CollapsingHeader("draw"))
	{
		ImGui::Checkbox(u8"加算合成するかどうか", &m_EffectInfo.bUseAdditiveSynthesis);								// 加算合成するかどうか
		ImGui::Checkbox(u8"Zバッファを使うか", &m_EffectInfo.bUseZBuffer);											// Zバッファを使うか
		ImGui::DragInt(u8"アルファテストのボーダー", &m_EffectInfo.nAlphaTestBorder, 1, INT_ZERO, ALPHATEST_MAX);	// αテストのボーダー
	}
}

//===============================================
// エフェクトの生成に関する設定
//===============================================
void CEffectTool::ImguiEffectCreate(void)
{
	if (ImGui::CollapsingHeader("create"))
	{
		ImGui::DragFloat(u8"生成するフレーム", &m_fCreateFlame, 1.0f, FLOAT_ZERO, CREATE_FLAME_MAX);	// 生成するフレーム
		ImGui::SameLine(); HelpText(u8"設定したフレームでエフェクトが出るようになる(最大値240)");

		// エフェクトを生成するかどうか(forじゃできなかったからなにかいい方法はないもんかねぇ)
		ImGui::Checkbox(u8"エフェクト0", &m_bCreate[0]);
		ImGui::Checkbox(u8"エフェクト1", &m_bCreate[1]);
		ImGui::Checkbox(u8"エフェクト2", &m_bCreate[2]);
		ImGui::Checkbox(u8"エフェクト3", &m_bCreate[3]);
		ImGui::Checkbox(u8"エフェクト4", &m_bCreate[4]);
		ImGui::Checkbox(u8"エフェクト5", &m_bCreate[5]);
		ImGui::Checkbox(u8"エフェクト6", &m_bCreate[6]);
		ImGui::Checkbox(u8"エフェクト7", &m_bCreate[7]);
		ImGui::Checkbox(u8"エフェクト8", &m_bCreate[8]);
		ImGui::Checkbox(u8"エフェクト9", &m_bCreate[9]);

		if (ImGui::Button("upload"))
		{
			CManager::GetEffectData()->UploadEffectInfo(m_bCreate);
		}
		ImGui::SameLine(); HelpText(u8"チェックを付けたエフェクトの情報をeffectinfo.txtにアップロードする");

		ImGui::SameLine();
		if (ImGui::Button("reload"))
		{
			// エフェクトデータのリロード
			CEffectData* pEffectData = CManager::GetEffectData();
			pEffectData->Init();
			SetEffectInfo(m_nEffectNum);
		}
		ImGui::SameLine(); HelpText(u8"effect.txtの情報をリロードする");
	}
}

//===============================================
// カメラに関する設定
//===============================================
void CEffectTool::ImguiEffectCamera(void)
{
	if (ImGui::CollapsingHeader("camera"))
	{
		if (ImGui::Button("CameraReset"))
		{
			// カメラのリセット
			CManager::GetCamera()->ResetGameCamera();
		}
		ImGui::SameLine(); HelpText(u8"カメラを初期位置に戻す");
	}
}

//===============================================
// エフェクトの生成
//===============================================
void CEffectTool::EffectCreate(void)
{
	// カウントが最大値を超えたら
	if (m_fCountFlame > CREATE_FLAME_MAX)
	{
		m_fCountFlame = INT_ZERO;
	}
	else
	{
		// カウントの加算
		m_fCountFlame++;
	}

	// 設定したフレームとカウントが一致したら
	if (m_fCreateFlame == m_fCountFlame)
	{
		// エフェクトの生成情報を取得
		CEffectData *pEffectData = CManager::GetEffectData();

		// 範囲からランダムに座標を決める
		D3DXVECTOR3 Randompos = D3DXVECTOR3((float)(rand() % (int)(m_RandomRangePos.x + 1.0f)),
											(float)(rand() % (int)(m_RandomRangePos.y + 1.0f)),
											(float)(rand() % (int)(m_RandomRangePos.z + 1.0f)))
											- m_RandomRangePos / 2.0f;

		for (int nCount = 0; nCount < CEffectData::TYPE::TYPE_MAX; nCount++)
		{
			if (m_bCreate[nCount])
			{
				// ランダムで発生させるか
				if (m_bRandamCreate)
				{
					// エフェクト発生
					CEffect3D::Emit(nCount, Randompos, pEffectData->GetCreateInfo(nCount)->fEmitRadius);
				}
				else
				{
					// エフェクト発生
					CEffect3D::Emit(nCount, m_EffectInfo.pos, pEffectData->GetCreateInfo(nCount)->fEmitRadius);
				}
			}
		}
		// カウントの初期化
		m_fCountFlame = INT_ZERO;
	}
}

//===============================================
// 注意書きの処理
//===============================================
void CEffectTool::HelpText(const char* cText)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(cText);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

//===============================================
// エフェクト情報セット処理
//===============================================
void CEffectTool::SetEffectInfo(int nEffectType)
{
	// エフェクトの生成情報を取得
	CEffectData *pEffectData = CManager::GetEffectData();
	CEffectData::CreateInfo *pCreateInfo = pEffectData->GetCreateInfo(nEffectType);

	m_EffectInfo.nTexType = pCreateInfo->nTexType;								// 使うテクスチャの種類
	m_EffectInfo.nNumOnce = pCreateInfo->nNumOnce;								// 同時発生数
	m_EffectInfo.nPlane = pCreateInfo->plane;									// 平面

	m_EffectInfo.bOnCircleEdge = pCreateInfo->bOnCircleEdge;					// 円周上にするかどうか
	m_EffectInfo.bEmitVectorInside = pCreateInfo->bEmitVectorInside;			// 放出方向を内側にするかどうか
	m_EffectInfo.nScatterAngle = pCreateInfo->nScatterAngle;					// 飛散角度（0～314）
	m_EffectInfo.nScatterWidth = pCreateInfo->nScatterWidth;					// 飛散幅（0～314）
	m_EffectInfo.fEmitRadius = pCreateInfo->fEmitRadius;						// 半径の大きさ

	m_EffectInfo.nSpeedMax = pCreateInfo->nSpeedMax;							// 最大速度
	m_EffectInfo.nSpeedMin = pCreateInfo->nSpeedMin;							// 最小速度
	m_EffectInfo.nAuxiliaryAxisSpeedMax = pCreateInfo->nAuxiliaryAxisSpeedMax;	// 最大補助軸（2D→3Dで、立体感を出すためのもの）
	m_EffectInfo.nAuxiliaryAxisSpeedMin = pCreateInfo->nAuxiliaryAxisSpeedMin;	// 最小補助軸（2D→3Dで、立体感を出すためのもの）

	m_EffectInfo.fAcceleration = pCreateInfo->fAcceleration;					// 加速度(1.0最大)
	m_EffectInfo.fGravity = pCreateInfo->fGravity;								// 重力
	m_EffectInfo.fGravityLimit = pCreateInfo->fGravityLimit;					// 重力制限

	m_EffectInfo.nLayRot = pCreateInfo->nLayRot;								// ポリゴンそのものを横にするかどうか（trueならビルボード解除）
	m_EffectInfo.bRotEqualMoveAngle = pCreateInfo->bRotEqualMoveAngle;			// 回転を移動の向きに合わせるか
	m_EffectInfo.nRotSpeedMax = pCreateInfo->nRotSpeedMax;						// 最大回転速度
	m_EffectInfo.nRotSpeedMin = pCreateInfo->nRotSpeedMin;						// 最小回転速度
																					
	m_EffectInfo.col = pCreateInfo->col;										// 色

	m_EffectInfo.colChangeRate = pCreateInfo->colChangeRate;					// 色変化割合
	m_EffectInfo.fFadeOutRate = pCreateInfo->fFadeOutRate;						// フェードアウトの割合
	m_EffectInfo.nCntFadeOutLock = pCreateInfo->nCntFadeOutLock;				// α値の変化をロックするカウンタ

	m_EffectInfo.nSizeMax = pCreateInfo->nSizeMax;									// 最大大きさ
	m_EffectInfo.nSizeMin = pCreateInfo->nSizeMin;									// 最小大きさ
	m_EffectInfo.fSizeChangeRate = pCreateInfo->sizeChangeRate;						// 拡大/縮小割合
	m_EffectInfo.nCntSizeChangeLock = pCreateInfo->nCntSizeChangeLock;				// 大きさをロックするカウンタ
	m_EffectInfo.bSizeChangeStartOrFinish = pCreateInfo->bSizeChangeStartOrFinish;	// 大きさを変えるのが始まりか、終わりか

	m_EffectInfo.bUseAdditiveSynthesis = pCreateInfo->bUseAdditiveSynthesis;	// 加算合成するかどうか
	m_EffectInfo.bUseZBuffer = pCreateInfo->bUseZBuffer;						// Zバッファを使うか
	m_EffectInfo.nAlphaTestBorder = pCreateInfo->nAlphaTestBorder;				// αテストのボーダー
}

//===============================================
// エフェクト情報取得処理
//===============================================
CEffectTool::EffectInfo * CEffectTool::GetEffectInfo(int nEffectType)
{
	return &m_EffectInfo;
}
