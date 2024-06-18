#ifndef BITSTREAM_H
#define BITSTREAM_H
#include "Hook.h"
class BitStream
{
public:
	void writePositiveIntMax7(int value)
	{
		return ((void (*)(BitStream*, int))(base + 0x9692FC))(this, value);
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
		return ((void (*)(BitStream*, int))(base + 0x969354))(this, value);
	}
	void writePositiveIntMax511(int value)
	{
		return ((void (*)(BitStream*, int))(base + 0x96932C))(this, value);
	}
};
#endif