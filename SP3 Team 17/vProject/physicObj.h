#include "vector3D.h"

#ifndef PHYSIC_OBJ_H
#define PHYSIC_OBJ_H

class physicObj
{
public:
	enum type
	{
		WALL=0,
		MISC,
	};
	physicObj(Vector3D Pos,Vector3D Size):pos(Pos),size(Size)
	{
	}
	Vector3D pos;
	Vector3D size;
	type Ptype;
};

#endif