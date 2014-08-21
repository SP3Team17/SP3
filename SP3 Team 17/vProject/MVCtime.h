#ifndef MVCTIME_H
#define MVCTIME_H

#include <Windows.h>//for timeGetTime
#include <string>
#include <vector>

class mvcTime
{
public:
	typedef struct
	{
		bool active;
		int previousTime,timeInterval,limiter;
	} timeKeeper;
	void updateTime();
	float getDelta();
	float getFPS();
	int insertNewTime(int limit);
	bool testTime(int num);
	void resetTime(int num);
	void changeLimit(int num,int nlimit);
	void init();
	void setActive(bool mode,int num);
	bool getActive(int num);
	int getTimeInterval(int num);
	int getLimit(int num);
	static mvcTime* getInstance(void);
	static void drop(void);
private:
	mvcTime();
	~mvcTime();
	static mvcTime* instance;
	int frameCount;
	float fps;
	std::vector<timeKeeper*> timer;
	int currentTime, previousTime,timeInterval,dtPTime;
	float dt;
};

#endif