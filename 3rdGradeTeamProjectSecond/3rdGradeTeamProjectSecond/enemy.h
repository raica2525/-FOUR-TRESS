//======================================================================================
//
// �G�l�~�[���� (enemy.h)
// Author : �㓡�T�V��
//
//======================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "character.h"
#include "model.h"
#include "player.h"
#include "effectData.h"

//================================================
// �}�N����`
//================================================

//================================================
// �O���錾
//================================================
class CModelEffect;

//================================================
// �N���X�錾
//================================================

// �G�l�~�[�N���X
class CEnemy : public CCharacter
{
public:
    CEnemy();
    ~CEnemy();

    // �G�̏o����
    typedef enum
    {
        APPEAR_STATE_EXIST = 0,       // �o�����Ă���
        APPEAR_STATE_WAIT_FORTRESS,   // �ړ��v�ǐڋߎ��A�o��
        APPEAR_STATE_WAIT_PLAYER,     // �v���C���[�ڋߎ��A�o��
    }APPEAR_STATE;

    // �^�[�Q�b�g�X��
    typedef enum
    {
        TARGET_TREND_PLAYER = 0,            // �v���C���[��_��
        TARGET_TREND_FORTRESS,              // �ړ��v�ǂ�_��
        TARGET_TREND_PLAYER_AND_FORTRESS,   // �v���C���[�ƈړ��v�ǂ�_��
    }TARGET_TREND;

    // �G�̎��
    typedef enum
    {
        TYPE_SPIDER = 0,    // �w�
        TYPE_ARMY,          // �A�[�~�[
        TYPE_KAMIKAZE,      // �J�~�J�[
        TYPE_CANNON,        // �L���m��
        TYPE_COMMANDER,     // �R�}���_�[
		TYPE_SHINIGAMI,     // �V�j�K�~
        TYPE_PENPEN,        // �y���y��
		TYPE_KIWI,
    }TYPE;

    // ��{���
    typedef enum
    {
        BASE_STATE_WAIT = 0,    // �ҋ@
        BASE_STATE_PATROL,      // ����
        BASE_STATE_ATTACK,      // �U��
        BASE_STATE_DAMAGE,      // �_���[�W
        BASE_STATE_PARALYSIS,   // ���
        BASE_STATE_DEATH,       // ���S
    }BASE_STATE;

    //=========================
    // �w�
    //=========================
    typedef enum
    {
        SPIDER_ANIM_IDLE = 0,      // �ҋ@
        SPIDER_ANIM_WALK,          // ����
        SPIDER_ANIM_TAUNT,         // ����
        SPIDER_ANIM_ATTACK,        // �U��
        SPIDER_ANIM_JUMP,          // �W�����v
        SPIDER_ANIM_MAX,           // �ő吔
    }SPIDER_ANIMATION;
    typedef enum
    {
        SPIDER_PARTS_BODY = 0,
        SPIDER_PARTS_STOMACH,
        SPIDER_PARTS_FANG_RIGHT,
        SPIDER_PARTS_FANG_LEFT,
        SPIDER_PARTS_LEG_RIGHT_0,
        SPIDER_PARTS_LEG_RIGHT_1,
        SPIDER_PARTS_LEG_RIGHT_2,
        SPIDER_PARTS_LEG_RIGHT_3,
        SPIDER_PARTS_LEG_LEFT_0,
        SPIDER_PARTS_LEG_LEFT_1,
        SPIDER_PARTS_LEG_LEFT_2,
        SPIDER_PARTS_LEG_LEFT_3,
        SPIDER_PARTS_STOMACH_CUBE, // �����甭�������铖���蔻��̈ʒu
        SPIDER_PARTS_MAX,
    }SPIDER_PARTS;

    //=========================
    // �A�[�~�[
    //=========================
    typedef enum
    {
        ARMY_ANIM_IDLE = 0,      // �ҋ@
        ARMY_ANIM_WALK,          // ����
        ARMY_ANIM_ATTACK,        // �U��
        ARMY_ANIM_DAMAGE,        // �_���[�W
        ARMY_ANIM_DEATH,         // ���S
        ARMY_ANIM_MAX,           // �ő吔
    }ARMY_ANIMATION;
    typedef enum
    {
        ARMY_PARTS_BODY = 0,
        ARMY_PARTS_RHAND,
        ARMY_PARTS_LHAND,
        ARMY_PARTS_MAX,
    }ARMY_PARTS;

    //=========================
    // �J�~�J�[
    //=========================
    typedef enum
    {
        KAMIKAZE_ANIM_IDLE = 0,      // �ҋ@
        KAMIKAZE_ANIM_WALK,          // ����
        KAMIKAZE_ANIM_ATTACK,        // �U��
        KAMIKAZE_ANIM_DAMAGE,        // �_���[�W
        KAMIKAZE_ANIM_DEATH,         // ���S
        KAMIKAZE_ANIM_MAX,           // �ő吔
    }KAMIKAZE_ANIMATION;
    typedef enum
    {
        KAMIKAZE_PARTS_BODY = 0,
        KAMIKAZE_PARTS_ARML,
        KAMIKAZE_PARTS_ARMR,
        KAMIKAZE_PARTS_BOMB,
        KAMIKAZE_PARTS_BOMB_CUBE,
        KAMIKAZE_PARTS_MAX,
    }KAMIKAZE_PARTS;

    //=========================
    // �L���m��
    //=========================
    typedef enum
    {
        CANNON_PARTS_BODY = 0,
        CANNON_PARTS_FIRE_CUBE,
        CANNON_PARTS_MAX,
    }CANNON_PARTS;

    //=========================
    // �R�}���_�[
    //=========================
    typedef enum
    {
        COMMANDER_ANIM_IDLE = 0,      // �ҋ@
        COMMANDER_ANIM_SPAWN_ENEMY,   // �G����
    }COMMANDER_ANIMATION;
    typedef enum
    {
        COMMANDER_PARTS_BODY = 0,
        COMMANDER_PARTS_PETAL1,
        COMMANDER_PARTS_PETAL2,
        COMMANDER_PARTS_PETAL3,
        COMMANDER_PARTS_PETAL4,
        COMMANDER_PARTS_PETAL5,
        COMMANDER_PARTS_SPAWN_POS,
        COMMANDER_PARTS_MAX,
    }COMMANDER_PARTS;

	//=========================
	// �V�j�K�~
	//=========================
	typedef enum
	{
		SHINIGAMI_ANIM_IDLE = 0,      // �ҋ@
		SHINIGAMI_ANIM_WALK,          // ����
		SHINIGAMI_ANIM_DAMAGE,        // �_���[�W
        SHINIGAMI_ANIM_ATTACK,        // �U��
		SHINIGAMI_ANIM_DEATH,         // ���S
		SHINIGAMI_ANIM_MAX,           // �ő吔
	}SHINIGAMI_ANIMATION;
	typedef enum
	{
		SHINIGAMI_PARTS_BODY = 0,
		SHINIGAMI_PARTS_WEP,
		SHINIGAMI_PARTS_MAX,
	}SHINIGAMI_PARTS;

    //=========================
    // �y���y��
    //=========================
    typedef enum
    {
        PENPEN_ANIM_IDLE = 0,      // �ҋ@
        PENPEN_ANIM_WALK,          // ����
        PENPEN_ANIM_ATTACK,        // �U��
        PENPEN_ANIM_DAMAGE,        // �_���[�W
        PENPEN_ANIM_DEATH,         // ���S
        PENPEN_ANIM_MAX,           // �ő吔
    }PENPEN_ANIMATION;
    typedef enum
    {
        PENPEN_PARTS_BODY = 0,
        PENPEN_PARTS_CUTTER_R,
        PENPEN_PARTS_CUTTER_L,
        PENPEN_PARTS_MAX,
    }PENPEN_PARTS;
	
	//=========================
	// �L�E�C
	//=========================
	typedef enum
	{
		KIWI_ANIM_IDLE = 0,      // �ҋ@
		KIWI_ANIM_WALK,          // ����
		KIWI_ANIM_DAMAGE,        // �_���[�W
		KIWI_ANIM_DEATH,         // ���S
		KIWI_ANIM_RUN,           // ����
		KIWI_ANIM_MAX,           // �ő吔
	}KIWI_ANIMATION;
	typedef enum
	{
		KIWI_PARTS_BODY = 0,
		KIWI_PARTS_WING_R,
		KIWI_PARTS_WING_L,
		KIWI_PARTS_FOOT_R,
		KIWI_PARTS_FOOT_L,
		KIWI_PARTS_MAX,
	}KIWI_PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CEnemy *Create(int type, D3DXVECTOR3 pos, float fStrength = 1.0f,
        int appearState = APPEAR_STATE_EXIST, float fChargeValue = NOT_EXIST_F, float fSearchDistanceForAppear = 2000.0f);// ��������

    void DiscoveryTarget(CCharacter *pTarget);                                          // �^�[�Q�b�g��������

    //=============================
    // �Z�b�^�[
    //=============================
    void SetBaseState(BASE_STATE nextBaseState, int nNextStateEndFrame = NOT_EXIST);    // ��{��Ԃ�ς��鏈��
    void SetWhoContribution(int nWho) { m_nWhoContribution = nWho; }

    //=============================
    // �Q�b�^�[
    //=============================
    int GetAppearState(void) { return m_appearState; }

private:
    int m_type;                              // ���
    float m_fSpeed;                          // ����
    float m_fStrength;                       // ����(��{1.0�{)
    float m_fChargeValue;                    // �`���[�W��

    int m_nCntTime;                          // ���Ԃ𐔂���
    bool m_bSquashedByFortress;              // �v�ǂɓ��݂Ԃ���邩�ǂ���

    int m_appearState;                       // �o�����
    bool m_bDeath;                           // ����Ă��邩�ǂ���
    BASE_STATE m_baseState;                  // ��{���

    int m_walkMotion;                        // �������[�V����
    int m_attackMotion;                      // �U�����[�V����
    int m_damageMotion;                      // �_���[�W���[�V����
    int m_deathMotion;                       // ���S���[�V����

    float m_fSearchDistanceForAppear;        // �o���̂��߂̌��m����
    D3DXVECTOR3 m_patrolCentralPos;          // ����̒��S�ʒu
    D3DXVECTOR3 m_moveAngle;                 // �ړ��p�x
    int m_nPatrolDistance;                   // ���񋗗�
    int m_nCurrentStateEndFrame;             // ���݂̏�Ԃ��I���t���[����

    bool m_bWarning;                         // �x�������ǂ���
    float m_fDiscoveryTargetDistance;        // �^�[�Q�b�g��������
    CCharacter *m_pTarget;                   // �W�I�̃L�����N�^�[
    int m_setAnimationThisFrame;             // ���̃t���[�����ŁA�ݒ肷��A�j���[�V�����ԍ�

    bool m_bUseCommonAtkFollow;              // �Ǐ]�U�����g�p���邩�ǂ���
    TARGET_TREND m_targetTrend;              // �^�[�Q�b�g�X��
    int m_nAddScore;                         // ���Z�X�R�A
    int m_nWhoContribution;                  // �N�̍v����
    int m_nDeathContributionPoint;           // ���S�����ۂɁA�v���C���[�ɓ���v���x

    CEffectData::IntervalEffect m_Effect;    // ���Ԋu�Ŕ���������G�t�F�N�g�i�J�~�J�[�̉ΉԂȂǁj

    bool m_bDeathBySquashed;                 // ���݂Ԃ���Ď��񂾂�
    bool m_bAtkStartFlag;                    // �U�����s��Ԋu�̂��̂Ɏg���A�U���J�n�t���O
    CModelEffect *m_pModelEffect;            // �ėp�̃��f���G�t�F�N�g�i�y���y���̉�]�U���̐n�Ȃǁj

    //=============================
    // ��ނ��Ƃ̏���
    //=============================
    void SetupInfoByType(void);
    void AtkCommonFollow(D3DXVECTOR3& myPos);
    void AtkArmy(D3DXVECTOR3& myPos);
    void AtkKamikaze(D3DXVECTOR3& myPos);
    void AtkCannon(D3DXVECTOR3& myPos);
    void AtkCommander(D3DXVECTOR3& myPos);
	void AtkShinigami(D3DXVECTOR3& myPos);
    void AtkPenpen(D3DXVECTOR3& myPos);
	void AtkKiwi(D3DXVECTOR3& myPos);

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void Appear(void);
    void SquashedByFortress(D3DXVECTOR3 myPos);
    void DeathOneFrame(D3DXVECTOR3 myPos);
    void RePatrol(void);

    //=============================
    // AI�n
    //=============================
    void WaitAI(D3DXVECTOR3& myPos);
    void PatrolAI(D3DXVECTOR3& myPos);
    void AttackAI(D3DXVECTOR3& myPos);
    void DamageAI(void);
};

#endif