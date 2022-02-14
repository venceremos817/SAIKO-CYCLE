#pragma once

//===================================================
//	�Q�[�����ɑ��݂���Q�[���I�u�W�F�N�g�̊��N���X
//===================================================

//===== �C���N���[�h�� =====
#include "HitBox.h"
#include "DirectX.h"
#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"
#include "myVector.h"
#include "CMyColor.h"

// �����蔻������{����Ƃ��̃I�u�W�F�N�g�̎��
enum E_ObjectCollisionType
{
	COLLISION_TYPE_STATIC,	// ���~����
	COLLISION_TYPE_DYNAMIC,	// ����
	COLLISION_TYPE_OVERRAP,	// �ђʂ���

	COLLISION_TYPE_MAX
};

enum E_ObjectCollider
{
	COLLIDER_SEGMENT,	// ����
	COLLIDER_PLANE,		// ����
	COLLIDER_AABB,		// ���W���ɉ������Ȓ�����
	COLLIDER_OBB,		// AABB���X��������
	COLLIDER_SPHERE,	// ��

	COLLISION_FORM_MAX
};

enum E_ObjectType
{
	TYPE_PLAYER,		// �v���C���[
	TYPE_PLANE,			// �X�e�[�W��̏��A�W�����v��Ȃ�
	TYPE_OBSTACLE,		// ��Q��(�Ԃ��Ƃ�ł��j

	TYPE_MAX
};


enum E_STATE
{
	STATE_STOP,
	STATE_BLOW_AWAY,

	STATE_RUN,
	STATE_TURN_LEFT,
	STATE_TURN_RIGHT,
	STATE_SLIP,
	STATE_STANT,
	STATE_AUTO_RUN,

	STATE_MAX
};



class GameObject
{
public:
	GameObject();
	virtual	~GameObject();

	virtual HRESULT Init();
	virtual	void	Uninit();
	virtual	void	Update();
	virtual	void	Draw();

	virtual void	OnCollision() {};

	void	SetWorld();

	DirectX::XMFLOAT3	GetPos();
	DirectX::XMFLOAT3	GetSize();
	DirectX::XMFLOAT3	GetRot();
	DirectX::XMFLOAT3	GetMove();

	E_ObjectCollisionType	GetCollisionType();
	E_ObjectCollider		GetCollisionForm();
	E_ObjectType			GetType();
	E_STATE					GetState();

	void	SetPos(float x, float y, float z);
	void	SetPos(DirectX::XMFLOAT3 pos);
	void	SetSize(DirectX::XMFLOAT3 size);
	void	SetSize(float x, float y, float z);
	void	SetRot(DirectX::XMFLOAT3 rot);
	void	SetRotX(float rotX);
	void	SetRotY(float rotY);
	void	SetRotZ(float rotZ);
	void	SetMove(DirectX::XMFLOAT3 move);
	void	SetMaterial(DirectX::XMFLOAT4 RGBA);
	void	SetMaterial(float r, float g, float b, float a);

	void	SetCollisionType(E_ObjectCollisionType colType);
	void	SetCollisionForm(E_ObjectCollider colForm);
	void	SetObjectType(E_ObjectType type);
	void	SetState(E_STATE state);

	HitBox	*GetHitBox();

	bool		m_isGround;
protected:
	DirectX::XMFLOAT3	m_pos;
	DirectX::XMFLOAT3	m_size;
	DirectX::XMFLOAT3	m_rot;
	DirectX::XMFLOAT3	m_move;
	E_ObjectCollisionType	m_collisionType;
	E_ObjectCollider		m_collisionForm;
	E_ObjectType			m_objType;
	CMyColor	m_MatColor;
	E_STATE		m_state;
	HitBox*		m_pHitBox;

private:

};