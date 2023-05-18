//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "texture.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
const string FILE_PATH[] =
{// テクスチャのパス
	"data/TEXTURE/Number.png",		// 数字
	"data/TEXTURE/Cursor.png",		// カーソル
	"data/TEXTURE/PressEnter.png",	// プレスエンター
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture()
{
	memset(m_pTexture, 0, sizeof(m_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_PATH[label].c_str(),
		&m_pTexture[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 破棄
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// テクスチャの解放
		m_pTexture[label]->Release();
		m_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return m_pTexture[label];
}
