#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "util.h"
#include "circulos.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

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
    sf::Image referencia;
    bool debug;
    std::vector<Individuo> populacao;
    double taxaCruzamento = 0.7;
    double taxaMutacao = 0.0009;

public:
    AlgoritmoGenetico(int tamanhoPopulacao, int comprimentoCromossomo, bool debug = false) : debug(debug) {
        std::cout << referencia.loadFromFile("LIA_LEDS.png");

        gerarPopulacaoInicial(tamanhoPopulacao, comprimentoCromossomo);
    }

    void gerarPopulacaoInicial(int tamanhoPopulacao, int comprimento) {
        for (int i = 0; i < tamanhoPopulacao; i++) {
            Individuo individuo;

            individuo.cromossomo = cromossomoAleatorio(comprimento);
            individuo.aptidao = avaliarIndividuo(individuo);
            populacao.push_back(individuo);

            std::cout << i << ": " << individuo.aptidao << "\n";
        }
    }

    const Individuo& getMelhorIndividuo() {
        int melhor = 0;
        for (int i = 1; i < populacao.size(); i++) {
            if (populacao[i].aptidao > populacao[melhor].aptidao) {
                melhor = i;
            }
        }

        return populacao[melhor];
    }

    const std::vector<Individuo>& getPopulacao() {
        return populacao;
    }

    /**
     * Realiza a execução de uma geração do algoritmo genético,
     * gerando uma nova população a partir dos operadores.
     */
    void evoluir() {
        std::vector<Individuo> novaPopulacao;

        Individuo melhor = getMelhorIndividuo();

        while (novaPopulacao.size() < populacao.size()) {
            if (debug) std::cout << "Selecionando...\n";
            std::vector<int> pais = selecionar();
            if (debug) std::cout << "Cruzando...\n";
            std::vector<Individuo> filhos = aplicarCruzamento(populacao[pais[0]], populacao[pais[1]]);

            if (debug) std::cout << "Mutando...\n";
            aplicarMutacao(filhos[0]);
            aplicarMutacao(filhos[1]);

            if (debug) std::cout << "Avaliando...\n";
            filhos[0].aptidao = avaliarIndividuo(filhos[0]);
            filhos[1].aptidao = avaliarIndividuo(filhos[1]);

            if (debug) {
                std::cout << "Filhos gerados com aptidão " << filhos[0].aptidao << " e " << filhos[1].aptidao << "\n";
            }

            novaPopulacao.push_back(filhos[0]);
            novaPopulacao.push_back(filhos[1]);
        }

        int pos = gerarAleatorio() * novaPopulacao.size();
        novaPopulacao[pos] = melhor;

        populacao = novaPopulacao;
    }

    double avaliarIndividuo(const Individuo& individuo) {
        sf::RenderTexture textura;

        textura.clear();
        gerarTextura(textura, individuo.cromossomo, 100, 203, 200);

        return 1 / computarDiferenca(textura.getTexture().copyToImage(), referencia);
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
            if (gerarAleatorio() < (taxaMutacao)) {
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
     * apenas dois elementos (os índices).
     */
    std::vector<int> selecionar() {
        double pressao = 0.85;

        int primeiro = executarTorneio(pressao);
        int segundo;

        do {
            segundo = executarTorneio(pressao);
        } while (primeiro == segundo);

        std::vector<int> resultado;

        resultado.push_back(primeiro);
        resultado.push_back(segundo);

        return resultado;
    }

    int executarRoleta() {
        double aptidaoTotal = 0;
        for (const Individuo& individuo : populacao) {
            aptidaoTotal += individuo.aptidao;
        }

        double valor = gerarAleatorio() * aptidaoTotal;
        double soma = 0;
        for (int i = 0; i < populacao.size(); i++) {
            // Se fosse passar do ponto escolhido, retornar o índice atual.
            if (soma + populacao[i].aptidao >= valor) {
                return i;
            }

            soma += populacao[i].aptidao;
        }
    }

    int executarTorneio(double pressao) {
        int a = gerarAleatorio() * populacao.size();
        int b = gerarAleatorio() * populacao.size();

        const Individuo& individuoA = populacao[a];
        const Individuo& individuoB = populacao[b];

        if (individuoB.aptidao > individuoA.aptidao) {
            std::swap(a, b);
        }

        if (gerarAleatorio() < pressao) {
            return a;
        } else {
            return b;
        }
    }

    /**
     * Efetua o cruzamento entre dois indivíduos, produzindo
     * dois novos indivíduos (contidos no vector retornado).
     * Caso o cruzamento falhe, os próprios indivíduos serão
     * retornados, inalterados.
     */
//    std::vector<Individuo> aplicarCruzamento(const Individuo& a, const Individuo& b) {
//        std::vector<Individuo> resultado;

//        if (gerarAleatorio() < taxaCruzamento) {
//            int comprimento = a.cromossomo.size();

//            // Converter (arredondando para baixo) o produto entre um número
//            // aleatório, de 0 a 1, e o comprimento do cromossomo.
//            int corte = static_cast<int>(gerarAleatorio() * comprimento);

//            Individuo filhoA;
//            Individuo filhoB;

//            for (int i = 0; i < comprimento; i++) {
//                if (i < corte) {
//                    // Abaixo do corte: recebe do pai contrário
//                    filhoA.cromossomo.push_back(b.cromossomo[i]);
//                    filhoB.cromossomo.push_back(a.cromossomo[i]);
//                } else {
//                    // Acima do corte: recebe do mesmo pai
//                    filhoA.cromossomo.push_back(a.cromossomo[i]);
//                    filhoB.cromossomo.push_back(b.cromossomo[i]);
//                }
//            }

//            resultado.push_back(filhoA);
//            resultado.push_back(filhoB);
//        } else {
//            resultado.push_back(a);
//            resultado.push_back(b);
//        }

//        return resultado;
//    }


    // Uniforme
    std::vector<Individuo> aplicarCruzamento(const Individuo& a, const Individuo& b) {
        std::vector<Individuo> resultado;

        if (gerarAleatorio() < taxaCruzamento) {
            int comprimento = a.cromossomo.size();

            // Converter (arredondando para baixo) o produto entre um número
            // aleatório, de 0 a 1, e o comprimento do cromossomo.
            int corte = static_cast<int>(gerarAleatorio() * comprimento);

            Individuo filhoA;
            Individuo filhoB;

            std::vector<int> mascara = cromossomoAleatorio(comprimento);
            for (int i = 0; i < comprimento; i++) {
                if (mascara[i] == 0) {
                    // Abaixo do corte: recebe do pai contrário
                    filhoA.cromossomo.push_back(b.cromossomo[i]);
                    filhoB.cromossomo.push_back(a.cromossomo[i]);
                } else {
                    // Acima do corte: recebe do mesmo pai
                    filhoA.cromossomo.push_back(a.cromossomo[i]);
                    filhoB.cromossomo.push_back(b.cromossomo[i]);
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
