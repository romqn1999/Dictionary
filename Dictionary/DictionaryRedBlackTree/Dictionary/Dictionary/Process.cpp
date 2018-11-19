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
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//printf("%s\n", fileName);
	FILE *f = fopen(fileName, "r");
	if (f == nullptr) {
		printf("Can't open data file.\n");
		return false;
	}
	char cstr[1234];
	string s;
	while (fgets(cstr, 1233, f)) {
		//cout << s << "\n";
		s = string(cstr);
		size_t foundPos = s.find("  ", 0);
		if (foundPos == string::npos) continue;
		//cout << i << " " << s.substr(0, foundPos) << "  " << s.substr(foundPos + 2, s.length() - foundPos - 1) << "\n";
		m_data.Insert(s.substr(0, foundPos), s.substr(foundPos + 2, s.length() - foundPos - 1));
	}
	printf("Load data done.\n");
	fclose(f);
	return true;
}

string Dictionary::search(string key) {
	standardize(key);
	return m_data.Find(key);
}

void Dictionary::add(string key, string value) {
	standardize(key);
	m_data.Insert(key, value);
}

void Dictionary::edit(string key, string value) {
	standardize(key);
	m_data.Delete(key);
	m_data.Insert(key, value);
}

void Dictionary::remove(string key) {
	standardize(key);
	m_data.Delete(key);
}

bool Dictionary::saveData(const char *fileName) {
	//int old = _dup(1);
	FILE *f = freopen(fileName, "w", stdout);
	if (f == nullptr) {
		printf("Can't open data file.\n");
		return false;
	}
	m_data.Inorder();
	/*fclose(f);
	_dup2(old, 1);*/
	//freopen("CONOUT$", "w", stdout);
	//cout << "Data saved.\n";
	return true;
}
