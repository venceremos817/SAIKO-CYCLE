#pragma once
#include "Field.h"
#include "model.h"

class Curve :
	public Field
{
public:
	Curve();
	virtual ~Curve();

	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

protected:
	static Model* m_pModel;
};

