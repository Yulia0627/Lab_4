#include <iostream>
#include <thread>
#include "processFile.h"
#include "struct.h"

using namespace std;

void runThreads(const vector<vector<string>>& allActions, DataStruct& data, const string& label, int threadCount)
{
	double totalTime = measureTime([&]() {
		vector<thread> threads;
		for (int i = 0; i < threadCount; ++i)
			threads.emplace_back([&, i]() { processFile(allActions[i], data); });
		for (auto& t : threads) t.join();
		});

	cout << label << ": " << totalTime << endl;
}

int main()
{
	get_correct_dist("correct_dist1.txt");
	get_even_dist("even_dist1.txt");
	get_wrong_dist("wrong_dist1.txt");

	get_correct_dist("correct_dist2.txt");
	get_even_dist("even_dist2.txt");
	get_wrong_dist("wrong_dist2.txt");

	get_correct_dist("correct_dist3.txt");
	get_even_dist("even_dist3.txt");
	get_wrong_dist("wrong_dist3.txt");

	vector<vector<string>> actions_correct = {
		readFile("correct_dist1.txt"),
		readFile("correct_dist2.txt"),
		readFile("correct_dist3.txt")
	};
	vector<vector<string>> actions_even = {
		readFile("even_dist1.txt"),
		readFile("even_dist2.txt"),
		readFile("even_dist3.txt")
	};
	vector<vector<string>> actions_wrong = {
		readFile("wrong_dist1.txt"),
		readFile("wrong_dist2.txt"),
		readFile("wrong_dist3.txt")
	};

	DataStruct data1, data2, data3, data4, data5, data6, data7, data8, data9;


	cout << "=== One thread ===" << endl;
	runThreads({ actions_correct[0] }, data1, "correct_dist", 1);
	runThreads({ actions_even[0] }, data2, "even_dist", 1);
	runThreads({ actions_wrong[0] }, data3, "wrong_dist", 1);

	cout << "\n=== Two threads ===" << endl;
	runThreads({ actions_correct[0], actions_correct[1] }, data4, "correct_dist", 2);
	runThreads({ actions_even[0], actions_even[1] }, data5, "even_dist", 2);
	runThreads({ actions_wrong[0], actions_wrong[1] }, data6, "wrong_dist", 2);

	cout << "\n=== Three threads ===" << endl;
	runThreads(actions_correct, data7, "correct_dist", 3);
	runThreads(actions_even, data8, "even_dist", 3);
	runThreads(actions_wrong, data9, "wrong_dist", 3);

}