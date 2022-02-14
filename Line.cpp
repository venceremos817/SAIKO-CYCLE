//===== インクルード部 =====
#include "Line.h"
#include "Shader.h"



Line::Line()
{
	// 描画する直線の頂点情報
	//--- 頂点バッファ
	struct Vertex
	{
		float pos[3];
		float color[4];
	};

	Vertex vtx[] =
	{
		{ {0,0,0}, {1,1,1,1} },	// 始点
		{ {5,5,5}, {1,1,1,1} },	// 終点
	};

	m_Buffer.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(vtx[0]));
}


Line::~Line()
{

}


void Line::SetLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end)
{

}


void Line::Draw()
{
	SHADER->SetTexture(nullptr);
	// 直線のプリミティブ
	// 頂点バッファ内のデータを2つずつ読み取って直線を描画
	m_Buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}