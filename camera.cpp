//===== インクルード部 =====
#include "Camera.h"
#include "Defines.h"
#include "Input.h"
#include "Shader.h"




Camera::Camera()
	: m_radius(20.0f)
	, m_pos(0, 0, -m_radius)
	, m_look(0, 0, 0)
	, m_up(0, 1, 0)
	, m_angle(60.0f)
	, m_near(0.5f)
	, m_far(500.0f)
	, m_xzAngle(0.0f)
	, m_xyAngle(0.0f)
	, m_isLate(false)
	, m_lateCoef(0.1f)
{
	m_latePos = m_pos;
	m_lateLook = m_look;
}


Camera::~Camera()
{

}




void Camera::Init()
{

}


void Camera::Uninit()
{

}


void Camera::Update()
{
	// 極座標系：角度と長さで座標を表す
	// 直交座標系：X軸とY軸で座標を表す
	// 直交座標系は人がぱっと見で理解しやすい
	// 極座標系は円を描くような動きを表現しやすい
	// x = sinΘ * r
	// y = -cosΘ * r
	// Θ... 角度 / r... 半径
	// 3Dの極座標
	// x = sinΘ * cosφ r
	// y = -cosΘ * cosφ * r
	// z = sinφ * r

	// カメラの角度変更
	if (IsKeyPress(VK_LEFT))
	{
		m_xzAngle += 1.0f;
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_xzAngle -= 1.0f;
	}
	if (IsKeyPress(VK_UP))
	{
		if (IsKeyPress(VK_SHIFT))
		{
			m_radius -= 10.0f / 60;		// 1秒(60FPS)に10メートル
			if (m_radius < 0)
				m_radius = 0.001f;
		}
		else
		{
			m_xyAngle -= 1.0f;
			// カメラのアップベクトルが常に上を向いているのでひっくり返った絵はとれない
			// ※常にまっすぐ立った状態の絵が取れる
			// 通常3Dのツールではカメラが真上から見下ろす、真下から見上げる絵にならないように移動の制限をかけている。
			if (m_xyAngle <= -90.0f)
			{
				m_xyAngle = -89.99999f;
			}
		}
	}
	if (IsKeyPress(VK_DOWN))
	{
		if (IsKeyPress(VK_SHIFT))
		{
			m_radius += 10.0f / 60;
		}
		else
		{
			m_xyAngle += 1.0f;
			if (m_xyAngle >= 90.0f)
			{
				m_xyAngle = 89.99999f;
			}
		}
	}


	// カメラ位置計算
	NormalCalc();
	if (m_isLate)
	{
		LateCalc();
	}
}


void Camera::NormalCalc()
{
	float xzRad = m_xzAngle * PI / 180.0f;		// Θ
	float xyRad = m_xyAngle * PI / 180.0f;		// φ

	m_pos.x = sinf(xzRad) * cosf(xyRad) * m_radius;
	m_pos.y = sinf(xyRad) * m_radius;
	m_pos.z = -cosf(xzRad) * cosf(xyRad) * m_radius;
}

void Camera::LateCalc()
{
	// 遅れ表現
	// 本来移動させたい距離よりも短い距離を移動させる
	DirectX::XMFLOAT3 move(
		m_look.x - m_lateLook.x,
		m_look.y - m_lateLook.y,
		m_look.z - m_lateLook.z
	);
	
	move.x *= m_lateCoef;
	move.y *= m_lateCoef;
	move.z *= m_lateCoef;
	m_lateLook = DirectX::XMFLOAT3(
		move.x + m_lateLook.x,
		move.y + m_lateLook.y,
		move.z + m_lateLook.z
	);

	DirectX::XMFLOAT3 posMove(
		m_pos.x - m_latePos.x,
		m_pos.y - m_latePos.y,
		m_pos.z - m_latePos.z
	);
	posMove.x *= m_lateCoef;
	posMove.y *= m_lateCoef;
	posMove.z *= m_lateCoef;
	m_latePos = DirectX::XMFLOAT3(
		posMove.x + m_latePos.x,
		posMove.y + m_latePos.y,
		posMove.z + m_latePos.z
	);
}


void Camera::SetXZAngle(float Angle)
{
	m_xzAngle = Angle;
}



void Camera::Bind()
{
	// カメラのパラメータをShaderに渡す
	// カメラ座標系に変換
	if (m_isLate)
	{
		//----- 遅れ
		m_viewMat = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_latePos.x, m_latePos.y, m_latePos.z, 0.0f),		// 第一引数:カメラの位置
			DirectX::XMVectorSet(m_lateLook.x, m_lateLook.y, m_lateLook.z, 0.0f),	// 第二引数:カメラの注視点
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f)			// 第三引数:カメラの上方向ベクトル
		);
	}
	else
	{
		//----- 通常
		m_viewMat = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),		// 第一引数:カメラの位置
			DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),	// 第二引数:カメラの注視点
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f)			// 第三引数:カメラの上方向ベクトル
		);
	}
	SHADER->SetView(m_viewMat);

	// カメラの画角設定
	SHADER->SetProjection(
		DirectX::XMMatrixPerspectiveFovLH
		(
			PI / 3.0f,									// 第一引数:画角(ラジアン角
			(float)SCREEN_WIDTH / SCREEN_HEIGHT,		// 第二引数:アスペクト比
			m_near, m_far								// 第三引数:ニアクリップ(近景　第四引数:ファークリップ(遠景
		)
	);

	// カメラの座標をシェーダに設定
	SHADER->SetPSCameraPos(m_pos);

	// Zバッファ有効
	EnableZBuffer(true);
}


void Camera::Bind2D()
{
	// 2Dの表示方法を平行投影と呼ぶ(3Dは透視投影)
	SHADER->SetView(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(0, 0, 0, 0.0f),		// 第一引数:カメラの位置
			DirectX::XMVectorSet(0, 0, 1, 0.0f),		// 第二引数:カメラの注視点
			DirectX::XMVectorSet(0, 1, 0, 0.0f)			// 第三引数:カメラの上方向ベクトル
		)
	);
	// ↑単位行列で省略できる		けど画面揺らしとかやりそうだからとりあえずそのまま残しとく
	//SHADER->SetView(
	//	DirectX::XMMatrixIdentity()
	//);

	SHADER->SetProjection(
		DirectX::XMMatrixOrthographicLH
		(
			SCREEN_WIDTH, SCREEN_HEIGHT,		// 縦横比(x,y)
			0.0f, 500.0f						// ニア、ファークリップ
		)
	);

	// Zバッファ無効
	EnableZBuffer(false);
}


DirectX::XMFLOAT3 Camera::GetPos()
{
	return m_pos;
}


float Camera::GetxzAngle()
{
	return m_xzAngle;
}


void Camera::isLate(bool isLate)
{
	m_isLate = isLate;
}