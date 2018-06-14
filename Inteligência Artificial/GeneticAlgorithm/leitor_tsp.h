#ifndef LEITOR_TSP_H
#define LEITOR_TSP_H

#include "util.h"
#include <vector>
#include <fstream>
#include <string>
#include <regex>


Ponto processarLinha(const std::string& linha) {
    std::regex padrao("\\d+\\s(.+)\\s(.+)");
    std::smatch match;

    if (std::regex_match(linha, match, padrao)) {
        std::string x = match[1].str();
        std::string y = match[2].str();

        return Ponto(std::stod(x), std::stod(y));
    }

    return Ponto(0, 0);
}

std::vector<Ponto> lerTSP(const std::string& caminho) {
    std::ifstream stream(caminho);

    std::cout << stream.is_open() << "\n";

    std::string linha;
    std::vector<Ponto> pontos;
    bool secaoCoordenadas = false;
    while (std::getline(stream, linha)) {
        std::cout << linha << "\n";
        if (secaoCoordenadas && linha != "EOF") {
            pontos.push_back(processarLinha(linha));

            std::cout << pontos.back() << "\n";
        } else if (linha == "NODE_COORD_SECTION") {
            secaoCoordenadas = true;
        }
    }

    return pontos;
}

#endif // LEITOR_TSP_H
