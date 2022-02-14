#include "JumpRamp.h"

Model* JumpRamp::m_pModel = nullptr;


JumpRamp::JumpRamp()
{
	// オブジェクト特性
	//SetObjectType(E_ObjectType::TYPE_PLANE);
	//SetCollisionType(E_ObjectCollisionType::COLLISION_TYPE_STATIC);

	// ヒットボックス設定
	m_pHitBox->SetSize(6.09999657f, 0.599999905f, 16.6000271f);
	m_pHitBox->SetRot(-0.305551171f, 0, 0);
	m_pHitBox->SetPos(-0.100000001f, 2.20000005f, 6.69999599f);
}

JumpRamp::~JumpRamp()
{

}


HRESULT JumpRamp::Init()
{
	HRESULT hr = S_OK;
	if (m_pModel == nullptr)
	{
		m_pModel = new Model;
		m_pModel->LoadModel("Assets/Model/Stage/JampRamp/ramp_12.fbx");
	}

	return hr;
}


void JumpRamp::Uninit()
{
	if (m_pModel != nullptr)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
}


void JumpRamp::Update()
{

}


void JumpRamp::Draw()
{
	SetWorld();
	m_pModel->Draw();

#ifdef TEST_DEBUG
	m_pHitBox->testDraw(m_pos, m_size, m_rot);
#endif // TEST_DEBUG
}