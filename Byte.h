#pragma once
#include <bitset>

struct byte
{
public:
	byte();
	byte(int);
	static byte Parse(char);
	static byte Parse(int);
	void operator=(int);
	bool operator==(byte);
	bool operator!=(byte);
	explicit operator int();
	explicit operator char();
	std::string ToString();
private:
	std::bitset<8> bp;
};