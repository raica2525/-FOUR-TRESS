//==============================================================================================================================
//
// カメラ処理 (camera.cpp)
// Author : 後藤慎之助
//
//==============================================================================================================================

//========================
// インクルードファイル
//========================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "character.h"
#include "player.h"
#include "text.h"
#include "fortress.h"

//========================
// 静的メンバ変数宣言
//========================

//================================================
// マクロ定義
//================================================

// カメラの基本情報
#define CAMERA_LOCK_ON_THETA D3DXToRadian(160.0f)    // 0度が真上
#define CAMERA_LOCK_ON_OFFSET -8750.0f               // 注視点との距離

// メニュー画面でのカメラ
#define CAMERA_POS_IN_MENU  D3DXVECTOR3(0.0f, 400.0f, -1000.0f)
#define CAMERA_DISTANCE_IN_MENU -750.0f
#define CAMERA_THETA_IN_MENU 1.4f

// 決着時のカメラの位置微調整
#define CAMERA_FINISH_NEXT_PLAYER_FRAME 90
#define CAMERA_FINISH_ROT_SPEED D3DXToRadian(3.0f)

// カメラの移動速度
#define CAMERA_MOVE_RATE 0.1f

// 視野
#define CAMERA_VIEW_RANGE 25000.0f

// 視野角
#define CAMERA_VIEW_ANGLE D3DXToRadian(45.0f)

// 目標位置との距離
#define DISTANCE_DEST_POS_MIN -7000.0f
#define DISTANCE_DEST_POS_MAX -13000.0f
#define DISTANCE_RATE 1.5f

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CCamera::CCamera()
{
    // ビューマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxView);

    // プロジェクションマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxProjection);

    m_posRDest = DEFAULT_VECTOR;
    m_posVDest = DEFAULT_VECTOR;
    m_pos = DEFAULT_VECTOR;
    m_posV = DEFAULT_VECTOR;
    m_posR = DEFAULT_VECTOR;
    m_fDistance = CAMERA_LOCK_ON_OFFSET;

    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_state = STATE_NONE;
    m_fPhi = 0.0f;
    m_fTheta = 1;
    m_nCntState = 0;
    m_shakePhase = SHAKE_PHASE_NONE;
    m_fShakeValue = 0.0f;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ゲーム遷移時のカメラのリセット
// Author : 後藤慎之助
//=============================================================================
void CCamera::ResetCamera(D3DXVECTOR3 pos, float fRot, SETTING setting)
{
    switch (setting)
    {
    case SETTING_GAME:
        m_posRDest = pos;
        m_pos = pos;
        m_posV = pos;
        m_posR = pos;
        m_fDistance = CAMERA_LOCK_ON_OFFSET;
        m_state = STATE_BUTTLE;   // バトル中のカメラにする
        m_fTheta = CAMERA_LOCK_ON_THETA;
        break;
    case SETTING_CUSTOM:
        m_posRDest = CAMERA_POS_IN_MENU;
        m_pos = CAMERA_POS_IN_MENU;
        m_posV = CAMERA_POS_IN_MENU;
        m_posR = CAMERA_POS_IN_MENU;
        m_fDistance = CAMERA_DISTANCE_IN_MENU;
        m_state = STATE_OUT_GAME;   // アウトゲームのカメラにする（メニュー画面想定）
        m_fTheta = CAMERA_THETA_IN_MENU;
        break;
    }

    m_posVDest = DEFAULT_VECTOR;
    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_fPhi = fRot;
    m_nCntState = 0;
    m_shakePhase = SHAKE_PHASE_NONE;

    // 位置を更新(球面座標の公式)
    m_posV.x = m_fDistance * (sin(m_fTheta) * cos(m_fPhi)) + m_pos.x;
    m_posV.y = (m_fDistance / 2.0f) * cos(m_fTheta) + m_pos.y;
    m_posV.z = m_fDistance * (sin(m_fTheta) * sin(m_fPhi)) + m_pos.z;
}

//=============================================================================
// カメラの振動処理
// Author : 後藤慎之助
//=============================================================================
void CCamera::Shake(void)
{
    // カウンタを加算
    m_nCntState++;

    // 位置を変える
    const int CHANGE_FRAME = 3;
    D3DXVECTOR3 cameraPos = m_pos;
    switch (m_shakePhase)
    {
    case SHAKE_PHASE_1:
        cameraPos.x += m_fShakeValue;
        cameraPos.y += m_fShakeValue;
        break;
    case SHAKE_PHASE_2:
        cameraPos.x += -m_fShakeValue;
        cameraPos.y += -m_fShakeValue;
        break;
    case SHAKE_PHASE_3:
        cameraPos.x += m_fShakeValue;
        cameraPos.y += -m_fShakeValue;
        break;
    case SHAKE_PHASE_4:
        cameraPos.x += -m_fShakeValue;
        cameraPos.y += m_fShakeValue;
        break;
    case SHAKE_PHASE_5:
        cameraPos.x += m_fShakeValue / 2.0f;
        cameraPos.y += m_fShakeValue / 2.0f;
        break;
    case SHAKE_PHASE_6:
        cameraPos.x -= m_fShakeValue / 2.0f;
        cameraPos.y -= m_fShakeValue / 2.0f;
        break;
    }

    // 次の振動段階へ
    if (m_nCntState >= CHANGE_FRAME)
    {
        m_nCntState = 0;
        m_shakePhase++;
        if (m_shakePhase >= SHAKE_PHASE_MAX)
        {
            m_shakePhase = SHAKE_PHASE_NONE;
        }
    }

    // 位置の目的地を更新(球面座標の公式)
    m_posVDest.x = m_fDistance * (sin(m_fTheta) * cos(m_fPhi)) + cameraPos.x;
    m_posVDest.y = (m_fDistance / 2.0f) * cos(m_fTheta) + cameraPos.y;
    m_posVDest.z = m_fDistance * (sin(m_fTheta) * sin(m_fPhi)) + cameraPos.z;

    // カメラの位置と注視点を更新
    m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
    m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;
}

//=============================================================================
// カメラ振動設定
// Author : 後藤慎之助
//=============================================================================
void CCamera::SetShake(float fShakeValue, bool bResetShake)
{
    if (CGame::GetState() == CGame::STATE_BUTTLE)
    {
        m_fShakeValue = fShakeValue;
        if (m_shakePhase == SHAKE_PHASE_NONE)
        {
            m_nCntState = 0;
            m_shakePhase = SHAKE_PHASE_1;
        }
        else
        {
            if (bResetShake)
            {
                m_nCntState = 0;
                m_shakePhase = SHAKE_PHASE_1;
            }
        }
    }
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CCamera::Init(void)
{
    // デバイスを取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // 仮に、メニュー画面に合わせている
    m_posRDest = DEFAULT_VECTOR;
    m_posVDest = DEFAULT_VECTOR;
    m_pos = CAMERA_POS_IN_MENU;
    m_posV = CAMERA_POS_IN_MENU;
    m_posR = CAMERA_POS_IN_MENU;
    m_pos = DEFAULT_VECTOR;
    m_posV = DEFAULT_VECTOR;
    m_posR = DEFAULT_VECTOR;
    m_fDistance = CAMERA_LOCK_ON_OFFSET;

    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_state = STATE_NONE;
    m_fPhi = 0.0f;
    m_fTheta = 1.0f;
    m_nCntState = 0;
    m_shakePhase = SHAKE_PHASE_NONE;

    // ビューマトリックスの作成
    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

    // プロジェクションマトリックスの作成
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, CAMERA_VIEW_ANGLE, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CCamera::Update(void)
{
    //  カメラ位置修正処理
    bool bResetCamera = false;
    switch (m_state)
    {
    case STATE_OUT_GAME:

        // カメラと自身の距離
        m_fDistance = CAMERA_LOCK_ON_OFFSET;

        // 位置の目的地を更新(球面座標の公式)
        m_posVDest.x = m_fDistance * (sin(m_fTheta) * cos(m_fPhi)) + m_pos.x;
        m_posVDest.y = (m_fDistance / 2.0f) * cos(m_fTheta) + m_pos.y;
        m_posVDest.z = m_fDistance * (sin(m_fTheta) * sin(m_fPhi)) + m_pos.z;

        // カメラの位置と注視点を更新
        m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
        m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;

        break;

    case STATE_BUTTLE:
    {
        // 各プレイヤーの平均位置にロックオンする
        D3DXVECTOR3 lockOnPos = DEFAULT_VECTOR;
        int nCntDispPlayer = 0;
        float fDistance = 0.0f;
        CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_PLAYER);
        for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_PLAYER); nCntScene++)
        {
            // 中身があるなら
            if (pScene)
            {
                // 次のシーンを記憶
                CScene*pNextScene = pScene->GetNextScene();
                // プレイヤーにキャスト
                CPlayer *pPlayer = (CPlayer*)pScene;

                // 表示しているかどうか
                if (!pPlayer->GetDisp())
                {
                    // 次のシーンにする
                    pScene = pNextScene;
                    continue;
                }

                // 人数を加算
                nCntDispPlayer++;

                // プレイヤーの位置を取得し、加算
                D3DXVECTOR3 playerPos = pPlayer->GetPos();
                lockOnPos += playerPos;

                // 距離も加算
                fDistance += sqrtf(
                    powf((m_pos.x - playerPos.x), 2.0f) +
                    powf((m_pos.z - playerPos.z), 2.0f));

                // 次のシーンにする
                pScene = pNextScene;
            }
        }

        // もし、プレイヤーが一体も表示されていないなら、移動要塞の位置を追従
        if (nCntDispPlayer <= 0)
        {
            CFortress*pFortress = NULL;
            pFortress = CGame::GetFortress();
            if (pFortress)
            {
                m_pos = pFortress->GetPos() + D3DXVECTOR3(0.0f, 225.0f, 0.0f);
                m_posRDest = m_pos;
                m_fDistance = DISTANCE_DEST_POS_MIN;
            }
        }
        else
        {
            m_pos = lockOnPos / (float)nCntDispPlayer + D3DXVECTOR3(0.0f, 225.0f, 0.0f);
            m_posRDest = m_pos;
            m_fDistance = DISTANCE_DEST_POS_MIN - (fDistance * DISTANCE_RATE / (float)nCntDispPlayer);
            if (m_fDistance < DISTANCE_DEST_POS_MAX)
            {
                m_fDistance = DISTANCE_DEST_POS_MAX;
            }
        }

        // 画面の揺れ
        if (m_shakePhase == SHAKE_PHASE_NONE)
        {
            // 位置の目的地を更新(球面座標の公式)
            m_posVDest.x = m_fDistance * (sin(m_fTheta) * cos(m_fPhi)) + m_pos.x;
            m_posVDest.y = (m_fDistance / 2.0f) * cos(m_fTheta) + m_pos.y;
            m_posVDest.z = m_fDistance * (sin(m_fTheta) * sin(m_fPhi)) + m_pos.z;

            // カメラの位置と注視点を更新
            m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
            m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;
        }
        else
        {
            Shake();
        }

        break;
    }

    case STATE_FINISH_EACH:
    {
        //// カウンタ加算
        //m_nCntState++;

        //if (m_nCntState < CAMERA_FINISH_NEXT_PLAYER_FRAME)
        //{
        //    // 最初は敗者にロックオン
        //    CPlayer *pLoser = NULL;
        //    for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
        //    {
        //        CPlayer *pPlayer = CGame::GetPlayer(nCntPlayer);
        //        if (pPlayer)
        //        {
        //            // 敗者を記憶
        //            if (pPlayer->GetIdxControlAndColor() == CGame::GetPlayerRankInThisRound(CPlayer::RANK_2))
        //            {
        //                pLoser = pPlayer;
        //            }
        //        }
        //    }

        //    // 敗者が存在するなら
        //    if (pLoser)
        //    {
        //        m_fPhi += CAMERA_FINISH_ROT_SPEED;
        //        m_pos = pLoser->GetPos() + D3DXVECTOR3(0.0f, pLoser->GetCollisionSizeDefence().y / 2.0f, 0.0f);
        //        m_posRDest = m_pos;
        //    }
        //}
        //else
        //{
        //    // 次に勝者へロックオン
        //    CPlayer *pWinner = NULL;
        //    for (int nCntPlayer = 0; nCntPlayer < CGame::GetNumAllPlayer(); nCntPlayer++)
        //    {
        //        CPlayer *pPlayer = CGame::GetPlayer(nCntPlayer);
        //        if (pPlayer)
        //        {
        //            // 勝者を記憶
        //            if (pPlayer->GetIdxControlAndColor() == CGame::GetPlayerRankInThisRound(CPlayer::RANK_1))
        //            {
        //                pWinner = pPlayer;
        //            }
        //        }
        //    }

        //    // 敗者が存在するなら
        //    if (pWinner)
        //    {
        //        m_fPhi -= CAMERA_FINISH_ROT_SPEED;
        //        m_pos = pWinner->GetPos() + D3DXVECTOR3(0.0f, pWinner->GetCollisionSizeDefence().y / 2.0f, 0.0f);
        //        m_posRDest = m_pos;
        //    }
        //}

        ////// カメラと自身の距離
        ////m_fDistance = CAMERA_LOCK_ON_OFFSET;

        //// 位置の目的地を更新(球面座標の公式)
        //m_posVDest.x = m_fDistance * (sin(m_fTheta) * cos(m_fPhi)) + m_pos.x;
        //m_posVDest.y = (m_fDistance / 2.0f) * cos(m_fTheta) + m_pos.y;
        //m_posVDest.z = m_fDistance * (sin(m_fTheta) * sin(m_fPhi)) + m_pos.z;

        //// カメラの位置と注視点を更新
        //m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
        //m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;

        break;
    }

    case STATE_SP:
    {
        // カウンタ加算し、必殺演出時間を管理
        m_nCntState++;
        if (m_nCntState >= PLAYER_SP_WHOLE_FRAME)
        {
            m_nCntState = 0;
            CGame::SetCurrentSpShot(false);
            bResetCamera = true;
        }
        else if (m_nCntState == 80)
        {
            CText *pSpName = CGame::GetSpText();
            if (pSpName)
            {
                pSpName->SetColor(TEXT_NOT_EXIST_COLOR);
            }
        }

        // 必殺技使用者にロックオン
        CPlayer *pUser = CGame::GetSpPlayer();
        if (pUser)
        {
            m_pos = pUser->GetPartsPos(CPlayer::PARTS_HEAD);
            m_posRDest = m_pos;
        }

        //// カメラと自身の距離
        //m_fDistance = CAMERA_LOCK_ON_OFFSET;

        // 位置の目的地を更新(球面座標の公式)
        m_posVDest.x = m_fDistance * (sin(m_fTheta) * cos(m_fPhi)) + m_pos.x;
        m_posVDest.y = (m_fDistance / 2.0f) * cos(m_fTheta) + m_pos.y;
        m_posVDest.z = m_fDistance * (sin(m_fTheta) * sin(m_fPhi)) + m_pos.z;

        // カメラの位置と注視点を更新
        m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
        m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;

        break;
    }

    }

    // ビューマトリックスの作成
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

    // プロジェクションマトリックスの作成
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, CAMERA_VIEW_ANGLE, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

    // リセットするフラグがあったら、カメラをリセット
    if (bResetCamera)
    {
        CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_GAME);
    }
}

//=============================================================================
// インスタンス生成処理
// Author : 後藤慎之助
//=============================================================================
CCamera * CCamera::Create(void)
{
    CCamera *pCamera = NULL;
    pCamera = new CCamera;
    pCamera->Init();
    return pCamera;
}