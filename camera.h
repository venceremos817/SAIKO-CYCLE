#ifndef __CAMERA_H__
#define __CAMERA_H__

//===== �C���N���[�h�� =====
#include <DirectXMath.h>	// DirectX���񋟂��Ă��鐔�w�n���C�u����
#include "GameObject.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Init();
	void Uninit();
	virtual void Update();
	void isLate(bool isLate);

	void Bind();		// 3D�`��p
	void Bind2D();		// 2D�`��p

	virtual void SetTargetObj(GameObject *pObj) {};
	void SetXZAngle(float Angle);
	void SetCameraLength(float len) { m_radius = len; }
	void SetLateCoef(float lateCoef) { m_lateCoef = lateCoef; }

	DirectX::XMFLOAT3 GetPos();
	float GetxzAngle();
	DirectX::XMMATRIX GetViewMat() { return m_viewMat; }
	float GetFar() { return m_far; }

protected:
	virtual void NormalCalc();
	virtual void LateCalc();

protected:
	DirectX::XMFLOAT3	m_pos;
	DirectX::XMFLOAT3	m_latePos;
	DirectX::XMFLOAT3	m_look;
	DirectX::XMFLOAT3	m_lateLook;
	DirectX::XMFLOAT3	m_up;
	float				m_angle;
	float				m_near;
	float				m_far;
	bool				m_isLate;		// �J������x�点�邩�ǂ���
	float				m_lateCoef;		// �x��W��
	//--- �ɍ��W ---
	float				m_xzAngle;	// XZ����ł̊p�x(0����-Z�̈ʒu
	float				m_xyAngle;	// XY����ł̊p�x(0���Ő���
	float				m_radius;	// ���S����̋���
	const float PI = 3.14159265359f;
	//--- �s�� ---
	DirectX::XMMATRIX	m_viewMat;
};


#endif // !__CAMERA_H__