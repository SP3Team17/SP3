#include "MVCtime.h"
#include <iostream>

void mvcTime::updateTime()
{
	//increase frame count
	frameCount++;

	long Ctime=timeGetTime();
	currentTime=Ctime;

	//calculate time passed
	timeInterval=currentTime-previousTime;
	dt=(currentTime-dtPTime)/1000.0f;
	dtPTime=currentTime;
	
	std::vector<timeKeeper*>::iterator end=timer.end();
	for(std::vector<timeKeeper*>::iterator it=timer.begin();it!=end;++it)
	{
		timeKeeper* t=*it;
		if(t->active)
			t->timeInterval=currentTime-t->previousTime;
	}

	//calculate time passed
	timeInterval=currentTime-previousTime;

	if(timeInterval>1000)//updates fps every 1s
	{
		//calculate the number of frames per second
		fps=frameCount/(timeInterval/1000.0f);

		//set time
		previousTime=currentTime;

		//reset frame count
		frameCount=0;
	}
	
}

mvcTime::~mvcTime() {}

mvcTime::mvcTime()
{
	frameCount=currentTime=previousTime=timeInterval=dtPTime=dt=0;
	fps=0.0f;
}

void mvcTime::init()
{
	previousTime=timeGetTime();
	frameCount=currentTime=0;
	fps=0.0f;
}

float mvcTime::getDelta()
{
	return dt;
}

float mvcTime::getFPS()
{
	return fps;
}

int mvcTime::insertNewTime(int limit)
{
	timeKeeper* Ntime=new timeKeeper;
	Ntime->limiter=limit;
	Ntime->active=true;
	Ntime->previousTime=timeGetTime();
	Ntime->timeInterval=0;
	timer.push_back(Ntime);
	return timer.size()-1;
}

bool mvcTime::testTime(int num)
{
	if(timer[num]->active)
	{
		if(timer[num]->timeInterval>timer[num]->limiter)
		{
			resetTime(num);
			return true;
		}
		return false;
	}
	else
		return true;
}

void mvcTime::resetTime(int num)
{
	timer[num]->previousTime=currentTime;
	timer[num]->timeInterval=0;
}

void mvcTime::changeLimit(int num,int nlimit)
{
	timer[num]->limiter=nlimit;
}

int mvcTime::getTimeInterval(int num)
{
	return timer[num]->timeInterval;
}

int mvcTime::getLimit(int num)
{
	return timer[num]->limiter;
}

void mvcTime::setActive(bool mode,int num)
{
	timer[num]->active=mode;
}

bool mvcTime::getActive(int num)
{
	return timer[num]->active;
}

mvcTime* mvcTime::getInstance(void)
{
	if(instance==NULL)
	{
		instance =new mvcTime;
	}
	return instance;
}

mvcTime* mvcTime::instance=NULL;

void mvcTime::drop()
{
	delete instance;
}