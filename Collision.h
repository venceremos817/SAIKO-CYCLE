#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "GameObject.h"
#include "List.h"
#include "TargetPoint.h"
#include "Stage.h"
#include "Player.h"
#include "Line.h"


#include "DebugDefine.h"




//===== 定数 =====
//const int MaxCollisionRegister = 1000;	// 当たり判定を行う組み合わせの最大数	※ほんとはリスト構造で制限ないほうがいい

class Collision
{
public:
	Collision();
	~Collision();

	HRESULT Init();
	void	Uninit();
	void	Update();

	static void Register(GameObject *pA, GameObject *pB);
	static void Register(List<TargetPoint> *pRpList, E_RANE rane);
	static void Register(Player* pPlayer);

#ifdef TEST_DEBUG
	Cube m_testCube;
	void TestDraw();
#endif // TEST_DEBUG


public:
	static bool IsHitSegment_Plane(GameObject *pA, GameObject *pB);	// 線分と無限平面の衝突判定
	static bool IsHitAABB_AABB(GameObject *pA, GameObject *pB);		// AABB同士の衝突判定
	static bool IsHitOBB_OBB(GameObject *pA, GameObject *pB);		// OBB同士の衝突判定
	static bool IsHitXZSegment_XZSegment(DirectX::XMFLOAT3 aS, DirectX::XMFLOAT3 aE, DirectX::XMFLOAT3 bS, DirectX::XMFLOAT3 bE);

	static bool IsHitSphere(DirectX::XMFLOAT3 aPos, DirectX::XMFLOAT3 bPos, float aRadius, float bRadius);
	//static bool IsHitSphere(GameObject* pA, GameObject* pB);

	static float GetDistance(DirectX::XMFLOAT3 aPos, DirectX::XMFLOAT3 bPos);
	static float GetDistance(GameObject* pA, GameObject* pB);
	static float GetDistance(DirectX::XMFLOAT3 pos, GameObject* pGameObj);

private:
	void Push(GameObject *pDynamic, GameObject *pStatic);
	// Bounce
	//----- プレイヤーとルートポイント -----
	void FunctionPlayer_TP();
	bool IsHitPlayer_TP(TargetPoint* pRp);



	// ----- 当たり判定 -----
	static bool CheckCollisionPointToCircle(float PointX, float PointY, float CirclePosX, float CirclePosY, float radius);
	static bool CheckCollisionCircleToCircle(DirectX::XMFLOAT2 CAPos, float CARadius, DirectX::XMFLOAT2 CBPos, float CBRadius);
	static bool CheckCollisionPoleToPole(DirectX::XMFLOAT3 PAPos, float PARadius, float PAHeight, DirectX::XMFLOAT3 PBPos, float PBRadius, float PBHeight);
	static bool CheckCollisionCircleToLine(DirectX::XMFLOAT2 CPos, float CRadius, DirectX::XMFLOAT2 LStartPos, DirectX::XMFLOAT2 LEndPos);



private:
	static List<GameObject> *m_pLIST[2];		// 当たり判定をとるペア
	static int			m_registerObjNum;		// 登録されている数
	static List<TargetPoint>	*m_pTpList[E_RANE::MAX_RANE];
	static Player		*m_pPlayer;

};

#endif // !__COLLISION_H__
