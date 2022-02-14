#pragma once
#include "Field.h"
#include "model.h"

class JumpRamp :
	public Field
{
public:
	JumpRamp();
	virtual ~JumpRamp();

	virtual HRESULT	Init();
	virtual void	Uninit();
	virtual void	Update();
	virtual void	Draw();

protected:
	static Model* m_pModel;
};

