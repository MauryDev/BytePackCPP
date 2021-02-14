#pragma once
#include "Byte.h"
struct ByteArray
{
public:
	static ByteArray Create(int size);
	static ByteArray Create(byte* arr, int size);
	void Clear();
	int size();
	byte operator[](int index);
	void SetValue(int index, byte val);
private:
	byte* arr;
	int count;
};