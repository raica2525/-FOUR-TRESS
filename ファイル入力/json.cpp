//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	json.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "json.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ�������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
const CManager::BUILDING CJson::DEFAULT_BUILDING =
{
	"New Building",					//name
	ZERO_VEC,						//pos
	ZERO_VEC,						//rot
	{1,1,1},						//size
	D3DCOLOR_RGBA(255,255,255,255),	//col
	{},							//modelname
	NOT_EXIST						//nCollisionIndex
};

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//JsonObject�`���ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CJson::ToJson()
{
	picojson::object obj;
	obj.emplace();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//MapObject�`���ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
picojson::object CJson::FromJson(std::string src)
{
	picojson::value value;
	picojson::parse(value, src);
	picojson::object obj = value.get<picojson::object>();
	return obj;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�z���D3DXVECTOR3�ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CJson::ArrayToD3DXVec3(picojson::array arr)
{
	int nCount = 0;
	D3DXVECTOR3 vec;
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++, nCount++)
	{
		vec[nCount] = (float)it->get<double>();
	}
	return vec;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�z���F���ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DCOLOR CJson::ArrayToD3DCol(picojson::array arr)
{
	int nCount = 0;
	D3DCOLOR col = 0;
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++, nCount++)
	{
		col += (int)it->get<double>();
	}
	col += D3DCOLOR_RGBA(0, 0, 0, 255);
	return col;
}

//TODO MapManager�Ɉړ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�b�v�I�u�W�F�N�g��JsonObject�ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
picojson::object CJson::BuildingDataToJsonObject(CManager::BUILDING building)
{
	picojson::object obj;
	picojson::array pos, rot, size,col;

	//D3DXVECTOR3��picojson�̔z��ɕϊ�
	for (int nCount = 0; nCount < 3; nCount++)
	{
		pos.push_back(picojson::value(building.pos[nCount]));
		rot.push_back(picojson::value(building.rot[nCount]));
		size.push_back(picojson::value(building.size[nCount]));
		col.push_back(picojson::value((double)(building.col & 0xff << ((2 - nCount) * 8) )));
	}
	//�I�u�W�F�N�g�ɓ���
	obj.insert(std::make_pair("name", building.name));
	obj.insert(std::make_pair("pos", pos));
	obj.insert(std::make_pair("rot", size));
	obj.insert(std::make_pair("col", col));
	obj.insert(std::make_pair("modelname", picojson::value(building.modelName)));
	obj.insert(std::make_pair("collisionindex", picojson::value((double)building.nCollisionIndex)));
	return obj;
}
