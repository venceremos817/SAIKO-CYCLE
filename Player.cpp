//===== インクルード部 =====
#include "Player.h"
#include "Input.h"
#include "myVector.h"
#include "DebugDefine.h"
#include "Collision.h"
#include "EffectManager.h"
#include "Score.h"
#include "StageStartDirecting.h"
#include "SceneMgr.h"

#define CAMERA_CONTROLL		// カメラが後ろに回るデバッグ時使いづらいためここで切り替え可能にしとく

const float MODEL_DIFFERENCE_ROT_X = 1.20000017f;
const float MODEL_DIFFERENCE_ROT_Y = 0.000000000f;
const float MODEL_DIFFERENCE_ROT_Z = 1.49011612e-08f;
const float MODEL_DIFFERENCE_POS_X = 1.49011612e-08f;
const float MODEL_DIFFERENCE_POS_Y = 4.89999771f;
const float MODEL_DIFFERENCE_POS_Z = 0.000000000f;

Node<TargetPoint>* Player::m_pNextTargetPointNode = nullptr;
Node<TargetPoint>* Player::m_pmemFirstTP = nullptr;
Node<TargetPoint>* Player::m_pGoalTP[MAX_RANE];
Controller* Player::m_pController = nullptr;
bool Player::m_bAutoRun = false;


const float PI = acosf(-1.0f);


Model* Player::m_pBikeModel = nullptr;
Model* Player::m_pPlayerModel = nullptr;
XAUDIO2_BUFFER* Player::m_pSound = nullptr;



Player::Player()
	: m_pControllCamera(nullptr)
	, m_preStick(0, 0)
	, m_curStick(0, 0)
	, isStant(false)
	, m_curRane(E_RANE::CENTER)
	, m_nextRane(m_curRane)
	, m_speed(0.0f)
	, m_ModelRot(m_rot)
{
	SetPos(0, 10, 0);
	SetSize(1, 1, 1);
	SetRot(DirectX::XMFLOAT3(0, 0, 0));
	SetCollisionForm(COLLIDER_SEGMENT);
	m_MatColor.SetRGBA(1, 1, 1, 1);
	Collision::Register(this);
	SetObjectType(E_ObjectType::TYPE_PLAYER);
	SetState(E_STATE::STATE_STOP);
	m_bAutoRun = false;

	// ヒットボックス設定
	m_pHitBox->SetPos(0.000000000f, 1.90000021f, -0.600000024f);
	m_pHitBox->SetRot(0.000000000f, 0.000000000f, 0.000000000f);
	m_pHitBox->SetSize(1.60000014f, 3.79999852f, 5.79999685f);
}


Player::~Player()
{
	m_pControllCamera = nullptr;
}


HRESULT Player::Init()
{
	HRESULT hr = S_OK;


	if (m_pBikeModel == nullptr)
	{
		m_pBikeModel = new Model;
		hr = m_pBikeModel->LoadModel("Assets/Model/Bike/model_base/bike_base.fbx");
		hr = m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_DRIVE] = m_pBikeModel->LoadAnimation("Assets/Model/Bike/bike_drive.fbx");
		hr = m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_JUMP] = m_pBikeModel->LoadAnimation("Assets/Model/Bike/bike_jump.fbx");
		hr = m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_TURN_L] = m_pBikeModel->LoadAnimation("Assets/Model/Bike/bike_turnL.fbx");
		hr = m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_TURN_R] = m_pBikeModel->LoadAnimation("Assets/Model/Bike/bike_turnR.fbx");
		m_pBikeModel->PlayAnime(m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_DRIVE], true);
	}
	if (m_pPlayerModel == nullptr)
	{
		m_pPlayerModel = new Model;
		hr = m_pPlayerModel->LoadModel("Assets/Model/Bike/model_base/Human_base.fbx");
		hr = m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_DRIVE] = m_pPlayerModel->LoadAnimation("Assets/Model/Bike/Human_drive.fbx");
		hr = m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_JUMP1] = m_pPlayerModel->LoadAnimation("Assets/Model/Bike/Human_jump1.fbx");
		hr = m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_JUMP2] = m_pPlayerModel->LoadAnimation("Assets/Model/Bike/Human_jump2.fbx");
		hr = m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_JUMP3] = m_pPlayerModel->LoadAnimation("Assets/Model/Bike/Human_jump3.fbx");
		hr = m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_TURN_L] = m_pPlayerModel->LoadAnimation("Assets/Model/Bike/Human_turnL.fbx");
		hr = m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_TURN_R] = m_pPlayerModel->LoadAnimation("Assets/Model/Bike/Human_turnR.fbx");
		m_pPlayerModel->PlayAnime(m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_DRIVE], true);
	}

	if (m_pSound == nullptr)
	{
		m_pSound = CreateSound("Assets/Sound/nyu3.mp3", false);
	}

	m_bAutoRun = false;
	SetState(E_STATE::STATE_STOP);

	return S_OK;
}


void Player::Uninit()
{
	m_pNextTargetPointNode = nullptr;
	m_pmemFirstTP = nullptr;

	if (m_pBikeModel != nullptr)
	{
		delete m_pBikeModel;
		m_pBikeModel = nullptr;
	}
	if (m_pPlayerModel != nullptr)
	{
		delete m_pPlayerModel;
		m_pPlayerModel = nullptr;
	}
}


void Player::ReSporn()
{
	m_pos = DirectX::XMFLOAT3(0, 1, 0);
	SetPos(DirectX::XMFLOAT3(0, 1, 0));
	SetMove(DirectX::XMFLOAT3(0, 0, 0));
	SetRot(DirectX::XMFLOAT3(0, 0, 0));
	isStant = false;
	m_preStick = DirectX::XMFLOAT2(0, 0);
	m_curStick = DirectX::XMFLOAT2(0, 0);
	m_pControllCamera->SetXZAngle(0);
	m_curRane = E_RANE::CENTER;
	m_nextRane = m_curRane;

	SetNextTargetPoint(m_pmemFirstTP);
}

void Player::Update()
{
	DirectX::XMStoreFloat(&m_speed, DirectX::XMVector3Length(DirectX::XMLoadFloat3(&m_move)));


	if (m_isGround && m_speed > -PlayerState::GRAVITY_ACC*20.0f)
	{
		DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pHitBox->GetPos(m_pos, m_size, m_rot));
		DirectX::XMVECTOR vSize = DirectX::XMLoadFloat3(&m_pHitBox->GetSize(m_size));
		DirectX::XMFLOAT3 Rot = m_pHitBox->GetRot(m_rot);
		vSize = DirectX::XMVector3Transform(vSize, DirectX::XMMatrixRotationX(Rot.x) * DirectX::XMMatrixRotationY(Rot.y) * DirectX::XMMatrixRotationZ(Rot.z));	// 傾きに合わせてsizeを回転する
		vPos = DirectX::XMVectorAdd(vPos, DirectX::XMVectorSet(0, -DirectX::XMVectorGetY(vSize)*0.5f, 0, 0));		// 後方下に移動
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, vPos);
		EffectManager::CreateSandSmoke(pos, m_speed * 10, m_speed / 10);
	}



	switch (m_state)
	{
	case STATE_STOP:
		UpdateStop();
		break;

	case STATE_RUN:
	case STATE_TURN_LEFT:
	case STATE_TURN_RIGHT:
		UpdateRun();
		break;

	case  STATE_AUTO_RUN:
		UpdateAutoRun();
		break;

	case STATE_SLIP:
		UpdateSlip();
		break;

	case STATE_STANT:
		UpdateStant();
		break;

	default:
		break;
	}

	// 下に行き過ぎるとリスポーン
	if (m_pos.y < PlayerState::KILL_POS_Y)
		ReSporn();

	// アニメーション
	m_pBikeModel->StepAnime(m_animStep);
	m_pPlayerModel->StepAnime(m_animStep);



	m_isGround = false;


	// ゴール判定
	for (int i = 0; i < MAX_RANE; i++)
	{
		if (m_pNextTargetPointNode == m_pGoalTP[i])
		{
			SetNextTargetPoint(m_pmemFirstTP);
			SetState(E_STATE::STATE_AUTO_RUN);
			SceneMgr::SetNextScene(SCENE_RESULT);
		}
	}

}

void Player::UpdateRun()
{
	bool IsKeyForward = IsKeyPress('W');
	bool IsKeyBrake = IsKeyPress('S');
	bool IsKeyLeft = IsKeyTrigger('A');
	bool IskeyRight = IsKeyTrigger('D');
	bool IsKeyJump = IsKeyTrigger(VK_SPACE);

	// 移動
	float AddSpeed = 0.0f;
	if (IsKeyForward) { AddSpeed += 1.5f; }
	if (m_pController != nullptr)
	{
		m_preStick = m_curStick;
		m_curStick = m_pController->GetLeftStick();
		DirectX::XMVECTOR preV = DirectX::XMLoadFloat2(&m_preStick);
		DirectX::XMVECTOR curV = DirectX::XMLoadFloat2(&m_curStick);
		float preVecLen;
		float curVecLen;
		DirectX::XMStoreFloat(&preVecLen, DirectX::XMVector2Length(preV));
		DirectX::XMStoreFloat(&curVecLen, DirectX::XMVector2Length(curV));
		if (preVecLen != 0 && curVecLen != 0)
		{
			curV = DirectX::XMVector2Normalize(curV);
			DirectX::XMStoreFloat(&AddSpeed,
				DirectX::XMVector2AngleBetweenVectors(preV, curV));
			AddSpeed *= 3.0f;
		}
		static int raneCool = 0;
		raneCool--;
		// レーン切り替え
		if (m_pController->IsLeftTrigger())
		{
			if (raneCool < 0)
			{
				switch (m_curRane)
				{
				case CENTER:
					m_nextRane = E_RANE::LEFT;
					SetState(E_STATE::STATE_TURN_LEFT);
					PlaySound(m_pSound);
					break;
				case RIGHT:
					m_nextRane = E_RANE::CENTER;
					SetState(E_STATE::STATE_TURN_LEFT);
					PlaySound(m_pSound);
					break;
				}
				raneCool = 10;
			}
		}
		if (m_pController->IsRightTrigger())
		{
			if (raneCool < 0)
			{
				switch (m_curRane)
				{
				case LEFT:
					m_nextRane = E_RANE::CENTER;
					SetState(E_STATE::STATE_TURN_RIGHT);
					PlaySound(m_pSound);
					break;
				case CENTER:
					m_nextRane = E_RANE::RIGHT;
					SetState(E_STATE::STATE_TURN_RIGHT);
					PlaySound(m_pSound);
					break;
				default:
					break;
				}
				raneCool = 10;
			}
		}

		// ジャンプ
		if (m_pController->IsPress(VK_PAD_A) && m_isGround == false)
		{
			StartStant();
		}
	}
	// レーン切り替え
	if (IsKeyTrigger('Q'))
	{
		switch (m_curRane)
		{
		case CENTER:
			m_nextRane = E_RANE::LEFT;
			SetState(E_STATE::STATE_TURN_LEFT);
			PlaySound(m_pSound);
			break;
		case RIGHT:
			m_nextRane = E_RANE::CENTER;
			SetState(E_STATE::STATE_TURN_LEFT);
			PlaySound(m_pSound);
			break;
		default:
			break;
		}
	}
	if (IsKeyTrigger('E'))
	{
		switch (m_curRane)
		{
		case LEFT:
			m_nextRane = E_RANE::CENTER;
			SetState(E_STATE::STATE_TURN_RIGHT);
			PlaySound(m_pSound);
			break;
		case CENTER:
			m_nextRane = E_RANE::RIGHT;
			SetState(E_STATE::STATE_TURN_RIGHT);
			PlaySound(m_pSound);
			break;
		default:
			break;
		}
	}
	if (IsKeyJump && m_isGround == false)
	{
		StartStant();
	}


	AddSpeed *= PlayerState::SPEED;
	float curSpd;
	DirectX::XMStoreFloat(&curSpd, DirectX::XMVector2Length(DirectX::XMVectorSet(m_move.x, m_move.z, 0, 0)));
	curSpd += AddSpeed;
	if (IsKeyBrake) { curSpd *= PlayerState::FrictionForce; }
	curSpd *= PlayerState::FrictionForce;	// 減速



	// 進行方向算出
	DirectX::XMVECTOR vMoveDirection = DirectX::XMVectorSet(0, 0, 1, 0);		// Z方向にまっすぐ
	if (m_pNextTargetPointNode != nullptr)
	{
		TargetPoint* tp = m_pNextTargetPointNode->GetObj();
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(tp->GetPos().x, 0, tp->GetPos().y, 0);	// 目標地点
		DirectX::XMVECTOR preTargetPos = DirectX::XMVectorSet(m_pos.x, 0, m_pos.z, 0);		// 現在位置
		vMoveDirection = DirectX::XMVectorSubtract(targetPos, preTargetPos);		// 現在位置から目標地点へ
		vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);

		// レーン切り替え時
		if (m_state == E_STATE::STATE_TURN_LEFT || m_state == E_STATE::STATE_TURN_RIGHT)
		{
			TargetPoint* PreTp = m_pNextTargetPointNode->GetPrev()->GetObj();		// 前回目標地点
			vMoveDirection = DirectX::XMVectorSubtract(targetPos, DirectX::XMVectorSet(PreTp->GetPos().x, 0, PreTp->GetPos().y, 0));		// 前回目標地点から目標地点
			// 前のポイントと次のポイントのベクトルに対して垂直な方向への成分
			DirectX::XMVECTOR vTurn = DirectX::XMVectorSubtract(targetPos, DirectX::XMVectorSet(PreTp->GetPos().x, 0, PreTp->GetPos().y, 0));
			switch (m_state)
			{
			case STATE_TURN_LEFT:
				vTurn = DirectX::XMVectorSet(-DirectX::XMVectorGetZ(vTurn), 0, DirectX::XMVectorGetX(vTurn), 0);
				break;
			case STATE_TURN_RIGHT:
				vTurn = DirectX::XMVectorSet(DirectX::XMVectorGetZ(vTurn), 0, -DirectX::XMVectorGetX(vTurn), 0);
				break;
			default:
				break;
			}
			vTurn = DirectX::XMVector3Normalize(vTurn);
			vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);
			vMoveDirection = DirectX::XMVectorAdd(vMoveDirection, vTurn);
		}
	}

	// 進行方向を向く
	FacingDireRotY(vMoveDirection);

	vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);
	vMoveDirection = DirectX::XMVectorScale(vMoveDirection, curSpd);
	float memY = m_move.y;
	DirectX::XMStoreFloat3(&m_move, vMoveDirection);

	m_move.y = memY + PlayerState::GRAVITY_ACC;
	SetMove(m_move);

	// 移動量適用
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	SetPos(m_pos);

	m_animStep = m_speed;

#ifdef CAMERA_CONTROLL
	m_pControllCamera->SetXZAngle(DirectX::XMConvertToDegrees(-m_rot.y));
#endif // CAMERA_CONTROLL

}


void Player::Draw()
{
	SHADER->Bind(VS_ANIMATION, PS_TOON);
	SHADER->SetDiffuse(DirectX::XMFLOAT4(0.95, 0.95, 0.95, 1));
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)*
		DirectX::XMMatrixRotationX(m_ModelRot.x)*DirectX::XMMatrixRotationY(m_ModelRot.y)*DirectX::XMMatrixRotationZ(m_ModelRot.z)*
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pBikeModel->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)*
		DirectX::XMMatrixRotationX(m_ModelRot.x + MODEL_DIFFERENCE_ROT_X)*
		DirectX::XMMatrixRotationY(m_ModelRot.y + MODEL_DIFFERENCE_ROT_Y)*
		DirectX::XMMatrixRotationZ(m_ModelRot.z + MODEL_DIFFERENCE_ROT_Z)*
		DirectX::XMMatrixTranslation(
			m_pos.x + MODEL_DIFFERENCE_POS_X,
			m_pos.y + MODEL_DIFFERENCE_POS_Y,
			m_pos.z + MODEL_DIFFERENCE_POS_Z));
	m_pPlayerModel->Draw();

#ifdef TEST_DEBUG
	m_pHitBox->testDraw(m_pos, m_size, m_rot);
#endif // TEST_DEBUG

}


void Player::UpdateStop()
{
	m_move.y += PlayerState::GRAVITY_ACC;
	SetMove(m_move);

	// 移動量適用
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	SetPos(m_pos);

	if (StageStartDirecting::m_isFinish)
		SetState(E_STATE::STATE_RUN);
}

void Player::UpdateGoLeft()
{

}

void Player::UpdateGoRight()
{

}

void Player::UpdateSlip()
{
	static int slipTime = 0;
	static float rot;
	
	if (slipTime == 0)rot = m_rot.y;

	m_move.x *= 0.95f;
	m_move.y += PlayerState::GRAVITY_ACC;
	m_move.z *= 0.95f;
	SetMove(m_move);
	// 移動量適用
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	SetPos(m_pos);

	//m_rot.y += PI / 10;
	//SetRotY(m_rot.y + PI / 10);
	rot += PI / 10;
	m_ModelRot.y = rot;
	slipTime++;

	// スリップ終了
	if (slipTime > PlayerState::SLIP_FRAME)
	{
		slipTime = 0;
		SetState(E_STATE::STATE_RUN);
	}

	// 進行方向算出
	DirectX::XMVECTOR vMoveDirection = DirectX::XMVectorSet(0, 0, 1, 0);		// Z方向にまっすぐ
	if (m_pNextTargetPointNode != nullptr)
	{
		TargetPoint* tp = m_pNextTargetPointNode->GetObj();
		TargetPoint* PreTp = m_pNextTargetPointNode->GetPrev()->GetObj();
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(tp->GetPos().x, 0, tp->GetPos().y, 0);	// 目標地点
		DirectX::XMVECTOR preTargetPos = DirectX::XMVectorSet(m_pos.x, 0, m_pos.z, 0);		// 現在位置
		vMoveDirection = DirectX::XMVectorSubtract(targetPos, preTargetPos);		// 現在位置から目標地点へ
		vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);

		// レーン切り替え時
		if (m_memState == E_STATE::STATE_TURN_LEFT || m_memState == E_STATE::STATE_TURN_RIGHT)
		{
			vMoveDirection = DirectX::XMVectorSubtract(targetPos, DirectX::XMVectorSet(PreTp->GetPos().x, 0, PreTp->GetPos().y, 0));		// 前回目標地点から目標地点
			// 前のポイントと次のポイントのベクトルに対して垂直な方向にも進む
			DirectX::XMVECTOR vTurn = DirectX::XMVectorSubtract(targetPos, DirectX::XMVectorSet(PreTp->GetPos().x, 0, PreTp->GetPos().y, 0));
			switch (m_state)
			{
			case STATE_TURN_LEFT:
				vTurn = DirectX::XMVectorSet(-DirectX::XMVectorGetZ(vTurn), 0, DirectX::XMVectorGetX(vTurn), 0);
				break;
			case STATE_TURN_RIGHT:
				vTurn = DirectX::XMVectorSet(DirectX::XMVectorGetZ(vTurn), 0, -DirectX::XMVectorGetX(vTurn), 0);
				break;
			default:
				break;
			}
			vTurn = DirectX::XMVector3Normalize(vTurn);
			vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);
			vMoveDirection = DirectX::XMVectorAdd(vMoveDirection, vTurn);
		}
	}
}

void Player::UpdateStant()
{
	bool isStanting = m_pBikeModel->GetFBXPlayer()->IsPlay() && m_pPlayerModel->GetFBXPlayer()->IsPlay();
	if (m_isGround == true && isStanting == false)
	{
		SetState(E_STATE::STATE_RUN);
	}
	m_move.y += PlayerState::GRAVITY_ACC;
	SetMove(m_move);

	// 移動量適用
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	SetPos(m_pos);
	
	// 進行方向算出
	DirectX::XMVECTOR vMoveDirection = DirectX::XMVectorSet(0, 0, 1, 0);		// Z方向にまっすぐ
	if (m_pNextTargetPointNode != nullptr)
	{
		TargetPoint* tp = m_pNextTargetPointNode->GetObj();
		TargetPoint* PreTp = m_pNextTargetPointNode->GetPrev()->GetObj();
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(tp->GetPos().x, 0, tp->GetPos().y, 0);	// 目標地点
		DirectX::XMVECTOR preTargetPos = DirectX::XMVectorSet(m_pos.x, 0, m_pos.z, 0);		// 現在位置
		vMoveDirection = DirectX::XMVectorSubtract(targetPos, preTargetPos);		// 現在位置から目標地点へ
		vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);

		// レーン切り替え時
		if (m_memState == E_STATE::STATE_TURN_LEFT || m_memState == E_STATE::STATE_TURN_RIGHT)
		{
			vMoveDirection = DirectX::XMVectorSubtract(targetPos, DirectX::XMVectorSet(PreTp->GetPos().x, 0, PreTp->GetPos().y, 0));		// 前回目標地点から目標地点
			// 前のポイントと次のポイントのベクトルに対して垂直な方向にも進む
			DirectX::XMVECTOR vTurn = DirectX::XMVectorSubtract(targetPos, DirectX::XMVectorSet(PreTp->GetPos().x, 0, PreTp->GetPos().y, 0));
			switch (m_state)
			{
			case STATE_TURN_LEFT:
				vTurn = DirectX::XMVectorSet(-DirectX::XMVectorGetZ(vTurn), 0, DirectX::XMVectorGetX(vTurn), 0);
				break;
			case STATE_TURN_RIGHT:
				vTurn = DirectX::XMVectorSet(DirectX::XMVectorGetZ(vTurn), 0, -DirectX::XMVectorGetX(vTurn), 0);
				break;
			default:
				break;
			}
			vTurn = DirectX::XMVector3Normalize(vTurn);
			vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);
			vMoveDirection = DirectX::XMVectorAdd(vMoveDirection, vTurn);
		}
	}

	// 進行方向を向く
	FacingDireRotY(vMoveDirection);

	m_animStep = 1.0f;
}

void Player::StartStant()
{
	m_move.y -= PlayerState::GRAVITY_ACC * 40;
	SetState(E_STATE::STATE_STANT);
	EffectManager::CreateJumpEffect(this);
	Score::Add(500);
}


void Player::UpdateAutoRun()
{
	// 移動
	float AddSpeed = 1.2f;

	AddSpeed *= PlayerState::SPEED;
	float curSpd;
	DirectX::XMStoreFloat(&curSpd, DirectX::XMVector2Length(DirectX::XMVectorSet(m_move.x, m_move.z, 0, 0)));
	curSpd += AddSpeed;
	curSpd *= PlayerState::FrictionForce;	// 減速

	// ジャンプ
	if (m_isGround == false)
	{
		StartStant();
	}

	// 進行方向算出
	DirectX::XMVECTOR vMoveDirection = DirectX::XMVectorSet(0, 0, 1, 0);		// Z方向にまっすぐ
	if (m_pNextTargetPointNode != nullptr)
	{
		TargetPoint* tp = m_pNextTargetPointNode->GetObj();
		TargetPoint* PreTp = m_pNextTargetPointNode->GetPrev()->GetObj();
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(tp->GetPos().x, 0, tp->GetPos().y, 0);	// 目標地点
		DirectX::XMVECTOR preTargetPos = DirectX::XMVectorSet(m_pos.x, 0, m_pos.z, 0);		// 現在位置
		vMoveDirection = DirectX::XMVectorSubtract(targetPos, preTargetPos);		// 現在位置から目標地点へ
		vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);
	}

	// 進行方向を向く
	FacingDireRotY(vMoveDirection);

	vMoveDirection = DirectX::XMVector3Normalize(vMoveDirection);
	vMoveDirection = DirectX::XMVectorScale(vMoveDirection, curSpd);
	float memY = m_move.y;
	DirectX::XMStoreFloat3(&m_move, vMoveDirection);

	m_move.y = memY + PlayerState::GRAVITY_ACC;
	SetMove(m_move);

	// 移動量適用
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	SetPos(m_pos);

	m_animStep = m_speed;
}



void Player::SetControllCamera(Camera *pCamera)
{
	m_pControllCamera = pCamera;
}


void Player::SetControler(Controller *pController)
{
	m_pController = pController;
}


void Player::SetGoalTP(Node<TargetPoint>* pTPNode, E_RANE rane)
{
	m_pGoalTP[rane] = pTPNode;
}



E_RANE Player::GetCurRane()
{
	return m_curRane;
}

E_RANE Player::GetNextRane()
{
	return m_nextRane;
}

void Player::SetCurRane(E_RANE rane)
{
	m_curRane = rane;
}

void Player::SetNextRane(E_RANE rane)
{
	m_nextRane = rane;
}



void Player::FacingDireRotY(const DirectX::XMVECTOR &vDirection)
{
	float rotY;
	float LR;

	DirectX::XMVECTOR target = DirectX::XMVectorSet(DirectX::XMVectorGetX(vDirection), DirectX::XMVectorGetZ(vDirection), 0, 0);
	DirectX::XMVECTOR forward = DirectX::XMVectorSet(0, 0, 1, 0);
	forward = DirectX::XMVector3Transform(forward, DirectX::XMMatrixRotationY(m_rot.y));
	forward = DirectX::XMVectorSet(DirectX::XMVectorGetX(forward), DirectX::XMVectorGetZ(forward), 0, 0);

	// 2つのベクトルのなす角を得る
	DirectX::XMStoreFloat(
		&rotY,
		DirectX::XMVector2AngleBetweenVectors(target, forward)
	);
	rotY *= 0.8f;

	// 外積で目標が左右のどちらにあるか調べる
	DirectX::XMStoreFloat(
		&LR,
		DirectX::XMVector2Cross(target, forward)
	);
	if (LR < 0)
	{
		rotY *= -1;
	}

	SetRotY(m_rot.y + rotY * 0.1f);

	m_ModelRot = m_rot;
}


void Player::SetState(E_STATE state)
{
	if (m_state == state) { return; }


	m_memState = m_state;
	m_state = state;

	int random;

	switch (state)
	{
	case STATE_RUN:
		if (m_bAutoRun)
		{
			SetState(STATE_AUTO_RUN);
			break;
		}
		m_pBikeModel->PlayAnime(m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_DRIVE], true);
		m_pPlayerModel->PlayAnime(m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_DRIVE], true);
		break;
	case STATE_TURN_LEFT:
		m_pBikeModel->PlayAnime(m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_TURN_L], true);
		m_pPlayerModel->PlayAnime(m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_TURN_L], true);
		break;
	case STATE_TURN_RIGHT:
		m_pBikeModel->PlayAnime(m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_TURN_R], true);
		m_pPlayerModel->PlayAnime(m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_TURN_R], true);
		break;
	case STATE_SLIP:
		Score::Add(-50);
		break;
	case STATE_STANT:
		m_pBikeModel->PlayAnime(m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_JUMP], false);
		random = PlayerState::E_PlayerAnimation::PLAYER_JUMP1 + (int)(rand()*(PlayerState::E_PlayerAnimation::PLAYER_JUMP3 - PlayerState::E_PlayerAnimation::PLAYER_JUMP1 + 1) / (1 + RAND_MAX));
		m_pPlayerModel->PlayAnime(m_playerAnimIdx[random], false);
		break;

	case STATE_AUTO_RUN:
		m_pBikeModel->PlayAnime(m_bikeAnimIdx[PlayerState::E_BikeAnimation::BIKE_DRIVE], true);
		m_pPlayerModel->PlayAnime(m_playerAnimIdx[PlayerState::E_PlayerAnimation::PLAYER_DRIVE], true);
		m_bAutoRun = true;
		break;
	default:
		break;
	}
}