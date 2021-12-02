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

//================================================
// �}�N����`
//================================================

//================================================
// �O���錾
//================================================

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

    // �G�̎��
    typedef enum
    {
        TYPE_SPIDER = 0,    // �w�
        TYPE_ARMY,          // �A�[�~�[
        TYPE_KAMIKAZE,      // �J�~�J�[
        TYPE_CANNON,        // �L���m��
        TYPE_COMMANDER,     // �R�}���_�[
    }TYPE;

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

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CEnemy *Create(int type, D3DXVECTOR3 pos, float fStrength = 1.0f,
        int appearState = APPEAR_STATE_EXIST);                  // ��������

    //=============================
    // �Z�b�^�[
    //=============================

    //=============================
    // �Q�b�^�[
    //=============================
    int GetIdx(void) { return m_nIdx; }

private:
    int m_type;                              // ���
    float m_fSpeed;                          // ����
    float m_fStrength;                       // ����(��{1.0�{)

    int m_nCntTime;                          // ���Ԃ𐔂���
    bool m_bSquashedByFortress;              // �v�ǂɓ��݂Ԃ���邩�ǂ���
    bool m_bDetectPlayer;                    // �v���C���[�������Ă��邩�ǂ���

    int m_appearState;                       // �o�����
    bool m_bDeath;                           // ����Ă��邩�ǂ���
    int m_nIdx;                              // �����̃C���f�b�N�X

    int m_walkMotion;                        // �������[�V����
    int m_attackMotion;                      // �U�����[�V����
    int m_damageMotion;                      // �_���[�W���[�V����
    int m_deathMotion;                       // ���S���[�V����

    //=============================
    // ��ނ��Ƃ̏���
    //=============================
    void SetupInfoByType(void);

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void Appear(void);
    void SquashedByFortress(D3DXVECTOR3 myPos);
};

#endif