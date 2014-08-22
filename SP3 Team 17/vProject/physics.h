#include "vector3D.h"


#ifndef PHYSICS_H
#define PHYSICS_H

struct physicObj
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

class physics
{
public:
	physics(void);
	~physics(void);
	bool testCol(physicObj,physicObj);
};

#endif
