#pragma once
#include "Field.h"
#include "model.h"

class StageStart :
	public Field
{
public:
	StageStart();
	virtual ~StageStart();

	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

protected:
	static Model* m_pModel;
};

