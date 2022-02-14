//--------------------------------------------
//FileName:ResultText.h
//--------------------------------------------
//内容：リザルトで使うテキストの処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/12/05   | 作成開始
//  2021/01/21   | 書き足し(定数定義)
//--------------------------------------------
#ifndef ___RESULTTEXT_H_
#define ___RESULTTEXT_H_

#include "Text.h"
#include "Controller.h"

//------定数定義------
//ミッションテキスト関係
#define MISSION_NUM (3)
#define MISSION_TEXT_SIZE_X (150.0f)
#define MISSION_TEXT_SIZE_Y (50.0f)
#define MISSION_INTERVAL (300)

//リザルト選択関係
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