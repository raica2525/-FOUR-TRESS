//=============================================================================
//
// UI (ui.cpp)
// Author : ã¡TV H¡»T(¶ñÌ¶¬)
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//=======================================
// CN[ht@C
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
// ÃIoÏé¾
//=======================================
CUI* CUI::m_apAccessUI[] = {};
std::vector<CUI*> CUI::m_pUI = {};  // UIÌîñ
bool CUI::IsPreview = false;        // vr[[h©

//=========================================================
// UIÌRXgN^
// Author : ã¡TV
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
// UIÌfXgN^
// Author : ã¡TV
//=========================================================
CUI::~CUI()
{

}

//=========================================================
// UIÌú»
// Author : ã¡TV
//=========================================================
HRESULT CUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ú»
    CScene2D::Init(pos, size);

    // eNX`ðèÄ
    BindTexture(m_nTexType);

    return S_OK;
}

//=========================================================
// UIÌI¹
// Author : ã¡TV
//=========================================================
void CUI::Uninit(void)
{
    // ANZX ðÁÄ¢éUIÍA»êðjü·é
    if (m_nAccessNum > NOT_EXIST && m_nAccessNum < MAX_ACCESS_NUM)
    {
        m_apAccessUI[m_nAccessNum] = NULL;
    }

    // I¹
    CScene2D::Uninit();
}

//=========================================================
// UIÌXV
// Author : ã¡TV
//=========================================================
void CUI::Update(void)
{
    // Aj[Vðg¤Èç
    if (m_nAnimPattern > 1)
    {
        // êüµÄ¢È¢ÈçeNX`Aj[VðXV
        if (!m_bOneRoundAnim)
        {
            // s[g·éÈçAêüÌtOÆÑÂ¯È¢
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

    // ANV
    for (int nCnt = 0; nCnt < MAX_ACTION; nCnt++)
    {
        PlayAction(nCnt);
    }

    // e¸_ðXVipxà½fjiQ[WnÍAÊÅ¸_îñð²®ÏÝj
    CScene2D::SetColor(m_col);
    if (m_aActionInfo[0].action != ACTION_GAUGE && m_aActionInfo[1].action != ACTION_GAUGE &&
        m_aActionInfo[2].action != ACTION_GAUGE && m_aActionInfo[3].action != ACTION_GAUGE)
    {
        CScene2D::SetRotVertex(m_fRotAngle);
    }

    if (IsPreview)
    {
        //§¾Aå«³ªÈ¢ÈçgptOðfalseÉ
        D3DXVECTOR3 size = CScene2D::GetSize();
        if (m_col.a < 0.0f || size.x < 0.0f || size.y < 0.0f)
        {
            m_bUse = false;
        }
    }

    // gptOªÈ¢ÈçI¹iãLÌgptOðfalseÉÈOÉàAZb^[©çfalseÉÅ«é½ß±Ìè@j
    if (!m_bUse)
    {
        Uninit();
    }
}

//=========================================================
// UIÌ`æ
// Author : ã¡TV
//=========================================================
void CUI::Draw(void)
{
    // \¦·éÈç
    if (m_bDisp)
    {
        // ÁZ¬
        if (m_bUseAdditiveSynthesis)
        {
            CScene2D::SetAdditiveSynthesis();
        }

        // `æ
        CScene2D::Draw();
    }
}

//=========================================================
// UIÌì¬
// Author : ã¡TV
//=========================================================
CUI *CUI::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRotAngle, D3DXCOLOR col,
    bool bFrontText, bool bUseAddiveSynthesis, int nAlphaTestBorder, bool bUseZBuffer,  D3DXVECTOR3 collisionPos, D3DXVECTOR3 collisionSize)
{
    // ÌmÛ
    CUI *pUI = NULL;

    // ^Cv²ÆÉAeLXgÌèO©ãëÌUI©Ç¤©ðßé
    if (bFrontText)
    {
        pUI = new CUI(CScene::OBJTYPE_UI_FRONT_TEXT);
    }
    else
    {
        pUI = new CUI(CScene::OBJTYPE_UI_BACK_TEXT);
    }

    // eNX`Ì^CvÍæÉÑÂ¯Ä¨­
    pUI->m_nTexType = nTexType;

    // ú»i3DfÌ És­ÈçAZBufferðl¶·éj
    float fZBufferValue = 0.0f;
    if (bUseZBuffer)
    {
        fZBufferValue = 1.0f;
    }
    pos.z = fZBufferValue;
    pUI->Init(pos, size);

    // e³ÉÝèð½f
    pUI->CScene2D::SetAlphaTestBorder(nAlphaTestBorder);

    // øðoÏÉÑÂ¯é
    if (nRotAngle != 0)
    {
        pUI->m_fRotAngle = D3DXToRadian((float)nRotAngle);
    }
    pUI->m_col = col;
    pUI->m_bUseAdditiveSynthesis = bUseAddiveSynthesis;
    pUI->m_collisionPos = collisionPos;
    pUI->m_collisionSize = collisionSize;

    // L¯pàÑÂ¯é
    pUI->m_memoryPos = pos;
    pUI->m_memorySize = size;
    pUI->m_fMemoryRotAngle = pUI->m_fRotAngle;
    pUI->m_memoryCol = col;

    // eNX`îñ©çAAj[VÌL³ðæ¾
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
// UIÌANZX ðæ¾
// Author : ã¡TV
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
// UIÌvfðí
//=========================================================
void CUI::EraseUI(int nUINum)
{
    // ReiàÌvfðí
    m_pUI.erase(m_pUI.begin() + nUINum);
    //m_pUI[nUINum] = nullptr;// null|C^É·é
}

//=========================================================
// UIÌANZX ðÝè
// Author : ã¡TV
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
// UIÌ®«îñðÝè
// Author : ã¡TV
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

        // eNX`uhANVÈçA±±Åp¢éeNX`ðoCh
        if (m_aActionInfo[nNum].action == ACTION_TEX_BREND)
        {
            // uhû@
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

            // uhpÌeNX`ðoCh
            m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_IDX]
                = (float)BindTexture((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_TEX_NUMBER], brend);
        }
        else if (m_aActionInfo[nNum].action == ACTION_ROT)
        {
            // ñ]ANVÈçAlðWAÉ·é
            m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE] = D3DXToRadian(m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE]);
            m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE] = D3DXToRadian(m_aActionInfo[nNum].afParam[PARAM_ROT_VALUE]);
        }
        else if (m_aActionInfo[nNum].action == ACTION_TEX_PLACE)
        {
            // `æ·éeNX`Ìêðwè
            CScene2D::SetTexturePlace((int)m_aActionInfo[nNum].afParam[PARAM_TEX_PLACE_PLACE], (int)m_aActionInfo[nNum].afParam[PARAM_TEX_PLACE_PATTERN]);
        }

        // L¯pÏÉÑÂ¯é
        m_aActionInfo[nNum].bMemoryLock = m_aActionInfo[nNum].bLock;
        for (int nCnt = 0; nCnt < MAX_ACTION_PARAM; nCnt++)
        {
            m_aActionInfo[nNum].afMemoryParam[nCnt] = m_aActionInfo[nNum].afParam[nCnt];
        }
}

//=========================================================
// UIÌANVÌbNóÔðÝè
// Author : ã¡TV
//=========================================================
void CUI::SetActionLock(int nNum, bool bLock)
{
    // ÍÍàÈç
    if (nNum >= 0 && nNum < MAX_ACTION)
    {
        m_aActionInfo[nNum].bLock = bLock;
    }
}

//=========================================================
// UIÌêÌANVóµðZbg
// Author : ã¡TV
//=========================================================
void CUI::SetActionReset(int nNum)
{
        // ÍÍàÈç
        if (nNum >= 0 && nNum < MAX_ACTION)
        {
            // \¢ÌÌàeðZbg
            m_aActionInfo[nNum].nCntTime = 0;
            m_aActionInfo[nNum].bLock = m_aActionInfo[nNum].bMemoryLock;
            for (int nCntParam = 0; nCntParam < MAX_ACTION_PARAM; nCntParam++)
            {
                m_aActionInfo[nNum].afParam[nCntParam] = m_aActionInfo[nNum].afMemoryParam[nCntParam];
            }

            // ANVÉæÁÄAZbg·éàÌðÏ¦é
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
                PlayActionTexBrend(nNum);   // eNX`ÀWXV
                break;
            case ACTION_LOOP_ANIM:
                CScene2D::ResetCountAnim();
                PlayActionLoopAnim(nNum);   // eNX`ÀWXV
                break;
            case ACTION_TEX_PLACE:
                CScene2D::SetTexturePlace((int)m_aActionInfo[nNum].afMemoryParam[PARAM_TEX_PLACE_PLACE], (int)m_aActionInfo[nNum].afMemoryParam[PARAM_TEX_PLACE_PATTERN]);
                break;
            }
        }

}

//=========================================================
// UIÌSÄÌANVóµðZbg
// Author : ã¡TV
//=========================================================
void CUI::SetAllActionReset(void)
{
    for (int nCnt = 0; nCnt < MAX_ACTION; nCnt++)
    {
        SetActionReset(nCnt);
    }
}

//=========================================================
// SÄÌANVðÀs·éàÆÌ
// Author : ã¡TV
//=========================================================
void CUI::PlayAction(int nNum)
{
    // bN³êÄ¢È¢Èç
    if (!m_aActionInfo[nNum].bLock)
    {
        // ANVðÀs·é
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
// TCYANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionSize(int nNum)
{
    // å«³ðæ¾
    D3DXVECTOR3 size = CScene2D::GetSize();

    // §Àðl¶
    bool bUpdateX = false;   // XðXV·é©Ç¤©
    bool bUpdateY = false;   // YðXV·é©Ç¤©
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_RIMIT])
    {
    case RIMIT_NONE:
        bUpdateX = true;
        bUpdateY = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_SIZE_FRAME])
        {
            // JE^ÁZ
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
            // JE^ÁZ
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
            bUpdateX = true;
            bUpdateY = true;
        }
        else
        {
            // JE^ZbgµAÏ»Êð½]³¹é
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
            // äÏ`©Ç¤©
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // äÏ`©Ç¤©
    if ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_EQUAL_RATIO] == 0)
    {
        // XXV
        if (bUpdateX)
        {
            size.x += m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X];
        }

        // YXV
        if (bUpdateY)
        {
            size.y += m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_Y];
        }
    }
    else if ((int)m_aActionInfo[nNum].afParam[PARAM_SIZE_EQUAL_RATIO] == 1)
    {
        // äÏ`ÍxîÅÁZµÄ¢é½ßAyðæÉvZµÈ¢Æs[gÅ¸êé
        if (bUpdateX)
        {
            if (size.x != 0.0f)
            {
                size.y += (size.y / size.x) * m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X];
            }
            size.x += m_aActionInfo[nNum].afParam[PARAM_SIZE_CHANGE_RATE_X];
        }
    }

    // å«³ðÝè
    CScene2D::SetSize(size);
}

//=========================================================
// ÊuANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionPos(int nNum)
{
    // Êuðæ¾
    D3DXVECTOR3 pos = CScene2D::GetPosition();

    // §Àðl¶
    bool bUpdateX = false;   // XXV·é©Ç¤©
    bool bUpdateY = false;   // YXV·é©Ç¤©
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_POS_RIMIT])
    {
    case RIMIT_NONE:
        bUpdateX = true;
        bUpdateY = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_POS_FRAME])
        {
            // JE^ÁZ
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
            // JE^ÁZ
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
            bUpdateX = true;
            bUpdateY = true;
        }
        else
        {
            // JE^ZbgµAÏ»Êð½]³¹é
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // XXV
    if (bUpdateX)
    {
        pos.x += m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X];
        m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_X] *= m_aActionInfo[nNum].afParam[PARAM_POS_ACCEL];
    }

    // YXV
    if (bUpdateY)
    {
        pos.y += m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y];
        m_aActionInfo[nNum].afParam[PARAM_POS_CHANGE_RATE_Y] *= m_aActionInfo[nNum].afParam[PARAM_POS_ACCEL];
    }

    // ÊuðÝè
    CScene2D::SetPosition(pos);
}

//=========================================================
// §¾xANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionAlpha(int nNum)
{
    // §Àðl¶
    bool bUpdate = false;   // XV·é©Ç¤©
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_RIMIT])
    {
    case RIMIT_NONE:
        bUpdate = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_ALPHA_FRAME])
        {
            // JE^ÁZ
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
            // JE^ÁZ
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
            bUpdate = true;
        }
        else
        {
            // JE^ZbgµAÏ»Êð½]³¹é
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // XV
    if (bUpdate)
    {
        m_col.a += m_aActionInfo[nNum].afParam[PARAM_ALPHA_CHANGE_RATE];
    }
}

//=========================================================
// FÏ¦ANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionColor(int nNum)
{
    // §Àðl¶
    bool bUpdateR = false;   // RXV·é©Ç¤©
    bool bUpdateG = false;   // GXV·é©Ç¤©
    bool bUpdateB = false;   // BXV·é©Ç¤©
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
            // JE^ÁZ
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
            // JE^ÁZ
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
            bUpdateR = true;
            bUpdateG = true;
            bUpdateB = true;
        }
        else
        {
            // JE^ZbgµAÏ»Êð½]³¹é
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
        }
        break;
    }

    // RXV
    if (bUpdateR)
    {
        m_col.r += m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_R];
    }

    // GXV
    if (bUpdateG)
    {
        m_col.g += m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_G];
    }

    // BXV
    if (bUpdateB)
    {
        m_col.b += m_aActionInfo[nNum].afParam[PARAM_COLOR_CHANGE_RATE_B];
    }
}

//=========================================================
// ñ]ANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionRot(int nNum)
{
         //Ïé¾
        const float ANGLE_ADJUST = D3DXToRadian(90.0f);   // vÅ¢¤0ª0xÌÉí¹éi2D|SÌ¸_ðZÅwèµÄ¢é©çj

        // §Àðl¶
        bool bUpdate = false;   // XV·é©Ç¤©
        switch ((int)m_aActionInfo[nNum].afParam[PARAM_ROT_RIMIT])
        {
        case RIMIT_NONE:
            bUpdate = true;
            break;

        case RIMIT_TO_FRAME:
            if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_ROT_FRAME])
            {
                // JE^ÁZ
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
                // JE^ÁZ
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
                // JE^ÁZ
                m_aActionInfo[nNum].nCntTime++;
                bUpdate = true;
            }
            else
            {
                // JE^ZbgµAÏ»Êð½]³¹é
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
                // JE^ÁZ
                m_aActionInfo[nNum].nCntTime++;
            }
            break;
        }

        // XV
        if (bUpdate)
        {
            m_fRotAngle += D3DXToRadian(m_aActionInfo[nNum].afParam[PARAM_ROT_CHANGE_RATE]);
        }

        //// pxÌ²®
        //if (m_fRotAngle > D3DXToRadian(180.0f) || m_fRotAngle < D3DXToRadian(-180.0f))
        //{
        //    m_fRotAngle *= -1;
        //}
}

//=========================================================
// eNX`uhANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionTexBrend(int nNum)
{
    //if (!IsPreview)// vr[[hÅÍÈ¢ÍXLbv
    //    return;

    // eNX`îñ©çAAj[VÌL³ðæ¾
    CTexture::Info *pTextureInfo = CManager::GetTexture()->GetInfo((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_TEX_NUMBER]);
    int nPattern = pTextureInfo->nPattern;
    int nAnimSpeed = pTextureInfo->nSpeed;

    // Aj[Vðg¤Èç
    if (nPattern > 1)
    {
        // textureÌûÅÝè³êÄ¢éàÌðg¤
        CScene2D::SetAnimation(nAnimSpeed, nPattern, (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_IDX]);
    }
    else
    {
        // C^[oÔðJEg_E
        if (m_aActionInfo[nNum].nCntTime > 0)
        {
            m_aActionInfo[nNum].nCntTime--;
        }
        else
        {
            // Ïé¾
            bool bRightToLeft = false;
            CScene2D::DIRECT direct = CScene2D::DIRECT_VERTICAL;

            // E©ç¶©
            if ((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_RIGHT_TO_LEFT] == 0)
            {
                bRightToLeft = false;
            }
            else if ((int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_RIGHT_TO_LEFT] == 1)
            {
                bRightToLeft = true;
            }

            // ü«
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

            // Aj[V³¹é
            if (SetFlowingAnimation(1, (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_ONE_ROUND_FRAME],
                bRightToLeft, direct, (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_IDX]))
            {
                // êüµ½çAC^[o
                m_aActionInfo[nNum].nCntTime = (int)m_aActionInfo[nNum].afParam[PARAM_TEX_BREND_INTERVAL_FRAME];
            }
        }
    }
}

//=========================================================
// [vAj[VANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionLoopAnim(int nNum)
{
    //if (!IsPreview)// vr[[hÅÍÈ¢ÍXLbv
    //    return;

    // Ïé¾
    bool bRightToLeft = false;
    CScene2D::DIRECT direct = CScene2D::DIRECT_VERTICAL;

    // E©ç¶©
    if ((int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_RIGHT_TO_LEFT] == 0)
    {
        bRightToLeft = false;
    }
    else if ((int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_RIGHT_TO_LEFT] == 1)
    {
        bRightToLeft = true;
    }

    // ü«
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

    // Aj[V³¹é
    SetFlowingAnimation(1, (int)m_aActionInfo[nNum].afParam[PARAM_LOOP_ANIM_ONE_ROUND_FRAME], bRightToLeft, direct);
}

//=========================================================
// GtFNg­¶ANV
// Author : ã¡TV
//=========================================================
void CUI::PlayActionEmitEffect(int nNum)
{
    // §Àðl¶ilÉÍÎµÄ¢È¢j
    bool bEmit = false;   // ­¶³¹é©Ç¤©
    switch ((int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_RIMIT])
    {
    case RIMIT_NONE:
        bEmit = true;
        break;

    case RIMIT_TO_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_FRAME])
        {
            // JE^ÁZ
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
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
        }
        break;

    case RIMIT_REPEAT_FRAME:
        if (m_aActionInfo[nNum].nCntTime < (int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_FRAME])
        {
            // JE^ÁZ
            m_aActionInfo[nNum].nCntTime++;
        }
        else
        {
            // GtFNgð­¶³¹AJE^Zbg
            bEmit = true;
            m_aActionInfo[nNum].nCntTime = 0;
        }
        break;
    }

    // GtFNg­¶
    if (bEmit)
    {
        // ­¶ÊuÍASÈOÉÏ¦é±ÆàÅ«é
        D3DXVECTOR3 emitPos = CScene2D::GetPosition() +
            D3DXVECTOR3(m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_ADJUST_EMIT_POS_X], 
                m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_ADJUST_EMIT_POS_Y], 0.0f);
        CEffect2D::Emit((int)m_aActionInfo[nNum].afParam[PARAM_EMIT_EFFECT_TYPE], emitPos, emitPos);
    }
}

//=========================================================
// ZlÜÅÌ¤Ê
// Author : ã¡TV
//=========================================================
void CUI::RimitToValue(const float fChangeRate, float& fCurrentValue, const float fDestValue, bool& bUpdate)
{
    // ÁZÈç
    if (fChangeRate > 0)
    {
        // ¡ñÌt[Åwèµ½lðI[o[µÈ¢ÈçAXV
        float fThisFrameValue = fCurrentValue + fChangeRate;
        if (fThisFrameValue < fDestValue)
        {
            bUpdate = true;
        }
        else
        {
            // wèµ½lÅ~ßÄ¨­
            fCurrentValue = fDestValue;
        }
    }
    else if (fChangeRate < 0)
    {
        // ¡ñÌt[Åwèµ½lðI[o[µÈ¢ÈçAXV
        float fThisFrameValue = fCurrentValue + fChangeRate;
        if (fThisFrameValue > fDestValue)
        {
            bUpdate = true;
        }
        else
        {
            // wèµ½lÅ~ßÄ¨­
            fCurrentValue = fDestValue;
        }
    }
}

//=========================================================
// ls[gÌ¤Ê
// Author : ã¡TV
//=========================================================
void CUI::RimitRepeatValue(float& fChangeRate, const float fMemoryValue, const float fCurrentValue, const float fDestValue, bool& bUpdate)
{
    // ÁZÈç
    if (fChangeRate > 0)
    {
        // L¯µ½lªÚIlæè¬³¢Èç
        if (fMemoryValue < fDestValue)
        {
            // »ÝÌlªÚIlæè¬³¢ÈçXV
            if (fCurrentValue < fDestValue)
            {
                bUpdate = true;
            }
            else
            {
                // Ï»Êð½]
                fChangeRate *= -1;
            }
        }
        else
        {
            // »ÝÌlªL¯µ½læè¬³¢ÈçXV
            if (fCurrentValue < fMemoryValue)
            {
                bUpdate = true;
            }
            else
            {
                // Ï»Êð½]
                fChangeRate *= -1;
            }
        }
    }
    else if (fChangeRate < 0)
    {
        // L¯µ½lªÚIlæè¬³¢Èç
        if (fMemoryValue < fDestValue)
        {
            // »ÝÌlªL¯µ½læèå«¢ÈçXV
            if (fCurrentValue > fMemoryValue)
            {
                bUpdate = true;
            }
            else
            {
                // Ï»Êð½]
                fChangeRate *= -1;
            }
        }
        else
        {
            // »ÝÌlªÚIlæèå«¢ÈçÚ®
            if (fCurrentValue > fDestValue)
            {
                bUpdate = true;
            }
            else
            {
                // Ï»Êð½]
                fChangeRate *= -1;
            }
        }
    }
}

//=========================================================
// [fileString] UIÌîñð¶ñÉÏ·
// Author : AYANOKUDO
// Ôèl : UIÌîñ
//=========================================================
std::string CUI::fileString(void)
{
    std::ostringstream oss;
    // UIÌîñðÐÆÜÆßÉ·é
    oss << BaseString()         // eNX`ÌíÞAÊuAå«³
        << RotString()          // px
        << ColorString()        // F
        << AddBlendString()     // ÁZ¬
        << AlphaTestString()    // At@eXg
        << ActionString();      // ANVÌ¶ñ

    return oss.str();
}

//=========================================================
// [BaseString] î{Ìîñð¶ñÉÏ·
// Author : AYANOKUDO
//=========================================================
std::string CUI::BaseString(void)
{
    std::ostringstream oss;
    oss << "TYPE = " << m_nTexType << std::endl
        << "POS  = " << std::_Floating_to_string("%.1f", m_memoryPos.x) << " " << std::_Floating_to_string("%.1f", m_memoryPos.y) << std::endl// Êu
        << "SIZE = " << std::_Floating_to_string("%.1f", m_memorySize.x) << " " << std::_Floating_to_string("%.1f", m_memorySize.y) << std::endl;// å«³
    return oss.str();
}

//=========================================================
// [RotString] ü«ð¶ñÉÏ·
// Author : AYANOKUDO
//=========================================================
std::string CUI::RotString(void)
{
    // ftHglÌêÍXLbv
    if (m_fMemoryRotAngle == 0.0f)
        return "\0";

    std::ostringstream oss;
    oss << "ROT  = " << m_fMemoryRotAngle << std::endl; // fO[\LÅoÍ

    return oss.str();
}

//=========================================================
// [ActionString] ANVîñð¶ñÉÏ·
// Author : AYANOKUDO
//=========================================================
std::string CUI::ActionString(void)
{
    // ftHglÌÆ«ÍXLbv

    std::ostringstream oss;

    // ANVÌ¾¯JèÔµ
    for (int nAction = 0; nAction < MAX_ACTION; nAction++)
    {
        // ANVª³¢Æ«ÍXLbv
        if (m_aActionInfo[nAction].action == 0)
        {
            continue;
        }

        // ¶ñÉÏ·
        oss << "ACTION" << nAction << " = " << m_aActionInfo[nAction].action << std::endl
            << "LOCK = " << m_aActionInfo[nAction].bLock << std::endl;

        // p[^[ÔñJèÔµ
        if (m_aActionInfo[nAction].action == 6)
        {// ñ]ANVÌÆ«ÌÝAÅÌp[^[ðfO[ÉÏ··é
            oss << "PARAM" << 0 << " = " << D3DXToDegree(m_aActionInfo[nAction].afMemoryParam[0]) << std::endl;
        }
        else
        {
            oss << "PARAM" << 0 << " = " << m_aActionInfo[nAction].afMemoryParam[0] << std::endl;
        }
        oss << "PARAM" << 1 << " = " << m_aActionInfo[nAction].afMemoryParam[1] << std::endl
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
// [ColorString] Fð¶ñÉÏ·
// Author : AYANOKUDO
//=========================================================
std::string CUI::ColorString(void)
{
    // ftHglÌêÍXLbv
    if (m_memoryCol == DEFAULT_COLOR)
        return "\0";

    std::ostringstream oss;

    oss << "COL  = " << std::_Floating_to_string("%.1f", m_memoryCol.r)            // FFR
        << " " << std::_Floating_to_string("%.1f", m_memoryCol.g)                  // FFG
        << " " << std::_Floating_to_string("%.1f", m_memoryCol.b)                  // FFB
        << " " << std::_Floating_to_string("%.1f", m_memoryCol.a) << std::endl;    // FFA
    return oss.str();
}

//=========================================================
// [AddBlendString] ÁZ¬©ð¶ñÉÏ·
// Author : AYANOKUDO
//=========================================================
std::string CUI::AddBlendString(void)
{
    // ftHglÌêÍXLbv
    if (m_bUseAdditiveSynthesis == false)
        return "\0";

    std::ostringstream oss;

    oss << "ADD_BLEND =" << m_bUseAdditiveSynthesis << std::endl;   //At@uhÌÝè

    return oss.str();
}

//=========================================================
// [AlphaTestString] At@uhð¶ñÉÏ·
// Author : AYANOKUDO
//=========================================================
std::string CUI::AlphaTestString(void)
{
    // ­îñÌæ¾
    int nAlphaTestBorder = GetAlphaTestBorder();

    // ftHglÌêÍXLbv
    if (nAlphaTestBorder == DEFAULT_ALPHATEST_BORDER_2D)
        return "\0";

    std::ostringstream oss;
    oss << "ALPHA_TEST_BORDER =" << nAlphaTestBorder << std::endl;

    return oss.str();
}
