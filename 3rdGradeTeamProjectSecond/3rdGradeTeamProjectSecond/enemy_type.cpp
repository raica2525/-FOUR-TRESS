//======================================================================================
//
// エネミーの種類派生処理 (enemy_type.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "animation.h"
#include "game.h"
#include "sound.h"
#include "modelData.h"
#include "effect3d.h"
#include "modelEffect.h"

//=============================================================================
// 種類ごとの初期設定
// Author : 後藤慎之助
//=============================================================================
void CEnemy::SetupInfoByType(void)
{
    switch (m_type)
    {
    case TYPE_SPIDER:
        // 固有の情報
        m_collisionSizeDeffence = D3DXVECTOR2(500.0f, 100.0f);
        m_fSpeed = 5.0f;
        m_fLife = 100.0f;
        // パーツ数を設定、モデルをバインド、アニメーションをバインド
        CCharacter::SetPartNum(SPIDER_PARTS_MAX);
        CCharacter::BindParts(SPIDER_PARTS_BODY, 18);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH, 19);
        CCharacter::BindParts(SPIDER_PARTS_FANG_LEFT, 20);
        CCharacter::BindParts(SPIDER_PARTS_FANG_RIGHT, 21);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_0, 22);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_1, 23);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_2, 24);
        CCharacter::BindParts(SPIDER_PARTS_LEG_RIGHT_3, 25);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_0, 26);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_1, 27);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_2, 28);
        CCharacter::BindParts(SPIDER_PARTS_LEG_LEFT_3, 29);
        CCharacter::BindParts(SPIDER_PARTS_STOMACH_CUBE, 30);
        CCharacter::LoadModelData("./data/ANIMATION/motion_spider.txt");
        break;
    }

    // 強さを反映
    m_fSpeed *= m_fStrength;
    m_fLife *= m_fStrength;
}