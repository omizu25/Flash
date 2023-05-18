//**************************************************
// 
// number_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "number_manager.h"
#include "number.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CNumberManager* CNumberManager::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int value)
{
	CNumberManager* pNumberManager = nullptr;

	pNumberManager = new CNumberManager;

	if (pNumberManager != nullptr)
	{// nullチェック
		float halfWidth = size.x * 0.5f;

		float posX = 0.0f;

		for (int i = 0; i < MAX_DIGIT; i++)
		{
			posX = pos.x - (halfWidth + (size.x * i));

			// 生成
			pNumberManager->m_pNumber[i] = CNumber::Create(D3DXVECTOR3(posX, pos.y, 0.0f), size);
		}

		// 初期化
		pNumberManager->Init();

		// 数の設定
		pNumberManager->Set(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CNumberManager::CNumberManager() : CObject(CObject::PRIORITY_SYSTEM),
	m_value(0),
	m_zeroDigit(0),
	m_interval(0),
	m_width(0.0f),
	m_zero(false)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_pNumber[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CNumberManager::~CNumberManager()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		assert(m_pNumber[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CNumberManager::Init()
{
	m_value = 0;
	m_interval = 0;
	m_width = 0.0f;
	m_zero = false;
	m_zeroDigit = MAX_DIGIT;

	// 変更
	Change();

	// ゼロの描画
	ZeroDraw();

	// 数の設定
	Set(0);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CNumberManager::Uninit()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_pNumber[i] != nullptr)
		{// nullチェック
			// 終了
			m_pNumber[i]->Uninit();
			m_pNumber[i] = nullptr;
		}
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CNumberManager::Update()
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CNumberManager::Draw()
{
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CNumberManager::Add(int value)
{
	m_value += value;

	if (m_value >= INT_MAX)
	{// 最大数以上
		m_value = INT_MAX;
	}
	else if (m_value <= 0)
	{// マイナス
		m_value = 0;
	}
	else if(MAX_DIGIT < Digit(m_value))
	{// 桁数が最大値を越している
		m_value -= value;
		assert(false);
	}

	// 変更
	Change();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CNumberManager::Set(int value)
{
	if (MAX_DIGIT < Digit(value))
	{// 桁数が最大値を越している
		assert(false);
		return;
	}

	m_value = value;

	if (m_value >= INT_MAX)
	{// 最大数以上
		m_value = INT_MAX;
	}
	else if (m_value <= 0)
	{// マイナス
		m_value = 0;
	}

	// 変更
	Change();
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CNumberManager::Get()
{
	return m_value;
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CNumberManager::SetPos(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = m_pNumber[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// 位置の設定
		m_pNumber[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void CNumberManager::SetCol(const D3DXCOLOR& col)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 色の設定
		m_pNumber[i]->SetCol(col);
	}
}

//--------------------------------------------------
// 描画の設定
//--------------------------------------------------
void CNumberManager::SetDraw(bool draw)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 描画の設定
		m_pNumber[i]->SetDraw(draw);
	}
}

//--------------------------------------------------
// ゼロの設定
//--------------------------------------------------
void CNumberManager::SetZero(bool zero)
{
	m_zero = zero;

	// ゼロの描画
	ZeroDraw();
}

//--------------------------------------------------
// ゼロの桁数の設定
//--------------------------------------------------
void CNumberManager::SetZeroDigit(int digit)
{
	m_zeroDigit = digit;

	// ゼロの描画
	ZeroDraw();
}

//--------------------------------------------------
// 間隔の設定
//--------------------------------------------------
void CNumberManager::SetInterval(int interval, float width)
{
	m_interval = interval;
	m_width = width;

	if (m_interval == 0)
	{// 間隔はいらない
		m_interval = 1;
		m_width = 0.0f;
	}

	D3DXVECTOR3 size = m_pNumber[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	D3DXVECTOR3 pos = m_pNumber[0]->GetPos();
	pos.x += halfWidth;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// 位置の設定
		m_pNumber[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// 描画の設定
//--------------------------------------------------
void CNumberManager::ZeroDraw()
{
	if (m_zero)
	{// ゼロを描画する
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_pNumber[i]->SetDraw(false);
		}

		for (int i = 0; i < m_zeroDigit; i++)
		{
			m_pNumber[i]->SetDraw(true);
		}
	}
	else
	{// ゼロを描画しない
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_pNumber[i]->SetDraw(false);
		}

		for (int i = 0; i < Digit(m_value); i++)
		{
			m_pNumber[i]->SetDraw(true);
		}
	}

	// 1桁目は絶対に描画する
	m_pNumber[0]->SetDraw(true);
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CNumberManager::Change()
{
	int num[MAX_DIGIT];

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		num[i] = 0;
	}

	int saveValue = m_value;

	for (int i = 0; i < Digit(m_value); i++)
	{// 一桁ずつに分ける
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 数の変更
		m_pNumber[i]->Change(num[i]);
	}

	// ゼロの描画
	ZeroDraw();
}
