//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	mapmanager.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "mapmanager.h"
#include "json.h"
#include "fileio.h"
#include "bg.h"
#include "block.h"
#include "enemy.h"
#include "ground.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CMapManager::CMapManager()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CMapManager::~CMapManager()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMapManager::Init(void)
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMapManager::Update(void)
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMapManager::Uninit(void)
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// JSONファイルからオブジェクトを生成
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMapManager::CreateMapFromJson(std::string filePath)
{
	std::string str;
	CFileIO::Load(&str, filePath);
	picojson::object obj = CJson::FromJson(str);
	
	// BGを生成
	picojson::array arr = obj["buildings"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateBgFromJsonObject(it->get<picojson::object>());
	}

	// Blockを生成
	arr = obj["blocks"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateBlockFromJsonObject(it->get<picojson::object>());
	}

	// enemyを生成
	arr = obj["enemys"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateEnemyFromJsonObject(it->get<picojson::object>());
	}

	// collisionを生成
	arr = obj["collisions"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateCollisionFromJsonObject(it->get<picojson::object>());
	}

	// groundを生成
	obj["grounds"].get<picojson::array>();
	for (picojson::array::iterator it = arr.begin(); it < arr.end(); it++)
	{
		CreateGroundFromJsonObject(it->get<picojson::object>());
	}

	// スポーン地点を設定
	picojson::object spawn = obj["spawn"].get<picojson::object>();
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(spawn, "pos"));
	// TODO スポーン地点設定
} 

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// BGを生成
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CBg* CMapManager::CreateBgFromJsonObject(picojson::object obj)
{
	// 各種情報を変数に変換
	D3DXVECTOR3 pos			= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot			= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));
	D3DXVECTOR3 size		= CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	D3DCOLOR col			= CJson::ArrayToD3DCol(CJson::Nullcheck<picojson::array>(obj, "col"));
	std::string modelname	= CJson::Nullcheck<std::string>(obj, "modelname");

	// オブジェクトの生成
	return CBg::Create();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// blockを生成
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CBlock* CMapManager::CreateBlockFromJsonObject(picojson::object obj)
{
	// 各種情報を変数に変換
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 rot = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "rot"));
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	D3DCOLOR col = CJson::ArrayToD3DCol(CJson::Nullcheck<picojson::array>(obj, "col"));
	std::string modelname = CJson::Nullcheck<std::string>(obj, "modelname");
	bool bBreakable = CJson::Nullcheck<bool>(obj, "breakable");;
	bool bGoalObject = CJson::Nullcheck<bool>(obj, "goal");

	// 当たり判定
	picojson::object collObj = obj["collision"].get<picojson::object>();
	D3DXVECTOR3 collPos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(collObj, "pos"));
	D3DXVECTOR3 collSize = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(collObj, "size"));

	//オブジェクトの生成
	return CBlock::Create();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// enemyを生成
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CEnemy* CMapManager::CreateEnemyFromJsonObject(picojson::object obj)
{
	// 各種情報を変数に変換
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	std::string modelname = CJson::Nullcheck<std::string>(obj, "modelname");
	float fStrength = (float)CJson::Nullcheck<double>(obj, "strength");
	CEnemy::APPEAR_STATE appearState = (CEnemy::APPEAR_STATE)(int)CJson::Nullcheck<double>(obj, "appearstate");
	float fChargeValue = (float)CJson::Nullcheck<double>(obj, "chargevalue");
	float fSearchDistance = (float)CJson::Nullcheck<double>(obj, "searchdistance");

	// オブジェクトの生成
	return CEnemy::Create();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// collisionを生成（Blockとして)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CBlock* CMapManager::CreateCollisionFromJsonObject(picojson::object obj)
{
	// 各種情報を変数に変換
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));

	// オブジェクトの生成
	return CBlock::Create();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// groundを生成
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGround* CMapManager::CreateGroundFromJsonObject(picojson::object obj)
{
	// 各種情報を変数に変換
	D3DXVECTOR3 pos = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "pos"));
	float fAngle = (float)CJson::Nullcheck<double>(obj, "angle");
	D3DXVECTOR3 size = CJson::ArrayToD3DXVec3(CJson::Nullcheck<picojson::array>(obj, "size"));
	std::string textureName = CJson::Nullcheck<std::string>(obj, "texturename");

	// オブジェクトの生成
	return CGround::Create(pos,fAngle,size,textureName);
}