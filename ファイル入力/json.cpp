//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	json.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "json.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数初期化
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//JsonObject形式に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CJson::ToJson()
{
	picojson::object obj;
	obj.emplace();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//MapObject形式に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
picojson::object CJson::FromJson(std::string src)
{
	picojson::value value;
	picojson::parse(value, src);
	picojson::object obj = value.get<picojson::object>();
	return obj;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//配列をD3DXVECTOR3に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//配列を色情報に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

//TODO MapManagerに移動
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マップオブジェクトをJsonObjectに変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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
	obj.insert(std::make_pair("modelname", picojson::value(building.modelName)));
	obj.insert(std::make_pair("collisionindex", picojson::value((double)building.nCollisionIndex)));
	return obj;
}
