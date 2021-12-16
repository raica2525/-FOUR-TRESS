//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	json.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "json.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//JsonObject形式に変換
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
std::string CJson::ToJson(picojson::object& obj)
{
	return picojson::value(obj).serialize(true);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//object形式に変換
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

picojson::array CJson::D3DXVec3ToArray(D3DXVECTOR3 vec3)
{
	picojson::array arr;
	for (int nCount = 0; nCount < 3; nCount++)
	{
		arr.push_back(picojson::value(vec3[nCount]));
	}
	return arr;
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
		col += (int)it->get<double>() << (16 - 8 * nCount);
	}
	col += D3DCOLOR_RGBA(0, 0, 0, 255);
	return col;
}

picojson::array CJson::D3DColToArray(D3DCOLOR col)
{
	picojson::array arr;
	for (int nCount = 0; nCount < 3; nCount++)
	{
		arr.push_back(picojson::value((double)((col & (0xff << ((2 - nCount) * 8))) >> ((2 - nCount) * 8))));
	}
	return arr;
}