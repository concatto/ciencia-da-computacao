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

void buscaExaustiva() {
    std::vector<std::vector<std::string>> dados = lerInstancia("instancia100.csv");

    Instancia problema;
    problema.custoMaximo = paraReal(dados[0][0]);

    for (int i = 1; i < dados.size(); i++) {
        std::string nome = dados[i][0];
        double importancia = paraReal(dados[i][1]);
        double custo = paraReal(dados[i][2]);

        adicionarOpcao(problema, nome, importancia, custo);
    }

    AlgoritmoGenetico ag(problema);

    int bits = problema.nomes.size();

    Solucao melhor;
    double melhorQualidade = 0;

    int total = std::pow(2, std::min(bits, 30));
    for (int i = 0; i < total; i++) {
        Solucao solucao;

        for (int j = 0; j < bits; j++) {
            solucao.bits.push_back(obterBit(i, j));
        }

        double qualidade = ag.avaliar(solucao);

        if (qualidade > melhorQualidade) {
            melhorQualidade = qualidade;
            melhor = solucao;
        }

        std::cout << i << "/" << total << " => " << melhorQualidade << "\n";
        //std::cout << "A qualidade da solucao é igual a: " << qualidade << "\n";
    }

    std::cout << "Melhor solucao encontrada tem qualidade " << melhorQualidade << "\n";
    std::cout << "Opcoes no maximo:\n";
    for (int i = 0; i < bits; i++) {
        if (melhor.bits[i] == 1) {
            imprimirOpcao(problema, i);
        }
    }
}


int main() {
    std::srand(std::time(nullptr));

    std::vector<std::vector<std::string>> dados = lerInstancia("instancia60.csv");

    Instancia problema;
    problema.custoMaximo = paraReal(dados[0][0]);

    for (int i = 1; i < dados.size(); i++) {
        std::string nome = dados[i][0];
        double importancia = paraReal(dados[i][1]);
        double custo = paraReal(dados[i][2]);

        adicionarOpcao(problema, nome, importancia, custo);
    }


//    adicionarOpcao(problema, "Resolucao da tela", 10, 12);
//    adicionarOpcao(problema, "Resolucao das texturas", 8, 6);
//    adicionarOpcao(problema, "Qualidade da iluminacao", 7, 3);
//    adicionarOpcao(problema, "Qualidade das sombras", 6, 9);
//    adicionarOpcao(problema, "Anti-aliasing", 3, 7);
//    problema.custoMaximo = 20;

    AlgoritmoGenetico ag(problema);
    ag.gerarPopulacaoInicial(1000);

    for (int i = 0; i < 100000; i++) {
        ag.evoluir();

        Solucao melhor = ag.getMelhorIndividuo();

        std::cout << "Melhor solucao encontrada tem qualidade " << melhor.aptidao << "\n";
    }

    return 0;
}
