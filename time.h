//**************************************************
// 
// time.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TIME_H_	//���̃}�N����`������ĂȂ�������
#define _TIME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "number_manager.h"

//==================================================
// �O���錾
//==================================================

//==================================================
// ��`
//==================================================
class CTime : public CNumberManager
{
	/* ����`�� */
public:

	/* ���ÓI�����o�֐��� */
public:
	static CTime* Create();	// ����

	/* �������o�֐��� */
public:
	CTime();			// �f�t�H���g�R���X�g���N�^
	~CTime() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Load();	// �ǂݍ���

	/* �������o�ϐ��� */
private:
	int m_time;		// ����
	int m_switch;	// �؂�ւ��b��
};

#endif // !_TIME_H_
