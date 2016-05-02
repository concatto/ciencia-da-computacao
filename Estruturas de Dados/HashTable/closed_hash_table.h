#ifndef CLOSED_HASH_TABLE_H
#define CLOSED_HASH_TABLE_H

#include "hash_table.h"

template <class K, class V>
class PairNode : public Pair<K, V> {
public:
    PairNode<K, V>* next;

    PairNode() : Pair<K, V>(), next(nullptr) {}
    PairNode(K key, V value) : Pair<K, V>(key, value), next(nullptr) {}
};

template <class K, class V>
class ClosedHashTable : public HashTable<K, V> {
	using Node = PairNode<K, V>;

private:
	using HashTable<K, V>::Capacity;
	using HashTable<V, V>::size;
	using HashTable<K, V>::iterations;
	Node* data[Capacity];

public:
	ClosedHashTable() : HashTable<K, V>() {
		for (int i = 0; i < Capacity; i++) {
			data[i] = nullptr;
		}
	}

	bool insert(K key, V value) override {
		iterations = 1;
		int index = this->generateIndex(key);
		Node* node = data[index];

		if (node == nullptr) {
			data[index] = new Node(key, value);
		} else {
			while (node->next != nullptr) {
				iterations++;
				if (node->getKey() == key) return false; //Already exists
				node = node->next;
			}

			node->next = new Node(key, value);
			size++;
			return true;
		}
	}

	bool contains(const K& key) override {
		return find(key) != nullptr;
	}

	Pair<K, V>* find(const K& key) override {
		iterations = 1;
		Node* node = data[this->generateIndex(key)];
		while (node != nullptr) {
			if (node->getKey() == key) return node;
			node = node->next;
			iterations++;
		}

		return nullptr;
	}

	int getIterations() const {
		return iterations;
	}

	void clear() override {
		for (int i = 0; i < Capacity; i++) {
			Node* navigator = data[i];
			while (navigator != nullptr) {
				Node* obsolete = navigator;
				navigator = navigator->next;
				delete obsolete;
			}
			data[i] = nullptr;
		}
		size = 0;
	}
};

#endif
