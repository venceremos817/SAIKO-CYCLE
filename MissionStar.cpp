//--------------------------------------------
//FileName:MissionStar.cpp
//--------------------------------------------
//内容：項目ごとの評価で使う星の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/12/10   | 作成開始
//--------------------------------------------
#include "MissionStar.h"
#include "Shader.h"
#include"Input.h"

//------定数定義------
#define SUCCESSSTAR_FILENAME "Assets/image/Star.png"
#define FAILURESTAR_FILENAME "Assets/image/NoStar.png"
#define STARSIZE_X (280.0f)
#define STARSIZE_Y (280.0f)
#define STAR_INTERVAL (300.0f)


MissionStar::MissionStar(void)
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		m_pStar[i].p_Star = new Board();
		m_pStar[i].p_Star->Init();

		m_pStar[i].m_bStarflg = false;

		m_pStar[i].fStarSize = DirectX::XMFLOAT2(STARSIZE_X, STARSIZE_Y);
	}

	LoadTextureFromFile(SUCCESSSTAR_FILENAME, &m_pStarTex.p_SuccessStarTex);
	LoadTextureFromFile(FAILURESTAR_FILENAME, &m_pStarTex.p_FailureStarTex);

}


MissionStar::~MissionStar(void)
{

}


void MissionStar::Init(void)
{



}


void MissionStar::Uninit(void)
{
	SAFE_RELEASE(m_pStarTex.p_SuccessStarTex);
	SAFE_RELEASE(m_pStarTex.p_FailureStarTex);

	for (int i = 0; i < 3; i++)
	{
		delete m_pStar[i].p_Star;
	}
}


void MissionStar::Draw(void)
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		SHADER->SetWorld(DirectX::XMMatrixScaling(m_pStar[i].fStarSize.x, m_pStar[i].fStarSize.y, 0) *
			DirectX::XMMatrixTranslation(-300.0f + STAR_INTERVAL * i, -20.0f, 0));

		if (m_pStar[i].m_bStarflg)
			SHADER->SetTexture(m_pStarTex.p_SuccessStarTex);
		else
			SHADER->SetTexture(m_pStarTex.p_FailureStarTex);

		m_pStar[i].p_Star->Draw();

	}

	SHADER->SetTexture(NULL);
}


void MissionStar::SetFlg(int nSelect, bool bflg)
{
	m_pStar[nSelect].m_bStarflg = bflg;
}
