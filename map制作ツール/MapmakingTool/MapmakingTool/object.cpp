//===============================================
//
// �V�[����̃I�u�W�F�N�g���� (scene.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "object.h"
#include "renderer.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================
int CObject::m_nNumObjectAll = 0;

CObject *CObject::m_apTop = {};
CObject *CObject::m_apCur = {};

//========================================
// �V�[����̃I�u�W�F�N�g�̃I�[�o�[���C�h���ꂽ�R���X�g���N�^
// Author : �㓡�T�V��
//========================================
CObject::CObject()
{
	// �擪���Ȃ��Ȃ�A�擪��
	if (m_apTop == NULL)
	{
		m_apTop = this;
	}

	// ���݂ɂ�����ŐV�̃I�u�W�F�N�g���Ȃ��Ȃ�A�ŐV��
	if (m_apCur == NULL)
	{
		m_apCur = this;
	}

	// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���A�����ɂ���
	m_apCur->m_pNext = this;

	// ���݂̃I�u�W�F�N�g�������̏ꍇ
	if (m_apCur == this)
	{
		// �����̑O�̃I�u�W�F�N�g���ANULL�ɂ���
		m_pPrev = NULL;
	}
	else
	{
		// �����̑O�̃I�u�W�F�N�g���A���݂̃I�u�W�F�N�g�ɂ���
		m_pPrev = m_apCur;
	}

	// ���݂̃I�u�W�F�N�g���A�����ɂ���
	m_apCur = this;

	// �����̎��̃I�u�W�F�N�g���ANULL�ɂ���
	m_pNext = NULL;

	// �S�̂̐����C���N�������g
	m_nNumObjectAll++;

	// �g�p����t���O��true��
	m_bUse = true;
}

//========================================
// �V�[����̃I�u�W�F�N�g�̃f�X�g���N�^
// Author : �㓡�T�V��
//========================================
CObject::~CObject()
{

}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�čX�V
// Author : �㓡�T�V��
//==============================================
void CObject::UpdateAll(void)
{
	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_apTop != NULL && m_apCur != NULL)
	{
		// �L���p�̕ϐ�
		CObject* pObject = m_apTop;

		do
		{
			// �L���p�̕ϐ�(Update���ɁAUninit����邱�Ƃ��l��)
			CObject* pNextScene = pObject->m_pNext;

			// �X�V����
			pObject->Update();

			// �g�p�t���O��false�Ȃ�
			if (pObject->m_bUse == false)
			{
				// �������̊J��
				delete pObject;
				pObject = NULL;
			}

			// ���̃V�[���ɕς��Ă���
			pObject = pNextScene;

		} while (pObject != NULL);
	}
}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�ĕ`��
// Author : �����N�m
//==============================================
void CObject::DrawAll(void) 
{
	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_apTop != NULL && m_apCur != NULL)
	{
		// �L���p�̕ϐ�
		CObject* pObject = m_apTop;

		do
		{
			// �L���p�̕ϐ�(Update���ɁAUninit����邱�Ƃ��l��)
			CObject* pNextScene = pObject->m_pNext;

			// �X�V����
			pObject->Draw();

			// �g�p�t���O��false�Ȃ�
			if (pObject->m_bUse == false)
			{
				// �������̊J��
				delete pObject;
				pObject = NULL;
			}

			// ���̃V�[���ɕς��Ă���
			pObject = pNextScene;

		} while (pObject != NULL);
	}
}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�ĊJ��
// Author : �㓡�T�V��
//==============================================
void CObject::ReleaseAll(void)
{
	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_apTop != NULL && m_apCur != NULL)
	{
		// �L���p�̕ϐ�
		CObject* pObject = m_apTop;

		do
		{
			// �L���p�̕ϐ�
			CObject* pNextScene = pObject->m_pNext;

			// �I������
			pObject->Uninit();

			// �g�p�t���O��false�Ȃ�
			if (pObject->m_bUse == false)
			{
				// �������̊J��
				delete pObject;
				pObject = NULL;
			}

			// ���̃V�[���ɕς��Ă���
			pObject = pNextScene;

		} while (pObject != NULL);
	}
}

//==============================================
// �V�[����̃I�u�W�F�N�g��S�ĊJ��
// Author : �㓡�T�V��
//==============================================
void CObject::Release(void)
{
	// ���g������Ȃ�A
	if (this != NULL)
	{
		// �擪�Ȃ�
		if (this == m_apTop)
		{
			// ���̒��g������Ȃ�
			if (m_pNext != NULL)
			{
				// ���̂��̂̑O�̏����ANULL��
				m_pNext->m_pPrev = NULL;

				// �����擪��
				m_apTop = m_pNext;
			}
			else
			{
				// �擪�̎����Ȃ��Ȃ�A�擪�ƌ��݂������|�C���^��NULL��
				m_apTop = NULL;
				m_apCur = NULL;
			}
		}
		// �擪�łȂ��Ȃ�
		else
		{
			// ���̒��g������Ȃ�
			if (m_pNext != NULL)
			{
				// �O�̂��̂̎��̏����A���g�̎��̏���
				m_pPrev->m_pNext = m_pNext;

				// ���̂��̂̑O�̏����A���g�̑O�̏���
				m_pNext->m_pPrev = m_pPrev;
			}
			else
			{
				// �O�̂��̂̎��̏����A�Ȃ���
				m_pPrev->m_pNext = NULL;

				// ���݂̍ŐV�̂��̂��A�O�̏���
				m_apCur = m_pPrev;
			}
		}

		//// �������̊J��(���X�g�\����m_pNext�ŃV�[����؂�ւ��Ă����ۂɎx�Ⴊ�o��̂ŁA�����ł͍s��Ȃ�)
		//delete this;
		////this = NULL;

		// �g�p�t���O��false��
		m_bUse = false;

		// �S�̂̐����f�N�������g
		m_nNumObjectAll--;
	}
}
