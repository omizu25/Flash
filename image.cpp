//**************************************************
// 
// image.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "image.h"
#include "application.h"
#include "mode.h"
#include "fade.h"
#include "game.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
const int MAX_TEXT = 1024;		// 文字の最大数
const int ERROR_NUMBER = -1;	// エラーの数字
const string TEXT_PATH = "data/TEXT/Game.txt";		// テキストのファイルパス
const string TEXTURE_PATH = "data/TEXTURE/Game/";	// テクスチャのファイルパス
}

//==================================================
// 静的メンバ変数
//==================================================
string* CImage::m_pPath = nullptr;		// テクスチャのパス
int* CImage::m_pUsed = nullptr;			// 使用した数字
int CImage::m_switchMax = ERROR_NUMBER;	// 切り替わる最大数
int CImage::m_num = ERROR_NUMBER;		// テクスチャの数

//--------------------------------------------------
// 生成
//--------------------------------------------------
CImage* CImage::Create()
{
	CImage* pImage = nullptr;

	pImage = new CImage;

	if (pImage == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pImage->Init();

	// 切り替え
	pImage->Switch();

	return pImage;
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CImage::Load()
{
	// ファイルを開く
	FILE* pFile = fopen(TEXT_PATH.c_str(), "r");

	// ウインドウ情報の取得
	HWND hWnd = CApplication::GetInstance()->GetWnd();

	if (pFile == nullptr)
	{// nullチェック
		assert(false);
		MessageBox(hWnd, "テキストが開けないよ", "警告！", MB_ICONWARNING);
		return;
	}

	char read[MAX_TEXT] = {};
	int num = 0;

	while (fscanf(pFile, "%s", read) != EOF)
	{// ファイルの最後が来るまで繰り返す
		if (strcmp(read, "#") == 0)
		{// 見出し
			fgets(read, MAX_TEXT, pFile);
			continue;
		}
		else if (strncmp(read, "#", 1) == 0)
		{// 枠線
			continue;
		}

		if (strcmp(read, "SWITCH_NUMBER") == 0)
		{// 読み込み
			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%d", &m_switchMax);

			if (m_switchMax <= 0)
			{// 切り替えない
				break;
			}
		}
		else if (strcmp(read, "NUM_TEXTURE") == 0)
		{// 読み込み
			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%d", &m_num);

			if (m_num <= 0)
			{// テクスチャなし
				break;
			}

			{// 使用した
				m_pUsed = new int[m_num];

				if (m_pUsed == nullptr)
				{// nullチェック
					assert(false);
				}

				for (int i = 0; i < m_num; i++)
				{
					m_pUsed[i] = -1;
				}
			}

			{// テクスチャのパス
				m_pPath = new string[m_num];

				if (m_pPath == nullptr)
				{// nullチェック
					assert(false);
				}
			}
		}
		else if (strcmp(read, "TEXTURE_NAME") == 0)
		{// 読み込み
			if (m_pPath == nullptr)
			{// 読み込みが出来ていない
				break;
			}

			if (num > m_num)
			{// テクスチャの数が多い
				break;
			}

			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%s", &read);

			m_pPath[num] = read;

			num++;
		}
	}

	// ファイルを閉じる
	fclose(pFile);

	bool error = false;
	string str;

	if (m_switchMax == ERROR_NUMBER || m_switchMax <= 0)
	{// 読み込みが出来ていない
		error = true;
		str = "切り替わる数が正しく読み込めません";
	}
	else if (m_num == ERROR_NUMBER || m_num <= 0)
	{// 読み込みが出来ていない
		error = true;
		str = "テクスチャ数が正しく読み込めません";
	}
	else if (num > m_num)
	{// テクスチャの数が多い
		error = true;
		str = "テクスチャ数よりテクスチャ名が多い";
	}
	else if (m_pPath == nullptr)
	{// 読み込みが出来ていない
		error = true;
		str = "テクスチャ名が正しく読み込めません";
	}

	if (error)
	{
		// エラーメッセージ
		MessageBox(hWnd, str.c_str(), "警告！", MB_ICONWARNING);

		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_TITLE);
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CImage::Release()
{
	if (m_pPath != nullptr)
	{// nullチェック
		delete[] m_pPath;
		m_pPath = nullptr;
	}

	if (m_pUsed != nullptr)
	{// nullチェック
		delete[] m_pUsed;
		m_pUsed = nullptr;
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CImage::CImage() :
	m_pTexture(nullptr),
	m_switch(0),
	m_index(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CImage::~CImage()
{
	assert(m_pTexture == nullptr);
}

//--------------------------------------------------
// 初期化
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

	// 初期化
	CObject2D::Init();

	D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.6f, 0.0f);

	// 位置の設定
	CObject2D::SetPos(pos);

	D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.75f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);

	// サイズの設定
	CObject2D::SetSize(size);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CImage::Uninit()
{
	if (m_pTexture != nullptr)
	{// テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// 終了
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CImage::Update()
{
	// 更新
	CObject2D::Update();

	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	
	if (!pGame->Switch())
	{// 切り替わっていない
		return;
	}

	if (m_switch >= m_switchMax || m_switch >= m_num)
	{// 切り替え終わった
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_TITLE);

		return;
	}
	
	// 切り替え
	Switch();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CImage::Draw()
{
	// 描画
	CObject2D::Draw();
}

//--------------------------------------------------
// 切り替え
//--------------------------------------------------
void CImage::Switch()
{
	if (m_pTexture != nullptr)
	{// テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// ランダム
	Random();

	if (m_pTexture == nullptr)
	{// 読み込みされていない
		string path = TEXTURE_PATH + m_pPath[m_index];

		// デバイスへのポインタの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			path.c_str(),
			&m_pTexture);
	}

	// テクスチャの設定
	CObject2D::SetTexture(m_pTexture);

	m_switch++;
}

//--------------------------------------------------
// ランダム
//--------------------------------------------------
void CImage::Random()
{
	while (true)
	{
		// ランダム
		m_index = IntRandom(m_num - 1, 0);
		assert(m_index >= 0 && m_index < m_num);

		bool same = false;

		for (int i = 0; i < m_switch; i++)
		{
			if (m_index == m_pUsed[i])
			{// 使用した数字と同じ
				same = true;
				break;
			}
		}

		if (!same)
		{// 新しい数字を見つけた
			m_pUsed[m_switch] = m_index;

			break;
		}
	}
}
