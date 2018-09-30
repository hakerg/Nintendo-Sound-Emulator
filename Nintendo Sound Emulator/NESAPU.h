#pragma once
#include "LowPassFilter.h"
#include "HighPassFilter.h"

class NESAPU
{
private:
	//static const uint16_t memoryStart = 0x4000, memorySize = 24;
	//uint8_t memory[memorySize];

	static const double cpuFrequency;
	static double pulseLookup[31], tndLookup[16][16][128];
	static const bool pulseSequence[4][8];
	static const uint8_t triangleSequence[32];
	static const uint8_t lengthTable[32];
	static const int noisePeriodTable[16];
	static const int dmcRates[16];
	static const int frameSequencer[5];
	static const bool quarterFrameSequence[2][5];
	static const bool halfFrameSequence[2][5];

	int pulse1SequencerPosition = 0, pulse1TimerPos = 0, pulse1LengthCounter = -1;
	int pulse1EnvelopeDivider = 0, pulse1DecayLevel = 0, pulse1SweepDivider = 0, pulse1TargetPeriod = 0;
	bool pulse1EnvelopeStartFlag = 0, pulse1SweepReloadFlag = 0;

	int pulse2SequencerPosition = 0, pulse2TimerPos = 0, pulse2LengthCounter = -1;
	int pulse2EnvelopeDivider = 0, pulse2DecayLevel = 0, pulse2SweepDivider = 0, pulse2TargetPeriod = 0;
	bool pulse2EnvelopeStartFlag = 0, pulse2SweepReloadFlag = 0;

	int triangleSequencerPosition = 0, triangleLinearCounter = 0, triangleTimerPos = 0, triangleLengthCounter = 0;
	bool triangleLinearCounterReloadFlag = 0;

	uint16_t noiseShiftRegister = 0x4000;
	int noiseTimerPos = 0, noiseLengthCounter = -1;
	int noiseEnvelopeDivider = 0, noiseDecayLevel = 0;
	bool noiseEnvelopeStartFlag = 0;

	int dmcTimerPos = 0, dmcOutput = 0, dmcBitsRemaining = 8, dmcRemainingCounter = 0;
	uint8_t dmcBuffer = 0, dmcShiftRegister = 0;
	uint16_t dmcReaderAdress = 0xC000;
	bool dmcSilenceFlag = 0, dmcBufferEmpty = true;

	int frameDivider = 0, frameStep = 0;
	bool callAPUClock = false;

	void quarterFrameClock();

	void halfFrameClock();

	void APUClock(bool & update);

	void checkDMCBuffer();

	void updatePulse1TargetPeriod();

	void updatePulse2TargetPeriod();

	void updateOutput();


	uint8_t Pulse1Duty = 0;
	bool Pulse1LoopEnv = 0;
	bool Pulse1ConstVol = 0;
	uint8_t Pulse1Vol = 0;

	bool Pulse1SweepEnable = 0;
	uint8_t Pulse1SweepPeriod = 0;
	bool Pulse1SweepNegate = 0;
	uint8_t Pulse1SweepShiftCount = 0;

	uint16_t Pulse1Timer = 0;


	uint8_t Pulse2Duty = 0;
	bool Pulse2LoopEnv = 0;
	bool Pulse2ConstVol = 0;
	uint8_t Pulse2Vol = 0;

	bool Pulse2SweepEnable = 0;
	uint8_t Pulse2SweepPeriod = 0;
	bool Pulse2SweepNegate = 0;
	uint8_t Pulse2SweepShiftCount = 0;

	uint16_t Pulse2Timer = 0;


	bool TriangleLengthCounterDisable = 0;
	uint8_t TriangleLinearCounterReloadValue = 0;

	uint16_t TriangleTimer = 0;


	bool NoiseLoopEnv = 0;
	bool NoiseConstVol = 0;
	uint8_t NoiseVol = 0;

	bool NoiseLoop = 0;
	int NoisePeriod = noisePeriodTable[0];


	bool DMCLoopSample = 0;
	int DMCFreq = dmcRates[0];

	uint16_t DMCSampleAdress = 0xC000;

	uint16_t DMCSampleLength = 1;


	bool DMCEnable = 0;
	bool NoiseEnable = 0;
	bool TriangleEnable = 0;
	bool Pulse2Enable = 0;
	bool Pulse1Enable = 0;

	int FrameCounterSteps = 4;


	double cpuClockOffset = 1.0;

	double output = 0;
	HighPassFilter highPass90;
	HighPassFilter highPass440;
	LowPassFilter lowPass14k;

/*protected:
	BitRef Pulse1Duty;
	BitRef Pulse1LoopEnv;
	BitRef Pulse1ConstVol;
	BitRef Pulse1Vol;

	BitRef Pulse1SweepEnable;
	BitRef Pulse1SweepPeriod;
	BitRef Pulse1SweepNegate;
	BitRef Pulse1SweepShiftCount;

	BitRef Pulse1TimerLow;

	BitRef Pulse1LengthCounterLoad;
	BitRef Pulse1TimerHigh;


	BitRef Pulse2Duty;
	BitRef Pulse2LoopEnv;
	BitRef Pulse2ConstVol;
	BitRef Pulse2Vol;

	BitRef Pulse2SweepEnable;
	BitRef Pulse2SweepPeriod;
	BitRef Pulse2SweepNegate;
	BitRef Pulse2SweepShiftCount;

	BitRef Pulse2TimerLow;

	BitRef Pulse2LengthCounterLoad;
	BitRef Pulse2TimerHigh;


	BitRef TriangleLengthCounterDisable;
	BitRef TriangleLinearCounterReloadValue;

	BitRef TriangleTimerLow;

	BitRef TriangleLengthCounterLoad;
	BitRef TriangleTimerHigh;


	BitRef NoiseLoopEnv;
	BitRef NoiseConstVol;
	BitRef NoiseVol;

	BitRef NoiseLoop;
	BitRef NoisePeriod;

	BitRef NoiseLengthCounterLoad;


	//BitRef DMCIRQEnable;
	BitRef DMCLoopSample;
	BitRef DMCFreq;

	BitRef DMCDirectLoad;

	BitRef DMCSampleAdress;

	BitRef DMCSampleLength;


	//BitRef DMCInterrupt;
	//BitRef FrameInterrupt;
	BitRef DMCEnable;
	BitRef NoiseLengthCounterEnable;
	BitRef TriangleLengthCounterEnable;
	BitRef Pulse2LengthCounterEnable;
	BitRef Pulse1LengthCounterEnable;

	BitRef FrameCounterSequence;
	//BitRef FrameCounterDisableInterrupt;*/


public:
	uint8_t * const ExternalMemory;

	enum class SampleFormat { UINT8, INT16, FLOAT32 };

	static uint8_t GetBits(uint8_t value, int bitOffset, unsigned bitCount);

	NESAPU(uint8_t * memory0x0000 = nullptr);

	~NESAPU();

	void Write(uint16_t address, uint8_t value);

	void GetOutput(char * out, unsigned long bytes, double sampleRate, SampleFormat format, unsigned audioChans);

	void CPUClock();

#ifdef BASS_H
	static DWORD CALLBACK BASSStreamProc(HSTREAM handle, void *buffer, DWORD length, void *user);
#endif //BASS_H
};

