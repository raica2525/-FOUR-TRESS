//====================================================================
//
// �u���b�N�̏��� (character.h)
// Author : ��{��
//
//====================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene3d.h"

//========================================
// �}�N����`
//========================================

#define LOAD_ENEMY_TXT "data/TXT/enemymodel.txt"

//================================================
// �N���X�錾
//================================================

// �u���b�N�N���X
class CEnemy : public CScene3D
{
public:

	// �G�̎��
	typedef enum
	{
		TYPE_1,
		TYPE_2,
		TYPE_3,
		TYPE_4,
		TYPE_5,
		TYPE_6,
		TYPE_7,
		TYPE_8,
		TYPE_9,
		TYPE_10,
		TYPE_11,
		TYPE_12,
		TYPE_13,
		TYPE_14,
		TYPE_15,
		TYPE_16,
		TYPE_17,
		TYPE_18,
		TYPE_19,
		TYPE_20,
		TYPE_21,
		TYPE_22,
		TYPE_23,
		TYPE_24,
		TYPE_25,
		TYPE_26,
		TYPE_27,
		TYPE_28,
		TYPE_29,
		TYPE_30,
		TYPE_31,
		TYPE_32,
		TYPE_33,
		TYPE_34,
		TYPE_35,
		TYPE_36,
		TYPE_37,
		TYPE_38,
		TYPE_39,
		TYPE_40,
		TYPE_MAX            // ��ނ̍ő吔
	}TYPE;

	// �I�u�W�F�N�g���
	typedef struct
	{
		char ModelPath[256];
		char TexturePath[256];
		char DrawName[256];
		TYPE Type;
		D3DXVECTOR3 Game_Collision_Siz;
		D3DXVECTOR3 Toul_Collision_Siz;
		bool bUseJudge;
	} ENEMYDATA;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static void LoadTxt(void);
	static ENEMYDATA GetEnemyData(int nNumber) { return m_aEnemyData[nNumber]; }
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

	D3DXVECTOR3 GetCollisionSize(void) { return m_collisionSize; }          // �Փ˂̑傫����Ԃ�
	bool GetWallRun(void) { return m_bWallRun; }                            // �Ǒ���ł��邩�ǂ�����Ԃ�

	static CEnemy*GetSelectEnemy(void) { return m_pSelectEnemy; }           // �I�����Ă���u���b�N���擾
	static void SetSelectEnemy(CEnemy* pBlock) { m_pSelectEnemy = pBlock; } // �I�����Ă���u���b�N��ݒ�

	int GetType(void) { return m_nType; }
	static int GetEnemyNumAll(void) { return m_nNumAll; }
	int GetNumber(void) { return m_nNumber; }

	static HRESULT SetEnemyData(char* ModelPath, char* TexturePath, char* DrawName, TYPE Type, D3DXVECTOR3 Game_Collision_Siz, D3DXVECTOR3 Toul_Collision_Siz, int nNum, bool bUseJudge);

private:
	static LPDIRECT3DTEXTURE9		m_apTexture[TYPE_MAX];  // �ǂݍ��ރe�N�X�`��
	static LPD3DXMESH				m_apMesh[TYPE_MAX];     // �ǂݍ��ރ��b�V��
	static LPD3DXBUFFER				m_apBuffMat[TYPE_MAX];  // �ǂݍ��ރ}�e���A���̃o�b�t�@
	static DWORD					m_aNumMat[TYPE_MAX];    // �ǂݍ��ރ}�e���A����

	static CEnemy *m_pSelectEnemy;                          // ���ݑI�����Ă���u���b�N�̃|�C���^

	D3DXVECTOR3 m_collisionSize;                            // �����蔻��̑傫��
	bool m_bWallRun;                                        // �Ǒ���ł��邩�ǂ���
	bool m_bBlink;                                          // �u�����ǂ���
	int m_nCntTime;                                         // ���Ԃ𐔂���
	static int m_nNumAll;                                   // �u���b�N�̑���
	int m_nNumber;                                            // �u���b�N�̔ԍ�
	static ENEMYDATA m_aEnemyData[TYPE_MAX];
	static char m_cTextureName[TYPE_MAX][256];                // �e�N�X�`���p�X�ۊǗp�ϐ�
	static char m_cModelName[TYPE_MAX][256];                  // ���f���p�X�ۊǗp�ϐ�

	int m_nType;                                            // ���
};

#endif
