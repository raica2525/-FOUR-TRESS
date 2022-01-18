//====================================================================
//
// ���f���G�t�F�N�g�̏��� (modelEffect.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _MODEL_EFFECT_H_
#define _MODEL_EFFECT_H_

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

// ���f���G�t�F�N�g�N���X
class CModelEffect : public CScene3D
{
public:

    CModelEffect();
    ~CModelEffect();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CModelEffect *Create(int nModelType, D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR, D3DXCOLOR col = DEFAULT_COLOR, D3DXCOLOR colChangeRate = DEFAULT_COLOR_NONE, bool bUseLight = true);

    //=======================
    // �Z�b�^�[
    //=======================
    void SetAdditive(void) { m_bUseAdditiveSynthesis = true; }
    void SetUseDraw(bool bUseDraw) { m_bUseDraw = bUseDraw; }
    void SetColor(D3DXCOLOR col) { m_col = col; }
    void SetShootUp(D3DXVECTOR2 slidePos);

    //=======================
    // �Q�b�^�[
    //=======================

private:
    int m_nModelType;             // �g�����f���̎��
    D3DXCOLOR m_col;              // �F
    D3DXCOLOR m_colChangeRate;    // �F�ω�����
    bool m_bUseLight;             // ���C�g���g�����ǂ���

    bool m_bUseDraw;              // �`�悷�邩�ǂ���
    bool m_bUseAdditiveSynthesis; // ���Z�����ɂ��邩�ǂ���

    bool m_bShootUp;              // �ł��グ�邩�ǂ���
    D3DXVECTOR3 m_move;           // �ړ���
    D3DXVECTOR3 m_rotMove;        // �����̈ړ���
};

#endif