#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

//===== �C���N���[�h�� =====
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
	myVector2	m_direction;	// �i�s����2�����x�N�g��(x,z)
	
private:
};

#endif // !__CHARACTER_BASE_H__
