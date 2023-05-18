//**************************************************
// 
// fade.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FADE_H_	//このマクロ定義がされてなかったら
#define _FADE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object2D.h"
#include "mode.h"

//==================================================
// クラス
//==================================================
class CFade : public CObject2D
{
	/* 定義 */
public:
	enum EState
	{
		STATE_NONE = -1,
		STATE_IN = 0,	// イン
		STATE_OUT,		// アウト
		STATE_MAX
	};

	/* ↓静的メンバ関数↓ */
public:
	static CFade* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CFade();			// デフォルトコンストラクタ
	~CFade() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void ChangeMode(CMode::EMode nextMode);	// モードの変更
	EState GetState();	// 状態の取得

private:
	void In();	// イン
	void Out();	// アウト

	/* ↓メンバ変数↓ */
private:
	CMode::EMode m_mode;	// 変更するモード
	EState m_state;			// 状態
};

#endif // !_FADE_H_
