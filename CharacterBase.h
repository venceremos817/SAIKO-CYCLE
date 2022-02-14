#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

//===== インクルード部 =====
#include "GameObject.h"
#include "myVector.h"

class CharacterBase
	:public GameObject
{
public:
	CharacterBase();
	virtual ~CharacterBase();

	void Draw();

protected:
	myVector2	m_direction;	// 進行方向2次元ベクトル(x,z)
	
private:
};

#endif // !__CHARACTER_BASE_H__
