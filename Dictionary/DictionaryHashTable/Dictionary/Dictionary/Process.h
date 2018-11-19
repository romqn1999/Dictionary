#pragma once

#include "HashMap.h"
#include <string>
#include <iostream>
#include <chrono>

using namespace std;
//using namespace std::chrono;

class Dictionary
{
private:
	HashMap<string, string, 100007, KeyHash<string, 100007>> m_data;
public:
	Dictionary() {};
	~Dictionary() {};
	bool loadData(const char *fileName);
	string search(string s);
	void add(string key, string value);
	void edit(string key, string value);
	void remove(string key);
	bool saveData(const char *fileName);
};

void standardize(string &s);
