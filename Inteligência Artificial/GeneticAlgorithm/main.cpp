#include <iostream>
#include <cstdlib>
#include <ctime>
#include "algoritmo_genetico.h"
#include "util.h"
#include "leitor_tsp.h"
#include <chrono>

int main() {
    std::srand(std::time(nullptr));

    std::vector<Ponto> cidades = lerTSP("test.tsp");
    AlgoritmoGenetico ag(100, cidades, false);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i <= 100000; i++) {
        std::cout << "Starting generation " << i << "\n";
        ag.evoluir();

        const Individuo& melhor = ag.getMelhorIndividuo();

        std::cout << "Distancia: " << (1 / melhor.aptidao) << "\n";
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "\n";

    return 0;
}
