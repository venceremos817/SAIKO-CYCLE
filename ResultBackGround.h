//--------------------------------------------
//FileName:ResultBackGround.h
//--------------------------------------------
//内容：リザルトで使う背景の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/12/05   | 作成開始
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