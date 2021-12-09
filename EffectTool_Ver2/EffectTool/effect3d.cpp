//===============================================
//
// �G�t�F�N�g3D���� (effect3d.cpp)
// Author : �ɓ��z��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "effect3d.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect3D::CEffect3D(CScene::OBJTYPE objtype) :CBillboard(objtype)
{
	m_nTexType = 0;

	m_move = DEFAULT_VECTOR;
	m_fAcceleration = 1.0f;
	m_fGravity = 0.0f;
	m_fGravityLimit = 0.0f;

	m_fRotSpeed = 0.0f;

	m_col = DEFAULT_COLOR;
	m_colChangeRate = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fFadeOutRate = 0.0f;
	m_nCntFadeOutLock = 0;

	m_sizeChangeRate = DEFAULT_VECTOR;
	m_nCntSizeChangeLock = 0;
	m_bSizeChangeStartOrFinish = false;

	m_bUseAdditiveSynthesis = false;
	m_bUseZBuffer = true;

	m_nCntAnimTime = 0;
	m_bOneRoundAnim = false;
	m_nAnimPattern = 0;
	m_nAnimSpeed = 0;
	m_bRepeat = false;

	m_nLife = 600;  // �����Ȃ����̂́A10�b�ŏ���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect3D::~CEffect3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect3D::Init()
{
	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �e�N�X�`�����o�C���h
	BindTexture(m_nTexType);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect3D::Uninit(void)
{
	// �r���{�[�h�̏I��
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect3D::Update(void)
{
	// �ʒu�Ƒ傫���Ɗp�x���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	float fRotAngle = GetRotAngle();

	// �ړ��ʂ̍X�V
	UpdateMove(pos);

	// �傫���̍X�V
	UpdateSize(size);

	// �F�̍X�V
	UpdateColor();

	// �p�x�̍X�V
	UpdateAngle(fRotAngle);

	// �ʒu�A�傫���A�F�A�p�x���r���{�[�h�ɔ��f
	CBillboard::SetPos(pos);
	CBillboard::SetSize(size);
	CBillboard::SetCol(m_col);
	CBillboard::SetRotAngle(fRotAngle);
	CBillboard::Update();

	// �����A�傫�����Ȃ��Ȃ�I������
	m_nLife--;
	if (m_col.a <= 0.0f || size.x < 0.0f || size.y < 0.0f || m_nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect3D::Draw(void)
{
	// ���Z����
	if (m_bUseAdditiveSynthesis)
	{
		CBillboard::SetAdditiveSynthesis();
	}

	// Z�o�b�t�@�𖳎����邩�ǂ���
	if (!m_bUseZBuffer)
	{
		CBillboard::SetZBufferNone();
	}

	CBillboard::Draw();
}

//=============================================================================
// �G�t�F�N�g���o�����i��ԍŏ��ɌĂяo���j
// nType�F�G�t�F�N�g�̃^�C�v
// pos�F���W
// fEmitRadius�F���a
//=============================================================================
CEffect3D* CEffect3D::Emit(const int nType, D3DXVECTOR3 pos, float fEmitRadius)
{
	// ��������G�t�F�N�g�̏��
	CEffect3D *pEffect3D = NULL;

	// �G�t�F�N�g�̐��������擾
	CEffectData *pEffectData = CManager::GetEffectData();
	CEffectData::CreateInfo *pCreateInfo = pEffectData->GetCreateInfo(nType);

	// �������������A��������
	for (int nCnt = 0; nCnt < pCreateInfo->nNumOnce; nCnt++)
	{
		// �������a��0�ȏ�Ȃ�
		if (fEmitRadius > 0.0f)
		{
			// �p�x���o��
			float fAngle = float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT - float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT;

			// ���o���̔��a���ǂ����邩
			D3DXVECTOR3 effectPos = pos;
			float fFinalEmitRadius = fEmitRadius;   // �~����
			if (!pCreateInfo->bOnCircleEdge)
			{
				// �~����
				int nEmitRadiusMax = int(fFinalEmitRadius * EFFECT_FLOATING_POINT);
				fFinalEmitRadius = float(rand() % (nEmitRadiusMax + 1)) / EFFECT_FLOATING_POINT;
			}

			// ���ʂɂ���Ĉʒu�Ɣ�U�p�x���ꍇ����
			float fScatterAngle = 0.0f;
			if (pCreateInfo->plane == CEffectData::PLANE_XY)
			{
				effectPos.x += sinf(fAngle)*fFinalEmitRadius;
				effectPos.y += cosf(fAngle)*fFinalEmitRadius;

				// XZ�Ƃ͋t
				if (pCreateInfo->bEmitVectorInside)
				{
					fScatterAngle = atan2((pos.x - effectPos.x), (pos.y - effectPos.y));
				}
				else
				{
					fScatterAngle = atan2((effectPos.x - pos.x), (effectPos.y - pos.y));
				}
			}
			else if (pCreateInfo->plane == CEffectData::PLANE_XZ)
			{
				effectPos.x += -sinf(fAngle)*fFinalEmitRadius;
				effectPos.z += -cosf(fAngle)*fFinalEmitRadius;

				if (pCreateInfo->bEmitVectorInside)
				{
					fScatterAngle = atan2((effectPos.x - pos.x), (effectPos.z - pos.z));
				}
				else
				{
					fScatterAngle = atan2((pos.x - effectPos.x), (pos.z - effectPos.z));
				}
			}

			// ����
			if (!pEffect3D)
			{
				pEffect3D = Create(nType, effectPos, fScatterAngle);
			}
			else
			{
				Create(nType, effectPos, fScatterAngle);
			}

		}
		else
		{
			// ����
			if (!pEffect3D)
			{
				pEffect3D = Create(nType, pos, 0.0f);
			}
			else
			{
				Create(nType, pos, 0.0f);
			}
		}
	}

	// �ŏ��ɐ����������Ԃ�
	return pEffect3D;
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CEffect3D * CEffect3D::Create(const int nType, D3DXVECTOR3 pos, float fScatterAngle)
{
	// �G�t�F�N�g�̐��������擾
	CEffectData *pEffectData = CManager::GetEffectData();
	CEffectData::CreateInfo *pCreateInfo = pEffectData->GetCreateInfo(nType);

	// �������̊m��
	CEffect3D *pEffect3D = NULL;

	// �^�C�v���ƂɁAZ�o�b�t�@�𖳌�������G�t�F�N�g���ǂ��������߂�
	if (pCreateInfo->bUseZBuffer)
	{
		pEffect3D = new CEffect3D(CScene::OBJTYPE_EFFECT3D_Z_NONE);
	}
	else
	{
		pEffect3D = new CEffect3D(CScene::OBJTYPE_EFFECT3D);
	}

	// ���������m�ۏo������
	if (pEffect3D != NULL)
	{
		// �e�N�X�`����񂩂�A�A�j���[�V�����̗L�����擾
		CTexture *pTexture = CManager::GetTexture();
		pEffect3D->m_nAnimPattern = pTexture->GetInfo(pCreateInfo->nTexType)->nPattern;
		pEffect3D->m_nAnimSpeed = pTexture->GetInfo(pCreateInfo->nTexType)->nSpeed;
		pEffect3D->m_bRepeat = pTexture->GetInfo(pCreateInfo->nTexType)->bRepeat;
		if (pEffect3D->m_nAnimPattern > 1)
		{
			pEffect3D->CBillboard::SetTexUV(0.0f, 1.0f / pEffect3D->m_nAnimPattern, 0.0f, 1.0f);
		}

		// �����̉�]�p�x�́A�ő��]���x��0���傫���Ȃ�ς���
		float fRotAngle = 0.0f;
		if (pCreateInfo->nRotSpeedMax > 0)
		{
			fRotAngle = float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT - float(rand() % EFFECT_PI) / EFFECT_FLOATING_POINT;
			pEffect3D->m_fRotSpeed = D3DXToRadian((float(rand() % (pCreateInfo->nRotSpeedMax - pCreateInfo->nRotSpeedMin + 1)) + float(pCreateInfo->nRotSpeedMin)) / EFFECT_FLOATING_POINT) ;

			// ��]�̌����������_���ɂ���
			int nRot = rand() % 1;
			if (nRot == 1)
			{
				pEffect3D->m_fRotSpeed *= -1;
			}
		}

		// ��]�̊p�x���Z�b�g
		pEffect3D->CBillboard::SetRotAngle(fRotAngle);

		// ��ނ����т��Ă���
		pEffect3D->m_nTexType = pCreateInfo->nTexType;

		// ������
		float fSize = 0.0f;
		if (pCreateInfo->nSizeMax > 0)
		{
			fSize = (float(rand() % (pCreateInfo->nSizeMax - pCreateInfo->nSizeMin + 1)) + float(pCreateInfo->nSizeMin)) / EFFECT_FLOATING_POINT;
		}

		// �r���{�[�h�֐ݒ�𔽉f
		D3DXVECTOR3 rot = DEFAULT_VECTOR;
		switch (pCreateInfo->nLayRot)
		{
		case 1:
			rot = LAY_ROT_BOT;
			break;
		case 2:
			rot = LAY_ROT_LEFT;
			break;
		case 3:
			rot = LAY_ROT_TOP;
			break;
		case 4:
			rot = LAY_ROT_RIGHT;
			break;
		}

		// �����o�ϐ��Ɋe�l�����т��Ă���
		pEffect3D->m_fAcceleration = pCreateInfo->fAcceleration;
		pEffect3D->m_fGravity = pCreateInfo->fGravity;
		pEffect3D->m_fGravityLimit = pCreateInfo->fGravityLimit;

		pEffect3D->m_col = pCreateInfo->col;
		pEffect3D->m_colChangeRate = pCreateInfo->colChangeRate;
		pEffect3D->m_fFadeOutRate = pCreateInfo->fFadeOutRate;
		pEffect3D->m_nCntFadeOutLock = pCreateInfo->nCntFadeOutLock;

		pEffect3D->m_sizeChangeRate = pCreateInfo->sizeChangeRate;
		pEffect3D->m_nCntSizeChangeLock = pCreateInfo->nCntSizeChangeLock;
		pEffect3D->m_bSizeChangeStartOrFinish = pCreateInfo->bSizeChangeStartOrFinish;

		pEffect3D->m_bUseAdditiveSynthesis = pCreateInfo->bUseAdditiveSynthesis;
		pEffect3D->m_bUseZBuffer = pCreateInfo->bUseZBuffer;

		// �ړ��ʂ͍Ō�Ɍ���i�ړ��̌����ɉ����āA�����̉�]�p�x���ς��\�������邽�߁j
		pEffect3D->MoveCalculation(nType, fScatterAngle);

		pEffect3D->CBillboard::SetPos(pos);
		pEffect3D->CBillboard::SetSize(D3DXVECTOR3(fSize, fSize, 0.0f));

		// ������
		pEffect3D->Init();

		pEffect3D->CBillboard::SetRot(rot);
		pEffect3D->CBillboard::SetColorVertex(pCreateInfo->col);
		pEffect3D->CBillboard::SetAlphaTestBorder(pCreateInfo->nAlphaTestBorder);
	}

	return pEffect3D;
}

//=============================================================================
// �ړ��ʂ��Z�o����
//=============================================================================
void CEffect3D::MoveCalculation(const int nType, const float fScatterAngle)
{
	// �G�t�F�N�g�̐��������擾
	CEffectData *pEffectData = CManager::GetEffectData();
	CEffectData::CreateInfo *pCreateInfo = pEffectData->GetCreateInfo(nType);

	// �������o��
	float fSpeed = (float(rand() % (pCreateInfo->nSpeedMax - pCreateInfo->nSpeedMin + 1)) + float(pCreateInfo->nSpeedMin)) / EFFECT_FLOATING_POINT;
	float fAuxiliaryAxisSpeed = (float(rand() % (pCreateInfo->nAuxiliaryAxisSpeedMax - pCreateInfo->nAuxiliaryAxisSpeedMin + 1)) + float(pCreateInfo->nAuxiliaryAxisSpeedMin)) / EFFECT_FLOATING_POINT;

	// �ړ��̊p�x�����߂�i��U���{��U�p�x�j
	float fScatterWidth = 0;
	if (pCreateInfo->nScatterWidth > 0)
	{
		fScatterWidth = float(rand() % (pCreateInfo->nScatterWidth + 1)) / EFFECT_FLOATING_POINT - float(pCreateInfo->nScatterWidth / 2.0f) / EFFECT_FLOATING_POINT + (float(pCreateInfo->nScatterAngle) / EFFECT_FLOATING_POINT);
	}
	else
	{
		fScatterWidth = (float(pCreateInfo->nScatterAngle) / EFFECT_FLOATING_POINT);
	}
	float fMoveAngle = fScatterAngle + fScatterWidth;

	// �����̉�]���ړ��̌����ɍ��킹�邩�ǂ���
	if (pCreateInfo->bRotEqualMoveAngle)
	{
		CBillboard::SetRotAngle(-fMoveAngle);  // �r���{�[�h�̕��ƍ��킹�邽�߂Ƀ}�C�i�X��������
	}

	// ���ʂɂ���Ĉړ��ʂ̌������ꍇ����
	if (pCreateInfo->plane == CEffectData::PLANE_XY)
	{
		m_move = D3DXVECTOR3(sinf(fMoveAngle) * fSpeed, cosf(fMoveAngle)* fSpeed, fAuxiliaryAxisSpeed);
	}
	else if (pCreateInfo->plane == CEffectData::PLANE_XZ)
	{
		m_move = D3DXVECTOR3(-sinf(fMoveAngle) * fSpeed, fAuxiliaryAxisSpeed, -cosf(fMoveAngle)* fSpeed);
	}
}

//=============================================================================
// �ړ��ʂ̍X�V
//=============================================================================
void CEffect3D::UpdateMove(D3DXVECTOR3 & pos)
{
	// �ʒu���X�V�i�d�͂�����x���l���j
	pos += m_move;
	m_move *= m_fAcceleration;
	m_move.y -= m_fGravity;
	if (m_fGravityLimit > 0.0f)
	{
		// �d�͐���
		if (m_move.y < -m_fGravityLimit)
		{
			m_move.y = -m_fGravityLimit;
		}
	}
}

//=============================================================================
// �傫���̍X�V
//=============================================================================
void CEffect3D::UpdateSize(D3DXVECTOR3 & size)
{
	// �傫�������b�N����J�E���^
	if (m_nCntSizeChangeLock > 0)
	{
		m_nCntSizeChangeLock--;
	}

	// �傫�����A�J�n�ƏI���ɏꍇ�������Ȃ���X�V
	if (!m_bSizeChangeStartOrFinish)
	{
		// �J�n���A�J�E���^���Ȃ��Ȃ�傫���X�V
		if (m_nCntSizeChangeLock <= 0)
		{
			size += m_sizeChangeRate;
		}
	}
	else
	{
		// �I���Ȃ�A�J�E���^���Ȃ��Ȃ�܂ő傫���X�V
		if (m_nCntSizeChangeLock > 0)
		{
			size += m_sizeChangeRate;
		}
	}
}

//=============================================================================
// �F�̍X�V
//=============================================================================
void CEffect3D::UpdateColor(void)
{
	// �F���X�V
	m_col += m_colChangeRate;

	// ���l�����b�N����J�E���^
	if (m_nCntFadeOutLock > 0)
	{
		m_nCntFadeOutLock--;
	}

	// �A�j���[�V�������g���Ȃ�i�t�F�[�h�A�E�g���肪�ς��j
	if (m_nAnimPattern > 1)
	{
		// ������Ă��Ȃ��Ȃ�e�N�X�`���A�j���[�V�������X�V
		if (!m_bOneRoundAnim)
		{
			// �J�E���g�A�b�v
			m_nCntAnimTime++;

			// �e�N�X�`�����W���X�V
			if (m_nCntAnimTime == m_nAnimSpeed)
			{
				// ���s�[�g����Ȃ�A����̃t���O�ƌ��т��Ȃ�
				if (m_bRepeat)
				{
					SetUpdateTexLeftToRight(m_nAnimPattern);
				}
				else
				{
					m_bOneRoundAnim = SetUpdateTexLeftToRight(m_nAnimPattern);
				}

				// �J�E���^���Z�b�g
				m_nCntAnimTime = 0;
			}
		}
		else
		{
			// ���l�̃��b�N�������ꂽ��
			if (m_nCntFadeOutLock <= 0)
			{
				// ���������t�F�[�h�A�E�g�J�n
				m_col.a -= m_fFadeOutRate;
			}
		}
	}
	else
	{
		// ���l�̃��b�N�������ꂽ��
		if (m_nCntFadeOutLock <= 0)
		{
			// �A�j���[�V�������g��Ȃ��Ȃ�t�F�[�h�A�E�g�J�n
			m_col.a -= m_fFadeOutRate;
		}
	}
}

//=============================================================================
// �p�x�̍X�V
//=============================================================================
void CEffect3D::UpdateAngle(float & fAngle)
{
	fAngle += m_fRotSpeed;
	// 2���ڂɍs���Ȃ��悤�ɂ���
	if (fAngle > D3DXToRadian(180.0f))
	{
		fAngle -= D3DXToRadian(360.0f);
	}
	if (fAngle < D3DXToRadian(-180.0f))
	{
		fAngle += D3DXToRadian(360.0f);
	}
}