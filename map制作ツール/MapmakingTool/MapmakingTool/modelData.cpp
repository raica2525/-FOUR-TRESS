//=============================================================================
//
// モデルデータの処理 [modelData.cpp]
// Author : 後藤慎之助
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルード
//=============================================================================
#include "modelData.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_DATA_FILENAME ("data/TXT/modelData.txt")	    // モデルデータを読み込むファイルの名前

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CModelData::CModelData()
{
	memset(m_aModelData, 0, sizeof(m_aModelData));
	memset(m_aModelData->apTexMat, 0, sizeof(m_aModelData->apTexMat));

	memset(m_aModelPosDef, 0, sizeof(m_aModelPosDef));
	memset(m_aModelPosDef->nIndex, 0, sizeof(m_aModelPosDef->nIndex));
	memset(m_aModelPosDef->nParent, 0, sizeof(m_aModelPosDef->nParent));
	memset(m_aModelPosDef->pos, 0, sizeof(m_aModelPosDef->pos));
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CModelData::~CModelData()
{
}

//=============================================================================
// 初期化処理
// Author : 後藤慎之助
//=============================================================================
HRESULT CModelData::Init(void)
{
	// ファイルポイント
	FILE *pFile = NULL;

	// 変数宣言
	char cReadText[2048];	               // 文字として読み取り用
	char cHeadText[2048];	               // 文字の判別用
	char cDie[2048];		               // 使わない文字
	int nNumType = 0;                      // タイプのナンバー
	char cLoadModelName[256];              // 読み込み時のモデル名

										   // モデルを読み込むためのデバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//======================================================================================
	// モデルデータファイルを開く
	pFile = fopen(MODEL_DATA_FILENAME, "r");

	// 開けたら
	if (pFile != NULL)
	{
		// SCRIPTの文字が見つかるまで
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			// テキストからcReadText分文字を受け取る
			fgets(cReadText, sizeof(cReadText), pFile);

			// cReedTextをcHeadTextに格納
			sscanf(cReadText, "%s", &cHeadText);
		}

		// cHeadTextがSCRIPTの時
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// cHeadTextがEND_SCRIPTになるまで
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				// cHeadTextがMODEL_DATASETの時
				if (strcmp(cHeadText, "MODEL_DATASET") == 0)
				{
					// cHeadTextがEND_MODEL_DATASETになるまで
					while (strcmp(cHeadText, "END_MODEL_DATASET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nNumType);
						}
						else if (strcmp(cHeadText, "NAME") == 0)
						{
							sscanf(cReadText, "%s %s %s", &cDie, &cDie, &cLoadModelName);

							// モデルデータの読み込み
							D3DXLoadMeshFromX(LPCSTR(cLoadModelName), D3DXMESH_SYSTEMMEM, pDevice, NULL,
								&m_aModelData[nNumType].pBuffMat, NULL, &m_aModelData[nNumType].nNumMat, &m_aModelData[nNumType].pMesh);

							// マテリアルのポインタを取得
							D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_aModelData[nNumType].pBuffMat->GetBufferPointer();

							// マテリアルのテクスチャを結びつける
							for (int nCntMat = 0; nCntMat < (int)m_aModelData[nNumType].nNumMat; nCntMat++)
							{
								D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_aModelData[nNumType].apTexMat[nCntMat]);
							}
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	// 開けなかったら
	else
	{
		printf("開けれませんでした\n");

		return E_FAIL;
	}
	//======================================================================================

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CModelData::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_MODEL_DATA; nCount++)
	{
		// マテリアルのテクスチャの破棄
		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			if (m_aModelData[nCount].apTexMat[nCntMat] != NULL)
			{
				m_aModelData[nCount].apTexMat[nCntMat]->Release();
				m_aModelData[nCount].apTexMat[nCntMat] = NULL;
			}
		}

		// メッシュの破棄
		if (m_aModelData[nCount].pMesh != NULL)
		{
			m_aModelData[nCount].pMesh->Release();
			m_aModelData[nCount].pMesh = NULL;
		}

		// マテリアルの破棄
		if (m_aModelData[nCount].pBuffMat != NULL)
		{
			m_aModelData[nCount].pBuffMat->Release();
			m_aModelData[nCount].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// モデルデータ情報の受け取りの処理
// Author : 後藤慎之助
//=============================================================================
CModelData::ModelData* CModelData::GetModelData(const int nNum)
{
	if (nNum < MAX_MODEL_DATA && nNum >= 0)
	{
		if (&m_aModelData[nNum] != NULL)
		{
			return &m_aModelData[nNum];
		}
	}

	return NULL;
}