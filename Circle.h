#ifndef	__CIRCLE_H__
#define __CIRCLE_H__

//======================================
//	基本図形	円
//======================================

//===== インクルード部 =====
#include "BasicFigure.h"


class Circle:public BasicFigure
{
public:
	Circle();
	Circle(int a);
	~Circle();
};

#endif // !__CIRCLE_H__

