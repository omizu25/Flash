//**************************************************
// 
// precompile.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PRECOMPILE_H_	//このマクロ定義がされてなかったら
#define _PRECOMPILE_H_	//２重インクルード防止のマクロ定義

// 基本
#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include <tchar.h>
#include <time.h>

// メモリーリークのチェック
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// STL
#include <string>
using namespace std;	// 名前空間の指定

// DirectX9
#include <d3dx9.h>

// Input
#define	 DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <xinput.h>

// Sound
#include <xaudio2.h>

#endif // !_PRECOMPILE_H_
