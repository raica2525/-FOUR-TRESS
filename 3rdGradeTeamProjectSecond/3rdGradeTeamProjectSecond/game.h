//=============================================================================
//
// �Q�[������ [game.h]
// Author : �㓡�T�V��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "mode.h"
#include "player.h"
#include "library.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPause;
class CUI;
class CEffect2D;
class CNumberArray;
class CText;
class CFortress;

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame : public CMode
{
public:

    // �Q�[���̎��
    typedef enum
    {
        TYPE_TRAINING = 0,     // �g���[�j���O
        TYPE_ARENA,            // ���Z��
        TYPE_MINI,             // �~�j�Q�[��
        TYPE_MAX			   // ��Ԃ̍ő吔
    }TYPE;

    // �Q�[���̏�ԁi���j
    typedef enum
    {
        STATE_ROUND_START = 0,     // �J�n
        STATE_BUTTLE,              // �o�g����
        STATE_BLOW_MOMENT,         // �ꌂ�̏u��
        STATE_FINISH,              // ����
        STATE_PAUSE_MENU,	       // �|�[�Y���j���[
        STATE_MAX			       // ��Ԃ̍ő吔
    }STATE;

    CGame();
    ~CGame();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);

    void ManageState(void);     // �Q�[����Ԃ̊Ǘ�
    void RoundStart(void);      // ���E���h�J�n
    void InButtle(void);        // �o�g����
    void BlowMoment(void);      // �ꌂ�̏u��
    void BlowMomentMakeSureReset(void);   // �ꌂ�̏u�Ԏ��A�O�̂��߃��Z�b�g�������
    void JudgmentFinish(void);  // ���s����

    /*========================================================
    // �Z�b�^�[
    //======================================================*/
    static void SetNextGameInDebug(TYPE gameType, int nNumPlayer, bool bUseKeyboard = false)
    {
        m_type = gameType;  m_nNumAllPlayer = nNumPlayer; m_bUseKeyboard = bUseKeyboard;
    }   // �f�o�b�O���j���[�ŁA���̃Q�[����ݒ�
    static void SetNextGameInCustom(TYPE gameType, int nNumPlayer)
    {
        m_type = gameType;  m_nNumAllPlayer = nNumPlayer;
    }   // �J�X�^�}�C�Y��ʂŁA���̃Q�[����ݒ�
    static void SetIdxPlayer(int nNum, int nIdxPlayer) { m_anMemoryIdxPlayer[nNum] = nIdxPlayer; }  // �v���C���[�̃C���f�b�N�X
    static void SetAILevel(int nNum, CPlayer::AI_LEVEL level) { m_aMemoryAILevel[nNum] = level; }   // AI���x��
    static void SetRole(int nNum, int role) { m_anMemoryRole[nNum] = role; }   // ����
    static void SetQuitPause(void) { m_state = STATE_BUTTLE; m_bStopObjUpdate = false; }    // �|�[�Y��Ԃ���߂�
    static void SetUseKeyboard(bool bUseKeyboard) { m_bUseKeyboard = bUseKeyboard; }
    static void SetSpPlayer(CPlayer *pPlayer) { m_bCurrentSpShot = true; m_pSpPlayer = pPlayer; }
    static void SetCurrentSpShot(bool bStopUpdate) { m_bCurrentSpShot = bStopUpdate; }

    /*========================================================
    // �Q�b�^�[
    //======================================================*/
    static STATE GetState(void) { return m_state; }                                 // �Q�[���̏�Ԃ��擾
    static CPlayer* GetPlayer(const int nNum) { return m_apPlayer[nNum]; }          // �v���C���[���擾
    static int GetNumAllPlayer(void) { return m_nNumAllPlayer; }                    // �S�̃v���C���[�l�����擾
    static TYPE GetType(void) { return m_type; }                                    // �Q�[����ނ��擾
    static bool GetStopObjUpdate(void) { return m_bStopObjUpdate; }                 // �I�u�W�F�N�g�̃A�b�v�f�[�g���~�߂邩�ǂ���
    static CEffect2D* GetNega(void) { return m_pEffect2d_Nega; }                    // ���]�����̃G�t�F�N�g���擾
    static CEffect2D* GetPosi(void) { return m_pEffect2d_Posi; }                    // ���]������߂����߂̃G�t�F�N�g���擾
    static bool GetUseKeyboard(void) { return m_bUseKeyboard; }                     // �L�[�{�[�h���g�����ǂ����擾
    static CPlayer*GetSpPlayer(void) { return m_pSpPlayer; }
    static bool GetCurrentSpShot(void) { return m_bCurrentSpShot; }
    static CText *GetSpText(void) { return m_pSpText; }
    static CFortress *GetFortress(void) { return m_pFortress; }

    /*========================================================
    // �֗��Ȋ֐�
    //======================================================*/
    static float GetAngleToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer = NOT_EXIST);    // ��ԋ߂��v���C���[�ւ̊p�x�����߂�
    static D3DXVECTOR3 GetPosToClosestPlayer(D3DXVECTOR3 myPos, int nIdxPlayer = NOT_EXIST);// ��ԋ߂��v���C���[�̈ʒu�����߂�
    static CCharacter *GetDistanceAndPointerToClosestPlayer(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer = NOT_EXIST);
    static CPlayer *GetDistanceAndPointerToClosestPlayer_Player(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer = NOT_EXIST);
    static CCharacter *GetDistanceAndPointerToClosestPlayerOrFortress(D3DXVECTOR3 myPos, float &fKeepDistance, int nIdxPlayer = NOT_EXIST);
    static CCharacter *GetDistanceAndPointerToClosestFortress(D3DXVECTOR3 myPos, float &fKeepDistance);
    static void SetBallGauge(int nMax, int nNow);                                   // �{�[�����˃Q�[�W
    static int GetCharacterIdx(void) 
    { 
        m_nCharacterIdx++;
        if (m_nCharacterIdx >= CHARACTER_IDX_MAX)
        {
            m_nCharacterIdx = CHARACTER_IDX_MIN_IN_RESET;
        }
        return m_nCharacterIdx;
    }
    static HIT_SURFACE MapLimit(D3DXVECTOR3 &pos, D3DXVECTOR3 posOld, D3DXVECTOR3 myCubeSize); // �}�b�v����
    static D3DXVECTOR3 GetPosToClosestEnemy(D3DXVECTOR3 myPos);// ��ԋ߂��G�̈ʒu�����߂�

private:

    static bool m_bStopObjUpdate;                          // �I�u�W�F�N�g�̃A�b�v�f�[�g���~�߂邩�ǂ���
    static CPlayer *m_apPlayer[MAX_PLAYER];                // �v���C���[�̃|�C���^
    static CPause *m_pPause;                               // �|�[�Y�̃|�C���^
    static CEffect2D *m_pEffect2d_Nega;                    // ���]�����ւ̃|�C���^
    static CEffect2D *m_pEffect2d_Posi;                    // ���]������߂����߂̃|�C���^

    static TYPE m_type;                                    // �Q�[�����
    static int m_nNumAllPlayer;                            // �S�̃v���C���[�l��
    static bool m_bUseKeyboard;                            // �L�[�{�[�h���g�����ǂ���
    static int m_anMemoryIdxPlayer[MAX_PLAYER];            // �v���C���[�̃C���f�b�N�X���L��
    static CPlayer::AI_LEVEL m_aMemoryAILevel[MAX_PLAYER]; // AI���x�����L��
    static int m_anMemoryRole[MAX_PLAYER];                 // �������L��
    static STATE m_state;                                  // ���

    static CPlayer *m_pSpPlayer;                           // �X�g���C�N�V���[�g�v���C���[�̃|�C���^
    static bool m_bCurrentSpShot;                          // ���݃X�g���C�N�V���[�g�������Ă��邩�ǂ���
    static CText *m_pSpText;                               // �X�g���C�N�V���[�g�̖��O

    int m_nCntGameTime;                                    // �Q�[�����Ԃ̃J�E���^
    bool m_bFirestRound;                                   // �ŏ��̃��E���h���ǂ���

    static CFortress *m_pFortress;                         // �ړ��v�ǂ̃|�C���^
    static int m_nCharacterIdx;                            // �L�����N�^�[�̃C���f�b�N�X
};

#endif