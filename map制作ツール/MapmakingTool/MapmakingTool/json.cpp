//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	json.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "json.h"

const CManager::BUILDING CJson::DEFAULT_BUILDING =
{
	"New Building",					//name
	ZERO_VEC,						//pos
	ZERO_VEC,						//rot
	{1,1,1},						//size
	D3DCOLOR_RGBA(255,255,255,255),	//col
	NOT_EXIST,						//nModelNum
	NOT_EXIST						//nCollisionIndex
};

void CJson::ToJson()
{
	picojson::object obj;
	obj.emplace();
}

picojson::object CJson::FromJson(char* src)
{
	picojson::value value;
	picojson::parse(value, src);
	picojson::object obj = value.get<picojson::object>();
	picojson::array arr = obj["buildings"].get<picojson::array>();

	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		picojson::object building = it->get<picojson::object>();
		std::string name = Nullcheck<std::string>(building, "name");

		int nCollisionIndex = Nullcheck<double>(building, "collisionindex");

		D3DXVECTOR3 pos = ArrayToD3DXVec3(Nullcheck<picojson::array>(building, "pos"));
		D3DXVECTOR3 rot = ArrayToD3DXVec3(Nullcheck<picojson::array>(building, "rot"));
		D3DXVECTOR3 size = ArrayToD3DXVec3(Nullcheck<picojson::array>(building, "size"));
		D3DCOLOR col = ArrayToD3DCol(Nullcheck<picojson::array>(building, "col"));
	}
	return obj;
}

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

picojson::object CJson::BuildingDataToJsonObject(CManager::BUILDING building)
{
	picojson::object obj;
	picojson::array pos, rot, size,col;

	//D3DXVECTOR3をpicojsonの配列に変換
	for (int nCount = 0; nCount < 3; nCount++)
	{
		pos.push_back(picojson::value(building.pos[nCount]));
		rot.push_back(picojson::value(building.rot[nCount]));
		size.push_back(picojson::value(building.size[nCount]));
		col.push_back(picojson::value((double)(building.col & 0xff << ((2 - nCount) * 8) )));
	}
	//オブジェクトに入力
	obj.insert(std::make_pair("name", building.name));
	obj.insert(std::make_pair("pos", pos));
	obj.insert(std::make_pair("rot", size));
	obj.insert(std::make_pair("col", col));
	obj.insert(std::make_pair("modelnum", picojson::value((double)building.nModelNum)));
	obj.insert(std::make_pair("collisionindex", picojson::value((double)building.nCollisionIndex)));
	return obj;
}
