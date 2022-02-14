//===== インクルード部 =====
#include "CharacterBase.h"



CharacterBase::CharacterBase()
	: m_direction(0, 0)
{
	// キャラクターは動くオブジェクトのはず
	m_collisionType = COLLISION_TYPE_DYNAMIC;
}


CharacterBase::~CharacterBase()
{

}


void CharacterBase::Draw()
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationX(m_rot.x) *	DirectX::XMMatrixRotationY(m_rot.y) *DirectX::XMMatrixRotationZ(m_rot.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	SHADER->SetAmbient(m_MatColor.GetRGBA());
}