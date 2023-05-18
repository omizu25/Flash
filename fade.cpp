//**************************************************
// 
// fade.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "fade.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
const float FADE_SPEED = 0.05f;	// フェードの速度
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CFade* CFade::Create()
{
	CFade* pFade = new CFade;

	if (pFade == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pFade->Init();

	return pFade;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CFade::CFade() : CObject2D(CObject::PRIORITY_FADE),
	m_mode(CMode::MODE_NONE),
	m_state(STATE_NONE)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CFade::~CFade()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CFade::Init()
{
	// 初期化
	CObject2D::Init();

	D3DXVECTOR3 vec = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

	// 位置の設定
	CObject2D::SetPos(vec * 0.5f);

	// サイズの設定
	CObject2D::SetSize(vec);

	// 色の設定
	CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	m_mode = CMode::MODE_NONE;
	m_state = STATE_NONE;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CFade::Uninit()
{
	// 終了
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CFade::Update()
{
	switch (m_state)
	{
	case STATE_NONE:
		/* 処理なし */
		break;

	case STATE_IN:
		In();
		break;

	case STATE_OUT:
		Out();
		break;

	case STATE_MAX:
	default:
		assert(false);
		break;
	}

	// 更新
	CObject2D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CFade::Draw()
{
	// 描画
	CObject2D::Draw();
}

//--------------------------------------------------
// モードの変更
//--------------------------------------------------
void CFade::ChangeMode(CMode::EMode nextMode)
{
	if (m_state != STATE_NONE)
	{// フェードをしている
		return;
	}

	// 初期化
	Init();

	m_mode = nextMode;
	m_state = STATE_IN;
}

//--------------------------------------------------
// 状態の取得
//--------------------------------------------------
CFade::EState CFade::GetState()
{
	return m_state;
}

//--------------------------------------------------
// イン
//--------------------------------------------------
void CFade::In()
{
	// 色の取得
	D3DXCOLOR col = CObject2D::GetCol();

	col.a += FADE_SPEED;

	if (col >= 1.0f)
	{// 指定の値以上
		col.a = 1.0F;
		m_state = STATE_OUT;
		
		// モードの設定
		CApplication::GetInstance()->SetMode(m_mode);
	}

	// 色の設定
	CObject2D::SetCol(col);
}

//--------------------------------------------------
// アウト
//--------------------------------------------------
void CFade::Out()
{
	// 色の取得
	D3DXCOLOR col = CObject2D::GetCol();

	col.a += -FADE_SPEED;

	if (col <= 0.0f)
	{// 指定の値以下
		col.a = 0.0F;
		m_state = STATE_NONE;
	}

	// 色の設定
	CObject2D::SetCol(col);
}
