#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <ctime>

namespace SortMode {
    enum Type {Bubble, Merge};
}

class RandomNumberGenerator {
    static bool initialized;
public:
    static int generate(int min, int max) {
        if (!initialized) {
            std::srand(std::time(NULL));
            initialized = true;
        }

        return min + std::rand() % (max - min + 1);
    }
};
bool RandomNumberGenerator::initialized = false;//!!!

template <class T>
class List {
private:
    void bubbleSort() {
        bool moved;
        do {
            moved = false;
            begin();
            for (int i = 0; i < size - 1; i++) {
                T& current = next();
                T& next = peek();
                if (current > next) {
                    std::swap(current, next);
                    moved = true;
                }
            }
        } while (moved);
    }

    //O(n)
    void combine(List<T>* left, List<T>* right) {
        T* combined = new T[left->size + right->size];

        left->begin();
        right->begin();

        int leftIndex = 0;
        int rightIndex = 0;
        for (int i = 0; i < left->size + right->size; i++) {
            if (leftIndex == left->size) {
                //Não resta nada na esquerda, então adicionamos os elementos da direita
                combined[i] = right->next();
                rightIndex++;
            } else if (rightIndex == right->size) {
                //Não resta nada na direita, então os elementos da esquerda são adicionados
                combined[i] = left->next();
                leftIndex++;
            } else if (left->peek() > right->peek()) {
                //Elemento da esquerda é maior que elemento da direita, então adicionamos o elemento da direita
                combined[i] = right->next();
                rightIndex++;
            } else {
                //Caso nenhuma condição seja verdadeira, o elemento da direita é maior, então adiciona-se o elemento da esquerda
                combined[i] = left->next();
                leftIndex++;
            }
        }

        //Por fim, copiamos os valores ordenados para os elementos originais
        //Como o último elemento da esquerda aponta para o primeiro da direita, podemos tratar como uma lista contínua
        left->begin();
        for (int i = 0; i < left->size + right->size; i++) {
            left->next() = combined[i];
        }
    }

    //O(n log n)
    void mergeSort() {
        if (size > 1) {
            int middle = size / 2;
            List<T>* left = subList(0, middle);
            List<T>* right = subList(middle, size - middle);

            left->mergeSort();
            right->mergeSort();

            combine(left, right);
        }
    }

protected:
    int size;

public:
    List(int size = 0) : size(size) {}

    virtual void begin() = 0; //Inicializa um navegador para o início da lista
    virtual bool hasNext() = 0; //Verifica se existem mais elementos
    virtual T& next() = 0; //Obtém o valor na posição atual e avança o navegador
    virtual T& peek() = 0; //Obtém o valor na posição atual, mas não avança o navegador
    virtual bool insert(T value, int position) = 0;
    virtual bool remove(int position) = 0;
    virtual T& get(int position) = 0;
    virtual List<T>* subList(int begin, int length) = 0;

    bool append(T value) {
        return insert(value, size);
    }

    bool prepend(T value) {
        return insert(value, 0);
    }

    bool removeLast() {
        return remove(size - 1);
    }

    bool removeFirst() {
        return remove(0);
    }

    void sort(SortMode::Type mode = SortMode::Merge) {
        if (mode == SortMode::Bubble) {
            bubbleSort();
        } else if (mode == SortMode::Merge) {
            mergeSort();
        }
	}

    //O(n²)
    void shuffle() {
        begin();
        for (int i = 0; i < size - 1; i++) {
            int randomIndex = RandomNumberGenerator::generate(0, size - i - 1);
            T& current = next();
            T& random = get(i + randomIndex);
            std::swap(current, random);
        }
    }

    int getSize() {
        return size;
    }

    T& operator[](int position) {
        return get(position);
    }
};

template <class T>
std::ostream& operator<<(std::ostream& out, List<T>& list) {
    out << "{";
    list.begin();
    while (list.hasNext()) {
        out << list.next();

        if (list.hasNext()) {
			out << ", ";
		}
    }
    out << "}";
    return out;
}

#endif
