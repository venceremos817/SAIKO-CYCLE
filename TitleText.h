//--------------------------------------------
//FileName:TitleText.h
//--------------------------------------------
//���e�F�^�C�g���Ŏg���e�L�X�g�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/12/05   | �쐬�J�n
//  2021/01/21   | ��������(�萔��`)
//--------------------------------------------
#ifndef ___TITLETEXT_H_
#define ___TITLETEXT_H_

#include "Text.h"
#include "Controller.h"

//------�萔��`------
//�Z���N�g���ڊ֌W
#define MAX_SELECT_NUM            (2)            //���ڐ�
#define TEXT_INTERVAL             (250.0f)       //���ڂ̊Ԃ̊Ԋu
#define SELECTTEXT_DEFAULT_SIZE_X (300.0f)       //�傫��X�̏����l
#define SELECTTEXT_DEFAULT_SIZE_Y (100.0f)       //�傫��Y�̏����l
#define SELECTTEXT_DEFAULT_POS_X  (400.0f)       //�ʒuX�̏����l
#define SELECTTEXT_DEFAULT_POS_Y  (150.0f)       //�ʒuY�̏����l
#define SIZE_UP_X                 (200.0f / 60)  //�傫���Ȃ鑬�xX
#define SIZE_UP_Y                 (50.0f / 60)   //�傫���Ȃ鑬�xY
#define TITLETEXT_LIMITE_SIZE_X   (450.0f)       //�傫���Ȃ���X
#define TITLETEXT_LIMITE_SIZE_Y   (75.0f)        //�傫���Ȃ���Y

//�^�C�g�����S�֌W
#define LOGOTEXT_DEFAULT_SIZE_X (1300.0f)  //�傫��X�̏����l
#define LOGOTEXT_DEFAULT_SIZE_Y (850.0f)   //�傫��Y�̏����l
#define LOGOTEXT_DEFAULT_POS_X  (0.0f)     //�ʒuX�̏����l
#define LOGOTEXT_DEFAULT_POS_Y  (20.0f)    //�ʒuY�̏����l
#define LOGOTEXT_MENU_SIZE_X    (1000.0f)  //���j���[���̑傫��X
#define LOGOTEXT_MENU_SIZE_Y    (800.0f)   //���j���[���̑傫��Y
#define LOGOTEXT_MENU_POS_X     (-220.0f)  //���j���[���̈ʒuX
#define LOGOTEXT_MENU_POS_Y     (20.0f)    //���j���[���̈ʒuY

//�v�b�V���e�L�X�g�֌W
#define PUSHTEXT_DEFAULT_SIZE_X (500.0f)     //�傫��X�̏����l
#define PUSHTEXT_DEFAULT_SIZE_Y (300.0f)     //�傫��Y�̏����l
#define PUSHTEXT_DEFAULT_POS_X  (0.0f)       //�ʒuX�̏����l
#define PUSHTEXT_DEFAULT_POS_Y  (-200.0f)    //�ʒuY�̏����l
#define PUSHTEXT_TOP            (-195.0f)    //�e�L�X�g�ʒu�̏��  
#define PUSHTEXT_BOTTOM         (-205.0f)    //�e�L�X�g�ʒu�̉���
#define PUSHTEXT_UPDOWN_SPEED   (15.0 / 60)  //�ړ����x

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
