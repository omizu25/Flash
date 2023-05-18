//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//このマクロ定義がされてなかったら
#define _MODE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"

//==================================================
// クラス
//==================================================
class CMode : public CObject
{
	/* 定義 */
public:
	enum EMode
	{
		MODE_NONE = -1,
		MODE_TITLE = 0,	// タイトル
		MODE_GAME,		// ゲーム
		MODE_MAX
	};

	/* 静的メンバ変数 */
public:
	static CMode* Create(EMode mode);	// 生成

	/* ↓メンバ関数↓ */
public:
	CMode();			// コンストラクタ
	~CMode() override;	// デストラクタ
	
public:
	virtual void Init() override = 0;	// 初期化
	virtual void Uninit() override = 0;	// 終了
	virtual void Update() override = 0;	// 更新
	virtual void Draw() override = 0;	// 描画
	
	/* ↓メンバ変数↓ */
private:
};

#endif // !_MODE_H_
