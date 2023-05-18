//**************************************************
// 
// number_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_MANAGER_H_	//このマクロ定義がされてなかったら
#define _NUMBER_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"

//==================================================
// 前方宣言
//==================================================
class CNumber;

//==================================================
// 定義
//==================================================
class CNumberManager : public CObject
{
	/* ↓定義↓ */
public:
	static const int MAX_DIGIT = 3;	// 桁の最大数

	/* ↓静的メンバ関数↓ */
public:
	static CNumberManager* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int value);	// 生成

	/* ↓メンバ関数↓ */
public:
	CNumberManager();	// デフォルトコンストラクタ
	~CNumberManager() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void Add(int value);	// 加算
	void Set(int value);	// 設定
	int Get();	// 取得

public:
	void SetPos(const D3DXVECTOR3& pos);	// 位置の設定
	void SetCol(const D3DXCOLOR& col);		// 色の設定
	void SetDraw(bool draw);				// 描画の設定
	void SetZero(bool zero);				// ゼロの設定
	void SetZeroDigit(int digit);			// ゼロの桁数の設定
	void SetInterval(int interval, float width);	// 間隔の設定

private:
	void ZeroDraw();	// ゼロの描画
	void Change();		// 変更

	/* ↓メンバ変数↓ */
private:
	CNumber* m_pNumber[MAX_DIGIT];	// 数
	int m_value;		// 値
	int m_zeroDigit;	// ゼロを描画する桁数
	int m_interval;		// 間隔
	float m_width;		// 間隔の幅
	bool m_zero;		// ゼロを描画するかどうか
};

#endif // !_NUMBER_MANAGER_H_
