#include "Curve.h"

Model* Curve::m_pModel = nullptr;

Curve::Curve()
{
	// ヒットボックス設定
	m_pHitBox->SetSize(85.0992737f, 0.599999905f, 223.201416f);
	m_pHitBox->SetRot(0.0f, 0.610865295f, 0.0f);
	m_pHitBox->SetPos(42.0999336f, -0.300000012f, 85.0002289f);
}

Curve::~Curve()
{

}


HRESULT Curve::Init()
{
	if (m_pModel == nullptr)
	{
		m_pModel = new Model;
		m_pModel->LoadModel("Assets/Model/Stage/Curve5/Curve_9.fbx", true);
	}
	return S_OK;
}


void Curve::Uninit()
{
	if (m_pModel != nullptr)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
}


void Curve::Update()
{

}

void Curve::Draw()
{
	SetWorld();

	m_pModel->Draw();

#ifdef TEST_DEBUG
	m_pHitBox->testDraw(m_pos, m_size, m_rot);
#endif // TEST_DEBUG
}