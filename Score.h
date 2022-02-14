//--------------------------------------------
//FileName:Score.h
//--------------------------------------------
//���e�F�X�R�A(UI)�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2021/01/16   | �쐬�J�n
//  2021/01/18   | �ꕔ�C��(�󂯎�蕔��)
//  2021/01/21   | �ꕔ�C��(�\������)
//  2021/01/22   | ��������(�e�L�X�g����)
//--------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "DirectX.h"
#include "DrawBuffer.h"
#include "UI.h"
#include "Text.h"

class Score : public UI
{
public:

	Score();	// �R���X�g���N�^
	~Score();	// �f�X�g���N�^

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �X�R�A�ɒǉ�
	//void Add(unsigned int addscore);
	static void Add(int addscore);
	// �X�R�A���擾
	int Get();
	// �X�R�A����}�C�i�X
	void Reduce(int minus);

	void SetPos(float, float, float, float);
	void SetSize(float, float, float, float);


private:
	TEXT m_ScoreText;

	static int	m_score;		// �X�R�A��ۑ�����
};

#endif _SOCRE_H_