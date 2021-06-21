#include "Timer.h"
Timer::Timer()
{
	time(&start);
}
Timer::~Timer()
{

}
double Timer::getDeltaTime()
{
	time(&stop);
	double elapsed = stop - start;
	time(&start);
	return elapsed;
}
