#include "processFile.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void generate_distribution(const string& filename, int n,
	int read0, int write0, int read1, int write1)
{
	ofstream file(filename);
	if (!file)
	{
		cerr << "Error: can't open file " << filename << endl;
		return;
	}

	int count_read0 = n * read0 / 100;
	int count_write0 = n * write0 / 100;
	int count_read1 = n * read1 / 100;
	int count_write1 = n * write1 / 100;
	int count_string = n - (count_read0 + count_write0 + count_write1 + count_read1);

	vector<string> commands;
	commands.reserve(n);

	commands.insert(commands.end(), count_read0, "read 0");
	commands.insert(commands.end(), count_write0, "write 0 1");
	commands.insert(commands.end(), count_write1, "write 1 1");
	commands.insert(commands.end(), count_read1, "read 1");
	commands.insert(commands.end(), count_string, "string");

	static random_device rd;
	static mt19937 gen(rd());
	shuffle(commands.begin(), commands.end(), gen);

	for (auto& cmd : commands)
		file << cmd << '\n';
	file.close();
}

void get_correct_dist(const string& filename, int n)
{
	generate_distribution(filename, n, 5, 40, 5, 5);

}

void get_even_dist(const string& filename, int n)
{
	generate_distribution(filename, n, 20, 20, 20, 20);
}

void get_wrong_dist(const string& filename, int n)
{
	generate_distribution(filename, n, 10, 5, 50, 10);
}

vector< string> readFile(const string& filename)
{
	ifstream file(filename);
	if (!file)
	{
		cout << "Error: can't open file " << filename << endl;
		return {};
	}
	vector <string> actions;
	string line;
	while (getline(file, line)) {
		actions.push_back(line);
	}

	return actions;
}


void processFile(const vector<string>& actions, DataStruct& data)
{
	for (auto& action : actions)
	{
		istringstream iss(action);
		string command;
		int index; int value;

		iss >> command;
		if (command == "write")
		{
			iss >> index >> value;
			data.write(index, value);
		}
		else if (command == "read")
		{
			iss >> index;
			data.read(index);
		}
		else
		{
			auto s = data.operator string();
		}

	}
}