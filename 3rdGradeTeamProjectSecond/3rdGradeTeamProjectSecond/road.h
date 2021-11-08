//====================================================================
//
// ���̏��� (road.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _ROAD_H_
#define _ROAD_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene3d.h"

//================================================
// �O���錾
//================================================

//================================================
// �}�N����`
//================================================

//================================================
// �N���X�錾
//================================================

// ���N���X
class CRoad : public CScene3D
{
public:

    // �J���[�t�F�[�Y
    typedef enum
    {
        COLOR_PHASE_G_DOWN = 0,
        COLOR_PHASE_G_UP,
    }COLOR_PHASE;

    CRoad();
    ~CRoad();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CRoad *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR);

    //=============================
    // �Q�b�^�[
    //=============================
    bool GetPast(void) { return m_bPast; }

    //=============================
    // �Z�b�^�[
    //=============================
    void SetPast(bool bPast) { m_bPast = bPast; }

private:
    D3DXCOLOR m_col;        // �F
    COLOR_PHASE m_colPhase; // �J���[�t�F�[�Y
    bool m_bPast;           // �ʂ�߂������ǂ���
};

#endif