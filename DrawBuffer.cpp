#include "DrawBuffer.h"




DrawBuffer::DrawBuffer()
	: m_pVtxBuffer(NULL)
	, m_vtxSize(0)
	, m_vtxCount(0)
	, m_pIndexBuffer(NULL)
	, m_idxCount(0)
{

}


DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pIndexBuffer);	// インデックスバッファの開放
	SAFE_RELEASE(m_pVtxBuffer);		// 頂点バッファの解放
}



HRESULT DrawBuffer::CreateVertexBuffer(void* pVtx, UINT size, UINT count, bool isWrite)
{
	//--- 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	// バッファの大きさ
	bufDesc.ByteWidth = size * count;
	// バッファの使用方法
	if (isWrite)
	{
		// 書き換え可
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		// 書き換え不可
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	// バッファの利用先(利用方法)
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//--- バッファの初期値設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	// 初期化に使うデータの置き場所(アドレス)の指定
	subResource.pSysMem = pVtx;

	//--- 頂点バッファの作成
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVtxBuffer);

	//--- その他の情報を設定
	if (SUCCEEDED(hr))
	{
		m_vtxSize = size;
		m_vtxCount = count;
	}

	return hr;
}


HRESULT DrawBuffer::CreateIndexBuffer(const long* pIdx, UINT count)
{
	//--- 作成するバッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	// バッファの大きさ
	bufDesc.ByteWidth = sizeof(long)*count;
	// バッファの使用方法
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	// バッファの利用先
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	//--- バッファの初期値設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	// 初期化に使うデータの置き場所
	subResource.pSysMem = pIdx;

	//--- インデックスバッファの作成
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIndexBuffer);

	//--- その他情報の設定
	if (SUCCEEDED(hr))
	{
		m_idxCount = count;
	}

	return hr;
}


void DrawBuffer::Write(void* pData)
{
	ID3D11DeviceContext* pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	HRESULT hr;
	
	hr = pContext->Map(m_pVtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	// Map関数で書き込みOKであれば実行
	if (SUCCEEDED(hr))
	{
		// 引数で渡された頂点情報をマップ領域にコピー
		memcpy_s(
			mapResource.pData,
			m_vtxSize * m_vtxCount,
			pData,
			m_vtxSize * m_vtxCount);
	}

	// 書き込み終了
	pContext->Unmap(m_pVtxBuffer, 0);
}


void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext = GetContext();
	// 頂点一つ当たりの大きさ
	UINT stride = m_vtxSize;
	// 頂点データの読み取り開始位置
	UINT offset = 0;

	//--- プリミティブの設定
	// TriangleList... 頂点を3つずつに区切って描画	
	// 例)	[0,1,2] [3,4,5]
	// TriangleStrip... 参照箇所を1つずつずらしながら描画
	// 例)	[0,1,2] [1,2,3] [2,3,4]
	pContext->IASetPrimitiveTopology(primitive);

	// 描画に使用するバッファの設定
	pContext->IASetVertexBuffers(
		0,					// GPUへの割り当て先
		1,					// 頂点バッファの数
		&m_pVtxBuffer,		// 頂点バッファ
		&stride,			// 頂点のサイズ
		&offset				// 読み取り開始位置
	);

	// 描画
	// インデックスバッファの有無で描画処理が異なる
	if (m_idxCount > 0)
	{
		// 描画に使用するインデックスバッファを設定
		pContext->IASetIndexBuffer(
			m_pIndexBuffer,
			DXGI_FORMAT_R32_UINT,	// インデックス1つあたりの大きさ	4byte = 32bit / 2byte = 16bit
			0
		);

		// インデックスバッファを用いた描画
		pContext->DrawIndexed(m_idxCount, 0, 0);

	}
	else
	{
		// 頂点バッファのみで描画
		pContext->Draw(m_vtxCount, 0);
	}

}