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
	void writePositiveIntMax3(int value)
	{
		return writePositiveInt(value, 2);
	}
	void writePositiveIntMax7(int value)
	{
		return writePositiveInt(value, 3);
	}
	bool writeBoolean(bool value)
	{
		return ((bool (*)(BitStream*, bool))(base + 0x969060))(this, value);
	}
	void writePositiveIntMax16383(int value)
	{
		return writePositiveInt(value, 14);
	}
	void writePositiveIntMax15(int value)
	{
		return writePositiveInt(value, 4);
	}
	void writePositiveIntMax31(int value)
	{
		return writePositiveInt(value, 5);
	}
	void writePositiveIntMax511(int value)
	{
		return writePositiveInt(value, 9);
	}
	void writePositiveIntMax1023(int value)
	{
		return writePositiveInt(value, 10);
	}
	void writePositiveIntMax4095(int value)
	{
		return writePositiveInt(value, 12);
	}
	void writePositiveIntMax8191(int value)
	{
		return writePositiveInt(value, 13);
	}
	void writeInt(int value, int bits)
	{
		return ((void (*)(BitStream*, int, int))(base + 0x96972C))(this, value, bits);
	}
	void writeIntMax63(int value) {
		return writeInt(value, 6);
	}
	void writePositiveVInt(int value, int bits)
	{
		return ((void (*)(BitStream*, int, int))(base + 0x9693C4))(this, value, bits);
	}
	void writePositiveVIntMax255OftenZero(int value)
	{
		if (value) {
			writePositiveInt(0, 1);
			writePositiveVInt(value, 3);
		}
		else writePositiveInt(1, 1);
	}
	void writePositiveVIntMax65535OftenZero(int value)
	{
		if (value) {
			writePositiveInt(0, 1);
			writePositiveVInt(value, 4);
		}
		else writePositiveInt(1, 1);
	}
	void writePositiveVIntMax16777215(int value)
	{
		writePositiveVInt(value, 5);
	}
};
#endif