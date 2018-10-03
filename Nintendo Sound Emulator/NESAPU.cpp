#include "pch.h"
#include "NESAPU.h"

const double NESAPU::cpuFrequency = 1789773.0;

double NESAPU::pulseLookup[31];

double NESAPU::tndLookup[16][16][128];

const bool NESAPU::pulseSequence[4][8] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0 }
};

const uint8_t NESAPU::triangleSequence[32] =
{
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
};

const uint8_t NESAPU::lengthTable[32] =
{
	10,254, 20,  2, 40,  4, 80,  6, 160,  8, 60, 10, 14, 12, 26, 14,
	12, 16, 24, 18, 48, 20, 96, 22, 192, 24, 72, 26, 16, 28, 32, 30
};

const int NESAPU::noisePeriodTable[16] =
{
	2, 6, 14, 30, 62, 94, 126, 158, 200, 252, 378, 506, 760, 1014, 2032, 4066
};

const int NESAPU::dmcRates[16] =
{
	426, 378, 338, 318, 284, 252, 224, 212, 188, 158, 140, 126, 104, 82, 70, 52
};

const int NESAPU::frameSequencer[5] =
{
	3728, 7456, 11185, 14914, 18640
};

const bool NESAPU::quarterFrameSequence[2][5] =
{
	{ true, true, true, true, false }, { true, true, true, false, true }
};

const bool NESAPU::halfFrameSequence[2][5] =
{
	{ false, true, false, true, false }, { false, true, false, false, true }
};

NESAPU::NESAPU(uint8_t * memory0x0000) : ExternalMemory(memory0x0000), highPass90(0, 0), highPass440(0, 0), lowPass14k(0)
{
	//memset(memory, 0, memorySize);
	//uint8_t * Memory = memory - memoryStart;

	/*Pulse1Duty = BitRef(Memory[0x4000], 6, 2);
	Pulse1LoopEnv = BitRef(Memory[0x4000], 5, 1);
	Pulse1ConstVol = BitRef(Memory[0x4000], 4, 1);
	Pulse1Vol = BitRef(Memory[0x4000], 0, 4);

	Pulse1SweepEnable = BitRef(Memory[0x4001], 7, 1);
	Pulse1SweepPeriod = BitRef(Memory[0x4001], 4, 3);
	Pulse1SweepNegate = BitRef(Memory[0x4001], 3, 1);
	Pulse1SweepShiftCount = BitRef(Memory[0x4001], 0, 3);

	Pulse1TimerLow = BitRef(Memory[0x4002], 0, 8);

	Pulse1LengthCounterLoad = BitRef(Memory[0x4003], 3, 5);
	Pulse1TimerHigh = BitRef(Memory[0x4003], 0, 3);


	Pulse2Duty = BitRef(Memory[0x4004], 6, 2);
	Pulse2LoopEnv = BitRef(Memory[0x4004], 5, 1);
	Pulse2ConstVol = BitRef(Memory[0x4004], 4, 1);
	Pulse2Vol = BitRef(Memory[0x4004], 0, 4);

	Pulse2SweepEnable = BitRef(Memory[0x4005], 7, 1);
	Pulse2SweepPeriod = BitRef(Memory[0x4005], 4, 3);
	Pulse2SweepNegate = BitRef(Memory[0x4005], 3, 1);
	Pulse2SweepShiftCount = BitRef(Memory[0x4005], 0, 3);

	Pulse2TimerLow = BitRef(Memory[0x4006], 0, 8);

	Pulse2LengthCounterLoad = BitRef(Memory[0x4007], 3, 5);
	Pulse2TimerHigh = BitRef(Memory[0x4007], 0, 3);


	TriangleLengthCounterDisable = BitRef(Memory[0x4008], 7, 1);
	TriangleLinearCounterReloadValue = BitRef(Memory[0x4008], 0, 7);

	TriangleTimerLow = BitRef(Memory[0x400A], 0, 8);

	TriangleLengthCounterLoad = BitRef(Memory[0x400B], 3, 5);
	TriangleTimerHigh = BitRef(Memory[0x400B], 0, 3);


	NoiseLoopEnv = BitRef(Memory[0x400C], 5, 1);
	NoiseConstVol = BitRef(Memory[0x400C], 4, 1);
	NoiseVol = BitRef(Memory[0x400C], 0, 4);

	NoiseLoop = BitRef(Memory[0x400E], 7, 1);
	NoisePeriod = BitRef(Memory[0x400E], 0, 4);

	NoiseLengthCounterLoad = BitRef(Memory[0x400F], 3, 5);


	//DMCIRQEnable = BitRef(Memory[0x4010], 7, 1);
	DMCLoopSample = BitRef(Memory[0x4010], 6, 1);
	DMCFreq = BitRef(Memory[0x4010], 0, 4);

	DMCDirectLoad = BitRef(Memory[0x4011], 0, 7);

	DMCSampleAdress = BitRef(Memory[0x4012], 0, 8);

	DMCSampleLength = BitRef(Memory[0x4013], 0, 8);


	//DMCInterrupt = BitRef(Memory[0x4015], 7, 1);
	//FrameInterrupt = BitRef(Memory[0x4015], 6, 1);
	DMCEnable = BitRef(Memory[0x4015], 4, 1);
	NoiseLengthCounterEnable = BitRef(Memory[0x4015], 3, 1);
	TriangleLengthCounterEnable = BitRef(Memory[0x4015], 2, 1);
	Pulse2LengthCounterEnable = BitRef(Memory[0x4015], 1, 1);
	Pulse1LengthCounterEnable = BitRef(Memory[0x4015], 0, 1);

	FrameCounterSequence = BitRef(Memory[0x4017], 7, 1);
	//FrameCounterDisableInterrupt = BitRef(Memory[0x4017], 6, 1);*/


	pulseLookup[0] = 0.0;
	for (int n = 1; n <= 30; n++)
	{
		pulseLookup[n] = 95.52 / (8128.0 / n + 100.0);
	}
	tndLookup[0][0][0] = 0.0;
	for (int t = 0; t <= 15; t++)
	{
		double tt = t / 8227.0;
		for (int n = 0; n <= 15; n++)
		{
			double nn = n / 12241.0;
			for (int d = 0; d <= 127; d++)
			{
				double dd = d / 22638.0;
				tndLookup[t][n][d] = 159.79 / (1.0 / (tt + nn + dd) + 100.0);
			}
		}
	}
}

NESAPU::~NESAPU()
{
}

void NESAPU::Write(uint16_t address, uint8_t value)
{
	if (address < 0x4000 || address > 0x4017)
	{
		throw std::string("Invalid adress");
	}
	if (address < 0x4010)
	{
		if (address < 0x4008)
		{
			if (address < 0x4004)
			{
				if (address < 0x4002)
				{
					if (address == 0x4000)
					{
						Pulse1Duty = GetBits(value, 6, 2);
						Pulse1LoopEnv = GetBits(value, 5, 1);
						Pulse1ConstVol = GetBits(value, 4, 1);
						Pulse1Vol = GetBits(value, 0, 4);
					}
					else
					{
						Pulse1SweepEnable = GetBits(value, 7, 1);
						Pulse1SweepPeriod = GetBits(value, 4, 3);
						Pulse1SweepNegate = GetBits(value, 3, 1);
						Pulse1SweepShiftCount = GetBits(value, 0, 3);
					}
				}
				else
				{
					if (address == 0x4002)
					{
						Pulse1Timer = Pulse1Timer & 0xFF00 | value;
					}
					else
					{
						if (Pulse1Enable)
						{
							pulse1LengthCounter = lengthTable[GetBits(value, 3, 5)];
						}
						Pulse1Timer = Pulse1Timer & 0x00FF | BitOffset16(value & 0x7, 8);
						pulse1SequencerPosition = 0;
						pulse1EnvelopeStartFlag = true;
					}
					updatePulse1TargetPeriod();
				}
			}
			else
			{
				if (address < 0x4006)
				{
					if (address == 0x4004)
					{
						Pulse2Duty = GetBits(value, 6, 2);
						Pulse2LoopEnv = GetBits(value, 5, 1);
						Pulse2ConstVol = GetBits(value, 4, 1);
						Pulse2Vol = GetBits(value, 0, 4);
					}
					else
					{
						Pulse2SweepEnable = GetBits(value, 7, 1);
						Pulse2SweepPeriod = GetBits(value, 4, 3);
						Pulse2SweepNegate = GetBits(value, 3, 1);
						Pulse2SweepShiftCount = GetBits(value, 0, 3);
					}
				}
				else
				{
					if (address == 0x4006)
					{
						Pulse2Timer = Pulse2Timer & 0xFF00 | value;
					}
					else
					{
						if (Pulse2Enable)
						{
							pulse2LengthCounter = lengthTable[GetBits(value, 3, 5)];
						}
						Pulse2Timer = Pulse2Timer & 0x00FF | BitOffset16(value & 0x7, 8);
						pulse2SequencerPosition = 0;
						pulse2EnvelopeStartFlag = true;
					}
					updatePulse2TargetPeriod();
				}
			}
		}
		else
		{
			if (address < 0x400C)
			{
				if (address < 0x400A)
				{
					if (address == 0x4008)
					{
						TriangleLengthCounterDisable = GetBits(value, 7, 1);
						TriangleLinearCounterReloadValue = GetBits(value, 0, 7);
					}
				}
				else
				{
					if (address == 0x400A)
					{
						TriangleTimer = TriangleTimer & 0xFF00 | value;
					}
					else
					{
						if (TriangleEnable)
						{
							triangleLengthCounter = lengthTable[GetBits(value, 3, 5)];
						}
						TriangleTimer = TriangleTimer & 0x00FF | BitOffset16(value & 0x7, 8);
						triangleLinearCounterReloadFlag = true;
					}
				}
			}
			else
			{
				if (address < 0x400E)
				{
					if (address == 0x400C)
					{
						NoiseLoopEnv = GetBits(value, 5, 1);
						NoiseConstVol = GetBits(value, 4, 1);
						NoiseVol = GetBits(value, 0, 4);
					}
				}
				else
				{
					if (address == 0x400E)
					{
						NoiseLoop = GetBits(value, 7, 1);
						NoisePeriod = noisePeriodTable[GetBits(value, 0, 4)];
					}
					else
					{
						if (NoiseEnable)
						{
							noiseLengthCounter = lengthTable[GetBits(value, 3, 5)];
						}
						noiseEnvelopeStartFlag = true;
					}
				}
			}
		}
	}
	else
	{
		if (address < 0x4014)
		{
			if (address < 0x4012)
			{
				if (address == 0x4010)
				{
					DMCLoopSample = GetBits(value, 6, 1);
					DMCFreq = dmcRates[GetBits(value, 0, 4)];
				}
				else
				{
					dmcOutput = GetBits(value, 0, 7);
				}
			}
			else
			{
				if (address == 0x4012)
				{
					DMCSampleAdress = GetDMCSampleAddress(value);
				}
				else
				{
					DMCSampleLength = GetDMCSampleLength(value);
				}
			}
		}
		else
		{
			if (address == 0x4015)
			{
				DMCEnable = GetBits(value, 4, 1);
				if (DMCEnable)
				{
					checkDMCBuffer();
				}
				else
				{
					dmcRemainingCounter = 0;
				}
			}
			if (NoiseEnable = GetBits(value, 3, 1))
			{
				noiseLengthCounter = -1;
			}
			if (TriangleEnable = GetBits(value, 2, 1))
			{
				triangleLengthCounter = 0;
			}
			if (Pulse2Enable = GetBits(value, 1, 1))
			{
				pulse2LengthCounter = -1;
			}
			if (Pulse1Enable = GetBits(value, 0, 1))
			{
				pulse1LengthCounter = -1;
			}
			else if (address == 0x4017)
			{
				FrameCounterSteps = (GetBits(value, 7, 1) ? 5 : 4);
			}
		}
	}
	updateOutput();
}

uint8_t NESAPU::GetBits(uint8_t value, int bitOffset, unsigned bitCount)
{
	return (value >> bitOffset) & ((1 << bitCount) - 1);
}

void NESAPU::quarterFrameClock()
{
	if (pulse1EnvelopeStartFlag)
	{
		pulse1EnvelopeStartFlag = false;
		pulse1DecayLevel = 15;
		pulse1EnvelopeDivider = Pulse1Vol;
	}
	else
	{
		if (pulse1EnvelopeDivider == 0)
		{
			pulse1EnvelopeDivider = Pulse1Vol;
			if (pulse1DecayLevel)
			{
				pulse1DecayLevel--;
			}
			else if (Pulse1LoopEnv)
			{
				pulse1DecayLevel = 15;
			}
		}
	}
	if (pulse2EnvelopeStartFlag)
	{
		pulse2EnvelopeStartFlag = false;
		pulse2DecayLevel = 15;
		pulse2EnvelopeDivider = Pulse2Vol;
	}
	else
	{
		if (pulse2EnvelopeDivider == 0)
		{
			pulse2EnvelopeDivider = Pulse2Vol;
			if (pulse2DecayLevel)
			{
				pulse2DecayLevel--;
			}
			else if (Pulse2LoopEnv)
			{
				pulse2DecayLevel = 15;
			}
		}
	}
	if (noiseEnvelopeStartFlag)
	{
		noiseEnvelopeStartFlag = false;
		noiseDecayLevel = 15;
		noiseEnvelopeDivider = NoiseVol;
	}
	else
	{
		if (noiseEnvelopeDivider == 0)
		{
			noiseEnvelopeDivider = NoiseVol;
			if (noiseDecayLevel)
			{
				noiseDecayLevel--;
			}
			else if (NoiseLoopEnv)
			{
				noiseDecayLevel = 15;
			}
		}
	}
	if (triangleLinearCounterReloadFlag)
	{
		triangleLinearCounter = TriangleLinearCounterReloadValue;
	}
	else if (triangleLinearCounter)
	{
		triangleLinearCounter--;
	}
	if (TriangleLengthCounterDisable == 0)
	{
		triangleLinearCounterReloadFlag = false;
	}
}

void NESAPU::halfFrameClock()
{
	if (pulse1LengthCounter != -1 && Pulse1LoopEnv == 0)
	{
		pulse1LengthCounter--;
	}
	if (pulse2LengthCounter != -1 && Pulse2LoopEnv == 0)
	{
		pulse2LengthCounter--;
	}
	if (triangleLengthCounter != 0 && TriangleLengthCounterDisable == 0)
	{
		triangleLengthCounter--;
	}
	if (noiseLengthCounter != -1 && NoiseLoopEnv == 0)
	{
		noiseLengthCounter--;
	}
	if (pulse1SweepDivider == 0 && Pulse1SweepEnable && pulse1TargetPeriod <= 0x7FF)
	{
		Pulse1Timer = pulse1TargetPeriod;
		updatePulse1TargetPeriod();
	}
	if (pulse1SweepDivider == 0 || pulse1SweepReloadFlag)
	{
		pulse1SweepDivider = Pulse1SweepPeriod;
		pulse1SweepReloadFlag = false;
	}
	else
	{
		pulse1SweepDivider--;
	}
	if (pulse2SweepDivider == 0 && Pulse2SweepEnable && pulse2TargetPeriod <= 0x7FF)
	{
		Pulse2Timer = pulse2TargetPeriod;
		updatePulse2TargetPeriod();
	}
	if (pulse2SweepDivider == 0 || pulse2SweepReloadFlag)
	{
		pulse2SweepDivider = Pulse2SweepPeriod;
		pulse2SweepReloadFlag = false;
	}
	else
	{
		pulse2SweepDivider--;
	}
}

void NESAPU::APUClock(bool & update)
{
	frameDivider++;
	if (pulse1TimerPos == 0)
	{
		pulse1TimerPos = Pulse1Timer;
		if (pulse1SequencerPosition == 0)
		{
			pulse1SequencerPosition = 7;
		}
		else
		{
			pulse1SequencerPosition--;
		}
		update = true;
	}
	else
	{
		pulse1TimerPos--;
	}
	if (pulse2TimerPos == 0)
	{
		pulse2TimerPos = Pulse2Timer;
		if (pulse2SequencerPosition == 0)
		{
			pulse2SequencerPosition = 7;
		}
		else
		{
			pulse2SequencerPosition--;
		}
		update = true;
	}
	else
	{
		pulse2TimerPos--;
	}
	if (noiseTimerPos == 0)
	{
		noiseTimerPos = NoisePeriod;
		bool feedback = ((noiseShiftRegister & 0x1) xor (noiseShiftRegister >> (NoiseLoop ? 6 : 1)) & 0x1);
		noiseShiftRegister >>= 1;
		if (feedback)
		{
			noiseShiftRegister |= 0x4000;
		}
		update = true;
	}
	else
	{
		noiseTimerPos -= 2;
	}
	if (DMCEnable)
	{
		if (dmcTimerPos == 0)
		{
			dmcTimerPos = DMCFreq;
			if (dmcSilenceFlag == false)
			{
				if (dmcShiftRegister & 0x1)
				{
					if (dmcOutput <= 125)
					{
						dmcOutput += 2;
						update = true;
					}
				}
				else
				{
					if (dmcOutput >= 2)
					{
						dmcOutput -= 2;
						update = true;
					}
				}
			}
			dmcShiftRegister >>= 1;
			dmcBitsRemaining--;
			if (dmcBitsRemaining == 0)
			{
				dmcBitsRemaining = 8;
				if (dmcBufferEmpty)
				{
					dmcSilenceFlag = true;
				}
				else
				{
					dmcSilenceFlag = false;
					dmcShiftRegister = dmcBuffer;
					dmcBufferEmpty = true;
					checkDMCBuffer();
				}
			}
		}
		else
		{
			dmcTimerPos -= 2;
		}
	}
}

void NESAPU::CPUClock()
{
	bool update = false;
	if (triangleTimerPos == 0)
	{
		triangleTimerPos = TriangleTimer;
		if (triangleLinearCounter && triangleLengthCounter)
		{
			if (triangleSequencerPosition == 31)
			{
				triangleSequencerPosition = 0;
			}
			else
			{
				triangleSequencerPosition++;
			}
			update = true;
		}
	}
	else
	{
		triangleTimerPos--;
	}
	if (callAPUClock)
	{
		APUClock(update);
	}
	else
	{
		if (frameDivider == frameSequencer[frameStep])
		{
			if (quarterFrameSequence[FrameCounterSteps - 4][frameStep])
			{
				quarterFrameClock();
				update = true;
			}
			if (halfFrameSequence[FrameCounterSteps - 4][frameStep])
			{
				halfFrameClock();
				update = true;
			}
			frameStep++;
			if (frameStep == FrameCounterSteps)
			{
				frameStep = 0;
				frameDivider = -1;
			}
		}
	}
	callAPUClock = !callAPUClock;
	if (update)
	{
		updateOutput();
	}
}

#ifdef BASS_H
DWORD NESAPU::BASSStreamProc(HSTREAM handle, void * buffer, DWORD length, void * user)
{
	BASS_CHANNELINFO info;
	BASS_ChannelGetInfo(handle, &info);
	NESAPU * nesapu = (NESAPU*)user;
	SampleFormat format = (info.flags & BASS_SAMPLE_8BITS ? SampleFormat::UINT8 : info.flags & BASS_SAMPLE_FLOAT ? SampleFormat::FLOAT32 : SampleFormat::INT16);
	nesapu->GetOutput((char*)buffer, length, info.freq, format, info.chans);
	return length;
}
uint16_t NESAPU::GetDMCSampleAddress(uint8_t address)
{
	return 0xC000 + uint16_t(address) * 64;
}
uint16_t NESAPU::GetDMCSampleLength(uint8_t length)
{
	return uint16_t(length) * 16 + 1;
}
#endif //BASS_H

void NESAPU::SetChannelsEnabled(bool enablePulse1, bool enablePulse2, bool enableTriangle, bool enableNoise, bool enableDMC)
{
	Write(0x4015, uint8_t(enablePulse1) | BitOffset8(enablePulse2, 1) | BitOffset8(enableTriangle, 2) | BitOffset8(enableNoise, 3) | BitOffset8(enableDMC, 4));
}
void NESAPU::SetPulse1StateConstVol(Duty duty, bool enableNoteLength, uint8_t volume_0_15)
{
	Write(0x4000, BitOffset8(duty, 6) | BitOffset8(!enableNoteLength, 5) | 0x10 | volume_0_15);
}
void NESAPU::SetPulse1StateEnvelope(Duty duty, bool loopEnvelope, uint8_t envelopePeriod_1_16)
{
	Write(0x4000, BitOffset8(duty, 6) | BitOffset8(loopEnvelope, 5) | (envelopePeriod_1_16 - 1));
}
void NESAPU::SetPulse1Sweep(bool enable, uint8_t period_1_8, bool goUp, uint8_t shiftCount_1_8)
{
	Write(0x4001, BitOffset8(enable, 7) | BitOffset8(period_1_8 - 1, 4) | BitOffset8(goUp, 3) | (shiftCount_1_8 - 1));
}
void NESAPU::SetPulse1Note(uint16_t timer_1_2048, uint8_t lengthIndex)
{
	timer_1_2048--;
	Write(0x4002, (uint8_t)timer_1_2048);
	Write(0x4003, BitOffset8(lengthIndex, 3) | (timer_1_2048 >> 8));
}
void NESAPU::SetPulse2StateConstVol(Duty duty, bool enableNoteLength, uint8_t volume_0_15)
{
	Write(0x4004, BitOffset8(duty, 6) | BitOffset8(!enableNoteLength, 5) | 0x10 | volume_0_15);
}
void NESAPU::SetPulse2StateEnvelope(Duty duty, bool loopEnvelope, uint8_t envelopePeriod_1_16)
{
	Write(0x4004, BitOffset8(duty, 6) | BitOffset8(loopEnvelope, 5) | (envelopePeriod_1_16 - 1));
}
void NESAPU::SetPulse2Sweep(bool enable, uint8_t period_1_8, bool goUp, uint8_t shiftCount_1_8)
{
	Write(0x4005, BitOffset8(enable, 7) | BitOffset8(period_1_8 - 1, 4) | BitOffset8(goUp, 3) | (shiftCount_1_8 - 1));
}
void NESAPU::SetPulse2Note(uint16_t timer_1_2048, uint8_t lengthIndex)
{
	timer_1_2048--;
	Write(0x4006, (uint8_t)timer_1_2048);
	Write(0x4007, BitOffset8(lengthIndex, 3) | (timer_1_2048 >> 8));
}

void NESAPU::SetTriangleLinearCounter(bool enable, uint8_t reloadValue_0_127)
{
	Write(0x4008, BitOffset8(enable, 7) | reloadValue_0_127);
}

void NESAPU::SetTriangleNote(uint16_t timer_1_2048, uint8_t lengthIndex)
{
	timer_1_2048--;
	Write(0x400A, (uint8_t)timer_1_2048);
	Write(0x400B, BitOffset8(lengthIndex, 3) | (timer_1_2048 >> 8));
}

void NESAPU::SetNoiseStateConstVol(bool enableNoteLength, uint8_t volume_0_15)
{
	Write(0x400C, BitOffset8(!enableNoteLength, 5) | 0x10 | volume_0_15);
}

void NESAPU::SetNoiseStateEnvelope(bool loopEnvelope, uint8_t envelopePeriod_1_16)
{
	Write(0x400C, BitOffset8(loopEnvelope, 5) | (envelopePeriod_1_16 - 1));
}

void NESAPU::SetNoiseTone(bool loopedNoise, uint8_t noisePeriodIndex)
{
	Write(0x400E, BitOffset8(loopedNoise, 7) | noisePeriodIndex);
}

void NESAPU::SetNoiseNoteLength(uint8_t lengthIndex)
{
	Write(0x400F, BitOffset8(lengthIndex, 3));
}

void NESAPU::SetDMCNote(bool loopSample, uint8_t freqIndex)
{
	Write(0x4010, BitOffset8(loopSample, 6) | freqIndex);
}

void NESAPU::SetDMCOutput(uint8_t value_0_127)
{
	Write(0x4011, value_0_127);
}

void NESAPU::SetDMCSampleAddress(uint8_t address)
{
	Write(0x4012, address);
}

void NESAPU::SetDMCSampleLength(uint8_t length)
{
	Write(0x4013, length);
}

void NESAPU::GetOutput(char * out, unsigned long bytes, double sampleRate, SampleFormat format, unsigned audioChans)
{
	highPass90.SetParameters(90, 1 / sampleRate);
	highPass440.SetParameters(440, 1 / sampleRate);
	lowPass14k.SetParameters(14000, 1 / sampleRate);
	const double cpuClocksPerSample = cpuFrequency / sampleRate;
	const double samplesPerCPUClock = 1.0 / cpuClocksPerSample;
	char * outEnd = out + bytes;
	while (out != outEnd)
	{
		double cpuClocksRemaining = cpuClocksPerSample;
		double timeToCPUClock = 1.0 - cpuClockOffset;
		double sample = output * timeToCPUClock;
		cpuClocksRemaining -= timeToCPUClock;
		while (cpuClocksRemaining >= 1.0)
		{
			CPUClock();
			cpuClocksRemaining--;
			sample += output;
		}
		CPUClock();
		cpuClockOffset = cpuClocksRemaining;
		sample += output * cpuClockOffset;
		sample = highPass90.nextSample(sample * samplesPerCPUClock - 0.5);
		sample = highPass440.nextSample(sample);
		sample = lowPass14k.nextSample(sample);
		sample += 0.5;
		if (format == SampleFormat::FLOAT32)
		{
			for (unsigned n = 0; n < audioChans; n++)
			{
				*(float*)out = float(sample * 2.0 - 1.0);
				out += 4;
			}
		}
		else if (format == SampleFormat::INT16)
		{
			for (unsigned n = 0; n < audioChans; n++)
			{
				*(int16_t*)out = int16_t((sample - 0.5) * 0xFFFE);
				out += 2;
			}
		}
		else
		{
			for (unsigned n = 0; n < audioChans; n++)
			{
				*(uint8_t*)out = uint8_t(sample * 0xFF);
				out++;
			}
		}
	}
}

void NESAPU::checkDMCBuffer()
{
	if (dmcBufferEmpty && dmcRemainingCounter)
	{
		dmcBuffer = ExternalMemory[dmcReaderAdress];
		dmcBufferEmpty = false;
		if (dmcReaderAdress == 0xFFFF)
		{
			dmcReaderAdress = 0x8000;
		}
		else
		{
			dmcReaderAdress++;
		}
		dmcRemainingCounter--;
		if (dmcRemainingCounter == 0 && DMCLoopSample)
		{
			dmcReaderAdress = DMCSampleAdress;
			dmcRemainingCounter = DMCSampleLength;
		}
	}
}

void NESAPU::updatePulse1TargetPeriod()
{
	int changeAmount = Pulse1Timer >> Pulse1SweepShiftCount;
	if (Pulse1SweepNegate)
	{
		changeAmount = -changeAmount - 1;
	}
	pulse1TargetPeriod = Pulse1Timer + changeAmount;
}

void NESAPU::updatePulse2TargetPeriod()
{
	int changeAmount = Pulse2Timer >> Pulse2SweepShiftCount;
	if (Pulse2SweepNegate)
	{
		changeAmount = -changeAmount;
	}
	pulse2TargetPeriod = Pulse2Timer + changeAmount;
}

void NESAPU::updateOutput()
{
	output = pulseLookup
		[
			(pulseSequence[Pulse1Duty][pulse1SequencerPosition] && pulse1TargetPeriod <= 0x7FF && pulse1LengthCounter && Pulse1Timer >= 8 ? (Pulse1ConstVol ? Pulse1Vol : pulse1DecayLevel) : 0) +
			(pulseSequence[Pulse2Duty][pulse2SequencerPosition] && pulse2TargetPeriod <= 0x7FF && pulse2LengthCounter && Pulse2Timer >= 8 ? (Pulse2ConstVol ? Pulse2Vol : pulse2DecayLevel) : 0)
		] + tndLookup[
			triangleSequence[triangleSequencerPosition]
		][
			noiseShiftRegister & 0x1 && noiseLengthCounter != -1 ? (NoiseConstVol ? NoiseVol : noiseDecayLevel) : 0
		][
			dmcOutput
		];
}
