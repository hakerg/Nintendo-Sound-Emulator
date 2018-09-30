#include "pch.h"
#include "BitRef.h"

const char BitRef::Hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

BitRef::BitRef()
{
}

BitRef::BitRef(uint8_t & ref, uint8_t startBit, uint8_t bitCount)
	: Ref(&ref), StartBit(startBit), BitCount(bitCount)
{
	mask = ((1 << bitCount) - 1) << startBit;
	nmask = ~mask;
}

BitRef::~BitRef()
{
}

uint8_t BitRef::Get()
{
	return (*Ref & mask) >> StartBit;
}

void BitRef::Set(uint8_t value)
{
	*Ref = (*Ref) & nmask | (value << StartBit);
}

std::string BitRef::AsBits(uint8_t value)
{
	std::string ret = "";
	for (int n = 7; n >= 0; n--)
	{
		ret += ((value >> n) & 1 ? '1' : '0');
	}
	return ret;
}

std::string BitRef::AsHex(uint8_t value)
{
	return std::string("") + Hex[value >> 4] + Hex[value & 0xF];
}