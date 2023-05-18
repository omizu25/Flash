//**************************************************
// 
// menu.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "menu.h"
#include "object2D.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "fade.h"

//==================================================
// 定義
//==================================================
namespace
{
const float CHANGE_SPEED = 0.02f;	// α値の変更速度
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMenu* CMenu::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval)
{
	CMenu* pMenu = new CMenu;

	if (pMenu == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pMenu->Init();

	// 設定
	pMenu->Set(pos, size, num, interval);

	return pMenu;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CMenu::CMenu() : CObject(CObject::PRIORITY_SYSTEM),
	m_pOption(nullptr),
	m_pFrame(nullptr),
	m_pCursor(nullptr),
	m_index(0),
	m_num(0),
	m_time(0),
	m_alpha(0.0f)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMenu::~CMenu()
{
	assert(m_pOption == nullptr);
	assert(m_pFrame == nullptr);
	assert(m_pCursor == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CMenu::Init()
{
	m_pOption = nullptr;
	m_pFrame = nullptr;
	m_pCursor = nullptr;
	m_index = 0;
	m_num = 0;
	m_time = 0;
	m_alpha = CHANGE_SPEED;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CMenu::Uninit()
{
	if (m_pOption != nullptr)
	{// nullチェック
		for (int i = 0; i < m_index; i++)
		{
			if (m_pOption[i] != nullptr)
			{// nullチェック
				m_pOption[i]->Uninit();
				m_pOption[i] = nullptr;
			}
		}

		delete[] m_pOption;
		m_pOption = nullptr;
	}
	
	if (m_pFrame != nullptr)
	{// nullチェック
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pCursor != nullptr)
	{// nullチェック
		m_pCursor->Uninit();
		m_pCursor = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CMenu::Update()
{
	// 入力
	Input();

	// α値の変更
	Alpha();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CMenu::Draw()
{
}

//--------------------------------------------------
// 選択
//--------------------------------------------------
int CMenu::Select()
{
	CFade::EState state = CApplication::GetInstance()->GetFade()->GetState();

	if (state != CFade::STATE_NONE)
	{// フェードしている
		return -1;
	}

	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_DECISION))
	{// 決定キーが押された
		m_alpha = 0.1f;

		return m_index;
	}

	return -1;
}

//--------------------------------------------------
// カーソルの設定
//--------------------------------------------------
void CMenu::SetCursor(const D3DXVECTOR3& size, float interval)
{
	if (m_pCursor != nullptr)
	{// nullチェック
		return;
	}

	// 生成
	m_pCursor = CObject2D::Create();

	D3DXVECTOR3 pos = m_pOption[m_index]->GetPos();
	pos.x -= ((size.x * 0.5f) + (m_pOption[m_index]->GetSize().x * 0.5f) + interval);

	// 位置の設定
	m_pCursor->SetPos(pos);

	// サイズの設定
	m_pCursor->SetSize(size);

	// テクスチャの設定
	m_pCursor->SetTexture(CTexture::LABEL_Cursor);
}

//--------------------------------------------------
// フレームの設定
//--------------------------------------------------
void CMenu::SetFrame(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	// 描画設定
	m_pFrame->SetDraw(true);

	// 位置の設定
	m_pFrame->SetPos(pos);

	// サイズの設定
	m_pFrame->SetSize(size);

	// 色の設定
	m_pFrame->SetCol(col);
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void CMenu::SetTexture(int idx, CTexture::ELabel label)
{
	if (idx == -1)
	{// 指定の値
		m_pFrame->SetTexture(label);
		return;
	}

	assert(idx >= 0 && idx < m_num);

	if (m_pOption[idx] == nullptr)
	{// nullチェック
		return;
	}
	
	// テクスチャの設定
	m_pOption[idx]->SetTexture(label);
}

//--------------------------------------------------
// サイズの設定
//--------------------------------------------------
void CMenu::SetSize(int idx, const D3DXVECTOR3& size)
{
	assert(idx >= 0 && idx < m_num);

	if (m_pOption[idx] == nullptr)
	{// nullチェック
		return;
	}

	int index = 0;
	float width = 0.0f;

	for (int i = 0; i < m_num; i++)
	{
		if (m_pOption[i] == nullptr)
		{// nullチェック
			continue;
		}

		if (m_pOption[i]->GetSize().x >= width)
		{// 他の選択肢以上の長さ
			width = m_pOption[i]->GetSize().x;
			index = i;
		}
	}
	
	width *= 0.5f;

	D3DXVECTOR3 pos = m_pOption[idx]->GetPos();
	pos.x = m_pOption[index]->GetPos().x - width;
	pos.x += size.x * 0.5f;

	// 位置の設定
	m_pOption[idx]->SetPos(pos);

	// サイズの設定
	m_pOption[idx]->SetSize(size);
}

//--------------------------------------------------
// 選択されている番号の取得
//--------------------------------------------------
int CMenu::GetSelectIdx()
{
	return m_index;
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CMenu::Set(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval)
{
	m_num = num;

	if (m_num == 0)
	{// 生成されない
		m_num = 1;
	}

	// 枠の作成
	m_pFrame = CObject2D::Create();

	// 描画設定
	m_pFrame->SetDraw(false);

	// 選択肢の生成
	m_pOption = new CObject2D*[m_num];

	if (m_pOption == nullptr)
	{// nullチェック
		assert(false);
		return;
	}

	D3DXVECTOR3 optionPos = pos;
	optionPos.y -= ((m_num - 1) * ((size.y * 0.5f) + (interval * 0.5f)));

	for (int i = 0; i < m_num; i++)
	{
		// 選択肢の作成
		m_pOption[i] = CObject2D::Create();

		// 位置の設定
		m_pOption[i]->SetPos(optionPos);

		// サイズの設定
		m_pOption[i]->SetSize(size);

		optionPos.y += size.y + interval;
	}
}

//--------------------------------------------------
// 入力
//--------------------------------------------------
void CMenu::Input()
{
	if (m_num == 1)
	{// 選択肢が一つだけ
		return;
	}

	if (m_alpha != CHANGE_SPEED)
	{// 決定されている
		return;
	}

	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_UP))
	{// 上キーが押された
		Add(-1);
	}
	if (pInput->Trigger(KEY_DOWN))
	{// 下キーが押された
		Add(1);
	}
}

//--------------------------------------------------
// α値
//--------------------------------------------------
void CMenu::Alpha()
{
	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, m_alpha) * 0.7f);

	// 色の設定
	m_pOption[m_index]->SetCol(col);
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CMenu::Add(int add)
{
	// 色の設定
	m_pOption[m_index]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_index = ((m_index + add) + m_num) % m_num;
	assert(m_index >= 0 && m_index < m_num);

	m_time = 0;

	if (m_pCursor != nullptr)
	{// nullチェック
		D3DXVECTOR3 pos = m_pCursor->GetPos();
		pos.y = m_pOption[m_index]->GetPos().y;

		// 位置の設定
		m_pCursor->SetPos(pos);
	}
}
