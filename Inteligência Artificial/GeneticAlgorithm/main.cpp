#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "algoritmo_genetico.h"
#include "util.h"

int main() {    
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");

    while (true) {
        window.clear();
        window.display();
    }

    AlgoritmoGenetico ag(100, 28, false);

    std::cout << "População inicial:\n";
    for (const Individuo& individuo : ag.getPopulacao()) {
        std::cout << paraDecimal(individuo.cromossomo) << "\n";
    }

    for (int i = 0; i <= 1000; i++) {
        ag.evoluir();

        if (i % 10 == 0) {
            const Individuo& melhor = ag.getMelhorIndividuo();
            std::cout << i << " = " << paraDecimal(melhor.cromossomo) << "; " << melhor.aptidao << "\n";
        }

    }




    return 0;
}
