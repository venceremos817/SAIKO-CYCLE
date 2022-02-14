#include "JumpEffectParticle.h"
#include "CameraInverse.h"
#include "DirectX.h"

const int SPLIT_X = 4;
const int SPLIT_Y = 4;
const int ANIM_FRAME = 1;
const int TOTAL_FRAME = SPLIT_X * SPLIT_Y * ANIM_FRAME;


ID3D11ShaderResourceView* JumpEffectParticle::m_pTexture = nullptr;



JumpEffectParticle::JumpEffectParticle()
	: m_pos(0, 0, 0)
	, m_size(1, 1, 1)
	, m_frame(0)
	, m_AnimIdx(0)
	, m_pBoard(nullptr)
	, m_move(0, 0, 0)
{
	if (m_pBoard == nullptr)
	{
		m_pBoard = new Board;
	}
}


JumpEffectParticle::~JumpEffectParticle()
{
	if (m_pBoard != nullptr)
	{
		delete m_pBoard;
		m_pBoard = nullptr;
	}
}


HRESULT JumpEffectParticle::Init()
{
	HRESULT hr;

	if (m_pTexture == nullptr)
	{
		hr = LoadTextureFromFile("Assets/image/effect/effect0.png", &m_pTexture);
		if (FAILED(hr)) { return hr; }
	}

	return hr;
}


void JumpEffectParticle::Uninit()
{
	SAFE_RELEASE(m_pTexture);
}


void JumpEffectParticle::Update()
{
	if (IsFinish())
		return;

	if (m_frame % ANIM_FRAME == 0)
	{
		m_AnimIdx++;	// ƒRƒ}‚ðˆê‚Âi‚ß‚é
		m_pBoard->SetUV(m_AnimIdx, SPLIT_X, SPLIT_Y);
	}

	m_pos = m_pFollowObj->GetHitBox()->GetPos(m_pFollowObj->GetPos(), m_pFollowObj->GetSize(), m_pFollowObj->GetRot());
	m_frame++;
}


void JumpEffectParticle::Draw()
{
	if (IsFinish())
		return;

	EnableZBuffer(false);
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	SHADER->SetTexture(m_pTexture);
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * CameraInverse::GetInversMatrix() * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pBoard->Draw();
	SHADER->Bind(VS_WORLD, PS_PHONG);
	EnableZBuffer(true);
}


bool JumpEffectParticle::IsFinish()
{
	return m_frame >= TOTAL_FRAME;
}