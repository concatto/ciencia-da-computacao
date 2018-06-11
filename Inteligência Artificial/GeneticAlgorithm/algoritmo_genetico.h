#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "util.h"
#include <vector>

/**
 * Este struct representa um indivíduo da população,
 * possuindo um cromossomo representado como uma sequência
 * de inteiros e um valor real de aptidão.
 */
struct Individuo {
    std::vector<int> cromossomo;
    double aptidao = 0;
};


/**
 * Esta classe implementa todas as funções essenciais
 * para o funcionamento de um algoritmo genético.
 */
class AlgoritmoGenetico {
private:
    std::vector<Individuo> populacao;
    double taxaCruzamento = 0.7;
    double taxaMutacao = 0.1;

public:
    AlgoritmoGenetico(int tamanhoPopulacao, int comprimentoCromossomo) {
        gerarPopulacaoInicial(tamanhoPopulacao, comprimentoCromossomo);
    }

    void gerarPopulacaoInicial(int tamanhoPopulacao, int comprimento) {
        for (int i = 0; i < tamanhoPopulacao; i++) {
            Individuo individuo;

            for (int j = 0; j < comprimento; j++) {
                int valor;

                if (aleatorio() < 0.5) {
                    valor = 0;
                } else {
                    valor = 1;
                }

                individuo.cromossomo.push_back(valor);
            }

            populacao.push_back(individuo);
        }
    }

    /**
     * Realiza a execução de uma geração do algoritmo genético,
     * gerando uma nova população a partir dos operadores.
     */
    void evoluir() {

    }

    double avaliarIndividuo(const Individuo& individuo) {
        return 0;
    }

    /**
     * Aplica o operador de mutação em cada um dos genes do
     * indivíduo com chance r/k, onde r é dado pela taxa de
     * mutação e k representa o comprimento do cromossomo.
     */
    void aplicarMutacao(Individuo& individuo) {
        int k = individuo.cromossomo.size();
        for (int i = 0; i < k; i++) {
            // Verificar se este gene sofrerá mutação
            if (aleatorio() < (taxaMutacao / k)) {
                // Substituir pelo valor contrário
                if (individuo.cromossomo[i] == 0) {
                    individuo.cromossomo[i] = 1;
                } else {
                    individuo.cromossomo[i] = 0;
                }

            }
        }
    }

    /**
     * Realiza a seleção de dois indivíduos da população,
     * onde a chance de seleção é proporcional à aptidão
     * do indivíduo. O vector retornado sempre conterá
     * apenas dois elementos.
     */
    std::vector<Individuo> selecionar() {

    }

    /**
     * Efetua o cruzamento entre dois indivíduos, produzindo
     * dois novos indivíduos (contidos no vector retornado).
     * Caso o cruzamento falhe, os próprios indivíduos serão
     * retornados, inalterados.
     */
    std::vector<Individuo> aplicarCruzamento(const Individuo& a, const Individuo& b) {
        std::vector<Individuo> resultado;

        if (aleatorio() < taxaCruzamento) {
            int comprimento = a.cromossomo.size();

            // Converter (arredondando para baixo) o produto entre um número
            // aleatório, de 0 a 1, e o comprimento do cromossomo.
            int corte = static_cast<int>(aleatorio() * comprimento);

            Individuo filhoA;
            Individuo filhoB;

            for (int i = 0; i < comprimento; i++) {
                if (i < corte) {
                    // Abaixo do corte: recebe do pai contrário
                    filhoA.cromossomo[i] = b.cromossomo[i];
                    filhoB.cromossomo[i] = a.cromossomo[i];
                } else {
                    // Acima do corte: recebe do mesmo pai
                    filhoA.cromossomo[i] = a.cromossomo[i];
                    filhoB.cromossomo[i] = b.cromossomo[i];
                }
            }

            resultado.push_back(filhoA);
            resultado.push_back(filhoB);
        } else {
            resultado.push_back(a);
            resultado.push_back(b);
        }

        return resultado;
    }
};

#endif // ALGORITMO_GENETICO_H
