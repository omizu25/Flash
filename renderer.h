//**************************************************
// 
// renderer.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RENDERER_H_	//このマクロ定義がされてなかったら
#define _RENDERER_H_	//２重インクルード防止のマクロ定義

//==================================================
// 前方宣言
//==================================================
class CCamera;

//==================================================
// クラス
//==================================================
class CRenderer
{
	/* ↓定義↓ */
public:

	/* ↓メンバ関数↓ */
public:
	CRenderer();	// デフォルトコンストラクタ
	~CRenderer();	// デストラクタ

public:
	HRESULT Init(HWND hWnd, bool bWindow);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

public:
	LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得
	CCamera* GetCamera();			// カメラの取得

private:
#ifdef _DEBUG
	void DrawFPS();	// FPS表示
#endif // _DEBUG

	/* ↓メンバ変数↓ */
private:
#ifdef _DEBUG
	LPD3DXFONT m_pFont;	// フォント
#endif // _DEBUG

	LPDIRECT3D9 m_pD3D;				// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト
	CCamera* m_pCamera;	// カメラの情報
};

#endif // !_RENDERER_H_
