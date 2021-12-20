//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	json.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _JSON_H_
#define _JSON_H_

#include "main.h"
#include "picojson.h"
#include "manager.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CJson
{
public:
	static std::string ToJson(picojson::object& obj);
	static picojson::object FromJson(std::string src);

	static D3DXVECTOR3 ArrayToD3DXVec3(picojson::array arr);
	static picojson::array D3DXVec3ToArray(D3DXVECTOR3 vec3);
	static D3DCOLOR ArrayToD3DCol(picojson::array arr);
	static picojson::array D3DColToArray(D3DCOLOR col);
	template<typename T> static T Nullcheck(picojson::object& obj, const char* key)
	{
		//if (obj[key].is<picojson::null>())
		//{
		//	return NULL;
		//}
		//else
		//{
			return obj[key].get<T>();
		//}
	};

private:

	CJson();		//コンストラクタ
};

#endif

