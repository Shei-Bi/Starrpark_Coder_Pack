#ifndef BITSTREAM_H
#define BITSTREAM_H
#include "Hook.h"
class BitStream
{
public:
	void writePositiveInt(int value, int bits)
	{
		return ((void (*)(BitStream*, int, int))(base + 0x969074))(this, value, bits);
	}
	void writePositiveIntMax7(int value)
	{
		return writePositiveInt(value, 3);
	}
	bool writeBoolean(bool value)
	{
		return ((bool (*)(BitStream*, bool))(base + 0x969060))(this, value);
	}
	void writePositiveVIntMax255OftenZero(int value)
	{
		return ((void (*)(BitStream*, int))(base + 0x969624))(this, value);
	}
	void writePositiveIntMax16383(int value)
	{
		return writePositiveInt(value, 14);
	}
	void writePositiveIntMax511(int value)
	{
		return writePositiveInt(value, 9);
	}
	void writePositiveIntMax1023(int value)
	{
		return writePositiveInt(value, 10);
	}
};
#endif