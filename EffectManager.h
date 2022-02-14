#pragma once

#include "List.h"
#include "GameObject.h"

// 3Dビルボードエフェクト
#include "JumpEffect.h"
#include "SandSmoke.h"
// 2Dエフェクト
#include "ConcentratedLine.h"


enum E_EFFECT_KIND
{
	JUMP_EFFECT,

	MAX_EFFECT_KIND
};


class EffectManager
{
public:
	EffectManager();
	virtual ~EffectManager();

	static	HRESULT	Init();
	static	void	Uninit();
	void	Update();
	void	Draw3D();
	void	Draw2D();

	static void CreateJumpEffect(GameObject* pObj);
	static void	CreateSandSmoke(DirectX::XMFLOAT3 pos, int num, float speed);

	static void ActiveConcentedLine(bool active);

private:

private:
	// 3Dビルボードエフェクト
	static List<JumpEffect>* m_pJumpEffectList;
	static SandSmoke*	m_pSandSmoke;
	// 2Dエフェクト
	static ConcentratedLine*	m_pConcentrateLine;
};

