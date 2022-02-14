#pragma once

#include "SandSmokeParticle.h"
#include "List.h"
#include "Texture.h"

class SandSmoke
{
public:
	SandSmoke();
	virtual ~SandSmoke();

	virtual	HRESULT Init();
	virtual	void	Uninit();
	virtual	void	Update();
	virtual	void	Draw();

	virtual	void	Create(DirectX::XMFLOAT3 pos, int num, float speed);
protected:
	List<SandSmokeParticle>*	m_pParticleLsist;
	ID3D11ShaderResourceView*	m_pTexture;
};

