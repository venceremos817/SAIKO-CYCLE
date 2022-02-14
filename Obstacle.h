#pragma once
#include "Field.h"
#include "model.h"

class Obstacle :
	public Field
{
public:
	Obstacle();
	virtual ~Obstacle();

	virtual HRESULT	Init();
	virtual void	Uninit();
	virtual void	Update();
	virtual void	Draw();

protected:

private:
	int m_flyFrame;
	DirectX::XMFLOAT3 m_rotSpd;
	static Model*	m_pModel;

private:
	void BlowAway();
};