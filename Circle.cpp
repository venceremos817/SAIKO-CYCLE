//======================================
//	基本図形	円
//======================================

//===== インクルード部 =====
#include "Circle.h"
#include <math.h>


//===== 定数定義 =====
const float PI = 3.14159265359f;




Circle::Circle()
	:BasicFigure(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	//--- 頂点バッファ
	struct Vertex
	{
		float pos[3];
		float color[4];
		float uv[2];
	};

	int vertexNum = 40;
	float fRadius = 0.5f;

	// 頂点数分の配列確保
	Vertex* pVertex = new Vertex[vertexNum + 1];
	Vertex* pVertexWork;
	Float2 baseCirclePos;
	int nWork;

	// 円周上に頂点を置く
	for (pVertexWork = pVertex, nWork = 0; nWork < vertexNum ; nWork++, pVertexWork++)
	{
		baseCirclePos.x = cosf(-(float)nWork / vertexNum * PI * 2);
		baseCirclePos.y = sinf(-(float)nWork / vertexNum * PI * 2);

		pVertexWork->pos[0] = baseCirclePos.x * fRadius;		// x
		pVertexWork->pos[1] = 0.0f;								// y
		pVertexWork->pos[2] = baseCirclePos.y * fRadius;		// z

		pVertexWork->uv[0] = baseCirclePos.x*0.5f + 0.5f;
		pVertexWork->uv[1] = baseCirclePos.y*0.5f + 0.5f;

		pVertexWork->color[0] = 1.0f;
		pVertexWork->color[1] = 1.0f;
		pVertexWork->color[2] = 1.0f;
		pVertexWork->color[3] = 1.0f;
	}
	// 中心点
	pVertex[vertexNum] = { { 0.0f, 0.0f , 0.0f},{ 1, 1, 1, 1},{0.5f, 0.5f} };

	long* pIdx = new long[vertexNum * 3];
	long* pIdxWork = pIdx;

	for (int i = 0; i < vertexNum; i++, pIdxWork++)
	{
		*pIdxWork = vertexNum;
		pIdxWork++;
		*pIdxWork = i;
		pIdxWork++;
		*pIdxWork = (i + 1) % vertexNum;
	}
	
	m_buffer.CreateVertexBuffer(
		pVertex, sizeof(Vertex),
		vertexNum + 1
	);

	m_buffer.CreateIndexBuffer(
		pIdx,
		(vertexNum + 1) * 3
	);

	delete[] pVertex;
	delete[] pIdx;
}


Circle::Circle(int a)
	:BasicFigure(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	//--- 頂点バッファ
	struct Vertex
	{
		float pos[3];
		float color[4];
		float uv[2];
	};

	int vertexNum = a;
	float fRadius = 0.5f;

	// 頂点数分の配列確保
	Vertex* pVertex = new Vertex[vertexNum + 1];
	Vertex* pVertexWork;
	Float2 baseCirclePos;
	int nWork;

	// 円周上に頂点を置く
	for (pVertexWork = pVertex, nWork = 0; nWork < vertexNum; nWork++, pVertexWork++)
	{
		baseCirclePos.x = cosf(-(float)nWork / vertexNum * PI * 2);
		baseCirclePos.y = sinf(-(float)nWork / vertexNum * PI * 2);

		pVertexWork->pos[0] = baseCirclePos.x * fRadius;		// x
		pVertexWork->pos[1] = 0.0f;								// y
		pVertexWork->pos[2] = baseCirclePos.y * fRadius;		// z

		pVertexWork->uv[0] = baseCirclePos.x*0.5f + 0.5f;
		pVertexWork->uv[1] = baseCirclePos.y*0.5f + 0.5f;

		pVertexWork->color[0] = 1.0f;
		pVertexWork->color[1] = 1.0f;
		pVertexWork->color[2] = 1.0f;
		pVertexWork->color[3] = 1.0f;
	}
	// 中心点
	pVertex[vertexNum] = { { 0.0f, 0.0f , 0.0f},{ 1, 1, 1, 1},{0.5f, 0.5f} };

	long* pIdx = new long[vertexNum * 3];
	long* pIdxWork = pIdx;

	for (int i = 0; i < vertexNum; i++, pIdxWork++)
	{
		*pIdxWork = vertexNum;
		pIdxWork++;
		*pIdxWork = i;
		pIdxWork++;
		*pIdxWork = (i + 1) % vertexNum;
	}

	m_buffer.CreateVertexBuffer(
		pVertex, sizeof(Vertex),
		vertexNum + 1
	);

	m_buffer.CreateIndexBuffer(
		pIdx,
		(vertexNum + 1) * 3
	);

	delete[] pVertex;
	delete[] pIdx;
}

Circle::~Circle()
{

}