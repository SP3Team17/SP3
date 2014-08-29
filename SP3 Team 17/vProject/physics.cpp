#include "physics.h"


physics::physics(void)
{
}


physics::~physics(void)
{
}

//Check for collision of hero with obstacles in a certain position
bool physics::testColMap(Vector3D pos, 
								   bool m_bCheckUpwards, bool m_bCheckDownwards, 
								   bool m_bCheckLeft, bool m_bCheckRight, CMap* map,int x_offset,int y_offset)
{
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	int tile_topleft_x = (int)floor((float)(x_offset+pos.x-LEFT_BORDER) / TILE_SIZE);
	int tile_topleft_y = (int)floor((float)(y_offset+pos.y-BOTTOM_BORDER)/ TILE_SIZE);
	int proceed=false;
	Vector3D reference[9];
	int j=0;
	if(tile_topleft_x<0||tile_topleft_x>map->getNumOfTiles_MapWidth()-2)
	{
		return true;
	}
	if(tile_topleft_y<0||tile_topleft_y>map->getNumOfTiles_MapHeight()-2)
	{
		return true;
	}
	if (m_bCheckLeft)
	{
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y+1)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
	}

	if (m_bCheckRight)
	{
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x+1] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x+1)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x+1] == 1)
		{
			reference[j].Set((tile_topleft_x+1)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y+1)*TILE_SIZE+BOTTOM_BORDER);
			proceed=true;
			j++;
		}
	}

	if (m_bCheckUpwards)
	{
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x+1] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x+1)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
	}

	if (m_bCheckDownwards)
	{
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y+1)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x+1] == 1)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x+1)*TILE_SIZE+LEFT_BORDER,(tile_topleft_y+1)*TILE_SIZE+BOTTOM_BORDER);
			j++;
		}
	}

	if(proceed)
	{
		for(int i=0;i<j;++i)
		{
			//if((pos - reference[i]).Length() < TILE_SIZE)
			if(abs(reference[i].x-x_offset-pos.x)<TILE_SIZE-2 && abs(reference[i].y-y_offset-pos.y)<TILE_SIZE-2)
			{
				return true;
			}
		}
	}
	return false;
}

bool physics::testColLineMap(Vector3D pos,Vector3D end,std::vector<physicObj*> wallList,int offset_x,int offset_y)
{
	for(vector<physicObj*>::iterator it=wallList.begin();it!=wallList.end();++it)
	{
		physicObj* temp=*it;
		Vector3D w0=((end+pos)*0.5);
		Vector3D b1=temp->pos-Vector3D(offset_x-TILE_SIZE/2,offset_y-TILE_SIZE/2);
		Vector3D NP(end.x-pos.x,(end.y-pos.y));
		NP.normalizeVector3D();
		if((w0-b1).dotVector3D(NP)<0)
		{
			NP=Vector3D(-NP.x,-NP.y,-NP.z);
		}
		Vector3D N(NP.y,-NP.x,0);
		N.normalizeVector3D();
		if(abs((w0-b1).dotVector3D(N))<32)
		{
			if(abs((w0-b1).dotVector3D(NP))<(pos-end).Length()*0.5+32)
			{
				float t=abs((w0-b1).dotVector3D(N));
				float f=(pos-end).Length()*0.5+32;
				return true;
			}
		}
		
	}
	return false;

	//for(vector<physicObj*>::iterator it=wallList.begin();it!=wallList.end();++it)
	//{
	//	physicObj* temp=*it;
	//	Vector3D w0=temp->pos-Vector3D(offset_x+TILE_SIZE/2,offset_y+TILE_SIZE/2);
	//	Vector3D b1=pos;
	//	Vector3D N(1,0);
	//	Vector3D N2(0,1);
	//	N.normalizeVector3D();
	//	if((w0-b1).dotVector3D(N)<0)
	//	{
	//		N=Vector3D(-N.x,-N.y,-N.z);
	//	}
	//	if((w0-b1).dotVector3D(N2)<0)
	//	{
	//		N2=Vector3D(-N2.x,-N2.y,-N2.z);
	//	}
	//	Vector3D NP(N.y,-N.x,0);
	//	Vector3D NP2(N2.y,-N2.x,0);
	//	NP.normalizeVector3D();
	//	NP2.normalizeVector3D();
	//	float r=0;
	//	float h=32;
	//	float l=32;

	//	w0=w0-N*(r+h/2);//offset the wall to a point by radius and width of wall

	//	float dist=(b1-w0).dotVector3D(N);
	//	float spd=(end-pos).dotVector3D(N);


	//	float th=dist/spd;

	//	if(th<0)
	//	{
	//		//cout<<th<<" "<<dist<<" "<<spd<<"\n";
	//		cout<<"can see\n";
	//		return false;
	//	}


	//	Vector3D bh=pos+(end-pos)*th;

	//	Vector3D w1=w0+NP*(l/2);
	//	Vector3D w2=w0-NP*(l/2);

	//	if((w1-bh).dotVector3D(NP)<0||(bh-w2).dotVector3D(NP)<0)
	//	{
	//		cout<<"can see\n";
	//		return false;
	//	}
	//	else
	//	{
	//		cout<<"cannot see\n";
	//		return true;

	//	}
	//}
}

bool physics::testCol(physicObj obj1,physicObj obj2)
{
	if(abs(obj1.pos.x-obj2.pos.x)<(obj1.size.x+obj2.size.x)*0.5&&abs(obj1.pos.y-obj2.pos.y)<(obj1.size.y+obj2.size.y)*0.5)
		return true;
	else 
		return false;
}