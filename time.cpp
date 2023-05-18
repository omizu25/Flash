//**************************************************
// 
// time.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "time.h"
#include "application.h"
#include "mode.h"
#include "fade.h"

//==================================================
// ��`
//==================================================
namespace
{
const int ONE_SECOND = 60;		// ��b
const int MAX_TEXT = 1024;		// �����̍ő吔
const int ERROR_NUMBER = -1;	// �G���[�̐���
const string FILE_PATH = "data/TEXT/Game.txt";	// �t�@�C���p�X
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CTime* CTime::Create()
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pTime->Init();

	// �ǂݍ���
	pTime->Load();

	return pTime;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTime::CTime() :
	m_time(0),
	m_switch(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTime::Init()
{
	m_time = 0;
	m_switch = ERROR_NUMBER;

	// ������
	CNumberManager::Init();

	D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(((float)CApplication::SCREEN_WIDTH * 0.5f) + (size.x * 0.5f), size.y * 0.65f, 0.0f);

	// �ʒu�̐ݒ�
	CNumberManager::SetPos(pos);

	// �T�C�Y�̐ݒ�
	CNumberManager::SetSize(size);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTime::Uninit()
{
	// �I��
	CNumberManager::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTime::Update()
{
	m_time++;

	if (m_time % ONE_SECOND == 0)
	{// ��b�Ԋu
		CNumberManager::Add(-1);
	}

	if (CNumberManager::Get() == 0)
	{// ���Ԃ�����
		CNumberManager::Set(m_switch);
	}

	// �X�V
	CNumberManager::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTime::Draw()
{
	// �`��
	CNumberManager::Draw();
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTime::Load()
{
	// �t�@�C�����J��
	FILE* pFile = fopen(FILE_PATH.c_str(), "r");

	// �E�C���h�E���̎擾
	HWND hWnd = CApplication::GetInstance()->GetWnd();
	
	if (pFile == nullptr)
	{// null�`�F�b�N
		assert(false);
		MessageBox(hWnd, "�e�L�X�g���J���Ȃ���", "�x���I", MB_ICONWARNING);
		return;
	}

	char read[MAX_TEXT] = {};

	while (fscanf(pFile, "%s", read) != EOF)
	{// �t�@�C���̍Ōオ����܂ŌJ��Ԃ�
		if (strcmp(read, "#") == 0)
		{// ���o��
			fgets(read, MAX_TEXT, pFile);
			continue;
		}
		else if (strncmp(read, "#", 1) == 0)
		{// �g��
			continue;
		}

		if (strcmp(read, "SWITCH_SECONDS") == 0)
		{// �ǂݍ���
			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%d", &m_switch);
		}
	}

	// �t�@�C�������
	fclose(pFile);

	if (m_switch == ERROR_NUMBER)
	{// �ǂݍ��݂��o���Ă��Ȃ�
		MessageBox(hWnd, "�؂�ւ��b�����ǂݍ��߂܂���", "�x���I", MB_ICONWARNING);

		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_TITLE);
		return;
	}

	// �ݒ�
	CNumberManager::Set(m_switch);
}
