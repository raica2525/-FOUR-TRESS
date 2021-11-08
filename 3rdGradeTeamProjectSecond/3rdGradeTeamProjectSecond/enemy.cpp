//======================================================================================
//
// エネミー処理 (enemy.cpp)
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
#include "debug.h"
#include "bullet.h"

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CEnemy::CEnemy() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_SPIDER;
    m_collisionSizeDeffence = D3DXVECTOR2(0.0f, 0.0f);
    m_fSpeed = 0.0f;
    m_fStrength = 1.0f;
    m_fLife = 0.0f;

    m_nCntTime = 0;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 種類ごとの初期設定
    SetupInfoByType();

    // キャラクターに反映
    CCharacter::Init(pos, DEFAULT_SCALE);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Update(void)
{
    D3DXVECTOR3 myPos = GetPos();

    // 仮の処理
    CPlayer *pPlayer = CGame::GetPlayer(0);
    if (pPlayer)
    {
        // 道の位置
        D3DXVECTOR3 playerPos = pPlayer->GetPos();

        // 距離計算
        float fDistance = sqrtf(
            powf((myPos.x - playerPos.x), 2) +
            powf((myPos.z - playerPos.z), 2));
        const float SEARCH_DISTANCE = 1000.0f;
        if (fDistance < SEARCH_DISTANCE)
        {
            SetRotDestY(GetAngleToTargetXZ(playerPos, myPos));

            RotControl();

            m_nCntTime++;

            if (m_nCntTime >= 75)
            {
                m_nCntTime = 0;
                D3DXVECTOR3 moveAngle = D3DXVECTOR3(-sinf(GetRot().y), 0.0f, -cosf(GetRot().y));
                CBullet::Create(CBullet::TYPE_ARMY_ATTACK, GetPos(), moveAngle);
            }
        }
    }

    // アニメーションさせる
    CCharacter::Update();

#ifdef COLLISION_TEST
    D3DXVECTOR3 size = D3DXVECTOR3(m_collisionSizeDeffence.x, m_collisionSizeDeffence.y, m_collisionSizeDeffence.x);
    CDebug::Create(GetPos(), size, CDebug::TYPE_MOMENT, 118);
#endif // COLLISION_TEST
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CEnemy::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// 生成処理
// Author : 後藤慎之助
//=============================================================================
CEnemy * CEnemy::Create(int type, D3DXVECTOR3 pos, float fStrength, D3DXVECTOR3 rot)
{
    // メモリ確保
    CEnemy *pEnemy = NULL;
    pEnemy = new CEnemy;

    // 先に結びつけておく
    pEnemy->m_type = type;
    pEnemy->m_fStrength = fStrength;
    pEnemy->CCharacter::SetPos(pos);
    pEnemy->CCharacter::SetRot(rot);

    // 初期化
    pEnemy->Init(pos, DEFAULT_SCALE);

    return pEnemy;
}