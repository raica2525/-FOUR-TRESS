//===============================================
//
// キャラクター処理 (character.cpp)
// Author : 後藤慎之助
//
//===============================================
#define _CRT_SECURE_NO_WARNINGS

//========================
// インクルードファイル
//========================
#include "character.h"
#include "animation.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "animation.h"
#include "scene3d.h"
#include "library.h"
#include "game.h"
#include "player.h"
#include "modelData.h"
#include "camera.h"
#include "effect3d.h"
#include "ui.h"
#include "wave.h"
#include "number_array.h"
#include "block.h"

//========================================
// マクロ定義
//========================================
#define PULL_TO_CENTER_VALUE 0.1f
#define PULL_TO_CENTER_VALUE_LIMIT 25.0f

//========================================
// 静的メンバ変数宣言
//========================================

//=============================================================================
// オーバーライドされたコンストラクタ
// Author : 後藤慎之助
//=============================================================================
CCharacter::CCharacter(OBJTYPE objtype) :CScene(objtype)
{
    m_posOld = DEFAULT_VECTOR;

    m_pos = DEFAULT_VECTOR;
    m_rot = DEFAULT_VECTOR;
    m_nPartsNum = 0;
    memset(m_apModel, 0, sizeof(m_apModel));
    memset(m_aPosDefault, 0, sizeof(m_aPosDefault));
    memset(m_anIndexParent, 0, sizeof(m_anIndexParent));
    memset(m_aPartsType, 0, sizeof(m_aPartsType));

    m_pAnimation = NULL;
    m_cAnimFilePass = NULL;

    m_bUseAnimation = true;
    m_rotDest = DEFAULT_VECTOR;
    m_pEffect3d_Shadow = NULL;
    m_collisionSizeDefence = D3DXVECTOR2(0.0f, 0.0f);

    m_fLife = 0.0f;
    m_fLife_red = 0.0f;
    m_fMaxLife = 0.0f;
    m_nCntStopRedLifeTime = 0;
    m_pUI_HP = NULL;
    m_pUI_HP_red = NULL;
    m_pUI_HP_bg = NULL;
    m_HPDisp = HP_DISP_NONE;

    m_move = DEFAULT_VECTOR;
    m_moveOld = DEFAULT_VECTOR;
    m_bUseControllerEffectByTakeDamage = false;
    m_fTurnSpeed = DEFAULT_TURN_SPEED;

    m_bResetAttackByDamage = false;
    m_bDisp = true;
    m_nIdx = 0;

    m_bIsInvincible = false;
    m_nCntTakeDamageTime = 0;
    m_damageState = DAMAGE_STATE_NONE;
    m_bUseWhiteDraw = false;
    m_nCntWhiteDrawTime = 0;
    m_bTakeKnockBack = true;
    m_bTakeWind = false;
    m_lastHit = OBJTYPE_NONE;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CCharacter::~CCharacter()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 位置を結びつける
    m_pos = pos;
    m_posOld = pos;

    // モデルをパーツ分メモリ確保し、初期化
    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        // 生成していないなら生成
        if (!m_apModel[nCount])
        {
            m_apModel[nCount] = new CModel;
            m_apModel[nCount]->Init(DEFAULT_VECTOR, DEFAULT_VECTOR);
            m_apModel[nCount]->SetScale(size);
            m_apModel[nCount]->SetPos(m_aPosDefault[nCount]);
        }

        // カスタマイズ用で、生成していても読み込む
        m_apModel[nCount]->BindModelData(m_aPartsType[nCount]);

        // アニメーションを生成してあるなら
        if (m_pAnimation)
        {
            m_pAnimation->SetAnimPosReset(nCount);
        }
    }

    // アニメーションのロード（使うかつ、生成していないなら）
    if (m_bUseAnimation)
    {
        if (!m_pAnimation)
        {
            m_pAnimation = CAnimation::Create(this, m_nPartsNum, m_cAnimFilePass);
        }
    }

    // ゲームなら影、HP表示を生成
    if (CManager::GetMode() == CManager::MODE_GAME)
    {
        if (!m_pEffect3d_Shadow)
        {
            m_pEffect3d_Shadow = CEffect3D::Create(CEffectData::TYPE_SHADOW, D3DXVECTOR3(pos.x, SHADOW_POS_Y, pos.z));
            m_pEffect3d_Shadow->SetSize(D3DXVECTOR3(m_collisionSizeDefence.x, m_collisionSizeDefence.x, 0.0f));
            m_pEffect3d_Shadow->SetDisp(false); // キャラクター側で描画を管理するため
        }

        if (!m_pUI_HP && !m_pUI_HP_red)
        {
            CreateHPGauge();
        }
    }

    // キャラクターのインデックスを取得
    m_nIdx = CGame::GetCharacterIdx();

    return S_OK;
}

//=============================================================================
// HP表示生成処理
// Author : 後藤慎之助
//=============================================================================
void CCharacter::CreateHPGauge(void)
{
    switch (m_HPDisp)
    {
    case HP_DISP_PLAYER_1:
    case HP_DISP_PLAYER_2:
    case HP_DISP_PLAYER_3:
    case HP_DISP_PLAYER_4:
    {
        const float UI_SIZE_X = 294.0f; // ここの値を、UIの大体の横幅に合わせる
        const float UI_FRAME_SIZE_X = 220.0f;
        const float UI_FRAME_SIZE_Y = 28.0f;
        const float UI_BAR_SIZE_X = 204.0f;
        const float UI_BAR_SIZE_Y = 20.0f;
        const float SPACE_SIZE = (SCREEN_WIDTH - (UI_SIZE_X * CGame::GetNumAllPlayer())) / (CGame::GetNumAllPlayer() + 1);
        const float FIRST_UI_POS_X = SPACE_SIZE + (UI_SIZE_X / 2.0f);
        const float NEXT_UI_POS_X = UI_SIZE_X + SPACE_SIZE;
        float fDigitPosX = FIRST_UI_POS_X + (NEXT_UI_POS_X * (float)m_HPDisp);
        m_pUI_HP_bg = CUI::Create(17, D3DXVECTOR3(fDigitPosX + 50.0f, 80.0f, 0.0f), D3DXVECTOR3(UI_FRAME_SIZE_X, UI_FRAME_SIZE_Y, 0.0f), 0, DEFAULT_COLOR);
        m_pUI_HP_red = CUI::Create(88, D3DXVECTOR3(fDigitPosX + 50.0f, 80.0f, 0.0f), D3DXVECTOR3(UI_BAR_SIZE_X, UI_BAR_SIZE_Y, 0.0f), 0, DEFAULT_COLOR);
        m_pUI_HP_red->SetActionInfo(0, CUI::ACTION_GAUGE, false);
        m_pUI_HP = CUI::Create(18, D3DXVECTOR3(fDigitPosX + 50.0f, 80.0f, 0.0f), D3DXVECTOR3(UI_BAR_SIZE_X, UI_BAR_SIZE_Y, 0.0f), 0, DEFAULT_COLOR);
        m_pUI_HP->SetActionInfo(0, CUI::ACTION_GAUGE, false);
    }
    break;
    case HP_DISP_FOLLOW:
    {
        const D3DXVECTOR3 firstPos = D3DXVECTOR3(-1000.0f, 0.0f, 0.0f);
        const D3DXVECTOR3 bgSize = D3DXVECTOR3(110.0f, 14.0f, 0.0f);
        const D3DXVECTOR3 barSize = D3DXVECTOR3(102.0f, 10.0f, 0.0f);
        m_pUI_HP_bg = CUI::Create(17, firstPos, bgSize, 0, DEFAULT_COLOR);
        m_pUI_HP_bg->SetDisp(false);
        m_pUI_HP_red = CUI::Create(88, firstPos, barSize, 0, DEFAULT_COLOR);
        m_pUI_HP_red->SetActionInfo(0, CUI::ACTION_GAUGE, false);
        m_pUI_HP_red->SetDisp(false);
        m_pUI_HP = CUI::Create(18, firstPos, barSize, 0, DEFAULT_COLOR);
        m_pUI_HP->SetActionInfo(0, CUI::ACTION_GAUGE, false);
        m_pUI_HP->SetDisp(false);
    }
    break;
    }
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CCharacter::Uninit(void)
{
    // 影を消す
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetDontUse();
    }

    // HP表示を消す
    if (m_pUI_HP)
    {
        m_pUI_HP->SetDontUse();
    }
    if (m_pUI_HP_bg)
    {
        m_pUI_HP_bg->SetDontUse();
    }
    if (m_pUI_HP_red)
    {
        m_pUI_HP_red->SetDontUse();
    }

    // モデルをパーツ分、終了し、メモリ開放
    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        // 中身があるなら
        if (m_apModel[nCount] != NULL)
        {
            // 終了処理
            m_apModel[nCount]->Uninit();

            // メモリ開放
            delete m_apModel[nCount];
            m_apModel[nCount] = NULL;
        }
    }

    // アニメーション情報を終了し、メモリ開放
    if (m_pAnimation != NULL)
    {
        // 終了処理
        m_pAnimation->Uninit();

        // メモリ開放
        delete m_pAnimation;
        m_pAnimation = NULL;
    }

    Release();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CCharacter::Update(void)
{
    // HP表示を更新
    if (m_pUI_HP && m_pUI_HP_red)
    {
        // 赤ゲージのカウントダウン
        if (m_nCntStopRedLifeTime > 0)
        {
            m_nCntStopRedLifeTime--;
        }

        // HPゲージ、赤ゲージを更新
        m_pUI_HP->SetLeftToRightGauge(m_fMaxLife, m_fLife);
        if (m_fLife_red > m_fLife && m_nCntStopRedLifeTime <= 0)
        {
            // 赤ゲージ停止時間が終わってから、更新する
            const float LIFE_DOWN_SPD = 6.0f;
            m_fLife_red -= LIFE_DOWN_SPD;
        }

        // 赤ゲージは、現在の体力を下回らない
        if (m_fLife_red < m_fLife)
        {
            m_fLife_red = m_fLife;
        }
        m_pUI_HP_red->SetLeftToRightGauge(m_fMaxLife, m_fLife_red);

        // 追従するなら
        if (m_HPDisp == HP_DISP_FOLLOW)
        {
            m_pUI_HP_bg->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, m_collisionSizeDefence.y, 0.0f));
            m_pUI_HP_red->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, m_collisionSizeDefence.y, 0.0f));
            m_pUI_HP->SetPosTo2D(GetPos() + D3DXVECTOR3(0.0f, m_collisionSizeDefence.y, 0.0f));
        }
    }

    // 影の位置を更新
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->SetPos(D3DXVECTOR3(m_pos.x, SHADOW_POS_Y, m_pos.z));
    }

    // アニメーションを使うフラグがtrueならアニメーションさせる
    if (m_bUseAnimation)
    {
        if (m_pAnimation)
        {
            m_pAnimation->Update();
        }
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CCharacter::Draw(void)
{
    // 影
    if (m_pEffect3d_Shadow)
    {
        m_pEffect3d_Shadow->CBillboard::Draw();
    }

    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        if (nCount == 0)
        {
            // 全ての親は、キャラクターの位置そのものを渡す
            m_apModel[nCount]->Draw(m_pos, m_rot, m_bUseWhiteDraw);
        }
        else
        {
            m_apModel[nCount]->Draw(m_apModel[m_anIndexParent[nCount]], m_bUseWhiteDraw);
        }
    }
}

//=============================================================================
// やられた時の描画
// Author : 後藤慎之助
//=============================================================================
void CCharacter::DeathDraw(void)
{
    // 決着の一撃中以外なら
    if (CManager::GetCamera()->CCamera::GetState() != CCamera::STATE_FINISH_EACH)
    {
        // Zバッファを無効化
        LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
        pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    }

    // 各パーツを、白くするためのtrue
    for (int nCount = 0; nCount < m_nPartsNum; nCount++)
    {
        if (nCount == 0)
        {
            m_apModel[nCount]->Draw(m_pos, m_rot, true);
        }
        else
        {
            m_apModel[nCount]->Draw(m_apModel[m_anIndexParent[nCount]], true);
        }
    }

    // 決着の一撃中以外なら
    if (CManager::GetCamera()->CCamera::GetState() != CCamera::STATE_FINISH_EACH)
    {
        // Zバッファを有効化
        LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
        pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    }
}

//=============================================================================
// モデルデータ（座標,親子関係）読み込み処理（テキストファイルから直接読み込む時に使う関数）
// Author : 後藤慎之助
//=============================================================================
void CCharacter::LoadModelData(char* cFilePass)
{
    // 名前を記憶
    m_cAnimFilePass = cFilePass;

    // ファイルポイント
    FILE *pFile = NULL;

    // 変数宣言
    int  nCntLoad = 0;
    char cReedText[2048];	// 文字として読み取り用
    char cHeadText[2048];	//
    char cDie[2048];
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 rot = DEFAULT_VECTOR;

    // ファイル開
    pFile = fopen(cFilePass, "r");

    // 開けた
    if (pFile != NULL)
    {
        while (strcmp(cHeadText, "CHARACTERSET") != 0)
        {
            fgets(cReedText, sizeof(cReedText), pFile);
            sscanf(cReedText, "%s", &cHeadText);
        }

        if (strcmp(cHeadText, "CHARACTERSET") == 0)
        {
            while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
            {

                fgets(cReedText, sizeof(cReedText), pFile);
                sscanf(cReedText, "%s", &cHeadText);

                if (strcmp(cHeadText, "\n") == 0)
                {
                }
                else if (strcmp(cHeadText, "PARTSSET") == 0)
                {
                    while (strcmp(cHeadText, "END_PARTSSET") != 0)
                    {

                        fgets(cReedText, sizeof(cReedText), pFile);
                        sscanf(cReedText, "%s", &cHeadText);

                        if (strcmp(cHeadText, "INDEX") == 0)
                        {
                            int nNum;
                            sscanf(cReedText, "%s %s %d", &cDie, &cDie, &nNum);
                        }

                        if (strcmp(cHeadText, "PARENT") == 0)
                        {
                            sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_anIndexParent[nCntLoad]);
                        }

                        if (strcmp(cHeadText, "POS") == 0)
                        {
                            sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);

                            m_aPosDefault[nCntLoad] = pos;
                        }

                        if (strcmp(cHeadText, "ROT") == 0)
                        {
                            sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &rot.x, &rot.y, &rot.z);
                        }
                    }
                    nCntLoad++;
                }
            }
        }
        // ファイル閉
        fclose(pFile);
    }
    else
    {
        printf("開けれませんでした\n");
    }
}

//=============================================================================
// モデルデータ（座標,親子関係）読み込み処理（モデルの初期位置データから読み込むときに使う関数）
// Author : 後藤慎之助
//=============================================================================
void CCharacter::LoadModelData(int nModelPosDefUp, int nModelPosDefDown)
{
    // モデルの初期位置データを受け取る
    CModelData *pModelData = CManager::GetModelData();

    // 上半身と下半身を分ける
    CModelData::ModelPosDef *pModelPosDefUp = pModelData->GetPosDef(nModelPosDefUp);
    CModelData::ModelPosDef *pModelPosDefDown = pModelData->GetPosDef(nModelPosDefDown);

    // 上半身
    for (int nCnt = 0; nCnt < MAX_MODEL_PARTS_SET; nCnt++)
    {
        m_anIndexParent[pModelPosDefUp->nIndex[nCnt]] = pModelPosDefUp->nParent[nCnt];
        m_aPosDefault[pModelPosDefUp->nIndex[nCnt]] = pModelPosDefUp->pos[nCnt];
    }

    // 下半身
    for (int nCnt = 0; nCnt < MAX_MODEL_PARTS_SET; nCnt++)
    {
        m_anIndexParent[pModelPosDefDown->nIndex[nCnt]] = pModelPosDefDown->nParent[nCnt];
        m_aPosDefault[pModelPosDefDown->nIndex[nCnt]] = pModelPosDefDown->pos[nCnt];
    }
}

//=============================================================================
// 向き調整処理
// Author : 後藤慎之助
//=============================================================================
void CCharacter::RotControl(void)
{
    // 回転の制限
    if (m_rot.y > D3DX_PI)
    {
        m_rot.y -= D3DX_PI * 2.0f;
    }
    else if (m_rot.y < -D3DX_PI)
    {
        m_rot.y += D3DX_PI * 2.0f;
    }

    // 目的の角度の回転を制限
    float fRotMin = m_rotDest.y - m_rot.y;
    if (fRotMin > D3DX_PI)
    {
        m_rotDest.y -= D3DX_PI * 2.0f;
    }
    else if (fRotMin < -D3DX_PI)
    {
        m_rotDest.y += D3DX_PI * 2.0f;
    }

    // 目的の値に近づける
    if (fabsf(fRotMin) >= 0.0f)
    {
        m_rot.y += (m_rotDest.y - m_rot.y) * m_fTurnSpeed;
    }
}

//=============================================================================
// ダメージを受ける処理
// Author : 後藤慎之助
//=============================================================================
bool CCharacter::TakeDamage(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, OBJTYPE lastHit, bool bUseKnockBack, int effectType)
{
    // 無敵でないなら
    if (!m_bIsInvincible)
    {
        // 体力が残っているなら、最後に攻撃してきた人を更新
        if (m_fLife > 0.0f)
        {
            m_lastHit = lastHit;
        }

        // HPを表示
        SetUIHPDisp(true);

        // 赤ゲージ硬直時間を設定
        if (m_nCntStopRedLifeTime <= 0)
        {
            const int STOP_RED_TIME = 60;
            m_nCntStopRedLifeTime = STOP_RED_TIME;
        }

        // 白描画時間を設定
        const int WHITE_DRAW_TIME = 8;
        m_nCntWhiteDrawTime = WHITE_DRAW_TIME;

        // 変数宣言
        D3DXVECTOR3 myPos = GetPos();                   // 位置を取得
        float fKnockbackValue = 0.0f;                   // ノックバック量
        DAMAGE_STATE damageState = DAMAGE_STATE_NONE;   // ダメージ状態
        int nCntTakeDamageTime = 0;                     // ダメージを受けた時のカウンタ

        // 負傷状態を、受けるダメージから判定
        int nEffectFrame = PLAYER_TAKE_DAMAGE_SMALL_EFFECT_FRAME;   // 振動フレーム
        if (fDamage < TAKE_DAMAGE_BORDER_DAMAGE)
        {
            // 小やられ
            damageState = DAMAGE_STATE_SMALL;
            fKnockbackValue = KNOCK_BACK_SMALL;
            nCntTakeDamageTime = TAKE_DAMAGE_SMALL_FRAME;
        }
        else
        {
            // 吹っ飛ばされ状態は、移動量がなくなって地面につくまで続く
            damageState = DAMAGE_STATE_BLOWN;
            fKnockbackValue = KNOCK_BACK_BIG;

            // 大きい振動
            nEffectFrame = PLAYER_TAKE_DAMAGE_BIG_EFFECT_FRAME;
        }

        // ダメージを受ける
        m_fLife -= fDamage;

        // ダメージ表記とエフェクトを表示
        if (fDamage > 0.0f)
        {
            D3DXVECTOR3 dispDamagePos = ConvertScreenPos(myPos);
            CNumberArray::Create(12, dispDamagePos, NUMBER_SIZE_X_DAMAGE, D3DXCOLOR(0.933f, 0.427f, 0.513f, 1.0f), (int)fDamage, false, true);

            // もしダメージの位置と、1F前のダメージの位置が同じなら、ダメージの位置をキャラクターの位置にする
            D3DXVECTOR3 hitEffectPos = damagePos;
            if (damagePos == damageOldPos)
            {
                D3DXVECTOR2 collisionSizeDefence = GetCollisionSizeDefence();
                hitEffectPos = myPos + D3DXVECTOR3(0.0f, collisionSizeDefence.y * 0.5f, 0.0f);
            }
            CEffect3D::Emit(effectType, hitEffectPos, damageOldPos);
        }

        // 体力がなくなったら
        if (m_fLife <= 0.0f)
        {
            // 死亡時の振動
            nEffectFrame = PLAYER_TAKE_DAMAGE_DEATH_EFFECT_FRAME;

            // 死亡表示に
            m_fLife = 0.0f;

            // 死亡用ノックバック
            fKnockbackValue = KNOCK_BACK_DEATH;

            // 表示を切る
            m_bDisp = false;
        }
        else
        {
            // 生存しているなら、ダメージ音（ヒット音を、ヒットエフェクトのように分けるのもあり）
            CManager::SoundPlay(CSound::LABEL_SE_DAMAGE);
        }

        // ノックバックがある攻撃かつ、ノックバックを利用する状態なら
        if (bUseKnockBack && m_bTakeKnockBack)
        {
            // ダメージ状態を更新
            m_damageState = damageState;
            m_nCntTakeDamageTime = nCntTakeDamageTime;

            // 攻撃状態をリセット
            m_bResetAttackByDamage = true;

            // 攻撃の方を向き、ノックバックさせる
            float fAngleToDamagePos = GetAngleToTargetXZ(damageOldPos, myPos);
            SetRot(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            SetRotDest(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            m_move.x = sinf(fAngleToDamagePos) * fKnockbackValue;
            m_move.z = cosf(fAngleToDamagePos) * fKnockbackValue;
        }

        // コントローラの振動
        if (m_bUseControllerEffectByTakeDamage)
        {
            CManager::GetInputJoypad()->StartEffect(m_HPDisp, nEffectFrame);
        }
    }

    // ダメージが入ったかどうか
    bool bHit = !m_bIsInvincible;
    return bHit;
}

//=============================================================================
// 中心に引き寄せる処理
// Author : 後藤慎之助
//=============================================================================
bool CCharacter::PullToCenter(D3DXVECTOR3 centerPos)
{
    // 無敵でないなら
    if (!m_bIsInvincible)
    {
        // ノックバックを利用する状態なら
        if (m_bTakeKnockBack)
        {
            // 風を受けたフラグをtrueに
            m_bTakeWind = true;

            // 変数宣言
            D3DXVECTOR3 myPos = GetPos();           // 位置を取得
            float fKnockbackValue = 0.0f;           // ノックバック量

            // 距離に応じてノックバック量を変える
            float fDistance = sqrtf(
                powf((centerPos.x - myPos.x), 2.0f) +
                powf((centerPos.z - myPos.z), 2.0f));
            fKnockbackValue = fDistance * PULL_TO_CENTER_VALUE;

            // ノックバック量制限
            if (fDistance > PULL_TO_CENTER_VALUE_LIMIT)
            {
                fDistance = PULL_TO_CENTER_VALUE_LIMIT;
            }

            // 攻撃状態をリセット
            m_bResetAttackByDamage = true;

            // 攻撃の方は向かず、ノックバックさせる
            float fAngleToDamagePos = GetAngleToTargetXZ(myPos, centerPos);
            //SetRot(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            //SetRotDest(D3DXVECTOR3(0.0f, fAngleToDamagePos, 0.0f));
            m_move.x = sinf(fAngleToDamagePos) * fKnockbackValue;
            m_move.z = cosf(fAngleToDamagePos) * fKnockbackValue;
        }
    }

    // 引き寄せられたかどうか
    bool bHit = !m_bIsInvincible;
    return bHit;
}

//=============================================================================
// 回復処理
// Author : 後藤慎之助
//=============================================================================
bool CCharacter::Healing(float fHealValue)
{
    // 表示されていないなら、関数を抜ける
    if (!m_bDisp)
    {
        return false;
    }

    // すでに最大値なら、回復失敗
    if (m_fLife >= m_fMaxLife)
    {
        return false;
    }

    // 最大値より超えないように回復
    m_fLife += fHealValue;
    if (m_fLife > m_fMaxLife)
    {
        m_fLife = m_fMaxLife;
    }

    // 自身の位置から回復エフェクトを発生

    // 回復成功
    return true;
}

//=============================================================================
// ダメージを受けている時間を数える処理（前作の名残でプレイヤーでしか使ってない処理有り）
// Author : 後藤慎之助
//=============================================================================
void CCharacter::CntDownTakeDamageTime(void)
{
    // 負傷状態管理
    if (m_nCntTakeDamageTime > 0)
    {
        m_nCntTakeDamageTime--;

        // 負傷終了時に状態を戻す
        if (m_nCntTakeDamageTime == 0)
        {
            m_bTakeWind = false;

            // ダウンからの起き上がり以外は、ダメージ状態を解除
            if (m_damageState != DAMAGE_STATE_BIG)
            {
                m_damageState = DAMAGE_STATE_NONE;
            }
            else
            {
                m_damageState = DAMAGE_STATE_STAND_UP;
                m_nCntTakeDamageTime = PLAYER_TAKE_DAMAGE_STAND_UP_FRAME;
            }
        }
    }

    // 白描画時間の管理
    if (m_nCntWhiteDrawTime > 0)
    {
        m_nCntWhiteDrawTime--;
        m_bUseWhiteDraw = true;
    }
    else
    {
        m_bUseWhiteDraw = false;
    }
}

//=============================================================================
// 移動量の制御処理
// Author : 後藤慎之助
//=============================================================================
void CCharacter::ControlMove(float& fMove, bool bGround)
{
    if (fMove != 0.0f)
    {
        // 制御の割合を、状況によって変える
        float fControlMoveRate = PLAYER_CONTROL_MOVE_ON_GROUND;

        // 負傷していないなら
        if (GetDamageState() == DAMAGE_STATE_NONE)
        {
            // 空中なら
            if (!bGround)
            {
                fControlMoveRate = PLAYER_CONTROL_MOVE_IN_AIR;
            }
        }
        else
        {
            // 風を受けているなら、地上と同じ
            if (m_bTakeWind)
            {
                fControlMoveRate = PLAYER_CONTROL_MOVE_ON_GROUND;
            }
            else
            {
                fControlMoveRate = PLAYER_CONTROL_MOVE_TAKE_DAMAGE;
            }
        }

        // 移動量制御
        fMove *= fControlMoveRate;
    }
}