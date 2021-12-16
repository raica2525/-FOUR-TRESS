//========================================================================================================================
//
// �J�������� [camera.h]
// Author : �㓡�T�V��
//
//========================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//================================================
// �}�N����`
//================================================

// �J�����̐U��
#define SHAKE_VALUE_BALL_HIT_WALL 6.25f
#define SHAKE_VALUE_SHOOT_BALL_SMALL 25.0f
#define SHAKE_VALUE_SHOOT_BALL_BIG 50.0f
#define SHAKE_VALUE_SHOOT_BALL_ULTRA 50.0f

#define CAMERA_DEFAULT_ROT D3DXToRadian(90.0f)

//================================================
// �J�����N���X�錾
//================================================
class CCamera
{
public:
    CCamera();
    ~CCamera();

    // �J�����̏��
    typedef enum
    {
        STATE_NONE = 0,         // �Ȃ�
        STATE_OUT_GAME,         // �A�E�g�Q�[��
        STATE_BUTTLE,           // �o�g����
        STATE_FINISH_EACH,      // �������̊e������
        STATE_SP,               // �K�E�Z��
    }STATE;

    // �J�����̎g�p���
    typedef enum
    {
        SETTING_GAME = 0,         // �Q�[����
        SETTING_CUSTOM,           // �J�X�^�}�C�Y��
    }SETTING;

    // �J�����̐U���i�K
    typedef enum
    {
        SHAKE_PHASE_NONE = 0,
        SHAKE_PHASE_1,
        SHAKE_PHASE_2,
        SHAKE_PHASE_3,
        SHAKE_PHASE_4,
        SHAKE_PHASE_5,
        SHAKE_PHASE_6,
        SHAKE_PHASE_MAX
    }SHAKE_PHASE;

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    CCamera *Create(void);
    void ResetCamera(D3DXVECTOR3 pos, float fRot, SETTING setting);     // �J�����̃��Z�b�g
    void Shake(void);

    /*========================================================
    // �Z�b�^�[
    //======================================================*/
    void SetState(STATE state) { m_nCntState = 0; m_shakePhase = SHAKE_PHASE_NONE; m_state = state; }    // ��Ԃ��Z�b�g����Ƃ��́A�J�E���^�������Ƀ��Z�b�g
    void SetLookAt(D3DXVECTOR3 pos) { m_posRDest = pos; }
    void SetShake(float fShakeValue, bool bResetShake = true);

    /*========================================================
    // �Q�b�^�[
    //======================================================*/
    STATE GetState(void) { return m_state; }
    D3DXVECTOR3 GetPos(void) { return m_posV; }
    D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }
    D3DXMATRIX GetViewMtx(void) { return m_mtxView; }

private:
    D3DXVECTOR3	m_posRDest;         // �J�����̒����_�i�ړI�l�j
    D3DXVECTOR3	m_posVDest;         // �J�����̍��W�i�ړI�l�j
    STATE m_state;                  // �J�����̏��
    D3DXVECTOR3	m_posV;             // �J�����̍��W
    D3DXVECTOR3	m_pos;              // �J�����̍��W
    D3DXVECTOR3	m_posR;             // �����_
    D3DXVECTOR3	m_vecU;             // ������̃x�N�g��
    D3DXMATRIX	m_mtxProjection;    // �v���W�F�N�V�����}�g���N�X
    D3DXMATRIX	m_mtxView;          // �r���[�}�g���N�X
    float		m_fDistance;        // ����
    float		m_fPhi;             // ����]
    float		m_fTheta;           // �c��]
    int m_nCntState;                // ��ԃJ�E���^
    int m_shakePhase;               // �U���i�K
    float m_fShakeValue;            // �U����
};

#endif