//--------------------------------------------
//FileName:Meter.h
//--------------------------------------------
//内容：メーター(UI)の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2021/01/21   | 作成開始
//--------------------------------------------
#ifndef ___METER_H_
#define ___METER_H_

#include "DirectX.h"
#include "DrawBuffer.h"
#include "UI.h"
#include "Text.h"

class Meter : public UI
{
public:

	Meter();	// コンストラクタ
	~Meter();	// デストラクタ

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// スコアを取得
	void Set(float);

	void SetPos(float, float, float, float);
	void SetSize(float, float, float, float);


private:
	TEXT m_MeterText;

	float	m_meter;		// 速度を保存する
};

#endif // !___METER_H_
