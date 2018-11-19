#pragma once


#include "HashNode.h"
#include "KeyHash.h"
#include <cstddef>
#include <vector>
#include <iostream>

using namespace std;


// Hash map class template
template <typename K, typename V, size_t tableSize, typename F>
class HashMap
{
private:
	// hash table
	HashNode<K, V> *table[tableSize];
	F hashFunc;

public:
	HashMap() :
		table(),
		hashFunc()
	{
	}

	~HashMap()
	{
		// destroy all buckets one by one
		for (size_t i = 0; i < tableSize; ++i) {
			HashNode<K, V> *entry = table[i];

			while (entry != NULL) {
				HashNode<K, V> *prev = entry;
				entry = entry->getNext();
				delete prev;
			}

			table[i] = NULL;
		}
	}

	bool get(const K &key, V &value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V> *entry = table[hashValue];

		while (entry != NULL) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return true;
			}

			entry = entry->getNext();
		}

		return false;
	}

	void put(const K &key, const V &value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V> *prev = NULL;
		HashNode<K, V> *entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new HashNode<K, V>(key, value);

			if (prev == NULL) {
				// insert as first bucket
				table[hashValue] = entry;

			}
			else {
				prev->setNext(entry);
			}

		}
		else {
			// just update the value
			entry->setValue(value);
		}
	}

	void remove(const K &key)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V> *prev = NULL;
		HashNode<K, V> *entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			// key not found
			return;

		}
		else {
			if (prev == NULL) {
				// remove first bucket of the list
				table[hashValue] = entry->getNext();

			}
			else {
				prev->setNext(entry->getNext());
			}

			delete entry;
		}
	}

	void printAll() {
		for (int i = 0; i < tableSize; ++i) {
			HashNode<K, V> *entry = table[i];
			while (entry)
			{
				cout << entry->getKey() << "  " << entry->getValue() << "\n\n";
				entry = entry->getNext();
			}
		}
	}

	int getLenghtLongestBucket() {
		int maxL = 0;
		for (int i = 0; i < tableSize; ++i) {
			HashNode<K, V> *entry = table[i];
			int l = 0;
			while (entry)
			{
				//cout << entry->getKey() << " " << entry->getValue() << "\n\n";
				++l;
				entry = entry->getNext();
			}
			if (maxL < l) {
				maxL = l;
			}
		}
		return maxL;
	}
};