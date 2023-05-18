//**************************************************
// 
// image.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _IMAGE_H_	//���̃}�N����`������ĂȂ�������
#define _IMAGE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object2D.h"

//==================================================
// �O���錾
//==================================================

//==================================================
// ��`
//==================================================
class CImage : public CObject2D
{
	/* ����`�� */
public:

	/* ���ÓI�����o�ϐ��� */
private:
	static string* m_pPath;	// �e�N�X�`���̃p�X
	static int* m_pUsed;	// �g�p��������
	static int m_switchMax;	// �؂�ւ��ő吔
	static int m_num;		// �e�N�X�`���̐�

	/* ���ÓI�����o�֐��� */
public:
	static CImage* Create();	// ����
	static void Load();			// �ǂݍ���
	static void Release();		// ���

	/* �������o�֐��� */
public:
	CImage();			// �f�t�H���g�R���X�g���N�^
	~CImage() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Switch();	// �؂�ւ�
	void Random();	// �����_��

	/* �������o�ϐ��� */
private:
	LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̏��
	int m_switch;		// �؂�ւ�����
	int m_index;		// ���݂̔ԍ�
};

#endif // !_IMAGE_H_
