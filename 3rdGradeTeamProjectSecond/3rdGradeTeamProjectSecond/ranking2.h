//====================================================================
//
// �����L���O2���� (ranking2.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _RANKING2_H_
#define _RANKING2_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"

//================================================
// �O���錾(�s���S�ȃN���X�́Acpp�̕��Ńw�b�_���Ăяo��)
//================================================
class CNumber;

//================================================
// �}�N����`
//================================================
#define RANKING2_FIRST_POS D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 665.0f, 0.0f)   // �����L���O2�̍ŏ��̈ʒu
#define RANKING2_CREATE_SCORE_SIZE D3DXVECTOR3(200.0f, 40.0f, 0.0f)   // �����L���O2�̈�̑傫��
#define MAX_RANKING2_NUMBER 48                                                   // �����L���O2�̐����̍ő吔(�����̃X�R�A�ƁA8��*5�ʂ܂�)

#define RANKING2_SCORE_MAX (6)   //5�ʂ܂�(������6�̒l���v�Z���邽��6)

//================================================
// �N���X�錾
//================================================

// �����L���O2�̃N���X
class CRanking2 : public CScene
{
public:
    CRanking2();
    ~CRanking2();
    static CRanking2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void ReleaseNumber(int nCntNumber);   // �������J��
    void Update(void);
    void Draw(void);

    void SetNumber(int nPlayScore, int nStartIndex);    // �X�R�A���i���o�[�ɓn���ĕ\������֐�
    void ReadScore(void);                               // �O���t�@�C������X�R�A��ǂݍ���
    bool RankIn(int nScore);                            // �����N�C���������ǂ���

    void FadeInNumber(int nCnt);                        // �t�F�[�h�C�����鐔��
    int SwapScoreNumberIndex(int nIndex);               // �X�R�A�̐����̃C���f�b�N�X�����ւ���

private:
    static CNumber *m_apNumber[MAX_RANKING2_NUMBER];  // �������
    int m_nCntTime;                                  // ���Ԃ𐔂���
    int m_aRankingScore[RANKING2_SCORE_MAX];		     // ��r����X�R�A
    int m_aRank[RANKING2_SCORE_MAX];                  // �����N�t�����邽��
    float m_aAlpha[MAX_RANKING2_NUMBER];              // �e�����̃��l
};

#endif