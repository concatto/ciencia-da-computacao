#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <vector>
#include <limits>

double gerarAleatorio() {
    return std::rand() / static_cast<double>(RAND_MAX);
}

int paraDecimal(const std::vector<int> binario, int inicio, int fim) {
    int total = 0;
    for (int i = inicio; i < fim; i++) {
        int deslocamento = binario.size() - i - 1;
        total = total | (binario[i] << deslocamento);
    }

    return total;
}

int paraDecimal(const std::vector<int> binario) {
    return paraDecimal(binario, 0, binario.size());
}

template <class T>
T infinito(bool positivo) {
    T valor = std::numeric_limits<T>::max();

    if (positivo) {
        return valor;
    } else {
        return -valor;
    }
}

int infinitoInt(bool positivo = true) {
    return infinito<int>(positivo);
}

double infinitoDouble(bool positivo = true) {
    return infinito<double>(positivo);
}



#endif // UTIL_H
