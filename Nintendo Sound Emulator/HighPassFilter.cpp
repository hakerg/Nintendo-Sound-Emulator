#include "pch.h"
#include "HighPassFilter.h"

HighPassFilter::HighPassFilter(double initPrevInput, double initOutput)
{
	output = initOutput;
	prevInput = initPrevInput;
}

HighPassFilter::HighPassFilter(double cutoffFreq, double deltaTime, double initPrevInput, double initOutput)
{
	SetParameters(cutoffFreq, deltaTime);
	output = initOutput;
	prevInput = initPrevInput;
}

HighPassFilter::~HighPassFilter()
{
}

double HighPassFilter::nextSample(double input)
{
	output = alpha * (output + input - prevInput);
	prevInput = input;
	return output;
}

void HighPassFilter::SetParameters(double cutoffFreq, double deltaTime)
{
	alpha = 1 / (2 * M_PI * deltaTime * cutoffFreq + 1);
}
