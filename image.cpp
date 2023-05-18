//**************************************************
// 
// image.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "image.h"
#include "application.h"
#include "mode.h"
#include "fade.h"
#include "game.h"
#include "utility.h"

//==================================================
// ��`
//==================================================
namespace
{
const int MAX_TEXT = 1024;		// �����̍ő吔
const int ERROR_NUMBER = -1;	// �G���[�̐���
const string TEXT_PATH = "data/TEXT/Game.txt";		// �e�L�X�g�̃t�@�C���p�X
const string TEXTURE_PATH = "data/TEXTURE/Game/";	// �e�N�X�`���̃t�@�C���p�X
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
string* CImage::m_pPath = nullptr;		// �e�N�X�`���̃p�X
int* CImage::m_pUsed = nullptr;			// �g�p��������
int CImage::m_switchMax = ERROR_NUMBER;	// �؂�ւ��ő吔
int CImage::m_num = ERROR_NUMBER;		// �e�N�X�`���̐�

//--------------------------------------------------
// ����
//--------------------------------------------------
CImage* CImage::Create()
{
	CImage* pImage = nullptr;

	pImage = new CImage;

	if (pImage == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pImage->Init();

	// �؂�ւ�
	pImage->Switch();

	return pImage;
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CImage::Load()
{
	// �t�@�C�����J��
	FILE* pFile = fopen(TEXT_PATH.c_str(), "r");

	// �E�C���h�E���̎擾
	HWND hWnd = CApplication::GetInstance()->GetWnd();

	if (pFile == nullptr)
	{// null�`�F�b�N
		assert(false);
		MessageBox(hWnd, "�e�L�X�g���J���Ȃ���", "�x���I", MB_ICONWARNING);
		return;
	}

	char read[MAX_TEXT] = {};
	int num = 0;

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

		if (strcmp(read, "SWITCH_NUMBER") == 0)
		{// �ǂݍ���
			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%d", &m_switchMax);

			if (m_switchMax <= 0)
			{// �؂�ւ��Ȃ�
				break;
			}
		}
		else if (strcmp(read, "NUM_TEXTURE") == 0)
		{// �ǂݍ���
			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%d", &m_num);

			if (m_num <= 0)
			{// �e�N�X�`���Ȃ�
				break;
			}

			{// �g�p����
				m_pUsed = new int[m_num];

				if (m_pUsed == nullptr)
				{// null�`�F�b�N
					assert(false);
				}

				for (int i = 0; i < m_num; i++)
				{
					m_pUsed[i] = -1;
				}
			}

			{// �e�N�X�`���̃p�X
				m_pPath = new string[m_num];

				if (m_pPath == nullptr)
				{// null�`�F�b�N
					assert(false);
				}
			}
		}
		else if (strcmp(read, "TEXTURE_NAME") == 0)
		{// �ǂݍ���
			if (m_pPath == nullptr)
			{// �ǂݍ��݂��o���Ă��Ȃ�
				break;
			}

			if (num > m_num)
			{// �e�N�X�`���̐�������
				break;
			}

			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%s", &read);

			m_pPath[num] = read;

			num++;
		}
	}

	// �t�@�C�������
	fclose(pFile);

	bool error = false;
	string str;

	if (m_switchMax == ERROR_NUMBER || m_switchMax <= 0)
	{// �ǂݍ��݂��o���Ă��Ȃ�
		error = true;
		str = "�؂�ւ�鐔���������ǂݍ��߂܂���";
	}
	else if (m_num == ERROR_NUMBER || m_num <= 0)
	{// �ǂݍ��݂��o���Ă��Ȃ�
		error = true;
		str = "�e�N�X�`�������������ǂݍ��߂܂���";
	}
	else if (num > m_num)
	{// �e�N�X�`���̐�������
		error = true;
		str = "�e�N�X�`�������e�N�X�`����������";
	}
	else if (m_pPath == nullptr)
	{// �ǂݍ��݂��o���Ă��Ȃ�
		error = true;
		str = "�e�N�X�`�������������ǂݍ��߂܂���";
	}

	if (error)
	{
		// �G���[���b�Z�[�W
		MessageBox(hWnd, str.c_str(), "�x���I", MB_ICONWARNING);

		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_TITLE);
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CImage::Release()
{
	if (m_pPath != nullptr)
	{// null�`�F�b�N
		delete[] m_pPath;
		m_pPath = nullptr;
	}

	if (m_pUsed != nullptr)
	{// null�`�F�b�N
		delete[] m_pUsed;
		m_pUsed = nullptr;
	}
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CImage::CImage() :
	m_pTexture(nullptr),
	m_switch(0),
	m_index(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CImage::~CImage()
{
	assert(m_pTexture == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CImage::Init()
{
	m_pTexture = nullptr;
	m_switch = 0;
	m_index = -1;

	for (int i = 0; i < m_num; i++)
	{
		m_pUsed[i] = -1;
	}

	// ������
	CObject2D::Init();

	D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.6f, 0.0f);

	// �ʒu�̐ݒ�
	CObject2D::SetPos(pos);

	D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.75f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);

	// �T�C�Y�̐ݒ�
	CObject2D::SetSize(size);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CImage::Uninit()
{
	if (m_pTexture != nullptr)
	{// �e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// �I��
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CImage::Update()
{
	// �X�V
	CObject2D::Update();

	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	
	if (!pGame->Switch())
	{// �؂�ւ���Ă��Ȃ�
		return;
	}

	if (m_switch >= m_switchMax || m_switch >= m_num)
	{// �؂�ւ��I�����
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_TITLE);

		return;
	}
	
	// �؂�ւ�
	Switch();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CImage::Draw()
{
	// �`��
	CObject2D::Draw();
}

//--------------------------------------------------
// �؂�ւ�
//--------------------------------------------------
void CImage::Switch()
{
	if (m_pTexture != nullptr)
	{// �e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// �����_��
	Random();

	if (m_pTexture == nullptr)
	{// �ǂݍ��݂���Ă��Ȃ�
		string path = TEXTURE_PATH + m_pPath[m_index];

		// �f�o�C�X�ւ̃|�C���^�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			path.c_str(),
			&m_pTexture);
	}

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(m_pTexture);

	m_switch++;
}

//--------------------------------------------------
// �����_��
//--------------------------------------------------
void CImage::Random()
{
	while (true)
	{
		// �����_��
		m_index = IntRandom(m_num - 1, 0);
		assert(m_index >= 0 && m_index < m_num);

		bool same = false;

		for (int i = 0; i < m_switch; i++)
		{
			if (m_index == m_pUsed[i])
			{// �g�p���������Ɠ���
				same = true;
				break;
			}
		}

		if (!same)
		{// �V����������������
			m_pUsed[m_switch] = m_index;

			break;
		}
	}
}
