#pragma once

#include "AVLTree.h"
#include <string>
#include <iostream>

using namespace std;

//static AVLTree<string> data;

class Dictionary
{
private:
	AVLTree<string> m_data;
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
