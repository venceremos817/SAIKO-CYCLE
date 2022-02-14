//========================================================
//	2021/01/28	アーカイブ作業開始
//========================================================


#ifndef __PLAYER_H__
#define __PLAYER_H__


//===== インクルード部 =====
#include "CharacterBase.h"
#include "Camera.h"
#include "SkySphere.h"
#include "Controller.h"
#include "TargetPoint.h"
#include "Stage.h"
#include "model.h"
#include "Sound.h"

namespace PlayerState
{
	const float SPEED = 1.0f / 60;		// 移動量(秒速)
	const float KILL_POS_Y = -50.0f;		// デッドライン
	const float GRAVITY_ACC = -0.98f / 60.0f;	// 重力
	const float	JUMP_POWER = 30.0f / 60.0f;	// ジャンプ力
	const float FrictionForce = 0.98f;
	const int	SLIP_FRAME = 30;		// スリップにかける時間(フレーム)

	enum E_PlayerAnimation
	{
		PLAYER_DRIVE,

		PLAYER_JUMP1,
		PLAYER_JUMP2,
		PLAYER_JUMP3,

		PLAYER_TURN_L,
		PLAYER_TURN_R,

		MAX_PLAYER_ANIM
	};

	enum E_BikeAnimation
	{
		BIKE_DRIVE,
		BIKE_JUMP,
		BIKE_TURN_L,
		BIKE_TURN_R,

		MAX_BIKE_ANIM
	};
}


class Player :
	public CharacterBase
{
public:
	Player();
	virtual ~Player();

	void ReSporn();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetControllCamera(Camera *pCamera);
	static void SetControler(Controller *pController);
	static void SetNextTargetPoint(Node<TargetPoint>* pTpNode) { m_pNextTargetPointNode = pTpNode; }
	static void SetFirstTargetPoint(Node<TargetPoint>* pTpNode) { m_pmemFirstTP = pTpNode; m_pNextTargetPointNode = pTpNode; }
	static void	SetGoalTP(Node<TargetPoint>* pTPNode, E_RANE rane);
	Node<TargetPoint>*	GetTargetPoint() { return m_pNextTargetPointNode; }
	E_RANE	GetCurRane();
	E_RANE	GetNextRane();
	float	GetSpeed() { return m_speed; }
	void	SetCurRane(E_RANE rane);
	void	SetNextRane(E_RANE rane);

	//----- 状態変更
	void SetState(E_STATE state);
	static bool m_bAutoRun;

private:
	DirectX::XMFLOAT3 m_ModelRot;
	float m_speed;
	static Model* m_pBikeModel;
	static Model* m_pPlayerModel;
	Camera	*m_pControllCamera;
	static Controller	*m_pController;
	// コントローラーのスティック
	DirectX::XMFLOAT2 m_preStick;
	DirectX::XMFLOAT2 m_curStick;

	bool	isStant;
	int		rotDis;		// スタント回転方向
	E_RANE m_curRane;
	E_RANE m_nextRane;

	static Node<TargetPoint>*	m_pNextTargetPointNode;		// 次の目標地点
	static Node<TargetPoint>*	m_pmemFirstTP;
	static Node<TargetPoint>*	m_pGoalTP[MAX_RANE];

	// サウンド
	static XAUDIO2_BUFFER* m_pSound;

	// アニメーション
	ANIME_INDEX m_playerAnimIdx[PlayerState::MAX_PLAYER_ANIM];
	ANIME_INDEX m_bikeAnimIdx[PlayerState::MAX_BIKE_ANIM];
	float	m_animStep;

	E_STATE m_memState;


private:
	void UpdateStop();
	void UpdateRun();
	void UpdateGoLeft();
	void UpdateGoRight();
	void UpdateSlip();
	void UpdateStant();
	void StartStant();
	void UpdateAutoRun();
	void FacingDireRotY(const DirectX::XMVECTOR &vDirection);
};

#endif // !__PLAYER_H__
