#ifndef __DRAW_BUFFER__
#define __DRAW_BUFFER__


//===== インクルード部 =====
#include "DirectX.h"


class DrawBuffer
{
public:
	DrawBuffer();
	~DrawBuffer();

	// DirectXはバッファに溜めた頂点情報を元に描画を行う。
	// 頂点の情報は増やしたり減らしたりすることができる。
	// そのため、引数で頂点の細かい情報を教える必要がある。
	// pVtx:描画に必要な頂点のデータ	size:一つ当たりの頂点のデータサイズ		count:描画する頂点の数
	HRESULT CreateVertexBuffer(void* pVtx, UINT size, UINT count, bool isWrite = false);

	// インデックスバッファの作成
	// 実際のモデルは同じ頂点を共有して三角形を描画することが多い
	// そこで三角形を描画する際に、直接頂点を指定するのではなく、インデックス(参照番号)を用いて描画する。
	// (多面体を描画するとき)頂点バッファのみで描画するよりもデータ量が軽くなる
	HRESULT CreateIndexBuffer(const long* pIdx, UINT count);

	// バッファの書き込み
	void Write(void* pData);

	// バッファの描画		D3D11_PRIMITIVE_TOPOLOGY: ポリゴンの描画方法	https://docs.microsoft.com/ja-jp/windows/uwp/graphics-concepts/primitive-topologies
	void Draw(D3D11_PRIMITIVE_TOPOLOGY primitive);

private:
	ID3D11Buffer*	m_pVtxBuffer;		// 頂点バッファ
	UINT			m_vtxSize;			// 頂点のデータサイズ
	UINT			m_vtxCount;			// 頂点の数
	ID3D11Buffer*	m_pIndexBuffer;		// インデックスバッファ
	UINT			m_idxCount;			// インデックスの数
};


#endif // !__DRAW_BUFFER__
