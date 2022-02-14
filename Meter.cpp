//--------------------------------------------
//FileName:Meter.cpp
//--------------------------------------------
//���e�F���[�^�[(UI)�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2021/01/21   | �쐬�J�n
//--------------------------------------------
#include "Meter.h"
#include "Shader.h"
#include "Texture.h"

//------�萔��`------
#define METER_POS_X   (-0.2)   //�ʒuX�̏����l
#define METER_POS_Y   (0.225)  //�ʒuY�̏����l
#define METER_SIZE_X  (0.03)   //�傫��X�̏����l
#define METER_SIZE_Y  (0.03)   //�傫��Y�̏����l
#define METER_SPLIT_U (5)      //�e�N�X�`���̕�����(��)  
#define METER_SPLIT_V (2)      //�e�N�X�`���̕�����(�c)


Meter::Meter():m_meter(0.0f)
{
	// �|�W�V�����̏�����
	m_pos.x = METER_POS_X;
	m_pos.y = METER_POS_Y;
	// �T�C�Y�̏�����
	m_size.x = METER_SIZE_X;
	m_size.y = METER_SIZE_Y;
	// UV�̏�����
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


	// ��Ɨp�ϐ�
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

