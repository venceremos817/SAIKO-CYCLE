#pragma once

//===== �C���N���[�h�� =====
#include <DirectXMath.h>

//===== 2�����x�N�g�� =====
class myVector2
{
private:

public:
	float x, y;

	myVector2();

	myVector2(float x, float y);
	myVector2(DirectX::XMFLOAT2);

	// �v�f�̃Z�b�g
	void operator()(float x, float y);
	void operator()(DirectX::XMFLOAT2 vec);

	//===== �x�N�g���̉��Z =====
	// �x�N�g�� + �x�N�g��
	const myVector2 operator+(const myVector2& vec) const;

	// �x�N�g�� - �x�N�g��
	const myVector2 operator-(const myVector2& vec) const;

	// �x�N�g�� * �X�J���[
	const myVector2 operator*(const float& scalar) const;

	// �x�N�g�� / �X�J���[
	const myVector2 operator/(const float& scalar) const;

	// �x�N�g���̑傫���擾
	float GetLength();

	static float GetLength(const myVector2& vec);

	// ����
	static float dot(const myVector2& vec1, const myVector2& vec2);

	// �O��
	static float cross(const myVector2& vec1, const myVector2& vec2);

	// 2�̃x�N�g���̂Ȃ��p 0...��
	static float GetRadian(const myVector2& vec1, const myVector2& vec2);

	// �P�ʃx�N�g�����擾
	myVector2 GetNormalize();
	static myVector2 GetNormalize(const myVector2& vec);
};
// �X�J���[ * �x�N�g��
const myVector2 operator*(const float& scalar, const myVector2& vec);


//===== 3�����x�N�g�� =====
class myVector3
{
public:
	myVector3();
	myVector3(float x, float y, float z);
	myVector3(DirectX::XMFLOAT3 vec);
	~myVector3();

	//--- �v�f�̃Z�b�g ---
	void operator()(float x, float y, float z);
	void operator()(DirectX::XMFLOAT3 vec);

	//===== �x�N�g���̉��Z =====
	// �x�N�g�� + �x�N�g��
	const myVector3 operator+(const myVector3& vec) const;
	// �x�N�g�� - �x�N�g��
	const myVector3 operator-(const myVector3& vec) const;
	// �x�N�g�� * �X�J���[
	const myVector3 operator*(const float& scalar) const;
	// �x�N�g�� / �X�J���[
	const myVector3 operator/(const float& scalar) const;
	// �x�N�g���̑傫���擾
	float GetLength();
	static float GetLength(const myVector3& vec);
	// ����
	static float dot(const myVector3& vec1, const myVector3& vec2);
	// �O��
	static myVector3 cross(const myVector3& vec1, const myVector3& vec2);
	// 2�̃x�N�g���̂Ȃ��p 0...��
	static float GetRadian(const myVector3& vec1, const myVector3& vec2);
	// �P�ʃx�N�g�����擾
	myVector3 GetNormalize();
	static myVector3 GetNormalize(const myVector3& vec);
	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	static float LenSegOnSeparateAxis(myVector3 *Sep, myVector3 *e1, myVector3 *e2, myVector3 *e3 = 0);

	// �x�N�g���̉�]
	static void RotX(myVector3* vec, float rad);	// X�����ɉ�]
	static void RotY(myVector3* vec, float rad);	// Y�����ɉ�]
	static void RotZ(myVector3* vec, float rad);	// Z�����ɉ�]
	static void Rot(myVector3* vec, DirectX::XMFLOAT3 rad);


	DirectX::XMFLOAT3 ReturnXMFLOAT3();

public:
	float x;
	float y;
	float z;
};
// �X�J���[ * �x�N�g��
const myVector3 operator*(const float& scalar, const myVector3& vec);
