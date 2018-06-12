#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <vector>
#include <limits>
#include <string>

struct Limitador {
    double min;
    double max;

    Limitador(double min, double max) : min(min), max(max) {}

    double aplicar(double valor, double novoMin, double novoMax) {
        return (valor - min) * (novoMax - novoMin) / (max - min) + novoMin;
    }
};

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

int paraDecimal(const std::vector<int>& binario, int inicio, int fim) {
    int total = 0;
    for (int i = inicio; i < fim; i++) {
        int deslocamento = binario.size() - i - 1;
        total = total | (binario[i] << deslocamento);
    }

    return total;
}

int paraDecimal(const std::vector<int>& binario) {
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

std::vector<std::vector<int>> segmentar(const std::vector<int>& binario, int segmentos) {
    std::vector<std::vector<int>> resultado;
    int tamanhoSegmento = binario.size() / segmentos;

    for (int i = 0; i < segmentos; i++) {
        std::vector<int> segmento;
        int inicio = i * tamanhoSegmento;

        for (int j = 0; j < tamanhoSegmento; j++) {
            segmento.push_back(binario[inicio + j]);
        }

        resultado.push_back(segmento);
    }

    return resultado;
}

std::vector<int> segmentarDecimal(const std::vector<int>& binario, int segmentos) {
    std::vector<int> resultado;

    for (const std::vector<int>& segmento : segmentar(binario, segmentos)) {
        resultado.push_back(paraDecimal(segmento));
    }

    return resultado;
}

std::vector<int> cromossomoAleatorio(int comprimento) {
    std::vector<int> cromossomo;

    for (int i = 0; i < comprimento; i++) {
        int valor;

        if (gerarAleatorio() < 0.5) {
            valor = 0;
        } else {
            valor = 1;
        }

        cromossomo.push_back(valor);
    }

    return cromossomo;
}

#endif // UTIL_H
