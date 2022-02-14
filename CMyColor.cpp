#include "CMyColor.h"



CMyColor::CMyColor()
	: m_RGB(1, 1, 1)
{
	m_Alpha = 0;
	ConvertRGBintoHSV();
}


CMyColor::~CMyColor()
{
}


void CMyColor::SetAlpha(float alpha)
{
	this->m_Alpha = alpha;
}


float CMyColor::GetAlpha()
{
	return this->m_Alpha;
}


void CMyColor::SetRGB(float red, float green, float blue)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
	
	ConvertRGBintoHSV();
}


void CMyColor::SetRGBA(float red, float green, float blue,float alpha)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
	SetAlpha(alpha);

	ConvertRGBintoHSV();
}

void CMyColor::SetRGB(DirectX::XMFLOAT3 RGB)
{
	SetRed(RGB.x);
	SetBlue(RGB.y);
	SetGreen(RGB.z);
	ConvertRGBintoHSV();
}

void CMyColor::SetRGBA(DirectX::XMFLOAT4 RGBA)
{
	SetRed(RGBA.x);
	SetBlue(RGBA.y);
	SetGreen(RGBA.z);
	SetAlpha(RGBA.w);
	ConvertRGBintoHSV();
}

void CMyColor::SetRed(float red)
{
	while (red > 1.0f)
	{
		red -= 1.0f;
	}

	while (red < 0.0f)
	{
		red += 1.0f;
	}

	this->m_RGB.x = red;
	ConvertRGBintoHSV();
}


void CMyColor::SetGreen(float green)
{
	while (green > 1.0f)
	{
		green -= 1.0f;
	}

	while (green < 0.0f)
	{
		green += 1.0f;
	}

	this->m_RGB.y = green;
	ConvertRGBintoHSV();
}


void CMyColor::SetBlue(float blue)
{
	while (blue > 1.0f)
	{
		blue -= 1.0f;
	}

	while (blue < 0.0f)
	{
		blue += 1.0f;
	}

	this->m_RGB.z = blue;
	ConvertRGBintoHSV();
}


DirectX::XMFLOAT3 CMyColor::GetRGB()
{
	return this->m_RGB;
}

DirectX::XMFLOAT4 CMyColor::GetRGBA()
{
	return DirectX::XMFLOAT4(m_RGB.x, m_RGB.y, m_RGB.z, m_Alpha);
}


float CMyColor::GetRed()
{
	return this->m_RGB.x;
}


float CMyColor::GetGreen()
{
	return this->m_RGB.y;
}


float CMyColor::GetBlue()
{
	return this->m_RGB.z;
}



void CMyColor::SetHSV(float hue, float saturation, float value)
{
	SetHue(hue);
	SetSaturation(saturation);
	SetValue(value);
	ConvertHSVintoRGB();
}


void CMyColor::SetHSVA(float hue, float saturation, float value,float alpha)
{
	SetHue(hue);
	SetSaturation(saturation);
	SetValue(value);
	SetAlpha(alpha);
	ConvertHSVintoRGB();
}


void CMyColor::SetHSV(DirectX::XMFLOAT3 HSV)
{
	SetHue(HSV.x);
	SetSaturation(HSV.y);
	SetSaturation(HSV.z);
	ConvertHSVintoRGB();
}

void CMyColor::SetHSV(DirectX::XMFLOAT4 HSVA)
{
	SetHue(HSVA.x);
	SetSaturation(HSVA.y);
	SetValue(HSVA.z);
	SetAlpha(HSVA.w);
	ConvertHSVintoRGB();
}


void CMyColor::SetHue(float hue)
{
	while (hue > 1.0f)
	{
		hue -= 1.0f;
	}

	while (hue < 0.0f)
	{
		hue += 1.0f;
	}

	this->m_HSV.x = hue;
	ConvertHSVintoRGB();
}


void CMyColor::SetSaturation(float saturation)
{
	while (saturation > 1.0f)
	{
		saturation -= 1.0f;
	}

	while (saturation < 0.0f)
	{
		saturation += 1.0f;
	}

	this->m_HSV.y = saturation;
	ConvertHSVintoRGB();
}


void CMyColor::SetValue(float value)
{
	while (value > 1.0f)
	{
		value -= 1.0f;
	}

	while (value < 0.0f)
	{
		value += 1.0f;
	}

	this->m_HSV.z = value;
	ConvertHSVintoRGB();
}


DirectX::XMFLOAT3 CMyColor::GetHSV()
{
	return this->m_HSV;
}

DirectX::XMFLOAT4 CMyColor::GetHSVA()
{
	return DirectX::XMFLOAT4(m_HSV.x, m_HSV.y, m_HSV.z, m_Alpha);
}


float CMyColor::GetHue()
{
	return this->m_HSV.x;
}


float CMyColor::GetSaturation()
{
	return this->m_HSV.y;
}


float CMyColor::GetValue()
{
	return this->m_HSV.z;
}


void CMyColor::ConvertRGBintoHSV()
{
	float max = m_RGB.x > m_RGB.y ? m_RGB.x : m_RGB.y;
	max = max > m_RGB.z ? max : m_RGB.z;
	float min = m_RGB.x < m_RGB.y ? m_RGB.x : m_RGB.y;
	min = min < m_RGB.y ? min : m_RGB.y;
	m_HSV.x = max - min;
	if (m_HSV.x > 0.0f)
	{
		if (max == m_RGB.x)
		{
			m_HSV.x = (m_RGB.y - m_RGB.y) / m_HSV.x;
			if (m_HSV.x < 0.0f)
			{
				m_HSV.x += 6.0f;
			}
		}
		else if (max == m_RGB.y)
		{
			m_HSV.x = 2.0f + (m_RGB.y - m_RGB.x) / m_HSV.x;
		}
		else
		{
			m_HSV.x = 4.0f + (m_RGB.x - m_RGB.y) / m_HSV.x;
		}
	}
	m_HSV.x /= 6.0f;
	m_HSV.y = (max - min);
	if (max != 0.0f)
		m_HSV.y /= max;
	m_HSV.z = max;
}


void CMyColor::ConvertHSVintoRGB()
{
	m_RGB.x = m_HSV.z;
	m_RGB.y = m_HSV.z;
	m_RGB.z = m_HSV.z;
	if (m_HSV.y > 0.0f) {
		m_HSV.x *= 6.0f;
		const int i = (int)m_HSV.x;
		const float f = m_HSV.x - (float)i;
		switch (i) {
		default:
		case 0:
			m_RGB.y *= 1 - m_HSV.y * (1 - f);
			m_RGB.z *= 1 - m_HSV.y;
			break;
		case 1:
			m_RGB.x *= 1 - m_HSV.y * f;
			m_RGB.z *= 1 - m_HSV.y;
			break;
		case 2:
			m_RGB.x *= 1 - m_HSV.y;
			m_RGB.z *= 1 - m_HSV.y * (1 - f);
			break;
		case 3:
			m_RGB.x *= 1 - m_HSV.y;
			m_RGB.y *= 1 - m_HSV.y * f;
			break;
		case 4:
			m_RGB.x *= 1 - m_HSV.y * (1 - f);
			m_RGB.y *= 1 - m_HSV.y;
			break;
		case 5:
			m_RGB.y *= 1 - m_HSV.y;
			m_RGB.z *= 1 - m_HSV.y * f;
			break;
		}
	}
}