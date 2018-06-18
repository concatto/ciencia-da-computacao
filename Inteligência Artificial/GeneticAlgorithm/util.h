#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <vector>
#include <limits>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_set>

struct Ponto {
    double x;
    double y;

    Ponto(double x, double y) : x(x), y(y) {}
};

std::ostream& operator<<(std::ostream& out, const Ponto& ponto) {
    out << "(" << ponto.x << ", " << ponto.y << ")";

    return out;
}

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

double distanciaEuclidiana(const Ponto& a, const Ponto& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return std::sqrt(dx * dx + dy * dy);
}

double gerarAleatorio() {
    return std::rand() / static_cast<double>(RAND_MAX);
}

int paraDecimal(const std::vector<int>& binario, int inicio, int fim) {
    int total = 0;
    for (int i = inicio; i < fim; i++) {
        int deslocamento = fim - i - 1;
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

template <class T>
bool contem(const T& valor, const std::vector<T>& lista) {
    return std::find(lista.begin(), lista.end(), valor) != lista.end();
}

template <class T>
bool contem(const T& valor, const std::unordered_set<T>& lista) {
    return std::find(lista.begin(), lista.end(), valor) != lista.end();
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
    int l = binario.size() / segmentos;
    for (int i = 0; i < segmentos; i++) {
        int inicio = i * l;
        resultado.push_back(paraDecimal(binario, inicio, inicio + l));
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

std::vector<int> conjuntoOrdenadoAleatorio(int n) {
    std::vector<int> conjunto;

    for (int i = 0; i < n; i++) {
        conjunto.push_back(i);
    }

    std::random_shuffle(conjunto.begin(), conjunto.end());

    return conjunto;
}

template <class T>
int buscarIndice(const T& valor, const std::vector<T>& lista) {
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i] == valor) {
            return i;
        }
    }

    return -1;
}

// Fonte: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++
unsigned int levenshtein(const std::string& s1, const std::string& s2) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for(unsigned int i = 1; i <= len1; ++i)
        for(unsigned int j = 1; j <= len2; ++j)
            // note that std::min({arg1, arg2, arg3}) works only in C++11,
            // for C++98 use std::min(std::min(arg1, arg2), arg3)
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
    return d[len1][len2];
}

#endif // UTIL_H
