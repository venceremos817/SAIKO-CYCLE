//--------------------------------------------
//FileName:Time.h
//--------------------------------------------
//���e�F�^�C�}�[(UI)�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2021/01/18   | �쐬�J�n
//  2021/01/21   | �ꕔ�C��(�󂯎�蕔���E�\������)
//  2021/01/22   | ��������(�e�L�X�g����)
//--------------------------------------------
#ifndef ___TIME_H_
#define ___TIME_H_

#include "UI.h"
#include "Text.h"

class Time : public UI
{
public:
	Time();
	~Time();

	void Init();
	void Uninit();

	void Update();
	void Draw();

	void SetPos(float, float, float, float);
	void SetSize(float, float, float, float);

	int Get();
private:
	TEXT m_TimeText;

	int m_time;
};

#endif // !___TIME_H_

