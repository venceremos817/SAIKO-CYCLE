//--------------------------------------------
//FileName:TitleScene.h
//--------------------------------------------
//���e�F�^�C�g���V�[���̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/11/25   | �쐬�J�n
//  2020/12/05   | ��������(TitleBackGround�֌W)
//  2020/12/06   | ��������(TitleText�֌W)
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
