//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "texture.h"
#include "application.h"

//==================================================
// ��`
//==================================================
namespace
{
const string FILE_PATH = "data/TEXTURE/System/";	// �t�@�C���p�X
const string TEXTURE_NAME[] =
{// �e�N�X�`���̖��O
	"Number.png",		// ����
	"Cursor.png",		// �J�[�\��
	"PressEnter.png",	// �v���X�G���^�[
};
}

static_assert(sizeof(TEXTURE_NAME) / sizeof(TEXTURE_NAME[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture()
{
	memset(m_pTexture, 0, sizeof(m_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �ǂݍ���
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	string path = FILE_PATH + TEXTURE_NAME[label];

	D3DXCreateTextureFromFile(pDevice,
		path.c_str(),
		&m_pTexture[label]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �j��
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// �e�N�X�`���̉��
		m_pTexture[label]->Release();
		m_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// �ǂݍ���
	Load(label);

	return m_pTexture[label];
}
