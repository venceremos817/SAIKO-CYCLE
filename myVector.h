#pragma once

//===== インクルード部 =====
#include <DirectXMath.h>

//===== 2次元ベクトル =====
class myVector2
{
private:

public:
	float x, y;

	myVector2();

	myVector2(float x, float y);
	myVector2(DirectX::XMFLOAT2);

	// 要素のセット
	void operator()(float x, float y);
	void operator()(DirectX::XMFLOAT2 vec);

	//===== ベクトルの演算 =====
	// ベクトル + ベクトル
	const myVector2 operator+(const myVector2& vec) const;

	// ベクトル - ベクトル
	const myVector2 operator-(const myVector2& vec) const;

	// ベクトル * スカラー
	const myVector2 operator*(const float& scalar) const;

	// ベクトル / スカラー
	const myVector2 operator/(const float& scalar) const;

	// ベクトルの大きさ取得
	float GetLength();

	static float GetLength(const myVector2& vec);

	// 内積
	static float dot(const myVector2& vec1, const myVector2& vec2);

	// 外積
	static float cross(const myVector2& vec1, const myVector2& vec2);

	// 2つのベクトルのなす角 0...π
	static float GetRadian(const myVector2& vec1, const myVector2& vec2);

	// 単位ベクトルを取得
	myVector2 GetNormalize();
	static myVector2 GetNormalize(const myVector2& vec);
};
// スカラー * ベクトル
const myVector2 operator*(const float& scalar, const myVector2& vec);


//===== 3次元ベクトル =====
class myVector3
{
public:
	myVector3();
	myVector3(float x, float y, float z);
	myVector3(DirectX::XMFLOAT3 vec);
	~myVector3();

	//--- 要素のセット ---
	void operator()(float x, float y, float z);
	void operator()(DirectX::XMFLOAT3 vec);

	//===== ベクトルの演算 =====
	// ベクトル + ベクトル
	const myVector3 operator+(const myVector3& vec) const;
	// ベクトル - ベクトル
	const myVector3 operator-(const myVector3& vec) const;
	// ベクトル * スカラー
	const myVector3 operator*(const float& scalar) const;
	// ベクトル / スカラー
	const myVector3 operator/(const float& scalar) const;
	// ベクトルの大きさ取得
	float GetLength();
	static float GetLength(const myVector3& vec);
	// 内積
	static float dot(const myVector3& vec1, const myVector3& vec2);
	// 外積
	static myVector3 cross(const myVector3& vec1, const myVector3& vec2);
	// 2つのベクトルのなす角 0...π
	static float GetRadian(const myVector3& vec1, const myVector3& vec2);
	// 単位ベクトルを取得
	myVector3 GetNormalize();
	static myVector3 GetNormalize(const myVector3& vec);
	// 分離軸に投影された軸成分から投影線分長を算出
	static float LenSegOnSeparateAxis(myVector3 *Sep, myVector3 *e1, myVector3 *e2, myVector3 *e3 = 0);

	// ベクトルの回転
	static void RotX(myVector3* vec, float rad);	// X軸回りに回転
	static void RotY(myVector3* vec, float rad);	// Y軸回りに回転
	static void RotZ(myVector3* vec, float rad);	// Z軸回りに回転
	static void Rot(myVector3* vec, DirectX::XMFLOAT3 rad);


	DirectX::XMFLOAT3 ReturnXMFLOAT3();

public:
	float x;
	float y;
	float z;
};
// スカラー * ベクトル
const myVector3 operator*(const float& scalar, const myVector3& vec);
