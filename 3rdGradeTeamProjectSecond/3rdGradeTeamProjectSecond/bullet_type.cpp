//======================================================================================
//
// 弾の種類派生処理 (bullet_type.cpp)
// Author : 後藤慎之助
//
//======================================================================================

//========================
// インクルードファイル
//========================
#include "bullet.h"
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
void CBullet::SetupInfoByType(float fStrength)
{
    switch (m_type)
    {
    case TYPE_ARMY_ATTACK:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 100.0f;
        m_bUseDraw = true;  // 仮
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    }

    // 強さを反映
    m_fSpeed *= fStrength;
    m_fDamage *= fStrength;
}