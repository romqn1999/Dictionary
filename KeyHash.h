#pragma once

#include <string>
#include <iostream>

using namespace std;


// Default hash function class
template <typename K, size_t tableSize>
struct KeyHash {
	/*unsigned long operator()(const K &key) const
	{
		return reinterpret_cast<unsigned long>(key) % tableSize;
	}*/

	unsigned long operator()(const K &key) const {
		unsigned long long value = 0;
		for (int i = 0; i < key.size(); ++i) {
			//cout << (int)key[i] << " ";
			value = (value * 311 + key[i]) % tableSize;
		}
		//cout << "\n";
		return value;
	}
};