//**************************************************
//
// utility.h
// Author  : katsuki mizuki
// Author  : YudaKaito
//
//**************************************************
#ifndef _UTILITY_H_	// このマクロ定義がされてなかったら
#define _UTILITY_H_	// ２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 角度の正規化
// 引数  : float* pAngle / 角度
//--------------------------------------------------
void NormalizeAngle(float* pAngle);

//--------------------------------------------------
// ホーミング
// 引数1  : D3DXVECTOR3* pPosOut / 位置
// 引数2  : D3DXVECTOR3& posNow / 現在の位置
// 引数3  : D3DXVECTOR3& posDest / 目的の位置
// 引数4  : float fSpeed / 速さ
// 返値  : bool / 目的の位置に着いたかどうか
//--------------------------------------------------
bool Homing(D3DXVECTOR3* pPosOut, const D3DXVECTOR3& posNow, const D3DXVECTOR3& posDest, float fSpeed);

//--------------------------------------------------
// 小数点のランダム
// 引数1  : float fMax / 最大値
// 引数2  : float fMin / 最小値
// 返値  : float / ランダム値
//--------------------------------------------------
float FloatRandom(float fMax, float fMin);

//--------------------------------------------------
// 整数のランダム
// 引数1  : int nMax / 最大値
// 引数2  : int nMin / 最小値
// 返値  : int / ランダム値
//--------------------------------------------------
int IntRandom(int nMax, int nMin);

//--------------------------------------------------
// sinカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int nTime / タイム
// 引数2  : float fCycle / 周期
// 返値  : float / 1.0f〜0.0fのsinカーブ
//--------------------------------------------------
float SinCurve(int nTime, float fCycle);

//--------------------------------------------------
// cosカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int nTime / タイム
// 引数2  : float fCycle / 周期
// 返値  : float / 1.0f〜0.0fのcosカーブ
//--------------------------------------------------
float CosCurve(int nTime, float fCycle);

//--------------------------------------------------
// カーブの値が帰ってくる
// 引数1  : float fCurve / カーブ
// 引数2  : float fMax / 最大値
// 引数3  : float fMin / 最小値
// 返値  : float / カーブ
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin);

//--------------------------------------------------
// 範囲内
// 引数1  : D3DXVECTOR3* pPos / 位置
// 引数2  : D3DXVECTOR3 range / 範囲
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range);

//--------------------------------------------------
// 範囲内で反射
// 引数1  : D3DXVECTOR3* pPos / 位置
// 引数2  : D3DXVECTOR3* pMove / 移動量
// 引数3  : D3DXVECTOR3 range / 範囲
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range);

//--------------------------------------------------
// 円の当たり判定
// 引数1  : D3DXVECTOR3& pos1 / １つ目の位置
// 引数2  : float radius1 / １つ目の半径
// 引数3  : D3DXVECTOR3& pos2 / ２つ目の位置
// 引数4  : float radius2 / ２つ目の半径
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2);

//--------------------------------------------------
// エリアの当たり判定
// 引数1  : D3DXVECTOR3& pos1 / １つ目の位置
// 引数2  : float radius1 / １つ目の半径
// 引数3  : D3DXVECTOR3* pPos2 / ２つ目の位置
// 引数4  : float radius2 / ２つ目の半径
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool CollisionArea(const D3DXVECTOR3& pos1, float radius1, D3DXVECTOR3* pPos2, float radius2);

//--------------------------------------------------
// 桁数
// 引数  : int number / 数
// 返値  : int / 桁数
//--------------------------------------------------
int Digit(int number);

//--------------------------------------------------
// 2Dベクトルの外積
// 引数1  : D3DXVECTOR3* v1 / １つ目のベクトル
// 引数2  : D3DXVECTOR3* v2 / ２つ目のベクトル
// 返値  : float / 外積
//--------------------------------------------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

//--------------------------------------------------
// 2Dベクトルの内積
// 引数1  : D3DXVECTOR3* v1 / １つ目のベクトル
// 引数2  : D3DXVECTOR3* v2 / ２つ目のベクトル
// 返値  : float / 内積
//--------------------------------------------------
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

#endif // !_UTILITY_H_
