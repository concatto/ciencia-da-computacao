#include <iostream>
#include <vector>
#include <cmath>
#include "leitor.h"
#include "util.h"

// Obtém o n-ésimo bit do valor, onde a posição 0 representa o bit menos significativo.
int obterBit(int valor, int posicao) {
    return (valor >> posicao) & 1;
}

// Converte um número em string para double.
double paraReal(const std::string& texto) {
    return std::stod(texto);
}



/**
 * Este struct consiste em uma instância do Problema do Menu
 * de Opções, contendo os nomes, importâncias e custos de cada opção,
 * alinhados em seus índices. A struct também conta com o valor
 * de custo máximo, a partir do qual a solução se torna inadmissível.
 */
struct Instancia {
    std::vector<std::string> nomes;
    std::vector<double> importancias;
    std::vector<double> custos;

    double custoMaximo;
};

/**
 * Este struct representa uma solução individual do problema,
 * através da qual deve ser possível demonstrar como o problema é
 * resolvido e designar um nível de qualidade.
 */
struct Solucao {
    // Como representar quais opções estão em "máximo" e quais não estão?
};

/**
 * Esta é a função de aptidão, que determina a qualidade da solução.
 * As informações contidas na instância do problema devem ser utilizadas
 * em conjunto com a solução recebida para que seja possível atribuir a qualidade.
 */
double avaliar(const Solucao& solucao, const Instancia& problema) {
    // Como dizer se a solução é boa ou ruim?
    // Lembre-se de verificar se o custo total não é alto demais!
    return 0;
}

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

Instancia carregarInstancia() {
    std::vector<std::vector<std::string>> dados = lerInstancia("instancia20.csv");

    Instancia problema;
    problema.custoMaximo = paraReal(dados[0][0]);

    for (int i = 1; i < dados.size(); i++) {
        std::string nome = dados[i][0];
        double importancia = paraReal(dados[i][1]);
        double custo = paraReal(dados[i][2]);

        adicionarOpcao(problema, nome, importancia, custo);
    }

    return problema;
}

int main() {
    std::srand(std::time(nullptr));

    Instancia problema;

    adicionarOpcao(problema, "Resolucao da tela", 10, 12);
    adicionarOpcao(problema, "Resolucao das texturas", 8, 6);
    adicionarOpcao(problema, "Qualidade da iluminacao", 7, 3);
    adicionarOpcao(problema, "Qualidade das sombras", 6, 9);
    adicionarOpcao(problema, "Anti-aliasing", 3, 7);
    problema.custoMaximo = 20;



    Solucao solucao;
    // Após construir a struct, represente a melhor solução possível:
    // Texturas, iluminação e sombra no máximo.



    double qualidade = avaliar(solucao, problema);

    std::cout << "A qualidade da solucao é igual a: " << qualidade << "\n";

    return 0;
}
