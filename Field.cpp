//===== �C���N���[�h�� =====
#include "Field.h"


Field::Field()
{
	// �I�u�W�F�N�g�̓���
	SetObjectType(E_ObjectType::TYPE_PLANE);

	// �q�b�g�{�b�N�X
	m_pHitBox->SetPos(m_pos);
	m_pHitBox->SetSize(m_size);
	m_pHitBox->SetRot(m_rot);
}

Field::Field(DirectX::XMFLOAT3 size)
{
	SetSize(size);
	SetCollisionForm(COLLIDER_PLANE);
	SetObjectType(E_ObjectType::TYPE_PLANE);

	// �q�b�g�{�b�N�X
	m_pHitBox->SetPos(m_pos);
	m_pHitBox->SetSize(m_size);
	m_pHitBox->SetRot(m_rot);
}


Field::~Field()
{

}