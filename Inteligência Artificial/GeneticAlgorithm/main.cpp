#include <iostream>
#include <cstdlib>
#include <ctime>
#include "algoritmo_genetico.h"
#include "util.h"
#include "leitor_tsp.h"
#include <chrono>
#include <cctype>

Instancia selecionarInstancia() {
    std::vector<Instancia> instancias = getInstancias();

    std::cout << "Instancias disponiveis:\n";
    for (const Instancia& instancia : instancias) {
        std::cout << instancia << "\n";
    }

    std::string nomeInstancia;
    std::cout << "Digite o nome da instancia desejada: \n";
    std::cin >> nomeInstancia;

    auto comparador = [&](const Instancia& a, const Instancia& b) {
        return levenshtein(a.nome, nomeInstancia) < levenshtein(b.nome, nomeInstancia);
    };

    auto it = std::min_element(instancias.begin(), instancias.end(), comparador);

    return *it;
}

double solicitarParametro(const std::string& nome) {
    double valor;
    std::cout << nome << ": ";
    std::cin >> valor;

    return valor;
}

void menu() {
    bool ativo = true;

    do {
        Instancia instancia = selecionarInstancia();
        std::cout << "Instancia selecionada: " << instancia.nome << ".\n\n";

        std::cout << "Parametros do Algoritmo Genetico\n";
        int populacao = solicitarParametro("Tamanho da populacao");
        double pressao = solicitarParametro("Pressao da selecao por torneio (0 a 1)");
        double cruzamento = solicitarParametro("Taxa de cruzamento (0 a 1)");
        double mutacao = solicitarParametro("Taxa de mutacao (0 a 1)");
        int geracoes = solicitarParametro("Numero de geracoes");


        std::vector<Ponto> cidades = lerTSP(instancia.arquivo);
        AlgoritmoGenetico ag(populacao, cidades, false);
        ag.definirParametros(pressao, cruzamento, mutacao);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < geracoes; i++) {
            ag.evoluir();

            const Individuo& melhor = ag.getMelhorIndividuo();

            double distancia = 1 / melhor.aptidao;
            std::cout << "(" << (i + 1) << "/" << geracoes << ") Distancia: " << distancia << " - ";
            std::cout << "Distancia do melhor (" << instancia.melhorSolucao << "): " << (distancia - instancia.melhorSolucao) << "\n";
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Segundos decorridos: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "\n";

        std::cout << "Deseja realizar outra execucao? [s/n]: ";
        char escolha;
        std::cin >> escolha;

        if (std::tolower(escolha) == 'n') {
            ativo = false;
        }
    } while (ativo);
}

int main() {
    std::srand(std::time(nullptr));

    menu();
    return 0;
}
