#pragma once


class Float2
{
public:
	Float2() { x = y = 0.0f; }
	Float2(float x, float y);

	float x;
	float y;

	void operator()(float x, float y);
	Float2 operator+(Float2 b);
	Float2 operator-(Float2 b);

	//Float2 operator=(Float2 a);
};


class Float3
{
public:
	Float3() { x = y = z = 0.0f; }
	Float3(float x, float y, float z);

	float x;
	float y;
	float z;

	void operator()(float x, float y, float z);
	Float3 operator+(Float3 b);
	Float3 operator-(Float3 b);
};

class Float4
{
public:
	Float4() { x = y = z = w = 0.0f; }
	Float4(float x, float y, float z, float w);

	float x;
	float y;
	float z;
	float w;

	void operator()(float x, float y, float z, float w);
	Float4 operator+(Float4 b);
	Float4 operator-(Float4 b);
};