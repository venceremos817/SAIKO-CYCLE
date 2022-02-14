#pragma once

#include "camera.h"
#include "board.h"

class CameraInverse
{
public:
	CameraInverse();
	virtual ~CameraInverse();

	virtual	HRESULT	Init();
	virtual	void	Uninit();
	virtual	void	Update();

	static	void	SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	static DirectX::XMMATRIX GetInversMatrix() { return m_InversMatrix; }

protected:
	static Camera*	m_pCamera;
	static DirectX::XMMATRIX	m_InversMatrix;
};

