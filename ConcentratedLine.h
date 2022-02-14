#pragma once

#include "board.h"
#include "Texture.h"

class ConcentratedLine
{
public:
	ConcentratedLine();
	virtual ~ConcentratedLine();

	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

	void	Active(bool active) { m_active = active; }

private:
	Board*	m_pBoard;
	ID3D11ShaderResourceView*	m_pTexture;
	UINT	m_Frame;
	int		m_AnimIdx;
	bool	m_active;
};

