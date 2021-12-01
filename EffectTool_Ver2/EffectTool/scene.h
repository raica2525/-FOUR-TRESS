//====================================================================
//
// �V�[����̃I�u�W�F�N�g���� (scene.h)
// Author : �ɓ��z��
//
//====================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================

//================================================
// �N���X�錾
//================================================

// �I�u�W�F�N�g�̃N���X
class CScene
{
public:
	// �I�u�W�F�N�g�̎��(�`�揇)
	typedef enum
	{
		OBJTYPE_NONE,				// �Ȃ�
		OBJTYPE_GRID,				// �O���b�h
		OBJTYPE_EFFECT3D,			// �G�t�F�N�g3D
		OBJTYPE_EFFECT3D_Z_NONE,	// �G�t�F�N�g3D�AZ�o�b�t�@�Ȃ�
		OBJTYPE_MAX					// �I�u�W�F�N�g�̎�ނ̍ő吔
	}OBJTYPE;

	CScene();
	CScene(OBJTYPE objType);	// �C�j�V�����C�U�ŃI�u�W�F�N�g�^�C�v��R�Â�
	virtual ~CScene();			// �e�N���X�̃f�X�g���N�^��virtual�����邱�ƂŁA���������[�N��}����
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);											// �S�čX�V
	static void DrawAll(void);												// �S�ĕ`��
	static void QuickSort(CScene*apScene[], int left, int right);			// �N�C�b�N�\�[�g
	static void ReleaseAll(void);											// �S�ĊJ��

	static int GetNumObjAll(void) { return m_nNumObjectAll; }				// �V�[����̑S�ẴI�u�W�F�N�g��
	static int GetNumAll(OBJTYPE objtype) { return m_nNumAll[objtype]; }	// ���̎�ނ̑S�̂̐����擾
	static CScene*GetTopScene(OBJTYPE objtype) { return m_pTop[objtype]; }	// ���̎�ނ̐擪�̃I�u�W�F�N�g���擾
	CScene* GetNextScene(void) { return m_pNext; }							// ���̃I�u�W�F�N�g���擾

protected:
	void Release(void);					// �P�̂��J��

private:
	static CScene *m_pTop[OBJTYPE_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[OBJTYPE_MAX];	// ���݂ɂ�����ŐV�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^

	static int m_nNumObjectAll;			// �V�[����̂��ׂẴI�u�W�F�N�g�̐�
	static int m_nNumAll[OBJTYPE_MAX];	// �V�[����̎�ނ��Ƃ̃I�u�W�F�N�g�̍ő吔
	OBJTYPE m_objType;					// �I�u�W�F�N�g�̎��

	bool m_bUse;						// �g�p���邩�ǂ���
};

#endif