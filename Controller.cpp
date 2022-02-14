//===== インクルード部 =====
#include "Controller.h"
#include <Windows.h>

#define LSTICK_DEAD_ZONE	(100)
#define RSTICK_DEAD_ZONE	(15000)


//===== 静的メンバ =====
int Controller::m_nControllerNum = 0;


Controller::Controller()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));		// ゼロ初期化
	ZeroMemory(&m_preState, sizeof(XINPUT_STATE));

	DWORD dwResult;

	// ジョイパッドの情報格納先を設定
	dwResult = XInputGetState(m_nControllerNum, &m_State);
	if (dwResult == ERROR_SUCCESS)
	{
		// つながった
		m_bConect = true;
		m_dwControllerID = m_nControllerNum;
		m_nControllerNum++;
	}
	else
	{
		// つながってない
		m_bConect = false;
		m_dwControllerID = -1;
	}

}


Controller::~Controller()
{

}


HRESULT Controller::Init()
{
	DWORD dwResult;

	// ジョイパッドの情報格納先を設定
	dwResult = XInputGetState(m_dwControllerID, &m_State);
	if (dwResult == ERROR_SUCCESS)
	{
		// つながった
		return S_OK;
	}
	else
	{
		// つながってない
		return S_FALSE;
	}
}

void Controller::Update()
{
	if (!m_bConect) return;

	DWORD dwResult;

	// ジョイパッドの情報格納先を設定
	m_preState = m_State;		// 過去情報
	dwResult = XInputGetState(m_dwControllerID, &m_State);
	if (dwResult == ERROR_SUCCESS)
	{
		// つながった
	}
	else
	{
		// つながってない
	}
}


bool Controller::IsPress(WORD buttonID)
{
	if (m_State.Gamepad.wButtons&buttonID)
		return true;

	return false;
}


bool Controller::IsTrigger(WORD buttonID)
{
	// 前回押されている
	if (m_preState.Gamepad.wButtons&buttonID)
		return false;

	// 今回押されている
	if (m_State.Gamepad.wButtons&buttonID)
		return true;

	return false;
}


bool Controller::IsRelease(WORD buttonID)
{
	// 今回押してる
	if (m_State.Gamepad.wButtons&buttonID)
		return false;

	// 前回押してる
	if (m_preState.Gamepad.wButtons&buttonID)
		return true;

	return false;
}


bool Controller::IsLeftTrigger()
{
	if (m_State.Gamepad.bLeftTrigger > 30)
		return true;

	return false;
}

bool Controller::IsRightTrigger()
{
	if (m_State.Gamepad.bRightTrigger > 30)
		return true;

	return false;
}


DirectX::XMFLOAT2 Controller::GetLeftStick()
{
	DirectX::XMFLOAT2 LStick;

	// デッドゾーン
	if ((m_State.Gamepad.sThumbLX <  LSTICK_DEAD_ZONE &&
		m_State.Gamepad.sThumbLX > -LSTICK_DEAD_ZONE) &&
		(m_State.Gamepad.sThumbLY <  LSTICK_DEAD_ZONE &&
			m_State.Gamepad.sThumbLY > -LSTICK_DEAD_ZONE))
	{
		m_State.Gamepad.sThumbLX = 0;
		m_State.Gamepad.sThumbLY = 0;
	}

	LStick.x = m_State.Gamepad.sThumbLX;
	LStick.y = m_State.Gamepad.sThumbLY;


	return LStick;
}


DirectX::XMFLOAT2 Controller::GetRightStick()
{
	DirectX::XMFLOAT2 RStick;

	// デッドゾーン
	if ((m_State.Gamepad.sThumbRX <  RSTICK_DEAD_ZONE &&
		m_State.Gamepad.sThumbRX > -RSTICK_DEAD_ZONE) &&
		(m_State.Gamepad.sThumbRY <  RSTICK_DEAD_ZONE &&
			m_State.Gamepad.sThumbRY > -RSTICK_DEAD_ZONE))
	{
		m_State.Gamepad.sThumbRX = 0;
		m_State.Gamepad.sThumbRY = 0;
	}

	RStick.x = m_State.Gamepad.sThumbRX;
	RStick.y = m_State.Gamepad.sThumbRY;


	return RStick;
}