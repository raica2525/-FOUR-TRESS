//====================================================================
//
// �t�B�[���h�̏��� (character.h)
// Author : ��{��
//
//====================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"
#include "tile.h"
#include "CreateStage.h"

//================================================
// �}�N����`
//================================================

#define FIELD_POS (D3DXVECTOR3(2000.0f, 0.0f, 4800.0f))  // �t�B�[���h�̈ʒu
#define FIELD_SCALE (D3DXVECTOR3(100.0f, 1.0f, 100.0f))  // �t�B�[���h�̃X�P�[��

#define MAP_WIDTH	75	// �}�b�v�̕�
#define MAP_HEIGHT	75	// �}�b�v�̉��s

#define NUM_TILE	(MAP_WIDTH * MAP_HEIGHT)

#define CSV_FIELD_NAME (CSV_TXT_NAME)

//================================================
// �N���X�錾
//================================================

// �t�B�[���h�N���X
class CField : public CScene
{
public:
    CField();
    ~CField();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
    void Uninit(void);
	void Update(void);
	void Draw(void);

	void LoadMapData(void);
	static void SetMapSiz(D3DXVECTOR3 pos) { m_siz = pos; }

	static CField *Create(void);

	static void SetField(void);
private:
	static D3DXVECTOR3 m_siz;
	static CTile*      m_pTile[MAP_WIDTH][MAP_HEIGHT];
	static int	       m_aGround[MAP_WIDTH][MAP_HEIGHT];
};

#endif