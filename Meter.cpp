//--------------------------------------------
//FileName:Meter.cpp
//--------------------------------------------
//内容：メーター(UI)の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2021/01/21   | 作成開始
//--------------------------------------------
#include "Meter.h"
#include "Shader.h"
#include "Texture.h"

//------定数定義------
#define METER_POS_X   (-0.2)   //位置Xの初期値
#define METER_POS_Y   (0.225)  //位置Yの初期値
#define METER_SIZE_X  (0.03)   //大きさXの初期値
#define METER_SIZE_Y  (0.03)   //大きさYの初期値
#define METER_SPLIT_U (5)      //テクスチャの分割数(横)  
#define METER_SPLIT_V (2)      //テクスチャの分割数(縦)


Meter::Meter():m_meter(0.0f)
{
	// ポジションの初期化
	m_pos.x = METER_POS_X;
	m_pos.y = METER_POS_Y;
	// サイズの初期化
	m_size.x = METER_SIZE_X;
	m_size.y = METER_SIZE_Y;
	// UVの初期化
	m_splitU = METER_SPLIT_U;
	m_splitV = METER_SPLIT_V;
}


Meter::~Meter()
{

}


void Meter::Init()
{
	HRESULT hr;
	hr = LoadTextureFromFile("Assets/image/numberYellow.png", &m_pTexture);

	m_MeterText.pBoard = new Board();
	hr = LoadTextureFromFile("Assets/image/text/kmhText.png", &m_MeterText.pTextTexture);
	m_MeterText.m_fTextPos = DirectX::XMFLOAT3(0, 0, 0);
	m_MeterText.m_fTextSize = DirectX::XMFLOAT2(1, 1);
}


void Meter::Uninit()
{
	SAFE_RELEASE(m_pTexture);


	delete m_MeterText.pBoard;
	SAFE_RELEASE(m_MeterText.pTextTexture);
}


void Meter::Update()
{

}


void Meter::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_MeterText.m_fTextSize.x, m_MeterText.m_fTextSize.y, 0) *
		DirectX::XMMatrixTranslation(m_MeterText.m_fTextPos.x, m_MeterText.m_fTextPos.y, 0.0f));
	SHADER->SetTexture(m_MeterText.pTextTexture);
	m_MeterText.pBoard->Draw();


	// 作業用変数
	int work = (m_meter * 100.0f) -1;

	work -= 13;
	if (work < 0)
		work = 0;

	SHADER->SetTexture(m_pTexture);

	for (int i = 0; i < 3; i++)
	{
		SetSplitUV(work % 10, m_splitU, m_splitV);

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			* DirectX::XMMatrixTranslation(m_pos.x - (i * (m_size.x * 1.5f + m_size.x)), m_pos.y, 0)
		);
		//m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		work /= 10;
	}
}


void Meter::Set(float fspeed)
{
	m_meter = fspeed;
}

void Meter::SetPos(float fposx, float fposy, float tposx, float tposy)
{
	m_pos.x = fposx;
	m_pos.y = fposy;
	m_MeterText.m_fTextPos.x = tposx;
	m_MeterText.m_fTextPos.y = tposy;
}


void Meter::SetSize(float fsizex, float fsizey, float tsizex, float tsizey)
{
	m_size.x = fsizex;
	m_size.y = fsizey;

	m_MeterText.m_fTextSize.x = tsizex;
	m_MeterText.m_fTextSize.y = tsizey;
}

