#pragma once

#include "RBTree.h"
#include <string>
#include <iostream>

using namespace std;

class Dictionary
{
private:
	RedBlack<string, string> m_data;
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
