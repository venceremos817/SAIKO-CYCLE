#include "Obstacle.h"

Model* Obstacle::m_pModel = nullptr;


namespace ObstacleState
{
	const float FLY_SPEED_COEFFICIENT = 10.0f / 60.0f;			// ������ё��x�̌W��
	const float FLY_MIN_SPEED = 20.0f / 60.0f;
	const int	FLY_FRAME = 30 * 60;
	const float	GRAVITY_ACC = -0.098f / 60.0f;
	const float ROT_SPEED = acosf(-1.0f) * 2 / 60;
	const float KILL_Y = -1000.0f;
}

Obstacle::Obstacle()
	: m_flyFrame(0)
{
	// �I�u�W�F�N�g����
	SetObjectType(E_ObjectType::TYPE_OBSTACLE);
	SetCollisionType(E_ObjectCollisionType::COLLISION_TYPE_DYNAMIC);

	// �q�b�g�{�b�N�X�ݒ�
	m_pHitBox->SetPos(0.000000000f, 1.30000019f, 0.000000000f);
	m_pHitBox->SetSize(9.70000076f, 2.40000010f, 1.40000010f);
	m_pHitBox->SetRot(0, 0, 0);
}

Obstacle::~Obstacle()
{

}


HRESULT Obstacle::Init()
{
	HRESULT hr = S_OK;
	if (m_pModel == nullptr)
	{
		m_pModel = new Model;
		m_pModel->LoadModel("Assets/Model/kon_tx_RE.fbx");
	}

	return hr;
}


void Obstacle::Uninit()
{
	if (m_pModel != nullptr)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
}


void Obstacle::Update()
{
	switch (m_state)
	{
	case STATE_BLOW_AWAY:
	{
		BlowAway();
	}
		break;

	default:
		break;
	}
}


void Obstacle::Draw()
{
	int a = 0;
	SetWorld();
	m_pModel->Draw();
#ifdef TEST_DEBUG
	m_pHitBox->testDraw(m_pos, m_size, m_rot);
#endif // TEST_DEBUG
}


void Obstacle::BlowAway()
{
	// �������
	if (m_flyFrame == 0)
	{
		// ������ѕ����������_���ɂ���	(Y�����͐�)
		DirectX::XMVECTOR flyDir = DirectX::XMVectorSet(rand() - RAND_MAX / 2.0f, rand(), rand() - RAND_MAX / 2.0f, 0);
		flyDir = DirectX::XMVector3Normalize(flyDir);
		float len;
		DirectX::XMStoreFloat(&len, DirectX::XMVector3Length(flyDir));
		// ���x�v�Z
		DirectX::XMVECTOR vMove = DirectX::XMLoadFloat3(&m_move);
		float move;
		DirectX::XMStoreFloat(&move, DirectX::XMVector3Length(vMove));
		// ���x�𐁂���ѕ����x�N�g���ɂ�����
		flyDir = DirectX::XMVectorScale(flyDir, move*ObstacleState::FLY_SPEED_COEFFICIENT + ObstacleState::FLY_MIN_SPEED);
		// �K�p
		DirectX::XMStoreFloat3(&m_move, flyDir);
		DirectX::XMStoreFloat(&len, DirectX::XMVector3Length(flyDir));

		SetMove(m_move);

		// ������݉�]����
		DirectX::XMVECTOR vRotSpd = DirectX::XMVectorSet(rand() - RAND_MAX / 2.0f, rand() - RAND_MAX / 2.0f, rand() - RAND_MAX / 2.0f, 0);
		vRotSpd = DirectX::XMVector3Normalize(vRotSpd);
		vRotSpd = DirectX::XMVectorScale(vRotSpd, ObstacleState::ROT_SPEED);
		DirectX::XMStoreFloat3(&m_rotSpd, vRotSpd);
	}

	// �������
	m_move.y += ObstacleState::GRAVITY_ACC;		// �d�͂͂����Ƃ�

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	SetPos(m_pos);
	m_rot.x += m_rotSpd.x;
	m_rot.y += m_rotSpd.y;
	m_rot.z += m_rotSpd.z;
	SetRot(m_rot);

	m_flyFrame++;

	// ������яI��
	if (m_flyFrame > ObstacleState::FLY_FRAME || m_pos.y < ObstacleState::KILL_Y)
	{
		m_flyFrame = 0;
		m_state = E_STATE::STATE_STOP;
	}
}