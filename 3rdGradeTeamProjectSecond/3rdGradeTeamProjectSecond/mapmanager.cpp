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
#include "road.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CMapManager::CMapManager()
{
    m_startPos = DEFAULT_VECTOR;
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
	picojson::array arr;
	// BG�𐶐�
	if (!obj["buildings"].is<picojson::null>())
	{
		arr = obj["buildings"].get<picojson::array>();
		for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
		{
			CreateBgFromJsonObject(it->get<picojson::object>());
		}
	}

	// Block�𐶐�
	if (!obj["blocks"].is<picojson::null>())
	{
		arr = obj["blocks"].get<picojson::array>();
		for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
		{
			CreateBlockFromJsonObject(it->get<picojson::object>());
		}
	}

	// enemy�𐶐�
	if (!obj["enemys"].is<picojson::null>())
	{
		arr = obj["enemys"].get<picojson::array>();
		for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
		{
			CreateEnemyFromJsonObject(it->get<picojson::object>());
		}
	}

	// collision�𐶐�
	if (!obj["collisions"].is<picojson::null>())
	{
		arr = obj["collisions"].get<picojson::array>();
		for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
		{
			CreateCollisionFromJsonObject(it->get<picojson::object>());
		}
	}

	// ground�𐶐�
	if (!obj["grounds"].is<picojson::null>())
	{
		arr = obj["grounds"].get<picojson::array>();
		for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
		{
			CreateGroundFromJsonObject(it->get<picojson::object>());
		}
	}

	// road�𐶐�
	if (!obj["roads"].is<picojson::null>())
	{
		arr = obj["roads"].get<picojson::array>();
		for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
		{
			CreateRoadFromJsonObject(it->get<picojson::object>());
		}
	}

	// �X�|�[���n�_��ݒ�
	if (!obj["spawn"].is<picojson::null>())
	{
		picojson::object spawn = obj["spawn"].get<picojson::object>();
		m_startPos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(spawn, "pos"));
	}
} 

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// BG�𐶐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CBg* CMapManager::CreateBgFromJsonObject(picojson::object obj)
{
	// �e�����ϐ��ɕϊ�
	D3DXVECTOR3 pos			= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot			= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));
	D3DXVECTOR3 size		= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	D3DCOLOR col			= CJson::ArrayToD3DCol(CJson::Nullcheck<picojson::array>(obj, "col"));
	std::string modelname	= CJson::Nullcheck<std::string>(obj, "modelname");

	// �I�u�W�F�N�g�̐���
	return CBg::Create(CManager::GetModelData()->GetIndexByName(modelname), pos);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// block�𐶐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CBlock* CMapManager::CreateBlockFromJsonObject(picojson::object obj)
{
	// �e�����ϐ��ɕϊ�
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	D3DCOLOR col = CJson::ArrayToD3DCol(CJson::Nullcheck<picojson::array>(obj, "col"));
	std::string modelname = CJson::Nullcheck<std::string>(obj, "modelname");
	bool bBreakable = CJson::Nullcheck<bool>(obj, "breakable");;
	bool bGoalObject = CJson::Nullcheck<bool>(obj, "goal");

	// �����蔻��
	picojson::object collObj = obj["collision"].get<picojson::object>();
	D3DXVECTOR3 collPos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(collObj, "pos"));
	D3DXVECTOR3 collSize = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(collObj, "size"));

	//�I�u�W�F�N�g�̐����i�����蔻��̈ʒu�A���炷�H�j
	return CBlock::Create(CManager::GetModelData()->GetBlockTypeByName(bBreakable, bGoalObject), pos, collSize, rot);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// enemy�𐶐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnemy* CMapManager::CreateEnemyFromJsonObject(picojson::object obj)
{
	// �e�����ϐ��ɕϊ�
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	std::string modelname = CJson::Nullcheck<std::string>(obj, "modelname");
	float fStrength = (float)CJson::Nullcheck<double>(obj, "strength");
	CEnemy::APPEAR_STATE appearState = (CEnemy::APPEAR_STATE)(int)CJson::Nullcheck<double>(obj, "appearstate");
	float fChargeValue = (float)CJson::Nullcheck<double>(obj, "chargevalue");
	float fSearchDistance = (float)CJson::Nullcheck<double>(obj, "searchdistance");

	// �I�u�W�F�N�g�̐����i�T�[�`�����́A�f�t�H���g�����ŌŒ肵���j
    return CEnemy::Create(CManager::GetModelData()->GetEnemyTypeByName(modelname), pos, fStrength, appearState, fChargeValue);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// collision�𐶐��iBlock�Ƃ���)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CBlock* CMapManager::CreateCollisionFromJsonObject(picojson::object obj)
{
	// �e�����ϐ��ɕϊ�
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));

	// �I�u�W�F�N�g�̐���
	return CBlock::Create(CBlock::TYPE_FRAME, pos, size, DEFAULT_VECTOR);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// ground�𐶐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGround* CMapManager::CreateGroundFromJsonObject(picojson::object obj)
{
	// �e�����ϐ��ɕϊ�
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	float fAngle = (float)CJson::Nullcheck<double>(obj, "angle");
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	std::string textureName = CJson::Nullcheck<std::string>(obj, "texturename");

	// �I�u�W�F�N�g�̐���
	return CGround::Create(pos,fAngle,size,textureName);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// Road�𐶐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRoad* CMapManager::CreateRoadFromJsonObject(picojson::object obj)
{
	// �e�����ϐ��ɕϊ�
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));

	// �I�u�W�F�N�g�̐���
	return CRoad::Create(pos, rot);
}