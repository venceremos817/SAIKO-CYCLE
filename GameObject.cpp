//===== インクルード部 =====
#include "GameObject.h"

#include "DebugDefine.h"

GameObject::GameObject()
	: m_pos(0, 0, 0)
	, m_size(1, 1, 1)
	, m_rot(0, 0, 0)
	, m_move(0, 0, 0)
	, m_collisionType(COLLISION_TYPE_STATIC)
	, m_collisionForm(COLLIDER_PLANE)
	, m_state(E_STATE::STATE_STOP)
	, m_objType(TYPE_PLANE)
	, m_pHitBox(nullptr)
	, m_isGround(false)
{
	m_MatColor.SetRGBA(1, 1, 1, 1);
	if (m_pHitBox == nullptr)
	{
		m_pHitBox = new HitBox;
	}
}


GameObject::~GameObject()
{
	Uninit();
}



HRESULT GameObject::Init()
{
	return S_OK;
}


void GameObject::Uninit()
{
	if (m_pHitBox != nullptr)
	{
		delete m_pHitBox;
		m_pHitBox = nullptr;
	}
}


void GameObject::Update()
{

}


void GameObject::Draw()
{
	// 3Dの座標変換の基本は行列での計算を行う。
	// 例えば、モデルを小さくする、回転させる、移動させる場合
	// それぞれの変換行列を作成する必要がある。
	// それぞれの変換行列を掛け合わせた行列が最終的なワールド変換行列となる。
	// (ただし、掛け算の順番をしっかり考える必要あり。基本的には 拡縮→回転→移動 の順
	SetWorld();

#ifndef TEST_DEBUG
	//m_pCube->Draw();
#endif // !TEST_DEBUG
	SHADER->SetAmbient(DirectX::XMFLOAT4(1, 1, 1, 1));

#ifdef TEST_DEBUG
	if (m_pHitBox != nullptr)
	{
		m_pHitBox->testDraw(m_pos, m_size, m_rot);
	}
#endif // TEST_DEBUG

}


void GameObject::SetWorld()
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationX(m_rot.x) * DirectX::XMMatrixRotationY(m_rot.y) * DirectX::XMMatrixRotationZ(m_rot.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	SHADER->SetAmbient(m_MatColor.GetRGBA());
}


DirectX::XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
}


DirectX::XMFLOAT3 GameObject::GetSize()
{
	return	m_size;
}


DirectX::XMFLOAT3 GameObject::GetRot()
{
	return m_rot;
}


DirectX::XMFLOAT3 GameObject::GetMove()
{
	return m_move;
}


E_ObjectCollisionType GameObject::GetCollisionType()
{
	return m_collisionType;
}


E_ObjectCollider GameObject::GetCollisionForm()
{
	return m_collisionForm;
}


E_ObjectType GameObject::GetType()
{
	return m_objType;
}

E_STATE GameObject::GetState()
{
	return m_state;
}

void GameObject::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void GameObject::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}


void GameObject::SetSize(DirectX::XMFLOAT3 size)
{
	m_size = size;
}


void GameObject::SetSize(float x, float y, float z)
{
	m_size.x = x;
	m_size.y = y;
	m_size.z = z;
}


void GameObject::SetRot(DirectX::XMFLOAT3 rot)
{
	SetRotX(rot.x);
	SetRotY(rot.y);
	SetRotZ(rot.z);
}

void GameObject::SetRotX(float rotX)
{
	m_rot.x = rotX;

	while (m_rot.x > DirectX::XM_2PI)
		m_rot.x -= DirectX::XM_2PI;
	while (m_rot.x < -DirectX::XM_2PI)
		m_rot.x += DirectX::XM_2PI;
}

void GameObject::SetRotY(float rotY)
{
	m_rot.y = rotY;

	while (m_rot.y > DirectX::XM_2PI)
		m_rot.y -= DirectX::XM_2PI;
	while (m_rot.y < -DirectX::XM_2PI)
		m_rot.y += DirectX::XM_2PI;
}

void GameObject::SetRotZ(float rotZ)
{
	m_rot.z = rotZ;

	while (m_rot.z > DirectX::XM_2PI)
		m_rot.z -= DirectX::XM_2PI;
	while (m_rot.z < -DirectX::XM_2PI)
		m_rot.z += DirectX::XM_2PI;
}


void GameObject::SetMove(DirectX::XMFLOAT3 move)
{
	m_move = move;
}

void GameObject::SetMaterial(DirectX::XMFLOAT4 MatColor)
{
	m_MatColor.SetRGBA(MatColor);
}

void GameObject::SetMaterial(float r, float g, float b, float a)
{
	m_MatColor.SetRGBA(r, g, b, a);
}


void GameObject::SetCollisionType(E_ObjectCollisionType colType)
{
	m_collisionType = colType;
}


void GameObject::SetCollisionForm(E_ObjectCollider colForm)
{
	m_collisionForm = colForm;
}


void GameObject::SetState(E_STATE state)
{
	m_state = state;
}


void GameObject::SetObjectType(E_ObjectType type)
{
	m_objType = type;
}


HitBox* GameObject::GetHitBox()
{
	return m_pHitBox;
}


