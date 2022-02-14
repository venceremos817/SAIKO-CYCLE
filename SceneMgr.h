#ifndef ___SCENEMGR_H_
#define ___SCENEMGR_H_
#include "Scene.h"
//#include "DShow.h"

#include "Sound.h"


class SceneMgr
{
public:
	SceneMgr(void);
	~SceneMgr(void);

	void Init(void);
	void Uninit(void);
	bool Update(void);
	void Draw(void);

	static void SetNextScene(E_SCENE_KIND nextScene);

private:
	Scene* m_pScene;
	Scene* m_pResultScene;
	E_SCENE_KIND m_SceneMode;
	static E_SCENE_KIND m_Next_SceneMode;
	//DShow*	m_pRoadingMovie;

	// ƒTƒEƒ“ƒh
	XAUDIO2_BUFFER* m_pTitleBGM;
	XAUDIO2_BUFFER* m_pGameBGM;
	XAUDIO2_BUFFER* m_pResultBGM;
	IXAudio2SourceVoice*	m_pBGMSpeaker;
};


#endif // !___SCENEMGR_H_



