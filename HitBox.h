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

	// �����Ƃ��ăI�u�W�F�N�g�̃��[���h���W������
	DirectX::XMFLOAT3 GetPos(DirectX::XMFLOAT3 objPos, DirectX::XMFLOAT3 objSize, DirectX::XMFLOAT3 objRot);
	DirectX::XMFLOAT3 GetSize(DirectX::XMFLOAT3 objSize);
	DirectX::XMFLOAT3 GetRot(DirectX::XMFLOAT3 objRot);

	myVector3 GetDirectW(int elem, DirectX::XMFLOAT3 objRot);

#ifdef TEST_DEBUG
	Cube m_TestCube;
	void testDraw(DirectX::XMFLOAT3 objPos, DirectX::XMFLOAT3 objSize, DirectX::XMFLOAT3 objRot);
#endif // TEST_DEBUG


protected:
	// �I�u�W�F�N�g�����[�J�����W�ɂ��鎞�̓����蔻��
	DirectX::XMFLOAT3 m_pos;	// �I�u�W�F�N�g�� 0,0,0 �ɂ��鎞�̃q�b�g�{�b�N�X�̒��S���W
	DirectX::XMFLOAT3 m_size;	// �I�u�W�F�N�g�̃X�P�[���� 1,1,1 �̎��̃q�b�g�{�b�N�X�̃X�P�[��
	DirectX::XMFLOAT3 m_rot;	// �I�u�W�F�N�g�̉�]�� 0,0,0 �̎��̃q�b�g�{�b�N�X�̉�]
};