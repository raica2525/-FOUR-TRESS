#define _CRT_SECURE_NO_WARNINGS

#include "CreateStage.h"

#include "block.h"
#include "enemy.h"
#include "field.h"
#include "camera.h"
#include "effect3d.h"
#include "library.h"

bool CCreateStage::m_bFixedSshaft[2]                                           = { false, false };
bool CCreateStage::m_bGreaseJudge                                              = false;
bool CCreateStage::m_bSaveJudge                                                = false;
bool CCreateStage::m_bPushedControlS                                           = false;
bool CCreateStage::m_bUseAllDelete                                             = false;
bool CCreateStage::m_WriteSaveDate                                             = false;
int CCreateStage::m_nCopyType                                                  = -1;
D3DXVECTOR3 CCreateStage::m_CopyRot                                            = {};
D3DXVECTOR3 CCreateStage::m_CopyPos                                            = {};
CCreateStage::BLOCKSAVEDATE CCreateStage::m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM] = {};
CCreateStage::CREATEOBJECT CCreateStage::m_CreateType                          = CREATEOBJECT_STAGE;
D3DXVECTOR3 CCreateStage::m_FieldSiz                                           = {};
char CCreateStage::m_cTxtName[3][256]                                          = {};
int CCreateStage::m_nBlockType                                                 = 0;
int CCreateStage::m_nEnemyType                                                 = 0;
bool CCreateStage::m_bPauseJudge                                               = false;

CCreateStage::CCreateStage()
{
	ZeroMemory(m_aBlockSaveDate, sizeof(m_aBlockSaveDate));
	LoadTextName();
}

CCreateStage::~CCreateStage()
{
}

HRESULT CCreateStage::Init(void)
{
    m_nBlockType = 0;
    m_nEnemyType = 0;

    return S_OK;
}

void CCreateStage::Uninit(void)
{
}

void CCreateStage::Update(void)
{
    static int nCount = 0;
    m_nLastCountPos   = 0;
    m_nLastCountRot   = 0;
    m_posR            = CCamera::GetCameraposR();
    //�L�[�{�[�h�̊m�ۂ������������擾
    m_pInputKeyboard = CManager::GetInputKeyboard();
    //�}�E�X�̊m�ۂ������������擾
    m_pMouse = CManager::GetMouse();

	// ���R���g���[����������Ă��Ȃ��ꍇ
	if (!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && !m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL)) {
		// P�L�[�Ń|�[�Y��ʂɂ���
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_P)) {
			// �|�[�Y��ʎg�p�̕ϐ����g���K�[����
			m_bPauseJudge = !m_bPauseJudge;
			ShowCursor(m_bPauseJudge);
			
		}
	}

	if (m_bPauseJudge == false) {
		// �ύX���e��control + Z�̎��ɕύX���ꂽ���̂̐��𐔂���
		CountDetallsChangeLAST();

		// F3/F4�L�[�������ꂽ�ꍇ�A�R�s�[���Ă��������������
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_F3) || m_pInputKeyboard->GetKeyboardTrigger(DIK_F4)) {
			// F3/F4�L�[�Őݒu����^�C�v��؂�ւ���
			if (m_pInputKeyboard->GetKeyboardTrigger(DIK_F3)) {
				m_CreateType = CREATEOBJECT_STAGE;
			}
			else{
				m_CreateType = CREATEOBJECT_ENEMY;
			}
			InitCopyDate();
		}

		// ���R���g���[����B�L�[�������ꂽ�Ƃ��ύX�O�̕ۑ�����Ă�������e�L�X�g�t�@�C���ɏo�͂���
		if (m_pInputKeyboard->GetKeyboardPress(DIK_B) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_B)) {

			m_WriteSaveDate = true;
			WriteBlockSaveDate(nCount);
		}

		// ���R���g���[����������Ă��Ȃ��ꍇ
		if (!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
			// Z�L�[�������ꂽ�Ƃ�
			if (m_pInputKeyboard->GetKeyboardTrigger(DIK_Z)) {
				// bool�^�ϐ����g�O��������
				m_bFixedSshaft[1] = !m_bFixedSshaft[1];
				m_FixedSshaft.z = m_posR.z;

				if (CBlock::GetSelectBlock() != NULL) {
					m_FixedSshaft.z = CBlock::GetSelectBlock()->GetPos().z;
				}
				
				if (m_bGreaseJudge == true) {
					m_FixedSshaft.z = m_CursorPos.z;
				}
			}

			// X�L�[�������ꂽ�Ƃ�
			if (m_pInputKeyboard->GetKeyboardTrigger(DIK_X)) {
				// bool�^�ϐ����g�O��������
				m_bFixedSshaft[0] = !m_bFixedSshaft[0];
				m_FixedSshaft.x = m_posR.x;
				if (CBlock::GetSelectBlock() != NULL) {
					m_FixedSshaft.x = CBlock::GetSelectBlock()->GetPos().x;
				}
				if (m_bGreaseJudge == true) {
					m_FixedSshaft.x = m_CursorPos.x;
				}
			}
		}

		// G�L�[�ŃO���b�h�̎g�p��؂�ւ���
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_G)) {
			m_bGreaseJudge = !m_bGreaseJudge;
		}

		// ���R���g���[����Y�L�[�������ꂽ�ꍇ
		if (m_pInputKeyboard->GetKeyboardPress(DIK_Y) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_Y)) {

			// �ߋ��̏������ɕύX��ɐi�߂�
			nCount = RedoUndoOperation(nCount);
		}
		// ���R���g���[����Z�L�[�������ꂽ�ꍇ
		if (m_pInputKeyboard->GetKeyboardPress(DIK_Z) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_Z)) {

			// �ߋ��̏������ɕύX�O�ɖ߂�
			nCount = UndoingOperation(nCount);
		}

		// �ݒu����^�C�v�ɂ���čX�V������؂�ւ���
		switch (m_CreateType) {
		case CREATEOBJECT_STAGE:
			nCount = SetObject(m_pInputKeyboard, m_posR, m_pMouse, nCount, m_aBlockSaveDate[nCount], m_CreateType);
			break;

		case CREATEOBJECT_ENEMY:
			nCount = SetEnemy(m_pInputKeyboard, m_posR, m_pMouse, nCount, m_aBlockSaveDate[nCount], m_CreateType);
			break;

		default:
			break;
		}

		// �O���b�h���L���̏ꍇ�A100�}�X��؂�ŃJ�[�\����ݒu����
		if (m_bGreaseJudge) {
			while ((int)m_posR.z % 100 != 0) {
				(int)m_posR.z--;
			}
			while ((int)m_posR.x % 100 != 0) {
				(int)m_posR.x--;
			}

			m_CursorPos = m_posR;
		}

		// �O���b�h�̎g�p��Ԃɍ��킹�ăJ�[�\���𐧌䂷��
		if (m_bGreaseJudge) {
			CursorControl(m_FixedSshaft, m_CursorPos, m_CreateType);
		}
		else {
			CursorControl(m_FixedSshaft, m_posR, m_CreateType);
		}

		// �u���݂ɕύX���e���ۑ�����Ă���ꍇ���v�A�u���݂ɑS�����ȊO�̕ύX�������ꍇ�v���A�u�����ɑS�����̕ύX���s���Ă����v�ꍇ�A���݈ڍs�s���Ă����ύX���e������������
		if (m_aBlockSaveDate[nCount].DetailsChange != DETAILSCHANGE_NULL && m_aBlockSaveDate[nCount].DetailsChange != DETAILSCHANGE_TOTALELIMINATION && m_aBlockSaveDate[nCount + 1].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
			InitArray(nCount + NEXT_DATA);
		}
		// ���݂̏�񂩂�ύX���ꂽ�����A�ύX���e���K������Ă��Ȃ��ꍇ���̓J�E���g�p�ϐ���i�߂�
		if (m_aBlockSaveDate[nCount].DetailsChange != DETAILSCHANGE_NULL && !m_aBlockSaveDate[nCount].bChangeJudge) {
			nCount++;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g��ݒu
//=============================================================================
int CCreateStage::SetObject(CInputKeyboard *m_pInputKeyboard,
                            D3DXVECTOR3 m_posR,
                            CMouse *m_pMouse,
                            int nCount,
                            BLOCKSAVEDATE m_aBlockSaveDate,
                            CREATEOBJECT m_CreateType)
{
    static D3DXVECTOR3 Pos;
    static D3DXVECTOR3 Rot;
    static int nNumber = -1;

    // �^�C�v���Ǘ�����ϐ����͈͊O�ɂȂ�Ȃ��悤�ɏ���
    if(m_nBlockType >= CBlock::TYPE_MAX) {
        m_nBlockType = CBlock::TYPE_MAX - 1;
    }
    if(m_nBlockType < 0) {
        m_nBlockType = 0;
    }

    //=================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
    // �ݒu�I�u�W�F�N�g�̕ύX

    // ���R���g���[����������Ă��Ȃ��ꍇ
    if(!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
        // ���C�������L�[
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_1)) {
			SetObjectType(CBlock::TYPE_1);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_2)) {
			SetObjectType(CBlock::TYPE_2);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_3)) {
			SetObjectType(CBlock::TYPE_3);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_4)) {
			SetObjectType(CBlock::TYPE_4);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_5)) {
			SetObjectType(CBlock::TYPE_5);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_6)) {
			SetObjectType(CBlock::TYPE_6);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_7)) {
			SetObjectType(CBlock::TYPE_7);
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_8)) {
			SetObjectType(CBlock::TYPE_8);
		}
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_9)) {
			SetObjectType(CBlock::TYPE_9);
		}
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_0)) {
			SetObjectType(CBlock::TYPE_10);
		}
		// �e���L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD1)) {
			SetObjectType(CBlock::TYPE_11);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD2)) {
			SetObjectType(CBlock::TYPE_12);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD3)) {
			SetObjectType(CBlock::TYPE_13);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD4)) {
			SetObjectType(CBlock::TYPE_14);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD5)) {
			SetObjectType(CBlock::TYPE_15);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD6)) {
			SetObjectType(CBlock::TYPE_16);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD7)) {
			SetObjectType(CBlock::TYPE_17);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD8)) {
			SetObjectType(CBlock::TYPE_18);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD9)) {
			SetObjectType(CBlock::TYPE_19);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0)) {
			SetObjectType(CBlock::TYPE_20);
		}
    }
    // ���R���g���[����������Ă���ꍇ
    else if(m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
		// ���C�������L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_1)) {
			SetObjectType(CBlock::TYPE_21);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_2)) {
			SetObjectType(CBlock::TYPE_22);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_3)) {
			SetObjectType(CBlock::TYPE_23);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_4)) {
			SetObjectType(CBlock::TYPE_24);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_5)) {
			SetObjectType(CBlock::TYPE_25);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_6)) {
			SetObjectType(CBlock::TYPE_26);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_7)) {
			SetObjectType(CBlock::TYPE_27);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_8)) {
			SetObjectType(CBlock::TYPE_28);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_9)) {
			SetObjectType(CBlock::TYPE_29);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_0)) {
			SetObjectType(CBlock::TYPE_30);
		}
		// �e���L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD1)) {
			SetObjectType(CBlock::TYPE_31);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD2)) {
			SetObjectType(CBlock::TYPE_32);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD3)) {
			SetObjectType(CBlock::TYPE_33);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD4)) {
			SetObjectType(CBlock::TYPE_34);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD5)) {
			SetObjectType(CBlock::TYPE_35);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD6)) {
			SetObjectType(CBlock::TYPE_36);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD7)) {
			SetObjectType(CBlock::TYPE_37);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD8)) {
			SetObjectType(CBlock::TYPE_38);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD9)) {
			SetObjectType(CBlock::TYPE_39);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0)) {
			SetObjectType(CBlock::TYPE_40);
		}
    }
    //=================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================

    // ���R���g���[����X�L�[�������ꂽ�Ƃ��I�𒆂̃I�u�W�F�N�g����ۑ����A�I�𒆂̃I�u�W�F�N�g������
    if(m_pInputKeyboard->GetKeyboardPress(DIK_X) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_X)) {

        // �I�u�W�F�N�g��I�����Ă���ꍇ
        if(CBlock::GetSelectBlock() != NULL) {
            // �z��̊m�F
            nCount = ShiftArray(nCount);
            // �����I�u�W�F�N�g����ۑ�
            SaveData(CBlock::GetSelectBlock()->GetPos(),
                     CBlock::GetSelectBlock()->GetRot(),
                     CBlock::GetSelectBlock()->GetNumber(),
                     DETAILSCHANGE_BREAK,
                     false,
                     CBlock::GetSelectBlock()->GetType(),
                     nCount,
                     CScene::OBJTYPE_BLOCK);
            // �I�𒆂̃I�u�W�F�N�g����ۑ�
            SetCopyData(CBlock::GetSelectBlock()->GetPos(),
                        CBlock::GetSelectBlock()->GetRot(),
                        CBlock::GetSelectBlock()->GetType());
            // �I�𒆂̃I�u�W�F�N�g������
            CBlock::GetSelectBlock()->Uninit();
        }
    }

    // �R���g���[����P�L�[�������ꂽ�ꍇ
    if(m_pInputKeyboard->GetKeyboardPress(DIK_P) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_P)) {

        if(CBlock::GetBlockNumAll() >= OBJECT_MIN_NUM) {
            // �ݒu����Ă���I�u�W�F�N�g��S�ď�������֐���ǂݍ��ޏ�ԂɕύX
            m_bUseAllDelete = true;
            // �S�������s���O�̃I�u�W�F�N�g�̑������擾
            m_nAllDeleteNum = CBlock::GetBlockNumAll();
        }
    }

    // �I�u�W�F�N�g��I���o���Ă���ꍇ
    if(CBlock::GetSelectBlock() != NULL) {
        // �ύX�O�̏����擾
        if(nNumber == -1 || nNumber != CBlock::GetSelectBlock()->GetNumber()) {
            Pos     = CBlock::GetSelectBlock()->GetPos();
            Rot     = CBlock::GetSelectBlock()->GetRot();
            nNumber = CBlock::GetSelectBlock()->GetNumber();
        }
        // �I�𒆂̃I�u�W�F�N�g�����擾
        D3DXVECTOR3 SelectBlockPos = CBlock::GetSelectBlock()->GetPos();
        D3DXVECTOR3 SelectBlockRot = CBlock::GetSelectBlock()->GetRot();
		
        // Q/E�L�[�Ŋp�x��90�x���ɕω�������
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_Q)) {
            nAddupAngle += 90;
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_E)) {
            nAddupAngle -= 90;
        }

        // ���R���g���[����������Ă��Ȃ��ꍇ
        if(!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            // U/J�L�[�ō�����15���ω�������
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_U)) {
                SelectBlockPos.y += 15;
            }
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_J)) {
                SelectBlockPos.y -= 15;
            }
            // I/K�L�[��X����15���ω�������
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_I)) {
                SelectBlockPos.x += 15;
            }
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_K)) {
                SelectBlockPos.x -= 15;
            }
            // O/L�L�[����15���ω�������
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_O)) {
                SelectBlockPos.z += 15;
            }
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_L)) {
                SelectBlockPos.z -= 15;
            }
        }
        // ���R���g���[����������Ă���ꍇ
        else if(m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            // U/J�L�[�ō�����15���ω�������
            if(m_pInputKeyboard->GetKeyboardPress(DIK_U)) {
                SelectBlockPos.y += 5;
            }
            if(m_pInputKeyboard->GetKeyboardPress(DIK_J)) {
                SelectBlockPos.y -= 5;
            }
            // I/K�L�[��X����15���ω�������
            if(m_pInputKeyboard->GetKeyboardPress(DIK_I)) {
                SelectBlockPos.x += 5;
            }
            if(m_pInputKeyboard->GetKeyboardPress(DIK_K)) {
                SelectBlockPos.x -= 5;
            }
            // O/L�L�[����15���ω�������
            if(m_pInputKeyboard->GetKeyboardPress(DIK_O)) {
                SelectBlockPos.z += 5;
            }
            if(m_pInputKeyboard->GetKeyboardPress(DIK_L)) {
                SelectBlockPos.z -= 5;
            }
        }

        // F1/F2�L�[�őI�𒆃I�u�W�F�N�g�̏���ݒu���ꂽ��Ԃɖ߂�
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_F1)) {
            CBlock::GetSelectBlock()->SetPos(D3DXVECTOR3(Pos.x, Pos.y, Pos.z));
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_F2)) {
            CBlock::GetSelectBlock()->SetRot(D3DXVECTOR3(Rot.x, Rot.y, Rot.z));
        }

        // ���R���g���[����C�L�[�������ꂽ�ꍇ
        if(m_pInputKeyboard->GetKeyboardPress(DIK_C) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_C)) {
			// �R�s�[����^�C�v��ϐ��ɕۑ�����
			m_nCopyType = CBlock::GetSelectBlock()->GetType();

            // �I�𒆂̃I�u�W�F�N�g����ۑ�����
            SetCopyData(SelectBlockPos, SelectBlockRot, m_nCopyType);
        }

        //�@���Z/���Z������ϐ����傫�����Ȃ��悤�ɒ���
        if(nAddupAngle % 360 == 0) {
            nAddupAngle = 0;
        }
        if(SelectBlockPos.y > 10000) {
            SelectBlockPos.y = 10000;
        }
        if(SelectBlockPos.y < -10000) {
            SelectBlockPos.y = -10000;
        }

        // Q/E�L�[�������ꂽ�ꍇ
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_Q) || m_pInputKeyboard->GetKeyboardTrigger(DIK_E)) {
            // �z��̊m�F
            nCount = ShiftArray(nCount);
            // �I�u�W�F�N�g�̌�����1���ڐ؂�̂Ă���
            int RotX = floor(SelectBlockRot.x);
            int RotY = floor(SelectBlockRot.y);
            int RotZ = floor(SelectBlockRot.z);
            // �ύX����ۑ�����
            SaveData(CBlock::GetSelectBlock()->GetPos(),
                     CBlock::GetSelectBlock()->GetRot(),
                     CBlock::GetSelectBlock()->GetNumber(),
                     DETAILSCHANGE_CHANGE_ROT,
                     false,
                     CBlock::GetSelectBlock()->GetType(),
                     nCount,
                     CScene::OBJTYPE_BLOCK);

            // �I�𒆂̃I�u�W�F�N�g�̌�����ύX
            CBlock::GetSelectBlock()->SetRot(
              D3DXVECTOR3(D3DXToRadian(RotX), D3DXToRadian(RotY + nAddupAngle), D3DXToRadian(RotZ)));
        }
        // ���R���g���[����������Ă��Ȃ��ꍇ
        if(!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_U) || m_pInputKeyboard->GetKeyboardTrigger(DIK_J) || m_pInputKeyboard->GetKeyboardTrigger(DIK_I) || m_pInputKeyboard->GetKeyboardTrigger(DIK_K) || m_pInputKeyboard->GetKeyboardTrigger(DIK_O) || m_pInputKeyboard->GetKeyboardTrigger(DIK_L)) {
                // �z��̊m�F
                nCount = ShiftArray(nCount);
                // �ύX����ۑ�����
                SaveData(CBlock::GetSelectBlock()->GetPos(),
                         CBlock::GetSelectBlock()->GetRot(),
                         CBlock::GetSelectBlock()->GetNumber(),
                         DETAILSCHANGE_CHANGE_POS,
                         false,
                         CBlock::GetSelectBlock()->GetType(),
                         nCount,
                         CScene::OBJTYPE_BLOCK);

                // �I�𒆂̃I�u�W�F�N�g�̍��W��ύX
				CBlock::GetSelectBlock()->SetPos(SelectBlockPos);
            }
        }
        else if(m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            if(m_pInputKeyboard->GetKeyboardPress(DIK_U) || m_pInputKeyboard->GetKeyboardPress(DIK_J) || m_pInputKeyboard->GetKeyboardPress(DIK_I) || m_pInputKeyboard->GetKeyboardPress(DIK_K) || m_pInputKeyboard->GetKeyboardPress(DIK_O) || m_pInputKeyboard->GetKeyboardPress(DIK_L)) {
                // �z��̊m�F
                nCount = ShiftArray(nCount);
                // �ύX����ۑ�����
                SaveData(CBlock::GetSelectBlock()->GetPos(),
                         CBlock::GetSelectBlock()->GetRot(),
                         CBlock::GetSelectBlock()->GetNumber(),
                         DETAILSCHANGE_CHANGE_POS,
                         false,
                         CBlock::GetSelectBlock()->GetType(),
                         nCount,
                         CScene::OBJTYPE_BLOCK);

                // �I�𒆂̃I�u�W�F�N�g�̍��W��ύX
				CBlock::GetSelectBlock()->SetPos(SelectBlockPos);
            }
        }
    }

    // ���R���g���[����S�L�[�扟���ꂽ�Ƃ�
    if(m_pInputKeyboard->GetKeyboardPress(DIK_S) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_S)) {

        // �R���g���[����S�L�[�������ꂽ���Ƃ𔻒�
        m_bPushedControlS = true;
        // �ۑ��o�������̃t���O�����s�̏�Ԃŏ���������
        m_bSaveJudge = false;
        //�u���b�N�̍��W��ۑ�
        SaveStage();
    }

    // ���R���g���[����V�L�[�������ꂽ�Ƃ�
    if(m_pInputKeyboard->GetKeyboardPress(DIK_V) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_V)) {

        //�I�u�W�F�N�g�̏�񂪓����Ă���ꍇ
        if(m_nCopyType >= 0) {
			if (m_bGreaseJudge) {
				CreatBlockControl(m_FixedSshaft,                                             // �O���b�W�h�K�p���̍��W
					D3DXVECTOR3(m_CursorPos.x, m_CopyPos.y, m_CursorPos.z),    // �J�[�\���̍��W
					m_CopyRot,                                                 // �R�s�[�����I�u�W�F�N�g�̌���
					m_nCopyType,                                               // �R�s�[�����I�u�W�F�N�g�̎��
					false,                                                     // �ύX��K�p�����{��Ԃɂ���
					nCount,                                                    // �ύX�ԍ�
					CScene::OBJTYPE_BLOCK,                                     // �I�u�W�F�N�g�̃^�C�v
					DETAILSCHANGE_CREATE);                                     // �ύX���e��ۑ�
			}
			else{
                CreatBlockControl(m_FixedSshaft,                                   // �O���b�h��K�p���̍��W
                                  D3DXVECTOR3(m_posR.x, m_CopyPos.y, m_posR.z),    // �J�[�\���̍��W
                                  m_CopyRot,                                       // �R�s�[�����I�u�W�F�N�g�̌���
                                  m_nCopyType,                                     // �R�s�[�����I�u�W�F�N�g�̎��
                                  false,                                           // �ύX��K�p�����{��Ԃɂ���
                                  nCount,                                          // �ύX�ԍ�
                                  CScene::OBJTYPE_BLOCK,                           // �I�u�W�F�N�g�̃^�C�v
                                  DETAILSCHANGE_CREATE);                           // �ύX���e��ۑ�
            }

        }
    }

    //�E�N���b�N���ꂽ��
    if(m_pMouse->GetMouseTriggerRight()) {
		if (m_bGreaseJudge) {
			CreatBlockControl(m_FixedSshaft, D3DXVECTOR3(m_CursorPos.x, 0, m_CursorPos.z), D3DXVECTOR3(0, 0, 0), m_nBlockType, false, nCount, CScene::OBJTYPE_BLOCK, DETAILSCHANGE_CREATE);
		}
		else {
            CreatBlockControl(m_FixedSshaft, D3DXVECTOR3(m_posR.x, 0, m_posR.z), D3DXVECTOR3(0, 0, 0), m_nBlockType, false, nCount, CScene::OBJTYPE_BLOCK, DETAILSCHANGE_CREATE);
        }

    }
    //���N���b�N���ꂽ��
    if(m_pMouse->GetMouseTriggerLeft()) {
        //�I�u�W�F�N�g��I�����Ă�ꍇ
        if(CBlock::GetSelectBlock() != NULL) {
            // �z��̊m�F
            nCount = ShiftArray(nCount);
            // �����I�u�W�F�N�g����ۑ�
            SaveData(CBlock::GetSelectBlock()->GetPos(),
                     CBlock::GetSelectBlock()->GetRot(),
                     CBlock::GetSelectBlock()->GetNumber(),
                     DETAILSCHANGE_BREAK,
                     false,
                     CBlock::GetSelectBlock()->GetType(),
                     nCount,
                     CScene::OBJTYPE_BLOCK);
            //�I�����Ă�I�u�W�F�g����������
            CBlock::GetSelectBlock()->Uninit();
        }
    }

    // �I�u�W�F�N�g�S�������Ǘ�����ϐ����L���̏ꍇ
    if(m_bUseAllDelete == true) {
        // �ݒu����Ă���I�u�W�F�N�g��S�ď�������
        nCount = BlockAllDelete(nCount);

        // �I�u�W�F�N�g������0�ɂȂ����ꍇ�A�����ɂ���
        if(CBlock::GetBlockNumAll() <= 0) {
            m_bUseAllDelete = false;
        }
    }

    return nCount;
}

//=============================================================================
// �G��ݒu
//=============================================================================
int CCreateStage::SetEnemy(CInputKeyboard *m_pInputKeyboard, D3DXVECTOR3 m_posR, CMouse *m_pMouse, int nCount, BLOCKSAVEDATE m_aBlockSaveDate, CREATEOBJECT m_CreateType)
{
    static D3DXVECTOR3 Pos;
    static D3DXVECTOR3 Rot;
    static int nNumber = -1;

    // �^�C�v���Ǘ�����ϐ����͈͊O�ɂȂ�Ȃ��悤�ɏ���
    if(m_nEnemyType >= CEnemy::TYPE_MAX) {
        m_nEnemyType = CEnemy::TYPE_MAX - 1;
    }
    if(m_nEnemyType < 0) {
        m_nEnemyType = 0;
    }

    //=================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
    // �ݒu�I�u�W�F�N�g�̕ύX

	// ���R���g���[����������Ă��Ȃ��ꍇ
	if (!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
		// ���C�������L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_1)) {
			SetObjectType(CEnemy::TYPE_1);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_2)) {
			SetObjectType(CEnemy::TYPE_2);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_3)) {
			SetObjectType(CEnemy::TYPE_3);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_4)) {
			SetObjectType(CEnemy::TYPE_4);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_5)) {
			SetObjectType(CEnemy::TYPE_5);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_6)) {
			SetObjectType(CEnemy::TYPE_6);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_7)) {
			SetObjectType(CEnemy::TYPE_7);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_8)) {
			SetObjectType(CEnemy::TYPE_8);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_9)) {
			SetObjectType(CEnemy::TYPE_9);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_0)) {
			SetObjectType(CEnemy::TYPE_10);
		}
		// �e���L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD1)) {
			SetObjectType(CEnemy::TYPE_11);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD2)) {
			SetObjectType(CEnemy::TYPE_12);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD3)) {
			SetObjectType(CEnemy::TYPE_13);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD4)) {
			SetObjectType(CEnemy::TYPE_14);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD5)) {
			SetObjectType(CEnemy::TYPE_15);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD6)) {
			SetObjectType(CEnemy::TYPE_16);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD7)) {
			SetObjectType(CEnemy::TYPE_17);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD8)) {
			SetObjectType(CEnemy::TYPE_18);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD9)) {
			SetObjectType(CEnemy::TYPE_19);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0)) {
			SetObjectType(CEnemy::TYPE_20);
		}
	}
	// ���R���g���[����������Ă���ꍇ
	else if (m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
		// ���C�������L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_1)) {
			SetObjectType(CEnemy::TYPE_21);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_2)) {
			SetObjectType(CEnemy::TYPE_22);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_3)) {
			SetObjectType(CEnemy::TYPE_23);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_4)) {
			SetObjectType(CEnemy::TYPE_24);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_5)) {
			SetObjectType(CEnemy::TYPE_25);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_6)) {
			SetObjectType(CEnemy::TYPE_26);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_7)) {
			SetObjectType(CEnemy::TYPE_27);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_8)) {
			SetObjectType(CEnemy::TYPE_28);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_9)) {
			SetObjectType(CEnemy::TYPE_29);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_0)) {
			SetObjectType(CEnemy::TYPE_30);
		}
		// �e���L�[
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD1)) {
			SetObjectType(CEnemy::TYPE_31);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD2)) {
			SetObjectType(CEnemy::TYPE_32);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD3)) {
			SetObjectType(CEnemy::TYPE_33);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD4)) {
			SetObjectType(CEnemy::TYPE_34);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD5)) {
			SetObjectType(CEnemy::TYPE_35);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD6)) {
			SetObjectType(CEnemy::TYPE_36);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD7)) {
			SetObjectType(CEnemy::TYPE_37);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD8)) {
			SetObjectType(CEnemy::TYPE_38);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD9)) {
			SetObjectType(CEnemy::TYPE_39);
		}
		if (m_pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0)) {
			SetObjectType(CEnemy::TYPE_40);
		}
	}
    //=================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================

    // ���R���g���[����X�L�[�������ꂽ�Ƃ��I�𒆂̃I�u�W�F�N�g����ۑ����A�I�𒆂̃I�u�W�F�N�g������
    if(m_pInputKeyboard->GetKeyboardPress(DIK_X) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_X)) {

        // �I�u�W�F�N�g��I�����Ă���ꍇ
        if(CEnemy::GetSelectEnemy() != NULL) {
            // �z��̊m�F
            nCount = ShiftArray(nCount);
            // �����I�u�W�F�N�g����ۑ�
            SaveData(CEnemy::GetSelectEnemy()->GetPos(),
                     CEnemy::GetSelectEnemy()->GetRot(),
                     CEnemy::GetSelectEnemy()->GetNumber(),
                     DETAILSCHANGE_BREAK,
                     false,
                     CEnemy::GetSelectEnemy()->GetType(),
                     nCount,
                     CScene::OBJTYPE_ENEMY);
            // �I�𒆂̃I�u�W�F�N�g����ۑ�
            SetCopyData(CEnemy::GetSelectEnemy()->GetPos(),
                        CEnemy::GetSelectEnemy()->GetRot(),
                        CEnemy::GetSelectEnemy()->GetType());
            // �I�𒆂̃I�u�W�F�N�g������
            CEnemy::GetSelectEnemy()->Uninit();
        }
    }

    // �R���g���[����P�L�[�������ꂽ�ꍇ
    if(m_pInputKeyboard->GetKeyboardPress(DIK_P) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_P)) {

        if(CEnemy::GetEnemyNumAll() >= OBJECT_MIN_NUM) {
            // �ݒu����Ă���I�u�W�F�N�g��S�ď�������֐���ǂݍ��ޏ�ԂɕύX
            m_bUseAllDelete = true;
            // �S�������s���O�̃I�u�W�F�N�g�̑������擾
            m_nAllDeleteNum = CEnemy::GetEnemyNumAll();
        }
    }

    // �I�u�W�F�N�g��I���o���Ă���ꍇ
    if(CEnemy::GetSelectEnemy() != NULL) {
        // �ύX�O�̏����擾
        if(nNumber == -1 || nNumber != CEnemy::GetSelectEnemy()->GetNumber()) {
            Pos     = CEnemy::GetSelectEnemy()->GetPos();
            Rot     = CEnemy::GetSelectEnemy()->GetRot();
            nNumber = CEnemy::GetSelectEnemy()->GetNumber();
        }
        // �I�𒆂̃I�u�W�F�N�g�����擾
        D3DXVECTOR3 SelectBlockPos = CEnemy::GetSelectEnemy()->GetPos();
        D3DXVECTOR3 SelectBlockRot = CEnemy::GetSelectEnemy()->GetRot();

        // Q/E�L�[�Ŋp�x��90�x���ɕω�������
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_Q)) {
            nAddupAngle += 90;
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_E)) {
            nAddupAngle -= 90;
        }

        // ���R���g���[����������Ă��Ȃ��ꍇ
        if(!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            // U/J�L�[�ō�����15���ω�������
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_U)) {
                SelectBlockPos.y += 15;
            }
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_J)) {
                SelectBlockPos.y -= 15;
            }
            // I/K�L�[��X����15���ω�������
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_I)) {
                SelectBlockPos.x += 15;
            }
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_K)) {
                SelectBlockPos.x -= 15;
            }
            // O/L�L�[����15���ω�������
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_O)) {
                SelectBlockPos.z += 15;
            }
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_L)) {
                SelectBlockPos.z -= 15;
            }
        }
        // ���R���g���[����������Ă���ꍇ
        else if(m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            // U/J�L�[�ō�����15���ω�������
            if(m_pInputKeyboard->GetKeyboardPress(DIK_U)) {
                SelectBlockPos.y += 5;
            }
            if(m_pInputKeyboard->GetKeyboardPress(DIK_J)) {
                SelectBlockPos.y -= 5;
            }
            // I/K�L�[��X����15���ω�������
            if(m_pInputKeyboard->GetKeyboardPress(DIK_I)) {
                SelectBlockPos.x += 5;
            }
            if(m_pInputKeyboard->GetKeyboardPress(DIK_K)) {
                SelectBlockPos.x -= 5;
            }
            // O/L�L�[����15���ω�������
            if(m_pInputKeyboard->GetKeyboardPress(DIK_O)) {
                SelectBlockPos.z += 5;
            }
            if(m_pInputKeyboard->GetKeyboardPress(DIK_L)) {
                SelectBlockPos.z -= 5;
            }
        }

        // F1/F2�L�[�őI�𒆃I�u�W�F�N�g�̏���ݒu���ꂽ��Ԃɖ߂�
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_F1)) {
            CEnemy::GetSelectEnemy()->SetPos(D3DXVECTOR3(Pos.x, Pos.y, Pos.z));
        }
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_F2)) {
            CEnemy::GetSelectEnemy()->SetRot(D3DXVECTOR3(Rot.x, Rot.y, Rot.z));
        }

        // ���R���g���[����C�L�[�������ꂽ�ꍇ
        if(m_pInputKeyboard->GetKeyboardPress(DIK_C) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_C)) {
			// �R�s�[����^�C�v��ϐ��ɕۑ�����
			m_nCopyType = CBlock::GetSelectBlock()->GetType();

            // �I�𒆂̃I�u�W�F�N�g����ۑ�����
            SetCopyData(SelectBlockPos, SelectBlockRot, m_nCopyType);
        }

        //�@���Z/���Z������ϐ����傫�����Ȃ��悤�ɒ���
        if(nAddupAngle % 360 == 0) {
            nAddupAngle = 0;
        }
        if(SelectBlockPos.y > 10000) {
            SelectBlockPos.y = 10000;
        }
        if(SelectBlockPos.y < -10000) {
            SelectBlockPos.y = -10000;
        }

        // Q/E�L�[�������ꂽ�ꍇ
        if(m_pInputKeyboard->GetKeyboardTrigger(DIK_Q) || m_pInputKeyboard->GetKeyboardTrigger(DIK_E)) {
            // �z��̊m�F
            nCount = ShiftArray(nCount);
            // �I�u�W�F�N�g�̌�����1���ڐ؂�̂Ă���
            int RotX = (int)CEnemy::GetSelectEnemy()->GetRot().x / 10 * 10;
            int RotY = (int)CEnemy::GetSelectEnemy()->GetRot().y / 10 * 10;
            int RotZ = (int)CEnemy::GetSelectEnemy()->GetRot().z / 10 * 10;
            // �ύX����ۑ�����
            SaveData(CEnemy::GetSelectEnemy()->GetPos(),
                     CEnemy::GetSelectEnemy()->GetRot(),
                     CEnemy::GetSelectEnemy()->GetNumber(),
                     DETAILSCHANGE_CHANGE_ROT,
                     false,
                     CEnemy::GetSelectEnemy()->GetType(),
                     nCount,
                     CEnemy::OBJTYPE_ENEMY);

            // �I�𒆂̃I�u�W�F�N�g�̌�����ύX
            CEnemy::GetSelectEnemy()->SetRot(
              D3DXVECTOR3(D3DXToRadian(RotX), D3DXToRadian(RotY + nAddupAngle), D3DXToRadian(RotZ)));
        }
        // ���R���g���[����������Ă��Ȃ��ꍇ
        if(!m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            if(m_pInputKeyboard->GetKeyboardTrigger(DIK_U) || m_pInputKeyboard->GetKeyboardTrigger(DIK_J) || m_pInputKeyboard->GetKeyboardTrigger(DIK_I) || m_pInputKeyboard->GetKeyboardTrigger(DIK_K) || m_pInputKeyboard->GetKeyboardTrigger(DIK_O) || m_pInputKeyboard->GetKeyboardTrigger(DIK_L)) {
                // �z��̊m�F
                nCount = ShiftArray(nCount);
                // �ύX����ۑ�����
                SaveData(CEnemy::GetSelectEnemy()->GetPos(),
                         CEnemy::GetSelectEnemy()->GetRot(),
                         CEnemy::GetSelectEnemy()->GetNumber(),
                         DETAILSCHANGE_CHANGE_POS,
                         false,
                         CEnemy::GetSelectEnemy()->GetType(),
                         nCount,
                         CEnemy::OBJTYPE_ENEMY);

                // �I�𒆂̃I�u�W�F�N�g�̍��W��ύX
                CEnemy::GetSelectEnemy()->SetPos(
                  D3DXVECTOR3(SelectBlockPos.x, SelectBlockPos.y, SelectBlockPos.z));
            }
        }
        // ���R���g���[����������Ă���ꍇ
        else if(m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL)) {
            if(m_pInputKeyboard->GetKeyboardPress(DIK_U) || m_pInputKeyboard->GetKeyboardPress(DIK_J) || m_pInputKeyboard->GetKeyboardPress(DIK_I) || m_pInputKeyboard->GetKeyboardPress(DIK_K) || m_pInputKeyboard->GetKeyboardPress(DIK_O) || m_pInputKeyboard->GetKeyboardPress(DIK_L)) {
                // �z��̊m�F
                nCount = ShiftArray(nCount);
                // �ύX����ۑ�����
                SaveData(CEnemy::GetSelectEnemy()->GetPos(),
                         CEnemy::GetSelectEnemy()->GetRot(),
                         CEnemy::GetSelectEnemy()->GetNumber(),
                         DETAILSCHANGE_CHANGE_POS,
                         false,
                         CEnemy::GetSelectEnemy()->GetType(),
                         nCount,
                         CEnemy::OBJTYPE_ENEMY);

                // �I�𒆂̃I�u�W�F�N�g�̍��W��ύX
                CEnemy::GetSelectEnemy()->SetPos(
                  D3DXVECTOR3(SelectBlockPos.x, SelectBlockPos.y, SelectBlockPos.z));
            }
        }
    }

    // ���R���g���[����S�L�[�扟���ꂽ�Ƃ�
    if(m_pInputKeyboard->GetKeyboardPress(DIK_S) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_S)) {

        // �R���g���[����S�L�[�������ꂽ���Ƃ𔻒�
        m_bPushedControlS = true;
        // �ۑ��o�������̃t���O�����s�̏�Ԃŏ���������
        m_bSaveJudge = false;
        //�u���b�N�̍��W��ۑ�
        SaveEnemy();
    }

    // ���R���g���[����V�L�[�������ꂽ�Ƃ�
    if(m_pInputKeyboard->GetKeyboardPress(DIK_V) && m_pInputKeyboard->GetKeyboardTrigger(DIK_LCONTROL) || m_pInputKeyboard->GetKeyboardPress(DIK_LCONTROL) && m_pInputKeyboard->GetKeyboardTrigger(DIK_V)) {

        //�I�u�W�F�N�g�̏�񂪓����Ă���ꍇ
        if(m_nCopyType >= 0) {
            if(m_bGreaseJudge = false) {
                CreatBlockControl(m_FixedSshaft,                                   // �O���b�h��K�p���̍��W
                                  D3DXVECTOR3(m_posR.x, m_CopyPos.y, m_posR.z),    // �J�[�\���̍��W
                                  m_CopyRot,                                       // �R�s�[�����I�u�W�F�N�g�̌���
                                  m_nCopyType,                                     // �R�s�[�����I�u�W�F�N�g�̎��
                                  false,                                           // �ύX��K�p�����{��Ԃɂ���
                                  nCount,                                          // �ύX�ԍ�
                                  CScene::OBJTYPE_ENEMY,                           // �I�u�W�F�N�g�̃^�C�v
                                  DETAILSCHANGE_CREATE);                           // �ύX���e��ۑ�
            }
            if(m_bGreaseJudge = true) {
                CreatBlockControl(m_FixedSshaft,                                             // �O���b�W�h�K�p���̍��W
                                  D3DXVECTOR3(m_CursorPos.x, m_CopyPos.y, m_CursorPos.z),    // �J�[�\���̍��W
                                  m_CopyRot,                                                 // �R�s�[�����I�u�W�F�N�g�̌���
                                  m_nCopyType,                                               // �R�s�[�����I�u�W�F�N�g�̎��
                                  false,                                                     // �ύX��K�p�����{��Ԃɂ���
                                  nCount,                                                    // �ύX�ԍ�
                                  CScene::OBJTYPE_ENEMY,                                     // �I�u�W�F�N�g�̃^�C�v
                                  DETAILSCHANGE_CREATE);                                     // �ύX���e��ۑ�
            }
        }
    }

    //�E�N���b�N���ꂽ��
    if(m_pMouse->GetMouseTriggerRight()) {
		if (m_bGreaseJudge) {
			CreatBlockControl(m_FixedSshaft, D3DXVECTOR3(m_CursorPos.x, 0, m_CursorPos.z), D3DXVECTOR3(0, 0, 0), m_nEnemyType, false, nCount, CScene::OBJTYPE_ENEMY, DETAILSCHANGE_CREATE);
		}
		else {
			CreatBlockControl(m_FixedSshaft, D3DXVECTOR3(m_posR.x, 0, m_posR.z), D3DXVECTOR3(0, 0, 0), m_nEnemyType, false, nCount, CScene::OBJTYPE_ENEMY, DETAILSCHANGE_CREATE);
		}

    }
    //���N���b�N���ꂽ��
    if(m_pMouse->GetMouseTriggerLeft()) {
        //�I�u�W�F�N�g��I�����Ă�ꍇ
        if(CEnemy::GetSelectEnemy() != NULL) {
            // �z��̊m�F
            nCount = ShiftArray(nCount);
            // �����I�u�W�F�N�g����ۑ�
            SaveData(CEnemy::GetSelectEnemy()->GetPos(),
                     CEnemy::GetSelectEnemy()->GetRot(),
                     CEnemy::GetSelectEnemy()->GetNumber(),
                     DETAILSCHANGE_BREAK,
                     false,
                     CEnemy::GetSelectEnemy()->GetType(),
                     nCount,
                     CScene::OBJTYPE_ENEMY);
            //�I�����Ă�I�u�W�F�g����������
            CEnemy::GetSelectEnemy()->Uninit();
        }
    }

    // �I�u�W�F�N�g�S�������Ǘ�����ϐ����L���̏ꍇ
    if(m_bUseAllDelete == true) {
        // �ݒu����Ă���I�u�W�F�N�g��S�ď�������
        nCount = EnemyAllDelete(nCount);

        // �G�̑�����0�̏ꍇ�A�����ɂ���
        if(CEnemy::GetEnemyNumAll() <= 0) {
            m_bUseAllDelete = false;
        }
    }

    return nCount;
}

//=============================================================================
// �ݒu����Ă���I�u�W�F�N�g��S�ď�������
//=============================================================================
int CCreateStage::BlockAllDelete(int nCount)
{
    // �u���b�N�Ƃ̓����蔻��
    CScene *pScene = CScene::GetTopScene();

    for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
        // ���g������Ȃ�
        if(pScene != NULL) {
            // ���̃V�[�����L��
            CScene *pNextScene = pScene->GetNextScene();

            // �^�C�v���擾
            CScene::OBJTYPE objType = pScene->GetObjType();

            // �u���b�N�Ȃ�A
            if(objType == CScene::OBJTYPE_BLOCK) {
                // �u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock *)pScene;

                // �z��̊m�F
                nCount = ShiftArray(nCount);

                // �����I�u�W�F�N�g����ۑ�
                SaveData(pBlock->GetPos(),
                         pBlock->GetRot(),
                         pBlock->GetNumber(),
                         DETAILSCHANGE_TOTALELIMINATION,
                         false,
                         pBlock->GetType(),
                         nCount,
                         CScene::OBJTYPE_BLOCK);

                pBlock->Uninit();

                nCount++;
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
        else {
            // ���g���Ȃ��Ȃ�A�����ŏ������I����
            break;
        }
    }

    return nCount;
}

//=============================================================================
// �ݒu����Ă���G��S�ď�������
//=============================================================================
int CCreateStage::EnemyAllDelete(int nCount)
{
    // �u���b�N�Ƃ̓����蔻��
    CScene *pScene = CScene::GetTopScene();

    for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
        // ���g������Ȃ�
        if(pScene != NULL) {
            // ���̃V�[�����L��
            CScene *pNextScene = pScene->GetNextScene();

            // �^�C�v���擾
            CScene::OBJTYPE objType = pScene->GetObjType();

            // �G�Ȃ�A
            if(objType == CScene::OBJTYPE_ENEMY) {
                // �G�ɃL���X�g
                CEnemy *pEnemy = (CEnemy *)pScene;

                // �z��̊m�F
                nCount = ShiftArray(nCount);

                // �����I�u�W�F�N�g����ۑ�
                SaveData(pEnemy->GetPos(),
                         pEnemy->GetRot(),
                         pEnemy->GetNumber(),
                         DETAILSCHANGE_TOTALELIMINATION,
                         false,
                         pEnemy->GetType(),
                         nCount,
                         CScene::OBJTYPE_ENEMY);

                pEnemy->Uninit();

                nCount++;
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
        else {
            // ���g���Ȃ��Ȃ�A�����ŏ������I����
            break;
        }
    }

    return nCount;
}

//=============================================================================
// �u���b�N�ݒu�̐���
//=============================================================================
void CCreateStage::CreatBlockControl(D3DXVECTOR3 FixedSshaft,
                                     D3DXVECTOR3 CursorPos,
                                     D3DXVECTOR3 PosR,
                                     int nType,
                                     bool Judge,
                                     int nCount,
                                     CScene::OBJTYPE ObjectType,
                                     DETAILSCHANGE DetallsChange)
{
	// �����ꎞ�ۑ�����p�ϐ�
    D3DXVECTOR3 pos;
    int nNumber;

    // �I�u�W�F�N�g�̎�ނɂ���Đ�������N���X��؂�ւ���
    switch(ObjectType) {
        case CScene::OBJTYPE_BLOCK:

            if(m_bFixedSshaft[0] == false && m_bFixedSshaft[1] == false) {
                // �I�u�W�F�N�g��ݒu
                CBlock::Create(D3DXVECTOR3(CursorPos.x, CursorPos.y, CursorPos.z), PosR, nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = CursorPos;
            }
            else if(m_bFixedSshaft[0] == true && m_bFixedSshaft[1] == false) {
                // �I�u�W�F�N�g��ݒu
                CBlock::Create(D3DXVECTOR3(FixedSshaft.x, CursorPos.y, CursorPos.z), PosR, nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = D3DXVECTOR3(FixedSshaft.x, CursorPos.y, CursorPos.z);
            }
            else if(m_bFixedSshaft[0] == false && m_bFixedSshaft[1] == true) {
                // �I�u�W�F�N�g��ݒu
                CBlock::Create(D3DXVECTOR3(CursorPos.x, CursorPos.y, FixedSshaft.z), PosR, nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
				pos = D3DXVECTOR3(CursorPos.x, CursorPos.y, FixedSshaft.z);
            }
            else {
                // �I�u�W�F�N�g��ݒu
                CBlock::Create(D3DXVECTOR3(FixedSshaft.x, CursorPos.y, FixedSshaft.z),
                               PosR,
                               nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = D3DXVECTOR3(FixedSshaft.x, CursorPos.y, FixedSshaft.z);
            }

            nNumber = (CBlock::GetBlockNumAll() - NEXT_DATA);

            break;

        case CScene::OBJTYPE_ENEMY:

            if(m_bFixedSshaft[0] == false && m_bFixedSshaft[1] == false) {
                // �G��ݒu
                CEnemy::Create(D3DXVECTOR3(CursorPos.x, CursorPos.y, CursorPos.z), PosR, nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = CursorPos;
            }
            else if(m_bFixedSshaft[0] == true && m_bFixedSshaft[1] == false) {
                // �G��ݒu
                CEnemy::Create(D3DXVECTOR3(FixedSshaft.x, CursorPos.y, CursorPos.z), PosR, nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = D3DXVECTOR3(FixedSshaft.x, CursorPos.y, CursorPos.z);
            }
            else if(m_bFixedSshaft[0] == false && m_bFixedSshaft[1] == true) {
                // �G��ݒu
                CEnemy::Create(D3DXVECTOR3(CursorPos.x, CursorPos.y, FixedSshaft.z), PosR, nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = D3DXVECTOR3(CursorPos.x, CursorPos.y, FixedSshaft.z);
            }
            else {
                // �G��ݒu
                CEnemy::Create(D3DXVECTOR3(FixedSshaft.x, CursorPos.y, FixedSshaft.z),
                               PosR,
                               nType);

                // �ݒu����I�u�W�F�N�g�̏���ۑ�
                pos = D3DXVECTOR3(FixedSshaft.x, CursorPos.y, FixedSshaft.z);
            }

            nNumber = (CEnemy::GetEnemyNumAll() - NEXT_DATA);

            break;
    }

    // �ݒu����I�u�W�F�N�g����ۑ�
    SaveData(pos,
             PosR,
             nNumber,
             DetallsChange,
             false,
             nType,
             nCount,
             ObjectType);
}

//=============================================================================
// �J�[�\���̐���
//=============================================================================
void CCreateStage::CursorControl(D3DXVECTOR3 FixedSshaft, D3DXVECTOR3 CursorPos, CREATEOBJECT m_CreateType)
{
    if(m_bFixedSshaft[0] == false && m_bFixedSshaft[1] == false) {
        // �u���ꏊ�𕪂���₷��
        CEffect3D::Create(D3DXVECTOR3(CursorPos.x, CURSOR_POS_Y, CursorPos.z),
                          CURSOR_SIZE,
                          DEFAULT_VECTOR,
                          DEFAULT_COLOR,
                          CEffect3D::TYPE_CURSOR);
        // �J�[�\���̓����蔻��
        CursorCollision(D3DXVECTOR3(CursorPos.x, CURSOR_POS_Y, CursorPos.z),
                        m_CreateType);
    }
    else if(m_bFixedSshaft[0] == true && m_bFixedSshaft[1] == false) {
        // �u���ꏊ�𕪂���₷��
        CEffect3D::Create(D3DXVECTOR3(FixedSshaft.x, CURSOR_POS_Y, CursorPos.z),
                          CURSOR_SIZE,
                          DEFAULT_VECTOR,
                          DEFAULT_COLOR,
                          CEffect3D::TYPE_CURSOR);
        // �J�[�\���̓����蔻��
        CursorCollision(D3DXVECTOR3(FixedSshaft.x, CURSOR_POS_Y, CursorPos.z),
                        m_CreateType);
    }
    else if(m_bFixedSshaft[0] == false && m_bFixedSshaft[1] == true) {
        // �u���ꏊ�𕪂���₷��
        CEffect3D::Create(D3DXVECTOR3(CursorPos.x, CURSOR_POS_Y, FixedSshaft.z),
                          CURSOR_SIZE,
                          DEFAULT_VECTOR,
                          DEFAULT_COLOR,
                          CEffect3D::TYPE_CURSOR);
        // �J�[�\���̓����蔻��
        CursorCollision(D3DXVECTOR3(CursorPos.x, CURSOR_POS_Y, FixedSshaft.z),
                        m_CreateType);
    }
    else {
        // �u���ꏊ�𕪂���₷��
        CEffect3D::Create(D3DXVECTOR3(FixedSshaft.x, CURSOR_POS_Y, FixedSshaft.z),
                          CURSOR_SIZE,
                          DEFAULT_VECTOR,
                          DEFAULT_COLOR,
                          CEffect3D::TYPE_CURSOR);
        // �J�[�\���̓����蔻��
        CursorCollision(D3DXVECTOR3(FixedSshaft.x, CURSOR_POS_Y, FixedSshaft.z),
                        m_CreateType);
    }
}

//=============================================================================
// �J�[�\���̓����蔻��
//=============================================================================
void CCreateStage::CursorCollision(D3DXVECTOR3 pos, CREATEOBJECT m_CreateType)
{
    // �u���b�N�Ƃ̓����蔻��
    CScene *pScene    = CScene::GetTopScene();
    bool bSelectBlock = false;    // �I�����Ă��邩�ǂ����̃t���O
    bool bSelectEnemy = false;
    for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
        // ���g������Ȃ�
        if(pScene != NULL) {
            // ���̃V�[�����L��
            CScene *pNextScene = pScene->GetNextScene();

            // �^�C�v���擾
            CScene::OBJTYPE objType = pScene->GetObjType();

            // �u���b�N�Ȃ�A
            if(objType == CScene::OBJTYPE_BLOCK && m_CreateType == CREATEOBJECT_STAGE) {
                // �u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock *)pScene;

                // �J�[�\���̓����蔻��̃T�C�Y��ݒ�
                D3DXVECTOR3 cursorCollisionSize = CURSOR_COLLISION_SIZE;

                // �J�[�\���̓����蔻����v�Z
                if(RectangleCollision3D(&pos, &pBlock->GetPos(), &cursorCollisionSize, &pBlock->GetCollisionSize()) == true) {
                    // �������Ă���Ȃ�A�I�����Ă���u���b�N�ɂ���
                    CBlock::SetSelectBlock(pBlock);

                    // �I�����Ă���
                    bSelectBlock = true;
                }
            }

            // �G�Ȃ�A
            if(objType == CScene::OBJTYPE_ENEMY && m_CreateType == CREATEOBJECT_ENEMY) {
                // �G�ɃL���X�g
                CEnemy *pEnemy = (CEnemy *)pScene;

                // �J�[�\���̓����蔻��̃T�C�Y��ݒ�
                D3DXVECTOR3 cursorCollisionSize = CURSOR_COLLISION_SIZE;

                // �J�[�\���̓����蔻����v�Z
                if(RectangleCollision3D(&pos, &pEnemy->GetPos(), &cursorCollisionSize, &pEnemy->GetCollisionSize()) == true) {
                    // �������Ă���Ȃ�A�I�����Ă���u���b�N�ɂ���
                    CEnemy::SetSelectEnemy(pEnemy);

                    // �I�����Ă���
                    bSelectEnemy = true;
                }
            }

            // ���̃V�[���ɂ���
            pScene = pNextScene;
        }
        else {
            // ���g���Ȃ��Ȃ�A�����ŏ������I����
            break;
        }
    }

    // �I�����Ă�����̂��Ȃ��Ȃ�
    if(bSelectBlock == false) {
        // �I�����Ă���u���b�N��NULL�ɂ���
        CBlock::SetSelectBlock(NULL);
    }
    // �I�����Ă�����̂������ꍇ
    if(bSelectEnemy == false) {
        // �I�����Ă���G��NULL�ɂ���
        CEnemy::SetSelectEnemy(NULL);
    }
}

//=============================================================================
// �X�e�[�W�̃I�u�W�F�N�g��ǂݍ���
//=============================================================================
HRESULT CCreateStage::LoadStage(void)
{
    // �t�@�C���|�C���g
    FILE *pFile = NULL;

    // �ϐ��錾
    int nCntLoad = 0;
    char cReedText[128];    // �����Ƃ��ēǂݎ��p
    char cHeadText[256];    //
    char cDie[128];

    // �f�o�b�O�p�̕ϐ�
    int nType[256];
    D3DXVECTOR3 pos[256];
    D3DXVECTOR3 rot[256];

    // �t�@�C���J
    pFile = fopen(m_cTxtName[0], "r");

    CField::SetMapSiz(D3DXVECTOR3(MAP_WIDTH, MAP_HEIGHT, 0));

    // �J����
    if(pFile != NULL) {
        while(strcmp(cHeadText, "MODELSET") != 0) {
            fgets(cReedText, sizeof(cReedText), pFile);
            sscanf(cReedText, "%s", &cHeadText);

            if(strcmp(cHeadText, "MAP_SIZ") == 0) {
                sscanf(cReedText, "%s %s %f %f", &cDie, &cDie, &m_FieldSiz.x, &m_FieldSiz.y);
                CField::SetMapSiz(m_FieldSiz);
            }
        }

        if(strcmp(cHeadText, "MODELSET") == 0) {
            while(strcmp(cHeadText, "END_SCRIPT") != 0) {
                fgets(cReedText, sizeof(cReedText), pFile);
                sscanf(cReedText, "%s", &cHeadText);

                if(strcmp(cHeadText, "\n") == 0) {
                }
                else if(strcmp(cHeadText, "END_MODELSET") != 0) {
                    if(strcmp(cHeadText, "TYPE") == 0) {
                        sscanf(cReedText, "%s %s %d", &cDie, &cDie, &nType[nCntLoad]);
                    }

                    if(strcmp(cHeadText, "POS") == 0) {
                        sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &pos[nCntLoad].x, &pos[nCntLoad].y, &pos[nCntLoad].z);
                    }

                    if(strcmp(cHeadText, "ROT") == 0) {
                        sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &rot[nCntLoad].x, &rot[nCntLoad].y, &rot[nCntLoad].z);

                        // �u���b�N�𐶐�
                        CBlock::Create(pos[nCntLoad],
                                       D3DXVECTOR3(D3DXToRadian(rot[nCntLoad].x),
                                                   D3DXToRadian(rot[nCntLoad].y),
                                                   D3DXToRadian(rot[nCntLoad].z)),
                                       nType[nCntLoad]);

                        nCntLoad++;
                    }
                }
            }
        }
        // �t�@�C����
        fclose(pFile);

        return S_OK;
    }

    // �J���Ȃ�
    else {
        printf("�J����܂���ł���\n");
    }

    return E_FAIL;
}

//=============================================================================
// �X�e�[�W�̓G��ǂݍ���
//=============================================================================
HRESULT CCreateStage::LoadEnemy(void)
{
    // �t�@�C���|�C���g
    FILE *pFile = NULL;

    // �ϐ��錾
    int nCntLoad = 0;
    char cReedText[128];    // �����Ƃ��ēǂݎ��p
    char cHeadText[256];    //
    char cDie[128];

    // �f�o�b�O�p�̕ϐ�
    int nType[256];
    D3DXVECTOR3 pos[256];
    D3DXVECTOR3 rot[256];

    // �t�@�C���J
    pFile = fopen(m_cTxtName[1], "r");

    // �J����
    if(pFile != NULL) {
        while(strcmp(cHeadText, "ENEMYSET") != 0) {
            fgets(cReedText, sizeof(cReedText), pFile);
            sscanf(cReedText, "%s", &cHeadText);
        }

        if(strcmp(cHeadText, "ENEMYSET") == 0) {
            while(strcmp(cHeadText, "END_SCRIPT") != 0) {
                fgets(cReedText, sizeof(cReedText), pFile);
                sscanf(cReedText, "%s", &cHeadText);

                if(strcmp(cHeadText, "\n") == 0) {
                }
                else if(strcmp(cHeadText, "END_ENEMYSET") != 0) {
                    if(strcmp(cHeadText, "TYPE") == 0) {
                        sscanf(cReedText, "%s %s %d", &cDie, &cDie, &nType[nCntLoad]);
                    }

                    if(strcmp(cHeadText, "POS") == 0) {
                        sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &pos[nCntLoad].x, &pos[nCntLoad].y, &pos[nCntLoad].z);
                    }

                    if(strcmp(cHeadText, "ROT") == 0) {
                        sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &rot[nCntLoad].x, &rot[nCntLoad].y, &rot[nCntLoad].z);

                        // �u���b�N�𐶐�
                        CEnemy::Create(pos[nCntLoad],
                                       D3DXVECTOR3(D3DXToRadian(rot[nCntLoad].x),
                                                   D3DXToRadian(rot[nCntLoad].y),
                                                   D3DXToRadian(rot[nCntLoad].z)),
                                       nType[nCntLoad]);

                        nCntLoad++;
                    }
                }
            }
        }
        // �t�@�C����
        fclose(pFile);

        return S_OK;
    }

    // �J���Ȃ�
    else {
        printf("�J����܂���ł���\n");
    }

    return E_FAIL;
}

//=============================================================================
// �X�e�[�W�̃I�u�W�F�N�g�����O���o��
//=============================================================================
HRESULT CCreateStage::SaveStage(void)
{
    FILE *fp;

    if(CBlock::GetBlockNumAll() != 0) {

        fp = fopen(m_cTxtName[0], "w");

        if(fp != NULL) {
            // �I�u�W�F�N�g�̐擪�̏����擾
            CScene *pScene = CScene::GetTopScene();

            fprintf(fp, "SCRIPT			# "
                        "���̍s�͐�Ώ����Ȃ����ƁI\n\n");

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �ǂݍ��ރ��f����\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "NUM_MODEL = %d\n\n", CBlock::GetBlockNumAll());

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �}�b�v�T�C�Y\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            // �}�b�v�̃T�C�Y���擾���A�傫����1�}�X�ȏ㑶�݂���ꍇ�A���݂̑傫������������
            if(m_FieldSiz.x >= 1 && m_FieldSiz.y >= 1) {
                fprintf(fp, "MAP_SIZ = %d %d\n\n", (int)m_FieldSiz.x, (int)m_FieldSiz.y);
            }
            // �}�b�v�̃T�C�Y��1�}�X�����̏ꍇ�A�}�N����`����Ă���傫������������
            else {
                fprintf(fp, "MAP_SIZ = %d %d\n\n", MAP_WIDTH, MAP_HEIGHT);
            }

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �ǂݍ��ރ��f���t�@�C����\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "\n\n");

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �\�����郂�f���̔z�u���\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");

            for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
                // ���g������Ȃ�
                if(pScene != NULL) {
                    // ���̃V�[�����L��
                    CScene *pNextScene = pScene->GetNextScene();

                    // �^�C�v���擾
                    CScene::OBJTYPE objType = pScene->GetObjType();

                    if(objType == CScene::OBJTYPE_BLOCK) {
                        // �u���b�N�ɃL���X�g
                        CBlock *pBlock = (CBlock *)pScene;

                        fprintf(fp, "MODELSET\n");

                        fprintf(fp, "	TYPE = %d\n", pBlock->GetType());
                        fprintf(fp, "	POS = %d %d %d\n", (int)pBlock->GetPos().x, (int)pBlock->GetPos().y, (int)pBlock->GetPos().z);
                        fprintf(fp, "	ROT = %d %d %d\n", (int)D3DXToDegree(pBlock->GetRot().x), (int)D3DXToDegree(pBlock->GetRot().y), (int)D3DXToDegree(pBlock->GetRot().z));

                        fprintf(fp, "END_MODELSET\n\n");
                    }

                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                }
                else {
                    // ���g���Ȃ��Ȃ�A�����ŏ������I����
                    break;
                }
            }

            fprintf(fp, "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI");

            fclose(fp);

            m_bSaveJudge = true;

            return S_OK;
        }
    }

    return E_FAIL;
}

//=============================================================================
// �X�e�[�W�̓G�����O���o��
//=============================================================================
HRESULT CCreateStage::SaveEnemy(void)
{
    FILE *fp;

    if(CEnemy::GetEnemyNumAll() != 0) {

        fp = fopen(m_cTxtName[1], "w");

        if(fp != NULL) {
            // �I�u�W�F�N�g�̐擪�̏����擾
            CScene *pScene = CScene::GetTopScene();

            fprintf(fp, "SCRIPT			# "
                        "���̍s�͐�Ώ����Ȃ����ƁI\n\n");

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �ǂݍ��ރ��f����\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "NUM_MODEL = %d\n\n", CEnemy::GetEnemyNumAll());

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �ǂݍ��ރ��f���t�@�C����\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "\n\n");

            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");
            fprintf(fp, "# �\�����郂�f���̔z�u���\n");
            fprintf(fp, "#-----------------------------------------------------------"
                        "-------------------\n");

            for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
                // ���g������Ȃ�
                if(pScene != NULL) {
                    // ���̃V�[�����L��
                    CScene *pNextScene = pScene->GetNextScene();

                    // �^�C�v���擾
                    CScene::OBJTYPE objType = pScene->GetObjType();

                    if(objType == CScene::OBJTYPE_ENEMY) {
                        // �u���b�N�ɃL���X�g
                        CEnemy *pEnemy = (CEnemy *)pScene;

                        fprintf(fp, "ENEMYSET\n");

                        fprintf(fp, "	TYPE = %d\n", pEnemy->GetType());
                        fprintf(fp, "	POS = %d %d %d\n", (int)pEnemy->GetPos().x, (int)pEnemy->GetPos().y, (int)pEnemy->GetPos().z);
                        fprintf(fp, "	ROT = %d %d %d\n", (int)D3DXToDegree(pEnemy->GetRot().x), (int)D3DXToDegree(pEnemy->GetRot().y), (int)D3DXToDegree(pEnemy->GetRot().z));

                        fprintf(fp, "END_ENEMYSET\n\n");
                    }

                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                }
                else {
                    // ���g���Ȃ��Ȃ�A�����ŏ������I����
                    break;
                }
            }

            fprintf(fp, "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI");

            fclose(fp);

            m_bSaveJudge = true;

            return S_OK;
        }
    }

    return E_FAIL;
}

//=============================================================================
// �ύX���e���O���o��
//=============================================================================
void CCreateStage::WriteBlockSaveDate(int nNumAll)
{
    FILE *fp;
    fp = fopen(DEBUG_TXT_NAME, "w");

    if(fp != NULL) {
        fprintf(fp, "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n\n");

        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "# �ۑ���\n");
        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "SAVE_NUM = %d\n\n", nNumAll);

        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "# �ύX���e�ƕύX�ԍ�\n");
        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "%d:DETAILSCHANGE_CHANGE_POS\n", DETAILSCHANGE_CHANGE_POS);
        fprintf(fp, "%d:DETAILSCHANGE_CHANGE_LAST_POS\n", DETAILSCHANGE_CHANGE_LAST_POS);
        fprintf(fp, "%d:DETAILSCHANGE_CHANGE_ROT\n", DETAILSCHANGE_CHANGE_ROT);
        fprintf(fp, "%d:DETAILSCHANGE_CHANGE_LAST_ROT\n", DETAILSCHANGE_CHANGE_LAST_ROT);
        fprintf(fp, "%d:DETAILSCHANGE_BREAK\n", DETAILSCHANGE_BREAK);
        fprintf(fp, "%d:DETAILSCHANGE_CREATE\n", DETAILSCHANGE_CREATE);
        fprintf(fp, "%d:DETAILSCHANGE_TOTALELIMINATION\n", DETAILSCHANGE_TOTALELIMINATION);
        fprintf(fp, "\n");

        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "# �I�u�W�F�N�g�ԍ��Ǝ��\n");
        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "%d:Block\n", CScene::OBJTYPE_BLOCK);
        fprintf(fp, "%d:Enemy\n", CScene::OBJTYPE_ENEMY);
        fprintf(fp, "\n\n");

        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");
        fprintf(fp, "# �ύX�O�̃I�u�W�F�N�g���\n");
        fprintf(fp, "#-------------------------------------------------------------"
                    "-----------------\n");

        for(int nCntScene = 0; nCntScene < nNumAll; nCntScene++) {
            if(m_aBlockSaveDate[nCntScene].DetailsChange != DETAILSCHANGE_NULL) {

                fprintf(fp, "DETAILSCHANGE : %d\n", nCntScene);

                fprintf(fp, "	NUMBER = %d\n", m_aBlockSaveDate[nCntScene].nNumber);
                fprintf(fp, "	DETAILSCHANGE = %d\n", m_aBlockSaveDate[nCntScene].DetailsChange);
                fprintf(fp, "	OBJTYPE = %d\n", m_aBlockSaveDate[nCntScene].ObjectType);
                fprintf(fp, "	TYPE = %d\n", m_aBlockSaveDate[nCntScene].nType);
                fprintf(fp, "	POS = %d %d %d\n", (int)m_aBlockSaveDate[nCntScene].pos.x, (int)m_aBlockSaveDate[nCntScene].pos.y, (int)m_aBlockSaveDate[nCntScene].pos.z);
                fprintf(fp, "	ROT = %d %d %d\n", (int)D3DXToDegree(m_aBlockSaveDate[nCntScene].rot.x), (int)D3DXToDegree(m_aBlockSaveDate[nCntScene].rot.y), (int)D3DXToDegree(m_aBlockSaveDate[nCntScene].rot.z));

                fprintf(fp, "END_DETAILSCHANGE\n\n");
            }
            else {
                break;
            }
        }

        fprintf(fp, "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI");

        fclose(fp);
    }
}

//=============================================================================
// �ύX���e�̏������ɖ߂�
//=============================================================================
int CCreateStage::UndoingOperation(int nCurNum)
{
    // �u���݂̔z���1��낪���݂��Ă���ꍇ�v���A�u���݂̔z���1���̕ύX���K�p����Ă��Ȃ���Ԃ̏ꍇ�v���A�u���݂̔z���1���̕ύX���e���o�^����Ă���ꍇ�v
    if(nCurNum - NEXT_DATA >= 0 && m_aBlockSaveDate[nCurNum - NEXT_DATA].bChangeJudge == false && m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange != DETAILSCHANGE_NULL) {
        // �擪�̃I�u�W�F�N�g�����擾
        CScene *pScene = CScene::GetTopScene();
        CBlock *pBlock;
        CEnemy *pEnemy;
        bool bSelectBlockJudge = false;    // �ύX���ꂽ�u���b�N�I�u�W�F�N�g�����o�������𔻒�
        bool bSelectEnemyJudge = false;    // �ύX���ꂽ�G�I�u�W�F�N�g�����o�������𔻒�
        bool bCheckData        = false;    // ���肵���I�u�W�F�N�g�ƕύX���e�̏�񂪑S�Ĉ�v���Ă��邩�𔻒�
        // �u�ύX���e�������ȊO�̏ꍇ�v���A�u�ύX���e���S�����ȊO�̏ꍇ�v
        if(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange != DETAILSCHANGE_BREAK && m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange != DETAILSCHANGE_TOTALELIMINATION) {
            // �ύX���K�p���ꂽ�I�u�W�F�N�g��{������
            for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
                // ���g������Ȃ�
                if(pScene != NULL) {
                    // ���̃V�[�����L��
                    CScene *pNextScene = pScene->GetNextScene();

                    // �^�C�v���擾
                    CScene::OBJTYPE objType = pScene->GetObjType();

                    // �u���b�N�Ȃ�A
                    if(objType == CScene::OBJTYPE_BLOCK && m_aBlockSaveDate[nCurNum - NEXT_DATA].ObjectType == CScene::OBJTYPE_BLOCK) {
                        // �u���b�N�ɃL���X�g
                        pBlock = (CBlock *)pScene;

                        // �ԍ����擾
                        int nNumber = pBlock->GetNumber();
                        // ��ނ��擾
                        int nType = pBlock->GetType();

                        // �u���b�N�ɃL���X�g�����I�u�W�F�N�g�ƕύX���ꂽ�I�u�W�F�N�g�̔ԍ�����v����ꍇ
                        if(nNumber == m_aBlockSaveDate[nCurNum - NEXT_DATA].nNumber && nType == m_aBlockSaveDate[nCurNum - NEXT_DATA].nType) {
                            // ����o������ԂɕύX
                            bSelectBlockJudge = true;
                            break;
                        }
                    }

                    // �G�Ȃ�A
                    if(objType == CScene::OBJTYPE_ENEMY && m_aBlockSaveDate[nCurNum - NEXT_DATA].ObjectType == CScene::OBJTYPE_ENEMY) {
                        // �G�ɃL���X�g
                        pEnemy = (CEnemy *)pScene;

                        // �ԍ����擾
                        int nNumber = pEnemy->GetNumber();
                        // ��ނ��擾
                        int nType = pEnemy->GetType();

                        // �G�ɃL���X�g�����I�u�W�F�N�g�ƕύX���ꂽ�I�u�W�F�N�g�̔ԍ�����v����ꍇ
                        if(nNumber == m_aBlockSaveDate[nCurNum - NEXT_DATA].nNumber && nType == m_aBlockSaveDate[nCurNum - NEXT_DATA].nType) {
                            // ����o������ԂɕύX
                            bSelectEnemyJudge = true;
                            break;
                        }
                    }

                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                }
                else {
                    // ���g���Ȃ��Ȃ�A�����ŏ������I����
                    break;
                }
            }
        }

		// �I�u�W�F�N�g�^�C�v���u���b�N�̏ꍇ
        if(m_aBlockSaveDate[nCurNum - NEXT_DATA].ObjectType == CScene::OBJTYPE_BLOCK) {
            // �u�ύX���K�p���ꂽ�u���b�N�����o�����ꍇ�v���́A�u�ύX���e�������̏ꍇ�v
            if(bSelectBlockJudge == true || m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_BREAK || m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                // �ύX���e�������̏ꍇ
                if(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_BREAK) {
                    CBlock::Create(m_aBlockSaveDate[nCurNum - NEXT_DATA].pos,
                                   m_aBlockSaveDate[nCurNum - NEXT_DATA].rot,
                                   m_aBlockSaveDate[nCurNum - NEXT_DATA].nType);
                }
                // �ύX���e���S�����̏ꍇ
                else if(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                    // �u���b�N�̏��ԂƐ����Ǘ�����ϐ�
                    int nBlockCount = 0;
                    // �u���b�N�̐����S�����������ȉ��̊Ԗ����Ƀ��[�v������
                    while(nBlockCount <= m_nAllDeleteNum) {
                        // �S�������������z����m�F����
                        for(int nCount = 1; nCount <= m_nAllDeleteNum; nCount++) {
                            // �I�u�W�F�N�g��S���������u�Ԃ̔ԍ����ɐ���
                            if(m_aBlockSaveDate[nCurNum - nCount].nNumber == nBlockCount) {
                                CBlock::Create(m_aBlockSaveDate[nCurNum - nCount].pos,
                                               m_aBlockSaveDate[nCurNum - nCount].rot,
                                               m_aBlockSaveDate[nCurNum - nCount].nType);

                                // �ύX���e���K�p���ꂽ��Ԃɂ���
                                m_aBlockSaveDate[nCurNum - nCount].bChangeJudge = true;

                                break;
                            }
                        }

                        // �ԍ��Ɛ���1���₷
                        nBlockCount++;
                    }
                }
                // �u�ύX���K�p���ꂽ�u���b�N�����o�����ꍇ�v���A�I�u�W�F�N�g�����擾�o���Ă���ꍇ
                else if(bSelectBlockJudge == true && pBlock != NULL) {
                    // �ύX���e�ɂ���ď�����ς���
                    switch(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange) {
                            // ���W�ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_POS:
                        case DETAILSCHANGE_CHANGE_POS:
                            // �u�ύX���K�p���ꂽ�u���b�N�̍��W�E�����E��ށE�ԍ����K�p����ύX���e�ƈ�v����ꍇ�v
                            if(pBlock->GetPos() == m_aBlockSaveDate[nCurNum - NEXT_DATA].pos && pBlock->GetRot() == m_aBlockSaveDate[nCurNum - NEXT_DATA].rot && pBlock->GetType() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nType && pBlock->GetNumber() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nNumber) {

                                bCheckData = true;
                                pBlock->SetPos(m_aBlockSaveDate[nCurNum - NEXT_TIME_DATA].pos);
                            }
                            else {
                                if(m_nLastCountPos == 0) {
                                    nCurNum = ShiftArray(nCurNum);

                                    SaveData(pBlock->GetPos(),
                                             pBlock->GetRot(),
                                             pBlock->GetNumber(),
                                             DETAILSCHANGE_CHANGE_LAST_POS,
                                             true,
                                             pBlock->GetType(),
                                             nCurNum,
                                             CScene::OBJTYPE_BLOCK);
                                }

                                pBlock->SetPos(m_aBlockSaveDate[nCurNum - NEXT_DATA].pos);
                            }
                            break;

                            // �����ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_ROT:
                        case DETAILSCHANGE_CHANGE_ROT:
                            // �u�ύX���K�p���ꂽ�u���b�N�̍��W�E�����E��ށE�ԍ����K�p����ύX���e�ƈ�v����ꍇ�v
                            if(pBlock->GetPos() == m_aBlockSaveDate[nCurNum - NEXT_DATA].pos && pBlock->GetRot() == m_aBlockSaveDate[nCurNum - NEXT_DATA].rot && pBlock->GetType() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nType && pBlock->GetNumber() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nNumber) {

                                bCheckData = true;
                                pBlock->SetRot(m_aBlockSaveDate[nCurNum - NEXT_TIME_DATA].rot);
                            }
                            else {
                                if(m_nLastCountRot == 0) {
                                    nCurNum = ShiftArray(nCurNum);

                                    SaveData(pBlock->GetPos(),
                                             pBlock->GetRot(),
                                             pBlock->GetNumber(),
                                             DETAILSCHANGE_CHANGE_LAST_ROT,
                                             true,
                                             pBlock->GetType(),
                                             nCurNum,
                                             CScene::OBJTYPE_BLOCK);
                                }

                                pBlock->SetRot(m_aBlockSaveDate[nCurNum - NEXT_DATA].rot);
                            }
                            break;

                            // �����̏ꍇ
                        case DETAILSCHANGE_CREATE:
                            pBlock->Uninit();
                            break;
                    }
                }
            }
        }

		// �I�u�W�F�N�g�^�C�v���G�̏ꍇ
        else if(m_aBlockSaveDate[nCurNum - NEXT_DATA].ObjectType == CScene::OBJTYPE_ENEMY) {
            // �u�ύX���K�p���ꂽ�G�����o�����ꍇ�v���́A�u�ύX���e�������̏ꍇ�v���́A�u�ύX���e���S�����̏ꍇ�v
            if(bSelectEnemyJudge == true || m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_BREAK || m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                // �ύX���e�������̏ꍇ
                if(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_BREAK) {
                    CEnemy::Create(m_aBlockSaveDate[nCurNum - NEXT_DATA].pos,
                                   m_aBlockSaveDate[nCurNum - NEXT_DATA].rot,
                                   m_aBlockSaveDate[nCurNum - NEXT_DATA].nType);
                }
                // �ύX���e���S�����̏ꍇ
                else if(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                    // �u���b�N�̏��ԂƐ����Ǘ�����ϐ�
                    int nBlockCount = 0;
                    // �u���b�N�̐����S�����������ȉ��̊Ԗ����Ƀ��[�v������
                    while(nBlockCount <= m_nAllDeleteNum) {
                        // �S�������������z����m�F����
                        for(int nCount = 1; nCount <= m_nAllDeleteNum; nCount++) {
                            // �I�u�W�F�N�g��S���������u�Ԃ̔ԍ����ɐ���
                            if(m_aBlockSaveDate[nCurNum - nCount].nNumber == nBlockCount) {
                                CEnemy::Create(m_aBlockSaveDate[nCurNum - nCount].pos,
                                               m_aBlockSaveDate[nCurNum - nCount].rot,
                                               m_aBlockSaveDate[nCurNum - nCount].nType);

                                // �ύX���e���K�p���ꂽ��Ԃɂ���
                                m_aBlockSaveDate[nCurNum - nCount].bChangeJudge = true;

                                break;
                            }
                        }

                        // �ԍ��Ɛ���1���₷
                        nBlockCount++;
                    }
                }
                // �u�ύX���K�p���ꂽ�G�����o�����ꍇ�v���A�I�u�W�F�N�g�����擾�o���Ă���ꍇ
                else if(bSelectEnemyJudge == true && pEnemy != NULL) {
                    // �ύX���e�ɂ���ď�����ς���
                    switch(m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange) {
                            // ���W�ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_POS:
                        case DETAILSCHANGE_CHANGE_POS:
                            // �u�ύX���K�p���ꂽ�G�̍��W�E�����E��ށE�ԍ����K�p����ύX���e�ƈ�v����ꍇ�v
                            if(pEnemy->GetPos() == m_aBlockSaveDate[nCurNum - NEXT_DATA].pos && pEnemy->GetRot() == m_aBlockSaveDate[nCurNum - NEXT_DATA].rot && pEnemy->GetType() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nType && pEnemy->GetNumber() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nNumber) {

                                bCheckData = true;
                                pEnemy->SetPos(m_aBlockSaveDate[nCurNum - NEXT_TIME_DATA].pos);
                            }
                            else {
                                if(m_nLastCountPos == 0) {
                                    nCurNum = ShiftArray(nCurNum);

                                    SaveData(pEnemy->GetPos(),
                                             pEnemy->GetRot(),
                                             pEnemy->GetNumber(),
                                             DETAILSCHANGE_CHANGE_LAST_POS,
                                             true,
                                             pEnemy->GetType(),
                                             nCurNum,
                                             CScene::OBJTYPE_ENEMY);
                                }

                                pEnemy->SetPos(m_aBlockSaveDate[nCurNum - NEXT_DATA].pos);
                            }
                            break;

                            // �����ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_ROT:
                        case DETAILSCHANGE_CHANGE_ROT:
                            // �u�ύX���K�p���ꂽ�G�̍��W�E�����E��ށE�ԍ����K�p����ύX���e�ƈ�v����ꍇ�v
                            if(pEnemy->GetPos() == m_aBlockSaveDate[nCurNum - NEXT_DATA].pos && pEnemy->GetRot() == m_aBlockSaveDate[nCurNum - NEXT_DATA].rot && pEnemy->GetType() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nType && pEnemy->GetNumber() == m_aBlockSaveDate[nCurNum - NEXT_DATA].nNumber) {

                                bCheckData = true;
                                pEnemy->SetRot(m_aBlockSaveDate[nCurNum - NEXT_TIME_DATA].rot);
                            }
                            else {
                                if(m_nLastCountRot == 0) {
                                    nCurNum = ShiftArray(nCurNum);

                                    SaveData(pEnemy->GetPos(),
                                             pEnemy->GetRot(),
                                             pEnemy->GetNumber(),
                                             DETAILSCHANGE_CHANGE_LAST_ROT,
                                             true,
                                             pEnemy->GetType(),
                                             nCurNum,
                                             CScene::OBJTYPE_ENEMY);
                                }

                                pEnemy->SetRot(m_aBlockSaveDate[nCurNum - NEXT_DATA].rot);
                            }
                            break;

                            // �����̏ꍇ
                        case DETAILSCHANGE_CREATE:
                            pEnemy->Uninit();
                            break;
                    }
                }
            }
        }

		// �u1���ɕύX���e���o�^����Ă���ꍇ�v���A
		// �u1���ɕύX���e���K�p����Ă��Ȃ���Ԃ̏ꍇ�v���́A�u1���̕ύX���e���S�����ȊO�̏ꍇ�v���A
		// �u1���ɕύX���e���K�p����Ă���ꍇ�v
		if (m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange != DETAILSCHANGE_NULL && m_aBlockSaveDate[nCurNum - NEXT_DATA].bChangeJudge == false || m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange == DETAILSCHANGE_TOTALELIMINATION && m_aBlockSaveDate[nCurNum - NEXT_DATA].bChangeJudge == true) {
			// �ύX���e���S�����ȊO�̏ꍇ
			if (m_aBlockSaveDate[nCurNum - NEXT_DATA].DetailsChange != DETAILSCHANGE_TOTALELIMINATION) {
				if (bCheckData == false) {
					// �ύX���e���K�p���ꂽ��Ԃɂ���
					m_aBlockSaveDate[nCurNum - NEXT_DATA].bChangeJudge = true;
					// �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���-1����
					nCurNum--;
				}
				if (bCheckData == true) {
					// �ύX���e���K�p���ꂽ��Ԃɂ���
					m_aBlockSaveDate[nCurNum - NEXT_DATA].bChangeJudge = true;
					m_aBlockSaveDate[nCurNum - NEXT_TIME_DATA].bChangeJudge = true;
					// �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���-1����
					nCurNum -= NEXT_TIME_DATA;
				}
			}
			// �ύX���e���S�����̏ꍇ
			else {
				// �S�������������z����m�F����
				for (int nCount = 1; nCount <= m_nAllDeleteNum; nCount++) {
					// �ύX���e���K�p���ꂽ��Ԃɂ���
					m_aBlockSaveDate[nCurNum - nCount].bChangeJudge = true;
					// �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���S�����̃I�u�W�F�N�g�������Z����
					nCurNum--;
				}
			}
		}
    }

    // �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���Ԃ�
    return nCurNum;
}

//=============================================================================
// �ύX���e�����ɐi�߂�
//=============================================================================
int CCreateStage::RedoUndoOperation(int nCurNum)
{
    // �u���݂̔z���1��낪���݂��Ă���ꍇ�v���A�u���݂̔z���1���̕ύX���K�p����Ă��Ȃ���Ԃ̏ꍇ�v���A�u���݂̔z���1���̕ύX���e���o�^����Ă���ꍇ�v
    if(m_aBlockSaveDate[nCurNum].bChangeJudge == true && m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_NULL) {
        // �擪�̃I�u�W�F�N�g�����擾
        CScene *pScene = CScene::GetTopScene();
        CBlock *pBlock;
        CEnemy *pEnemy;
        bool bSelectBlockJudge = false;    // �ύX���ꂽ�u���b�N�I�u�W�F�N�g�����o�������𔻒�
        bool bSelectEnemyJudge = false;    // �ύX���ꂽ�G�I�u�W�F�N�g�����o�������𔻒�
        bool bCheckData        = false;    // ���肵���I�u�W�F�N�g�ƕύX���e�̏�񂪑S�Ĉ�v���Ă��邩�𔻒�
        // �u�ύX���e�������ȊO�̏ꍇ�v���A�u�ύX���e���S�����ȊO�̏ꍇ�v
        if(m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_CREATE && m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_TOTALELIMINATION) {
            // �ύX���K�p���ꂽ�I�u�W�F�N�g��{������
            for(int nCntScene = 0; nCntScene < CScene::GetNumAll(); nCntScene++) {
                // ���g������Ȃ�
                if(pScene != NULL) {
                    // ���̃V�[�����L��
                    CScene *pNextScene = pScene->GetNextScene();

                    // �^�C�v���擾
                    CScene::OBJTYPE objType = pScene->GetObjType();

                    // �u���b�N�Ȃ�A
                    if(objType == CScene::OBJTYPE_BLOCK && m_aBlockSaveDate[nCurNum].ObjectType == CScene::OBJTYPE_BLOCK) {
                        // �u���b�N�ɃL���X�g
                        pBlock = (CBlock *)pScene;

                        // �ԍ����擾
                        int nNumber = pBlock->GetNumber();
                        // ��ނ��擾
                        int nType = pBlock->GetType();
						// ���W�擾
						D3DXVECTOR3 pos = pBlock->GetPos();

                        // �u���b�N�ɃL���X�g�����I�u�W�F�N�g�ƕύX���ꂽ�I�u�W�F�N�g�̔ԍ�����v����ꍇ
                        if(nNumber == m_aBlockSaveDate[nCurNum].nNumber && nType == m_aBlockSaveDate[nCurNum].nType ||
							nType == m_aBlockSaveDate[nCurNum].nType && pos == m_aBlockSaveDate[nCurNum].pos) {
                            // ����o������ԂɕύX
                            bSelectBlockJudge = true;
                            break;
                        }
                    }

                    // �G�Ȃ�A
                    if(objType == CScene::OBJTYPE_ENEMY && m_aBlockSaveDate[nCurNum].ObjectType == CScene::OBJTYPE_ENEMY) {
                        // �G�ɃL���X�g
                        pEnemy = (CEnemy *)pScene;

                        // �ԍ����擾
                        int nNumber = pEnemy->GetNumber();
                        // ��ނ��擾
                        int nType = pEnemy->GetType();
						// ���W�擾
						D3DXVECTOR3 pos = pEnemy->GetPos();

                        // �G�ɃL���X�g�����I�u�W�F�N�g�ƕύX���ꂽ�I�u�W�F�N�g�̔ԍ�����v����ꍇ
                        if(nNumber == m_aBlockSaveDate[nCurNum].nNumber && nType == m_aBlockSaveDate[nCurNum].nType ||
							nType == m_aBlockSaveDate[nCurNum].nType && pos == m_aBlockSaveDate[nCurNum].pos) {
                            // ����o������ԂɕύX
                            bSelectEnemyJudge = true;
                            break;
                        }
                    }

                    // ���̃V�[���ɂ���
                    pScene = pNextScene;
                }
                else {
                    // ���g���Ȃ��Ȃ�A�����ŏ������I����
                    break;
                }
            }
        }

		// �I�u�W�F�N�g�^�C�v���u���b�N�̏ꍇ
        if(m_aBlockSaveDate[nCurNum].ObjectType == CScene::OBJTYPE_BLOCK) {
            // �u�ύX���K�p���ꂽ�u���b�N�����o�����ꍇ�v���́A�u�ύX���e�������̏ꍇ�v���́A�u�ύX���e���S�����̏ꍇ�v
            if(bSelectBlockJudge == true || m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_CREATE || m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                // �ύX���e�������̏ꍇ
                if(m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_CREATE) {
                    CBlock::Create(m_aBlockSaveDate[nCurNum].pos,
                                   m_aBlockSaveDate[nCurNum].rot,
                                   m_aBlockSaveDate[nCurNum].nType);
                }
                // �ύX���e���S�����̏ꍇ
                else if(m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                    m_bUseAllDelete = true;
                }
                // �u�ύX���K�p���ꂽ�u���b�N�����o�����ꍇ�v���A�u�I�u�W�F�N�g�����擾�o���Ă���ꍇ�v
                else if(bSelectBlockJudge == true && pBlock != NULL) {
                    // �ύX���e�ɂ���ď�����ς���
                    switch(m_aBlockSaveDate[nCurNum].DetailsChange) {
                            // ���W�ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_POS:
                        case DETAILSCHANGE_CHANGE_POS:
                            if(pBlock->GetPos() == m_aBlockSaveDate[nCurNum].pos && pBlock->GetRot() == m_aBlockSaveDate[nCurNum].rot && pBlock->GetType() == m_aBlockSaveDate[nCurNum].nType && pBlock->GetNumber() == m_aBlockSaveDate[nCurNum].nNumber && m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_NULL) {

                                bCheckData = true;
                                pBlock->SetPos(m_aBlockSaveDate[nCurNum + NEXT_DATA].pos);
                            }
                            else {
                                pBlock->SetPos(m_aBlockSaveDate[nCurNum].pos);
                            }
                            break;

                            // �����ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_ROT:
                        case DETAILSCHANGE_CHANGE_ROT:
                            if(pBlock->GetPos() == m_aBlockSaveDate[nCurNum].pos && pBlock->GetRot() == m_aBlockSaveDate[nCurNum].rot && pBlock->GetType() == m_aBlockSaveDate[nCurNum].nType && pBlock->GetNumber() == m_aBlockSaveDate[nCurNum].nNumber && m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_NULL) {

                                bCheckData = true;
                                pBlock->SetRot(m_aBlockSaveDate[nCurNum + NEXT_DATA].rot);
                            }
                            else {
                                pBlock->SetRot(m_aBlockSaveDate[nCurNum].rot);
                            }
                            break;

                            // �����̏ꍇ
                        case DETAILSCHANGE_BREAK:
                            pBlock->Uninit();
                            break;
                    }
                }
            }
        }

		// �I�u�W�F�N�g�^�C�v���G�̏ꍇ
        else if(m_aBlockSaveDate[nCurNum].ObjectType == CScene::OBJTYPE_ENEMY) {
            // �u�ύX���K�p���ꂽ�G�����o�����ꍇ�v���́A�u�ύX���e�������̏ꍇ�v���́A�u�ύX���e���S�����̏ꍇ�v
            if(bSelectEnemyJudge == true || m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_CREATE || m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                // �ύX���e�������̏ꍇ
                if(m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_CREATE) {
                    CEnemy::Create(m_aBlockSaveDate[nCurNum].pos,
                                   m_aBlockSaveDate[nCurNum].rot,
                                   m_aBlockSaveDate[nCurNum].nType);
                }
                // �ύX���e���S�����̏ꍇ
                else if(m_aBlockSaveDate[nCurNum].DetailsChange == DETAILSCHANGE_TOTALELIMINATION) {
                    m_bUseAllDelete = true;
                }
                // �u�ύX���K�p���ꂽ�u���b�N�����o�����ꍇ�v���A�u�I�u�W�F�N�g�����擾�o���Ă���ꍇ�v
                else if(bSelectEnemyJudge == true && pEnemy != NULL) {
                    // �ύX���e�ɂ���ď�����ς���
                    switch(m_aBlockSaveDate[nCurNum].DetailsChange) {
                            // ���W�ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_POS:
                        case DETAILSCHANGE_CHANGE_POS:
                            if(pEnemy->GetPos() == m_aBlockSaveDate[nCurNum].pos && pEnemy->GetRot() == m_aBlockSaveDate[nCurNum].rot && pEnemy->GetType() == m_aBlockSaveDate[nCurNum].nType && pEnemy->GetNumber() == m_aBlockSaveDate[nCurNum].nNumber && m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_NULL) {

                                bCheckData = true;
                                pEnemy->SetPos(m_aBlockSaveDate[nCurNum + NEXT_DATA].pos);
                            }
                            else {
                                pEnemy->SetPos(m_aBlockSaveDate[nCurNum].pos);
                            }
                            break;

                            // �����ύX�̏ꍇ
                        case DETAILSCHANGE_CHANGE_LAST_ROT:
                        case DETAILSCHANGE_CHANGE_ROT:
                            if(pEnemy->GetPos() == m_aBlockSaveDate[nCurNum].pos && pEnemy->GetRot() == m_aBlockSaveDate[nCurNum].rot && pEnemy->GetType() == m_aBlockSaveDate[nCurNum].nType && pEnemy->GetNumber() == m_aBlockSaveDate[nCurNum].nNumber && m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_NULL) {

                                bCheckData = true;
                                pEnemy->SetRot(m_aBlockSaveDate[nCurNum + NEXT_DATA].pos);
                            }
                            else {
                                pEnemy->SetRot(m_aBlockSaveDate[nCurNum].rot);
                            }
                            break;

                            // �����̏ꍇ
                        case DETAILSCHANGE_BREAK:
                            pEnemy->Uninit();
                            break;
                    }
                }
            }
        }

		// �u�ύX���e���o�^����Ă���ꍇ�v���A�u�ύX���e���K�p����Ă����Ԃ̏ꍇ�v
		if (m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_NULL && m_aBlockSaveDate[nCurNum].bChangeJudge == true) {
			// �ύX���e���S�����ȊO�̏ꍇ
			if (m_aBlockSaveDate[nCurNum].DetailsChange != DETAILSCHANGE_TOTALELIMINATION) {
				if (bCheckData == false) {
					// �ύX���e���K�p����Ă��Ȃ���Ԃɂ���
					m_aBlockSaveDate[nCurNum].bChangeJudge = false;
					// �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���+1����
					nCurNum++;
				}
				if (bCheckData == true) {
					// �ύX���e���K�p����Ă��Ȃ���Ԃɂ���
					m_aBlockSaveDate[nCurNum].bChangeJudge = false;
					m_aBlockSaveDate[nCurNum + NEXT_DATA].bChangeJudge = false;
					// �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���+1����
					nCurNum += NEXT_TIME_DATA;
				}
			}
			// �ύX���e���S�����̏ꍇ
			else {
				// �S�������������z����m�F����
				for (int nCount = 0; nCount < m_nAllDeleteNum; nCount++) {
					// �ύX���e���K�p����Ă��Ȃ���Ԃɂ���
					m_aBlockSaveDate[nCurNum + nCount].bChangeJudge = false;
					// �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���S�����̃I�u�W�F�N�g�������Z����
					nCurNum++;
				}
			}
		}
    }

    // �ύX����ۑ�����ϐ��̔z����Ǘ�����ϐ���Ԃ�
    return nCurNum;
}

//=============================================================================
// �z��̈ړ]
//=============================================================================
int CCreateStage::ShiftArray(int nCount)
{
    if(nCount >= BLOCK_SAVE_MAX_NUM) {
        for(int nCount = 1; nCount < BLOCK_SAVE_MAX_NUM; nCount++) {
            // �z��̑O�̏��ɔz��̌��݂̏���������
            m_aBlockSaveDate[nCount - NEXT_DATA].pos           = m_aBlockSaveDate[nCount].pos;
            m_aBlockSaveDate[nCount - NEXT_DATA].rot           = m_aBlockSaveDate[nCount].rot;
            m_aBlockSaveDate[nCount - NEXT_DATA].nType         = m_aBlockSaveDate[nCount].nType;
            m_aBlockSaveDate[nCount - NEXT_DATA].bChangeJudge  = m_aBlockSaveDate[nCount].bChangeJudge;
            m_aBlockSaveDate[nCount - NEXT_DATA].DetailsChange = m_aBlockSaveDate[nCount].DetailsChange;
            m_aBlockSaveDate[nCount - NEXT_DATA].nNumber       = m_aBlockSaveDate[nCount].nNumber;
            m_aBlockSaveDate[nCount - NEXT_DATA].ObjectType    = m_aBlockSaveDate[nCount].ObjectType;
        }

        // �Ō�̏�������
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].pos           = D3DXVECTOR3(0, 0, 0);
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].rot           = D3DXVECTOR3(0, 0, 0);
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].nType         = -1;
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].bChangeJudge  = false;
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].DetailsChange = DETAILSCHANGE_NULL;
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].nNumber       = -1;
        m_aBlockSaveDate[BLOCK_SAVE_MAX_NUM - NEXT_DATA].ObjectType    = CScene::OBJTYPE_NONE;

        return BLOCK_SAVE_MAX_NUM - NEXT_DATA;
    }

    return nCount;
}

//=============================================================================
// �ύX���e��S�ĕۑ�
//=============================================================================
void CCreateStage::SaveData(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumber, DETAILSCHANGE DetailsChange, bool bChangeJudge, int nType, int nCount, CScene::OBJTYPE ObjectType)
{
    // �����̔z����ɕύX���e���ۑ�����Ă���ꍇ�A�����̔z�����S�ď���������
    if(m_aBlockSaveDate[nCount + NEXT_DATA].DetailsChange != DETAILSCHANGE_NULL) {
        InitArray(nCount + NEXT_DATA);
    }

    // �ύX���e��ۑ�
    m_aBlockSaveDate[nCount].nType         = nType;
    m_aBlockSaveDate[nCount].bChangeJudge  = bChangeJudge;
    m_aBlockSaveDate[nCount].DetailsChange = DetailsChange;
    m_aBlockSaveDate[nCount].nNumber       = nNumber;
    m_aBlockSaveDate[nCount].ObjectType    = ObjectType;

    // ���W�ύX�̏ꍇ
    if(DetailsChange == DETAILSCHANGE_CHANGE_POS || DetailsChange == DETAILSCHANGE_CHANGE_LAST_POS) {
        m_aBlockSaveDate[nCount].pos = pos;
    }
    // �����ύX�̏ꍇ
    if(DetailsChange == DETAILSCHANGE_CHANGE_ROT || DetailsChange == DETAILSCHANGE_CHANGE_LAST_ROT) {
        m_aBlockSaveDate[nCount].rot = rot;
    }
    // �S�����̏ꍇ
    if(DetailsChange == DETAILSCHANGE_TOTALELIMINATION || DetailsChange == DETAILSCHANGE_CREATE || DetailsChange == DETAILSCHANGE_BREAK) {
        m_aBlockSaveDate[nCount].pos = pos;
        m_aBlockSaveDate[nCount].rot = rot;
    }
}

//=============================================================================
// �R�s�[�p�ϐ��ɃR�s�[���e��ۑ�
//=============================================================================
void CCreateStage::SetCopyData(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
    m_CopyPos   = pos;
    m_CopyRot   = rot;
    m_nCopyType = nType;
}

//=============================================================================
// �R�s�[�p�ϐ���������
//=============================================================================
void CCreateStage::InitCopyDate(void)
{
    m_CopyPos   = D3DXVECTOR3(0, 0, 0);
    m_CopyRot   = D3DXVECTOR3(0, 0, 0);
    m_nCopyType = -1;
}

//=============================================================================
// �z���������
//=============================================================================
void CCreateStage::InitArray(int nCount)
{
    for(int nCOunt = nCount; nCOunt < BLOCK_SAVE_MAX_NUM; nCOunt++) {
        m_aBlockSaveDate[nCOunt].pos           = D3DXVECTOR3(0, 0, 0);
        m_aBlockSaveDate[nCOunt].rot           = D3DXVECTOR3(0, 0, 0);
        m_aBlockSaveDate[nCOunt].nType         = -1;
        m_aBlockSaveDate[nCOunt].bChangeJudge  = false;
        m_aBlockSaveDate[nCOunt].DetailsChange = DETAILSCHANGE_NULL;
        m_aBlockSaveDate[nCOunt].nNumber       = -1;
        m_aBlockSaveDate[nCOunt].ObjectType    = CScene::OBJTYPE_NONE;
    }
}

//=============================================================================
// control + Z�Œǉ����ꂽ��񐔂𐔂���
//=============================================================================
void CCreateStage::CountDetallsChangeLAST(void)
{
    for(int nCount = 0; nCount < BLOCK_SAVE_MAX_NUM; nCount++) {
        if(m_aBlockSaveDate[nCount].DetailsChange == DETAILSCHANGE_CHANGE_LAST_POS) {
            m_nLastCountPos++;
        }

        if(m_aBlockSaveDate[nCount].DetailsChange == DETAILSCHANGE_CHANGE_LAST_ROT) {
            m_nLastCountRot++;
        }
    }
}

//=============================================================================
// �ǂݍ��ރe�L�X�g�t�@�C�����擾�E�Z�b�g����
//=============================================================================
HRESULT CCreateStage::LoadTextName(void) {
	// �t�@�C���|�C���g
	FILE *pFile = NULL;

	// �ϐ��錾
	int nCntLoad = 0;
	char cReedText[128];    // �����Ƃ��ēǂݎ��p
	char cHeadText[256];    //
	char cDie[128];

	// �t�@�C���J
	pFile = fopen("data/TXT/LoadTextName.txt", "r");

	// �J����
	if (pFile != NULL) {
		while (strcmp(cHeadText, "START") != 0) {
			fgets(cReedText, sizeof(cReedText), pFile);
			sscanf(cReedText, "%s", &cHeadText);
		}

		if (strcmp(cHeadText, "START") == 0) {
			while (strcmp(cHeadText, "END") != 0) {
				fgets(cReedText, sizeof(cReedText), pFile);
				sscanf(cReedText, "%s", &cHeadText);

				if (strcmp(cHeadText, "\n") == 0) {
				}
				else if (strcmp(cHeadText, "END") != 0) {
					if (strcmp(cHeadText, "Block") == 0) {
						sscanf(cReedText, "%s %s %s", &cDie, &cDie, &m_cTxtName[0][0]);
					}

					if (strcmp(cHeadText, "Enemy") == 0) {
						sscanf(cReedText, "%s %s %s", &cDie, &cDie, &m_cTxtName[1][0]);
					}

					if (strcmp(cHeadText, "Map") == 0) {
						sscanf(cReedText, "%s %s %s", &cDie, &cDie, &m_cTxtName[2][0]);

						nCntLoad++;
					}
				}
			}
		}
		// �t�@�C����
		fclose(pFile);

		return S_OK;
	}

	// �J���Ȃ�
	else {
		printf("�J����܂���ł���\n");
	}

	return E_FAIL;
}

//=============================================================================
// �I�������I�u�W�F�N�g�^�C�v���g�p�o���邩�𔻒�
//=============================================================================
void CCreateStage::SetObjectType(int nType) {
	if (m_CreateType == CREATEOBJECT_STAGE && CBlock::GetBlockData(nType).bUseJudge == true) {
		m_nBlockType = nType;
	}
	else if (m_CreateType == CREATEOBJECT_ENEMY && CEnemy::GetEnemyData(nType).bUseJudge == true) {
		m_nEnemyType = nType;
	}
}
