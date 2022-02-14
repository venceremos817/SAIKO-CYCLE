//===== インクルード部 =====
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
	// リストの先頭のノードを取りだす
	Node<GameObject> *pNA = m_pLIST[0]->GetHead();
	Node<GameObject> *pNB = m_pLIST[1]->GetHead();

	// 当たり判定処理
	for (int i = 0; i < m_registerObjNum; i++, pNA = m_pLIST[0]->GetNext(pNA), pNB = m_pLIST[1]->GetNext(pNB))
	{
		// ノードからオブジェクトを取り出す
		GameObject *pOA = pNA->GetObj();
		GameObject *pOB = pNB->GetObj();

		// 登録されていないデータは実施しない
		if (pOA == nullptr || pOB == nullptr)
		{
			continue;
		}

		//----- 衝突判定 -----
		bool isHit = false;

		isHit = IsHitOBB_OBB(pOA, pOB);

		if (isHit)
		{
			//----- 衝突時の挙動 -----
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

	// プレイヤーと目標地点
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
	// 線分
	struct Segment
	{
		DirectX::XMFLOAT3 StartPos;	// 始点
		DirectX::XMFLOAT3 EndPos;		// 終点
	};
	// 無限平面
	struct PLANE
	{
		myVector3 Normal;		// 平面の法線
		float	fDistance;		// ワールド原点からの距離
	};

	// 計算に使う要素
	DirectX::XMFLOAT3 aMove = pA->GetMove();
	DirectX::XMFLOAT3 bPos = pB->GetPos();

	Segment seg;
	seg.EndPos = pA->GetPos();
	seg.StartPos = DirectX::XMFLOAT3(seg.EndPos.x - aMove.x, seg.EndPos.y - aMove.y, seg.EndPos.z - aMove.z);
	PLANE plane;
	plane.fDistance = bPos.x*bPos.x + bPos.y*bPos.y + bPos.z*bPos.z;
	plane.Normal(0, 1, 0);		// 平面の法線。とりあえず上向きで。後々オブジェクトのメンバにすべきかも...
	myVector3::Rot(&plane.Normal, pB->GetRot());		// 法線をオブジェクトの傾き分回転
	myVector3 vecS(seg.StartPos.x - bPos.x, seg.StartPos.y - bPos.y, seg.StartPos.z - bPos.z);
	myVector3 vecE(seg.EndPos.x - bPos.x, seg.EndPos.y - bPos.y, seg.EndPos.z - bPos.z);

	float dotS = myVector3::dot(vecS, plane.Normal);
	float dotE = myVector3::dot(vecE, plane.Normal);

	if (dotE * dotS <= 0)
	{
#ifdef TEST_DEBUG
		// 衝突している
		pA->SetMaterial(1, 0, 0, 1);
		pB->SetMaterial(1, 0, 0, 1);
#endif // TEST_DEBUG
		return true;
	}

#ifdef TEST_DEBUG
	// 衝突してない
	pA->SetMaterial(1, 1, 1, 1);
	pB->SetMaterial(1, 1, 1, 1);
#endif // TEST_DEBUG
	return false;
}

bool Collision::IsHitAABB_AABB(GameObject *pA, GameObject *pB)
{
	// 直方体同士の当たり判定
	// 中心までの距離 < 半分の大きさを足し合わせた数
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

// OBB同士の衝突判定
// 参考：http://marupeke296.com/COL_3D_No13_OBBvsOBB.html
bool Collision::IsHitOBB_OBB(GameObject *pA, GameObject *pB)
{
	// 各方向ベクトルの確保
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
	// 衝突してない
	pA->SetMaterial(1, 1, 1, 1);
	pB->SetMaterial(1, 1, 1, 1);
#endif // TEST_DEBUG

	// 分離軸:Ae1
	float rA = myVector3::GetLength(Ae1);
	float rB = myVector3::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabsf(myVector3::dot(Interval, NAe1));
	if (L > rA + rB)
	{
		return false;	// 衝突してない
	}

	// 分離軸:Ae2
	rA = myVector3::GetLength(Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, NAe2));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:Ae3
	rA = myVector3::GetLength(Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, NAe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:Be1
	rA = myVector3::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = myVector3::GetLength(Be1);
	L = fabsf(myVector3::dot(Interval, NBe1));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:Be2
	rA = myVector3::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = myVector3::GetLength(Be2);
	L = fabsf(myVector3::dot(Interval, NBe2));
	if (L > rA + rB)
	{
		return false;
	}

	//分離軸:Be3
	rA = myVector3::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = myVector3::GetLength(Be3);
	L = fabsf(myVector3::dot(Interval, NBe3));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C11
	myVector3 Cross;
	Cross = myVector3::cross(NAe1, NBe1);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C12
	Cross = myVector3::cross(NAe1, NBe2);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C13
	Cross = myVector3::cross(NAe1, NBe3);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C21
	Cross = myVector3::cross(NAe2, NBe1);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C22
	Cross = myVector3::cross(NAe2, NBe2);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C23
	Cross = myVector3::cross(NAe2, NBe3);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C31
	Cross = myVector3::cross(NAe3, NBe1);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C32
	Cross = myVector3::cross(NAe3, NBe2);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}

	// 分離軸:C33
	Cross = myVector3::cross(NAe3, NBe3);
	rA = myVector3::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = myVector3::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(myVector3::dot(Interval, Cross));
	if (L > rA + rB)
	{
		return false;
	}
#ifdef TEST_DEBUG
	// 衝突している
	pA->SetMaterial(0, 1, 0, 1);
	pB->SetMaterial(0, 1, 0, 1);
#endif // TEST_DEBUG
	// 分離平面が存在しないので衝突している
	return true;
}


// XMFLOAT3型をXMVECTOR型に変換して返す
DirectX::XMVECTOR ConvertXMVECTOR(DirectX::XMFLOAT3 xmfloat3)
{
	return DirectX::XMVectorSet(xmfloat3.x, xmfloat3.y, xmfloat3.z, 0.0f);
};


void Collision::Push(GameObject *pDynamic, GameObject *pStatic)
{
	// 当たり判定をとる点を計算(プレイヤーの前方下)
	DirectX::XMVECTOR dHitPos = ConvertXMVECTOR(pDynamic->GetHitBox()->GetPos(pDynamic->GetPos(), pDynamic->GetSize(), pDynamic->GetRot()));	// dynamicの中心座標
	DirectX::XMVECTOR dSize = ConvertXMVECTOR(pDynamic->GetHitBox()->GetSize(pDynamic->GetSize()));		// dynamicのサイズ
	DirectX::XMVECTOR dMove = ConvertXMVECTOR(pDynamic->GetMove());		// dynamicの移動量
	DirectX::XMFLOAT3 dRot = pDynamic->GetHitBox()->GetRot(pDynamic->GetRot());						// dynamicの傾き
	dSize = DirectX::XMVector3Transform(dSize, DirectX::XMMatrixRotationX(dRot.x) * DirectX::XMMatrixRotationY(dRot.y)	* DirectX::XMMatrixRotationZ(dRot.z));	// 傾きに合わせてsizeを回転する
	dHitPos = DirectX::XMVectorAdd(dHitPos, DirectX::XMVectorSet(0, -DirectX::XMVectorGetY(dSize)*0.5f, DirectX::XMVectorGetZ(dSize)*0.5f, 0));		// 前方下に移動
	// 移動前の点
	DirectX::XMVECTOR dPreHitPos = DirectX::XMVectorSubtract(dHitPos, dMove);	// 移動量を引いて前の座標を求める

	// 平面のとある点を計算
	DirectX::XMVECTOR sPos = ConvertXMVECTOR(pStatic->GetHitBox()->GetPos(pStatic->GetPos(), pStatic->GetSize(), pStatic->GetRot()));	// staticの中心座標
	DirectX::XMVECTOR sSize = ConvertXMVECTOR(pStatic->GetHitBox()->GetSize(pStatic->GetSize()));	// staticのサイズ
	DirectX::XMFLOAT3 sRot = pStatic->GetHitBox()->GetRot(pStatic->GetRot());						// staticの傾き
	DirectX::XMVECTOR vsNormal = DirectX::XMVectorSet(0, 1, 0, 0);	// 法線(上向きに設定)
	// 法線をstaticの傾きに対応させる
	vsNormal = DirectX::XMVector3Transform(vsNormal, DirectX::XMMatrixRotationX(sRot.x)	* DirectX::XMMatrixRotationY(sRot.y) * DirectX::XMMatrixRotationZ(sRot.z));
	sSize = DirectX::XMVectorMultiply(sSize, DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0));	// sizeを半分にする
	float planeDis = DirectX::XMVectorGetY(sSize);
	sPos = DirectX::XMVectorAdd(sPos, DirectX::XMVectorMultiply(vsNormal, DirectX::XMVectorSet(planeDis, planeDis, planeDis, 0)));			// 法線方向にsize分移動した点が平面上の点

	// 内積を求めるためのベクトル
	DirectX::XMVECTOR vStart = DirectX::XMVectorSubtract(dPreHitPos, sPos);	// 平面の点から移動前の点へのベクトル
	DirectX::XMVECTOR vEnd = DirectX::XMVectorSubtract(dHitPos, sPos);		// 平面の点から移動後の点へのベクトル
	float dotS, dotE;
	DirectX::XMStoreFloat(&dotS, DirectX::XMVector3Dot(vStart, vsNormal));
	DirectX::XMStoreFloat(&dotE, DirectX::XMVector3Dot(vEnd, vsNormal));
	dotE *= 1.1f;

	if (dotS * dotE <= 0)
	{
		//--- ぶつかっている ---
		// 押し出し
		float PushDis = -dotE;
		DirectX::XMFLOAT3 dPos = pDynamic->GetPos();
		dPos.x += PushDis * DirectX::XMVectorGetX(vsNormal);
		dPos.y += PushDis * DirectX::XMVectorGetY(vsNormal);
		dPos.z += PushDis * DirectX::XMVectorGetZ(vsNormal);
		pDynamic->SetPos(dPos);

		// 移動量
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
	// 右左折状態出ないなら
	if (m_pPlayer->GetState() != E_STATE::STATE_TURN_LEFT&&m_pPlayer->GetState() != E_STATE::STATE_TURN_RIGHT)
	{
		// エラー防止用に
		Node<TargetPoint>* memTP = m_pPlayer->GetTargetPoint();
		// TPがプレイヤーより後ろにある時、TPがプレイヤーの前に来るまでTPを送る
		while (true)
		{
			if (m_pPlayer->GetTargetPoint() == nullptr || m_pPlayer->GetTargetPoint()->GetObj() == nullptr)
			{
				m_pPlayer->SetNextTargetPoint(memTP);
				break;
			}

			// プレイヤーの羽になるようなベクトル
			DirectX::XMVECTOR vPlayerWing = DirectX::XMVectorSet(1, 0, 0, 0);
			vPlayerWing = DirectX::XMVector3Transform(vPlayerWing, DirectX::XMMatrixRotationY(m_pPlayer->GetRot().y));
			vPlayerWing = DirectX::XMVectorSet(DirectX::XMVectorGetX(vPlayerWing), DirectX::XMVectorGetZ(vPlayerWing), 0, 0);
			// プレイヤーからTPへのベクトル
			DirectX::XMVECTOR vPlayerToTP = DirectX::XMVectorSubtract(
				DirectX::XMLoadFloat2(&m_pPlayer->GetTargetPoint()->GetObj()->GetPos()),
				DirectX::XMVectorSet(m_pPlayer->GetPos().x, m_pPlayer->GetPos().z, 0, 0));
			// 外積
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
	else if (m_pPlayer->GetState() == E_STATE::STATE_TURN_LEFT || m_pPlayer->GetState() == E_STATE::STATE_TURN_RIGHT)	// 右左折時
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
	// TPがプレイヤーより後ろにあったら前方にあるTPまで送る
	const float RpRadius = 1.0f;
	DirectX::XMFLOAT2 PlayerPos = DirectX::XMFLOAT2(m_pPlayer->GetPos().x, m_pPlayer->GetPos().z);		// プレイヤーの座標	x,z平面のみでおｋ
	DirectX::XMFLOAT2 PlayerPrePos = DirectX::XMFLOAT2(PlayerPos.x - m_pPlayer->GetMove().x, PlayerPos.y - m_pPlayer->GetMove().z);
	DirectX::XMFLOAT2 RpPos = pRp->GetPos();				// ルートポイントの座標

	return CheckCollisionCircleToLine(RpPos, RpRadius, PlayerPrePos, PlayerPos);
}


// 点と円の当たり判定
bool Collision::CheckCollisionPointToCircle(float PointX, float PointY, float CirclePosX, float CirclePosY, float radius)
{
	float distance;		// 点と円の距離^2

	distance = (PointX - CirclePosX)*(PointX - CirclePosX) + (PointY - CirclePosY)*(PointY - CirclePosY);
	if (distance <= radius)
		return true;

	return false;
}


bool Collision::CheckCollisionCircleToCircle(DirectX::XMFLOAT2 CAPos, float CARadius, DirectX::XMFLOAT2 CBPos, float CBRadius)
{
	float distance;		// 円と円の距離

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


// 線分と円の当たり判定
bool Collision::CheckCollisionCircleToLine(DirectX::XMFLOAT2 CPos, float CRadius, DirectX::XMFLOAT2 LStartPos, DirectX::XMFLOAT2 LEndPos)
{
	DirectX::XMVECTOR SE = DirectX::XMVectorSet(LEndPos.x - LStartPos.x, LEndPos.y - LStartPos.y, 0, 0);	// 始点から終点へ
	DirectX::XMVECTOR SC = DirectX::XMVectorSet(CPos.x - LStartPos.x, CPos.y - LStartPos.y, 0, 0);	// 始点から円の中心へ
	DirectX::XMVECTOR EC = DirectX::XMVectorSet(CPos.x - LEndPos.x, CPos.y - LEndPos.y, 0, 0);		// 始点から円の中心へ

	SE = DirectX::XMVector2Normalize(SE);

	// 円から直線への最短距離
	float ShortestLength;
	DirectX::XMStoreFloat(&ShortestLength, DirectX::XMVector2Cross(SE, SC));

	if (ShortestLength < 0)
		ShortestLength *= -1.0f;

	// 半径の方が短いなら当たっている可能性はない
	if (CRadius < ShortestLength)
		return false;

	// 円が線分内にあるか調べる
	float innerCSE, innerCES;
	DirectX::XMStoreFloat(&innerCSE, DirectX::XMVector2Dot(SC, SE));
	DirectX::XMStoreFloat(&innerCES, DirectX::XMVector2Dot(EC, SE));

	// 内積の積が負なら線分内
	if (innerCES * innerCSE < 0)
		return true;

	// 線分の端が円に含まれているか調べる
	if (CheckCollisionPointToCircle(LStartPos.x, LStartPos.y, CPos.x, CPos.y, CRadius))		// 始点
		return true;

	if (CheckCollisionPointToCircle(LEndPos.x, LEndPos.y, CPos.x, CPos.y, CRadius))			// 終点
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