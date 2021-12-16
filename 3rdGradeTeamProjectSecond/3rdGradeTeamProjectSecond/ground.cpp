//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	ground.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "ground.h"
#include "manager.h"
#include "polygon3d.h"
#include "texturemanager.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
const float CGround::DEFAULT_SIZE = 500.0f;
const std::string CGround::DEFAULT_NAME = "Ground";
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGround::CGround()
{
	m_fAngle = 0.0f;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGround::~CGround()
{

}



//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CGround::Update(void)
{
	pPolygon3D->SetPos(GetPos());
	pPolygon3D->SetSize(GetSize());
	pPolygon3D->SetRot(D3DXVECTOR3(90.0f, m_fAngle, 0.0f));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CGround::Uninit(void)
{
	if (pPolygon3D != NULL)
	{
		pPolygon3D->Uninit();
		pPolygon3D = NULL;
	}

	CMapObject::Uninit();
}

void CGround::SetTexKey(const std::string &key)
{
	m_texKey = key;
	pPolygon3D->BindTexture(CManager::GetTextureManager()->GetTexture(key));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �f�t�H���g��������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGround* CGround::CreateDefault(void)
{
	CGround* pGround = new CGround;
	pGround->m_name = DEFAULT_NAME;
	pGround->SetSize(D3DXVECTOR3(DEFAULT_SIZE, DEFAULT_SIZE, 0.0f));
	pGround->pPolygon3D = CPolygon3D::Create(ZERO_VEC, D3DXVECTOR3(90.0f, 0.0f, 0.0f), pGround->GetSize());
	return pGround;
}

CGround* CGround::Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR3 size, std::string name, std::string textureName)
{
	CGround* pGround = new CGround;
	pGround->m_fAngle = fAngle;
	pGround->m_name = name;
	pGround->SetPos(pos);
	pGround->SetSize(size);
	pGround->pPolygon3D = CPolygon3D::Create(pos, D3DXVECTOR3(90.0f, fAngle, 0.0f),size);
	pGround->SetTexKey(textureName);
	return pGround;
}

