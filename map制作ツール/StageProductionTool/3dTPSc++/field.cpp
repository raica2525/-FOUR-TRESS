#define _CRT_SECURE_NO_WARNINGS

//===============================================
//
// �t�B�[���h���� (field.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "CreateStage.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================
CTile *CField::m_pTile[MAP_WIDTH][MAP_HEIGHT] = {};
int CField::m_aGround[MAP_WIDTH][MAP_HEIGHT] = {};
D3DXVECTOR3 CField::m_siz = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CField::CField() {}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CField::~CField() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot) {
  LoadMapData();

  return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CField::Uninit(void) {
  for (int nCountHeight = 0; nCountHeight < m_siz.y; nCountHeight++) {
    for (int nCountWidth = 0; nCountWidth < m_siz.x; nCountWidth++) {
      m_pTile[nCountHeight][nCountWidth]->Uninit();
      delete m_pTile[nCountHeight][nCountWidth];
      m_pTile[nCountHeight][nCountWidth] = NULL;
    }
  }
}

//=============================================================================
// �X�V����
//=============================================================================
void CField::Update(void) {}

//=============================================================================
// �`�揈��
//=============================================================================
void CField::Draw(void) {
  for (int nCountHeight = 0; nCountHeight < m_siz.y; nCountHeight++) {
    for (int nCountWidth = 0; nCountWidth < m_siz.x; nCountWidth++) {
      m_pTile[nCountHeight][nCountWidth]->Draw();
    }
  }
}

//=============================================================================
// ���f���f�[�^�ǂݍ��ݏ���
//=============================================================================
void CField::LoadMapData(void) {
  FILE *pFile = fopen(CCreateStage::GetTxtName(2), "r");

  int nHeight = 0;
  int nWidth = 0;

  for (int nCountMap = 0; nCountMap < NUM_TILE; nCountMap++) {
    if (pFile != NULL) {
      while (fscanf(pFile, "%d,", &m_aGround[nHeight][nWidth]) != EOF) {
        nWidth++;
        if (nWidth >= m_siz.x) {
          nWidth = 0;
          nHeight++;
        }
      }
    }
  }

  fclose(pFile);
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CField *CField::Create(void) {
  CField *m_pField;

  m_pField = new CField;
  m_pField->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
                 D3DXVECTOR3(0.0f, 0.0f, 0.0f));
  m_pField->SetField();

  return m_pField;
}

//=============================================================================
// �t�B�[���h��������
//=============================================================================
void CField::SetField(void) {
  int nHeight = 0;

  for (int nCountHeight = m_siz.y - 1; nCountHeight > -1; nCountHeight--) {
    for (int nCountWidth = 0; nCountWidth < m_siz.x; nCountWidth++) {
      switch (m_aGround[nHeight][nCountWidth]) {
      case CTile::TILE_BLACK:
        m_pTile[nCountHeight][nCountWidth] = new CTile;
        m_pTile[nCountHeight][nCountWidth]->Init(CTile::TILE_BLACK);
        m_pTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(nCountWidth * TILE_SIZE / 2, 0.0f, nCountHeight * TILE_SIZE / 2));
        m_pTile[nCountHeight][nCountWidth]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
        m_pTile[nCountHeight][nCountWidth]->Update();
        break;
      case CTile::TILE_WHITE:
        m_pTile[nCountHeight][nCountWidth] = new CTile;
        m_pTile[nCountHeight][nCountWidth]->Init(CTile::TILE_WHITE);
        m_pTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(nCountWidth * TILE_SIZE / 2, 0.0f, nCountHeight * TILE_SIZE / 2));
        m_pTile[nCountHeight][nCountWidth]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
        m_pTile[nCountHeight][nCountWidth]->Update();
        break;
      case CTile::TILE_RED:
        m_pTile[nCountHeight][nCountWidth] = new CTile;
        m_pTile[nCountHeight][nCountWidth]->Init(CTile::TILE_RED);
        m_pTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(nCountWidth * TILE_SIZE / 2, 0.0f, nCountHeight * TILE_SIZE / 2));
        m_pTile[nCountHeight][nCountWidth]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
        m_pTile[nCountHeight][nCountWidth]->Update();
        break;
      case CTile::TILE_GREENERY:
        m_pTile[nCountHeight][nCountWidth] = new CTile;
        m_pTile[nCountHeight][nCountWidth]->Init(CTile::TILE_GREENERY);
        m_pTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(nCountWidth * TILE_SIZE / 2, 0.0f, nCountHeight * TILE_SIZE / 2));
        m_pTile[nCountHeight][nCountWidth]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
        m_pTile[nCountHeight][nCountWidth]->Update();
        break;
	  case CTile::TILE_SIDEWALK:
		  m_pTile[nCountHeight][nCountWidth] = new CTile;
		  m_pTile[nCountHeight][nCountWidth]->Init(CTile::TILE_SIDEWALK);
		  m_pTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(nCountWidth * TILE_SIZE / 2, 0.0f, nCountHeight * TILE_SIZE / 2));
		  m_pTile[nCountHeight][nCountWidth]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
		  m_pTile[nCountHeight][nCountWidth]->Update();
		  break;
	  case CTile::TILE_CHUOLINE:
		  m_pTile[nCountHeight][nCountWidth] = new CTile;
		  m_pTile[nCountHeight][nCountWidth]->Init(CTile::TILE_CHUOLINE);
		  m_pTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(nCountWidth * TILE_SIZE / 2, 0.0f, nCountHeight * TILE_SIZE / 2));
		  m_pTile[nCountHeight][nCountWidth]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
		  m_pTile[nCountHeight][nCountWidth]->Update();
		  break;
      default:
        break;
      }
    }

    nHeight++;
  }
}
