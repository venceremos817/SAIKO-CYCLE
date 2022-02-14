#include "ConcentratedLine.h"
#include "Defines.h"

const int SPLIT_X = 4;
const int SPLIT_Y = 4;
const int ANIM_NUM = SPLIT_X * SPLIT_Y;
const int ANIM_SPEED = 1;


ConcentratedLine::ConcentratedLine()
	: m_pBoard(nullptr)
	, m_pTexture(nullptr)
	, m_Frame(0)
	, m_AnimIdx(0)
	, m_active(false)
{
	Init();
}

ConcentratedLine::~ConcentratedLine()
{
	Uninit();
}


HRESULT ConcentratedLine::Init()
{
	HRESULT hr = S_OK;

	if (m_pTexture == nullptr)
	{
		hr = LoadTextureFromFile("Assets/image/effect/effect2.png", &m_pTexture);
		if (FAILED(hr)) { return hr; }
	}

	if (m_pBoard == nullptr)
	{
		m_pBoard = new Board;
	}

	return hr;
}


void ConcentratedLine::Uninit()
{
	if (m_pBoard != nullptr)
	{
		delete m_pBoard;
		m_pBoard = nullptr;
	}

	SAFE_RELEASE(m_pTexture);
}


void ConcentratedLine::Update()
{
	if (!m_active)
		return;

	if (m_Frame % ANIM_SPEED == 0)
	{
		m_AnimIdx++;	// ƒRƒ}‚ðˆê‚Âi‚ß‚é
		m_AnimIdx %= ANIM_NUM;
		m_pBoard->SetUV(m_AnimIdx, SPLIT_X, SPLIT_Y);
	}

	m_Frame++;
}


void ConcentratedLine::Draw()
{
	if (!m_active)
		return;

	SHADER->SetTexture(m_pTexture);
	SHADER->SetWorld(DirectX::XMMatrixScaling(SCREEN_WIDTH, SCREEN_HEIGHT, 1));

	m_pBoard->Draw();
}