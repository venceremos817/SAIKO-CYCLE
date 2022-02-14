//--------------------------------------------
//FileName:Meter.h
//--------------------------------------------
//���e�F���[�^�[(UI)�̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2021/01/21   | �쐬�J�n
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

	Meter();	// �R���X�g���N�^
	~Meter();	// �f�X�g���N�^

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �X�R�A���擾
	void Set(float);

	void SetPos(float, float, float, float);
	void SetSize(float, float, float, float);


private:
	TEXT m_MeterText;

	float	m_meter;		// ���x��ۑ�����
};

#endif // !___METER_H_
