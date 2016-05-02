#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <utility>
#include <functional>

template <class K, class V>
class Pair {
private:
	K key;
	V value;

public:
	Pair() {}
	Pair(K key, V value) : key(key), value(value) {}
	K getKey() const { return key; }
	V getValue() const { return value; }
};

template <class K, class V>
class HashTable {
private:
	std::hash<K> hasher;

protected:
	const static unsigned int Capacity = 1000;
	int size;
	int iterations;

	int generateIndex(const K& key) {
		int hash = hasher(key);
		return hash % Capacity;
	}

public:
	HashTable() : size(0) {}

	virtual bool insert(K key, V value) = 0;
	virtual bool contains(const K& key) = 0;
	virtual Pair<K, V>* find(const K& key) = 0;
	virtual void clear() = 0;

	V get(const K& key) {
		return find(key).getValue();
	}

	int getSize() const {
		return size;
	}

	int getIterations() const {
		return iterations;
	}
};

#endif
