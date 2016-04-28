#ifndef CLOSED_HASH_TABLE_H
#define CLOSED_HASH_TABLE_H

#include "hash_table.h"
#include "linked_list.h"

template <class K, class V>
class ClosedHashTable : public HashTable<K, V> {
	
	using PairList = LinkedList<Pair<K, V>*>;

private:
	using HashTable<V, V>::size;
	PairList data[HashTable<K, V>::Capacity];
	int iterations;

public:
	ClosedHashTable() : HashTable<K, V>() {}

	bool insert(K key, V value) override {
		int index = this->getIndex(key);
		PairList& list = data[index];

		bool success = list.prepend(new Pair<K, V>(key, value));
		iterations = list.getIterations();
		size++;
		return success;
	}

	bool contains(const K& key) override {
		return find(key) != nullptr;
	}

	Pair<K, V>* find(const K& key) override {
		iterations = 1;
		PairList& list = data[this->getIndex(key)];
		list.begin();
		while (list.hasNext()) {
			Pair<K, V>* pair = list.next();
			iterations++;
			if (pair->getKey() == key) {
				return pair;
			}
		}
		//Não existe!
		return nullptr;
	}

	bool remove(const K& key) override {
		int index = this->getIndex(key);
		PairList& list = data[index];
		
		iterations = 1;
		list.begin();
		for (int i = 0; list.hasNext(); i++) {
			iterations++;
			Pair<K, V>* pair = list.next();
			if (pair->getKey() == key) {
				return list.remove(i);
			}
		}
		return false;
	}

	int getIterations() const {
		return iterations;
	}
};

#endif
