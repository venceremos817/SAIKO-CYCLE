#ifndef __SHPRE_H__
#define __SHPRE_H__

//======================================
//	��{�}�`	UV��
//======================================


//===== �C���N���[�h�� =====
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

