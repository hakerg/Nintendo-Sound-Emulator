#pragma once

class Timer
{
private:
	double clocks = 0;

public:
	double Period;

	Timer(double period);

	~Timer();

	void AddTime(double time);

	double TimeToNextClock();

	double Clocks();

	void Reset();
};

