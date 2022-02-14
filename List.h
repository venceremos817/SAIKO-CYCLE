#pragma once
//========================================================
//	汎用双方向リスト
//--------------------------------------------------------
//	オブジェクトをリストに格納して管理することで、
//	オブジェクトを一括で管理できるようにすることを目的とする。
//--------------------------------------------------------
//	2020.11.02	製作開始
//				リストに格納するノード製作(Node.h)
//		.11.03	リスト解放時にノードに格納されているオブジェクトは解放しないようにした。
//========================================================


//===== インクルード部 =====
#include "Node.h"

template<class T>
class List
{
public:
	List<T>();
	virtual ~List();

	void AddObject(T* pObj);				// リストの末尾にオブジェクトを追加する。ノードは自動的に作られる
	T* CreateNewObj();						// リストの末尾にオブジェクトを新規作成し、追加する。ノードは自動的に作られる。	(使用例	 CEnemy* pEnemy = list.CreateNewObj();
	void DestroyNode(Node<T>* pDestNode);	// 引数に渡されたノードを破棄・解放する。ノードに紐づけられたオブジェクトは解放しない
	void DestryoObj(T* pDestObj);			// 指定されたオブジェクトとそのノードを解放する
	void ClearList();						// リスト内のノードを全て解放する。オブジェクトは解放しない
	void ClearAll();						// リスト内のすべてのオブジェクト・ノードを解放する

	Node<T>* GetHead() { return m_pHead; }	// リストに登録されている先頭のノードのポインタを取得。ループ処理の最初によく使う
	Node<T>* GetTail() { return m_pTail; }	// リストに登録されている末尾のノードのポインタを取得
	Node<T>* GetPrev(Node<T> *pNode);		// 引数に渡したノードの前のノードを返す。前のノードがなければnullptrが返る
//	Node<T>* GetRef();
	Node<T>* GetNext(Node<T> *pNode);		// 引数に渡したノードの次のノードを返す。次のノードがなければnullptrが返る

	void	Swap(Node<T> *pA, Node<T> *pB); // ノードの位置を入れ替える


private:
	Node<T>	*m_pHead;		// リストの先頭
	Node<T>	*m_pTail;		// リストの末尾
//	Node<T>	*m_pRef;	// 現在の参照位置
};




////////////////////////////////////////////////////////////
// メンバ関数をListBase.cppにて実装すると他cppから
// 関数テンプレートの定義が見えなくなるため、ヘッダファイルで
// メンバ関数の実装を行う!!!!!!!!!!!!!!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////


template<class T>
List<T>::List()
	: m_pHead(nullptr)
	, m_pTail(nullptr)
//	, m_pRef(nullptr)
{

}


template<class T>
List<T>::~List()
{
	ClearList();
	m_pHead = nullptr;
	m_pTail = nullptr;
}


template<class T>
void List<T>::AddObject(T* pObj)
{
	// ノードを新規作成 (動的確保)
	Node<T> *pNewNode = new Node<T>(pObj);

	//--- リストがカラの場合 ---
	if (m_pHead == nullptr)
	{
		// 先頭と末尾設定
		m_pHead = pNewNode;
		m_pTail = pNewNode;
		// このノードは先頭なので前後は無し
		pNewNode->SetPrevNext(nullptr, nullptr);
	}
	else	//--- リストにノードが存在する場合 ---
	{
		// 現在の末尾の次に追加
		GetTail()->SetNext(pNewNode);
		// 新しく作ったノードの前後関係設定
		pNewNode->SetPrevNext(GetTail(), nullptr);
		// リストの末尾が新規ノードになる
		m_pTail = pNewNode;
	}
}


template<class T>
T* List<T>::CreateNewObj()
{
	T* NewObj = new T;
	AddObject(NewObj);

	return NewObj;
}


template<class T>
void List<T>::DestroyNode(Node<T>* pDestNode)
{
	// リスト内で該当のノードを探索
	Node<T> *pNode = nullptr;

	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		if (pNode == pDestNode)
			break;
	}

	// 見つからなかった場合
	if (pNode == nullptr)
		return;

	//--- 見つかった ---
	// 先頭だったとき
	if (pDestNode == m_pHead)
	{
		// 2番目が先頭になる
		m_pHead = m_pHead->GetNext();
		m_pHead->SetPrev(nullptr);
		// オブジェクト解放
		//pDestNode->DeleateObj();
		// ノード解放
		delete pDestNode;
		pDestNode = nullptr;
	}
	else if (pDestNode == m_pTail)	// 末尾だったとき
	{
		// 末尾から2番目が末尾になる
		m_pTail = m_pTail->GetPrev();
		m_pTail->SetNext(nullptr);
		// オブジェクト解放
		//pDestNode->DeleateObj();
		// ノード解放
		delete pDestNode;
		pDestNode = nullptr;
	}
	else	// それ以外
	{
		// 消すノードの前後をくっつける
		pDestNode->m_pPrev->m_pNext = pDestNode->m_pNext;
		pDestNode->m_pNext->m_pPrev = pDestNode->m_pPrev;
		// オブジェクト解放
		//pDestNode->DeleateObj();
		// ノード解放
		delete pDestNode;
		pDestNode = nullptr;
	}

}


template<class T>
void List<T>::DestryoObj(T* pDestObj)
{
	// リスト内で該当のオブジェクトを持つノードを探索
	Node<T> *pNode = nullptr;

	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		if (pNode->GetObj() == pDestObj)
			break;
	}

	// 見つからなかった場合
	if (pNode == nullptr)
		return;

	//--- 見つかった ---
	// 先頭だったとき
	if (pNode == m_pHead)
	{
		// 2番目が先頭になる
		m_pHead = m_pHead->GetNext();
		// 2番目が存在するなら
		if (m_pHead != nullptr)
			m_pHead->SetPrev(nullptr);
		// オブジェクト解放
		pNode->DeleateObj();
		// ノード解放
		delete pNode;
		pNode = nullptr;
	}
	else if (pNode == m_pTail)	// 末尾だったとき
	{
		// 末尾から2番目が末尾になる
		m_pTail = m_pTail->GetPrev();
		m_pTail->SetNext(nullptr);
		// オブジェクト解放
		pNode->DeleateObj();
		// ノード解放
		delete pNode;
		pNode = nullptr;
	}
	else	// それ以外
	{
		// 消すノードの前後をくっつける
		pNode->m_pPrev->m_pNext = pNode->m_pNext;
		pNode->m_pNext->m_pPrev = pNode->m_pPrev;
		// オブジェクト解放
		pNode->DeleateObj();
		// ノード解放
		delete pNode;
		pNode = nullptr;
	}
}


template<class T>
void List<T>::ClearList()
{
	Node<T>	*pNode = nullptr;
	Node<T> *pNextNode = nullptr;

	// 先頭からオブジェクトの解放とノードの解放をしていく
	for (pNode = m_pHead; pNode != nullptr; pNode = pNextNode)
	{
		// 次のノードを確保
		pNextNode = pNode->GetNext();

		// オブジェクトの解放
		//pNode->DeleateObj();

		// ノードの開放
		delete pNode;
		pNode = nullptr;
	}
	m_pHead = nullptr;
	m_pTail = nullptr;
}


template<class T>
void List<T>::ClearAll()
{
	Node<T>	*pNode = nullptr;
	Node<T> *pNextNode = nullptr;

	// 先頭からオブジェクトの解放とノードの解放をしていく
	for (pNode = m_pHead; pNode != nullptr; pNode = pNextNode)
	{
		// 次のノードを確保
		pNextNode = pNode->GetNext();

		// オブジェクトの解放
		pNode->DeleateObj();

		// ノードの開放
		delete pNode;
		pNode = nullptr;
	}
	m_pHead = nullptr;
	m_pTail = nullptr;
}


template<class T>
Node<T>* List<T>::GetPrev(Node<T>* pNode)
{
	return pNode->GetPrev();
}


template<class T>
Node<T>* List<T>::GetNext(Node<T> *pNode)
{
	return pNode->GetNext();
}


template<class T>
void List<T>::Swap(Node<T> *pA, Node<T> *pB)
{
	Node<T> *pTmp;

	pTmp = pA;
	pA = pB;
	pB = pTmp;
}