//**************************************************
// 
// object.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT_H_	//このマクロ定義がされてなかったら
#define _OBJECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// クラス
//==================================================
class CObject
{
	/* ↓定義↓ */
public:
	enum EPriority
	{
		PRIORITY_NONE = -1,
		PRIORITY_SYSTEM = 0,	// システム
		PRIORITY_3D,			// 3D
		PRIORITY_EFFECT,		// エフェクト
		PRIORITY_2D,			// 2D
		PRIORITY_FADE,			// フェード
		PRIORITY_MAX
	};

	/* ↓静的メンバ関数↓ */
public:
	static void ReleaseAll();	// 全ての解放
	static void UpdateAll();	// 全ての更新
	static void DrawAll();		// 全ての描画
	static int GetNumAll();		// 総数の取得

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;	// 総数
	static CObject* m_pTop[PRIORITY_MAX];		// 先頭
	static CObject* m_pCurrent[PRIORITY_MAX];	// 最後尾

	/* ↓メンバ関数↓ */
public:
	CObject() = delete;	// デフォルトコンストラクタ
	explicit CObject(EPriority priority);	// コンストラクタ
	virtual ~CObject();	// デストラクタ

public:
	virtual void Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画

public:
	void Release();		// 解放
	void SetRelease();	// 解放する
	bool GetRelease();	// 解放するかどうかの取得

	/* ↓メンバ変数↓ */
private:
	CObject* m_pPrev;		// 前
	CObject* m_pNext;		// 次
	EPriority m_priority;	// 優先順位
	bool m_release;			// 解放するかどうか
};

#endif // !_OBJECT_H_
