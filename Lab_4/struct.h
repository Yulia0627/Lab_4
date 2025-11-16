#pragma once
#include <vector>
#include <mutex>
#include <string>
#include<shared_mutex>

using namespace std;

class DataStruct
{
	vector <int> fields;
	mutex mtx0;
	mutex mtx1;
	mutex& getMutex(int index);

public:
	DataStruct();
	int read(int index);
	void write(int index, int value);
	operator string();	
};
