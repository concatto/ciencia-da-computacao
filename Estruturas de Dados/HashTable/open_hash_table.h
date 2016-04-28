#ifndef OPEN_HASH_TABLE_H
#define OPEN_HASH_TABLE_H

#include "hash_table.h"
#include "Windows.h"
#include <iostream>

template <class K, class V>
class OpenHashTable : public HashTable<K, V> {
private:
	using HashTable<K, V>::Capacity;
	using HashTable<K, V>::size;
	Pair<K, V>* data[Capacity];
	int iterations;
	const int probingIncrement = 1;

	int probeOpenSlot(int startIndex) {
		iterations = 1;
		for (int i = startIndex; i < (startIndex + Capacity); i += probingIncrement) {
			iterations++;
			int index = i % Capacity;
			Pair<K, V>* pair = data[index];
			Sleep(20);
			if (pair == nullptr) {
				return index;
			} else {
				std::cout << "Key at " << index << " is " << pair->getKey() << "\n";
			}
		}
		return -1;
	}
	
	int findByIndex(const K& key) {
		int startIndex = this->getIndex(key);
		
		iterations = 1;
		for (int i = startIndex; i < (startIndex + Capacity); i += probingIncrement) {
			iterations++;
			int index = i % Capacity;
			if (data[index] == nullptr) {
				return -1;
			} else if (data[index]->getKey() == key) {
				return index;
			}
		}
		return -1;
	}

public:
	OpenHashTable() : HashTable<K, V>() {
		for (int i = 0; i < Capacity; i++) {
			data[i] == nullptr;
		}
	}

	bool insert(K key, V value) override {
		iterations = 1;

		if (size >= Capacity) {
			return false;
		}

		unsigned int hash = this->getIndex(key);
		std::cout << "Hashed to " << hash << "!; ";
		int index = probeOpenSlot(hash);
		if (index == -1) {
			std::cout << "what\n";
			return false;
		} else {
			std::cout << "found slot at " << index << "\n";
			data[index] = new Pair<K, V>(key, value);
			size++;
			return true;
		}
	}

	bool contains(const K& key) override {
		return find(key) != nullptr;
	}

	Pair<K, V>* find(const K& key) override {
		int index = findByIndex(key);
		if (index == -1) {
			return nullptr;
		} else {
			return data[index];
		}
	}

	bool remove(const K& key) override {
		int index = findByIndex(key);
		if (index == -1) {
			return false;
		} else {
			delete data[index];
			data[index] = nullptr;
			size--;
			return true;
		}
	}

	int getIterations() const {
		return iterations;
	}
};

#endif
