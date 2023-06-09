//**************************************************
// 
// object2D.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "object2D.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
struct VERTEX
{// 頂点データ
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

// 頂点フォーマット
const DWORD FVF_VERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const int NUM_VERTEX = 4;		// 頂点の数
const int NUM_POLYGON = 2;		// ポリゴンの数
const float STD_SIZE = 100.0f;	// 基準のサイズ
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = new CObject2D;

	if (pObject2D == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pObject2D->Init();

	// サイズの設定
	pObject2D->SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	return pObject2D;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CObject2D::CObject2D(CObject::EPriority prio) : CObject(prio),
	m_pVtxBuff(nullptr),
	m_pTexture(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_rot(0.0f),
	m_draw(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CObject2D::Init()
{
	m_pTexture = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_rot = 0.0f;
	m_draw = true;
	
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX* pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CObject2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{// テクスチャの破棄
		m_pTexture = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObject2D::Update()
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObject2D::Draw()
{
	if (!m_draw)
	{// 描画しない
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,						// 描画する最初の頂点インデックス
		NUM_POLYGON);			// プリミティブ(ポリゴン)数
	
	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CObject2D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;

	// 頂点情報の設定
	SetVtxPos();
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CObject2D::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// サイズの設定
//--------------------------------------------------
void CObject2D::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;

	// 頂点情報の設定
	SetVtxPos();
}

//--------------------------------------------------
// サイズの取得
//--------------------------------------------------
const D3DXVECTOR3& CObject2D::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void CObject2D::SetCol(const D3DXCOLOR& col)
{
	m_col = col;

	VERTEX* pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
const D3DXCOLOR& CObject2D::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// 向きの設定
//--------------------------------------------------
void CObject2D::SetRot(float rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// 向きの取得
//--------------------------------------------------
const float CObject2D::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// 描画するかどうかの設定
//--------------------------------------------------
void CObject2D::SetDraw(bool draw)
{
	m_draw = draw;
}

//--------------------------------------------------
// 描画するかどうかの取得
//--------------------------------------------------
bool CObject2D::GetDraw()
{
	return m_draw;
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void CObject2D::SetTexture(CTexture::ELabel texture)
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	m_pTexture = pTexture->Get(texture);
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void CObject2D::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//--------------------------------------------------
// テクスチャ座標の設定
//--------------------------------------------------
void CObject2D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2& v)
{
	VERTEX* pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(u.x, v.x);
	pVtx[1].tex = D3DXVECTOR2(u.y, v.x);
	pVtx[2].tex = D3DXVECTOR2(u.x, v.y);
	pVtx[3].tex = D3DXVECTOR2(u.y, v.y);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 頂点情報の設定
//--------------------------------------------------
void CObject2D::SetVtxPos()
{
	D3DXMATRIX mtx, mtxTrans;

	// 回転の反映
	D3DXMatrixRotationZ(&mtx, -m_rot);

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	
	D3DXVECTOR3 pVtxPos[NUM_VERTEX];

	float width = m_size.x * 0.5f;
	float height = m_size.y * 0.5f;

	// 頂点情報の設定
	pVtxPos[0] = D3DXVECTOR3(-width, -height, 0.0f);
	pVtxPos[1] = D3DXVECTOR3(+width, -height, 0.0f);
	pVtxPos[2] = D3DXVECTOR3(-width, +height, 0.0f);
	pVtxPos[3] = D3DXVECTOR3(+width, +height, 0.0f);

	VERTEX* pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{// 頂点情報の設定
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxPos[i], &mtx);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
