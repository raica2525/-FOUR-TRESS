//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _SCENE_H_
#define _SCENE_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�v���g�^�C�v�錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define PRIORITY_MAX	(3)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
	}OBJTYPE;

	CScene(int nPriority = 1);
	virtual ~CScene();
	virtual HRESULT Init(void)	= 0;		//�������z�֐��Q
	virtual void Uninit(void)	= 0;
	virtual void Update(void)	= 0;
	virtual void Draw(void)		= 0;

	static void UpdateAll(void);		//�S�V�[�������Q
	static void DrawAll(void);
	static void ReleaseAll(void);

	void SetObjType(OBJTYPE type)	{ m_objType = type; }
	static CScene** GetTop(void)	{ return m_pTop; }
	CScene* GetNext(void)			{ return m_pNext; }
	CScene* GetPrev(void)			{ return m_pPrev; }
	OBJTYPE GetObjType(void)		{ return m_objType; }

protected:
	void Release(void);					//�V�[���̊J��

private:
	void Death(void);
	static CScene* m_pTop[PRIORITY_MAX];
	static CScene* m_pCur[PRIORITY_MAX];
	CScene* m_pPrev;
	CScene* m_pNext;
	int m_nPriority;
	bool m_bDestroy;
	OBJTYPE m_objType;
};

#endif
