//--------------------------------------------
//FileName:Time.h
//--------------------------------------------
//内容：タイマー(UI)の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2021/01/18   | 作成開始
//  2021/01/21   | 一部修正(受け取り部分・表示部分)
//  2021/01/22   | 書き足し(テキスト部分)
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

