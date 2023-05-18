//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
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
// 定義
//==================================================
namespace
{
const CMode::EMode START_MODE = CMode::MODE_TITLE;	// 最初のモード
}

//==================================================
// 静的メンバ変数
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CApplication* CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{// nullチェック
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pTexture(nullptr),
	m_pMode(nullptr),
	m_pFade(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pFade == nullptr);
	assert(m_pMode == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pRenderer == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	{// レンダラー
		m_pRenderer = new CRenderer;

		// nullチェック
		assert(m_pRenderer != nullptr);

		bool window = true; // ウインドウモードにするかどうか

#ifdef _DEBUG
		window = true;
#else
		window = false;
#endif

		if (FAILED(m_pRenderer->Init(hWnd, window)))
		{// 初期化
			return S_FALSE;
		}
	}

	{// 入力
		CInput::Create();

		if (FAILED(CInput::GetKey()->Init(hInstance, hWnd)))
		{// 初期化
			return E_FAIL;
		}
	}

	{// テクスチャ
		m_pTexture = new CTexture;

		// nullチェック
		assert(m_pTexture != nullptr);
	}

	{// フェード
		m_pFade = CFade::Create();

		// nullチェック
		assert(m_pFade != nullptr);

		// 初期化
		m_pFade->Init();
	}

	// 画像の読み込み
	CImage::Load();

	m_hWnd = hWnd;
	m_mode = START_MODE;

	// モードの設定
	m_pFade->ChangeMode(m_mode);

	// ランダムの初期化
	srand((unsigned int)time(NULL));

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CApplication::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll();

	// 画像の解放
	CImage::Release();

	m_pMode = nullptr;

	if (m_pFade != nullptr)
	{// nullチェック
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	if (m_pTexture != nullptr)
	{// nullチェック
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// 入力処理の終了
	CInput::GetKey()->Uninit();

	if (m_pRenderer != nullptr)
	{// nullチェック
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CApplication::Update()
{
	// 入力処理の更新
	CInput::GetKey()->Update();

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 更新
		m_pRenderer->Update();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// nullチェック
		// 描画処理
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// ウインドウ情報の取得
//--------------------------------------------------
HWND CApplication::GetWnd()
{
	return m_hWnd;
}

//--------------------------------------------------
// モードの設定
//--------------------------------------------------
CMode::EMode CApplication::GetModeEnum()
{
	return m_mode;
}

//--------------------------------------------------
// モードの設定
//--------------------------------------------------
void CApplication::SetMode(CMode::EMode mode)
{
	m_mode = mode;

	// 全ての解放
	CObject::ReleaseAll();

	// モードの生成
	m_pMode = CMode::Create(mode);
}

//--------------------------------------------------
// デバイスの取得
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// レンダラーの取得
//--------------------------------------------------
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//--------------------------------------------------
// テクスチャの取得
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// モードの取得
//--------------------------------------------------
CMode* CApplication::GetMode()
{
	return m_pMode;
}

//--------------------------------------------------
// フェードの取得
//--------------------------------------------------
CFade* CApplication::GetFade()
{
	return m_pFade;
}
