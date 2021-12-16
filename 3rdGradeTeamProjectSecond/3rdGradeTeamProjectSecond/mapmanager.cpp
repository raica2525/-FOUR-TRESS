//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	mapmanager.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "mapmanager.h"
#include "json.h"
#include "fileio.h"
#include "bg.h"
#include "block.h"
#include "enemy.h"
#include "ground.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CMapManager::CMapManager()
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CMapManager::~CMapManager()
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMapManager::Init(void)
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMapManager::Update(void)
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMapManager::Uninit(void)
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// JSON�t�@�C������I�u�W�F�N�g�𐶐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMapManager::CreateMapFromJson(std::string filePath)
{
	std::string str;
	CFileIO::Load(&str, filePath);
	picojson::object obj = CJson::FromJson(str);
	
	picojson::array arr = obj["buildings"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateBgFromJsonObject(it->get<picojson::object>());
	}

	picojson::array arr = obj["blocks"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateBlockFromJsonObject(it->get<picojson::object>());
	}

	picojson::array arr = obj["enemys"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateEnemyFromJsonObject(it->get<picojson::object>());
	}

	picojson::array arr = obj["collisions"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateCollisionFromJsonObject(it->get<picojson::object>());
	}

	picojson::array arr = obj["grounds"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateGroundFromJsonObject(it->get<picojson::object>());
	}

	picojson::object spawn = obj["spawn"].get<picojson::object>();
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(spawn, "pos"));
	//�X�|�[���n�_�ݒ�
} 

CBg* CMapManager::CreateBgFromJsonObject(picojson::object obj)
{
	D3DXVECTOR3 pos			= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot			= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));
	D3DXVECTOR3 size		= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	D3DCOLOR col			= CJson::ArrayToD3DCol(CJson::Nullcheck<picojson::array>(obj, "col"));
	std::string modelname	= CJson::Nullcheck<std::string>(obj, "modelname");

	return CBg::Create();
}

CBlock* CMapManager::CreateBlockFromJsonObject(picojson::object obj)
{
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	D3DCOLOR col = CJson::ArrayToD3DCol(CJson::Nullcheck<picojson::array>(obj, "col"));
	std::string modelname = CJson::Nullcheck<std::string>(obj, "modelname");
	bool bBreakable = CJson::Nullcheck<bool>(obj, "breakable");;
	bool bGoalObject = CJson::Nullcheck<bool>(obj, "goal");

	picojson::object collObj = obj["collision"].get<picojson::object>();
	D3DXVECTOR3 collPos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(collObj, "pos"));
	D3DXVECTOR3 collSize = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(collObj, "size"));
	return CBlock::Create();
}

CEnemy* CMapManager::CreateEnemyFromJsonObject(picojson::object obj)
{
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	std::string modelname = CJson::Nullcheck<std::string>(obj, "modelname");
	float fStrength = (float)CJson::Nullcheck<double>(obj, "strength");
	CEnemy::APPEAR_STATE appearState = (CEnemy::APPEAR_STATE)(int)CJson::Nullcheck<double>(obj, "appearstate");
	float fChargeValue = (float)CJson::Nullcheck<double>(obj, "chargevalue");
	float fSearchDistance = (float)CJson::Nullcheck<double>(obj, "searchdistance");
	return CEnemy::Create();
}

CBlock* CMapManager::CreateCollisionFromJsonObject(picojson::object obj)
{
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));

	return CBlock::Create();
}

CGround* CMapManager::CreateGroundFromJsonObject(picojson::object obj)
{
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	float fAngle = (float)CJson::Nullcheck<double>(obj, "angle");
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	std::string textureName = CJson::Nullcheck<std::string>(obj, "texturename");

	return CGround::Create(pos,fAngle,size,textureName);
}