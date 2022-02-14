#pragma once

#include "Shader.h"
#include "Texture.h"
#include "DrawBuffer.h"

class Board
{
public:
	// --- ŠÖ”
	Board();
	~Board();

	void Init();
	void Uninit();
	void Draw();

	void SetUV(int index, int splitX, int splitY);
	
private:
	// --- •Ï”
	ID3D11ShaderResourceView *m_ptexture;
	DrawBuffer m_BufferB;

	float Size;

};