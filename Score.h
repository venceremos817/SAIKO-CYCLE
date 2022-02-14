//--------------------------------------------
//FileName:Score.h
//--------------------------------------------
//内容：スコア(UI)の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2021/01/16   | 作成開始
//  2021/01/18   | 一部修正(受け取り部分)
//  2021/01/21   | 一部修正(表示部分)
//  2021/01/22   | 書き足し(テキスト部分)
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

	Score();	// コンストラクタ
	~Score();	// デストラクタ

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// スコアに追加
	//void Add(unsigned int addscore);
	static void Add(int addscore);
	// スコアを取得
	int Get();
	// スコアからマイナス
	void Reduce(int minus);

	void SetPos(float, float, float, float);
	void SetSize(float, float, float, float);


private:
	TEXT m_ScoreText;

	static int	m_score;		// スコアを保存する
};

#endif _SOCRE_H_