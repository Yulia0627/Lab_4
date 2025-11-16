#pragma once
#include "struct.h"
#include <chrono>
#include <random>

void get_correct_dist(const string& filename, int n = 1000000);
void get_even_dist(const string& filename, int n = 1000000);
void get_wrong_dist(const string& filename, int n = 1000000);

void processFile(const vector<string>& actions, DataStruct& data);
vector< string> readFile (const string& filename);

template <typename Func>
double measureTime(Func func)
{
	auto start = chrono::high_resolution_clock::now();
	func();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end - start;
	return diff.count();
}