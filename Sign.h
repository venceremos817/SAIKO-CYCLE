#pragma once

//===== インクルード部 =====
#include "DrawBuffer.h"

class Sign
{
public:
	Sign();
	~Sign();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();


private:
	DrawBuffer* m_pBufferS;

	float nCnt;
	int i;
};
