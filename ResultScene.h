//--------------------------------------------
//FileName:ResultScene.h
//--------------------------------------------
//���e�F���U���g�V�[���̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/11/25   | �쐬�J�n
//  2020/12/06   | ��������(ResultBackGround�EResulrText)
//  2020/12/12   | ��������(MissionStar)
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