#pragma once

//===== インクルード部 =====
#include <DirectXMath.h>

enum E_RANE
{
	LEFT,
	CENTER,
	RIGHT,

	MAX_RANE
};


class TargetPoint
{
public:
	TargetPoint();
	TargetPoint(DirectX::XMFLOAT2 pos);
	~TargetPoint();

	void SetPos(DirectX::XMFLOAT2 pos);
	void SetPos(float x, float z);
	void SetRane(E_RANE rane);
	DirectX::XMFLOAT2 GetPos();
	E_RANE GetRane();
private:
	DirectX::XMFLOAT2 m_pos;			// X,Zとする
	int	m_idx;
	E_RANE m_rane;
};

