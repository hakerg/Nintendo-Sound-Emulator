#pragma once

class LowPassFilter
{
private:
	double alpha;
	double output;

public:
	LowPassFilter(double initOutput);

	LowPassFilter(double cutoffFreq, double deltaTime, double initOutput);

	~LowPassFilter();

	double nextSample(double input);

	void SetParameters(double cutoffFreq, double deltaTime);
};

