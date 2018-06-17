#ifndef LEITOR_TSP_H
#define LEITOR_TSP_H

#include "util.h"
#include <vector>
#include <fstream>
#include <string>
#include <regex>


std::vector<std::string> processarLinha(const std::string& linha) {
    std::vector<std::string> resultado;

    std::string pedaco;
    std::istringstream stream(linha);

    while (std::getline(stream, pedaco, ',')) {
        if (!pedaco.empty()) {
            resultado.push_back(pedaco);
        }
    }

    return resultado;
}

// Linha 1: custo máximo
// Linhas 2 a n: nome, importância, custo
std::vector<std::vector<std::string>> lerInstancia(const std::string& caminho) {
    std::ifstream stream(caminho);

    std::string linha;
    std::vector<std::vector<std::string>> dados;

    while (std::getline(stream, linha)) {
        if (linha.size() > 0 && linha[linha.size() - 1] == '\r') {
            linha.pop_back();
        }

        dados.push_back(processarLinha(linha));
    }

    return dados;
}

#endif // LEITOR_TSP_H
