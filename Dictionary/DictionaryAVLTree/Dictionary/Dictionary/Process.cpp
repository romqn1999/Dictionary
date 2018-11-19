#include "stdafx.h"
#include "Process.h"

//static AVLTree<string> data;

void standardize(string &s) {
	while (s[0] == ' ') s.erase(0);
	if ('a' <= s[0] && s[0] <= 'z') s[0] += 'A' - 'a';
	while (s.size() > 0 && s[s.size() - 1] == ' ') s.erase(s.size() - 1);
	int i = 0;
	while (i + 1 < s.size())
	{
		if (s[i] == ' ' && s[i + 1] == ' ') s.erase(i);
		else ++i;
	}
}

bool Dictionary::loadData(const char *fileName) {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	FILE *f = freopen(fileName, "r", stdin);
	if (f == nullptr) {
		return false;
	}
	string s;
	while (getline(cin, s)) {
		//cout << s << "\n";
		size_t foundPos = s.find("  ", 0);
		if (foundPos == string::npos) continue;
		//cout << i << " " << s.substr(0, foundPos) << "  " << s.substr(foundPos + 2, s.length() - foundPos - 1) << "\n";
		m_data.insert(s.substr(0, foundPos), s.substr(foundPos + 2, s.length() - foundPos - 1));
	}
	cout << "Load data done.\n";
	return true;
}

string Dictionary::search(string key) {
	standardize(key);
	return m_data.search(key);
}

void Dictionary::add(string key, string value) {
	standardize(key);
	m_data.insert(key, value);
}

void Dictionary::edit(string key, string value) {
	standardize(key);
	m_data.remove(key);
	m_data.insert(key, value);
}

void Dictionary::remove(string key) {
	standardize(key);
	m_data.remove(key);
}

bool Dictionary::saveData(const char *fileName) {
	FILE *f = freopen(fileName, "w", stdout);
	if (f == nullptr) {
		printf("Can't open data file.\n");
		return false;
	}
	m_data.inorderTravesal();
	//cout << "Data saved.\n";
	return true;
}
