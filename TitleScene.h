//--------------------------------------------
//FileName:TitleScene.h
//--------------------------------------------
//内容：タイトルシーンの処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/11/25   | 作成開始
//  2020/12/05   | 書き足し(TitleBackGround関係)
//  2020/12/06   | 書き足し(TitleText関係)
//--------------------------------------------
#ifndef ___TITLESCENE_H_
#define ___TITLESCENE_H_
#include "Scene.h"
#include "Camera.h"
#include "Defines.h"
#include "TitleBackGround.h"
#include "TitleText.h"

class TitleScene :public Scene
{
public:
	TitleScene(void);
	~TitleScene(void);

	void Init(void);
	void Uninit(void);
	E_SCENE_KIND Update(void);
	void Draw(void);

private:
	Camera *m_pCamera;
	TitleBackGround *m_TitleBackGround;
	TitleText *m_TitleText;
};


#endif // !___TITLESCENE_H_
