//===============================================
//
// �V�[�����2D�|���S������ (scene2d.cpp)
// Author : �㓡�T�V���A�r�c�I��i�e�N�X�`���u�����f�B���O�Ή��j
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//========================================
// �ÓI�����o�ϐ���
//========================================
bool CScene2D::m_bAdditiveSynthesis = false;

//===========================================
// �e���v���[�g�֐�                       
//===========================================

//===========================================
// ����Z
//
// ����   :data0,data1�̓f�[�^
// �߂�l :�v�Z����
//===========================================
template<class T> T Divide(const T data0, const T data1)
{
	// �ϐ��錾
	T answer;   // ����

				// ����
	answer = data0 / data1;

	return answer;
}

//============================================================
// �V�[�����2D�|���S���̃I�[�o�[���C�h���ꂽ�R���X�g���N�^
// Author : �㓡�T�V��
//============================================================
CScene2D::CScene2D() : CObject()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = DEFAULT_VECTOR;
	m_size = DEFAULT_VECTOR;
	m_nAlphaTestBorder = DEFAULT_ALPHATEST_BORDER_2D;
}

//============================================================
// �V�[�����2D�|���S���̃f�X�g���N�^
// Author : �㓡�T�V��
//============================================================
CScene2D::~CScene2D()
{

}

//============================================================
// �V�[�����2D�|���S���̏���������
// Author : �㓡�T�V��
//============================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����_���[����f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�����т���
	m_pos = pos;

	// �傫�������т���
	m_size = size;

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

												// ���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�i�l��1.0�Őݒ肷��j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[��ݒ�i0.0f�`1.0f�̒l�Őݒ肷��j
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================
// �V�[�����2D�|���S���̏I������
// Author : �㓡�T�V��
//============================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//============================================================
// �V�[�����2D�|���S���̍X�V����
// Author : �㓡�T�V��
//============================================================
void CScene2D::Update(void)
{

}

//=============================================================
// �V�[�����2D�|���S���̕`�揈��
// Author : �r�c�I��i�e�N�X�`���u�����f�B���O�Ή��j�A�㓡�T�V��
//=============================================================
void CScene2D::Draw(void)
{
	// �����_���[����f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �A���t�@�e�X�g�i��⋭���j
	if (m_nAlphaTestBorder != DEFAULT_ALPHATEST_BORDER_2D)
	{
		//�A���t�@�e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		//�A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaTestBorder);
		//�A���t�@�e�X�g�̔�r���@�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	// ���Z����
	if (m_bAdditiveSynthesis)
	{
		// �����_�[�X�e�[�g(���Z�����ɂ���)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}


	// �u�����h���@��߂�
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���]������߂�

	// ���Z������߂�
	if (m_bAdditiveSynthesis)
	{
		// �����_�[�X�e�[�g(���Z������߂�)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// ���Z�����̃t���O��false�ɖ߂�
		m_bAdditiveSynthesis = false;
	}

	// �A���t�@�e�X�g��߂�
	if (m_nAlphaTestBorder != DEFAULT_ALPHATEST_BORDER_2D)
	{
		//�A���t�@�e�X�g�𖳌���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}

	// �e�N�X�`���̐ݒ�̉����@//�r�c�ύX
	pDevice->SetTexture(0, NULL);


}

//=============================================================
// �V�[�����2D�|���S���̃e�N�X�`�������蓖��
// Author : �㓡�T�V���A�r�c�I��
//=============================================================
void CScene2D::BindTexture(const int nNumTexture)
{

}

//=============================================================
// �V�[�����2D�|���S���̒��_���W��ݒ�
// Author : �㓡�T�V��
//=============================================================
void CScene2D::SetVertex(void)
{
	VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

												// ���_���W�̐ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-(m_size.x / 2.0f), -(m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+(m_size.x / 2.0f), -(m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-(m_size.x / 2.0f), +(m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+(m_size.x / 2.0f), +(m_size.y / 2.0f), 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// �V�[�����2D�|���S���̉�]���钸�_���W��ݒ�
// Author : �㓡�T�V��
//=============================================================
void CScene2D::SetRotVertex(float fAngle)
{
	// �ϐ��錾
	// �e���_
	D3DXVECTOR3 vertex1 = DEFAULT_VECTOR;
	D3DXVECTOR3 vertex2 = DEFAULT_VECTOR;
	D3DXVECTOR3 vertex3 = DEFAULT_VECTOR;
	D3DXVECTOR3 vertex4 = DEFAULT_VECTOR;

	//==========================================================================================================
	// �摜���A�摜�̒��S�����ɉ�]������
	// ����̒��_
	vertex1.x = -(m_size.x / 2.0f)*cosf(fAngle)
		- (-(m_size.y / 2.0f))*sinf(fAngle);
	vertex1.y = -(m_size.x / 2.0f)*sinf(fAngle)
		+ (-(m_size.y / 2.0f))*cosf(fAngle);

	// �E��̒��_
	vertex2.x = (m_size.x / 2.0f)*cosf(fAngle)
		- (-(m_size.y / 2.0f))*sinf(fAngle);
	vertex2.y = (m_size.x / 2.0f)*sinf(fAngle)
		+ (-(m_size.y / 2.0f))*cosf(fAngle);

	// �����̒��_
	vertex3.x = -(m_size.x / 2.0f)*cosf(fAngle)
		- (m_size.y / 2.0f)*sinf(fAngle);
	vertex3.y = -(m_size.x / 2.0f)*sinf(fAngle)
		+ (m_size.y / 2.0f)*cosf(fAngle);

	// �E���̒��_
	vertex4.x = (m_size.x / 2.0f)*cosf(fAngle)
		- (m_size.y / 2.0f)*sinf(fAngle);
	vertex4.y = (m_size.x / 2.0f)*sinf(fAngle)
		+ (m_size.y / 2.0f)*cosf(fAngle);
	//==========================================================================================================

	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx = NULL;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = m_pos + vertex1;
	pVtx[1].pos = m_pos + vertex2;
	pVtx[2].pos = m_pos + vertex3;
	pVtx[3].pos = m_pos + vertex4;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// �V�[�����2D�|���S���̌�������̒��_���W��ݒ�
// Author : �㓡�T�V��
//=============================================================
void CScene2D::SetVisualVertex(D3DXVECTOR3 posVisual, D3DXVECTOR3 sizeVisual)
{
	VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

												// ���_���W�̐ݒ�
	pVtx[0].pos = posVisual + D3DXVECTOR3(-(sizeVisual.x / 2.0f), -(sizeVisual.y / 2.0f), 0.0f);
	pVtx[1].pos = posVisual + D3DXVECTOR3(+(sizeVisual.x / 2.0f), -(sizeVisual.y / 2.0f), 0.0f);
	pVtx[2].pos = posVisual + D3DXVECTOR3(-(sizeVisual.x / 2.0f), +(sizeVisual.y / 2.0f), 0.0f);
	pVtx[3].pos = posVisual + D3DXVECTOR3(+(sizeVisual.x / 2.0f), +(sizeVisual.y / 2.0f), 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// �e�N�X�`���̕`��͈͂̐ݒ�
// Author : �㓡�T�V��
//=============================================================
void CScene2D::SetTextureRange(int nRange, int nPattern)
{
	VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

												// �e�N�X�`�����W�̐ݒ�
												// �ϐ��錾
	float fEqualDivision = 0.0f;   // �e�N�X�`���𓙕�����

								   // ���������邩�v�Z
	fEqualDivision = Divide((float)nRange, (float)nPattern);

	// �e�N�X�`���̍��W�𔽉f
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fEqualDivision, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fEqualDivision, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// �e�N�X�`���̕`��ꏊ�����߂�
// Author : �㓡�T�V��
//=============================================================
void CScene2D::SetTexturePlace(int nPlace, int nPattern)
{
	VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

												// �e�N�X�`�����W�̐ݒ�
												// �ϐ��錾
	float fEqualDivision = 0.0f;   // �e�N�X�`���𓙕�����

								   // ���������邩�v�Z
	fEqualDivision = Divide(1.0f, (float)nPattern);

	// �e�N�X�`���̍��W�𔽉f
	pVtx[0].tex = D3DXVECTOR2((fEqualDivision * nPlace), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fEqualDivision + (fEqualDivision * nPlace), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((fEqualDivision * nPlace), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fEqualDivision + (fEqualDivision * nPlace), 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// �V�[�����2D�|���S���̐F��ς���
// Author : �㓡�T�V��
//=============================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[��ݒ�i0.0f�`1.0f�̒l�Őݒ肷��j
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}