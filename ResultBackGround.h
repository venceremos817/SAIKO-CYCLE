//--------------------------------------------
//FileName:ResultBackGround.h
//--------------------------------------------
//���e�F���U���g�Ŏg���w�i�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/12/05   | �쐬�J�n
//--------------------------------------------
#ifndef ___RESULTBACKGROUND_H_
#define ___RESULTBACKGROUND_H_
#include "BackGround.h"

class ResultBackGround :public BackGround
{
public:
	ResultBackGround(void);
	~ResultBackGround(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

};



#endif // !___RESULTBACKGROUND_H_