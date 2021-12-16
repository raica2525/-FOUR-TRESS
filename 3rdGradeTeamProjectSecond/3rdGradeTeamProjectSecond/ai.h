//====================================================================
//
// AI���� (ai.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _AI_H_
#define _AI_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "player.h"

//================================================
// �N���X�錾
//================================================

// AI�N���X
class CAi
{
public:
    CAi();
    ~CAi();

    // �{�^���̓��͏��
    typedef struct
    {
        bool bButtonA;
        bool bButtonX;
        bool bButtonB;
        bool bButtonR2;
    }ButtonState;

    // �S�����Ă��邱��
    typedef enum
    {
        CORE_THINKING = 0, // �l����
        CORE_ASSAULT,      // ���P�i�K���U�߁j
        CORE_AVOID,        // ������i�K�������j
        CORE_WAIT,         // �҂i�K���҂��j
        CORE_MAX
    }CORE;

    void Update(void);						    // �X�V����
    static CAi * Create(CPlayer *pPlayer);		// �C���X�^���X��������
    void Thinking(void);                        // �l����
    void AnotherAction(void);                   // �l����ȊO�̍s����
    void GetThinkingTime(void);                 // �l�����Ԃ𓾂�
    void GetAssaultTime(void);                  // ���P���Ԃ𓾂�
    void GetAvoidTime(void);                    // �����鎞�Ԃ𓾂�
    void GetWaitTime(void);                     // �҂��Ԃ𓾂�
    void DontMove(bool bUseTurn);               // �ړ����Ȃ�
    bool IsFacingEnemy(void);                   // �G�l�~�[�̕��������Ă��邩
    void RushToTarget(void);                    // �^�[�Q�b�g�ɋl�ߊ��
    void RunAwayFromBall(void);                 // �{�[�����瓦����
    bool JumpBecauseEnemyBulletClose(void);     // �G�̒e���߂�����W�����v����
    bool JumpBecauseBallMoveDown(void);         // �{�[�����������Ă��Ă��邩��W�����v����
    bool DecideAttack(void);                    // ���߂���U�������邩�ǂ���
    void GetAttackAngle(void);                  // �U�����ɂǂ̕����ɃX�e�B�b�N��|����

    void GetTargetPos(void);                    // �^�[�Q�b�g�̈ʒu�����߂�
    void GetAttackRange(void);                  // �U���̎˒��𓾂�

private:
    CPlayer *m_pPlayer;
    ButtonState m_buttonStateOld;   // 1F�O�̃{�^�����͏��

    CORE m_core;                    // ���݉���S�����Ă��邩
    int m_nCntActionTime;           // �s���̃J�E���^

    D3DXVECTOR3 m_targetPos;        // �W�I�̈ʒu
    int m_nCntSearchTarget;         // �W�I��T�����߂̃J�E���^
    float m_fAttackRange;           // �U���̎˒�
};

#endif