#ifndef __BASIC_FIGURE_H__
#define __BASIC_FIGURE_H__

//===================================
//	基本図形 基底クラス
//===================================

//===== インクルード部 =====
#include "CommonClass.h"
#include <DirectXMath.h>
#include "DrawBuffer.h"


class BasicFigure
{
public:
	BasicFigure();
	BasicFigure(D3D11_PRIMITIVE_TOPOLOGY);
	BasicFigure(D3D11_PRIMITIVE_TOPOLOGY, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size);
	virtual ~BasicFigure();

	virtual void SetPos(float x, float y, float z);
	virtual void SetPos(Float3 pos);
	virtual void SetPos(DirectX::XMFLOAT3 pos);

	virtual void SetSize(float width, float height, float depth);
	virtual void SetSize(Float3 size);
	virtual void SetSize(DirectX::XMFLOAT3 size);
	virtual void SetSize(float scale);

	virtual void SetRot(DirectX::XMFLOAT3 rot);

	virtual void SetTexture(ID3D11ShaderResourceView*);

	virtual void Draw();

protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;
	DirectX::XMFLOAT3 m_rot;
	DrawBuffer m_buffer;
	ID3D11ShaderResourceView*	m_pTexture;
	D3D11_PRIMITIVE_TOPOLOGY	m_primitive;
};
#endif // !__BASIC_FIGURE_H__


