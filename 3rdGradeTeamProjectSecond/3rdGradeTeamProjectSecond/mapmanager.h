//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	mapmanager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・


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

};

#endif // !_MAPMANAGER_H_
