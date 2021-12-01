//====================================================================
//
// �G�t�F�N�g�c�[���̏��� (effecttool.h)
// Author : �ɓ��@�z��
//
//====================================================================
#ifndef _EFFECTTOOL_H_
#define _EFFECTTOOL_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define EFFECT_TYPE (10)

//================================================
// �G�t�F�N�g�c�[���N���X
//================================================
class CEffectTool
{
public:

	CEffectTool();
	~CEffectTool();

	typedef struct
	{
		D3DXVECTOR3 pos;				// ���W

		int nTexType;					// �g���e�N�X�`���̎��
		int nNumOnce;					// ����������
		int nPlane;						// ����

		bool bOnCircleEdge;				// �~����ɂ��邩�ǂ���
		bool bEmitVectorInside;			// ���o����������ɂ��邩�ǂ���
		int nScatterAngle;				// ��U�p�x�i0�`314�j
		int nScatterWidth;				// ��U���i0�`314�j
		float fEmitRadius;				// ���a�̑傫��

		int nSpeedMax;					// �ő呬�x
		int nSpeedMin;					// �ŏ����x
		int nAuxiliaryAxisSpeedMax;		// �ő�⏕���i2D��3D�ŁA���̊����o�����߂̂��́j
		int nAuxiliaryAxisSpeedMin;		// �ŏ��⏕���i2D��3D�ŁA���̊����o�����߂̂��́j

		float fAcceleration;			// �����x(1.0�ő�)
		float fGravity;					// �d��
		float fGravityLimit;			// �d�͐���

		int nLayRot;					// �|���S�����̂��̂����ɂ��邩�ǂ����i1,2�Ȃ�r���{�[�h�����j
		bool bRotEqualMoveAngle;		// ��]���ړ��̌����ɍ��킹�邩
		int nRotSpeedMax;				// �ő��]���x
		int nRotSpeedMin;				// �ŏ���]���x

		D3DXCOLOR col;					// �F
		D3DXCOLOR colChangeRate;		// �F�ω�����
		float fFadeOutRate;				// �t�F�[�h�A�E�g�̊���
		int nCntFadeOutLock;			// ���l�����b�N����J�E���^

		int nSizeMax;					// �ő�傫��
		int nSizeMin;					// �ŏ��傫��
		D3DXVECTOR3 fSizeChangeRate;	// �g��/�k������
		int nCntSizeChangeLock;			// �傫�������b�N����J�E���^
		bool bSizeChangeStartOrFinish;	// �傫����ς���̂��n�܂邩�A�I���̂�

		bool bUseAdditiveSynthesis;		// ���Z�������邩�ǂ���
		bool bUseZBuffer;				// Z�o�b�t�@���g����
		int nAlphaTestBorder;			// ���e�X�g�̃{�[�_�[
	}EffectInfo;	// �G�t�F�N�g�̏��

	HRESULT Init(HWND hWnd);	// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void SetEffectInfo(int nEffectType);		// �G�t�F�N�g���Z�b�g����
	EffectInfo* GetEffectInfo(int nEffectType);	// �G�t�F�N�g���擾����
private:
	//====================
	// �����o�֐�
	//====================
	EffectInfo InitEffectInfo(void);	// �G�t�F�N�g�c�[���̏�����C�ɏ��������鏈��

	void UpdateEffectImgui(void);	// �G�t�F�N�g�pImgui�̍X�V����
	void UpdateOptionImgui(void);	// �I�v�V�����pImgui�̍X�V����

	// Imgui�̍��ڂ��Ƃ̏���
	void ImguiEffectPos(void);		// ���W�Ɋւ���ݒ�
	void ImguiEffectOption(void);	// �G�t�F�N�g�Ɋւ���ݒ�
	void ImguiEffectMove(void);		// �ړ��Ɋւ���ݒ�
	void ImguiEffectRot(void);		// ��]�Ɋւ���ݒ�
	void ImguiEffectCol(void);		// �F�Ɋւ���ݒ�
	void ImguiEffectSize(void);		// �T�C�Y�Ɋւ���ݒ�
	void ImguiEffectDraw(void);		// �`��Ɋւ���ݒ�
	void ImguiEffectCreate(void);	// �G�t�F�N�g�̐����Ɋւ���ݒ�
	void ImguiEffectCamera(void);	// �J�����Ɋւ���ݒ�
	void EffectCreate(void);		// �G�t�F�N�g�̐���

	void HelpText(const char* cText);	// ���ӏ����̏���

	//====================
	// �����o�ϐ�
	//====================
	EffectInfo m_EffectInfo;		// �G�t�F�N�g�̏��
	int m_nEffectNum;				// �G�t�F�N�g�̔ԍ�
	float m_fCreateFlame;			// ��������t���[��
	float m_fCountFlame;			// �J�E���g
	float m_fBarWidth;				// �o�[�̉���
	bool m_bCreate[EFFECT_TYPE];	// �e�G�t�F�N�g�̐������邩���Ȃ���
	bool m_bRandamCreate;			// �����_���Ő��������邩
	bool m_bShowImguiWindow[2];		// Imgui�̃E�B���h�E�����邩������
	D3DXVECTOR3 m_RandomRangePos;	// �����_���ȍ��W�Ő�������Ƃ��͈̔�
};

#endif