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

	// �ėp�p�[�e�B�N��
	hr = Particle::Init();
	if (FAILED(hr)) { return hr; }

	// �W�����v�G�t�F�N�g
	if (m_pJumpEffectList == nullptr)
	{
		m_pJumpEffectList = new List<JumpEffect>;
	}
	hr = JumpEffect::Init();
	if (FAILED(hr)) { return hr; }

	// ����
	if (m_pSandSmoke == nullptr)
	{
		m_pSandSmoke = new SandSmoke;
	}
	hr = m_pSandSmoke->Init();
	if (FAILED(hr)) { return hr; }

	// �W����
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
	// �W����
	if (m_pConcentrateLine != nullptr)
	{
		m_pConcentrateLine->Uninit();
		delete m_pConcentrateLine;
		m_pConcentrateLine = nullptr;
	}

	// ����
	if (m_pSandSmoke != nullptr)
	{
		m_pSandSmoke->Uninit();
		delete m_pSandSmoke;
		m_pSandSmoke = nullptr;
	}

	// �W�����v�G�t�F�N�g
	if (m_pJumpEffectList != nullptr)
	{
		m_pJumpEffectList->ClearAll();
		delete m_pJumpEffectList;
		m_pJumpEffectList = nullptr;
	}
	JumpEffect::Uninit();

	// �ėp�p�[�e�B�N��
	Particle::Uninit();
}


void EffectManager::Update()
{
	// �W�����v�G�t�F�N�g
	Node<JumpEffect>* pJENode = m_pJumpEffectList->GetHead();
	while (pJENode != nullptr)
	{
		pJENode->GetObj()->Update();
		// �Đ��I�����Ă�m�[�h�Ȃ�j��
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

	// ����
	m_pSandSmoke->Update();

	// �W����
	m_pConcentrateLine->Update();
}


void EffectManager::Draw3D()
{
	// �W�����v�G�t�F�N�g
	Node<JumpEffect>* pJENode = m_pJumpEffectList->GetHead();
	SetBlendMode(BlendMode::BLEND_ADD);
	while (pJENode != nullptr)
	{
		pJENode->GetObj()->Draw();
		pJENode = pJENode->GetNext();
	}
	SetBlendMode(BlendMode::BLEND_ALPHA);

	// ����
	m_pSandSmoke->Draw();
}


void EffectManager::Draw2D()
{
	// �W����
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