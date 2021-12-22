//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �㓡�T�V��
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// �C���N���[�h�t�@�C��
//========================
#include "game.h"
#include "manager.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"
#include "input.h"
#include "scene.h"
#include "library.h"
#include "debug.h"
#include "pause.h"
#include "scene2d.h"
#include "camera.h"
#include "bg.h"
#include "wave.h"
#include "effect2d.h"
#include "effect3d.h"
#include "number_array.h"
#include "text.h"
#include "enemy.h"
#include "road.h"
#include "fortress.h"
#include "block.h"
#include "bullet.h"
#include "mapmanager.h"

//========================================
// �}�N����`
//========================================

// �Q�[����Ԃ̊Ǘ��t���[��
#define BLOW_MOMENT_FRAME 180          // �ꌂ�̏u�ԃt���[����
#define FINISH_WAIT_FRAME 240          // �������ɁA�҂t���[����
#define CREATE_POS_Y_RATE 0.8f         // �{�[���̔����ʒuY�̊���
#define FADE_IN_TELOP 30               // �e���b�v�̃t�F�[�h�C���J�n�t���[��
#define FADE_OUT_TELOP 150             // �e���b�v�̃t�F�[�h�A�E�g�J�n�t���[��
#define FADE_IN_FINISH_TELOP 90        // �t�B�j�b�V���e���b�v�̃t�F�[�h�C���J�n�t���[��

#define DISTANCE_INIT_VALUE 999999.9f  // �����������l
#define DEFAULT_INIT_DISTANCE 2000.0f

#define MAP_FILENAME ("data/TXT/testdata.json")			// �}�b�v�Ŏg�p���郂�f���f�[�^�̃t�@�C��

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CGame::m_bStopObjUpdate = false;

CPlayer *CGame::m_apPlayer[] = {};
CPause *CGame::m_pPause = NULL;
CEffect2D *CGame::m_pEffect2d_Nega = NULL;
CEffect2D *CGame::m_pEffect2d_Posi = NULL;

CGame::TYPE CGame::m_type = TYPE_TRAINING;
int CGame::m_nNumAllPlayer = 0;
bool CGame::m_bUseKeyboard = false;      // �f�o�b�O���͂�����ς���
int CGame::m_anMemoryIdxPlayer[] = {};
CPlayer::AI_LEVEL CGame::m_aMemoryAILevel[] = {};
int CGame::m_anMemoryRole[] = {};
CGame::STATE CGame::m_state = STATE_ROUND_START;

CPlayer *CGame::m_pSpPlayer = NULL;
bool CGame::m_bCurrentSpShot = false;
CText *CGame::m_pSpText = NULL;

CFortress *CGame::m_pFortress = NULL;
int CGame::m_nCharacterIdx = 0;
CNumberArray *CGame::m_pScore = NULL;
int CGame::m_nScore = 0;

CGame::INFO_IN_RESULT CGame::m_aInfoInResult[] = {};
bool CGame::m_bWin = false;

//=============================================================================
// �Q�[���̃R���X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CGame::CGame()
{
    m_bStopObjUpdate = false;
    m_bCurrentSpShot = false;
    m_pSpText = NULL;

    memset(m_apPlayer, 0, sizeof(m_apPlayer));
    m_pPause = NULL;
    m_pEffect2d_Nega = NULL;
    m_pEffect2d_Posi = NULL;
    m_pSpPlayer = NULL;

    // �ÓI�����o�ϐ����������i�J�ڎ��ɖ���K�v�Ȃ��̂����j
    //m_type = TYPE_TRAINING;
    //m_nNumAllPlayer = 0;
    //m_nNumStock = 0;
    //m_bUseKeyboard = false;
    //memset(m_anMemoryIdxPlayer, 0, sizeof(m_anMemoryIdxPlayer));
    //memset(m_aMemoryAILevel, 0, sizeof(m_aMemoryAILevel));
    m_state = STATE_ROUND_START;

    m_nCntGameTime = 0;
    m_bFirestRound = true;

    m_pFortress = NULL;
    m_nCharacterIdx = 0;
    m_pScore = NULL;
    m_nScore = 0;

    memset(m_aInfoInResult, 0, sizeof(m_aInfoInResult));
    m_bWin = false;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
// Author : �㓡�T�V��
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
// Author : �㓡�T�V��
//=============================================================================
HRESULT CGame::Init(void)
{
    // �e�L�X�g����
    m_pSpText = CText::Create(D3DXVECTOR3(640.0f, 500.0f, 0.0f), 100,
        "�Ȃ�", CText::ALIGN_CENTER, "Reggae One", TEXT_NOT_EXIST_COLOR);

    // ��`
    const float SPLIT_RATE_UNDER_3 = 0.5f;
    const float SPLIT_RATE_ABOVE_2 = 0.333f;

    // �v���C���[�̐���
    D3DXVECTOR3 player1Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);
    D3DXVECTOR3 player2Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);
    D3DXVECTOR3 player3Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);
    D3DXVECTOR3 player4Pos = D3DXVECTOR3(1000.0f, 1000.0f * CREATE_POS_Y_RATE, 0.0f);

    if (m_type == TYPE_TRAINING)
    {
        //m_nNumAllPlayer = 1;                // �g���[�j���O��1�l�Œ�
        //CBg::Create(84, DEFAULT_VECTOR);    // �f�o�b�O�X�e�[�W�̏�
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(0.0f, 0.0f, 3300.0f), D3DXVECTOR3(6500.0f, 500.0f, 500.0f), DEFAULT_VECTOR);  // �u���b�N����
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(0.0f, 0.0f, -3300.0f), D3DXVECTOR3(6500.0f, 500.0f, 500.0f), DEFAULT_VECTOR);  // �u���b�N����
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(3300.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 6500.0f), DEFAULT_VECTOR);  // �u���b�N����
        //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(-3300.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 6500.0f), DEFAULT_VECTOR);  // �u���b�N����

        //CBg::Create(66, D3DXVECTOR3(1000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(66, D3DXVECTOR3(-1000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(66, D3DXVECTOR3(3000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(66, D3DXVECTOR3(-3000.0f, 0.0f, 4000.0f), CBg::COLOR_PHASE_G_UP);

        //CBg::Create(67, D3DXVECTOR3(1000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(67, D3DXVECTOR3(-1000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(67, D3DXVECTOR3(3000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);
        //CBg::Create(67, D3DXVECTOR3(-3000.0f, 0.0f, -4000.0f), CBg::COLOR_PHASE_G_UP);

        // �W�F�C�\���t�@�C������}�b�v�𐶐����A�����n�_���擾����
        CMapManager *pMapManager = CManager::GetMapManager();
        pMapManager->CreateMapFromJson(MAP_FILENAME);
        D3DXVECTOR3 startPos = pMapManager->GetStartPos();
        player1Pos = startPos;
        player2Pos = startPos;
        player3Pos = startPos;
        player4Pos = startPos;
        m_pFortress = CFortress::Create(startPos); // �ړ��v�ǐ����i���G��ԁj
        //m_pFortress->SetSpeed(0.0f);
    }
    else if (m_type == TYPE_ARENA)
    {
        m_pFortress = CFortress::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f)); // �ړ��v�ǐ���
        // ���̓�����
        D3DXVECTOR3 roadPos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
        for (int nCnt = 0; nCnt < 20; nCnt++)
        {
            D3DXVECTOR3 rot = DEFAULT_VECTOR;
            roadPos.x += 1000.0f;
            rot = D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f);
            CRoad::Create(roadPos, rot);
        }

        // ���̓G�i�ŏ��̕ǂɎ���܂Łj
        D3DXVECTOR3 enemyPos = D3DXVECTOR3(3000.0f, 0.0f, 1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_ARMY, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        enemyPos = D3DXVECTOR3(4000.0f, 0.0f, 1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_KAMIKAZE, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        enemyPos = D3DXVECTOR3(3000.0f, 0.0f, -1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_KAMIKAZE, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        enemyPos = D3DXVECTOR3(4000.0f, 0.0f, -1500.0f);
        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            CEnemy::Create(CEnemy::TYPE_ARMY, enemyPos, 1.0f, CEnemy::APPEAR_STATE_EXIST, 0.0f, 50.0f);
            enemyPos.x += 2000.0f;
        }
        //CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(7000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        //CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(7000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(10000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(10000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(10000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);

        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(15000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(15000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(15000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(17000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(17000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(17000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(14000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(14000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(14000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(16000.0f, 0.0f, 500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(16000.0f, 0.0f, -500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(16000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(19000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(20500.0f, 0.0f, 750.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST, 3000.0f);
        CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(20500.0f, 0.0f, -750.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST, 3000.0f);

        // ���̃S�[���Q�[�g
        CBlock::Create(CBlock::TYPE_NORMAL_GATE, D3DXVECTOR3(12000.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 5000.0f, 5000.0f), MODEL_DIRECT_LEFT);
        CBlock::Create(CBlock::TYPE_GOAL_GATE, D3DXVECTOR3(22000.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 5000.0f, 5000.0f), MODEL_DIRECT_LEFT);
    }

    // �X�e�[�W�̃��f���𐶐�
    //CBg::Create(34, DEFAULT_VECTOR);    // �X�e�[�W1��34

    // UI�𐶐�
    CUI::Place(CUI::SET_GAME);

    // �|�[�Y�̐���
    m_pPause = CPause::Create();

    // �v���C���[�̐�������
    float fSplitXRate = 0.0f;
    switch (m_nNumAllPlayer)
    {
    case 1:
        fSplitXRate = SPLIT_RATE_UNDER_3;
        player1Pos.x *= -fSplitXRate;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        break;
    case 2:
        fSplitXRate = SPLIT_RATE_UNDER_3;
        player1Pos.x *= -fSplitXRate;
        player2Pos.x *= fSplitXRate;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        m_apPlayer[1] = CPlayer::CreateInGame(player2Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            1, m_anMemoryIdxPlayer[1], m_aMemoryAILevel[1], m_anMemoryRole[1]);
        break;
    case 3:
        fSplitXRate = SPLIT_RATE_ABOVE_2;
        player1Pos.x *= -fSplitXRate * 2.0f;
        player2Pos.x *= -fSplitXRate;
        player3Pos.x *= fSplitXRate;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        m_apPlayer[1] = CPlayer::CreateInGame(player2Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            1, m_anMemoryIdxPlayer[1], m_aMemoryAILevel[1], m_anMemoryRole[1]);
        m_apPlayer[2] = CPlayer::CreateInGame(player3Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            2, m_anMemoryIdxPlayer[2], m_aMemoryAILevel[2], m_anMemoryRole[2]);
        break;
    case 4:
        fSplitXRate = SPLIT_RATE_ABOVE_2;
        player1Pos.x *= -fSplitXRate * 2.0f;
        player2Pos.x *= -fSplitXRate;
        player3Pos.x *= fSplitXRate;
        player4Pos.x *= fSplitXRate * 2.0f;
        m_apPlayer[0] = CPlayer::CreateInGame(player1Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            0, m_anMemoryIdxPlayer[0], m_aMemoryAILevel[0], m_anMemoryRole[0], m_bUseKeyboard);
        m_apPlayer[1] = CPlayer::CreateInGame(player2Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_RIGHT, 0.0f),
            1, m_anMemoryIdxPlayer[1], m_aMemoryAILevel[1], m_anMemoryRole[1]);
        m_apPlayer[2] = CPlayer::CreateInGame(player3Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            2, m_anMemoryIdxPlayer[2], m_aMemoryAILevel[2], m_anMemoryRole[2]);
        m_apPlayer[3] = CPlayer::CreateInGame(player4Pos, D3DXVECTOR3(0.0f, PLAYER_ROT_LEFT, 0.0f),
            3, m_anMemoryIdxPlayer[3], m_aMemoryAILevel[3], m_anMemoryRole[3]);
        break;
    }
    // �J�����̃��b�N�I���ꏊ��ς���
    CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_GAME);

    // ���]�����p�̃G�t�F�N�g�𐶐�
    m_pEffect2d_Nega = CEffect2D::Create(3, DEFAULT_VECTOR);
    m_pEffect2d_Nega->SetUseUpdate(false);
    m_pEffect2d_Posi = CEffect2D::Create(3, DEFAULT_VECTOR);
    m_pEffect2d_Posi->SetUseUpdate(false);

    // �X�R�A�\���𐶐�
    m_pScore = CNumberArray::Create(12, D3DXVECTOR3(640.0f, 675.0f, 0.0f), NUMBER_SIZE_X_BALL_SPD, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 0, false);

    // BGM�������_���Đ�
    int nRand = GetRandNum(2, 0);
    switch (nRand)
    {
    case 0:
        CManager::SoundPlay(CSound::LABEL_BGM_BATTLE00);
        break;
    case 1:
        CManager::SoundPlay(CSound::LABEL_BGM_BATTLE01);
        break;
    case 2:
        CManager::SoundPlay(CSound::LABEL_BGM_BATTLE02);
        break;
    }

    //// ���̌����ڊm�F�p���f������
    //CDebug::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CDebug::TYPE_PERMANENT, 31);
    //CDebug::Create(D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CDebug::TYPE_PERMANENT, 0);

    //// ���̓G�z�u
    //D3DXVECTOR3 enemyPos = D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
    //bool bNextParagraph = false;
    //for (int nCnt = 1; nCnt < 26; nCnt++)
    //{
    //    if (bNextParagraph)
    //    {
    //        enemyPos.x = -2000.0f;
    //        bNextParagraph = false;
    //    }

    //    CEnemy::Create(CEnemy::TYPE_SPIDER, enemyPos);

    //    if (nCnt % 5 == 0)
    //    {
    //        enemyPos.z += 1000.0f;
    //        bNextParagraph = true;
    //    }
    //    
    //    enemyPos.x += 1000.0f;
    //}
    //CEnemy::Create(CEnemy::TYPE_SPIDER, D3DXVECTOR3(-1000.0f, 1000.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_SPIDER, D3DXVECTOR3(0.0f, 0.0f, 1500.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_PLAYER);
    //CEnemy::Create(CEnemy::TYPE_SPIDER, D3DXVECTOR3(1000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_WAIT_FORTRESS);
    //CEnemy::Create(CEnemy::TYPE_ARMY, D3DXVECTOR3(2000.0f, 0.0f, 0.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_KAMIKAZE, D3DXVECTOR3(2000.0f, 0.0f, 1000.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_CANNON, D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);
    //CEnemy::Create(CEnemy::TYPE_COMMANDER, D3DXVECTOR3(2000.0f, 0.0f, 3000.0f), 1.0f, CEnemy::APPEAR_STATE_EXIST);

    //// ���̓�����
    //D3DXVECTOR3 roadPos = D3DXVECTOR3(-1500.0f, 0.0f, -1500.0f);
    //for (int nCnt = 0; nCnt < 10; nCnt++)
    //{
    //    D3DXVECTOR3 rot = DEFAULT_VECTOR;
    //    if (nCnt < 5)
    //    {
    //        roadPos.z += 500.0f;
    //    }
    //    else
    //    {
    //        roadPos.x += 500.0f;
    //        rot = D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f);
    //    }
    //    CRoad::Create(roadPos, rot);
    //}
    
    //// �w�i����
    //CBg::Create(56, D3DXVECTOR3(0.0f, 0.0f, 3000.0f), CBg::COLOR_PHASE_G_UP);
    //CBg::Create(56, D3DXVECTOR3(-500.0f, 0.0f, 3000.0f), CBg::COLOR_PHASE_G_UP);
    //CBg::Create(56, D3DXVECTOR3(500.0f, 0.0f, 3000.0f), CBg::COLOR_PHASE_G_UP);

    //// �u���b�N����
    //CBlock::Create(CBlock::TYPE_FRAME, D3DXVECTOR3(-500.0f, 0.0f, 3000.0f), D3DXVECTOR3(5000.0f, 500.0f, 500.0f), DEFAULT_VECTOR);
    //CBlock::Create(CBlock::TYPE_GOAL_GATE, D3DXVECTOR3(5000.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 5000.0f), MODEL_DIRECT_LEFT);

    return S_OK;
}

//=============================================================================
// �I������
// Author : �㓡�T�V��
//=============================================================================
void CGame::Uninit(void)
{
    // �S�Ẳ����~
    CManager::SoundStopAll();

    // �|�[�Y��j��
    if (m_pPause != NULL)
    {
        m_pPause->Uninit();
        delete m_pPause;
        m_pPause = NULL;
    }
}

//=============================================================================
// �X�V����
// Author : �㓡�T�V��
//=============================================================================
void CGame::Update(void)
{
    // �Q�[����Ԃ̊Ǘ�
    ManageState();

    // ���]�����̏I���`�F�b�N
    if (m_pEffect2d_Nega && m_pEffect2d_Posi)
    {
        // �|�W�̂ق������̑傫���ɒB������A�ǂ�����T�C�Y��߂�
        if (m_pEffect2d_Posi->GetSize().x >= SCREEN_WIDTH * 2)
        {
            m_pEffect2d_Nega->SetSize(DEFAULT_VECTOR);
            m_pEffect2d_Posi->SetSize(DEFAULT_VECTOR);
            m_pEffect2d_Nega->SetUseUpdate(false);
            m_pEffect2d_Posi->SetUseUpdate(false);
            m_pEffect2d_Nega->SetRotVertex(0.0f);     // �X�V���~�߂����ɁA���_�͂����Œ���
            m_pEffect2d_Posi->SetRotVertex(0.0f);     // �X�V���~�߂����ɁA���_�͂����Œ���
        }
    }

}

//=============================================================================
// �Q�[����Ԃ̊Ǘ�
// Author : �㓡�T�V��
//=============================================================================
void CGame::ManageState(void)
{
    switch (m_state)
    {
    case STATE_ROUND_START:
        // ���E���h�J�n
        RoundStart();
        break;

    case STATE_BUTTLE:
        // �o�g����
        InButtle();
        break;

    case STATE_BLOW_MOMENT:
        // �ꌂ�̏u��
        BlowMoment();
        break;

    case STATE_FINISH:
        // ���s����
        JudgmentFinish();
        break;

    case STATE_PAUSE_MENU:
        // �|�[�Y�̍X�V
        m_pPause->Update();
        break;
    }
}

//=============================================================================
// ���E���h�J�n����
// Author : �㓡�T�V��
//=============================================================================
void CGame::RoundStart(void)
{
    // ���X�|�[������
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �������Ă��Ȃ��Ȃ�
        if (!m_apPlayer[nCntPlayer]->GetDisp())
        {
            m_apPlayer[nCntPlayer]->Respawn();
        }

        // �����E���h���Z�b�g����X�e�[�^�X
        m_apPlayer[nCntPlayer]->ResetStatusEveryRound();
    }

    // �J�E���^�����Z
    m_nCntGameTime++;

    // ���t���[���ŁA�o�g������
    if (m_nCntGameTime >= 180)
    {
        // �J�E���^���Z�b�g
        m_nCntGameTime = 0;

        //// �~�b�V�����X�^�[�g�\��
        //CUI::Create(UI_EXTEND_MISSION_POS, DEFAULT_VECTOR, DEFAULT_COLOR, CUI::TYPE_MISSION_START);

        // �o�g������
        m_state = STATE_BUTTLE;
    }
    else if (m_nCntGameTime == FADE_OUT_TELOP)
    {
        if (!m_bFirestRound)
        {
            // �l�N�X�g���E���h
            CUI *pTelopBg = CUI::GetAccessUI(4);
            CUI *pTelop = CUI::GetAccessUI(5);
            if (pTelopBg)
            {
                pTelopBg->SetActionLock(2, false);
            }
            if (pTelop)
            {
                pTelop->SetActionLock(2, false);
            }
        }
        else
        {
            // �t�@�[�X�g���E���h�̃t���O��؂�
            m_bFirestRound = false;

            // �o�g���X�^�[�g
            CUI *pTelopBg = CUI::GetAccessUI(2);
            CUI *pTelop = CUI::GetAccessUI(3);
            if (pTelopBg)
            {
                pTelopBg->SetActionLock(2, false);
            }
            if (pTelop)
            {
                pTelop->SetActionLock(2, false);
            }
        }
    }
    else if (m_nCntGameTime == FADE_IN_TELOP)
    {
        if (!m_bFirestRound)
        {
            // �l�N�X�g���E���h
            CUI *pTelopBg = CUI::GetAccessUI(4);
            CUI *pTelop = CUI::GetAccessUI(5);
            if (pTelopBg)
            {
                pTelopBg->SetActionReset(0);
                pTelopBg->SetActionLock(0, false);
                pTelopBg->SetActionReset(2);
            }
            if (pTelop)
            {
                pTelop->SetActionReset(0);
                pTelop->SetActionLock(0, false);
                pTelop->SetActionReset(1);
                pTelop->SetActionLock(1, false);
                pTelop->SetActionReset(2);
            }
        }
        else
        {
            // �o�g���X�^�[�g
            CUI *pTelopBg = CUI::GetAccessUI(2);
            CUI *pTelop = CUI::GetAccessUI(3);
            if (pTelopBg)
            {
                pTelopBg->SetActionReset(0);
                pTelopBg->SetActionLock(0, false);
                pTelopBg->SetActionReset(2);
            }
            if (pTelop)
            {
                pTelop->SetActionReset(0);
                pTelop->SetActionLock(0, false);
                pTelop->SetActionReset(1);
                pTelop->SetActionLock(1, false);
                pTelop->SetActionReset(2);
            }
        }
    }
}

//=============================================================================
// �o�g����
// Author : �㓡�T�V��
//=============================================================================
void CGame::InButtle(void)
{
    switch (m_type)
    {
    case TYPE_TRAINING:
    {
        // �C�ӂ̓G���o�������邽�߂̈ʒu
        D3DXVECTOR3 spawnPos = DEFAULT_VECTOR;
        const int SPAWN_RADIUS_MAX = 2750;
        const int SPAWN_RADIUS_MIN = 500;
        spawnPos.x = float(GetRandNum(SPAWN_RADIUS_MAX, SPAWN_RADIUS_MIN));
        spawnPos.z = float(GetRandNum(SPAWN_RADIUS_MAX, SPAWN_RADIUS_MIN));
        int nToggleX = GetRandNum(1, 0);
        if (nToggleX == 1)
        {
            spawnPos.x *= -1.0f;
        }
        int nToggleZ = GetRandNum(1, 0);
        if (nToggleZ == 1)
        {
            spawnPos.z *= -1.0f;
        }

        // �L�[�{�[�h����
        CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
        if (pInputKeyboard->GetKeyboardTrigger(DIK_1))
        {
            CEnemy::Create(CEnemy::TYPE_ARMY, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_2))
        {
            CEnemy::Create(CEnemy::TYPE_KAMIKAZE, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_3))
        {
            CEnemy::Create(CEnemy::TYPE_CANNON, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_4))
        {
            CEnemy::Create(CEnemy::TYPE_COMMANDER, spawnPos);
        }
        else if (pInputKeyboard->GetKeyboardTrigger(DIK_5))
        {
            CEnemy::Create(CEnemy::TYPE_SHINIGAMI, spawnPos);
        }
    }
        break;
    case TYPE_ARENA:
        //// �A���[�i���[�h��1�l�c������
        //if (m_nNumDefeatPlayer >= m_nNumAllPlayer - m_nNumDeathPlayer - 1)
        //{
        //    // ���̎c�����l���A1�ʂɂ���
        //    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
        //    {
        //        if (m_apPlayer[nCntPlayer]->GetDisp())
        //        {
        //            m_anPlayerRank[CPlayer::RANK_1] = m_apPlayer[nCntPlayer]->GetIdxControlAndColor();
        //            m_anPlayerRankInThisRound[CPlayer::RANK_1] = m_apPlayer[nCntPlayer]->GetIdxControlAndColor();
        //        }
        //    }

        //    // �ꌂ�̏u�Ԃ�
        //    m_state = STATE_BLOW_MOMENT;

        //    // �X�V���~�߂Ă���
        //    m_bStopObjUpdate = true;

        //    // ���҂Ɣs�҂̒�����
        //    CManager::GetCamera()->SetState(CCamera::STATE_FINISH_EACH);

        //    // ���̃t���[���̓|�[�Y�������Ȃ����߁A�֐��𔲂���
        //    return;
        //}
        break;
    }

    //================================================================================
    // �|�[�Y����
    if (!m_bStopObjUpdate && !m_bCurrentSpShot)
    {
        const int NO_PAUSE_PLAYER = -1; // �N���|�[�Y�������Ă��Ȃ�

                                        // �ϐ��錾
        CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();  // �L�[�{�[�h
        CInputJoypad *pInputJoypad = CManager::GetInputJoypad();        // �R���g���[��
        int nNumPausePlayer = NO_PAUSE_PLAYER;  // �|�[�Y���������v���C���[

                                                // �X�^�[�g�{�^�����������l�����т���
        if (pInputJoypad->GetJoypadTrigger(PLAYER_1, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_1;
        }
        else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_2;
        }
        else if (pInputJoypad->GetJoypadTrigger(PLAYER_3, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_3;
        }
        else if (pInputJoypad->GetJoypadTrigger(PLAYER_4, XINPUT_GAMEPAD_START))
        {
            nNumPausePlayer = PLAYER_4;
        }

        // �|�[�Y����Ȃ�
        if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || nNumPausePlayer != NO_PAUSE_PLAYER)
        {
            // SE
            CManager::SoundPlay(CSound::LABEL_SE_OPEN_POSE);

            // �L�[�{�[�h����Ń|�[�Y����ۂ́A1P�̃R���g���[�����g��
            if (nNumPausePlayer == NO_PAUSE_PLAYER)
            {
                nNumPausePlayer = PLAYER_1;
            }

            // �|�[�Y��Ԃɂ���
            m_state = STATE_PAUSE_MENU;
            m_pPause->SetPauseMenuSelect(nNumPausePlayer);
            m_bStopObjUpdate = true;

            // �J�������~�߂�
            CManager::GetCamera()->SetState(CCamera::STATE_NONE);
        }
    }
    //================================================================================
}

//=============================================================================
// �ꌂ�̏u��
// Author : �㓡�T�V��
//=============================================================================
void CGame::BlowMoment(void)
{
    // �w�i�ƍ������擾
    CUI *pBg = CUI::GetAccessUI(100);
    CUI *pLine = CUI::GetAccessUI(101);
    // �w�i�ƍ�����������悤��
    if (pBg)
    {
        pBg->SetDisp(true);
    }
    if (pLine)
    {
        pLine->SetDisp(true);
    }

    // �J�E���^�����Z
    m_nCntGameTime++;

    // ���t���[���ŁA���s����
    if (m_nCntGameTime >= BLOW_MOMENT_FRAME)
    {
        // �w�i�ƍ����������Ȃ��悤��
        if (pBg)
        {
            pBg->SetDisp(false);
        }
        if (pLine)
        {
            pLine->SetDisp(false);
        }

        // �J�E���^�����Z�b�g
        m_nCntGameTime = 0;

        // �J�����̃��b�N�I���ꏊ�����Z�b�g
        CManager::GetCamera()->CCamera::ResetCamera(DEFAULT_VECTOR, CAMERA_DEFAULT_ROT, CCamera::SETTING_GAME);

        // �X�V�J�n
        m_bStopObjUpdate = false;

        // ���s�����
        m_state = STATE_FINISH;

        // �ꌂ�̏u�Ԏ��A�O�̂��߃��Z�b�g�������
        BlowMomentMakeSureReset();
    }
}

//=============================================================================
// �ꌂ�̏u�Ԏ��A�O�̂��߃��Z�b�g�������
// Author : �㓡�T�V��
//=============================================================================
void CGame::BlowMomentMakeSureReset(void)
{
    // ���]�������A�O�̂��ߎ~�߂�iAI�悢���m�Ő�킹���ہA���]�������߂�Ȃ��܂܃Q�[�����i�s�������߁j�i���ł��n��1F�ɓ�����������?�j
    if (m_pEffect2d_Nega && m_pEffect2d_Posi)
    {
        m_pEffect2d_Nega->SetSize(DEFAULT_VECTOR);
        m_pEffect2d_Posi->SetSize(DEFAULT_VECTOR);
        m_pEffect2d_Nega->SetUseUpdate(false);
        m_pEffect2d_Posi->SetUseUpdate(false);
        m_pEffect2d_Nega->SetRotVertex(0.0f);     // �X�V���~�߂����ɁA���_�͂����Œ���
        m_pEffect2d_Posi->SetRotVertex(0.0f);     // �X�V���~�߂����ɁA���_�͂����Œ���
    }

    // ���ݕK�E�Z���g���Ă���󋵂��A�O�̂��߃��Z�b�g����i�K�E�Z���g��������1F�ɓ|�����ƁA�����̃t���O���߂�Ȃ��Ȃ������߁j
    m_bCurrentSpShot = false;
    if (m_pSpText)
    {
        m_pSpText->SetColor(TEXT_NOT_EXIST_COLOR);
    }
}

//=============================================================================
// ���s����
// Author : �㓡�T�V��
//=============================================================================
void CGame::JudgmentFinish(void)
{
    // �J�E���^�����Z
    m_nCntGameTime++;

    // ���t���[���ŁA���s����
    if (m_nCntGameTime >= FINISH_WAIT_FRAME)
    {
        // �J�E���^�����Z�b�g
        m_nCntGameTime = 0;

        // ���U���g��ʂɓn�����߂̏��������Ă���
        for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
        {
            m_aInfoInResult[nCntPlayer].nIdxControlAndColor = m_apPlayer[nCntPlayer]->GetIdxControlAndColor();
            m_aInfoInResult[nCntPlayer].nContributionPoint = m_apPlayer[nCntPlayer]->GetContributionPoint();
        }

        //// ���񂾃v���C���[���S�̂̃v���C���[-1�ɒB������
        //if (m_nNumDeathPlayer >= m_nNumAllPlayer - 1)
        //{
            // ���U���g�Ɉڍs
            CFade::SetFade(CManager::MODE_RESULT);
        //}
        //else
        //{
        //    // ���ꂽ�v���C���[�l�������Z�b�g
        //    m_nNumDefeatPlayer = 0;

        //    // ������x���E���h�J�n��
        //    m_state = STATE_ROUND_START;
        //}
    }
    else if (m_nCntGameTime == FADE_IN_FINISH_TELOP)
    {
        //// ���񂾃v���C���[���S�̂̃v���C���[-1�ɒB������
        //if (m_nNumDeathPlayer >= m_nNumAllPlayer - 1)
        //{
        //    // SE
        //    CManager::SoundPlay(CSound::LABEL_SE_FINISH);

        //    // �t�B�j�b�V��
        //    CUI *pTelopBg = CUI::GetAccessUI(6);
        //    CUI *pTelop = CUI::GetAccessUI(7);
        //    if (pTelopBg)
        //    {
        //        pTelopBg->SetActionReset(0);
        //        pTelopBg->SetActionLock(0, false);
        //        pTelopBg->SetActionReset(2);
        //    }
        //    if (pTelop)
        //    {
        //        pTelop->SetActionReset(0);
        //        pTelop->SetActionLock(0, false);
        //        pTelop->SetActionReset(1);
        //        pTelop->SetActionLock(1, false);
        //        pTelop->SetActionReset(2);
        //    }
        //}
    }
}

//========================================
// ������Ԃɂ��邽�߂̊֐�
// Author : �㓡�T�V��
//========================================
void CGame::SetFinish(bool bWin)
{
    m_bWin = bWin;
    m_state = STATE_FINISH;
}

//========================================
// ��ԋ߂��v���C���[�ւ̊p�x�����߂�
// Author : �㓡�T�V��
//========================================
float CGame::GetAngleToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer)
{
    // �ϐ��錾
    float fAngle = 0.0f;                        // �Ԃ��p�x
    float fFirstDistance = DISTANCE_INIT_VALUE; // ����
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;     // �Ώۂ̈ʒu

    // �Ώۂ̈ʒu���A�����̐��ʂֈ�x���߂Ă���
    targetPos = D3DXVECTOR3(myPos.x + DEFAULT_INIT_DISTANCE, 0.0f, myPos.z);

    // ��������ԋ߂��v���C���[�����߂�i�����ȊO�Łj
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �����ȊO��
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // �������Ă���Ȃ�
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // ���̃v���C���[�̈ʒu
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // ���������߂�
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // �����̔�r�ƁA�Ώۂ̈ʒu���X�V
            if (fFirstDistance > fSecondDistance)
            {
                fFirstDistance = fSecondDistance;
                targetPos = otherPlayerPos;
            }
        }
    }

    // �p�x�����߂�
    fAngle = atan2((targetPos.x - myPos.x), (targetPos.z - myPos.z));

    return fAngle;
}

//========================================
// ��ԋ߂��v���C���[�̈ʒu�����߂�
// Author : �㓡�T�V��
//========================================
D3DXVECTOR3 CGame::GetPosToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer)
{
    // �ϐ��錾
    float fFirstDistance = DISTANCE_INIT_VALUE; // ����
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;     // �Ώۂ̈ʒu

    // �Ώۂ̈ʒu���A�����̐��ʂֈ�x���߂Ă���
    targetPos = D3DXVECTOR3(myPos.x + DEFAULT_INIT_DISTANCE, 0.0f, myPos.z);

    // ��������ԋ߂��v���C���[�����߂�i�����ȊO�Łj
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �����ȊO��
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // �������Ă���Ȃ�
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // ���̃v���C���[�̈ʒu
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // ���������߂�
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // �����̔�r�ƁA�Ώۂ̈ʒu���X�V
            if (fFirstDistance > fSecondDistance)
            {
                fFirstDistance = fSecondDistance;
                targetPos = otherPlayerPos;
            }
        }
    }

    return targetPos;
}

//========================================
// ��ԋ߂��v���C���[�Ƃ̋����ƃ|�C���^�𓾂�
// Author : �㓡�T�V��
//========================================
CCharacter *CGame::GetDistanceAndPointerToClosestPlayer(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer)
{
    // �ϐ��錾
    CCharacter*pTarget = NULL;

    // ��������ԋ߂��v���C���[�����߂�i�����ȊO�Łj
    fKeepDistance = DISTANCE_INIT_VALUE;
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �����ȊO��
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // �������Ă���Ȃ�
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // ���̃v���C���[�̈ʒu
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // ���������߂�
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // �����̔�r�ƁA�Ώۂ̃|�C���^���X�V
            if (fKeepDistance > fSecondDistance)
            {
                fKeepDistance = fSecondDistance;
                pTarget = (CCharacter*)m_apPlayer[nCntPlayer];
            }
        }
    }

    return pTarget;
}

//========================================
// ��ԋ߂��v���C���[�Ƃ̋����ƃ|�C���^�𓾂�_�d�r�o�[�W����
// Author : �㓡�T�V��
//========================================
CPlayer *CGame::GetDistanceAndPointerToClosestPlayer_Denti(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer)
{
    // �ϐ��錾
    CPlayer*pTarget = NULL;

    // ��������ԋ߂��v���C���[�����߂�i�����ȊO�Łj
    fKeepDistance = DISTANCE_INIT_VALUE;
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �����ȊO��
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // �������Ă��邩�A�`���[�W�ʂ��ő�łȂ��Ȃ�
        if (m_apPlayer[nCntPlayer]->GetDisp() && m_apPlayer[nCntPlayer]->GetCurrentEnergy() < m_apPlayer[nCntPlayer]->GetCurrentEnergyMax())
        {
            // ���̃v���C���[�̈ʒu
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // ���������߂�
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // �����̔�r�ƁA�Ώۂ̃|�C���^���X�V
            if (fKeepDistance > fSecondDistance)
            {
                fKeepDistance = fSecondDistance;
                pTarget = m_apPlayer[nCntPlayer];
            }
        }
    }

    return pTarget;
}

//========================================
// ��ԋ߂��v���C���[���ړ��v�ǂƂ̋����ƃ|�C���^�𓾂�
// Author : �㓡�T�V��
//========================================
CCharacter *CGame::GetDistanceAndPointerToClosestPlayerOrFortress(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer)
{
    // �ϐ��錾
    CCharacter*pTarget = NULL;

    // ��������ԋ߂��v���C���[�����߂�i�����ȊO�Łj
    fKeepDistance = DISTANCE_INIT_VALUE;
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �����ȊO��
        if (nIdxPlayer == nCntPlayer)
        {
            continue;
        }

        // �������Ă���Ȃ�
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            // ���̃v���C���[�̈ʒu
            D3DXVECTOR3 otherPlayerPos = m_apPlayer[nCntPlayer]->GetPos();

            // ���������߂�
            float fSecondDistance = sqrtf(
                powf((myPos.x - otherPlayerPos.x), 2.0f) +
                powf((myPos.z - otherPlayerPos.z), 2.0f));

            // �����̔�r�ƁA�Ώۂ̃|�C���^���X�V
            if (fKeepDistance > fSecondDistance)
            {
                fKeepDistance = fSecondDistance;
                pTarget = (CCharacter*)m_apPlayer[nCntPlayer];
            }
        }
    }

    // ��������ԋ߂��v���C���[�ƈړ��v�ǂłǂ��炪�߂�����ׂ�
    D3DXVECTOR3 fortressPos = m_pFortress->GetPos();
    float fDistanceToFortress = sqrtf(
        powf((myPos.x - fortressPos.x), 2.0f) +
        powf((myPos.z - fortressPos.z), 2.0f));
    if (fKeepDistance > fDistanceToFortress)
    {
        fKeepDistance = fDistanceToFortress;
        pTarget = (CCharacter*)m_pFortress;
    }

    return pTarget;
}

//========================================
// ��ԋ߂��ړ��v�ǂƂ̋����ƃ|�C���^�𓾂�
// Author : �㓡�T�V��
//========================================
CCharacter *CGame::GetDistanceAndPointerToClosestFortress(D3DXVECTOR3 myPos, float &fKeepDistance)
{
    // �ϐ��錾
    CCharacter*pTarget = NULL;

    // ��������ԋ߂��ړ��v�ǂ��߂�����ׂ�
    fKeepDistance = DISTANCE_INIT_VALUE;

    // �������Ă��Ȃ��Ȃ�A�֐��𔲂���
    if (!m_pFortress->GetDisp())
    {
        return NULL;
    }

    D3DXVECTOR3 fortressPos = m_pFortress->GetPos();
    float fDistanceToFortress = sqrtf(
        powf((myPos.x - fortressPos.x), 2.0f) +
        powf((myPos.z - fortressPos.z), 2.0f));
    if (fKeepDistance > fDistanceToFortress)
    {
        fKeepDistance = fDistanceToFortress;
        pTarget = (CCharacter*)m_pFortress;
    }

    return pTarget;
}

//========================================
// �{�[�����˃Q�[�W�̐ݒ�
// Author : �㓡�T�V��
//========================================
void CGame::SetBallGauge(int nMax, int nNow)
{
    // UI���擾
    CUI *pBallGaugeR = CUI::GetAccessUI(0);
    CUI *pBallGaugeL = CUI::GetAccessUI(1);

    // ���E�̃Q�[�W��ݒ�
    if (pBallGaugeR)
    {
        pBallGaugeR->SetLeftToRightGauge((float)nMax, (float)nNow);
    }
    if (pBallGaugeL)
    {
        pBallGaugeL->SetRightToLeftGauge((float)nMax, (float)nNow);
    }
}

//=============================================================================
// �}�b�v��������
// Author : �㓡�T�V��
//=============================================================================
HIT_SURFACE CGame::MapLimit(D3DXVECTOR3 &pos, D3DXVECTOR3 posOld, D3DXVECTOR3 myCubeSize)
{
    HIT_SURFACE returnHitSurface = HIT_SURFACE_NONE;

    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
    {
        // ���g������Ȃ�
        if (pScene)
        {
            // ���̃V�[�����L��
            CScene*pNextScene = pScene->GetNextScene();

            // �u���b�N�ɃL���X�g
            CBlock *pBlock = (CBlock*)pScene;

            // �}�b�v�����𔽉f
            HIT_SURFACE hitSurface = IsBlockCollisionXZ(pos, posOld, pBlock->GetPos(), myCubeSize, pBlock->GetCollisionSize());
            if (hitSurface != HIT_SURFACE_NONE)
            {
                returnHitSurface = hitSurface;
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }

    return returnHitSurface;
}

//========================================
// ��ԋ߂��G�̈ʒu�����߂�
// Author : �㓡�T�V��
//========================================
D3DXVECTOR3 CGame::GetPosToClosestEnemy(D3DXVECTOR3 myPos)
{
    // �ϐ��錾
    float fFirstDistance = DISTANCE_INIT_VALUE; // ����
    D3DXVECTOR3 targetPos = DEFAULT_VECTOR;     // �Ώۂ̈ʒu

    // �Ώۂ̈ʒu���A�����̐��ʂֈ�x���߂Ă���
    targetPos = D3DXVECTOR3(myPos.x + DEFAULT_INIT_DISTANCE, 0.0f, myPos.z);

    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
    {
        // ���g������Ȃ�
        if (pScene)
        {
            // ���̃V�[�����L��
            CScene*pNextScene = pScene->GetNextScene();

            // �G�ɃL���X�g
            CEnemy *pEnemy = (CEnemy*)pScene;

            // �o�����Ă���Ȃ�
            if (pEnemy->GetAppearState() == CEnemy::APPEAR_STATE_EXIST)
            {
                // �G�̈ʒu
                D3DXVECTOR3 enemyPos = pEnemy->GetPos();

                // ���������߂�
                float fSecondDistance = sqrtf(
                    powf((myPos.x - enemyPos.x), 2.0f) +
                    powf((myPos.z - enemyPos.z), 2.0f));

                // �����̔�r�ƁA�Ώۂ̈ʒu���X�V
                if (fFirstDistance > fSecondDistance)
                {
                    fFirstDistance = fSecondDistance;
                    targetPos = enemyPos;
                }
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }

    return targetPos;
}

//========================================
// ��ԋ߂��G�̒e�̋��������߂�
// Author : �㓡�T�V��
//========================================
float CGame::GetDistanceToClosestEnemyBullet(D3DXVECTOR3 myPos)
{
    // �ϐ��錾
    float fFirstDistance = DISTANCE_INIT_VALUE; // ����

    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BULLET);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BULLET); nCntScene++)
    {
        // ���g������Ȃ�
        if (pScene)
        {
            // ���̃V�[�����L��
            CScene*pNextScene = pScene->GetNextScene();

            // �G�ɃL���X�g
            CBullet *pBullet = (CBullet*)pScene;

            // �G�̒e�Ȃ�
            if (pBullet->GetWhoShot() == CScene::OBJTYPE_ENEMY)
            {
                // �e�̈ʒu
                D3DXVECTOR3 bulletPos = pBullet->GetPos();

                // ���������߂�
                float fSecondDistance = sqrtf(
                    powf((myPos.x - bulletPos.x), 2.0f) +
                    powf((myPos.z - bulletPos.z), 2.0f));

                // �����̔�r�ƁA�Ώۂ̈ʒu���X�V
                if (fFirstDistance > fSecondDistance)
                {
                    fFirstDistance = fSecondDistance;
                }
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
    }

    return fFirstDistance;
}

//========================================
// �X�R�A�����Z���鏈��
// Author : �㓡�T�V��
//========================================
void CGame::AddScore(const int nScore)
{
    m_nScore += nScore;
    m_pScore->SetDispNumber(m_nScore);
}

//========================================
// �v���C���[���N�����瑶�݂��Ă��邩�擾����
// Author : �㓡�T�V��
//========================================
bool CGame::GetDispAnyPlayer(void)
{
    for (int nCntPlayer = 0; nCntPlayer < m_nNumAllPlayer; nCntPlayer++)
    {
        // �������Ă���Ȃ�
        if (m_apPlayer[nCntPlayer]->GetDisp())
        {
            return true;
        }
    }

    return false;
}