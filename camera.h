#ifndef __CAMERA_H__
#define __CAMERA_H__

//===== インクルード部 =====
#include <DirectXMath.h>	// DirectXが提供している数学系ライブラリ
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

	void Bind();		// 3D描画用
	void Bind2D();		// 2D描画用

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
	bool				m_isLate;		// カメラを遅らせるかどうか
	float				m_lateCoef;		// 遅れ係数
	//--- 極座標 ---
	float				m_xzAngle;	// XZ軸上での角度(0°で-Zの位置
	float				m_xyAngle;	// XY軸上での角度(0°で水平
	float				m_radius;	// 中心からの距離
	const float PI = 3.14159265359f;
	//--- 行列 ---
	DirectX::XMMATRIX	m_viewMat;
};


#endif // !__CAMERA_H__