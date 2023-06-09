//**************************************************
// 
// time.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TIME_H_	//このマクロ定義がされてなかったら
#define _TIME_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "number_manager.h"

//==================================================
// 前方宣言
//==================================================

//==================================================
// 定義
//==================================================
class CTime : public CNumberManager
{
	/* ↓定義↓ */
public:

	/* ↓静的メンバ関数↓ */
public:
	static CTime* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CTime();			// デフォルトコンストラクタ
	~CTime() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	bool Switch();	// 切り替わったかどうか

private:
	void Load();	// 読み込み

	/* ↓メンバ変数↓ */
private:
	int m_time;			// 時間
	int m_switchTime;	// 切り替わる秒数
	bool m_switch;		// 切り替わったかどうか
};

#endif // !_TIME_H_
