#pragma once

class HighPassFilter
{
private:
	double alpha;
	double output, prevInput;

public:
	HighPassFilter(double initPrevInput, double initOutput);

	HighPassFilter(double cutoffFreq, double deltaTime, double initPrevInput, double initOutput);

	~HighPassFilter();

	double nextSample(double input);

	void SetParameters(double cutoffFreq, double deltaTime);
};

