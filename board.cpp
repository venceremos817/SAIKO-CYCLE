#include "board.h"


struct Vertex
{
	float pos[3];		// x, y
	float color[4];		// r, g, b, a
	float uv[2];		// u, v
};

// コンストラクタ
Board::Board() : m_ptexture(NULL), Size(0.5f)
{

	Vertex vtx[] = {
		// 2D板
		{ { -Size , Size, 0 },{ 1,1,1,1 },{ 0,0 } },	// 左上
		{ {  Size , Size, 0 },{ 1,1,1,1 },{ 1,0 } },	// 右上
		{ { -Size ,-Size, 0 },{ 1,1,1,1 },{ 0,1 } },	// 左下
		{ {  Size , Size, 0 },{ 1,1,1,1 },{ 1,0 } },	// 右上
		{ {  Size ,-Size, 0 },{ 1,1,1,1 },{ 1,1 } },	// 右下
		{ { -Size ,-Size, 0 },{ 1,1,1,1 },{ 0,1 } },	// 左下
	};

	m_BufferB.CreateVertexBuffer(vtx, sizeof(Vertex), sizeof(vtx) / sizeof(Vertex), true);


}
// デストラクタ
Board::~Board()
{
	Uninit();
}

void Board::Init()
{



}
void Board::Uninit()
{

}
void Board::Draw()
{
	m_BufferB.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Board::SetUV(int index, int splitX, int splitY)
{
	float u;
	float v;


	u = index % splitY;
	v = index / splitX;

	Vertex vtx[] = {
		// 2D板
		{ { -Size , Size, 0 },{ 1,1,1,1 },{  u / splitX,  v / splitY } },	// 左上
		{ {  Size , Size, 0 },{ 1,1,1,1 },{ (u + 1) / splitX,  v / splitY } },	// 右上
		{ { -Size ,-Size, 0 },{ 1,1,1,1 },{  u / splitX, (v + 1) / splitY } },	// 左下
		{ {  Size , Size, 0 },{ 1,1,1,1 },{ (u + 1) / splitX,  v / splitY } },	// 右上
		{ {  Size ,-Size, 0 },{ 1,1,1,1 },{ (u + 1) / splitX, (v + 1) / splitY } },	// 右下
		{ { -Size ,-Size, 0 },{ 1,1,1,1 },{  u / splitX, (v + 1) / splitY } },	// 左下
	};

	m_BufferB.Write(vtx);
}
