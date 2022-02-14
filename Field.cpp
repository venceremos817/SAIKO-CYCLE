//===== インクルード部 =====
#include "Field.h"


Field::Field()
{
	// オブジェクトの特性
	SetObjectType(E_ObjectType::TYPE_PLANE);

	// ヒットボックス
	m_pHitBox->SetPos(m_pos);
	m_pHitBox->SetSize(m_size);
	m_pHitBox->SetRot(m_rot);
}

Field::Field(DirectX::XMFLOAT3 size)
{
	SetSize(size);
	SetCollisionForm(COLLIDER_PLANE);
	SetObjectType(E_ObjectType::TYPE_PLANE);

	// ヒットボックス
	m_pHitBox->SetPos(m_pos);
	m_pHitBox->SetSize(m_size);
	m_pHitBox->SetRot(m_rot);
}


Field::~Field()
{

}