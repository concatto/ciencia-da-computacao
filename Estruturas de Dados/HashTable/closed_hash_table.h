#ifndef CLOSED_HASH_TABLE_H
#define CLOSED_HASH_TABLE_H

#include "hash_table.h"
#include "linked_list.h"

template <class K, class V>
class ClosedHashTable : public HashTable<K, V> {
	using PairList = LinkedList<Pair<K, V>>;

private:
	using HashTable<V, V>::size;
	PairList data[HashTable<K, V>::Capacity];
	int iterations;

public:
	bool insert(K key, V value) override {
		int index = this->getIndex(key);
		PairList& list = data[index];

		bool success = list.prepend(Pair<K, V>(key, value));
		iterations = list.getIterations();
		size++;
		return success;
	}

	bool contains(const K& key) override {
		return find(key).isInitialized();
	}

	Pair<K, V> find(const K& key) override {
		iterations = 1;
		PairList& list = data[this->getIndex(key)];
		list.begin();
		while (list.hasNext()) {
			Pair<K, V>& pair = list.next();
			iterations++;
			if (pair.getKey() == key) {
				return pair;
			}
		}
		//Não existe!
		return Pair<K, V>();
	}

	bool remove(const K& key) override {
		if (contains(key)) {
			size--;
			return data[this->getIndex(key)].remove(iterations - 1);
		}
		return false;
	}

	int getIterations() const {
		return iterations;
	}
};

#endif
