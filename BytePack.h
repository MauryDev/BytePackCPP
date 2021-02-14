#pragma once
#include <string>
#include "ByteArray.h"
#include <map>
#include <vector>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <stack>
#include <queue>

enum class TypeID
{
	None,
	INT32,
	ByteArray,
	INT16,
	INT64,
	Float,
	Double,
	Bool,
	Char,
	Wchar_t,
	Uint16,
	Uint32,
	Uint64,
	String,
	Byte,
	Map,
	Vector,
	Array,
	ArrayPTR,
	Deque,
	Forward_List,
	List,
	Set,
	Stack,
	Queue
};
class BytePack
{
public:
	BytePack();
	BytePack(ByteArray);
	~BytePack();
	int get_Count();
	int get_Capacity();
	int get_Index();
	void ResetIndex();
	byte* ReadBytes(int);
	byte ReadByte();
	char ReadChar();
	wchar_t ReadWchar_t();
	__int16 ReadShort();
    uint16_t ReadUshort();
	int ReadInt();
	uint32_t ReadUint();
	__int64 ReadLong();
	uint64_t ReadUlong();
	float ReadFloat();
	double ReadDouble();
	bool ReadBoolean();
	std::string ReadString();
	template<typename T>
	T* ReadArrayPTR();
	template<typename T>
	std::vector<T> ReadVector();
	template<typename T, typename T2>
	std::map<T, T2> ReadMap();
	template<typename T, size_t T2>
	std::array<T, T2> ReadArray();
	template<typename T>
	std::deque<T> ReadDeque();
	template<typename T>
	std::forward_list<T> ReadForward_List();
	template<typename T>
	std::list<T> ReadList();
	template<typename T>
	std::set<T> ReadSet();
	template<typename T>
	std::stack<T> ReadStack();
	template<typename T>
	std::queue<T> ReadQueue();
	void Write(ByteArray);
	void Write(byte);
	void Write(__int16);
	void Write(int);
	void Write(__int64);
	void Write(float);
	void Write(double);
	void Write(bool);
	void Write(char);
	void Write(wchar_t);
	void Write(uint16_t);
	void Write(uint32_t);
	void Write(uint64_t);
	void Write(std::string);
	template<typename T>
	void Write(T[],int size);
	template<typename T>
	void Write(std::vector<T>);
	template<typename T,typename T2>
	void Write(std::map<T,T2>);
	template<typename T,size_t T2>
	void Write(std::array<T,T2>);
	template<typename T>
	void Write(std::deque<T>);
	template<typename T>
	void Write(std::forward_list<T>);
	template<typename T>
	void Write(std::list<T>);
	template<typename T>
	void Write(std::set<T>);
	template<typename T>
	void Write(std::stack<T>);
	template<typename T>
	void Write(std::queue<T>);
private:
	template<typename T>
	static TypeID GetTypeCode();
	void WriteByTypeID(void*,TypeID);
	void* ReadByTypeID(TypeID,bool&);
	static const int MaxCapacity = 1000000000;
	bool TryAddCapacity(size_t);
	int index = 0;
	int capacity;
	int count;
	ByteArray buff;
};
