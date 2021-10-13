#ifndef CREATSTAGE_H
#define CREATSTAGE_H

#include "main.h"
#include "manager.h"
#include "mode.h"
#include "input.h"
#include "scene.h"
#include "field.h"

#include <stdio.h>
#include <string.h>

#define BYTE (256)                                      // ������̊m�ۃ�������
#define BLOCK_SAVE_MAX_NUM (256)                        // �ύX���e��ۑ��o���鐔
#define OBJECT_MIN_NUM (1)                              // �I�u�W�F�N�g�̍Œᐔ
#define NEXT_DATA (1) // �����߂��ꍇ�́A�Q�Ƃ���z��
#define NEXT_TIME_DATA (2)
#define DEBUG_TXT_NAME "data/TXT/debug.txt"             // �ύX���e���o�͂���e�L�X�g�t�@�C��

class CCreateStage : public CMode {
public:
	typedef enum {
		DETAILSCHANGE_NULL = 0,         // �ύX���e���ݒ�
		DETAILSCHANGE_CHANGE_POS,       // ���W�ύX
		DETAILSCHANGE_CHANGE_LAST_POS,  // ���W�ύX(control + Z�𔻒�)
		DETAILSCHANGE_CHANGE_ROT,       // �����ύX
		DETAILSCHANGE_CHANGE_LAST_ROT,  // �����ύX(control + Z�𔻒�)
		DETAILSCHANGE_BREAK,            // �I�u�W�F�N�g����
		DETAILSCHANGE_CREATE,           // �I�u�W�F�N�g����
		DETAILSCHANGE_TOTALELIMINATION, // �I�u�W�F�N�g�S����
		DETAILSCHANGE_MAX               // ���ڍő吔
	} DETAILSCHANGE;

	typedef enum {
		CREATEOBJECT_STAGE, // �X�e�[�W�ݒu���[�h
		CREATEOBJECT_ENEMY, // �G�ݒu���[�h
		CREATEOBJECT_MAX    // ���[�h�ő吔
	} CREATEOBJECT;

	typedef struct {
		int nNumber;                 // �ԍ�
		int nType;                   // ���
		bool bChangeJudge;           // �ύX��K�p����������
		DETAILSCHANGE DetailsChange; // �ύX���e
		D3DXVECTOR3 pos;             // ���W
		D3DXVECTOR3 rot;             // ����
		CScene::OBJTYPE ObjectType;  // �I�u�W�F�N�g�^�C�v
	}BLOCKSAVEDATE;

	CCreateStage();
	~CCreateStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static HRESULT LoadStage(void);
	static HRESULT SaveStage(void);
	static HRESULT LoadEnemy(void);
	static HRESULT SaveEnemy(void);
	void CursorCollision(D3DXVECTOR3 pos, CREATEOBJECT m_CreateType);
	static CREATEOBJECT GetCreateObject(void) { return m_CreateType; }

	static bool GetFixedSshaft(int nshaft) { return m_bFixedSshaft[nshaft]; }
	static bool GetGreaseJudge(void) { return m_bGreaseJudge; }
	static bool GetSaveJudge(void) { return m_bSaveJudge; }
	static void SetSaveJudge(bool bJudge) { m_bSaveJudge = bJudge; }
	static bool GetPushedControlS(void) { return m_bPushedControlS; }
	static void SetPushedControlS(bool bJudge) { m_bPushedControlS = bJudge; }
	static D3DXVECTOR3 GetCopyPosR(void) { return m_CopyRot; }
	static D3DXVECTOR3 GetCopyPos(void) { return m_CopyPos; }
	static int GetCopynType(void) { return m_nCopyType; }
	static bool GetWriteSaveDetaJudge() { return m_WriteSaveDate; }
	static void SetWriteSaveDataJudge(bool bJudge) { m_WriteSaveDate = bJudge; }
	void CursorControl(D3DXVECTOR3 FixedSshaft, D3DXVECTOR3 CursorPos, CREATEOBJECT m_CreateType);
	void CreatBlockControl(D3DXVECTOR3 FixedSshaft, D3DXVECTOR3 CursorPos, D3DXVECTOR3 PosR, int nType, bool Judge, int nCount, CScene::OBJTYPE ObjectType, DETAILSCHANGE DetallsChange);
	void WriteBlockSaveDate(int nNumAll);
	int UndoingOperation(int nNumAll);
	int RedoUndoOperation(int nNumAll);
	int ShiftArray(int nCount);
	void SetCopyData(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	void InitCopyDate(void);
	void SaveData(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumber, DETAILSCHANGE DetailsChange, bool bChangeJudge, int nType, int nCount, CScene::OBJTYPE ObjectType);
	int BlockAllDelete(int nCount);
	int EnemyAllDelete(int nCount);
	int SetObject(CInputKeyboard* m_pInputKeyboard, D3DXVECTOR3 m_posR, CMouse* m_pMouse, int nCount, BLOCKSAVEDATE m_aBlockSaveDate, CREATEOBJECT m_CreateType);
	int SetEnemy(CInputKeyboard* m_pInputKeyboard, D3DXVECTOR3 m_posR, CMouse* m_pMouse, int nCount, BLOCKSAVEDATE m_aBlockSaveDate, CREATEOBJECT m_CreateType);
	void InitArray(int nCount);
	void CountDetallsChangeLAST(void);
	HRESULT LoadTextName(void);
	static char* GetTxtName(int nNumber) { return m_cTxtName[nNumber]; }
	void SetObjectType(int nType);
	static int GetBlockType(void) { return m_nBlockType; }
	static int GetEnemyType(void) { return m_nEnemyType; }
	static int GetCopyType(void) { return m_nCopyType; }
	static bool GetPauseJudge(void) { return m_bPauseJudge; }

private:
	static D3DXVECTOR3 m_FieldSiz;                             // �t�B�[���h�̑傫��
	D3DXVECTOR3 m_posR;                                        // �J�����̌���
	D3DXVECTOR3 m_CursorPos;                                   // �J�[�\���̍��W
	static D3DXVECTOR3 m_CopyRot;                              // �R�s�[�����I�u�W�F�N�g�̌���
	static D3DXVECTOR3 m_CopyPos;                              // �R�s�[�����I�u�W�F�N�g�̍��W
	static int m_nBlockType;                                   // �u���b�N�̃^�C�v�i�[�p
	static int m_nEnemyType;                                   // �G�̃^�C�v�i�[�p
	static int m_nCopyType;                                    // �R�s�[�����I�u�W�F�N�g�^�C�v�i�[�p
	CMouse* m_pMouse;                                          // �}�E�X�̃|�C���^
	CInputKeyboard* m_pInputKeyboard;                          // �L�[�{�[�h�̃|�C���^
	static bool m_bFixedSshaft[2];                             // 0->x��, 1->z��
	D3DXVECTOR3 m_FixedSshaft;                                 // �Œ莲
	static bool m_bGreaseJudge;                                // �O���b�h�̎g�p���
	static bool m_bSaveJudge;                                  // �Z�[�u�̐������
	static bool m_bPushedControlS;                             // control��S�������ꂽ�����擾
	static BLOCKSAVEDATE m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM]; // �ύX���e�i�[�p
	static CREATEOBJECT m_CreateType;                          // ��������I�u�W�F�N�g�^�C�v
	static bool m_bUseAllDelete;                               // �S�������m�F
	static bool m_WriteSaveDate;                               // �ύX���e���o�͏o���������擾
	int m_nAllDeleteNum;                                       // �S���������s�����u�Ԃ́A���̃I�u�W�F�N�g�̑���
	int m_nLastCountPos;                                       // ���W�ύX�񐔂��J�E���g
	int m_nLastCountRot;                                       // �����ύX�񐔂��J�E���g
	static char m_cTxtName[3][256];                            // �ǂނ��ރt�@�C�����i�[�p
	static bool m_bPauseJudge;                                 // �|�[�Y�g�p����

	int nAddupAngle = 0;                                       // �A���O��
	int nAddY = 0;                                             // Y���ǉ���
};

#endif
