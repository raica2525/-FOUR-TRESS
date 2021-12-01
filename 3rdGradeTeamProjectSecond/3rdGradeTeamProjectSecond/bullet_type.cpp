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
void CBullet::SetupInfoByType(float fStrength, const D3DXVECTOR3 pos)
{
    // 影を生成するかどうか
    bool bUseShadow = true;

    switch (m_type)
    {
    case TYPE_ARMY_ATTACK:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(100.0f, 100.0f);
        m_fSpeed = 20.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_PLAYER);
        m_nLife = 120;
        m_fDamage = 500.0f;
        m_bUseDraw = true;  // 仮
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_RAILGUN_LV2:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(500.0f, 500.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 180;
        m_fDamage = 5000.0f;
        m_bUseDraw = true;  // 仮
        m_bHitErase = false;// 貫通
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    case TYPE_RAILGUN_LV3:
        // 固有の情報
        m_collisionSize = D3DXVECTOR2(1000.0f, 1000.0f);
        m_fSpeed = 15.0f;
        BITON(m_collisionFlag, COLLISION_FLAG_ENEMY);
        m_nLife = 300;
        m_fDamage = 10000.0f;
        m_bUseDraw = true;  // 仮
        m_bHitErase = false;// 貫通
        // モデルをバインド
        BindModelData(32);  // 仮にボール
        break;
    }

    // 強さを反映
    //m_fSpeed *= fStrength;    // 移動速度も速くなるのは違和感？
    m_fDamage *= fStrength;

    // 影生成
    if (bUseShadow)
    {
        m_pEffect3d_Shadow = CEffect3D::Create(CEffectData::TYPE_SHADOW, D3DXVECTOR3(pos.x, SHADOW_POS_Y, pos.z));
        m_pEffect3d_Shadow->SetSize(D3DXVECTOR3(m_collisionSize.x, m_collisionSize.x, 0.0f));
        m_pEffect3d_Shadow->SetDisp(false); // バレット側で描画を管理するため
    }
}