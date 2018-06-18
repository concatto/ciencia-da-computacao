#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "util.h"
#include <vector>
#include <cmath>
#include <cstdlib>

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
    bool debug;
    std::vector<Ponto> cidades;
    std::vector<Individuo> populacao;
    double taxaCruzamento = 0.9;
    double taxaMutacao = 0.01;

public:
    AlgoritmoGenetico(int tamanhoPopulacao, const std::vector<Ponto>& cidades, bool debug = false) : debug(debug) {
        this->cidades = cidades;
        gerarPopulacaoInicial(tamanhoPopulacao);
    }

    void gerarPopulacaoInicial(int tamanhoPopulacao) {
        for (int i = 0; i < tamanhoPopulacao; i++) {
            Individuo individuo;

            individuo.cromossomo = conjuntoOrdenadoAleatorio(cidades.size());
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

        // Elitismo
        int pos = gerarAleatorio() * novaPopulacao.size();
        novaPopulacao[pos] = melhor;

        populacao = novaPopulacao;
    }

    double avaliarIndividuo(const Individuo& individuo) {
        double soma = 0;
        const std::vector<int>& cromossomo = individuo.cromossomo;

        for (int i = 0; i < cromossomo.size(); i++) {
            int destino = i + 1;

            if (destino == cromossomo.size()) {
                destino = 0;
            }

            int a = cromossomo[i];
            int b = cromossomo[destino];

            double dist = distanciaEuclidiana(cidades[a], cidades[b]);

            soma += dist;
        }

        return 1 / soma;
    }

    /**
     * Aplica o operador de mutação no indivíduo com
     * chance r, onde r é dado pela taxa de mutação.
     */
    void aplicarMutacao(Individuo& individuo) {
        if (gerarAleatorio() < (taxaMutacao)) {
            int a = gerarAleatorio() * individuo.cromossomo.size();
            int b = gerarAleatorio() * individuo.cromossomo.size();

            std::swap(individuo.cromossomo[a], individuo.cromossomo[b]);
        }
    }

    /**
     * Realiza a seleção de dois indivíduos da população,
     * onde a chance de seleção é proporcional à aptidão
     * do indivíduo. O vector retornado sempre conterá
     * apenas dois elementos (os índices).
     */
    std::vector<int> selecionar() {
        double pressao = 0.8;

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
    std::vector<Individuo> aplicarCruzamento(const Individuo& a, const Individuo& b) {
        std::vector<Individuo> resultado;

        if (gerarAleatorio() < taxaCruzamento) {
            resultado.push_back(pmx(a, b));
            resultado.push_back(pmx(b, a));
        } else {
            resultado.push_back(a);
            resultado.push_back(b);
        }

        return resultado;
    }

    Individuo pmx(const Individuo& a, const Individuo& b) {
        Individuo filho;

        // Iniciamos com uma cópia do cromossomo de B
        filho.cromossomo = b.cromossomo;

        int inicio = gerarAleatorio() * filho.cromossomo.size();
        int fim = gerarAleatorio() * filho.cromossomo.size();

        if (inicio > fim) {
            std::swap(inicio, fim);
        }

        std::vector<int> trecho;
        // Copiar os valores do trecho de A para o filho
        for (int i = inicio; i < fim; i++) {
            filho.cromossomo[i] = a.cromossomo[i];

            trecho.push_back(a.cromossomo[i]);
        }

        for (int i = inicio; i < fim; i++) {
            int valorB = b.cromossomo[i];

            if (!contem(valorB, trecho)) {
                int indiceA = i;
                bool finalizado = false;
                do {
                    int valorA = a.cromossomo[indiceA];

                    indiceA = buscarIndice(valorA, b.cromossomo);
                    if (indiceA < inicio || indiceA >= fim) {
                        finalizado = true;
                    }
                } while (!finalizado);

                filho.cromossomo[indiceA] = valorB;
            }
        }

        return filho;
    }
};

#endif // ALGORITMO_GENETICO_H
