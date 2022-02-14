//===== �C���N���[�h�� =====
#include "Collision.h"
#include "CMyColor.h"


List<GameObject>* Collision::m_pLIST[2];
List<TargetPoint>* Collision::m_pTpList[E_RANE::MAX_RANE];
int Collision::m_registerObjNum = 0;
Player* Collision::m_pPlayer = nullptr;

Collision::Collision()
{
	for (int i = 0; i < 2; i++)
	{
		m_pLIST[i] = nullptr;
	}
}


Collision::~Collision()
{
	Uninit();
}



HRESULT Collision::Init()
{
	m_pLIST[0] = new List<GameObject>;
	m_pLIST[1] = new List<GameObject>;

	return S_OK;
}


void Collision::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_pLIST[i] != nullptr)
		{
			m_pLIST[i]->ClearList();
			delete m_pLIST[i];
			m_pLIST[i] = nullptr;
		}
	}
}


void Collision::Update()
{
	// ���X�g�̐擪�̃m�[�h����肾��
	Node<GameObject> *pNA = m_pLIST[0]->GetHead();
	Node<GameObject> *pNB = m_pLIST[1]->GetHead();

	// �����蔻�菈��
	for (int i = 0; i < m_registerObjNum; i++, pNA = m_pLIST[0]->GetNext(pNA), pNB = m_pLIST[1]->GetNext(pNB))
	{
		// �m�[�h����I�u�W�F�N�g�����o��
		GameObject *pOA = pNA->GetObj();
		GameObject *pOB = pNB->GetObj();

		// �o�^����Ă��Ȃ��f�[�^�͎��{���Ȃ�
		if (pOA == nullptr || pOB == nullptr)
		{
			continue;
		}

		//----- �Փ˔��� -----
		bool isHit = false;

		isHit = IsHitOBB_OBB(pOA, pOB);

		if (isHit)
		{
			//----- �Փˎ��̋��� -----
			E_ObjectCollisionType aColType = pOA->GetCollisionType();
			E_ObjectCollisionType bColType = pOB->GetCollisionType();
			E_ObjectType aObjType = pOA->GetType();
			E_ObjectType bObjType = pOB->GetType();

			// dynamic - static
			if (aColType == COLLISION_TYPE_DYNAMIC && bColType == COLLISION_TYPE_STATIC)
			{
				Push(pOA, pOB);
			}
			else if (bColType == COLLISION_TYPE_DYNAMIC && aColType == COLLISION_TYPE_STATIC)
			{
				Push(pOB, pOA);
			}

			// dynamic - dynamic
			if (aColType == COLLISION_TYPE_DYNAMIC && bColType == COLLISION_TYPE_DYNAMIC)
			{
				if (aObjType == TYPE_PLAYER && bObjType == TYPE_OBSTACLE)
				{
					pOA->SetState(E_STATE::STATE_SLIP);
					if (pOB->GetState() != E_STATE::STATE_BLOW_AWAY)
						pOB->SetMove(pOA->GetMove());
					pOB->SetState(E_STATE::STATE_BLOW_AWAY);
				}
				else if (bObjType == TYPE_OBSTACLE && aObjType == TYPE_PLAYER)
				{
					if (pOA->GetState() != E_STATE::STATE_BLOW_AWAY)
						pOA->SetMove(pOB->GetMove());
					pOA->SetState(E_STATE::STATE_BLOW_AWAY);
					pOB->SetState(E_STATE::STATE_SLIP);
				}

			}
	
		}
	}

	m_pLIST[0]->ClearList();
	m_pLIST[1]->ClearList();
	m_registerObjNum = 0;

	// �v���C���[�ƖڕW�n�_
	FunctionPlayer_TP();
}



void Collision::Register(GameObject *pA, GameObject *pB)
{
	m_pLIST[0]->AddObject(pA);
	m_pLIST[1]->AddObject(pB);

	++m_registerObjNum;
}

void Collision::Register(List<TargetPoint>* pRpList, E_RANE rane)
{
	m_pTpList[rane] = pRpList;
}

void Collision::Register(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}


bool Collision::IsHitSegment_Plane(GameObject *pA, GameObject *pB)
{
	// ����
	struct Segment
	{
		DirectX::XMFLOAT3 StartPos;	// �n�_
		DirectX::XMFLOAT3 EndPos;		// �I�_
	};
	// ��������
	struct PLANE
	{
		myVector3 Normal;		// ���ʂ̖@��
		float	fDistance;		// ���[���h���_����̋���
	};

	// �v�Z�Ɏg���v�f
	DirectX::XMFLOAT3 aMove = pA->GetMove();
	DirectX::XMFLOAT3 bPos = pB->GetPos();

	Segment seg;
	seg.EndPos = pA->GetPos();
	seg.StartPos = DirectX::XMFLOAT3(seg.EndPos.x - aMove.x, seg.EndPos.y - aMove.y, seg.EndPos.z - aMove.z);
	PLANE plane;
	plane.fDistance = bPos.x*bPos.x + bPos.y*bPos.y + bPos.z*bPos.z;
	plane.Normal(0, 1, 0);		// ���ʂ̖@���B�Ƃ肠����������ŁB��X�I�u�W�F�N�g�̃����o�ɂ��ׂ�����...
	myVector3::Rot(&plane.Normal, pB->GetRot());		// �@�����I�u�W�F�N�g�̌X������]
	myVector3 vecS(seg.StartPos.x - bPos.x, seg.StartPos.y - bPos.y, seg.StartPos.z - bPos.z);
	myVector3 vecE(seg.EndPos.x - bPos.x, seg.EndPos.y - bPos.y, seg.EndPos.z - bPos.z);

	float dotS = myVector3::dot(vecS, plane.Normal);
	float dotE = myVector3::dot(vecE, plane.Normal);

	if (dotE * dotS <= 0)
	{
#ifdef TEST_DEBUG
		// �Փ˂��Ă���
		pA->SetMaterial(1, 0, 0, 1);
		pB->SetMaterial(1, 0, 0, 1);
#endif // TEST_DEBUG
		return true;
	}

#ifdef TEST_DEBUG
	// �Փ˂��ĂȂ�
	pA->SetMaterial(1, 1, 1, 1);
	pB->SetMaterial(1, 1, 1, 1);
#endif // TEST_DEBUG
	return false;
}

bool Collision::IsHitAABB_AABB(GameObject *pA, GameObject *pB)
{
	// �����̓��m�̓����蔻��
	// ���S�܂ł̋��� < �����̑傫���𑫂����킹����
	DirectX::XMFLOAT3 aPos = pA->GetPos();
	DirectX::XMFLOAT3 bPos = pB->GetPos();
	DirectX::XMFLOAT3 aSize = pA->GetSize();
	DirectX::XMFLOAT3 bSize = pB->GetSize();

	DirectX::XMFLOAT3 distance(
		fabsf(bPos.x - aPos.x),
		fabsf(bPos.y - aPos.y),
		fabsf(bPos.z - aPos.z)
	);
	bool hitX = distance.x < (aSize.x + bSize.x)*0.5f;
	bool hitY = distance.y < (aSize.y + bSize.y)*0.5f;
	bool hitZ = distance.z < (aSize.z + bSize.z)*0.5f;

	return (hitX && hitY && hitZ);
}

// OBB���m�̏Փ˔���
// �Q�l�Fhttp://marupeke296.com/COL_3D_No13_OBBvsOBB.html
bool Collision::IsHitOBB_OBB(GameObject *pA, GameObject *pB)
{
	// �e�����x�N�g���̊m��
	myVector3 NAe1 = pA->GetHitBox()->GetDirectW(0, pA->GetRot()), Ae1 = NAe1 * (pA->GetHitBox()->GetSize(pA->GetSize()).x * 0.5f);
	myVector3 NAe2 = pA->GetHitBox()->GetDirectW(1, pA->GetRot()), Ae2 = NAe2 * (pA->GetHitBox()->GetSize(pA->GetSize()).y * 0.5f);
	myVector3 NAe3 = pA->GetHitBox()->GetDirectW(2, pA->GetRot()), Ae3 = NAe3 * (pA->GetHitBox()->GetSize(pA->GetSize()).z * 0.5f);
	myVector3 NBe1 = pB->GetHitBox()->GetDirectW(0, pB->GetRot()), Be1 = NBe1 * (pB->GetHitBox()->GetSize(pB->GetSize()).x * 0.5f);
	myVector3 NBe2 = pB->GetHitBox()->GetDirectW(1, pB->GetRot()), Be2 = NBe2 * (pB->GetHitBox()->GetSize(pB->GetSize()).y * 0.5f);
	myVector3 NBe3 = pB->GetHitBox()->GetDirectW(2, pB->GetRot()), Be3 = NBe3 * (pB->GetHitBox()->GetSize(pB->GetSize()).z * 0.5f);
	myVector3 Interval(
		pA->GetHitBox()->GetPos(pA->GetPos(), pA->GetSize(), pA->GetRot()).x - pB->GetHitBox()->GetPos(pB->GetPos(), pB->GetSize(), pB->GetRot()).x,
		pA->GetHitBox()->GetPos(pA->GetPos(), pA->GetSize(), pA->GetRot()).y - pB->GetHitBox()->GetPos(pB->GetPos(), pB->GetSize(), pB->GetRot()).y,
		pA->GetHitBox()->GetPos(pA->GetPos(), pA->GetSize(), pA->GetRot()).z - pB->GetHitBox()->GetPos(pB->GetPos(), pB->GetSize(), pB->GetRot()).z
	);

#ifdef TEST_DEBUG
	// �Փ˂��ĂȂ�
	pA->SetMaterial(1, 1, 1, 1);
	pB->SetMaterial(1, 1, 1, 1);
#endif // TEST_DEBUG

	// ������:Ae1
	float rA = myVector3::GetLength(Ae1);
	float rB = myVector3::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabsf(myVector3::dot(Interval, NAe1));
	if (L > rA + rB)
	{
		return false;	// �Փ˂��ĂȂ�
	}

	// ������:Ae2
	rA = myVector3::GetLength(Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, NAe2));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:Ae3
	rA = myVector3::GetLength(Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, NAe3));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:Be1
	rA = myVector3::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = myVector3::GetLength(Be1);
	L = fabsf(myVector3::dot(Interval, NBe1));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:Be2
	rA = myVector3::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = myVector3::GetLength(Be2);
	L = fabsf(myVector3::dot(Interval, NBe2));
	if (L > rA + rB)
	{
		return false;
	}

	//������:Be3
	rA = myVector3::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = myVector3::GetLength(Be3);
	L = fabsf(myVector3::dot(Interval, NBe3));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C11
	myVector3 Cross;
	Cross = myVector3::cross(NAe1, NBe1);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C12
	Cross = myVector3::cross(NAe1, NBe2);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C13
	Cross = myVector3::cross(NAe1, NBe3);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C21
	Cross = myVector3::cross(NAe2, NBe1);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C22
	Cross = myVector3::cross(NAe2, NBe2);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C23
	Cross = myVector3::cross(NAe2, NBe3);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C31
	Cross = myVector3::cross(NAe3, NBe1);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C32
	Cross = myVector3::cross(NAe3, NBe2);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// ������:C33
	Cross = myVector3::cross(NAe3, NBe3);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}
#ifdef TEST_DEBUG
	// �Փ˂��Ă���
	pA->SetMaterial(0, 1, 0, 1);
	pB->SetMaterial(0, 1, 0, 1);
#endif // TEST_DEBUG
	// �������ʂ����݂��Ȃ��̂ŏՓ˂��Ă���
	return true;
}


// XMFLOAT3�^��XMVECTOR�^�ɕϊ����ĕԂ�
DirectX::XMVECTOR ConvertXMVECTOR(DirectX::XMFLOAT3 xmfloat3)
{
	return DirectX::XMVectorSet(xmfloat3.x, xmfloat3.y, xmfloat3.z, 0.0f);
};


void Collision::Push(GameObject *pDynamic, GameObject *pStatic)
{
	// �����蔻����Ƃ�_���v�Z(�v���C���[�̑O����)
	DirectX::XMVECTOR dHitPos = ConvertXMVECTOR(pDynamic->GetHitBox()->GetPos(pDynamic->GetPos(), pDynamic->GetSize(), pDynamic->GetRot()));	// dynamic�̒��S���W
	DirectX::XMVECTOR dSize = ConvertXMVECTOR(pDynamic->GetHitBox()->GetSize(pDynamic->GetSize()));		// dynamic�̃T�C�Y
	DirectX::XMVECTOR dMove = ConvertXMVECTOR(pDynamic->GetMove());		// dynamic�̈ړ���
	DirectX::XMFLOAT3 dRot = pDynamic->GetHitBox()->GetRot(pDynamic->GetRot());						// dynamic�̌X��
	dSize = DirectX::XMVector3Transform(dSize, DirectX::XMMatrixRotationX(dRot.x) * DirectX::XMMatrixRotationY(dRot.y)	* DirectX::XMMatrixRotationZ(dRot.z));	// �X���ɍ��킹��size����]����
	dHitPos = DirectX::XMVectorAdd(dHitPos, DirectX::XMVectorSet(0, -DirectX::XMVectorGetY(dSize)*0.5f, DirectX::XMVectorGetZ(dSize)*0.5f, 0));		// �O�����Ɉړ�
	// �ړ��O�̓_
	DirectX::XMVECTOR dPreHitPos = DirectX::XMVectorSubtract(dHitPos, dMove);	// �ړ��ʂ������đO�̍��W�����߂�

	// ���ʂ̂Ƃ���_���v�Z
	DirectX::XMVECTOR sPos = ConvertXMVECTOR(pStatic->GetHitBox()->GetPos(pStatic->GetPos(), pStatic->GetSize(), pStatic->GetRot()));	// static�̒��S���W
	DirectX::XMVECTOR sSize = ConvertXMVECTOR(pStatic->GetHitBox()->GetSize(pStatic->GetSize()));	// static�̃T�C�Y
	DirectX::XMFLOAT3 sRot = pStatic->GetHitBox()->GetRot(pStatic->GetRot());						// static�̌X��
	DirectX::XMVECTOR vsNormal = DirectX::XMVectorSet(0, 1, 0, 0);	// �@��(������ɐݒ�)
	// �@����static�̌X���ɑΉ�������
	vsNormal = DirectX::XMVector3Transform(vsNormal, DirectX::XMMatrixRotationX(sRot.x)	* DirectX::XMMatrixRotationY(sRot.y) * DirectX::XMMatrixRotationZ(sRot.z));
	sSize = DirectX::XMVectorMultiply(sSize, DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0));	// size�𔼕��ɂ���
	float planeDis = DirectX::XMVectorGetY(sSize);
	sPos = DirectX::XMVectorAdd(sPos, DirectX::XMVectorMultiply(vsNormal, DirectX::XMVectorSet(planeDis, planeDis, planeDis, 0)));			// �@��������size���ړ������_�����ʏ�̓_

	// ���ς����߂邽�߂̃x�N�g��
	DirectX::XMVECTOR vStart = DirectX::XMVectorSubtract(dPreHitPos, sPos);	// ���ʂ̓_����ړ��O�̓_�ւ̃x�N�g��
	DirectX::XMVECTOR vEnd = DirectX::XMVectorSubtract(dHitPos, sPos);		// ���ʂ̓_����ړ���̓_�ւ̃x�N�g��
	float dotS, dotE;
	DirectX::XMStoreFloat(&dotS, DirectX::XMVector3Dot(vStart, vsNormal));
	DirectX::XMStoreFloat(&dotE, DirectX::XMVector3Dot(vEnd, vsNormal));
	dotE *= 1.1f;

	if (dotS * dotE <= 0)
	{
		//--- �Ԃ����Ă��� ---
		// �����o��
		float PushDis = -dotE;
		DirectX::XMFLOAT3 dPos = pDynamic->GetPos();
		dPos.x += PushDis * DirectX::XMVectorGetX(vsNormal);
		dPos.y += PushDis * DirectX::XMVectorGetY(vsNormal);
		dPos.z += PushDis * DirectX::XMVectorGetZ(vsNormal);
		pDynamic->SetPos(dPos);

		// �ړ���
		DirectX::XMFLOAT3 move = pDynamic->GetMove();
		move.x -= (fabsf(DirectX::XMVectorGetX(vsNormal)) * move.x)*0.1f;
		move.y -= (fabsf(DirectX::XMVectorGetY(vsNormal)) * move.y)*0.1f;
		move.z -= (fabsf(DirectX::XMVectorGetZ(vsNormal)) * move.z)*0.1f;
		pDynamic->SetMove(move);

		pDynamic->m_isGround = true;
	}
}


DirectX::XMFLOAT3 convertF2toF3(DirectX::XMFLOAT2 fl2)
{
	return DirectX::XMFLOAT3(fl2.x, 0, fl2.y);
}

void Collision::FunctionPlayer_TP()
{
	// �E���܏�ԏo�Ȃ��Ȃ�
	if (m_pPlayer->GetState() != E_STATE::STATE_TURN_LEFT&&m_pPlayer->GetState() != E_STATE::STATE_TURN_RIGHT)
	{
		// �G���[�h�~�p��
		Node<TargetPoint>* memTP = m_pPlayer->GetTargetPoint();
		// TP���v���C���[�����ɂ��鎞�ATP���v���C���[�̑O�ɗ���܂�TP�𑗂�
		while (true)
		{
			if (m_pPlayer->GetTargetPoint() == nullptr || m_pPlayer->GetTargetPoint()->GetObj() == nullptr)
			{
				m_pPlayer->SetNextTargetPoint(memTP);
				break;
			}

			// �v���C���[�̉H�ɂȂ�悤�ȃx�N�g��
			DirectX::XMVECTOR vPlayerWing = DirectX::XMVectorSet(1, 0, 0, 0);
			vPlayerWing = DirectX::XMVector3Transform(vPlayerWing, DirectX::XMMatrixRotationY(m_pPlayer->GetRot().y));
			vPlayerWing = DirectX::XMVectorSet(DirectX::XMVectorGetX(vPlayerWing), DirectX::XMVectorGetZ(vPlayerWing), 0, 0);
			// �v���C���[����TP�ւ̃x�N�g��
			DirectX::XMVECTOR vPlayerToTP = DirectX::XMVectorSubtract(
				DirectX::XMLoadFloat2(&m_pPlayer->GetTargetPoint()->GetObj()->GetPos()),
				DirectX::XMVectorSet(m_pPlayer->GetPos().x, m_pPlayer->GetPos().z, 0, 0));
			// �O��
			float cross;
			DirectX::XMStoreFloat(&cross, DirectX::XMVector2Cross(vPlayerWing, vPlayerToTP));
			if (cross <= 0.0f)
			{
				m_pPlayer->SetNextTargetPoint(m_pPlayer->GetTargetPoint()->GetNext());
				memTP = m_pPlayer->GetTargetPoint();
			}
			else
			{
				break;
			}
		}
	}
	else if (m_pPlayer->GetState() == E_STATE::STATE_TURN_LEFT || m_pPlayer->GetState() == E_STATE::STATE_TURN_RIGHT)	// �E���܎�
	{
		bool isHit;
		DirectX::XMFLOAT3 playerCurPos = m_pPlayer->GetPos();
		DirectX::XMFLOAT3 playerPrePos(
			playerCurPos.x - m_pPlayer->GetMove().x,
			playerCurPos.y - m_pPlayer->GetMove().y,
			playerCurPos.z - m_pPlayer->GetMove().z
		);
		Node<TargetPoint>* tpA = m_pTpList[m_pPlayer->GetNextRane()]->GetHead();
		Node<TargetPoint>* tpB = tpA->GetNext();
		DirectX::XMFLOAT3 PointA;
		DirectX::XMFLOAT3 PointB;

		while (tpA != nullptr && tpB != nullptr)
		{
			PointA = convertF2toF3(tpA->GetObj()->GetPos());
			PointB = convertF2toF3(tpB->GetObj()->GetPos());

			isHit = IsHitXZSegment_XZSegment(playerCurPos, playerPrePos, PointA, PointB);
			if (isHit)
			{
				m_pPlayer->SetState(E_STATE::STATE_RUN);
				m_pPlayer->SetNextTargetPoint(tpB);
				m_pPlayer->SetCurRane(tpB->GetObj()->GetRane());
				m_pPlayer->SetNextRane(tpB->GetObj()->GetRane());
				break;
			}
			tpA = tpB;
			tpB = tpA->GetNext();
		}

	}
}


bool Collision::IsHitPlayer_TP(TargetPoint* pRp)
{
	// TP���v���C���[�����ɂ�������O���ɂ���TP�܂ő���
	const float RpRadius = 1.0f;
	DirectX::XMFLOAT2 PlayerPos = DirectX::XMFLOAT2(m_pPlayer->GetPos().x, m_pPlayer->GetPos().z);		// �v���C���[�̍��W	x,z���ʂ݂̂ł���
	DirectX::XMFLOAT2 PlayerPrePos = DirectX::XMFLOAT2(PlayerPos.x - m_pPlayer->GetMove().x, PlayerPos.y - m_pPlayer->GetMove().z);
	DirectX::XMFLOAT2 RpPos = pRp->GetPos();				// ���[�g�|�C���g�̍��W

	return CheckCollisionCircleToLine(RpPos, RpRadius, PlayerPrePos, PlayerPos);
}


// �_�Ɖ~�̓����蔻��
bool Collision::CheckCollisionPointToCircle(float PointX, float PointY, float CirclePosX, float CirclePosY, float radius)
{
	float distance;		// �_�Ɖ~�̋���^2

	distance = (PointX - CirclePosX)*(PointX - CirclePosX) + (PointY - CirclePosY)*(PointY - CirclePosY);
	if (distance <= radius)
		return true;

	return false;
}


bool Collision::CheckCollisionCircleToCircle(DirectX::XMFLOAT2 CAPos, float CARadius, DirectX::XMFLOAT2 CBPos, float CBRadius)
{
	float distance;		// �~�Ɖ~�̋���

	distance = (CAPos.x - CBPos.x)*(CAPos.x - CBPos.x) + (CAPos.y - CBPos.y)*(CBPos.y - CBPos.y);
	if (distance <= CARadius + CBRadius)
	{
		return true;
	}

	return false;
}


bool Collision::CheckCollisionPoleToPole(DirectX::XMFLOAT3 PAPos, float PARadius, float PAHeight, DirectX::XMFLOAT3 PBPos, float PBRadius, float PBHeight)
{
	bool hit;
	DirectX::XMFLOAT2 CAPos(PAPos.x, PAPos.z);
	DirectX::XMFLOAT2 CBPos(PBPos.x, PBPos.z);

	hit = CheckCollisionCircleToCircle(CAPos, PARadius, CBPos, PBRadius);
	if (!hit)
		return false;

	float ATop = PAPos.y + PAHeight / 2;
	float ABottom = PAPos.y - PAHeight / 2;
	float BTop = PBPos.y + PBHeight / 2;
	float BBottom = PBPos.y - PBHeight / 2;

	if (ATop < BBottom)
		return false;
	if (ABottom > BTop)
		return false;

	return true;
}


// �����Ɖ~�̓����蔻��
bool Collision::CheckCollisionCircleToLine(DirectX::XMFLOAT2 CPos, float CRadius, DirectX::XMFLOAT2 LStartPos, DirectX::XMFLOAT2 LEndPos)
{
	DirectX::XMVECTOR SE = DirectX::XMVectorSet(LEndPos.x - LStartPos.x, LEndPos.y - LStartPos.y, 0, 0);	// �n�_����I�_��
	DirectX::XMVECTOR SC = DirectX::XMVectorSet(CPos.x - LStartPos.x, CPos.y - LStartPos.y, 0, 0);	// �n�_����~�̒��S��
	DirectX::XMVECTOR EC = DirectX::XMVectorSet(CPos.x - LEndPos.x, CPos.y - LEndPos.y, 0, 0);		// �n�_����~�̒��S��

	SE = DirectX::XMVector2Normalize(SE);

	// �~���璼���ւ̍ŒZ����
	float ShortestLength;
	DirectX::XMStoreFloat(&ShortestLength, DirectX::XMVector2Cross(SE, SC));

	if (ShortestLength < 0)
		ShortestLength *= -1.0f;

	// ���a�̕����Z���Ȃ瓖�����Ă���\���͂Ȃ�
	if (CRadius < ShortestLength)
		return false;

	// �~���������ɂ��邩���ׂ�
	float innerCSE, innerCES;
	DirectX::XMStoreFloat(&innerCSE, DirectX::XMVector2Dot(SC, SE));
	DirectX::XMStoreFloat(&innerCES, DirectX::XMVector2Dot(EC, SE));

	// ���ς̐ς����Ȃ������
	if (innerCES * innerCSE < 0)
		return true;

	// �����̒[���~�Ɋ܂܂�Ă��邩���ׂ�
	if (CheckCollisionPointToCircle(LStartPos.x, LStartPos.y, CPos.x, CPos.y, CRadius))		// �n�_
		return true;

	if (CheckCollisionPointToCircle(LEndPos.x, LEndPos.y, CPos.x, CPos.y, CRadius))			// �I�_
		return true;

	return false;

}


bool Collision::IsHitXZSegment_XZSegment(DirectX::XMFLOAT3 aS, DirectX::XMFLOAT3 aE, DirectX::XMFLOAT3 bS, DirectX::XMFLOAT3 bE)
{
	DirectX::XMVECTOR aSaE = DirectX::XMVectorSet(aE.x - aS.x, aE.z - aS.z, 0, 0);
	DirectX::XMVECTOR aSbS = DirectX::XMVectorSet(bS.x - aS.x, bS.z - aS.z, 0, 0);
	DirectX::XMVECTOR aSbE = DirectX::XMVectorSet(bE.x - aS.x, bE.z - aS.z, 0, 0);

	DirectX::XMVECTOR bSbE = DirectX::XMVectorSet(bE.x - bS.x, bE.z - bS.z, 0, 0);
	DirectX::XMVECTOR bSaS = DirectX::XMVectorSet(aS.x - bS.x, aS.z - bS.z, 0, 0);
	DirectX::XMVECTOR bSaE = DirectX::XMVectorSet(aE.x - bS.x, aE.z - bS.z, 0, 0);

	float crossA, crossB;
	DirectX::XMStoreFloat(&crossA, DirectX::XMVector2Cross(aSaE, aSbS));
	DirectX::XMStoreFloat(&crossB, DirectX::XMVector2Cross(aSaE, aSbE));

	if (crossA * crossB >= 0.0f)
	{
		return false;
	}

	DirectX::XMStoreFloat(&crossA, DirectX::XMVector2Cross(bSbE, bSaS));
	DirectX::XMStoreFloat(&crossB, DirectX::XMVector2Cross(bSbE, bSaE));

	if (crossA * crossB >= 0.0f)
	{
		return false;
	}

	return true;
}


bool Collision::IsHitSphere(DirectX::XMFLOAT3 aPos, DirectX::XMFLOAT3 bPos, float aRadius, float bRadius)
{
	return
		(bPos.x - aPos.x)*(bPos.x - aPos.x) + (bPos.y - aPos.y)*(bPos.y - aPos.y) + (bPos.z - aPos.z)*(bPos.z - aPos.z)
		< (aRadius + bRadius)*(aRadius + bRadius);
}


float Collision::GetDistance(DirectX::XMFLOAT3 aPos, DirectX::XMFLOAT3 bPos)
{
	return sqrtf(
		(aPos.x - bPos.x)*(aPos.x - bPos.x) +
		(aPos.y - bPos.y)*(aPos.y - bPos.y) +
		(aPos.z - bPos.z)*(aPos.z - bPos.z)
	);
}

float Collision::GetDistance(GameObject* pA, GameObject* pB)
{
	return GetDistance(pA->GetPos(), pB->GetPos());
}

float Collision::GetDistance(DirectX::XMFLOAT3 pos, GameObject* pGameObj)
{
	return GetDistance(pos, pGameObj->GetPos());
}


#ifdef TEST_DEBUG


void Collision::TestDraw()
{
	for (int i = 0; i < E_RANE::MAX_RANE; i++)
	{
		if (m_pTpList[i] == nullptr)
			continue;

		Node<TargetPoint>* pNTp = m_pTpList[i]->GetHead();
		while (pNTp != nullptr)
		{
			SHADER->SetWorld(DirectX::XMMatrixScaling(0.02f, 200.0f, 0.02f) * DirectX::XMMatrixTranslation(pNTp->GetObj()->GetPos().x, 0, pNTp->GetObj()->GetPos().y));
			m_testCube.Draw();
			pNTp = pNTp->GetNext();
		}
	}
}

#endif // TEST_DEBUG