//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	json.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "json.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//JsonObject�`���ɕϊ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
std::string CJson::ToJson(picojson::object& obj)
{
	return picojson::value(obj).serialize(true);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//object�`���ɕϊ�
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

picojson::array CJson::D3DXVec3ToArray(D3DXVECTOR3 vec3)
{
	picojson::array arr;
	for (int nCount = 0; nCount < 3; nCount++)
	{
		arr.push_back(picojson::value(vec3[nCount]));
	}
	return arr;
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