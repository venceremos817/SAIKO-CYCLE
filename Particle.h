#pragma once

#include "board.h"

class Particle
{
public:
	Particle();
	virtual ~Particle();

	static	HRESULT Init();
	static	void	Uninit();
	virtual void	Update();
	virtual void	Draw();

	virtual void	SetPos(DirectX::XMFLOAT3 pos);
	virtual void	SetPos(float x, float y, float z);
	virtual void	SetSize(DirectX::XMFLOAT3 size);
	virtual void	SetSize(float x, float y, float z);

protected:
	static	Board*	m_stpBoard;

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;
};

