#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "list.h"

template <class T>
class StaticList : public List<T> {
private:
    using List<T>::size;
    int iterator;
    int maximum;
    T* data;

public:
    StaticList(int maximum = 10) : List<T>(0), maximum(maximum), data(new T[maximum]) {}
    StaticList(T* data, int size) : List<T>(size), maximum(size), data(data) {}

    bool remove(int position) override {
        if (position > size || position < 0) return false;

        for (int i = position; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        size--;
        return true;
    }

    bool insert(T value, int position) override {
        if (position > size || position < 0 || size == maximum) return false;

        for (int i = size; i > position; i--) {
            data[i] = data[i - 1];
        }

        data[position] = value;
        size++;
        return true;
    }

    void begin() override {
        iterator = 0;
    }

    bool hasNext() override {
        return iterator < size;
    }

    T& next() override {
        T& value = data[iterator];
        iterator++;
        return value;
    }

    T& peek() override {
        return data[iterator];
    }

    T& get(int position) override {
        return data[position];
    }

    List<T>* subList(int begin, int length) override {
        return new StaticList<T>(data + begin, length);
    }
};

#endif
