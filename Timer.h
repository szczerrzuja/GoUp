#pragma once
#include <time.h>
class Timer
{
private:
	time_t start,stop;

public:
	Timer();
	~Timer();
	double getDeltaTime();
};

