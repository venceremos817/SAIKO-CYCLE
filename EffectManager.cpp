#include "EffectManager.h"


List<JumpEffect>*	EffectManager::m_pJumpEffectList = nullptr;
SandSmoke*	EffectManager::m_pSandSmoke = nullptr;
ConcentratedLine* EffectManager::m_pConcentrateLine = nullptr;

EffectManager::EffectManager()
{

}


EffectManager::~EffectManager()
{

}


HRESULT EffectManager::Init()
{
	HRESULT hr;

	// 汎用パーティクル
	hr = Particle::Init();
	if (FAILED(hr)) { return hr; }

	// ジャンプエフェクト
	if (m_pJumpEffectList == nullptr)
	{
		m_pJumpEffectList = new List<JumpEffect>;
	}
	hr = JumpEffect::Init();
	if (FAILED(hr)) { return hr; }

	// 砂煙
	if (m_pSandSmoke == nullptr)
	{
		m_pSandSmoke = new SandSmoke;
	}
	hr = m_pSandSmoke->Init();
	if (FAILED(hr)) { return hr; }

	// 集中線
	if (m_pConcentrateLine == nullptr)
	{
		m_pConcentrateLine = new ConcentratedLine;
	}
	hr = m_pConcentrateLine->Init();
	if (FAILED(hr)) { return hr; }

	return hr;
}


void EffectManager::Uninit()
{
	// 集中線
	if (m_pConcentrateLine != nullptr)
	{
		m_pConcentrateLine->Uninit();
		delete m_pConcentrateLine;
		m_pConcentrateLine = nullptr;
	}

	// 砂煙
	if (m_pSandSmoke != nullptr)
	{
		m_pSandSmoke->Uninit();
		delete m_pSandSmoke;
		m_pSandSmoke = nullptr;
	}

	// ジャンプエフェクト
	if (m_pJumpEffectList != nullptr)
	{
		m_pJumpEffectList->ClearAll();
		delete m_pJumpEffectList;
		m_pJumpEffectList = nullptr;
	}
	JumpEffect::Uninit();

	// 汎用パーティクル
	Particle::Uninit();
}


void EffectManager::Update()
{
	// ジャンプエフェクト
	Node<JumpEffect>* pJENode = m_pJumpEffectList->GetHead();
	while (pJENode != nullptr)
	{
		pJENode->GetObj()->Update();
		// 再生終了してるノードなら破棄
		if (!pJENode->GetObj()->IsPlaying())
		{
			JumpEffect* pDeleteObj = pJENode->GetObj();
			pJENode = pJENode->GetNext();
			m_pJumpEffectList->DestryoObj(pDeleteObj);
		}
		else
		{
			pJENode = pJENode->GetNext();
		}
	}

	// 砂煙
	m_pSandSmoke->Update();

	// 集中線
	m_pConcentrateLine->Update();
}


void EffectManager::Draw3D()
{
	// ジャンプエフェクト
	Node<JumpEffect>* pJENode = m_pJumpEffectList->GetHead();
	SetBlendMode(BlendMode::BLEND_ADD);
	while (pJENode != nullptr)
	{
		pJENode->GetObj()->Draw();
		pJENode = pJENode->GetNext();
	}
	SetBlendMode(BlendMode::BLEND_ALPHA);

	// 砂煙
	m_pSandSmoke->Draw();
}


void EffectManager::Draw2D()
{
	// 集中線
	m_pConcentrateLine->Draw();
}


void EffectManager::CreateJumpEffect(GameObject* pObj)
{
	JumpEffect* pJumpEffect = m_pJumpEffectList->CreateNewObj();
	
	pJumpEffect->Create(pObj);
}


void EffectManager::CreateSandSmoke(DirectX::XMFLOAT3 pos, int num, float speed)
{
	m_pSandSmoke->Create(pos, num, speed);
}


void EffectManager::ActiveConcentedLine(bool active)
{
	m_pConcentrateLine->Active(active);
}