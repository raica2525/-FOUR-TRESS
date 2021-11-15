//=============================================================================
//
// UI処理 (ui.cpp)
// Author : 後藤慎之助 工藤綾乃(文字列の生成処理)
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//=======================================
// インクルードファイル
//=======================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "input.h"
#include "title.h"
#include "texture.h"
#include "effect2d.h"
#include<string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

//=======================================
// 静的メンバ変数宣言
//=======================================
CUI* CUI::m_apAccessUI[] = {};
std::vector<CUI*> CUI::m_pUI = {};  // UIの情報
bool CUI::IsPreview = false;        // プレビューモードか

//=========================================================
// UIのコンストラクタ
// Author : 後藤慎之助
//=========================================================
CUI::CUI(CScene::OBJTYPE objtype) :CScene2D(objtype)
{
    m_nTexType = 0;
    memset(m_aActionInfo, 0, sizeof(m_aActionInfo));
    memset(m_aActionInfo->afParam, 0, sizeof(m_aActionInfo->afParam));
    memset(m_aActionInfo->afMemoryParam, 0, sizeof(m_aActionInfo->afMemoryParam));
    m_bUse = true;

    m_fRotAngle = 0.0f;
    m_col = DEFAULT_COLOR;
    m_bUseAdditiveSynthesis = false;

    m_memoryPos = DEFAULT_VECTOR;                
    m_memorySize = DEFAULT_VECTOR;
    m_fMemoryRotAngle = 0.0f;          
    m_memoryCol = DEFAULT_COLOR;

    m_bOneRoundAnim = false;
    m_nAnimParagraph = 0;
    m_nAnimPattern = 0;
    m_nAnimSpeed = 0;
    m_bRepeat = false;

    m_collisionPos = DEFAULT_VECTOR;
    m_collisionSize = DEFAULT_VECTOR;
    m_nAccessNum = NOT_EXIST;
    m_bDisp = true;
}

//=========================================================
// UIのデストラクタ
// Author : 後藤慎之助
//=========================================================
CUI::~CUI()
{

}

//=========================================================
// UIの初期化処理
// Author : 後藤慎之助
//=========================================================
HRESULT CUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // 初期化
    CScene2D::Init(pos, size);

    // テクスチャを割り当て
    BindTexture(m_nTexType);

    return S_OK;
}

//=========================================================
// UIの終了処理
// Author : 後藤慎之助
//=========================================================
void CUI::Uninit(void)
{
    // アクセス権を持っているUIは、それを破棄する
    if (m_nAccessNum > NOT_EXIST && m_nAccessNum < MAX_ACCESS_NUM)
    {
        m_apAccessUI[m_nAccessNum] = NULL;
    }

    // 終了処理
    CScene2D::Uninit();
}

//=========================================================
// UIの更新処理
// Author : 後藤慎之助
//=========================================================
void CUI::Update(void)
{

        // アニメーションを使うなら
        if (m_nAnimPattern > 1)
        {
            // 一周していないならテクスチャアニメーションを更新
            if (!m_bOneRoundAnim)
            {
                // リピートするなら、一周のフラグと結びつけない
                if (m_bRepeat)
                {
                    if (m_nAnimParagraph > 2)
                    {
                        CScene2D::SetAllParagraphAnimation(m_nAnimParagraph, m_nAnimSpeed, m_nAnimPattern);
                    }
                    else
                    {
                        CScene2D::SetAnimation(m_nAnimSpeed, m_nAnimPattern);
                    }
                }
                else
                {
                    if (m_nAnimParagraph > 2)
                    {
                        m_bOneRoundAnim = CScene2D::SetAllParagraphAnimation(m_nAnimParagraph, m_nAnimSpeed, m_nAnimPattern);
                    }
                    else
                    {
                        m_bOneRoundAnim = CScene2D::SetAnimation(m_nAnimSpeed, m_nAnimPattern);
                    }
                }
            }
        }

        // アクション
        for (int nCnt = 0; nCnt < MAX_ACTION; nCnt++)
        {
            PlayAction(nCnt);
        }

    // 各頂点を更新（角度も反映）（ゲージ系は、別で頂点情報を調整済み）
    CScene2D::SetColor(m_col);
    if (m_aActionInfo[0].action != ACTION_GAUGE && m_aActionInfo[1].action != ACTION_GAUGE &&
        m_aActionInfo[2].action != ACTION_GAUGE && m_aActionInfo[3].action != ACTION_GAUGE)
    {
        CScene2D::SetRotVertex(m_fRotAngle);
    }

    if (IsPreview)
    {
        //透明、大きさがないなら使用フラグをfalseに
        D3DXVECTOR3 size = CScene2D::GetSize();
        if (m_col.a < 0.0f || size.x < 0.0f || size.y < 0.0f)
        {
            m_bUse = false;
        }
    }
    
    // 使用フラグがないなら終了処理（上記の使用フラグをfalseに以外にも、セッターからfalseにできるためこの手法）
    if (!m_bUse)
    {
        Uninit();
    }
}

//=========================================================
// UIの描画処理
// Author : 後藤慎之助
//=========================================================
void CUI::Draw(void)
{
    // 表示するなら
    if (m_bDisp)
    {
        // 加算合成
        if (m_bUseAdditiveSynthesis)
        {
            CScene2D::SetAdditiveSynthesis();
        }

        // 描画処理
        CScene2D::Draw();
    }
}

//=========================================================
// UIの作成
// Author : 後藤慎之助
//=========================================================
CUI *CUI::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRotAngle, D3DXCOLOR col,
    bool bFrontText, bool bUseAddiveSynthesis, int nAlphaTestBorder, bool bUseZBuffer,  D3DXVECTOR3 collisionPos, D3DXVECTOR3 collisionSize)
{
    // メモリの確保
    CUI *pUI = NULL;

    // タイプごとに、テキストの手前か後ろのUIかどうかを決める
    if (bFrontText)
    {
        pUI = new CUI(CScene::OBJTYPE_UI_FRONT_TEXT);
    }
    else
    {
        pUI = new CUI(CScene::OBJTYPE_UI_BACK_TEXT);
    }

    // テクスチャのタイプは先に結びつけておく
    pUI->m_nTexType = nTexType;

    // 初期化（3Dモデルの裏に行くなら、ZBufferを考慮する）
    float fZBufferValue = 0.0f;
    if (bUseZBuffer)
    {
        fZBufferValue = 1.0f;
    }
    pos.z = fZBufferValue;
    pUI->Init(pos, size);

    // 親元に設定を反映
    pUI->CScene2D::SetAlphaTestBorder(nAlphaTestBorder);

    // 引数をメンバ変数に結びつける
    if (nRotAngle != 0)
    {
        pUI->m_fRotAngle = D3DXToRadian((float)nRotAngle);
    }
    pUI->m_col = col;
    pUI->m_bUseAdditiveSynthesis = bUseAddiveSynthesis;
    pUI->m_collisionPos = collisionPos;
    pUI->m_collisionSize = collisionSize;

    // 記憶用も結びつける
    pUI->m_memoryPos = pos;
    pUI->m_memorySize = size;
    pUI->m_fMemoryRotAngle = pUI->m_fRotAngle;
    pUI->m_memoryCol = col;

    // テクスチャ情報から、アニメーションの有無等を取得
    CTexture *pTexture = CManager::GetTexture();
    pUI->m_nAnimParagraph = pTexture->GetInfo(pUI->m_nTexType)->nParagraph;
    pUI->m_nAnimPattern = pTexture->GetInfo(pUI->m_nTexType)->nPattern;
    pUI->m_nAnimSpeed = pTexture->GetInfo(pUI->m_nTexType)->nSpeed;
    pUI->m_bRepeat = pTexture->GetInfo(pUI->m_nTexType)->bRepeat;

#ifdef _DEBUG
    if (collisionSize != DEFAULT_VECTOR && CManager::GetRenderer()->GetDispFont())
    {
        CUI *pDebugCollision = Create(52, collisionPos, collisionSize, 0, DEFAULT_COLOR, true);
        pDebugCollision->SetReloadUI();
    }
#endif

    return pUI;
}

//=========================================================
// UIのアクセス権を取得
// Author : 後藤慎之助
//=========================================================
CUI * CUI::GetAccessUI(int nNum)
{
    if (nNum > NOT_EXIST && nNum < MAX_ACCESS_NUM)
    {
        return m_apAccessUI[nNum];
    }

    return NULL;
}

//=========================================================
// UIのアクセス権を設定
// Author : 後藤慎之助
//=========================================================
void CUI::SetAccessUI(int nNum)
{
    if (nNum > NOT_EXIST && nNum < MAX_ACCESS_NUM)
    {
        m_nAccessNum = nNum;
        m_apAccessUI[nNum] = this;
    }
}

//=========================================================
// UIの動き情報を設定
// Author : 後藤慎之助
//=========================================================
void CUI::SetActionInfo(int nNum, int action, bool bLock, float fParam0, float fParam1, float fParam2, float fParam3, float fParam4, float fParam5, float fParam6, float fParam7)
{
        m_aActionInfo[nNum].action = action;
        m_aActionInfo[nNum].nCntTime = 0;
        m_aActionInfo[nNum].bLock = bLock;
        m_aActionInfo[nNum].afParam[0] = fParam0;
        m_aActionInfo[nNum].afParam[1] = fParam1;
        m_aActionInfo[nNum].afParam[2] = fParam2;
        m_aActionInfo[nNum].afParam[3] = fParam3;
        m_aActionInfo[nNum].afParam[4] = fParam4;
        m_aActionInfo[nNum].afParam[5] = fParam5;
        m_aActionInfo[nNum].afParam[6] = fParam6;
        m_aActionInfo[nNum].afParam[7] = fParam7;

        // テクスチャブレンドアクションなら、ここで用いるテクスチャをバインド
        if (m_aActionInfo[nNum].action == ACTION_TEX_BREND)
        {
            // ブレンド方法
            CScene2D::BREND brend = CScene2D::BREND_NORMAL;
            switch ((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_HOW_TO])
            {
            case CScene2D::BREND_NORMAL:
                brend = CScene2D::BREND_NORMAL;
                break;
            case CScene2D::BREND_SEAL:
                brend = CScene2D::BREND_SEAL;
                break;
            case CScene2D::BREND_IGNORE_INFO:
                brend = CScene2D::BREND_APPLY_INFO;
                CScene2D::SetBrend(CScene2D::BREND_IGNORE_INFO);
                break;
            }

            // ブレンド用のテクスチャをバインド
            m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_IDX]
                = (float)BindTexture((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_TEX_NUMBER], brend);
        }
        else if (m_aActionInfo[nNum].action == ACTION_ROT)
        {
            // 回転アクションなら、値をラジアンにする
            m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE] = D3DXToRadian(m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE]);
            m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE] = D3DXToRadian(m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE]);
        }
        else if (m_aActionInfo[nNum].action == ACTION_TEX_PLACE)
        {
            // 描画するテクスチャの場所を指定
            CScene2D::SetTexturePlace((int)m_aActionInfo[nNum].afParam[PARAM_TEX_PLACE_PLACE], (int)m_aActionInfo[nNum].afParam[PARAM_TEX_PLACE_PATTERN]);
        }

        // 記憶用変数に結びつける
        m_aActionInfo[nNum].bMemoryLock = m_aActionInfo[nNum].bLock;
        for (int nCnt = 0; nCnt < MAX_ACTION_PARAM; nCnt++)
        {
            m_aActionInfo[nNum].afMemoryParam[nCnt] = m_aActionInfo[nNum].afParam[nCnt];
        }
}

//=========================================================
// UIのアクションのロック状態を設定
// Author : 後藤慎之助
//=========================================================
void CUI::SetActionLock(int nNum, bool bLock)
{
    // 範囲内なら
    if (nNum >= 0 && nNum < MAX_ACTION)
    {
        m_aActionInfo[nNum].bLock = bLock;
    }
}

//=========================================================
// UIの一部のアクション状況をリセット
// Author : 後藤慎之助
//=========================================================
void CUI::SetActionReset(int nNum)
{
        // 範囲内なら
        if (nNum >= 0 && nNum < MAX_ACTION)
        {
            // 構造体の内容をリセット
            m_aActionInfo[nNum].nCntTime = 0;
            m_aActionInfo[nNum].bLock = m_aActionInfo[nNum].bMemoryLock;
            for (int nCntParam = 0; nCntParam < MAX_ACTION_PARAM; nCntParam++)
            {
                m_aActionInfo[nNum].afParam[nCntParam] = m_aActionInfo[nNum].afMemoryParam[nCntParam];
            }

            // アクションによって、リセットするものを変える
            switch (m_aActionInfo[nNum].action)
            {
            case ACTION_SIZE:
                CScene2D::SetSize(m_memorySize);
                break;
            case ACTION_POS:
                CScene2D::SetPosition(m_memoryPos);
                break;
            case ACTION_ALPHA:
                m_col.a = m_memoryCol.a;
                break;
            case ACTION_COLOR:
                m_col = m_memoryCol;
                break;
            case ACTION_ROT:
                m_fRotAngle = m_fMemoryRotAngle;
                break;
            case ACTION_TEX_BREND:
                CScene2D::ResetCountAnim((int)m_aActionInfo[nNum].afMemoryParam[PARAM_TEX_BREND_IDX]);
                PlayActionTexBrend(nNum);   // テクスチャ座標更新
                break;
            case ACTION_LOOP_ANIM:
                CScene2D::ResetCountAnim();
                PlayActionLoopAnim(nNum);   // テクスチャ座標更新
                break;
            case ACTION_TEX_PLACE:
                CScene2D::SetTexturePlace((int)m_aActionInfo[nNum].afMemoryParam[PARAM_TEX_PLACE_PLACE], (int)m_aActionInfo[nNum].afMemoryParam[PARAM_TEX_PLACE_PATTERN]);
                break;
            }
        }

}

//=========================================================
// UIの全てのアクション状況をリセット
// Author : 後藤慎之助
//=========================================================
void CUI::SetAllActionReset(void)
{
    for (int nCnt = 0; nCnt < MAX_ACTION; nCnt++)
    {
        SetActionReset(nCnt);
    }
}

//=========================================================
// 全てのアクションを実行するもとの処理
// Author : 後藤慎之助
//=========================================================
void CUI::PlayAction(int nNum)
{
    // ロックされていないなら
    if (!m_aActionInfo[nNum].bLock)
    {
        // アクションを実行する
        switch (m_aActionInfo[nNum].action)
        {
        case ACTION_SIZE:
            PlayActionSize(nNum);
            break;
        case ACTION_POS:
            PlayActionPos(nNum);
            break;
        case ACTION_ALPHA:
            PlayActionAlpha(nNum);
            break;
        case ACTION_COLOR:
            PlayActionColor(nNum);
            break;
        case ACTION_ROT:
            PlayActionRot(nNum);
            break;
        case ACTION_TEX_BREND:
            PlayActionTexBrend(nNum);
            break;
        case ACTION_LOOP_ANIM:
            PlayActionLoopAnim(nNum);
            break;
        case ACTION_EMIT_EFFECT:
            PlayActionEmitEffect(nNum);
            break;
        }
    }
}

//=========================================================
// サイズアクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionSize(int nNum)
{
    // 大きさを取得
    D3DXVECTOR3 size = CScene2D::GetSize();

    // 制限を考慮
    bool bUpdateX = false;   // Xを更新するかどうか
    bool bUpdateY = false;   // Yを更新するかどうか
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_RIMIT])
    {
    case RIMIT_NONE:
        bUpdateX = true;
        bUpdateY = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_SIZE_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdateX = true;
            bUpdateY = true;
        }
        break;

    case RIMIT_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_SIZE_FRAME])
        {
            bUpdateX = true;
            bUpdateY = true;
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;

    case RIMIT_TO_VALUE:
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X],
            size.x, m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_X], bUpdateX);
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_Y],
            size.y, m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_Y], bUpdateY);
        break;

    case RIMIT_REPEAT_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_SIZE_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdateX = true;
            bUpdateY = true;
        }
        else
        {
            // カウンタリセットし、変化量を反転させる
            m_aActionInfo[nNum].nCntTime = 0;
            m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X] *= -1;
            m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_Y] *= -1;
        }
        break;

    case RIMIT_REPEAT_VALUE:
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X],
            m_memorySize.x, size.x, m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_X], bUpdateX);
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_Y],
            m_memorySize.y, size.y, m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_Y], bUpdateY);
        break;

    case RIMIT_EQUAL_VALUE_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_SIZE_FRAME])
        {
            // 等比変形かどうか
            if ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_EQUAL_RATIO] == 0)
            {
                size.x = m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_X];
                size.y = m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_Y];
            }
            else if ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_EQUAL_RATIO] == 1)
            {
                if (size.x != 0.0f)
                {
                    size.y = (size.y / size.x) * m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_X];
                }
                size.x = m_aActionInfo[nNum].afParam[PARAM_SIZE_VALUE_X];
            }
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // 等比変形かどうか
    if ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_EQUAL_RATIO] == 0)
    {
        // X更新
        if (bUpdateX)
        {
            size.x += m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X];
        }

        // Y更新
        if (bUpdateY)
        {
            size.y += m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_Y];
        }
    }
    else if ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_EQUAL_RATIO] == 1)
    {
        // 等比変形はx基準で加算しているため、yを先に計算しないとリピートでずれる
        if (bUpdateX)
        {
            if (size.x != 0.0f)
            {
                size.y += (size.y / size.x) * m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X];
            }
            size.x += m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X];
        }
    }

    // 大きさを設定
    CScene2D::SetSize(size);
}

//=========================================================
// 位置アクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionPos(int nNum)
{
    // 位置を取得
    D3DXVECTOR3 pos = CScene2D::GetPosition();

    // 制限を考慮
    bool bUpdateX = false;   // X更新するかどうか
    bool bUpdateY = false;   // Y更新するかどうか
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_POS_RIMIT])
    {
    case RIMIT_NONE:
        bUpdateX = true;
        bUpdateY = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_POS_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdateX = true;
            bUpdateY = true;
        }
        break;

    case RIMIT_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_POS_FRAME])
        {
            bUpdateX = true;
            bUpdateY = true;
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;

    case RIMIT_TO_VALUE:
        // X
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X],
            pos.x, m_aActionInfo[nNum].afParam[PARAM_POS_VALUE_X], bUpdateX);
        // Y
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y],
            pos.y, m_aActionInfo[nNum].afParam[PARAM_POS_VALUE_Y], bUpdateY);
        break;

    case RIMIT_REPEAT_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_POS_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdateX = true;
            bUpdateY = true;
        }
        else
        {
            // カウンタリセットし、変化量を反転させる
            m_aActionInfo[nNum].nCntTime = 0;
            m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X] *= -1;
            m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y] *= -1;
        }
        break;

    case RIMIT_REPEAT_VALUE:
        // X
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X],
            m_memoryPos.x, pos.x, m_aActionInfo[nNum].afParam[PARAM_POS_VALUE_X], bUpdateX);
        // Y
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y],
            m_memoryPos.y, pos.y, m_aActionInfo[nNum].afParam[PARAM_POS_VALUE_Y], bUpdateY);
        break;

    case RIMIT_EQUAL_VALUE_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_POS_FRAME])
        {
            pos.x = m_aActionInfo[nNum].afParam[PARAM_POS_VALUE_X];
            pos.y = m_aActionInfo[nNum].afParam[PARAM_POS_VALUE_Y];
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // X更新
    if (bUpdateX)
    {
        pos.x += m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X];
        m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X] *= m_aActionInfo[nNum].afParam[PARAM_POS_ACCEL];
    }

    // Y更新
    if (bUpdateY)
    {
        pos.y += m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y];
        m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y] *= m_aActionInfo[nNum].afParam[PARAM_POS_ACCEL];
    }

    // 位置を設定
    CScene2D::SetPosition(pos);
}

//=========================================================
// 透明度アクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionAlpha(int nNum)
{
    // 制限を考慮
    bool bUpdate = false;   // 更新するかどうか
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_RIMIT])
    {
    case RIMIT_NONE:
        bUpdate = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdate = true;
        }
        break;

    case RIMIT_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_FRAME])
        {
            bUpdate = true;
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;

    case RIMIT_TO_VALUE:
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_ALPHA_CHANGE_RATE],
            m_col.a, m_aActionInfo[nNum].afParam[PARAM_ALPHA_VALUE], bUpdate);
        break;

    case RIMIT_REPEAT_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdate = true;
        }
        else
        {
            // カウンタリセットし、変化量を反転させる
            m_aActionInfo[nNum].nCntTime = 0;
            m_aActionInfo[nNum].afParam[PARAM_ALPHA_CHANGE_RATE] *= -1;
        }
        break;

    case RIMIT_REPEAT_VALUE:
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_ALPHA_CHANGE_RATE],
            m_memoryCol.a, m_col.a, m_aActionInfo[nNum].afParam[PARAM_ALPHA_VALUE], bUpdate);
        break;

    case RIMIT_EQUAL_VALUE_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_FRAME])
        {
            m_col.a = m_aActionInfo[nNum].afParam[PARAM_ALPHA_VALUE];
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // 更新
    if (bUpdate)
    {
        m_col.a += m_aActionInfo[nNum].afParam[PARAM_ALPHA_CHANGE_RATE];
    }
}

//=========================================================
// 色変えアクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionColor(int nNum)
{
    // 制限を考慮
    bool bUpdateR = false;   // R更新するかどうか
    bool bUpdateG = false;   // G更新するかどうか
    bool bUpdateB = false;   // B更新するかどうか
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_COLOR_RIMIT])
    {
    case RIMIT_NONE:
        bUpdateR = true;
        bUpdateG = true;
        bUpdateB = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_COLOR_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdateR = true;
            bUpdateG = true;
            bUpdateB = true;
        }
        break;

    case RIMIT_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_COLOR_FRAME])
        {
            bUpdateR = true;
            bUpdateG = true;
            bUpdateB = true;
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;

    case RIMIT_TO_VALUE:
        // R
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_R],
            m_col.r, m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_R], bUpdateR);
        // G
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_G],
            m_col.g, m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_G], bUpdateG);
        // B
        RimitToValue(m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_B],
            m_col.b, m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_B], bUpdateB);
        break;

    case RIMIT_REPEAT_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_COLOR_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bUpdateR = true;
            bUpdateG = true;
            bUpdateB = true;
        }
        else
        {
            // カウンタリセットし、変化量を反転させる
            m_aActionInfo[nNum].nCntTime = 0;
            m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_R] *= -1;
            m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_G] *= -1;
            m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_B] *= -1;
        }
        break;

    case RIMIT_REPEAT_VALUE:
        // R
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_R],
            m_memoryCol.r, m_col.r, m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_R], bUpdateR);
        // G
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_G],
            m_memoryCol.g, m_col.g, m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_G], bUpdateG);
        // B
        RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_B],
            m_memoryCol.b, m_col.b, m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_B], bUpdateB);
        break;

    case RIMIT_EQUAL_VALUE_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_COLOR_FRAME])
        {
            m_col.r = m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_R];
            m_col.g = m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_G];
            m_col.b = m_aActionInfo[nNum].afParam[PARAM_COLOR_VALUE_B];
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // R更新
    if (bUpdateR)
    {
        m_col.r += m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_R];
    }

    // G更新
    if (bUpdateG)
    {
        m_col.g += m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_G];
    }

    // B更新
    if (bUpdateB)
    {
        m_col.b += m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_B];
    }
}

//=========================================================
// 回転アクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionRot(int nNum)
{
         //変数宣言
        const float ANGLE_ADJUST = D3DXToRadian(90.0f);   // 時計でいう0が0度の時に合わせる（2Dポリゴンの頂点をZで指定しているから）

        // 制限を考慮
        bool bUpdate = false;   // 更新するかどうか
        switch ((int)m_aActionInfo[nNum].afParam[PARAM_ROT_RIMIT])
        {
        case RIMIT_NONE:
            bUpdate = true;
            break;

        case RIMIT_TO_FRAME:
            if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_ROT_FRAME])
            {
                // カウンタ加算
                m_aActionInfo[nNum].nCntTime++;
                bUpdate = true;
            }
            break;

        case RIMIT_FROM_FRAME:
            if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_ROT_FRAME])
            {
                bUpdate = true;
            }
            else
            {
                // カウンタ加算
                m_aActionInfo[nNum].nCntTime++;
            }
            break;

        case RIMIT_TO_VALUE:
            RimitToValue(m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE],
                m_fRotAngle, m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE] - ANGLE_ADJUST, bUpdate);
            break;

        case RIMIT_REPEAT_FRAME:
            if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_ROT_FRAME])
            {
                // カウンタ加算
                m_aActionInfo[nNum].nCntTime++;
                bUpdate = true;
            }
            else
            {
                // カウンタリセットし、変化量を反転させる
                m_aActionInfo[nNum].nCntTime = 0;
                m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE] *= -1;
            }
            break;

        case RIMIT_REPEAT_VALUE:
            RimitRepeatValue(m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE],
                m_fMemoryRotAngle, m_fRotAngle, m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE] - ANGLE_ADJUST, bUpdate);
            break;

        case RIMIT_EQUAL_VALUE_FROM_FRAME:
            if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_ROT_FRAME])
            {
                m_fRotAngle = m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE];
            }
            else
            {
                // カウンタ加算
                m_aActionInfo[nNum].nCntTime++;
            }
            break;
        }

        // 更新
        if (bUpdate)
        {
            m_fRotAngle += m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE];
        }

        // 角度の調整
        if (m_fRotAngle > D3DXToRadian(180.0f) || m_fRotAngle < D3DXToRadian(-180.0f))
        {
            m_fRotAngle *= -1;
        }
}

//=========================================================
// テクスチャブレンドアクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionTexBrend(int nNum)
{
    //if (!IsPreview)// プレビューモードではない時はスキップ
    //    return;

    // テクスチャ情報から、アニメーションの有無等を取得
    CTexture::Info *pTextureInfo = CManager::GetTexture()->GetInfo((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_TEX_NUMBER]);
    int nPattern = pTextureInfo->nPattern;
    int nAnimSpeed = pTextureInfo->nSpeed;

    // アニメーションを使うなら
    if (nPattern > 1)
    {
        // textureの方で設定されているものを使う
        CScene2D::SetAnimation(nAnimSpeed, nPattern, (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_IDX]);
    }
    else
    {
        // インターバル時間をカウントダウン
        if (m_aActionInfo[nNum].nCntTime > 0)
        {
            m_aActionInfo[nNum].nCntTime--;
        }
        else
        {
            // 変数宣言
            bool bRightToLeft = false;
            CScene2D::DIRECT direct = CScene2D::DIRECT_VERTICAL;

            // 右から左か
            if ((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_RIGHT_TO_LEFT] == 0)
            {
                bRightToLeft = false;
            }
            else if ((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_RIGHT_TO_LEFT] == 1)
            {
                bRightToLeft = true;
            }

            // 向き
            switch ((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_DIRECT])
            {
            case CScene2D::DIRECT_VERTICAL:
                direct = CScene2D::DIRECT_VERTICAL;
                break;
            case CScene2D::DIRECT_HORIZON:
                direct = CScene2D::DIRECT_HORIZON;
                break;
            case CScene2D::DIRECT_RIGHT_UP:
                direct = CScene2D::DIRECT_RIGHT_UP;
                break;
            case CScene2D::DIRECT_RIGHT_DOWN:
                direct = CScene2D::DIRECT_RIGHT_DOWN;
                break;
            }

            // アニメーションさせる
            if (SetFlowingAnimation(1, (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_ONE_ROUND_FRAME],
                bRightToLeft, direct, (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_IDX]))
            {
                // 一周したら、インターバル
                m_aActionInfo[nNum].nCntTime = (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_INTERVAL_FRAME];
            }
        }
    }
}

//=========================================================
// ループアニメーションアクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionLoopAnim(int nNum)
{
    //if (!IsPreview)// プレビューモードではない時はスキップ
    //    return;

    // 変数宣言
    bool bRightToLeft = false;
    CScene2D::DIRECT direct = CScene2D::DIRECT_VERTICAL;

    // 右から左か
    if ((int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_RIGHT_TO_LEFT] == 0)
    {
        bRightToLeft = false;
    }
    else if ((int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_RIGHT_TO_LEFT] == 1)
    {
        bRightToLeft = true;
    }

    // 向き
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_DIRECT])
    {
    case CScene2D::DIRECT_VERTICAL:
        direct = CScene2D::DIRECT_VERTICAL;
        break;
    case CScene2D::DIRECT_HORIZON:
        direct = CScene2D::DIRECT_HORIZON;
        break;
    case CScene2D::DIRECT_RIGHT_UP:
        direct = CScene2D::DIRECT_RIGHT_UP;
        break;
    case CScene2D::DIRECT_RIGHT_DOWN:
        direct = CScene2D::DIRECT_RIGHT_DOWN;
        break;
    }

    // アニメーションさせる
    SetFlowingAnimation(1, (int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_ONE_ROUND_FRAME], bRightToLeft, direct);
}

//=========================================================
// エフェクト発生アクション
// Author : 後藤慎之助
//=========================================================
void CUI::PlayActionEmitEffect(int nNum)
{
    // 制限を考慮（値には対応していない）
    bool bEmit = false;   // 発生させるかどうか
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_RIMIT])
    {
    case RIMIT_NONE:
        bEmit = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
            bEmit = true;
        }
        break;

    case RIMIT_FROM_FRAME:
        if (m_aActionInfo[nNum].nCntTime >= (int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_FRAME])
        {
            bEmit = true;
        }
        else
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        break;

    case RIMIT_REPEAT_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_FRAME])
        {
            // カウンタ加算
            m_aActionInfo[nNum].nCntTime++;
        }
        else
        {
            // エフェクトを発生させ、カウンタリセット
            bEmit = true;
            m_aActionInfo[nNum].nCntTime = 0;
        }
        break;
    }

    // エフェクト発生
    if (bEmit)
    {
        // 発生位置は、中心以外に変えることもできる
        D3DXVECTOR3 emitPos = CScene2D::GetPosition() +
            D3DXVECTOR3(m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_ADJUST_EMIT_POS_X], 
                m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_ADJUST_EMIT_POS_Y], 0.0f);
        CEffect2D::Emit((int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_TYPE], emitPos, emitPos);
    }
}

//=========================================================
// 〇値までの共通処理
// Author : 後藤慎之助
//=========================================================
void CUI::RimitToValue(const float fChangeRate, float& fCurrentValue, const float fDestValue, bool& bUpdate)
{
    // 加算中なら
    if (fChangeRate > 0)
    {
        // 今回のフレームで指定した値をオーバーしないなら、更新
        float fThisFrameValue = fCurrentValue + fChangeRate;
        if (fThisFrameValue < fDestValue)
        {
            bUpdate = true;
        }
        else
        {
            // 指定した値で止めておく
            fCurrentValue = fDestValue;
        }
    }
    else if (fChangeRate < 0)
    {
        // 今回のフレームで指定した値をオーバーしないなら、更新
        float fThisFrameValue = fCurrentValue + fChangeRate;
        if (fThisFrameValue > fDestValue)
        {
            bUpdate = true;
        }
        else
        {
            // 指定した値で止めておく
            fCurrentValue = fDestValue;
        }
    }
}

//=========================================================
// 値リピートの共通処理
// Author : 後藤慎之助
//=========================================================
void CUI::RimitRepeatValue(float& fChangeRate, const float fMemoryValue, const float fCurrentValue, const float fDestValue, bool& bUpdate)
{
    // 加算中なら
    if (fChangeRate > 0)
    {
        // 記憶した値が目的値より小さいなら
        if (fMemoryValue < fDestValue)
        {
            // 現在の値が目的値より小さいなら更新
            if (fCurrentValue < fDestValue)
            {
                bUpdate = true;
            }
            else
            {
                // 変化量を反転
                fChangeRate *= -1;
            }
        }
        else
        {
            // 現在の値が記憶した値より小さいなら更新
            if (fCurrentValue < fMemoryValue)
            {
                bUpdate = true;
            }
            else
            {
                // 変化量を反転
                fChangeRate *= -1;
            }
        }
    }
    else if (fChangeRate < 0)
    {
        // 記憶した値が目的値より小さいなら
        if (fMemoryValue < fDestValue)
        {
            // 現在の値が記憶した値より大きいなら更新
            if (fCurrentValue > fMemoryValue)
            {
                bUpdate = true;
            }
            else
            {
                // 変化量を反転
                fChangeRate *= -1;
            }
        }
        else
        {
            // 現在の値が目的値より大きいなら移動
            if (fCurrentValue > fDestValue)
            {
                bUpdate = true;
            }
            else
            {
                // 変化量を反転
                fChangeRate *= -1;
            }
        }
    }
}

//=========================================================
// [fileString] UIの情報を文字列に変換
// Author : AYANOKUDO
// 返り値 : UIの情報
//=========================================================
std::string CUI::fileString(void)
{
    std::ostringstream oss;
    // UIの情報をひとまとめにする
    oss << BaseString()         // テクスチャの種類、位置、大きさ
        << RotString()          // 角度
        << ColorString()        // 色
        << AddBlendString()     // 加算合成
        << AlphaTestString()    // アルファテスト
        << ActionString();      // アクションの文字列

    return oss.str();
}

//=========================================================
// [BaseString] 基本の情報を文字列に変換
// Author : AYANOKUDO
//=========================================================
std::string CUI::BaseString(void)
{
    std::ostringstream oss;
    oss << "TYPE = " << m_nTexType << std::endl
        << "POS  = " << std::_Floating_to_string("%.1f", m_memoryPos.x) << " " << std::_Floating_to_string("%.1f", m_memoryPos.y) << std::endl// 位置
        << "SIZE = " << std::_Floating_to_string("%.1f", m_memorySize.x) << " " << std::_Floating_to_string("%.1f", m_memorySize.y) << std::endl;// 大きさ
    return oss.str();
}

//=========================================================
// [RotString] 向きを文字列に変換
// Author : AYANOKUDO
//=========================================================
std::string CUI::RotString(void)
{
    // デフォルト値の場合はスキップ
    if (m_fMemoryRotAngle == 0.0f)
        return "\0";

    std::ostringstream oss;
    oss << "ROT  = " << m_fMemoryRotAngle << std::endl; 

    return oss.str();
}

//=========================================================
// [ActionString] アクション情報を文字列に変換
// Author : AYANOKUDO
//=========================================================
std::string CUI::ActionString(void)
{
    // デフォルト値のときはスキップ

    std::ostringstream oss;
    //std::vector<std::ostringstream > action(MAX_ACTION);            // アクションの文字列
    //std::vector<std::ostringstream > param(MAX_ACTION_PARAM);       // パラメータの文字列

    // アクションの数だけ繰り返し
    for (int nAction = 0; nAction < MAX_ACTION; nAction++)
    {
        // アクションが無いときはスキップ
        if (m_aActionInfo[nAction].action == 0)
        {
            continue;
        }

        // 文字列に変換
        oss << "ACTION" << nAction << " = " << m_aActionInfo[nAction].action << std::endl
            << "LOCK = " << m_aActionInfo[nAction].bLock << std::endl

            // パラメーターぶん繰り返し
            << "PARAM" << 0 << " = " << m_aActionInfo[nAction].afMemoryParam[0] << std::endl
            << "PARAM" << 1 << " = " << m_aActionInfo[nAction].afMemoryParam[1] << std::endl
            << "PARAM" << 2 << " = " << m_aActionInfo[nAction].afMemoryParam[2] << std::endl
            << "PARAM" << 3 << " = " << m_aActionInfo[nAction].afMemoryParam[3] << std::endl
            << "PARAM" << 4 << " = " << m_aActionInfo[nAction].afMemoryParam[4] << std::endl
            << "PARAM" << 5 << " = " << m_aActionInfo[nAction].afMemoryParam[5] << std::endl
            << "PARAM" << 6 << " = " << m_aActionInfo[nAction].afMemoryParam[6] << std::endl
            << "PARAM" << 7 << " = " << m_aActionInfo[nAction].afMemoryParam[7] << std::endl;
    }

    return oss.str();
}

//=========================================================
// [ColorString] 色を文字列に変換
// Author : AYANOKUDO
//=========================================================
std::string CUI::ColorString(void)
{
    // デフォルト値の場合はスキップ
    if (m_memoryCol == DEFAULT_COLOR)
        return "\0";

    std::ostringstream oss;

    oss << "COL  = " << std::_Floating_to_string("%.1f", m_memoryCol.r)            // 色：R
        << " " << std::_Floating_to_string("%.1f", m_memoryCol.g)                  // 色：G
        << " " << std::_Floating_to_string("%.1f", m_memoryCol.b)                  // 色：B
        << " " << std::_Floating_to_string("%.1f", m_memoryCol.a) << std::endl;    // 色：A
    return oss.str();
}

//=========================================================
// [AddBlendString] 加算合成かを文字列に変換
// Author : AYANOKUDO
//=========================================================
std::string CUI::AddBlendString(void)
{
    // デフォルト値の場合はスキップ
    if (m_bUseAdditiveSynthesis == false)
        return "\0";

    std::ostringstream oss;

    oss << "ADD_BLEND =" << m_bUseAdditiveSynthesis << std::endl;   //アルファブレンドの設定

    return oss.str();
}

//=========================================================
// [AlphaTestString] アルファブレンドを文字列に変換
// Author : AYANOKUDO
//=========================================================
std::string CUI::AlphaTestString(void)
{
    // 書く情報の取得
    int nAlphaTestBorder = GetAlphaTestBorder();

    // デフォルト値の場合はスキップ
    if (nAlphaTestBorder == DEFAULT_ALPHATEST_BORDER_2D)
        return "\0";

    std::ostringstream oss;
    oss << "ALPHA_TEST_BORDER =" << nAlphaTestBorder << std::endl;

    return oss.str();
}
