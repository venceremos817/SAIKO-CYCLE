#include "myVector.h"
#include <math.h>

const float PI = acosf(-1.0f);

// �R���X�g���N�^
myVector2::myVector2()
	: x(0), y(0)
{
}

myVector2::myVector2(float x, float y)
	: x(x), y(y)
{
}

myVector2::myVector2(DirectX::XMFLOAT2 vec)
	: x(vec.x), y(vec.y)
{
}

// �v�f�̐ݒ�
void myVector2::operator()(float x, float y)
{
	this->x = x;
	this->y = y;
}

void myVector2::operator()(DirectX::XMFLOAT2 vec)
{
	x = vec.x;
	y = vec.y;
}

// �x�N�g�� + �x�N�g��
const myVector2 myVector2::operator+(const myVector2& vec) const
{
	myVector2 ret;

	ret.x = x + vec.x;
	ret.y = y + vec.y;

	return ret;
}

// �x�N�g�� - �x�N�g��
const myVector2 myVector2::operator-(const myVector2& vec) const
{
	myVector2 ret;

	ret.x = x - vec.x;
	ret.y = y - vec.y;

	return ret;
}

// �x�N�g�� * �X�J���[
const myVector2 myVector2::operator*(const float& sc) const
{
	myVector2 ret;

	ret.x = x * sc;
	ret.y = y * sc;

	return ret;
}


// �X�J���[ * �x�N�g��
const myVector2 operator*(const float& scalar, const myVector2& vec)
{
	myVector2 ret;

	ret.x = vec.x * scalar;
	ret.y = vec.y * scalar;

	return ret;
}


// �x�N�g�� / �X�J���[
const myVector2 myVector2::operator/(const float& scalar) const
{
	myVector2 ret;

	ret.x = x / scalar;
	ret.y = y / scalar;

	return ret;
}


// ����
float myVector2::dot(const myVector2& vec1, const myVector2& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}


// �O��
float myVector2::cross(const myVector2& vec1, const myVector2& vec2)
{
	return vec1.x*vec2.y - vec1.y*vec2.x;
}


// 2�̃x�N�g���̂Ȃ��p 0...��
float myVector2::GetRadian(const myVector2& vec1, const myVector2& vec2)
{
	// �[���x�N�g���Ȃ�Ȃ��p���o���Ȃ�
	if (GetLength(vec1) * GetLength(vec2) == 0)
		return 0;

	float x = dot(vec1, vec2) / (GetLength(vec1) * GetLength(vec2));

	if (x > 1.0f)
	{
		x = 1.0f;
	}
	else if (x < -1.0f)
	{
		x = -1.0f;
	}

	// rad = arccos( A dot B / |A|*|B| )
	//return acosf(dot(vec1, vec2) / (GetLength(vec1) * GetLength(vec2)));
	return acosf(x);
}


// �x�N�g���̑傫���擾
float myVector2::GetLength()
{
	return sqrtf(x * x + y * y);
}


float myVector2::GetLength(const myVector2& vec)
{
	return sqrtf(vec.x*vec.x + vec.y*vec.y);
}


// �P�ʃx�N�g�����擾
myVector2 myVector2::GetNormalize()
{
	myVector2 ret(0, 0);
	float len = GetLength();
	
	if (len == 0)
	{
		return ret;
	}

	ret.x = x;
	ret.y = y;

	return ret / len;
}

myVector2 myVector2::GetNormalize(const myVector2& vec)
{
	float len = GetLength(vec);

	if (len == 0)
	{
		myVector2 ret;
		return ret;
	}

	return vec / len;
}




//===== 3�����x�N�g�� =====
myVector3::myVector3()
	:x(0), y(0), z(0)
{
}

myVector3::myVector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}
myVector3::myVector3(DirectX::XMFLOAT3 vec)
	: x(vec.x), y(vec.y), z(vec.z)
{
}


myVector3::~myVector3()
{

}


//--- �v�f�̃Z�b�g ---
void myVector3::operator()(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void myVector3::operator()(DirectX::XMFLOAT3 vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

//===== �x�N�g���̉��Z =====
// �x�N�g�� + �x�N�g��
const myVector3 myVector3::operator+(const myVector3& vec) const
{
	myVector3 ret;

	ret.x = x + vec.x;
	ret.y = y + vec.y;
	ret.z = z + vec.z;

	return ret;
}

// �x�N�g�� - �x�N�g��
const myVector3 myVector3::operator-(const myVector3& vec) const
{
	myVector3 ret;

	ret.x = x - vec.x;
	ret.y = y - vec.y;
	ret.z = z - vec.z;

	return ret;
}

// �x�N�g�� * �X�J���[
const myVector3 myVector3::operator*(const float& scalar) const
{
	myVector3 ret;

	ret.x = x * scalar;
	ret.y = y * scalar;
	ret.z = z * scalar;

	return ret;
}
// �X�J���[ * �x�N�g��
const myVector3 operator*(const float& scalar, const myVector3& vec)
{
	myVector3 ret;

	ret.x = vec.x * scalar;
	ret.y = vec.y * scalar;
	ret.z = vec.z * scalar;

	return ret;
}

// �x�N�g�� / �X�J���[
const myVector3 myVector3::operator/(const float& scalar) const
{
	myVector3 ret;

	ret.x = x / scalar;
	ret.y = y / scalar;
	ret.z = z / scalar;

	return ret;
}

// �x�N�g���̑傫���擾
float myVector3::GetLength()
{
	return sqrtf(x * x + y * y + z * z);
}

float myVector3::GetLength(const myVector3& vec)
{
	return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

// ����
float myVector3::dot(const myVector3& vec1, const myVector3& vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

// �O��
myVector3 myVector3::cross(const myVector3& vec1, const myVector3& vec2)
{
	myVector3 ret;

	ret.x = vec1.y*vec2.z - vec1.z*vec2.y;
	ret.y = vec1.z*vec2.x - vec1.x*vec2.z;
	ret.z = vec1.x*vec2.y - vec1.y*vec2.x;

	return ret;
}

// 2�̃x�N�g���̂Ȃ��p 0...��
float myVector3::GetRadian(const myVector3& vec1, const myVector3& vec2)
{
	// �[���x�N�g���͊p�x���o���Ȃ�
	if (GetLength(vec1)*GetLength(vec2) == 0.0f)
	{
		return 0;
	}

	float x = dot(vec1, vec2) / (GetLength(vec1)*GetLength(vec2));

	if (x > 1.0f)
	{
		x = 1.0f;
	}
	else if (x < -1.0f)
	{
		x = -1.0f;
	}

	return acosf(x);
}

// �P�ʃx�N�g�����擾
myVector3 myVector3::GetNormalize()
{
	myVector3 ret;
	float len = GetLength();

	if (len == 0.0f)
	{
		return ret;
	}

	ret.x = x / len;
	ret.y = y / len;
	ret.z = z / len;

	return ret;
}

myVector3 myVector3::GetNormalize(const myVector3& vec)
{
	float len = GetLength(vec);

	if (len == 0.0f)
	{
		myVector3 ret;
		return ret;
	}

	return vec / len;
}


float myVector3::LenSegOnSeparateAxis(myVector3 *Sep, myVector3 *e1, myVector3 *e2, myVector3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͒P�ʉ�����Ă��邱��
	//Sep = &Sep->GetNormalize();
	float r1 = fabsf(dot(*Sep, *e1));
	float r2 = fabsf(dot(*Sep, *e2));
	float r3 = e3 ? (fabsf(dot(*Sep, *e3))) : 0;

	return r1 + r2 + r3;
}

void myVector3::RotX(myVector3* vec, float rad)
{
	myVector3 work;

	work.x = vec->x;
	work.y = vec->y * cosf(rad) - vec->z * sinf(rad);
	work.z = vec->y * sinf(rad) + vec->z * cosf(rad);

	*vec = work;
}

void myVector3::RotY(myVector3* vec, float rad)
{
	myVector3 work;

	work.x = vec->x * cosf(rad) + vec->z * sinf(rad);
	work.y = vec->y;
	work.z = -vec->x * sinf(rad) + vec->z * cosf(rad);

	*vec = work;
}

void myVector3::RotZ(myVector3* vec, float rad)
{
	myVector3 work;

	work.x = vec->x * cosf(rad) - vec->y * sinf(rad);
	work.y = vec->x * sinf(rad) + vec->y * cosf(rad);
	work.z = vec->z;

	*vec = work;
}

void myVector3::Rot(myVector3* vec, DirectX::XMFLOAT3 rad)
{
//	RotZ(vec, rad.z);
	RotX(vec, rad.x);
	RotY(vec, rad.y);
	RotZ(vec, rad.z);
}


DirectX::XMFLOAT3 myVector3::ReturnXMFLOAT3()
{
	return DirectX::XMFLOAT3(x, y, z);
}