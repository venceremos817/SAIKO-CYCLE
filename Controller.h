#pragma once

//===== インクルード部 =====
#include "DirectX.h"
#include <DirectXMath.h>
#pragma comment(lib,"xinput.lib")
#include <Xinput.h>




class Controller
{
public:
	Controller();
	~Controller();

	HRESULT Init();
	void Update();

	bool IsPress(WORD buttonID);		//各ボタンの値 https://docs.microsoft.com/ja-jp/previous-versions/direct-x/bb174833(v=vs.85)	// このままクリックすると最後のカッコ閉じ ')' がつかないので手動で付けて
	bool IsTrigger(WORD buttonID);
	bool IsRelease(WORD buttonID);
	bool IsLeftTrigger();
	bool IsRightTrigger();
	DirectX::XMFLOAT2 GetLeftStick();
	DirectX::XMFLOAT2 GetRightStick();
	XINPUT_STATE GetState() { return m_State; };

private:
	XINPUT_STATE	m_State;		// ゲームパッドの状態
	XINPUT_STATE	m_preState;		// ゲームパッドの状態
	PXINPUT_KEYSTROKE	m_KeyStroke;	// キーの入力状況
	DWORD		m_dwControllerID;	// コントローラーのインデックス
	static int	m_nControllerNum;	// 接続されているコントローラーの数
	bool		m_bConect;			// 接続されているかどうか
};


