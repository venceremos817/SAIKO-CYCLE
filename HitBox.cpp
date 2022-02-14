#include "HitBox.h"
#include "Shader.h"

#ifdef TEST_DEBUG
#include "DirectX.h"
#endif // TEST_DEBUG




HitBox::HitBox()
	: m_pos(0, 0, 0)
	, m_size(1, 1, 1)
	, m_rot(0, 0, 0)
{

}

HitBox::HitBox(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 rot)
	: m_pos(pos)
	, m_size(size)
	, m_rot(rot)
{

}

HitBox::~HitBox()
{

}





void HitBox::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void HitBox::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}


void HitBox::SetSize(DirectX::XMFLOAT3 size)
{
	m_size = size;
}

void HitBox::SetSize(float x, float y, float z)
{
	m_size.x = x;
	m_size.y = y;
	m_size.z = z;
}


void HitBox::SetRot(DirectX::XMFLOAT3 rot)
{
	m_rot = rot;
}

void HitBox::SetRot(float x, float y, float z)
{
	m_rot.x = x;
	m_rot.y = y;
	m_rot.z = z;
}


DirectX::XMFLOAT3 HitBox::GetPos(DirectX::XMFLOAT3 objPos, DirectX::XMFLOAT3 objSize, DirectX::XMFLOAT3 objRot)
{
	DirectX::XMFLOAT3 retPos;
	DirectX::XMVECTOR hitBoxPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMMATRIX transform;

	transform = (DirectX::XMMatrixScaling(objSize.x, objSize.y, objSize.z) *
		DirectX::XMMatrixRotationX(objRot.x) * DirectX::XMMatrixRotationY(objRot.y) * DirectX::XMMatrixRotationZ(objRot.z) *
		DirectX::XMMatrixTranslation(objPos.x, objPos.y, objPos.z));
	hitBoxPos = DirectX::XMVector3Transform(hitBoxPos, transform);
	DirectX::XMStoreFloat3(&retPos, hitBoxPos);

	return retPos;
}


DirectX::XMFLOAT3 HitBox::GetSize(DirectX::XMFLOAT3 objSize)
{
	return DirectX::XMFLOAT3(m_size.x*objSize.x, m_size.y*objSize.y, m_size.z*objSize.z);
}


DirectX::XMFLOAT3 HitBox::GetRot(DirectX::XMFLOAT3 objRot)
{
	DirectX::XMFLOAT3 retRot;
	
	retRot.x = m_rot.x + objRot.x;
	retRot.y = m_rot.y + objRot.y;
	retRot.z = m_rot.z + objRot.z;

	return retRot;
}


myVector3 HitBox::GetDirectW(int elem,DirectX::XMFLOAT3 objRot)
{
	myVector3 Normal;
	switch (elem)
	{
	case 0:
		Normal(1, 0, 0);
		break;

	case 1:
		Normal(0, 1, 0);
		break;

	case 2:
		Normal(0, 0, 1);
		break;
	default:
		break;
	}
	
	myVector3::Rot(&Normal, GetRot(objRot));
	return Normal.GetNormalize();
}


#ifdef TEST_DEBUG
void HitBox::testDraw(DirectX::XMFLOAT3 objPos, DirectX::XMFLOAT3 objSize, DirectX::XMFLOAT3 objRot)
{
	DirectX::XMFLOAT3 Pos = GetPos(objPos, objSize, objRot);
	DirectX::XMFLOAT3 Size = GetSize(objSize);
	DirectX::XMFLOAT3 Rot = GetRot(objRot);

	SHADER->SetWorld(DirectX::XMMatrixScaling(Size.x, Size.y, Size.z)
		* DirectX::XMMatrixRotationX(Rot.x) * DirectX::XMMatrixRotationY(Rot.y) * DirectX::XMMatrixRotationZ(Rot.z)
		* DirectX::XMMatrixTranslation(Pos.x, Pos.y, Pos.z));
	SetCullingMode(CULL_WIREFRAME);
	m_TestCube.Draw();
	SetCullingMode(CULL_DEFAULT);
}

#endif // TEST_DEBUG
