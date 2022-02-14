#pragma once
#include "board.h"
#include "Sign.h"
#include "Sphere.h"


class StageStartDirecting
{
public:
	StageStartDirecting();
	virtual ~StageStartDirecting();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static bool m_isFinish;

private:
	Sign*	m_pSign;
	Board*	m_pBoard;
	Sphere*	m_pSphere;

	DirectX::XMFLOAT2 m_size;
	ID3D11ShaderResourceView*	m_pTex[3];
	bool m_bDraw[2];
	float y;
};

