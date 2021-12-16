//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	mapmanager.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

#include "main.h"
#include <string>
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CBg;
class CBlock;
class CEnemy;
class CGround;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// �N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CMapManager
{
public:
	CMapManager();
	~CMapManager();

	void Init(void);
	void Update(void);
	void Uninit(void);

	void CreateMapFromJson(std::string filePath);
	CBg* CreateBgFromJsonObject(picojson::object obj);
	CBlock* CreateBlockFromJsonObject(picojson::object obj);
	CEnemy* CreateEnemyFromJsonObject(picojson::object obj);
	CBlock* CreateCollisionFromJsonObject(picojson::object obj);
	CGround* CreateGroundFromJsonObject(picojson::object obj);
};

#endif // !_MAPMANAGER_H_
