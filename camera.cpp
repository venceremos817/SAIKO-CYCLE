//===== �C���N���[�h�� =====
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
	// �ɍ��W�n�F�p�x�ƒ����ō��W��\��
	// �������W�n�FX����Y���ō��W��\��
	// �������W�n�͐l���ς��ƌ��ŗ������₷��
	// �ɍ��W�n�͉~��`���悤�ȓ�����\�����₷��
	// x = sin�� * r
	// y = -cos�� * r
	// ��... �p�x / r... ���a
	// 3D�̋ɍ��W
	// x = sin�� * cos�� r
	// y = -cos�� * cos�� * r
	// z = sin�� * r

	// �J�����̊p�x�ύX
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
			m_radius -= 10.0f / 60;		// 1�b(60FPS)��10���[�g��
			if (m_radius < 0)
				m_radius = 0.001f;
		}
		else
		{
			m_xyAngle -= 1.0f;
			// �J�����̃A�b�v�x�N�g������ɏ�������Ă���̂łЂ�����Ԃ����G�͂Ƃ�Ȃ�
			// ����ɂ܂�������������Ԃ̊G������
			// �ʏ�3D�̃c�[���ł̓J�������^�ォ�猩���낷�A�^�����猩�グ��G�ɂȂ�Ȃ��悤�Ɉړ��̐����������Ă���B
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


	// �J�����ʒu�v�Z
	NormalCalc();
	if (m_isLate)
	{
		LateCalc();
	}
}


void Camera::NormalCalc()
{
	float xzRad = m_xzAngle * PI / 180.0f;		// ��
	float xyRad = m_xyAngle * PI / 180.0f;		// ��

	m_pos.x = sinf(xzRad) * cosf(xyRad) * m_radius;
	m_pos.y = sinf(xyRad) * m_radius;
	m_pos.z = -cosf(xzRad) * cosf(xyRad) * m_radius;
}

void Camera::LateCalc()
{
	// �x��\��
	// �{���ړ������������������Z���������ړ�������
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
	// �J�����̃p�����[�^��Shader�ɓn��
	// �J�������W�n�ɕϊ�
	if (m_isLate)
	{
		//----- �x��
		m_viewMat = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_latePos.x, m_latePos.y, m_latePos.z, 0.0f),		// ������:�J�����̈ʒu
			DirectX::XMVectorSet(m_lateLook.x, m_lateLook.y, m_lateLook.z, 0.0f),	// ������:�J�����̒����_
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f)			// ��O����:�J�����̏�����x�N�g��
		);
	}
	else
	{
		//----- �ʏ�
		m_viewMat = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),		// ������:�J�����̈ʒu
			DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),	// ������:�J�����̒����_
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f)			// ��O����:�J�����̏�����x�N�g��
		);
	}
	SHADER->SetView(m_viewMat);

	// �J�����̉�p�ݒ�
	SHADER->SetProjection(
		DirectX::XMMatrixPerspectiveFovLH
		(
			PI / 3.0f,									// ������:��p(���W�A���p
			(float)SCREEN_WIDTH / SCREEN_HEIGHT,		// ������:�A�X�y�N�g��
			m_near, m_far								// ��O����:�j�A�N���b�v(�ߌi�@��l����:�t�@�[�N���b�v(���i
		)
	);

	// �J�����̍��W���V�F�[�_�ɐݒ�
	SHADER->SetPSCameraPos(m_pos);

	// Z�o�b�t�@�L��
	EnableZBuffer(true);
}


void Camera::Bind2D()
{
	// 2D�̕\�����@�𕽍s���e�ƌĂ�(3D�͓������e)
	SHADER->SetView(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(0, 0, 0, 0.0f),		// ������:�J�����̈ʒu
			DirectX::XMVectorSet(0, 0, 1, 0.0f),		// ������:�J�����̒����_
			DirectX::XMVectorSet(0, 1, 0, 0.0f)			// ��O����:�J�����̏�����x�N�g��
		)
	);
	// ���P�ʍs��ŏȗ��ł���		���ǉ�ʗh�炵�Ƃ���肻��������Ƃ肠�������̂܂܎c���Ƃ�
	//SHADER->SetView(
	//	DirectX::XMMatrixIdentity()
	//);

	SHADER->SetProjection(
		DirectX::XMMatrixOrthographicLH
		(
			SCREEN_WIDTH, SCREEN_HEIGHT,		// �c����(x,y)
			0.0f, 500.0f						// �j�A�A�t�@�[�N���b�v
		)
	);

	// Z�o�b�t�@����
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