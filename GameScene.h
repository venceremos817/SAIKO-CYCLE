#ifndef ___GAMESCENE_H_
#define ___GAMESCENE_H_
#include "Scene.h"

#include "TPSCamera.h"
#include "Player.h"
#include "SkySphere.h"
#include "Stage.h"
#include "Collision.h"
//#include "Sound.h"
#include "CameraInverse.h"
#include "EffectManager.h"

#include "StageStartDirecting.h"

#include "Score.h"
#include "Time.h"
#include "Meter.h"

#include "ResultScene.h"


class GameScene :public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	void Init(void);
	void Uninit(void);
	E_SCENE_KIND Update(void);
	void Draw(void);

	static Camera* GetCamera() { return m_pCamera; }

	float SetScore(void);
	float SetTime(void);

private:
	static Camera*	m_pCamera;
	Player*		m_pPlayer;
	SkySphere*	m_pSkyShpere;
	Stage*		m_pStage;
	Collision*	m_pCollision;
	ID3D11ShaderResourceView* m_pSkyTex;
	CameraInverse*	m_pCameraInverse;
	EffectManager*	m_pEffectManager;

	StageStartDirecting*	m_pStartDirecting;

	Score*	m_pScore;
	Time*	m_pTime;
	Meter*  m_pMeter;

	//// ƒTƒEƒ“ƒh
	//static XAUDIO2_BUFFER*	m_pBGM;
	//IXAudio2SourceVoice*	m_pBGMSpeaker;


//	ResultScene*	m_pResult;
};


#endif // !___GAMESCENE_H_