#pragma once
//========================================================
//	List.hの汎用リストに格納するための汎用ノード
//--------------------------------------------------------
//	各オブジェクトを格納し、前後のノードへのポインタを持つ。
//--------------------------------------------------------
//	2020.11.02	製作開始。完了
//========================================================

template<class T>
class Node
{
public:
	Node<T>(T* pObj);
	virtual ~Node();

	T* GetObj();
	Node<T>* GetPrev();
	Node<T>* GetNext();

	void SetPrev(Node<T> *pPrev);
	void SetNext(Node<T> *pNext);
	void SetPrevNext(Node<T> *pPrev, Node<T> *pNext);

	void DeleateObj();

	T		*m_pObj;
	Node<T>	*m_pPrev;
	Node<T>	*m_pNext;
protected:
};


template<class T>
Node<T>::Node(T* pObj)
	:m_pPrev(nullptr)
	, m_pObj(pObj)
	, m_pNext(nullptr)
{

}


template<class T>
Node<T>::~Node()
{
	//DeleateObj();
	m_pObj = nullptr;
	m_pPrev = nullptr;
	m_pNext = nullptr;
}


template<class T>
Node<T>* Node<T>::GetPrev()
{
	return m_pPrev;
}


template<class T>
T* Node<T>::GetObj()
{
	return m_pObj;
}


template<class T>
Node<T>* Node<T>::GetNext()
{
	return m_pNext;
}


template<class T>
void Node<T>::SetPrev(Node<T> *pPrev)
{
	m_pPrev = pPrev;
}


template<class T>
void Node<T>::SetNext(Node<T> *pNext)
{
	m_pNext = pNext;
}


template<class T>
void Node<T>::SetPrevNext(Node<T> *pPrev, Node<T> *pNext)
{
	SetPrev(pPrev);
	SetNext(pNext);
}



template<class T>
void Node<T>::DeleateObj()
{
	if (m_pObj != nullptr)
	{
		delete m_pObj;
		m_pObj = nullptr;
	}
}