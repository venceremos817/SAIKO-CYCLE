#pragma once
//==================================================
//	CMyColor.h
//--------------------------------------------------
//	author:大平哲士
//--------------------------------------------------
//	RGB,HSVの数値を扱う
//	各数値は 0.0f ～ 1.0f の範囲の値とする
//--- 更新履歴 ---
//	2020/09/06	製作開始
//		11/19	DirectX::XMFLOAT型に対応するためオーバーロード関数増やしたり
//==================================================

#include <DirectXMath.h>

class CMyColor
{
public:
	CMyColor();
	~CMyColor();

	void SetRGB(float r, float g, float b);
	void SetRGBA(float r, float g, float b, float a);
	void SetRGB(DirectX::XMFLOAT3 RGB);
	void SetRGBA(DirectX::XMFLOAT4 RGBA);
	void SetRed(float);
	void SetGreen(float);
	void SetBlue(float);

	DirectX::XMFLOAT3 GetRGB();
	DirectX::XMFLOAT4 GetRGBA();
	float GetRed();
	float GetGreen();
	float GetBlue();

	void SetHSV(float H, float S, float V);
	void SetHSVA(float H, float S, float V, float A);
	void SetHSV(DirectX::XMFLOAT3 HSV);
	void SetHSV(DirectX::XMFLOAT4 HSVA);
	void SetHue(float);
	void SetSaturation(float);
	void SetValue(float);
	DirectX::XMFLOAT3 GetHSV();
	DirectX::XMFLOAT4 GetHSVA();
	float GetHue();
	float GetSaturation();
	float GetValue();

	void SetAlpha(float);
	float GetAlpha();

private:
	DirectX::XMFLOAT3 m_RGB;
	DirectX::XMFLOAT3 m_HSV;
	float m_Alpha;

	// RGB→HSV
	void ConvertRGBintoHSV();
	// HSV→RGB
	void ConvertHSVintoRGB();
};

