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
#include <iostream>
bool physics::testColLineMap(Vector3D pos,Vector3D end,std::vector<physicObj*> wallList,int offset_x,int offset_y)
{
	for(vector<physicObj*>::iterator it=wallList.begin();it!=wallList.end();++it)
	{
		physicObj* temp=*it;
		Vector3D w0=((pos+end)*0.5);
		Vector3D b1=temp->pos-Vector3D(offset_x-TILE_SIZE/2,offset_y-TILE_SIZE/2);
		Vector3D N(pos.x-end.x,-(pos.y-end.y));
		N.normalizeVector3D();
		if((w0-b1).dotVector3D(N)<0)
		{
			N=Vector3D(-N.x,-N.y,-N.z);
		}
		Vector3D NP(N.y,-N.x,0);
		NP.normalizeVector3D();
		if(abs((w0-b1).dotVector3D(N))<32)
		{
			if(abs((w0-b1).dotVector3D(NP))<(pos-end).Length()*0.5)
			{
				float t=abs((w0-temp->pos).dotVector3D(N));
				std::cout<<temp->pos.x<<" "<<temp->pos.y<<" "<<t<<"\n";
				return true;
			}
			/*float t=(w0-temp->pos).dotVector3D(N);
			std::cout<<temp->pos.x<<" "<<temp->pos.y<<" "<<t<<"\n";
			return true;*/
		}
		
	}
	return false;
}