//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 後藤慎之助
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "game.h"
#include "debug.h"
#include "effect2d.h"
#include "file_manager.h"

//=============================================================================
// タイトルのコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CTitle::CTitle()
{
    m_nCntTime = 0;
    m_bEmitWingEffect = true;
}

//=============================================================================
// タイトルのデストラクタ
// Author : 後藤慎之助
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CTitle::Init(void)
{
    // マウスカーソルの表示(念のため)
    ShowCursor(TRUE);

    // ファイルの読み込み
    CFile_Manager::GetInstance()->CFile_Manager::Read();

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CTitle::Uninit(void)
{

}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CTitle::Update(void)
{

}

//=============================================================================
// 画面の上か下に炎を出す処理
// Author : 後藤慎之助
//=============================================================================
void CTitle::EmitFire(FIRE_POS firePos)
{
    // 変数宣言
    const float ANGLE_ADJUST = 90.0f;   // 時計でいう0が0度の時に合わせる（2Dポリゴンの頂点をZで指定しているから）
    const float POS_Y_ADJUST = 50.0f;
    const int RAND_X = 1380;
    const float BASE_ANGLE = 67.5f;
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    float fAngle = 0.0f;
    CEffectData::TYPE effectType = CEffectData::TYPE_TITLE_FIRE_RED;

    // 位置と向きと色を決める
    switch (firePos)
    {
    case FIRE_POS_UP:
        pos.y = -POS_Y_ADJUST;
        pos.x = float(rand() % RAND_X);
        fAngle = D3DXToRadian(180.0f) + BASE_ANGLE - ANGLE_ADJUST;
        effectType = CEffectData::TYPE_TITLE_FIRE_BLUE;
        break;
    case FIRE_POS_DOWN:
        pos.y = SCREEN_HEIGHT + POS_Y_ADJUST;
        pos.x = float(rand() % RAND_X) - float(RAND_X - SCREEN_WIDTH);
        fAngle = BASE_ANGLE - ANGLE_ADJUST;
        effectType = CEffectData::TYPE_TITLE_FIRE_RED;
        break;
    }

    // 炎生成
    CEffect2D::Create(effectType, pos, fAngle);
}
