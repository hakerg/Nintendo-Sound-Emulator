#include "pch.h"
#include "Timer.h"
#include <math.h>

Timer::Timer(double period) : Period(period)
{
}

Timer::~Timer()
{
}

void Timer::AddTime(double time)
{
	clocks += time / Period;
}

double Timer::TimeToNextClock()
{
	return (ceil(clocks) - clocks) * Period;
}

double Timer::Clocks()
{
	return floor(clocks);
}

void Timer::Reset()
{
	clocks = 0;
}