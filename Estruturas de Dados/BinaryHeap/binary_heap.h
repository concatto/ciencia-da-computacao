#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include <initializer_list>

template <class K, class V>
struct HeapNode {
    K key;
    V value;

    HeapNode() {}
    HeapNode(K key, V value = V()) : key(key), value(value) {}
};

template <class K, class V>
class BinaryHeap {
    using Node = HeapNode<K, V>;

private:
    Node* data;
    int size;
    int maximum;

    void heapifyUp(int index) {
        if (index > 0) {
            int j = parent(index);
            if (data[index].key < data[j].key) {
                std::swap(data[index], data[j]);
                heapifyUp(j);
            }
        }
    }

    void heapifyDown(int index) {
        int j = leftChild(index);
        if (j > size) return;

        //If the right child exists and has the lower key
        if ((j + 1) < size && (data[j].key > data[j + 1].key)) {
            j++;
        }

        if (data[j].key < data[index].key) {
            std::swap(data[index], data[j]);
            heapifyDown(j);
        }
    }

    int parent(int index) {
        return ((index - 1) / 2);
    }

    int leftChild(int index) {
        return (2 * index) + 1;
    }

    int rightChild(int index) {
        return leftChild(index) + 1;
    }

public:
    BinaryHeap(int maximum) : data(new Node[maximum]), size(0), maximum(maximum) {}
    BinaryHeap(int maximum, std::initializer_list<Node> nodes) : BinaryHeap<K, V>(maximum) {
        for (const Node node : nodes) {
            insert(node.key, node.value);
        }
    }

    void insert(K key, V value) {
        data[size] = Node(key, value);
        heapifyUp(size);
        size++;
    }

    bool removeMinimum() {
        if (size > 0) {
            data[0] = data[size - 1];
            size--;
            heapifyDown(0);
            return true;
        }
        return false;
    }

    Node getMinimum() const {
        return data[0];
    }

    int getSize() const {
        return size;
    }

    void changeKey(int index, K newKey) {
        data[index].key = newKey;
        if (index > 0 && newKey < data[parent(index)].key) {
            heapifyUp(index);
        } else {
            heapifyDown(index);
        }
    }

    int search(const K& key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) {
                return i;
            }
        }
        return -1;
    }

    int searchByValue(const V& value) {
        for (int i = 0; i < size; i++) {
            if (data[i].value == value) {
                return i;
            }
        }
        return -1;
    }

    Node* getData() const {
        return data;
    }
};

#endif
