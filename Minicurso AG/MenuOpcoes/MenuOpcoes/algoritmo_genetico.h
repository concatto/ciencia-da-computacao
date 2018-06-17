#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "util.h"
#include <vector>
#include <cmath>
#include <cstdlib>

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
    std::vector<int> bits;
    double aptidao;
};


/**
 * Esta classe implementa todas as funções essenciais
 * para o funcionamento de um algoritmo genético.
 */
class AlgoritmoGenetico {
private:
    Instancia problema;
    std::vector<Solucao> populacao;

public:
    AlgoritmoGenetico(const Instancia& instancia) : problema(instancia) {
        // Apenas para inicializar a instância
    }

    /**
     * Esta é a função de aptidão, que determina a qualidade da solução.
     * As informações contidas na instância do problema devem ser utilizadas
     * em conjunto com a solução recebida para que seja possível atribuir a qualidade.
     */
    double avaliar(const Solucao& solucao) {
        double custoTotal = 0;
        double qualidade = 0;

        for (int i = 0; i < solucao.bits.size(); i++) {
            if (solucao.bits[i] == 1) {
                custoTotal += problema.custos[i];
                qualidade += problema.importancias[i];
            }
        }

        if (custoTotal > problema.custoMaximo) {
            return problema.custoMaximo - custoTotal;
        }

        return qualidade;
    }

    /**
     * Cria uma população inicial aleatória como ponto
     * de partida para o algoritmo genético.
     */
    void gerarPopulacaoInicial(int tamanhoPopulacao) {
        for (int i = 0; i < tamanhoPopulacao; i++) {
            Solucao individuo;

            for (int j = 0; j < problema.importancias.size(); j++) {
                individuo.bits.push_back(std::rand() % 2);
            }

            individuo.aptidao = avaliar(individuo);
            populacao.push_back(individuo);
        }
    }

    /**
     * Recupera o indivíduo com maior aptidão de toda
     * a população atual (somente leitura).
     */
    const Solucao& getMelhorIndividuo() {
        int melhor = 0;
        for (int i = 1; i < populacao.size(); i++) {
            if (populacao[i].aptidao > populacao[melhor].aptidao) {
                melhor = i;
            }
        }

        return populacao[melhor];
    }

    /**
     * Realiza a execução de uma geração do algoritmo genético,
     * gerando uma nova população a partir dos operadores.
     */
    void evoluir() {
        std::vector<Solucao> novaPopulacao;

        while (novaPopulacao.size() < populacao.size()) {
            std::vector<int> pais = selecionar();

            std::vector<Solucao> filhos = aplicarCruzamento(populacao[pais[0]], populacao[pais[1]]);

            aplicarMutacao(filhos[0]);
            aplicarMutacao(filhos[1]);

            filhos[0].aptidao = avaliar(filhos[0]);
            filhos[1].aptidao = avaliar(filhos[1]);

            novaPopulacao.push_back(filhos[0]);
            novaPopulacao.push_back(filhos[1]);
        }

        int indice = std::rand() % novaPopulacao.size();
        novaPopulacao[indice] = getMelhorIndividuo();

        populacao = novaPopulacao;
    }

    /**
     * Tenta causar uma mutação em cada um dos genes do
     * indivíduo, com chance de sucesso dada pela taxa de
     * mutação. Caso consiga, deve inverter o valor do gene.
     */
    void aplicarMutacao(Solucao& individuo) {
        for (int i = 0; i < individuo.bits.size(); i++) {
            if (gerarAleatorio() < 0.01) {
                if (individuo.bits[i] == 0) {
                    individuo.bits[i] = 1;
                } else {
                    individuo.bits[i] = 0;
                }
            }
        }
    }

    /**
     * Realiza a seleção de dois indivíduos da população,
     * onde a chance de seleção é proporcional à aptidão
     * do indivíduo. O vector retornado sempre conterá
     * apenas dois elementos (os índices).
     */
    std::vector<int> selecionar() {
        std::vector<int> resultado;

        double p = 0.8;

        int a = torneio(p);
        int b;

        do {
            b = torneio(p);
        } while (a == b);

        resultado.push_back(a);
        resultado.push_back(b);

        return resultado;
    }

    int torneio(double p) {
        int a = std::rand() % populacao.size();
        int b = std::rand() % populacao.size();

        if (gerarAleatorio() < p) {
            // Retornar o mais forte
            if (populacao[a].aptidao > populacao[b].aptidao) {
                return a;
            } else {
                return b;
            }
        } else {
            // Retornar o mais fraco
            if (populacao[a].aptidao > populacao[b].aptidao) {
                return b;
            } else {
                return a;
            }
        }
    }

    /**
     * Efetua o cruzamento entre dois indivíduos, produzindo
     * dois novos indivíduos (contidos no vector retornado).
     * Caso o cruzamento falhe, os próprios indivíduos serão
     * retornados, inalterados.
     */
    std::vector<Solucao> aplicarCruzamento(const Solucao& a, const Solucao& b) {
        std::vector<Solucao> resultado;

        Solucao filhoA = a;
        Solucao filhoB = b;

        double chance = 0.9;

        if (gerarAleatorio() < chance) {
            int ponto = std::rand() % a.bits.size();

            for (int i = 0; i < ponto; i++) {
//              int alelo = filhoA.bits[i];
//              filhoA.bits[i] = filhoB.bits[i];
//              filhoB.bits[i] = alelo;

                std::swap(filhoA.bits[i], filhoB.bits[i]);
            }
        }

        resultado.push_back(filhoA);
        resultado.push_back(filhoB);

        return resultado;
    }
};

#endif // ALGORITMO_GENETICO_H
