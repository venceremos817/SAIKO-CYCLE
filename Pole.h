#ifndef	__POLE_H__
#define __POLE_H__

//======================================
//	��{�}�`	�~��
//======================================

//===== �C���N���[�h�� =====
#include "BasicFigure.h"

#include "DrawBuffer.h"
#include "CommonClass.h"


class Pole :public BasicFigure
{
public:
	Pole(int division = 10);
	~Pole();
};

#endif // !__POLE_H__

