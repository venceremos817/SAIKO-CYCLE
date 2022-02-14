#include "GameScene.h"
#include "SceneMgr.h"
#include "Input.h"


//------定数定義------
//スコア表示用
//---数字
#define SCORE_POS_X   (600.0f)  //表示の位置X
#define SCORE_POS_Y   (340.0f)  //表示の位置Y
#define SCORE_SIZE_X  (10.0f)   //表示の大きさX
#define SCORE_SIZE_Y  (20.0f)   //表示の大きさY
//---テキスト
#define SCORETEXT_POS_X   (300.0f)  //表示の位置X
#define SCORETEXT_POS_Y   (340.0f)  //表示の位置Y
#define SCORETEXT_SIZE_X  (110.0f)   //表示の大きさX
#define SCORETEXT_SIZE_Y  (50.0f)   //表示の大きさY

//タイム表示用
//---数字
#define TIME_POS_X    (-440.0f)  //表示の位置X
#define TIME_POS_Y    (340.0f)   //表示の位置Y
#define TIME_SIZE_X   (10.0f)    //表示の大きさX
#define TIME_SIZE_Y   (20.0f)    //表示の大きさY
//---テキスト
#define TIMETEXT_POS_X    (-590.0f)  //表示の位置X
#define TIMETEXT_POS_Y    (340.0f)   //表示の位置Y
#define TIMETEXT_SIZE_X   (90.0f)    //表示の大きさX
#define TIMETEXT_SIZE_Y   (50.0f)    //表示の大きさY

//メーター表示用
//---数字
#define METER_POS_X   (500.0f)	 //表示の位置X
#define METER_POS_Y   (-300.0f)	 //表示の位置Y
#define METER_SIZE_X  (30.0f)	 //表示の大きさX
#define METER_SIZE_Y  (60.0f)	 //表示の大きさY
//---テキスト
#define METERTEXT_POS_X   (585.0f)	 //表示の位置X
#define METERTEXT_POS_Y   (-315.0f)	 //表示の位置Y
#define METERTEXT_SIZE_X  (110.0f)	 //表示の大きさX
#define METERTEXT_SIZE_Y  (80.0f)	 //表示の大きさY


// 静的メンバ定義
//XAUDIO2_BUFFER* GameScene::m_pBGM = nullptr;
Camera* GameScene::m_pCamera = nullptr;


GameScene::GameScene(void)
	: m_pPlayer(nullptr)
	, m_pSkyShpere(nullptr)
	, m_pSkyTex(nullptr)
	, m_pStage(nullptr)
	, m_pCollision(nullptr)
	, m_pStartDirecting(nullptr)
	, m_pScore(nullptr)
	, m_pTime(nullptr)
	, m_pCameraInverse(nullptr)
	, m_pEffectManager(nullptr)
	, m_pMeter(nullptr)
{

}


GameScene::~GameScene(void)
{
	Uninit();
}


void GameScene::Init(void)
{
	//if (m_pBGM == nullptr)
	//	m_pBGM = CreateSound("Assets/Sound/BGMGame.wav", true);
	//m_pBGMSpeaker = PlaySound(m_pBGM);

	if (m_pCamera == nullptr)
		m_pCamera = new TPSCamera;
	if (m_pPlayer == nullptr)
		m_pPlayer = new Player;
	if (m_pSkyShpere == nullptr)
		m_pSkyShpere = new SkySphere;
	if (m_pStage == nullptr)
		m_pStage = new Stage;
	if (m_pCollision == nullptr)
		m_pCollision = new Collision;
	if (m_pSkyTex == nullptr)
		LoadTextureFromFile("Assets/image/blueclou.png", &m_pSkyTex);
	if (m_pStartDirecting == nullptr)
		m_pStartDirecting = new StageStartDirecting;
	if (m_pScore == nullptr)
		m_pScore = new Score;
	if (m_pTime == nullptr)
		m_pTime = new Time;
	if (m_pMeter == nullptr)
		m_pMeter = new Meter;
	if (m_pCameraInverse == nullptr)
		m_pCameraInverse = new CameraInverse;
	if (m_pEffectManager == nullptr)
		m_pEffectManager = new EffectManager;
	
	
	m_pCamera->Init();
	m_pPlayer->Init();
	m_pStage->Init();
	m_pCollision->Init();
	m_pCamera->SetTargetObj(m_pPlayer);
	m_pPlayer->SetControllCamera(m_pCamera);
	m_pSkyShpere->SetTargetObj(m_pPlayer);
	m_pSkyShpere->SetTexture(m_pSkyTex);
	m_pSkyShpere->SetSize(m_pCamera->GetFar()*1.5f);
	m_pStartDirecting->Init();
	m_pScore->Init();
	m_pScore->SetPos(SCORE_POS_X, SCORE_POS_Y, SCORETEXT_POS_X, SCORETEXT_POS_Y);
	m_pScore->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y, SCORETEXT_SIZE_X, SCORETEXT_SIZE_Y);
	m_pTime->Init();
	m_pTime->SetPos(TIME_POS_X, TIME_POS_Y, TIMETEXT_POS_X, TIMETEXT_POS_Y);
	m_pTime->SetSize(TIME_SIZE_X, TIME_SIZE_Y, TIMETEXT_SIZE_X, TIMETEXT_SIZE_Y);
	m_pMeter->Init();
	m_pMeter->SetPos(METER_POS_X, METER_POS_Y, METERTEXT_POS_X, METERTEXT_POS_Y);
	m_pMeter->SetSize(METER_SIZE_X, METER_SIZE_Y, METERTEXT_SIZE_X, METERTEXT_SIZE_Y);
	m_pCameraInverse->Init();
	m_pCameraInverse->SetCamera(m_pCamera);
	m_pEffectManager->Init();

	m_pEffectManager->ActiveConcentedLine(true);
}


void GameScene::Uninit(void)
{
	SAFE_RELEASE(m_pSkyTex);
	UNINIT_DELETE(m_pCameraInverse);
	UNINIT_DELETE(m_pEffectManager);

	if (m_pMeter != nullptr)
	{
		m_pMeter->Uninit();
		delete m_pMeter;
		m_pMeter = nullptr;
	}

	UNINIT_DELETE(m_pTime);

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}
	if (m_pStartDirecting != nullptr)
	{
		m_pStartDirecting->Uninit();
		delete m_pStartDirecting;
		m_pStartDirecting = nullptr;
	}
	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = nullptr;
	}
	if (m_pStage != nullptr)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage= nullptr;
	}
	if (m_pSkyShpere != nullptr)
	{
		delete m_pSkyShpere;
		m_pSkyShpere = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}	

	// 
	//m_pBGMSpeaker->Stop();
}


E_SCENE_KIND GameScene::Update(void)
{
	m_pStartDirecting->Update();

	m_pPlayer->Update();
	m_pStage->Update();

	m_pScore->Update();
	m_pTime->Update();

	m_pCameraInverse->Update();

	Node<Field>* pFieldNode = Stage::GetFieldList()->GetHead();
	while (pFieldNode != nullptr)
	{
		m_pCollision->Register(m_pPlayer, pFieldNode->GetObj());
		pFieldNode = pFieldNode->GetNext();
	}

	m_pCollision->Update();

	m_pCamera->Update();
	m_pSkyShpere->Update();
	m_pEffectManager->Update();

	m_pMeter->Set(m_pPlayer->GetSpeed());


	//シーンの遷移判定
	if (IsKeyTrigger(VK_RETURN))
	{
		//SceneMgr::SetNextScene(E_SCENE_KIND::SCENE_RESULT);
		//m_pBGMSpeaker->Stop();
	}

	return SCENE_GAME;
}


void GameScene::Draw(void)
{
	SHADER->Bind(VS_WORLD, PS_PHONG);
	//SHADER->SetLightDir(DirectX::XMFLOAT4(0, 1, 0, 0));
	SHADER->SetLightAmbient(DirectX::XMFLOAT4(1, 1, 1, 1));
	SHADER->SetLightDiffuse(DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1));
	SHADER->SetAmbient(DirectX::XMFLOAT4(1, 1, 1, 1));
	SHADER->SetDiffuse(DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 1));
	SHADER->SetSpecular(DirectX::XMFLOAT4(1, 1, 1, 1), 50);

	//===== 3D描画 =====
	m_pCamera->Bind();
	//m_pSkyShpere->Draw();
	m_pSkyShpere->Draw();
	m_pStage->Draw();
	m_pPlayer->Draw();
	m_pEffectManager->Draw3D();

#ifdef TEST_DEBUG
	m_pCollision->TestDraw();
#endif // TEST_DEBUG


	//===== 2D描画 =====
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	//SHADER->SetLightAmbient(DirectX::XMFLOAT4(1, 1, 1, 1));
	SHADER->SetLightDiffuse(DirectX::XMFLOAT4(1, 1, 1, 1));
	SHADER->SetAmbient(DirectX::XMFLOAT4(1, 1, 1, 1));
	SHADER->SetDiffuse(DirectX::XMFLOAT4(1, 1, 1, 1));
	m_pCamera->Bind2D();
	
	m_pScore->Draw();
	m_pTime->Draw();
	m_pMeter->Draw();
	//m_pEffectManager->Draw2D();

	
	m_pStartDirecting->Draw();
}

float GameScene::SetScore(void)
{
	return m_pScore->Get();
}

float GameScene::SetTime(void)
{
	return m_pTime->Get();
}