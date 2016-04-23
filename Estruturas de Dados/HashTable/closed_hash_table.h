#include "hash_table.h"
#include "linked_list.h"

template <class K, class V>
struct Pair {
	K key;
	V value;
	
	Pair() {}
	Pair(K key, V value) : key(key), value(value) {}
};

template <class K, class V>
class ClosedHashTable : public HashTable<K, V> {
	using PairList = LinkedList<Pair<K, V>>;
	
private:
	PairList data[HashTable<K, V>::Capacity];

public:	
	void insert(K key, V value) override {
		PairList& list = data[this->getIndex(key)];
		
		list.append(Pair<K, V>(key, value));
	}
	
	bool contains(K key) override {
		
	}
	
	V find(K key) override {
		PairList& list = data[this->getIndex(key)];
		list.begin();
		while (list.hasNext()) {
			Pair<K, V>& pair = list.next();
			if (pair.key == key) {
				return pair.value;
			}
		}
		//Não existe!
		return V();
	}
	
	void remove(K key) override {
		
	}
};
