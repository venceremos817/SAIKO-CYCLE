#ifndef __FIELD_H__
#define __FIELD_H__

//===== インクルード部 =====
#include "GameObject.h"




class Field :
	public GameObject
{
public:
	Field();
	Field(DirectX::XMFLOAT3 size);
	virtual ~Field();

	enum E_FIELD_KIND
	{
		FIELD_START,
		FIELD_STRAIGHT,
		FIELD_CURVE,
		
		FIELD_JUMP,
		FIELD_OBSTACLE,

		FIELD_MAX
	};
};

#endif // !__FIELD_H__
