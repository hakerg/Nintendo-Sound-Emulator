#include "pch.h"
#include "LowPassFilter.h"

LowPassFilter::LowPassFilter(double initOutput)
{
	output = initOutput;
}

LowPassFilter::LowPassFilter(double cutoffFreq, double deltaTime, double initOutput)
{
	SetParameters(cutoffFreq, deltaTime);
	output = initOutput;
}

LowPassFilter::~LowPassFilter()
{
}

double LowPassFilter::nextSample(double input)
{
	return output += alpha * (input -output);
}

void LowPassFilter::SetParameters(double cutoffFreq, double deltaTime)
{
	alpha = 2 * M_PI * deltaTime * cutoffFreq / (2 * M_PI * deltaTime * cutoffFreq + 1);
}
