
#include "stdafx.h"
#include "ByteArray.h"

ByteArray ByteArray::Create(int size)
{
	ByteArray ba;
	ba.count = size;
	ba.arr = new byte[size];
	return ba;
}

ByteArray ByteArray::Create(byte * arr, int size)
{
	ByteArray ba;
	ba.count = size;
	ba.arr = new byte[size];
	auto e = sizeof(arr);
	for (int i = 0; i < size; i++)
	{
		ba.arr[i] = arr[i];
	}
	return ba;
}

void ByteArray::Clear()
{
	delete[] arr;
	count = 0;
}

int ByteArray::size()
{
	return count;
}

byte ByteArray::operator[](int index)
{
	if (index > count)
	{
		throw "Error: Index > Count";
	}
	return arr[index];
}

void ByteArray::SetValue(int index, byte val)
{
	if (index > count)
	{
		throw "Error: Index > Count";
	}
	arr[index] = val;
}
