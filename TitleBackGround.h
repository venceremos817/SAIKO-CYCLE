//--------------------------------------------
//FileName:TitleBackGround.h
//--------------------------------------------
//���e�F�^�C�g���Ŏg���w�i�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/12/05   | �쐬�J�n
//--------------------------------------------
#ifndef ___TITLEBACKGROUND_H_
#define ___TITLEBACKGROUND_H_
#include "BackGround.h"

class TitleBackGround :public BackGround
{
public:
	TitleBackGround(void);
	~TitleBackGround(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

};



#endif // !___TITLEBACKGROUND_H_
