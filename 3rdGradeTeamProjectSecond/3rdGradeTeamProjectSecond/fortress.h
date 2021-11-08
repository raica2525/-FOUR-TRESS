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

//================================================
// �}�N����`
//================================================

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

    // �񋓌^�錾(���[�V����)
    typedef enum
    {
        ANIM_IDLE = 0,      // �ҋ@
        ANIM_WARN,          // �Њd
        ANIM_MAX,           // �ő吔
    }ANIMATION;

    // �񋓌^�錾
    typedef enum
    {
        PARTS_FIGHTER = 0,
        PARTS_RIGHT_WING_0,
        PARTS_RIGHT_WING_1,
        PARTS_RIGHT_WING_2,
        PARTS_RIGHT_WING_3,
        PARTS_LEFT_WING_0,
        PARTS_LEFT_WING_1,
        PARTS_LEFT_WING_2,
        PARTS_LEFT_WING_3,
        PARTS_MAX,
    }PARTS;

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);                                    // ����������
    void Uninit(void);                                                                  // �I������
    void Update(void);                                                                  // �X�V����
    void Draw(void);                                                                    // �`�揈��
    static CFortress *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = DEFAULT_VECTOR);        // ��������

    //=============================
    // �Q�b�^�[
    //=============================
    D3DXVECTOR2 GetCollisionSizeDeffence(void) { return m_collisionSizeDeffence; }

    //=============================
    // �Z�b�^�[
    //=============================

private:
    D3DXVECTOR2 m_collisionSizeDeffence;     // �h��Փ˃T�C�Y
    float m_fSpeed;                          // ����
    float m_fLife;                           // �̗�

    bool m_bSearchRoad;                      // ����T���Ă��邩�ǂ���
    D3DXVECTOR3 m_moveAngle;                 // �ړ��̌���
    CRoad* m_pTargetRoad;                    // �ڕW�̓�

    //=============================
    // ���̃N���X���ł̂ݎg������
    //=============================
    void SearchRoad(D3DXVECTOR3 myPos);
};

#endif