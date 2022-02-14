#include "JumpEffect.h"


const int MIN_PARTICAL_NUM = 3;
const int MAX_PARTICAL_NUM = 10;
const float MOVE_SPEED = 3.0f / 60.0f;


JumpEffect::JumpEffect()
	: m_pParticleList(nullptr)
	, m_isPlaying(true)
{
	m_pParticleList = new List<JumpEffectParticle>;
}

JumpEffect::~JumpEffect()
{
	if (m_pParticleList != nullptr)
	{
		m_pParticleList->ClearAll();
		delete m_pParticleList;
		m_pParticleList = nullptr;
	}
}


HRESULT JumpEffect::Init()
{
	HRESULT hr;
	hr = JumpEffectParticle::Init();
	if (FAILED(hr)) { return hr; }

	return hr;
}


void JumpEffect::Uninit()
{
	JumpEffectParticle::Uninit();
}


void JumpEffect::Update()
{
	if (m_pParticleList == nullptr)
	{
		m_isPlaying = false;
		return;
	}

	Node<JumpEffectParticle>* pNode = m_pParticleList->GetHead();
	int liveCnt = 0;
	while (pNode != nullptr)
	{
		pNode->GetObj()->Update();

		if (!pNode->GetObj()->IsFinish())
			liveCnt++;		// Ä¶’†‚È‚ç{

		pNode = pNode->GetNext();
	}

	if (liveCnt == 0)
		m_isPlaying = false;
}


void JumpEffect::Draw()
{
	if (!m_isPlaying)
		return;

	Node<JumpEffectParticle>* pNode = m_pParticleList->GetHead();
	while (pNode != nullptr)
	{
		pNode->GetObj()->Draw();
		pNode = pNode->GetNext();
	}
}


int	RandInteger(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void JumpEffect::Create(GameObject* pObj)
{
	JumpEffectParticle* pParticle = m_pParticleList->CreateNewObj();
	pParticle->SetFollowObj(pObj);
	pParticle->SetSize(DirectX::XMFLOAT3(10, 10, 10));
}