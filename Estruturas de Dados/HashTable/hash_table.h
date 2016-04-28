#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <utility>
#include <functional>

template <class K, class V>
class Pair {
private:
	K key;
	V value;
	bool initialized;

public:
	Pair() : initialized(false) {}
	Pair(K key, V value) : key(key), value(value), initialized(true) {}
	K getKey() const { return key; }
	V getValue() const { return value; }
	bool isInitialized() const { return initialized; }
};

template <class K, class V>
class HashTable {
private:
	std::hash<K> hasher;
	
protected:
	const static unsigned int Capacity = 1000;
	int size;

	int getIndex(const K& key) {
		int hash = hasher(key);
		return hash % Capacity;
	}

public:
	HashTable() {}

	virtual bool insert(K key, V value) = 0;
	virtual bool contains(const K& key) = 0;
	virtual Pair<K, V>* find(const K& key) = 0;
	virtual bool remove(const K& key) = 0;

	V get(const K& key) {
		return find(key).getValue();
	}

	int getSize() const {
		return size;
	}
};

#endif
