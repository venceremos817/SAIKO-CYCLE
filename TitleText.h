//--------------------------------------------
//FileName:TitleText.h
//--------------------------------------------
//内容：タイトルで使うテキストの処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/12/05   | 作成開始
//  2021/01/21   | 書き足し(定数定義)
//--------------------------------------------
#ifndef ___TITLETEXT_H_
#define ___TITLETEXT_H_

#include "Text.h"
#include "Controller.h"

//------定数定義------
//セレクト項目関係
#define MAX_SELECT_NUM            (2)            //項目数
#define TEXT_INTERVAL             (250.0f)       //項目の間の間隔
#define SELECTTEXT_DEFAULT_SIZE_X (300.0f)       //大きさXの初期値
#define SELECTTEXT_DEFAULT_SIZE_Y (100.0f)       //大きさYの初期値
#define SELECTTEXT_DEFAULT_POS_X  (400.0f)       //位置Xの初期値
#define SELECTTEXT_DEFAULT_POS_Y  (150.0f)       //位置Yの初期値
#define SIZE_UP_X                 (200.0f / 60)  //大きくなる速度X
#define SIZE_UP_Y                 (50.0f / 60)   //大きくなる速度Y
#define TITLETEXT_LIMITE_SIZE_X   (450.0f)       //大きくなる上限X
#define TITLETEXT_LIMITE_SIZE_Y   (75.0f)        //大きくなる上限Y

//タイトルロゴ関係
#define LOGOTEXT_DEFAULT_SIZE_X (1300.0f)  //大きさXの初期値
#define LOGOTEXT_DEFAULT_SIZE_Y (850.0f)   //大きさYの初期値
#define LOGOTEXT_DEFAULT_POS_X  (0.0f)     //位置Xの初期値
#define LOGOTEXT_DEFAULT_POS_Y  (20.0f)    //位置Yの初期値
#define LOGOTEXT_MENU_SIZE_X    (1000.0f)  //メニュー中の大きさX
#define LOGOTEXT_MENU_SIZE_Y    (800.0f)   //メニュー中の大きさY
#define LOGOTEXT_MENU_POS_X     (-220.0f)  //メニュー中の位置X
#define LOGOTEXT_MENU_POS_Y     (20.0f)    //メニュー中の位置Y

//プッシュテキスト関係
#define PUSHTEXT_DEFAULT_SIZE_X (500.0f)     //大きさXの初期値
#define PUSHTEXT_DEFAULT_SIZE_Y (300.0f)     //大きさYの初期値
#define PUSHTEXT_DEFAULT_POS_X  (0.0f)       //位置Xの初期値
#define PUSHTEXT_DEFAULT_POS_Y  (-200.0f)    //位置Yの初期値
#define PUSHTEXT_TOP            (-195.0f)    //テキスト位置の上限  
#define PUSHTEXT_BOTTOM         (-205.0f)    //テキスト位置の下限
#define PUSHTEXT_UPDOWN_SPEED   (15.0 / 60)  //移動速度

class TitleText:public Text
{
public:
	TitleText(void);
	~TitleText(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool GetMenuFlg(void);

	void SetMenuFlg(bool);


	void ResetSize(void);
	void LogoANDPushReset(void);

private:
	TEXT m_Titlelogo;
	TEXT m_PushText;
	bool m_bPushText;
	TEXT m_TitleSelectText[MAX_SELECT_NUM];


	bool m_bMenu;
	bool m_bOldMenu;


};


#endif // !___TITLETEXT_H_
