#include "Particle.h"
#include "CameraInverse.h"

Board* Particle::m_stpBoard = nullptr;

Particle::Particle()
	: m_pos(0, 0, 0)
	, m_size(0.5, 0.5, 0.5)
{

}

Particle::~Particle()
{

}


HRESULT Particle::Init()
{
	if (m_stpBoard == nullptr)
	{
		m_stpBoard = new Board;
	}

	return S_OK;
}


void Particle::Uninit()
{
	if (m_stpBoard != nullptr)
	{
		delete m_stpBoard;
		m_stpBoard = nullptr;
	}
}


void Particle::Update()
{

}


void Particle::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * CameraInverse::GetInversMatrix() * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_stpBoard->Draw();
}


void Particle::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void Particle::SetPos(float x, float y, float z)
{
	SetPos(DirectX::XMFLOAT3(x, y, z));
}


void Particle::SetSize(DirectX::XMFLOAT3 size)
{
	m_size = size;
}

void Particle::SetSize(float x, float y, float z)
{
	SetPos(DirectX::XMFLOAT3(x, y, z));
}