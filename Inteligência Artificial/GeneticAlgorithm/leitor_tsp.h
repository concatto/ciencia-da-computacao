#ifndef LEITOR_TSP_H
#define LEITOR_TSP_H

#include "util.h"
#include <vector>
#include <fstream>
#include <string>
#include <regex>

struct Instancia {
    std::string nome;
    std::string arquivo;
    int cidades;
    double melhorSolucao;

    Instancia(const std::string& nome, const std::string& arquivo, int cidades, double melhorSolucao)
        : nome(nome), arquivo(arquivo), cidades(cidades), melhorSolucao(melhorSolucao) {

    }
};

std::ostream& operator<<(std::ostream& out, const Instancia& instancia) {
    out << instancia.nome << " (" << instancia.arquivo << "): " << instancia.cidades << " cidades; melhor solucao conhecida: " << instancia.melhorSolucao;
    return out;
}


Ponto processarLinha(const std::string& linha) {
    std::regex padrao("\\d+\\s(.+)\\s(.+\\d).*");
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
        if (linha[linha.size() - 1] == '\r') {
            linha.pop_back();
        }

        if (linha.find("EOF") == 0) {
            break;
        } else if (secaoCoordenadas) {
            pontos.push_back(processarLinha(linha));
        } else if (linha.find("NODE_COORD_SECTION") == 0) {
            secaoCoordenadas = true;
        }
    }
    std::cout << "Cidades lidas: " << pontos.size() << "\n";

    return pontos;
}

std::vector<Instancia> getInstancias() {
    return {
        {"Djibouti", "dj38.tsp", 38, 6656},
        {"Qatar", "qa194.tsp", 194, 9352},
        {"Uruguay", "uy734.tsp", 734, 79114},
        {"Zimbabwe", "zi929.tsp", 929, 95345},
        {"Oman", "mu1979.tsp", 1979, 86891},
        {"Canada", "ca4663.tsp", 4663, 1290319},
        {"Italy", "it16862.tsp", 16862, 557315}
    };
}

#endif // LEITOR_TSP_H
