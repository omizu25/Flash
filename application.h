//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//このマクロ定義がされてなかったら
#define _APPLICATION_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CRenderer;
class CTexture;
class CFade;

//==================================================
// クラス
//==================================================
class CApplication
{
	/* ↓定義↓ */
public:
	static const int SCREEN_WIDTH = 1280;	// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

	/* ↓静的メンバ関数↓ */
public:
	static CApplication* GetInstance();	// インスタンスの取得

	/* ↓静的メンバ変数↓ */
private:
	static CApplication* m_pApplication;	// 自分のクラス

	/* ↓メンバ関数↓ */
private:
	CApplication();		// デフォルトコンストラクタ

public:
	~CApplication();	// デストラクタ

public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

public:
	CMode::EMode GetModeEnum();
	void SetMode(CMode::EMode mode);	// モードの設定
	LPDIRECT3DDEVICE9 GetDevice();		// デバイスの取得
	CRenderer* GetRenderer();			// レンダラーの取得
	CTexture* GetTexture();				// テクスチャの取得
	CMode* GetMode();					// モードの取得
	CFade* GetFade();					// フェードの取得

	/* ↓メンバ変数↓ */
private:
	CMode::EMode m_mode;	// 現在のモード
	CRenderer* m_pRenderer;	// レンダラーの情報
	CTexture* m_pTexture;	// テクスチャの情報
	CMode* m_pMode;			// モードの情報
	CFade* m_pFade;			// フェードの情報
};

#endif // !_APPLICATION_H_
