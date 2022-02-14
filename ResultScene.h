//--------------------------------------------
//FileName:ResultScene.h
//--------------------------------------------
//内容：リザルトシーンの処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/11/25   | 作成開始
//  2020/12/06   | 書き足し(ResultBackGround・ResulrText)
//  2020/12/12   | 書き足し(MissionStar)
//--------------------------------------------
#ifndef ___RESULTSCENE_H_
#define ___RESULTSCENE_H_
#include "Scene.h"
#include "Camera.h"
#include "ResultBackGround.h"
#include "ResultText.h"
#include "MissionStar.h"

class ResultScene :public Scene
{
public:
	ResultScene(void);
	~ResultScene(void);

	void Init(void);
	void Uninit(void);
	E_SCENE_KIND Update(void);
	void Draw(void);

	void GetScore(float);
	void GetTime(float);

private:
	Camera *m_pResultCamera;
	ResultBackGround *m_pResultBackGround;
	ResultText *m_pResultText;
	MissionStar *m_pMStar;
};


#endif // !___RESULTSCENE_H_