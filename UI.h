//--------------------------------------------
//FileName:UI.h
//--------------------------------------------
//内容：UIの基盤
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2021/01/21   | 作成開始
//--------------------------------------------
#ifndef __UI_H__
#define __UI_H__

#include "DirectX.h"
#include "Shader.h"
#include "DrawBuffer.h"
#include <DirectXMath.h>

class UI
{
public:

	UI();	// コンストラクタ
	virtual ~UI();	// デストラクタ

	virtual void Draw();

	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT3 size);
	void SetRot(DirectX::XMFLOAT3 rot);

protected:
	void SetSplitUV(int index, int splitU,int splitV);

protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;
	DirectX::XMFLOAT3 m_rot;
	int m_index;
	int m_splitU;
	int m_splitV;
	DrawBuffer m_buffer;
	ID3D11ShaderResourceView*	m_pTexture;
};
#endif 