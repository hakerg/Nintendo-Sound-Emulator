#pragma once
#include <cstdint>
#include <string>

class BitRef
{
private:
	uint8_t mask, nmask;

public:
	uint8_t * Ref;
	uint8_t StartBit, BitCount;

	static const char Hex[16];

	BitRef();

	BitRef(uint8_t & ref, uint8_t startBit, uint8_t bitCount);

	~BitRef();

	uint8_t Get();

	void Set(uint8_t value);

	static std::string AsBits(uint8_t value);

	static std::string AsHex(uint8_t value);
};

