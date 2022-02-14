//--------------------------------------------
//FileName:TitleBackGround.h
//--------------------------------------------
//内容：タイトルで使う背景の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/12/05   | 作成開始
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
