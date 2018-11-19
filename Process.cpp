
#include "stdafx.h"
#include "Process.h"
#include <io.h>

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
	//auto start = high_resolution_clock::now();
	FILE *f = fopen(fileName, "r");
	if (!f) {
		printf("Can't open data file.\n");
		return false;
	}
	char cstr[1234];
	string s;
	//int i = 0;
	while (fgets(cstr, 1233, f)) {
		int k = 0;
		while (k + 1 < strlen(cstr) && !(cstr[k] == ' ' && cstr[k + 1] == ' ')) ++k;
		if (cstr[k] != ' ' || cstr[k + 1] != ' ') continue;
		cstr[k] = '\0';
		//cout << string(cstr) << "  " << string(cstr + (k + 2)) << "\n";
		m_data.put(string(cstr), string(cstr + (k + 2)));
		//s = string(cstr);
		//size_t foundPos = s.find("  ", 0);
		//if (foundPos == string::npos) continue;
		//++i;
		//cout << i << " " << s.substr(0, foundPos) << "  " << s.substr(foundPos + 2, s.length() - foundPos - 1) << "\n";
		//m_data.put(s.substr(0, foundPos), s.substr(foundPos + 2, s.length() - foundPos - 1));
	}
	//cout << i << "\n";
	//printf("Load data done.\n");
	fclose(f);
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<milliseconds>(stop - start);
	//cout << "Load data done in " << duration.count() << "ms\n";
	//cout << m_data.getLenghtLongestBucket() << "\n";
	return true;
}

string Dictionary::search(string key) {
	standardize(key);
	string value;
	m_data.get(key, value);
	return value;
}

void Dictionary::add(string key, string value) {
	standardize(key);
	m_data.put(key, value);
}

void Dictionary::edit(string key, string value) {
	standardize(key);
	//m_data.remove(key);
	m_data.put(key, value);
}

void Dictionary::remove(string key) {
	standardize(key);
	m_data.remove(key);
}

bool Dictionary::saveData(const char *fileName) {
	//auto start = high_resolution_clock::now();
	FILE *f = freopen(fileName, "w", stdout);
	if (f == nullptr) {
		printf("Can't open data file.\n");
		return false;
	}
	m_data.printAll();
	freopen("CONOUT$", "w", stdout);
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<milliseconds>(stop - start);
	//cout << "Data saved in " << duration.count() << "ms\n";
	return true;
}
