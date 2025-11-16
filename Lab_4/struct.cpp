#include "struct.h"

DataStruct :: DataStruct(): fields(2, 0) {}

mutex& DataStruct::getMutex(int index)
{
	if (index == 0) return mtx0;
	else return mtx1;
}
int DataStruct::read(int index)
{
	lock_guard<mutex> lock(getMutex(index));
	return fields[index];
}

void DataStruct::write(int index, int value)
{
	lock_guard<mutex> lock(getMutex(index));
	fields[index] = value;
}

DataStruct :: operator string() 
{
	lock_guard<mutex> lock0(mtx0);
	lock_guard<mutex> lock1(mtx1);
	string result;
	for (int i = 0; i < fields.size(); i++)
	{
			result += to_string(fields[i]);
			if (i < fields.size() - 1)
			{
				result += " ";
			}
	}
	return result;
}