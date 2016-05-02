#ifndef OPEN_HASH_TABLE_H
#define OPEN_HASH_TABLE_H

#include "hash_table.h"

template <class K, class V>
class OpenHashTable : public HashTable<K, V> {
private:
	using HashTable<K, V>::Capacity;
	using HashTable<K, V>::size;
	using HashTable<K, V>::iterations;
	Pair<K, V>* data[Capacity];
	static const int ProbingIncrement = 1;

	int probe(const K& key) {
		unsigned int startIndex = this->generateIndex(key);

		iterations = 0;
		for (int i = startIndex; i < (startIndex + Capacity); i += ProbingIncrement) {
			iterations++;
			int index = i % Capacity;
			Pair<K, V>* pair = data[index];
			if (pair == nullptr || pair->getKey() == key) {
				return index;
			}
		}
		return -1;
	}

public:
	OpenHashTable() : HashTable<K, V>() {
		for (int i = 0; i < Capacity; i++) {
			data[i] = nullptr;
		}
	}

	bool insert(K key, V value) override {
		iterations = 1;

		if (size >= Capacity) {
			return false;
		}

		int index = probe(key);
		if (data[index] == nullptr) {
			data[index] = new Pair<K, V>(key, value);
			size++;
			return true;
		}

		return false; //Already exists
	}

	bool contains(const K& key) override {
		return find(key) != nullptr;
	}

	Pair<K, V>* find(const K& key) override {
		int index = probe(key);
		if (index == -1) {
			return nullptr;
		} else {
			return data[index];
		}
	}

	int getIterations() const {
		return iterations;
	}

	void clear() override {
		for (int i = 0; i < Capacity; i++) {
			if (data[i] != nullptr) {
				delete data[i];
				data[i] = nullptr;
			}
		}
		size = 0;
	}
};

#endif
