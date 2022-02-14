#ifndef __SHPRE_H__
#define __SHPRE_H__

//======================================
//	基本図形	UV球
//======================================


//===== インクルード部 =====
#include "BasicFigure.h"



class Sphere:public BasicFigure
{
public:
	Sphere();
	Sphere(int segment, int ring);
	~Sphere();

private:
	void Init(int segment, int ring);
};



#endif // !__SHPRE_H__

