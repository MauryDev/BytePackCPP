#include "stdafx.h"
#include "Byte.h"
#include <sstream>

byte::byte()
{
}

byte::byte(int value)
{
	byte c = *((byte*)&value);
	this->bp = c.bp;
}

byte byte::Parse(char val)
{
	byte c;
	c = *(byte*)(&val);
	return c;
}

byte byte::Parse(int val)
{
	byte c;
	c = *(byte*)(&val);
	return c;
}

void byte::operator=(int value)
{
	byte c = *((byte*)&value);
	this->bp = c.bp;
}

bool byte::operator==(byte val)
{
	return this->bp == val.bp;
}

bool byte::operator!=(byte val)
{
	return this->bp != val.bp;
}

byte::operator int()
{
	int* val = new int(0);
	byte* val2 = (byte*)val;
	*val2 = *this;
	return *val;
}

byte::operator char()
{
	char* result = (char*)this;
	return result[0];
}
byte* To10Precision(byte t)
{
	byte* s = new byte[2];
	int v = (int)t;
	for (int i = 0; i < 2; i++)
	{
		if (i != 1)
		{
			int val = v / 100;
			s[i] = val % 100;
			v = v - val * 100;
		}
		else
		{
			s[i] = v;
			v = 0;
		}
	}
	return s;
}
std::string byte::ToString()
{
	auto buff = To10Precision(*this);
	char* c = new char[3]{
		(char)(48 + (int)buff[0]),
		(char)(48 + (int)buff[1] / 10),
		(char)(48 + (int)buff[1] % 10)
	};
	int c2 = 0;
	if (c[0] == 48)
	{
		c2 = 1;
	}
	if (c2 == 1 && c[1] == 48)
	{
		c2 = 2;
	}
	return std::string(c, c2, 3-c2);
}
