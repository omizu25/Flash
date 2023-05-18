//**************************************************
// 
// time.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "time.h"
#include "application.h"
#include "mode.h"
#include "fade.h"

//==================================================
// 定義
//==================================================
namespace
{
const int ONE_SECOND = 60;		// 一秒
const int MAX_TEXT = 1024;		// 文字の最大数
const int ERROR_NUMBER = -1;	// エラーの数字
const string FILE_PATH = "data/TEXT/Game.txt";	// ファイルパス
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTime* CTime::Create()
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pTime->Init();

	// 読み込み
	pTime->Load();

	return pTime;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTime::CTime() :
	m_time(0),
	m_switch(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTime::Init()
{
	m_time = 0;
	m_switch = ERROR_NUMBER;

	// 初期化
	CNumberManager::Init();

	D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(((float)CApplication::SCREEN_WIDTH * 0.5f) + (size.x * 0.5f), size.y * 0.65f, 0.0f);

	// 位置の設定
	CNumberManager::SetPos(pos);

	// サイズの設定
	CNumberManager::SetSize(size);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTime::Uninit()
{
	// 終了
	CNumberManager::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTime::Update()
{
	m_time++;

	if (m_time % ONE_SECOND == 0)
	{// 一秒間隔
		CNumberManager::Add(-1);
	}

	if (CNumberManager::Get() == 0)
	{// 時間が来た
		CNumberManager::Set(m_switch);
	}

	// 更新
	CNumberManager::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTime::Draw()
{
	// 描画
	CNumberManager::Draw();
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTime::Load()
{
	// ファイルを開く
	FILE* pFile = fopen(FILE_PATH.c_str(), "r");

	// ウインドウ情報の取得
	HWND hWnd = CApplication::GetInstance()->GetWnd();
	
	if (pFile == nullptr)
	{// nullチェック
		assert(false);
		MessageBox(hWnd, "テキストが開けないよ", "警告！", MB_ICONWARNING);
		return;
	}

	char read[MAX_TEXT] = {};

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

		if (strcmp(read, "SWITCH_SECONDS") == 0)
		{// 読み込み
			fscanf(pFile, "%s", &read);
			fscanf(pFile, "%d", &m_switch);
		}
	}

	// ファイルを閉じる
	fclose(pFile);

	if (m_switch == ERROR_NUMBER)
	{// 読み込みが出来ていない
		MessageBox(hWnd, "切り替わる秒数が読み込めません", "警告！", MB_ICONWARNING);

		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_TITLE);
		return;
	}

	// 設定
	CNumberManager::Set(m_switch);
}
