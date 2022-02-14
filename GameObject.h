#pragma once

//===================================================
//	ゲーム内に存在するゲームオブジェクトの基底クラス
//===================================================

//===== インクルード部 =====
#include "HitBox.h"
#include "DirectX.h"
#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"
#include "myVector.h"
#include "CMyColor.h"

// 当たり判定を実施するときのオブジェクトの種類
enum E_ObjectCollisionType
{
	COLLISION_TYPE_STATIC,	// 制止する
	COLLISION_TYPE_DYNAMIC,	// 動く
	COLLISION_TYPE_OVERRAP,	// 貫通する

	COLLISION_TYPE_MAX
};

enum E_ObjectCollider
{
	COLLIDER_SEGMENT,	// 線分
	COLLIDER_PLANE,		// 平面
	COLLIDER_AABB,		// 座標軸に沿ったな直方体
	COLLIDER_OBB,		// AABBが傾いたもの
	COLLIDER_SPHERE,	// 球

	COLLISION_FORM_MAX
};

enum E_ObjectType
{
	TYPE_PLAYER,		// プレイヤー
	TYPE_PLANE,			// ステージ上の床、ジャンプ台など
	TYPE_OBSTACLE,		// 障害物(ぶっとんでく）

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