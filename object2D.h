//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//このマクロ定義がされてなかったら
#define _OBJECT2D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "texture.h"

//==================================================
// クラス
//==================================================
class CObject2D : public CObject
{
	/* ↓定義↓ */
public:

	/* ↓静的メンバ関数↓ */
public:
	static CObject2D* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
//	CObject2D() = delete;	// デフォルトコンストラクタ
	explicit CObject2D(CObject::EPriority prio = CObject::PRIORITY_2D);	// コンストラクタ
	~CObject2D() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void SetPos(const D3DXVECTOR3& pos);		// 位置の設定
	const D3DXVECTOR3& GetPos() const;			// 位置の取得
	void SetSize(const D3DXVECTOR3& size);		// サイズの設定
	const D3DXVECTOR3& GetSize() const;			// サイズの取得
	void SetCol(const D3DXCOLOR& col);			// 色の設定
	const D3DXCOLOR& GetCol() const;			// 色の取得
	void SetRot(float rot);						// 向きの設定
	const float GetRot() const;					// 向きの取得
	void SetDraw(bool draw);					// 描画するかどうかの設定
	bool GetDraw();								// 描画するかどうかの取得
	void SetTexture(CTexture::ELabel texture);	// テクスチャの設定
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2& v);	// テクスチャ座標の設定

private:
	void SetVtxPos();	// 頂点情報の設定

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	CTexture::ELabel m_texture;	// テクスチャの列挙型
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_size;	// サイズ
	D3DXCOLOR m_col;	// 色
	float m_rot;		// 向き
	bool m_draw;		// 描画するかどうか
};

#endif // !_OBJECT2D_H_
