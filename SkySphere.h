#pragma once

//===== インクルード部 =====
#include "BasicFigure.h"
#include "GameObject.h"
#include "Texture.h"

class SkySphere
	:public BasicFigure
{
public:
	SkySphere();
	SkySphere(int segment,int ring);
	virtual ~SkySphere();

	void Update();
	void Draw();


	void SetTargetObj(GameObject *pObj);

private:
	void Init(int segment, int ring);

	GameObject	*m_pObj;
};

