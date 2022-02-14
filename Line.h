#ifndef __LINE_H__
#define __LINE_H__

//===== インクルード部 =====
#include "DrawBuffer.h"
#include <DirectXMath.h>

class Line
{
public:
	Line();
	~Line();

	void Draw();

	void SetLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end);

private:
	DirectX::XMFLOAT3	m_start;
	DirectX::XMFLOAT3	m_end;

	DrawBuffer	m_Buffer;
};

#endif // !__LINE_H__
