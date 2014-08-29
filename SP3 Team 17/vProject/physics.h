#include "vector3D.h"
#include "Map.h"
#include "definitions.h"
#include <vector>
#include "physicObj.h"

#ifndef PHYSICS_H
#define PHYSICS_H



class physics
{
private:
	physics(void);
	~physics(void);
public:
	static bool testCol(physicObj,physicObj);
	static bool testColMap(Vector3D pos,bool m_bCheckUpwards, bool m_bCheckDownwards, bool m_bCheckLeft, bool m_bCheckRight, CMap* map,int x_offset,int y_offset);
	static bool testColLineMap(Vector3D pos,Vector3D end,std::vector<physicObj*> wallList,int offset_x,int offset_y);
};

#endif
