#pragma once

#include "Particle.h"

class SandSmokeParticle :
	public Particle
{
public:
	SandSmokeParticle();
	virtual ~SandSmokeParticle();

	void	Update();

	void	SetMove(DirectX::XMFLOAT3 move);
	void	SetMove(float x, float y, float z);

	int		GetLife() { return m_life; }
protected:
	DirectX::XMFLOAT3 m_move;
	int m_life;
};

