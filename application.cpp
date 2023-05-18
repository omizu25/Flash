//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "object.h"
#include "texture.h"
#include "mode.h"
#include "fade.h"
#include "image.h"

//==================================================
// ��`
//==================================================
namespace
{
const CMode::EMode START_MODE = CMode::MODE_TITLE;	// �ŏ��̃��[�h
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CApplication* CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{// null�`�F�b�N
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pTexture(nullptr),
	m_pMode(nullptr),
	m_pFade(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pFade == nullptr);
	assert(m_pMode == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pRenderer == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	{// �����_���[
		m_pRenderer = new CRenderer;

		// null�`�F�b�N
		assert(m_pRenderer != nullptr);

		bool window = true; // �E�C���h�E���[�h�ɂ��邩�ǂ���

#ifdef _DEBUG
		window = true;
#else
		window = false;
#endif

		if (FAILED(m_pRenderer->Init(hWnd, window)))
		{// ������
			return S_FALSE;
		}
	}

	{// ����
		CInput::Create();

		if (FAILED(CInput::GetKey()->Init(hInstance, hWnd)))
		{// ������
			return E_FAIL;
		}
	}

	{// �e�N�X�`��
		m_pTexture = new CTexture;

		// null�`�F�b�N
		assert(m_pTexture != nullptr);
	}

	{// �t�F�[�h
		m_pFade = CFade::Create();

		// null�`�F�b�N
		assert(m_pFade != nullptr);

		// ������
		m_pFade->Init();
	}

	// �摜�̓ǂݍ���
	CImage::Load();

	m_hWnd = hWnd;
	m_mode = START_MODE;

	// ���[�h�̐ݒ�
	m_pFade->ChangeMode(m_mode);

	// �����_���̏�����
	srand((unsigned int)time(NULL));

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CApplication::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll();

	// �摜�̉��
	CImage::Release();

	m_pMode = nullptr;

	if (m_pFade != nullptr)
	{// null�`�F�b�N
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	if (m_pTexture != nullptr)
	{// null�`�F�b�N
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// ���͏����̏I��
	CInput::GetKey()->Uninit();

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CApplication::Update()
{
	// ���͏����̍X�V
	CInput::GetKey()->Update();

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pRenderer->Update();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// �E�C���h�E���̎擾
//--------------------------------------------------
HWND CApplication::GetWnd()
{
	return m_hWnd;
}

//--------------------------------------------------
// ���[�h�̐ݒ�
//--------------------------------------------------
CMode::EMode CApplication::GetModeEnum()
{
	return m_mode;
}

//--------------------------------------------------
// ���[�h�̐ݒ�
//--------------------------------------------------
void CApplication::SetMode(CMode::EMode mode)
{
	m_mode = mode;

	// �S�Ẳ��
	CObject::ReleaseAll();

	// ���[�h�̐���
	m_pMode = CMode::Create(mode);
}

//--------------------------------------------------
// �f�o�C�X�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// �����_���[�̎擾
//--------------------------------------------------
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//--------------------------------------------------
// �e�N�X�`���̎擾
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// ���[�h�̎擾
//--------------------------------------------------
CMode* CApplication::GetMode()
{
	return m_pMode;
}

//--------------------------------------------------
// �t�F�[�h�̎擾
//--------------------------------------------------
CFade* CApplication::GetFade()
{
	return m_pFade;
}
