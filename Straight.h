#pragma once
#include "Field.h"
#include "model.h"


class Straight :
	public Field
{
public:
	Straight();
	virtual ~Straight();

	virtual HRESULT Init();
	virtual void	Uninit();
	virtual void	Update();
	virtual void	Draw();

protected:
	static Model* m_pModel;
};

