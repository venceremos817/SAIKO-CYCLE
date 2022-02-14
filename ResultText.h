//--------------------------------------------
//FileName:ResultText.h
//--------------------------------------------
//���e�F���U���g�Ŏg���e�L�X�g�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/12/05   | �쐬�J�n
//  2021/01/21   | ��������(�萔��`)
//--------------------------------------------
#ifndef ___RESULTTEXT_H_
#define ___RESULTTEXT_H_

#include "Text.h"
#include "Controller.h"

//------�萔��`------
//�~�b�V�����e�L�X�g�֌W
#define MISSION_NUM (3)
#define MISSION_TEXT_SIZE_X (150.0f)
#define MISSION_TEXT_SIZE_Y (50.0f)
#define MISSION_INTERVAL (300)

//���U���g�I���֌W
#define RESULT_SELECT_NUM (2)
#define RESULT_SELECT_TEXT_SIZE_X (150.0f)
#define RESULT_SELECT_TEXT_SIZE_Y (37.5f)
#define RESULT_SIZE_UP_X (100.0f / 60)
#define RESULT_SIZE_UP_Y (25.0f / 60)
#define RESULTTEXT_LIMITE_SIZE_X (225.0f)
#define RESULTTEXT_LIMITE_SIZE_Y (56.25f)
#define RESULTTEXT_INTERVAL (200)

class ResultText :public Text
{
public:
	ResultText(void);
	~ResultText(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void ResultResetSize(void);
public:
	TEXT m_Resultlogo;
	TEXT m_ResultMissionText[MISSION_NUM];
	TEXT m_ResultMissionItemName[MISSION_NUM];
	TEXT m_ResultSelectText[RESULT_SELECT_NUM];

};


#endif // !___RESULTTEXT_H_