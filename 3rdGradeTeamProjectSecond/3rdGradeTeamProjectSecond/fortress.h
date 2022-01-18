//======================================================================================
//
// �ړ��v�Ǐ��� (fortress.h)
// Author : �㓡�T�V��
//
//======================================================================================
#ifndef _FORTRESS_H_
#define _FORTRESS_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "character.h"
#include "model.h"
#include "road.h"
#include "effectData.h"

//================================================
// �}�N����`
//================================================
#define FORTRESS_CRUSH_DAMAGE 5000.0f

//================================================
// �O���錾
//================================================

//================================================
// �N���X�錾
//================================================

// �ړ��v�ǃN���X
class CFortress : public CCharacter
{
public:
    CFortress();
    ~CFortress();

    // �񋓌^�錾
    typedef enum
    {
        PARTS_BODY = 0,         // �ԑ�
        PARTS_CANNON_CENTER,    // �C�䒆�S
        PARTS_SEAT,             // ����
        PARTS_FIRE_POS,         // ���ˈʒu
        PARTS_TIRE_1,           // �^�C��1
        PARTS_TIRE_2,           // �^�C��2
        PARTS_TIRE_3,           // �^�C��3
        PARTS_TIRE_4,           // �^�C��4
        PARTS_MAX,
    }PARTS;

// �ړ��v�ǂŎg�p����G�t�F�N�g�̎��(�H���ǉ�)
    typedef enum 
    {
        EFFECT_SMOKE=0,     // ��
        EFFECT_LIGHTNING,   // �d��
        EFFECT_LIGHTNING_CHARGE_0,
        EFFECT_LIGHTNING_CHARGE_1,
        EFFECT_LIGHTNING_CHARGE_2,
        EFFECT_LIGHTNING_SETUP,// �U������
        EFFECT_MAX,
    }EFFECT;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CFortress *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR);        // ��������

    void ResetAttack(void);
    void AddChargeValue(const float fChargeValue);

    //=============================
    // �Z�b�^�[
    //=============================
    void SetNowWhoRiding(bool bRiding) { m_bNowWhoRiding = bRiding; }
    void SetAttackPhase(bool bAttackPhase, int nWho) { m_bAttackPhase = bAttackPhase; m_nWhoAttackPhase = nWho; }
    void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

    //=============================
    // �Q�b�^�[
    //=============================
    bool GetNowWhoRiding(void) { return m_bNowWhoRiding; }
    bool GetAttackPhase(void) { return m_bAttackPhase; }
    float GetChargeValue(void) { return m_fChargeValue; }
    D3DXVECTOR3 GetPlayerSpawnPos(int nIndex);

private:
    float m_fSpeed;             // ����

    bool m_bSearchRoad;         // ����T���Ă��邩�ǂ���
    D3DXVECTOR3 m_moveAngle;    // �ړ��̌���
    CRoad* m_pTargetRoad;       // �ڕW�̓�
    bool m_bNowWhoRiding;       // �N��������Ă��邩�ǂ���

    float m_fChargeValue;       // �`���[�W��
    bool m_bAttackPhase;        // �U���t�F�[�Y���ǂ���
    int m_nCntTime;             // ���Ԃ��J�E���g

    bool m_bDisp;               // �\�����Ă��邩�ǂ���
    int m_nWhoAttackPhase;      // �N���A�^�b�N�t�F�[�Y�ɕς�����

    CEffectData::IntervalEffect m_Effect[EFFECT_MAX];// �G�t�F�N�g
    float m_fTireRotAngle;      // �^�C���̉�]�p�x
    bool m_bShootUpDebris;      // �j�Ђ��΂�܂������ǂ���

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void SearchRoad(D3DXVECTOR3 myPos);
    void AttackPhase(void);
    bool CollisionWall(D3DXVECTOR3 myPos);
};

#endif