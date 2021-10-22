//===============================================
//
// �����̏��� (building.cpp)
// Author : �����N�m
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"

//========================
// �R���X�g���N�^
//========================
CEnemy::CEnemy() 
{
}

//========================
// �f�X�g���N�^
//========================
CEnemy::~CEnemy() 
{
}

//========================
// ����������
//========================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) 
{
	CScene3D::Init(pos, scale);

	SetScale(scale);

	return S_OK;
}

//========================
// �X�V����
//========================
void CEnemy::Update() 
{

}

//========================
// �`�揈��
//========================
void CEnemy::Draw() 
{
	// �X�e���V���o�b�t�@���g��
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Z�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// Z�e�X�g��K�����s��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

	// �X�e���V���e�X�g�L��
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// �X�e���V���o�b�t�@�֔��f����Q�ƒl
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	// �Q�ƒl�}�X�N
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	// �X�e���V���e�X�g��K��������
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// �X�e���V���e�X�g�̃e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// �ʏ�̕`��̑O��ŁA�X�P�[����������
	D3DXVECTOR3 memoryScale = GetScale();
	CScene3D::Draw(false, false);
	SetScale(memoryScale);

	// �X�e���V���e�X�g����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// ZBUFFER��r�ݒ�ύX => (�Q�ƒl <= �o�b�t�@�l)(�߂�)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �ʏ�̕`��
	CScene3D::Draw(false, false);
}

//========================
// �I������
//========================
void CEnemy::Uninit() 
{
	CScene3D::Uninit();
}

//========================
// ��������
//========================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot) 
{
	// �|�C���^��p��
	CEnemy *pEnemy = NULL;

	// �������m��
	pEnemy = new CEnemy;

	// ������
	pEnemy->Init(pos, scale);

	// �����ݒ�
	pEnemy->SetRot(rot);

	return pEnemy;
}