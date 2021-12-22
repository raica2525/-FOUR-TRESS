//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	mapmanager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "json.h"
#include <string>

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CBg;
class CBlock;
class CEnemy;
class CGround;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

    D3DXVECTOR3 GetStartPos(void) { return m_startPos; }

private:
    D3DXVECTOR3 m_startPos; // スタート地点
};

#endif // !_MAPMANAGER_H_
