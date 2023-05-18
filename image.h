//**************************************************
// 
// image.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _IMAGE_H_	//このマクロ定義がされてなかったら
#define _IMAGE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object2D.h"

//==================================================
// 前方宣言
//==================================================

//==================================================
// 定義
//==================================================
class CImage : public CObject2D
{
	/* ↓定義↓ */
public:

	/* ↓静的メンバ関数↓ */
public:
	static CImage* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CImage();			// デフォルトコンストラクタ
	~CImage() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Load();	// 読み込み
	void Switch();	// 切り替え
	void Random();	// ランダム

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャの情報
	string* m_pPath;	// テクスチャのパス
	int* m_pUsed;		// 使用した
	int m_switchMax;	// 切り替わる最大数
	int m_switch;		// 切り替えた数
	int m_num;			// テクスチャの数
	int m_index;		// 現在の番号
};

#endif // !_IMAGE_H_
