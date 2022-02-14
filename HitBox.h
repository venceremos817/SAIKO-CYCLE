#pragma once

#include <DirectXMath.h>
#include "DebugDefine.h"
#include "Cube.h"
#include "myVector.h"


class HitBox
{
public:
	HitBox();
	HitBox(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 rot);
	virtual ~HitBox();

	void SetPos(DirectX::XMFLOAT3 pos);
	void SetPos(float x, float y, float z);
	void SetSize(DirectX::XMFLOAT3 size);
	void SetSize(float x, float y, float z);
	void SetRot(DirectX::XMFLOAT3 rot);
	void SetRot(float x, float y, float z);

	// 引数としてオブジェクトのワールド座標を入れる
	DirectX::XMFLOAT3 GetPos(DirectX::XMFLOAT3 objPos, DirectX::XMFLOAT3 objSize, DirectX::XMFLOAT3 objRot);
	DirectX::XMFLOAT3 GetSize(DirectX::XMFLOAT3 objSize);
	DirectX::XMFLOAT3 GetRot(DirectX::XMFLOAT3 objRot);

	myVector3 GetDirectW(int elem, DirectX::XMFLOAT3 objRot);

#ifdef TEST_DEBUG
	Cube m_TestCube;
	void testDraw(DirectX::XMFLOAT3 objPos, DirectX::XMFLOAT3 objSize, DirectX::XMFLOAT3 objRot);
#endif // TEST_DEBUG


protected:
	// オブジェクトがローカル座標にある時の当たり判定
	DirectX::XMFLOAT3 m_pos;	// オブジェクトが 0,0,0 にある時のヒットボックスの中心座標
	DirectX::XMFLOAT3 m_size;	// オブジェクトのスケールが 1,1,1 の時のヒットボックスのスケール
	DirectX::XMFLOAT3 m_rot;	// オブジェクトの回転が 0,0,0 の時のヒットボックスの回転
};