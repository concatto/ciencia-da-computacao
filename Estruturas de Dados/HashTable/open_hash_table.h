#ifndef OPEN_HASH_TABLE_H
#define OPEN_HASH_TABLE_H

#include "hash_table.h"
#include <iostream>

template <class K, class V>
class OpenHashTable : public HashTable<K, V> {
private:
	using HashTable<K, V>::Capacity;
	using HashTable<K, V>::size;
	Pair<K, V> data[Capacity];
	int iterations;
	const int probingIncrement = 1;

	int probeSlot(int startIndex) {
		iterations = 1;
		for (int i = startIndex; i < (startIndex + Capacity); i += probingIncrement) {
			iterations++;
			int index = i % Capacity;
			Pair<K, V>& pair = data[index];
			if (!pair.isInitialized()) {
				return index;
			}
		}
		return -1;
	}

public:
	bool insert(K key, V value) override {
		iterations = 1;

		if (size >= Capacity) {
			return false;
		}

		int index = probeSlot(this->getIndex(key));
		data[index] = Pair<K, V>(key, value);
		size++;
		return true;
	}

	bool contains(const K& key) override {
		return find(key).isInitialized();
	}

	Pair<K, V> find(const K& key) override {
		int startIndex = this->getIndex(key);

		iterations = 1;
		for (int i = startIndex; i < (startIndex + Capacity); i += probingIncrement) {
			iterations++;
			int index = i % Capacity;
			if (!data[index].isInitialized()) {
				return Pair<K, V>();
			} else if (data[index].getKey() == key) {
				return data[index];
			}
		}
		return Pair<K, V>();
	}

	bool remove(const K& key) override {
		if (contains(key)) {
			data[iterations % Capacity] = Pair<K, V>();
			size--;
			return true;
		}
		return false;
	}

	int getIterations() const {
		return iterations;
	}
};

#endif
