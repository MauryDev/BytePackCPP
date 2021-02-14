// BytePack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "BytePack.h"
#include <iostream>
#include <vector>
#include <map>
#include <ctime>

BytePack::BytePack()
{
	
	capacity = 32;
	count = 0;
	auto ba = new byte[capacity];
	buff = ByteArray::Create(ba, 32);
}
BytePack::BytePack(ByteArray arr)
{
	
	this->count = arr.size();
	capacity = count;
	buff = arr;
}
template<typename T>
T* BytePack::ReadArrayPTR()
{
	TypeID type = GetTypeCode<T>();
	auto size = ReadInt();
	T* result = new T[size];
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type,success);
		if (success)
		{
			result[i] = *tempresult;
		}
		else
		{
			result[i] = T();
		}
	}
	return result;
}

template<typename T>
std::vector<T> BytePack::ReadVector()
{
	std::vector<T> result;
	TypeID type = GetTypeCode<T>();
	auto size = ReadInt();
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result.push_back(*tempresult);
		}
		else
		{
			result.push_back(T());
		}
	}
	return result;
}

template<typename T, typename T2>
std::map<T, T2> BytePack::ReadMap()
{
	std::map<T, T2> result;
	TypeID type = GetTypeCode<T>();
	TypeID type2 = GetTypeCode<T>();
	auto size = ReadInt();
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		bool success2 = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		T2* tempresult2 = (T2*)ReadByTypeID(type2, success2);
		if (success && success2)
		{
			result[*tempresult] = *tempresult2;
		}
		else
		{
			result[T()] = T2();
		}
	}
	return result;
}

template<typename T, size_t T2>
std::array<T, T2> BytePack::ReadArray()
{
	std::array<T, T2> result;
	for (size_t i = 0; i < T2; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result[i] = *tempresult;
		}
		else
		{
			result = T();
		}
	}
	return result;
}

template<typename T>
std::deque<T> BytePack::ReadDeque()
{
	std::deque<T> result;
	TypeID type = GetTypeCode<T>();
	auto size = ReadInt();
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result.push_back(*tempresult);
		}
		else
		{
			result.push_back(T());
		}
	}
	return result;
}

template<typename T>
std::forward_list<T> BytePack::ReadForward_List()
{
	std::forward_list<T> result;
	TypeID type = GetTypeCode<T>();
	auto size = ReadInt();
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result.push_front(*tempresult);
		}
		else
		{
			result.push_front(T());
		}
	}
	result.reverse();
	return result;
}

template<typename T>
std::list<T> BytePack::ReadList()
{
	std::list<T> result;
	TypeID type = GetTypeCode<T>();
	auto size = ReadInt();
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result.push_back(*tempresult);
		}
		else
		{
			result.push_back(T());
		}
	}
	return result;
}

template<typename T>
std::set<T> BytePack::ReadSet()
{
	TypeID type = GetTypeCode<T>();
	auto bp = new BytePack();
	
	std::set<T> result;
	auto size = ReadInt();
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result.insert(*tempresult);
		}
		else
		{
			result.insert(T());
		}
	}
	return result;
}

template<typename T>
std::stack<T> BytePack::ReadStack()
{
	TypeID type = GetTypeCode<T>();
	std::stack<T> result;
	auto size = ReadInt();
	T* resultemp = new T[size];
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			resultemp[i] = *tempresult;
		}
		else
		{
			resultemp[i] = T();
		}
	}
	for (int i2 = size-1; i2 >= 0; i2--)
	{
		result.push(resultemp[i2]);
	}
	return result;
}

template<typename T>
std::queue<T> BytePack::ReadQueue()
{
	TypeID type = GetTypeCode<T>();
	std::queue<T> result;
	auto size = ReadInt();
	T* resultemp = new T[size];
	for (int i = 0; i < size; i++)
	{
		bool success = false;
		T* tempresult = (T*)ReadByTypeID(type, success);
		if (success)
		{
			result.push(*tempresult);
		}
		else
		{
			result.push(T());
		}
	}
	return result;
}

void BytePack::Write(ByteArray bytes)
{
	auto size = bytes.size();
	if (count+size > capacity && !TryAddCapacity(size))
	{
		throw "IndexOutOfRangeException";
	}
	for (int i = 0; i < size; i++)
	{
		buff.SetValue(index++, bytes[i]);
	}
	if (index > count)
	{
		count = index;
	}
}

BytePack::~BytePack()
{
}

int BytePack::get_Count()
{
	return count;
}

int BytePack::get_Capacity()
{
	return capacity;
}

int BytePack::get_Index()
{
	return index;
}

void BytePack::ResetIndex()
{
	index = 0;
}

byte BytePack::ReadByte()
{
	if (index+1 < count)
	{
		return buff[index++];
	}
	else
	{
		throw "Error: Current >= Count";
	}
}
char BytePack::ReadChar()
{
	char val = *(char*)ReadBytes(1);
	return val;
}
wchar_t BytePack::ReadWchar_t()
{
	short val = *(wchar_t*)ReadBytes(2);
	return val;
}
__int16 BytePack::ReadShort()
{
	short val = *(__int16 *)ReadBytes(2);
	return val;
}
uint16_t BytePack::ReadUshort()
{
	return (uint16_t)ReadShort();
}
int BytePack::ReadInt()
{
	int val = *(int*)ReadBytes(4);
	return val;
}
uint32_t BytePack::ReadUint()
{
	return (uint32_t)ReadInt();
}
__int64 BytePack::ReadLong()
{
	__int64 val = *(__int64*)ReadBytes(8);
	return val;
}
uint64_t BytePack::ReadUlong()
{
	return (uint64_t)ReadLong();
}
float BytePack::ReadFloat()
{
	float val = *(float*)ReadBytes(4);
	return val;
}
double BytePack::ReadDouble()
{
	double val = *(double*)ReadBytes(8);
	return val;
}
bool BytePack::ReadBoolean()
{
	return (*(bool*)ReadBytes(1));
}
std::string BytePack::ReadString()
{
	auto size = ReadInt();
	char* c = new char[size];
	
	auto buff = ReadBytes(size);
	for (int i = 0; i < size; i++)
	{
		char e = (char)buff[i];
		c[i] = e;
	}
	return std::string(c,size);
}
void BytePack::WriteByTypeID(void* val,TypeID type)
{
	switch (type)
	{
	case TypeID::INT32:
		Write(*((int*)val));
		break;
	case TypeID::INT16:
		Write(*((int16_t*)val));
		break;
	case TypeID::INT64:
		Write(*((int64_t*)val));
		break;
	case TypeID::Float:
		Write(*((float*)val));
		break;
	case TypeID::Double:
		Write(*((double*)val));
		break;
	case TypeID::Bool:
		Write(*((bool*)val));
		break;
	case TypeID::Char:
		Write(*((char*)val));
		break;
	case TypeID::Wchar_t:
		Write(*((wchar_t*)val));
		break;
	case TypeID::Uint16:
		Write(*((uint16_t*)val));
		break;
	case TypeID::Uint32:
		Write(*((uint32_t*)val));
		break;
	case TypeID::Uint64:
		Write(*((uint64_t*)val));
		break;
	case TypeID::String:
		Write(*((std::string*)val));
		break;
	case TypeID::Byte:
		Write(*((byte*)val));
		break;
	}
}

template<typename T>
T* GetIntPtr(T value)
{
	T* val2 = new T();
	*val2 = value;
	return val2;
}
void* BytePack::ReadByTypeID(TypeID type,bool &success)
{
	void* result = NULL;
	success = true;
	switch (type)
	{
	case TypeID::INT32:
		result = GetIntPtr(ReadInt());
		break;
	case TypeID::INT16:
		result = GetIntPtr(ReadShort());
		break;
	case TypeID::INT64:
		result = GetIntPtr(ReadLong());
		break;
	case TypeID::Float:
		result = GetIntPtr(ReadFloat());
		break;
	case TypeID::Double:
		result = GetIntPtr(ReadDouble());
		break;
	case TypeID::Bool:
		result = GetIntPtr(ReadBoolean());
		break;
	case TypeID::Char:
		result = GetIntPtr(ReadChar());
		break;
	case TypeID::Wchar_t:
		result = GetIntPtr(ReadWchar_t());
		break;
	case TypeID::Uint16:
		result = GetIntPtr(ReadUshort());
		break;
	case TypeID::Uint32:
		result = GetIntPtr(ReadUint());
		break;
	case TypeID::Uint64:
		result = GetIntPtr(ReadUlong());
		break;
	case TypeID::String:
		result = GetIntPtr(ReadString());
		break;
	case TypeID::Byte:
		result = GetIntPtr(ReadByte());
		break;
	default:
		success = false;
		break;
	}

	return result;
}

void BytePack::Write(byte val)
{
	Write(ByteArray::Create((byte*)&val, 1));
}
void BytePack::Write(__int16 val)
{
	Write(ByteArray::Create((byte*)&val, 2));
}
void BytePack::Write(int val)
{
	Write(ByteArray::Create((byte*)&val,4));
}
void BytePack::Write(__int64 val)
{
	Write(ByteArray::Create((byte*)&val, 8));
}
void BytePack::Write(float val)
{
	Write(ByteArray::Create((byte*)&val, 4));
}
void BytePack::Write(double val)
{
	
	Write(ByteArray::Create((byte*)&val, 8));
}
void BytePack::Write(bool val)
{
	Write(ByteArray::Create((byte*)&val, 1));
}
void BytePack::Write(char val)
{
	Write(ByteArray::Create((byte*)&val, 1));
}
void BytePack::Write(wchar_t val)
{
	Write(ByteArray::Create((byte*)&val, 2));
}
void BytePack::Write(uint16_t val)
{
	Write((__int16)val);
}
void BytePack::Write(uint32_t val)
{
	Write((int)val);
}
void BytePack::Write(uint64_t val)
{
	Write((__int64)val);
}
void BytePack::Write(std::string val)
{
	auto size = val.size();
	Write(size);
	for (size_t i = 0; i < size; i++)
	{
		Write(val[i]);
	}	
}
template<typename T>
void BytePack::Write(T val[],int size)
{
	
	
	TypeID type = GetTypeCode<T>();
	Write(size);
	for (int i = 0; i < size; i++)
	{
		WriteByTypeID((void*)&val[i], type);
	}
}
template<typename T>
void BytePack::Write(std::vector<T> val)
{
	TypeID type = GetTypeCode<T>();
	Write((int)val.size());
	for (T e : val)
	{
		WriteByTypeID((void*)&e, type);
	}
}
template<typename T, typename T2>
void BytePack::Write(std::map<T, T2> val)
{
	std::map<int, int> e;
	TypeID type = GetTypeCode<T>();
	TypeID type2 = GetTypeCode<T2>();
	Write((int)val.size());
	for (std::pair<T,T2> e: val)
	{
		WriteByTypeID((void*)&e.first, type);
		WriteByTypeID((void*)&e.second, type2);
	}
	
}
template<typename T, size_t T2>
void BytePack::Write(std::array<T, T2> val)
{
	TypeID type = GetTypeCode<T>();
	for (T e : val)
	{
		WriteByTypeID((void*)&e, type);
	}
}
template<typename T>
void BytePack::Write(std::deque<T> val)
{
	TypeID type = GetTypeCode<T>();
	Write((int)val.size());
	for (T e : val)
	{
		WriteByTypeID((void*)&e, type);
	}
}
template<typename T>
void BytePack::Write(std::forward_list<T> val)
{
	
	TypeID type = GetTypeCode<T>();
	int size = 0;
	for (auto e : val)
	{
		size += 1;
	}
	Write(size);
	for (auto e : val)
	{
		WriteByTypeID((void*)&e, type);
	}
}
template<typename T>
void BytePack::Write(std::list<T> val)
{
	TypeID type = GetTypeCode<T>();
	Write((int)val.size());
	for (T e : val)
	{
		WriteByTypeID((void*)&e, type);
	}
}
template<typename T>
void BytePack::Write(std::set<T> val)
{
	TypeID type = GetTypeCode<T>();
	Write((int)val.size());
	for (T e : val)
	{
		WriteByTypeID((void*)&e, type);
	}
}
template<typename T>
void BytePack::Write(std::stack<T> val)
{
	TypeID type = GetTypeCode<T>();
	Write((int)val.size());
	while (!val.empty())
	{
		T value = val.top();
		WriteByTypeID((void*)&value, type);
		val.pop();
	}
}
template<typename T>
void BytePack::Write(std::queue<T> val)
{
	TypeID type = GetTypeCode<T>();
	Write((int)val.size());
	while (!val.empty())
	{
		T value = val.front();
		WriteByTypeID((void*)&value, type);
		val.pop();
	}
}
template<typename T>
TypeID BytePack::GetTypeCode()
{
	TypeID result = TypeID::None;
	const std::type_info& c = typeid(T);
	
	if (c == typeid(int))
	{
		result = TypeID::INT32;
	}
	else if (c == typeid(ByteArray))
	{
		result = TypeID::ByteArray;
	}
	else if (c == typeid(__int16))
	{
		result = TypeID::INT16;
	}
	else if (c == typeid(byte))
	{
		result = TypeID::Byte;
	}
	else if (c == typeid(__int64))
	{
		result = TypeID::INT64;
	}
	else if (c == typeid(float))
	{
		result = TypeID::Float;
	}
	else if (c == typeid(double))
	{
		result = TypeID::Double;
	}
	else if (c == typeid(bool))
	{
		result = TypeID::Bool;
	}
	else if (c == typeid(char))
	{
		result = TypeID::Char;
	}
	else if (c == typeid(wchar_t))
	{
		result = TypeID::Wchar_t;
	}
	else if (c == typeid(uint16_t))
	{
		result = TypeID::Uint16;
	}
	else if (c == typeid(uint32_t))
	{
		result = TypeID::Uint32;
	}
	else if (c == typeid(uint64_t))
	{
		result = TypeID::Uint64;
	}
	else if (c == typeid(std::string))
	{
		result = TypeID::String;
	}
	return result;
}

bool BytePack::TryAddCapacity(size_t value)
{
	auto tempcapacity = capacity * 2 + value;
	if (tempcapacity > MaxCapacity)
	{
		return false;
	}
	else
	{
		
		capacity = tempcapacity;
		auto newbuff = new byte[capacity];
		for (int i = 0; i < count; i++)
		{
			newbuff[i] = buff[i];
		}
		buff.Clear();
		buff = ByteArray::Create(newbuff, capacity);
		return true;
	}
}
byte* BytePack::ReadBytes(int size)
{
	if (index + size > count)
	{
		throw "IndexOutOfRangeException";
	}
	byte* val = new byte[size];
	for (int i = 0; i < size; i++)
	{
		val[i] = buff[index++];
	}
	return val;
}
void calcule(void(*fp)())
{
	time_t begin, end;
	time(&begin);
	fp();
	time(&end);
	double difference = difftime(end, begin);
	printf("time taken for function() %.2lf seconds.\n", difference);
}
int main()
{
	calcule([]()
	{
		auto bp = new BytePack();
		std::queue<int> myqueue;

		for (int i = 0; i < 5; ++i) myqueue.push(i);
		bp->Write(myqueue);
		bp->ResetIndex();
		auto e = bp->ReadQueue<int>();
	});	
	system("pause");
    return 0;
}

