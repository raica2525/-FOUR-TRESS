//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	json.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _JSON_H_
#define _JSON_H_

#include "main.h"
#include "picojson.h"
#include "manager.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CJson
{
public:
	static void ToJson();
	static picojson::object FromJson(char* src);
private:

	CJson();		//�R���X�g���N�^
	static D3DXVECTOR3 ArrayToD3DXVec3(picojson::array arr);
	static D3DCOLOR ArrayToD3DCol(picojson::array arr);
	static picojson::object BuildingDataToJsonObject(CManager::BUILDING building);

	template<typename T> static T Nullcheck(picojson::object& obj, const char* key)
	{
		picojson::object defaultBuilding = BuildingDataToJsonObject(DEFAULT_BUILDING);
		if (obj[key].is<picojson::null>())
		{
			return defaultBuilding[key].get<T>();
		}
		else
		{
			return obj[key].get<T>();
		}
	};
	static const CManager::BUILDING DEFAULT_BUILDING;
};

#endif

