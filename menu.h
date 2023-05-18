//**************************************************
// 
// menu.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MENU_H_	//このマクロ定義がされてなかったら
#define _MENU_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "texture.h"

//==================================================
// 前方宣言
//==================================================
class CObject2D;

//==================================================
// 定義
//==================================================
class CMenu : public CObject
{
	/* ↓定義↓ */
public:
	
	/* ↓静的メンバ関数↓ */
public:
	//--------------------------------------------------
	// 生成
	// pos / 位置
	// size / サイズ
	// num / 選択肢の数
	// interval / 間隔
	// cursor / カーソルを使うかどうか
	//--------------------------------------------------
	static CMenu* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval);

	/* ↓メンバ関数↓ */
public:
	CMenu();			// デフォルトコンストラクタ
	~CMenu() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	int Select();	// 選択
	void SetCursor(const D3DXVECTOR3& size, float interval);	// カーソルの設定
	void SetFrame(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col);	// 枠の設定
	void SetTexture(int idx, CTexture::ELabel label);	// テクスチャの設定
	void SetSize(int idx, const D3DXVECTOR3& size);		// サイズの設定
	int GetSelectIdx();	// 選択されている番号の取得

private:
	void Set(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval);	// 設定
	void Input();		// 入力
	void Alpha();		// α値
	void Add(int add);	// 加算

	/* ↓メンバ変数↓ */
private:
	CObject2D** m_pOption;	// 選択肢
	CObject2D* m_pFrame;	// 枠
	CObject2D* m_pCursor;	// カーソル
	int m_index;	// 選択されている番号
	int m_num;		// 選択肢の数
	int m_time;		// タイム
	float m_alpha;	// α値
};

#endif // !_MENU_H_
