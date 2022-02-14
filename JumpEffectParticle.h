#pragma once

#include "board.h"
#include "GameObject.h"

class JumpEffectParticle
{
public:
	JumpEffectParticle();
	virtual ~JumpEffectParticle();

	static	HRESULT Init();
	static	void	Uninit();
	void	Update();
	void	Draw();

	void	SetPos(DirectX::XMFLOAT3 pos) { m_pos = pos; }
	void	SetSize(DirectX::XMFLOAT3 size) { m_size = size; }
	void	SetMove(DirectX::XMFLOAT3 move) { m_move = move; }
	void	SetFollowObj(GameObject* pObj) { m_pFollowObj = pObj; }

	bool	IsFinish();


private:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;
	DirectX::XMFLOAT3 m_move;
	int	m_frame;
	int m_AnimIdx;
	Board*	m_pBoard;
	GameObject*	m_pFollowObj;

	static ID3D11ShaderResourceView*	m_pTexture;

};

