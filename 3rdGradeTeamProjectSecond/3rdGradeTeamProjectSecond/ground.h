//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	ground.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _GROUND_H_
#define _GROUND_H_

#include "polygon3d.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CGround : public CPolygon3D
{
public:
	CGround();		//コンストラクタ
	~CGround();

	void Update(void);
	void Uninit(void);

	void SetAngle(const float fAngle) { m_fAngle = fAngle; }
	void SetName(const std::string &name) { m_name = name; }
	void SetTexKey(const std::string &key);
	float GetAngle(void) const { return m_fAngle; }
	std::string GetName(void) const { return m_name; }
	std::string GetTexKey(void) const { return m_texKey; }
	static CGround* Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR3 size, std::string textureName);
	
private:
	float m_fAngle;
	std::string m_name;
	std::string m_texKey;
	static const float DEFAULT_SIZE;
	static const std::string DEFAULT_NAME;
};

#endif

