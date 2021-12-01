//================================================
//
// �O���b�h�̏��� (grid.cpp)
// Author : �ɓ��z��
//
//================================================

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "grid.h"
#include "manager.h"
#include "renderer.h"

//================================================
// �}�N����`
//================================================
#define MAX_GRID_LINE_NUM (11)							// �O���b�h�̐��̍ő吔
#define GRID_DISTANCE_SIZE (100.0f)						// �O���b�h���Ƃ̊Ԋu
#define GRID_SIDE_SIZE (GRID_DISTANCE_SIZE * 10.0f)		// �O���b�h�̈�{���̒���
#define GRID_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// �O���b�h�̐F
#define AXIS_VERTEX_NUM (22)							// �����ƂɎg�����_�̐�
#define ZX_AXIS_LINE (0)
#define XY_AXIS_LINE (1)
#define YZ_AXIS_LINE (2)


//=============================================================================
// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
//=============================================================================
CGrid::CGrid(CScene::OBJTYPE objtype) :CScene(objtype)
{
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = DEFAULT_VECTOR;
	m_fsize = GRID_DISTANCE_SIZE;
	m_fAllsize = GRID_SIDE_SIZE;
	m_col = GRID_COLOR;
	m_fDistance = 0.0f;
	memset(m_bShow, true, sizeof(m_bShow));
}

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGrid::CGrid()
{
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = DEFAULT_VECTOR;
	m_fsize = GRID_DISTANCE_SIZE;
	m_fAllsize = GRID_SIDE_SIZE;
	m_col = GRID_COLOR;
	m_fDistance = 0.0f;
	memset(m_bShow, true, sizeof(m_bShow));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGrid::~CGrid()
{
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = DEFAULT_VECTOR;
	m_fsize = 0.0f;
	m_fAllsize = 0.0f;
	m_col = GRID_COLOR;
	m_fDistance = 0.0f;
	memset(m_bShow, true, sizeof(m_bShow));
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CGrid * CGrid::Create()
{
	CGrid* pGrid = nullptr;

	if (pGrid == nullptr)
	{
		pGrid = new CGrid(OBJTYPE_GRID);

		// ������
		pGrid->Init();
	}

	return pGrid;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGrid::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AXIS_VERTEX_NUM * 6, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGrid::Uninit(void)
{
	// ���_�o�b�t�@���J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �V�[���̊J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGrid::Update(void)
{
	// ��ӂ��Ƃ̑傫���̍��v
	m_fAllsize = m_fsize * (MAX_GRID_LINE_NUM - 1);

	// ���������Ƃ��̊Ԋu
	m_fDistance = m_fAllsize / (MAX_GRID_LINE_NUM - 1);

	VERTEX_3D *pVtx = NULL;	// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	// �e���_�̐F�Ɩ@���x�N�g�����X�V
	for (int nCount = 0; nCount < AXIS_VERTEX_NUM * 6; nCount++)
	{
		// �e���_�̃e�N�X�`�����W���X�V
		pVtx[nCount].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCount].col = m_col;
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	for (int nCount = 0; nCount < MAX_GRID_LINE_NUM; nCount++)
	{
		// ���������Ԋu
		float fDistance = (m_fAllsize / 2) - (nCount * m_fDistance);

		ZXAxisLine(pVtx, nCount, fDistance);	// ZX���̐�
		XYAxisLine(pVtx, nCount, fDistance);	// XY���̐�
		YZAxisLine(pVtx, nCount, fDistance);	// YZ���̐�
	}

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGrid::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ���C�g�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	// Z�o�b�t�@�𖳌���
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NUM_POLYGON * MAX_GRID_LINE_NUM * 3);

	// �e�N�X�`����NULL��
	pDevice->SetTexture(0, NULL);

	// Z�o�b�t�@��L����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���C�g��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ZX���̐�
//=============================================================================
void CGrid::ZXAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance)
{
	// Z���ɕ��s�Ȑ�
	ZAxisLine(pVtx, nCount, 0, D3DXVECTOR3(fDistance, 0.0f, 0.0f));

	// X���ɕ��s�Ȑ�
	XAxisLine(pVtx, nCount, AXIS_VERTEX_NUM, D3DXVECTOR3(0.0f, 0.0f, fDistance));

	// ����\�����邩���Ȃ���
	ShowLine(pVtx, nCount, 0, ZX_AXIS_LINE);
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM, ZX_AXIS_LINE);
}

//=============================================================================
// XY���̐�
//=============================================================================
void CGrid::XYAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance)
{
	// X���ɕ��s�Ȑ�
	XAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 2, D3DXVECTOR3(0.0f, fDistance, 0.0f));

	// Y���ɕ��s�Ȑ�
	YAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 3, D3DXVECTOR3(fDistance, 0.0f, 0.0f));

	// ����\�����邩���Ȃ���
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 2, XY_AXIS_LINE);
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 3, XY_AXIS_LINE);
}

//=============================================================================
// YZ���̐�
//=============================================================================
void CGrid::YZAxisLine(VERTEX_3D* pVtx, const int nCount, const float fDistance)
{
	// Y���ɕ��s�Ȑ�
	YAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 4, D3DXVECTOR3(0.0f, 0.0f, fDistance));

	// Z���ɕ��s�Ȑ�
	ZAxisLine(pVtx, nCount, AXIS_VERTEX_NUM * 5, D3DXVECTOR3(0.0f, fDistance, 0.0f));

	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 4, YZ_AXIS_LINE);
	ShowLine(pVtx, nCount, AXIS_VERTEX_NUM * 5, YZ_AXIS_LINE);
}

//=============================================================================
// X���̐�
//=============================================================================
void CGrid::XAxisLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance)
{
	// X���ɕ��s�Ȑ�
	// ���_���W�̐ݒ�
	pVtx[(nCount * 2) + nVertex].pos = m_pos + Distance + D3DXVECTOR3(-m_fAllsize, 0.0f, 0.0f) / 2.0f;
	pVtx[(nCount * 2) + nVertex + 1].pos = m_pos + Distance + D3DXVECTOR3(m_fAllsize, 0.0f, 0.0f) / 2.0f;

	// ���S�̐���Ԃ�
	if (nCount == 5)
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

//=============================================================================
// Y���̐�
//=============================================================================
void CGrid::YAxisLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance)
{
	// Y���ɕ��s�Ȑ�
	// ���_���W�̐ݒ�
	pVtx[(nCount * 2) + nVertex].pos = m_pos + Distance + D3DXVECTOR3(0.0f, -m_fAllsize, 0.0f) / 2.0f;
	pVtx[(nCount * 2) + nVertex + 1].pos = m_pos + Distance + D3DXVECTOR3(0.0f, m_fAllsize, 0.0f) / 2.0f;

	// ���S�̐���΂�
	if (nCount == 5)
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
}

//=============================================================================
// Z���̐�
//=============================================================================
void CGrid::ZAxisLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const D3DXVECTOR3 Distance)
{
	// Z���ɕ��s�Ȑ�
	// ���_���W�̐ݒ�
	pVtx[(nCount * 2) + nVertex].pos = m_pos + Distance + D3DXVECTOR3(0.0f, 0.0f, -m_fAllsize) / 2.0f;
	pVtx[(nCount * 2) + nVertex + 1].pos = m_pos + Distance + D3DXVECTOR3(0.0f, 0.0f, m_fAllsize) / 2.0f;

	// ���S�̐����
	if (nCount == 5)
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
// ����\�����邩���Ȃ���
//=============================================================================
void CGrid::ShowLine(VERTEX_3D * pVtx, const int nCount, const int nVertex, const int nAxisLine)
{
	if (!m_bShow[nAxisLine])
	{
		pVtx[(nCount * 2) + nVertex].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 2) + nVertex + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �傫���̎擾
//=============================================================================
float & CGrid::GetSize(void)
{
	return m_fsize;
}

//=============================================================================
// �O���b�h��\�����邩���Ȃ������擾
//=============================================================================
bool & CGrid::GetbShowLine(const int nAxisLine)
{
	return m_bShow[nAxisLine];
}
