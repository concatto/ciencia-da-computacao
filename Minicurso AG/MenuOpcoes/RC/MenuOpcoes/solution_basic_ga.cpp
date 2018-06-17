#include <iostream>
#include <vector>
#include <cmath>
#include "leitor.h"
#include "util.h"
#include "algoritmo_genetico.h"

void adicionarOpcao(Instancia& instancia, const std::string& nome, double importancia, double custo) {
    instancia.nomes.push_back(nome);
    instancia.importancias.push_back(importancia);
    instancia.custos.push_back(custo);
}

void imprimirOpcao(const Instancia& instancia, int indice) {
    std::cout << "Nome: " << instancia.nomes[indice] << "; ";
    std::cout << "Importancia: " << instancia.importancias[indice] << "; ";
    std::cout << "Custo: " << instancia.custos[indice] << "\n";
}

int main() {
    Instancia problema;

    adicionarOpcao(problema, "Resolucao da tela", 10, 12);
    adicionarOpcao(problema, "Resolucao das texturas", 8, 6);
    adicionarOpcao(problema, "Qualidade da iluminacao", 7, 3);
    adicionarOpcao(problema, "Qualidade das sombras", 6, 9);
    adicionarOpcao(problema, "Anti-aliasing", 3, 7);
    problema.custoMaximo = 20;

    AlgoritmoGenetico ag(problema);
    ag.gerarPopulacaoInicial(100);

    for (int i = 0; i < 200; i++) {
        ag.evoluir();

        Solucao melhor = ag.getMelhorIndividuo();

        std::cout << "Melhor solucao encontrada tem qualidade " << melhor.aptidao << "\n";
    }

    return 0;
}
