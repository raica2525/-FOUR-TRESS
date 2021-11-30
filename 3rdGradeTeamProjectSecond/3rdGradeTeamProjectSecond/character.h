//==========================================================================================
//
// �L�����N�^�[�̏��� (character.h)
// Author : �㓡�T�V��
//
//==========================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene.h"
#include "model.h"
#include "ui.h"

//================================================
// �}�N����`
//================================================
#define CHARCTER_PARTS_MAX 18    // �L�����N�^�[�̃p�[�c�̍ő吔

#define TAKE_DAMAGE_BORDER_DAMAGE 500.0f             // �����ꂩ�����̋��ڃ_���[�W
#define TAKE_DAMAGE_SMALL_FRAME 30                   // �������t���[����
#define TAKE_DAMAGE_BIG_FRAME 180                    // ������t���[����
#define TAKE_DAMAGE_LUCKY_GUARD_FRAME 40             // �������b�L�[�K�[�h�t���[����
#define KNOCK_BACK_SMALL 10.0f                       // �m�b�N�o�b�N�ʁi�������j
#define KNOCK_BACK_BIG 22.5f                         // �m�b�N�o�b�N�ʁi������j
#define KNOCK_BACK_LUCKY_GUARD 25.0f                 // �m�b�N�o�b�N�ʁi���b�L�[�K�[�h�j
#define KNOCK_BACK_DEATH_X 25.0f                     // �m�b�N�o�b�N�ʁi���S��X�j
#define KNOCK_BACK_DEATH_Y 12.5f                     // �m�b�N�o�b�N�ʁi���S��Y�j
#define KNOCK_BACK_STOP_BORDER 7.5f                  // �m�b�N�o�b�N���~�܂����Ƃ݂Ȃ����E�l

//================================================
// �O���錾 
//================================================
class CModel;
class CAnimation;
class CEffect3D;
class CUI;

//================================================
// �N���X�錾
//================================================

// �L�����N�^�[�N���X
class CCharacter : public CScene
{
public:

    // �������
    typedef enum
    {
        DAMAGE_STATE_NONE = 0,      // �Ȃ�
        DAMAGE_STATE_SMALL,         // �̂�����
        DAMAGE_STATE_BIG,           // �_�E��
        DAMAGE_STATE_STAND_UP,      // �N���オ��
        DAMAGE_STATE_BLOWN,         // ������΂���
        DAMAGE_STATE_MAX,
    }DAMAGE_STATE;

    // HP�\���̎��
    typedef enum
    {
        HP_DISP_NONE = -1,      // �\���Ȃ�
        HP_DISP_PLAYER_1,       // �v���C���[1
        HP_DISP_PLAYER_2,       // �v���C���[2
        HP_DISP_PLAYER_3,       // �v���C���[3
        HP_DISP_PLAYER_4,       // �v���C���[4
        HP_DISP_FOLLOW,         // �Ǐ]
    }HP_DISP;

    CCharacter(OBJTYPE objType);
    ~CCharacter();

    virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void CreateHPGauge(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    void DeathDraw(void);                                         // ���ꂽ���̕`��
    void LoadModelData(char* cFilePass);                          // �e�L�X�g�t�@�C�����璼�ړǂݍ��ގ��Ɏg���֐�
    void LoadModelData(int nModelPosDefUp, int nModelPosDefDown); // ���f���̏����ʒu�f�[�^����ǂݍ��ނƂ��Ɏg���֐�
    void RotControl(void);                                        // �����𒲐�
    bool TakeDamage(float fDamage, D3DXVECTOR3 damagePos, D3DXVECTOR3 damageOldPos, int effectType = 20);   // �_���[�W���󂯂�
    void CntDownTakeDamageTime(void);                             // �_���[�W���󂯂����Ԃ��J�E���g
    void ControlMove(float& fMove, bool bGround = true);          // �ړ��ʐ���

    /*========================================================
    // �Z�b�^�[
    //======================================================*/
    void SetPartPos(int index, D3DXVECTOR3 pos) { m_apModel[index]->SetPos(pos); }
    void SetPartRot(int index, D3DXVECTOR3 rot) { m_apModel[index]->SetRot(rot); }
    void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
    void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
    void SetRotY(const float fRotY) { m_rot.y = fRotY; }
    void SetPartNum(int nPartNum) { m_nPartsNum = nPartNum; }                       // �p�[�c�̍ő吔��ݒ�
    void SetPosOld(const D3DXVECTOR3 posOld) { m_posOld = posOld; }
    void SetAnimFilePass(char* cFilePass) { m_cAnimFilePass = cFilePass; }
    void SetRotDest(const D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
    void SetRotDestY(const float fRotDestY) { m_rotDest.y = fRotDestY; }
    void SetCollisionSizeDefence(const D3DXVECTOR2 collisionSizeDeffence = D3DXVECTOR2(0.0f, 0.0f)) { m_collisionSizeDefence = collisionSizeDeffence; }
    void SetLife(float fLife) { m_fLife = fLife;}
    void SetUpLife(float fLife) { m_fLife = fLife; m_fLife_red = fLife; m_fMaxLife = fLife; }
    void SetHPDisp(int hpDisp) { m_HPDisp = hpDisp; }
    void SetUIHPDisp(bool bDisp)
    {
        if (m_pUI_HP_bg && m_pUI_HP_red && m_pUI_HP)
        {
            m_pUI_HP_bg->SetDisp(bDisp);
            m_pUI_HP_red->SetDisp(bDisp);
            m_pUI_HP->SetDisp(bDisp);
        }
    }
    void SetInvincible(bool bInvincible) { m_bIsInvincible = bInvincible; }
    void SetUseControllerEffectByTakeDamage(bool bUse) { m_bUseControllerEffectByTakeDamage = bUse; }
    void SetMove(D3DXVECTOR3 move) { m_move = move; }
    void SetTakeDamageTime(int nTime) { m_nCntTakeDamageTime = nTime; }
    void SetDamageState(DAMAGE_STATE damageState) { m_damageState = damageState; }
    void SetResetAttack(bool bReset) { m_bIsAttackReset = bReset; }
    void SetMoveOld(D3DXVECTOR3 moveOld) { m_moveOld = moveOld; }
    void SetUseKnockBack(bool bUse) { m_bUseKnockBack = bUse; }

    void BindParts(int nPartsIndex, int nPartsType) { m_aPartsType[nPartsIndex] = nPartsType; }

    /*========================================================
    // �Q�b�^�[
    //======================================================*/
    D3DXVECTOR3 GetDefaultPos(int index) { return m_aPosDefault[index]; }
    D3DXVECTOR3 GetPartsPos(int index) { return D3DXVECTOR3(m_apModel[index]->GetWorldMtx()._41, m_apModel[index]->GetWorldMtx()._42, m_apModel[index]->GetWorldMtx()._43); }
    D3DXVECTOR3 GetPartsRot(int index) { return m_apModel[index]->GetRot(); }
    CModel * GetParts(int index) { return m_apModel[index]; }
    D3DXVECTOR3 GetPos(void) { return m_pos; }
    D3DXVECTOR3 GetRot(void) { return m_rot; }
    CAnimation * GetAnimation(void) { return m_pAnimation; }
    D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
    D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }
    D3DXVECTOR2 GetCollisionSizeDefence(void) { return m_collisionSizeDefence; }
    float GetLife(void) { return m_fLife; }
    bool GetInvincible(void) { return m_bIsInvincible; }
    bool GetIsPlayer(void)
    {
        if (m_HPDisp == HP_DISP_PLAYER_1 || m_HPDisp == HP_DISP_PLAYER_2 ||
            m_HPDisp == HP_DISP_PLAYER_3 || m_HPDisp == HP_DISP_PLAYER_4)
        {
            return true;
        }
        return false;
    }
    DAMAGE_STATE GetDamageState(void) { return m_damageState; }
    D3DXVECTOR3 GetMove(void) { return m_move; }
    bool GetResetAttack(void) { return m_bIsAttackReset; }
    D3DXVECTOR3 GetMoveOld(void) { return m_moveOld; }
    int GetTakeDamageTime(void) { return m_nCntTakeDamageTime; }

    // �A�j���[�V�������g�p���Ȃ��ꍇ�̃Z�b�^�[
    void SetDontUseAnimation(void) { m_bUseAnimation = false; }

private:
    int                     m_aPartsType[CHARCTER_PARTS_MAX];           // �p�[�c�^�C�v
    D3DXVECTOR3				m_aPosDefault[CHARCTER_PARTS_MAX];          // �����ʒu
    int						m_anIndexParent[CHARCTER_PARTS_MAX];        // �e�ݒ�

    D3DXVECTOR3		m_pos;                                              // �S�Ă̐e�̈ʒu
    D3DXVECTOR3		m_rot;                                              // �S�Ă̐e�̌���
    int				m_nPartsNum;                                        // �p�[�c��

    CModel			*m_apModel[CHARCTER_PARTS_MAX];                     // ���f���ւ̃|�C���^
    CAnimation		*m_pAnimation;                                      // �A�j���[�V�����ւ̃|�C���^

    D3DXVECTOR3		m_posOld;                                           // 1F�O�̈ʒu

    char* m_cAnimFilePass;                                              // �A�j���[�V�����t�@�C���̃p�X

    bool m_bUseAnimation;												// �A�j���[�V���������邩�ǂ���
    D3DXVECTOR3 m_rotDest;                                              // ����(�ړI�l)
    CEffect3D *m_pEffect3d_Shadow;                                      // �e�ւ̃|�C���^
    D3DXVECTOR2 m_collisionSizeDefence;                                 // �h��Փ˃T�C�Y�i�~���j

    float m_fLife;                                                      // �̗�
    float m_fLife_red;                                                  // �ԑ̗�
    float m_fMaxLife;                                                   // �ő�̗�
    int m_nCntStopRedLifeTime;                                          // �ԃQ�[�W��~���Ԃ̃J�E���^
    CUI *m_pUI_HP;                                                      // HP�Q�[�W�ւ̃|�C���^
    CUI *m_pUI_HP_red;                                                  // ��HP�Q�[�W�ւ̃|�C���^
    CUI *m_pUI_HP_bg;                                                   // HP�Q�[�W�w�i�ւ̃|�C���^
    int m_HPDisp;                                                       // HP�\�����@

    //==============================
    // �ړ�����
    //==============================
    D3DXVECTOR3 m_move;                      // �ړ���
    D3DXVECTOR3 m_moveOld;                   // 1F�O�̈ړ���
    bool m_bUseControllerEffectByTakeDamage; // �R���g���[���[�̐U�����A�_���[�W���󂯂����Ɏg����

    //==============================
    // �U������
    //==============================
    bool m_bIsAttackReset;                   // �U�������Z�b�g���邩�ǂ���

    //==============================
    // �h�����
    //==============================
    bool m_bIsInvincible;                    // ���G���ǂ���
    int m_nCntTakeDamageTime;                // �U�����󂯂Ă��鎞��
    DAMAGE_STATE m_damageState;              // �������
    bool m_bUseWhiteDraw;                    // ���`����g�p���邩�ǂ���
    int m_nCntWhiteDrawTime;                 // ���`�������t���[����
    bool m_bUseKnockBack;                    // �m�b�N�o�b�N���g�p���邩�ǂ���
};

#endif