#pragma once

#include "JumpEffectParticle.h"
#include "List.h"


class JumpEffect
{
public:
	JumpEffect();
	virtual ~JumpEffect();

	static	HRESULT Init();
	static	void	Uninit();
	void	Update();
	void	Draw();

	void	Create(GameObject* pObj);
	bool	IsPlaying() { return m_isPlaying; }

private:
	List<JumpEffectParticle>*	m_pParticleList;
	bool	m_isPlaying;
};

