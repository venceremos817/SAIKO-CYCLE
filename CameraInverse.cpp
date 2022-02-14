#include "CameraInverse.h"

Camera*	CameraInverse::m_pCamera = nullptr;
DirectX::XMMATRIX CameraInverse::m_InversMatrix;


CameraInverse::CameraInverse()
{
	Init();
}


CameraInverse::~CameraInverse()
{
	Uninit();
}


HRESULT CameraInverse::Init()
{
	m_InversMatrix = DirectX::XMMatrixIdentity();

	return S_OK;
}


void CameraInverse::Uninit()
{

}


void CameraInverse::Update()
{
	//===== ƒJƒƒ‰‚É‘Î‚·‚é‰ñ“]‚ð‘Å‚¿Á‚·s—ñ‚ðì‚é
	m_InversMatrix = DirectX::XMMatrixInverse(nullptr, m_pCamera->GetViewMat());
	DirectX::XMFLOAT4X4 workMat;
	DirectX::XMStoreFloat4x4(&workMat, m_InversMatrix);

	workMat._41 = 0;
	workMat._42 = 0;
	workMat._43 = 0;
	// YŽ²ŒÅ’è
	//workMat._21 = 0;
	//workMat._22 = 1;
	//workMat._23 = 0;
	// XŽ²ŒÅ’è
	//workMat._11 = 1;
	//workMat._12 = 0;
	//workMat._13 = 0;
	// ZŽ²ŒÅ’è
	//workMat._31 = 0;
	//workMat._32 = 0;
	//workMat._33 = 1;

	m_InversMatrix = DirectX::XMLoadFloat4x4(&workMat);
}


