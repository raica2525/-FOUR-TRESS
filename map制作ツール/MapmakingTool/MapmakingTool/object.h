//====================================================================
//
// �V�[����̃I�u�W�F�N�g���� (scene.h)
// Author : �㓡�T�V��
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
class CObject
{
public:
	CObject();    // �C�j�V�����C�U�ŃI�u�W�F�N�g�^�C�v��R�Â�
	virtual ~CObject();  // �e�N���X�̃f�X�g���N�^��virtual�����邱�ƂŁA���������[�N��}����
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);                                                        // �S�čX�V
	static void DrawAll(void);															// �S�ĕ`��
	static void ReleaseAll(void);                                                       // �S�ĊJ��

	static int GetNumObjAll(void) { return m_nNumObjectAll; }                           // �V�[����̑S�ẴI�u�W�F�N�g��
	static CObject*GetTopScene(void) { return m_apTop; }              // �擪�̃I�u�W�F�N�g���擾
	CObject* GetNextScene(void) { return m_pNext; }                                      // ���̃I�u�W�F�N�g���擾

/*============================================================================================================================
// �I�u�W�F�N�g�̃^�C�v���ƂŃR���X�g���N�^�Ŏ��̃V�[�������L�����Ă��邽�߁A��΂ɃI�u�W�F�N�g�^�C�v�����������Ă͂����Ȃ�
//void SetObjType(OBJTYPE objtype) { m_objType = objtype; }
// �g�b�v�Ɏ�ނ����Ď擾�ł���̂ŁA�Q�b�^�[���g���@��Ȃ��Ȃ���
//OBJTYPE GetObjType(void) { return m_objType; }
============================================================================================================================*/

protected:
	void Release(void);                 // �P�̂��J��

private:
	static CObject *m_apTop;  // �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_apCur;  // ���݂ɂ�����ŐV�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;                      // �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;                      // ���̃I�u�W�F�N�g�ւ̃|�C���^

	static int m_nNumObjectAll;          // �V�[����̂��ׂẴI�u�W�F�N�g�̐�

	bool m_bUse;                         // �g�p���邩�ǂ���
};

#endif