//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//==================================================
// 静的メンバ変数
//==================================================
int CObject::m_numAll = 0;
CObject* CObject::m_pTop[PRIORITY_MAX] = {};
CObject* CObject::m_pCurrent[PRIORITY_MAX] = {};

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		CObject* pObj = m_pTop[i];

		if (pObj == nullptr || i == PRIORITY_FADE)
		{// nullチェック
			continue;
		}

		while (true)
		{
			CObject* pObjNext = pObj->m_pNext;

			// 終了
			pObj->Uninit();

			pObj = pObjNext;

			if (pObj == nullptr)
			{// 最後まで来た
				break;
			}
		}
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		CObject* pObj = m_pTop[i];

		if (pObj == nullptr)
		{// nullチェック
			continue;
		}

		while (true)
		{
			if (!pObj->m_release)
			{// 解放しない
				pObj->Update();
			}

			pObj = pObj->m_pNext;

			if (pObj == nullptr)
			{// 最後まで来た
				break;
			}
		}

		pObj = m_pTop[i];

		while (true)
		{
			CObject* pObjNext = pObj->m_pNext;

			if (pObj->m_release)
			{// 解放する
				pObj->Uninit();
			}

			pObj = pObjNext;

			if (pObj == nullptr)
			{// 最後まで来た
				break;
			}
		}
	}
}

//--------------------------------------------------
// 全ての描画
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		CObject* pObj = m_pTop[i];

		if (pObj == nullptr)
		{// nullチェック
			continue;
		}

		while (true)
		{
			if (!pObj->m_release)
			{// 解放しない
				pObj->Draw();
			}

			pObj = pObj->m_pNext;

			if (pObj == nullptr)
			{// 最後まで来た
				break;
			}
		}
	}
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CObject::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CObject::CObject(EPriority priority) :
	m_pPrev(nullptr),
	m_pNext(nullptr),
	m_priority(priority),
	m_release(false)
{
	if (m_pTop[priority] == nullptr)
	{// 誰もいない
		assert(m_pCurrent[priority] == nullptr);

		m_pTop[priority] = this;
		m_pCurrent[priority] = this;
	}
	else
	{
		m_pPrev = m_pCurrent[priority];
		m_pCurrent[priority]->m_pNext = this;
		m_pCurrent[priority] = this;
	}

	m_numAll++;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject::~CObject()
{
	assert(m_pPrev == nullptr);
	assert(m_pNext == nullptr);

	m_numAll--;
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CObject::Release()
{
	if (this == nullptr)
	{// nullチェック
		return;
	}
	else if (m_pPrev == nullptr && m_pNext == nullptr)
	{// 自分しかいない
		assert(m_pTop[m_priority] == this);
		assert(m_pCurrent[m_priority] == this);

		m_pTop[m_priority] = nullptr;
		m_pCurrent[m_priority] = nullptr;
	}
	else if (m_pPrev == nullptr)
	{// 先頭
		assert(m_pTop[m_priority] == this);

		m_pTop[m_priority] = m_pNext;
		m_pTop[m_priority]->m_pPrev = nullptr;
	}
	else if (m_pNext == nullptr)
	{// 最後尾
		assert(m_pCurrent[m_priority] == this);

		m_pCurrent[m_priority] = m_pPrev;
		m_pCurrent[m_priority]->m_pNext = nullptr;
	}
	else
	{// 中間
		assert(m_pTop[m_priority] != this);
		assert(m_pCurrent[m_priority] != this);

		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}

	m_pPrev = nullptr;
	m_pNext = nullptr;

	delete this;
}

//--------------------------------------------------
// 解放する
//--------------------------------------------------
void CObject::SetRelease()
{
	m_release = true;
}

//--------------------------------------------------
// 解放するかどうかの取得
//--------------------------------------------------
bool CObject::GetRelease()
{
	return m_release;
}
