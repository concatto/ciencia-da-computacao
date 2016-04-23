#include <utility>
#include <functional>

template <class K, class V>
class HashTable {
protected:
	const static unsigned int Capacity = 1000;
	std::hash<K> hasher;
	
	int getIndex(const K& key) {
		int hash = hasher(key);
		return hash % Capacity;
	}
	
public:
	HashTable() {}
	
	virtual void insert(K key, V value) = 0;
	virtual bool contains(K key) = 0;
	virtual V find(K key) = 0;
	virtual void remove(K key) = 0;
};