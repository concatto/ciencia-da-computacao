#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "base.h"
#include <iostream>
#include <algorithm>

template <class T>
class StaticList {
private:
    int maximum;
    int size;
    T* data;

    void bubbleSort() {
        bool moved;
        do {
            moved = false;
            for (int i = 0; i < size - 1; i++) {
                if (data[i] > data[i + 1]) {
                    std::swap(data[i], data[i + 1]);
                    moved = true;
                }
            }
        } while (moved);
    }

    void combine(StaticList<T>& left, StaticList<T>& right) {
        StaticList<T> combined(left.size + right.size);

        int leftIndex = 0;
        int rightIndex = 0;
        for (int i = 0; i < combined.maximum; i++) {
            if (leftIndex == left.size) {
                combined.append(right[rightIndex]);
                rightIndex++;
            } else if (rightIndex == right.size) {
                combined.append(left[leftIndex]);
                leftIndex++;
            } else if (left[leftIndex] > right[rightIndex]) {
                combined.append(right[rightIndex]);
                rightIndex++;
            } else {
                combined.append(left[leftIndex]);
                leftIndex++;
            }
        }

        //Como os dados são contíguos, podemos ir além do limite de "left"
        for (int i = 0; i < combined.size; i++) {
            left.data[i] = combined.data[i];
        }
    }

    void mergeSort() {
        if (size > 1) {
            int middle = size / 2;

            StaticList<T> left(data, middle);
            StaticList<T> right(data + middle, size - middle); //Utilização de aritmética de ponteiro

            left.mergeSort();
            right.mergeSort();

            combine(left, right);
        }
    }

public:
    StaticList(int maximum = 10) : maximum(maximum), size(0), data(new T[maximum]) {}
    StaticList(T* data, int size) : maximum(size), size(size), data(data) {}

    void sort(SortMode::Type mode = SortMode::Merge) {
        if (mode == SortMode::Bubble) {
            bubbleSort();
        } else if (mode == SortMode::Merge) {
            mergeSort();
        }
	}

    /*void shuffle() {
        for (int i = 0; i < size - 1; i++) {
            int index = RandomNumberGenerator::generate(0, size - i - 1);
            std::swap(data[i], data[i + index]);
        }
    }*/

    bool remove(int position) {
        if (position > size || position < 0) return false;

        for (int i = position; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        size--;
        return true;
    }

    bool removeFirst() {
        return remove(0);
    }

    bool removeLast() {
        return remove(size - 1);
    }

    bool insert(T value, int position) {
        if (position > size || position < 0 || size == maximum) return false;

        for (int i = size; i > position; i--) {
            data[i] = data[i - 1];
        }

        data[position] = value;
        size++;
        return true;
    }

    bool append(T value) {
        return insert(value, size);
    }

    bool prepend(T value) {
        return insert(value, 0);
    }

    int getSize() {
        return size;
    }

    T& operator[](int index) {
        return data[index];
    }
};

template <class T>
std::ostream& operator<<(std::ostream& out, StaticList<T>& list) {
    out << "{";
    for (int i = 0; i < list.getSize(); i++) {
        if (i > 0) {
            out << ", ";
        }

        out << list[i];
    }
    out << "}";
    return out;
}

#endif
