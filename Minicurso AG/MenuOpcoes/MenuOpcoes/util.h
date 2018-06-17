#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <vector>
#include <limits>
#include <string>

std::string paraString(const std::vector<int>& cromossomo) {
    std::string str = "";
    for (int v : cromossomo) {
        str.append(std::to_string(v));
    }
    return str;
}

double gerarAleatorio() {
    return std::rand() / static_cast<double>(RAND_MAX);
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
