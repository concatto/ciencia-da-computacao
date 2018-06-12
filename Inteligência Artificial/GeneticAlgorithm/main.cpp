#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "algoritmo_genetico.h"
#include "util.h"
#include "circulos.h"

void desenharIndividuo(const Individuo& individuo, sf::RenderWindow& janela, int segmentos) {
    sf::Vector2u tamanho = janela.getSize();

    sf::RenderTexture textura;

    textura.clear();
    gerarTextura(textura, individuo.cromossomo, segmentos, tamanho.x, tamanho.y);

    janela.draw(sf::Sprite(textura.getTexture()));
}

int main() {    
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(203, 200), "Hello SFML");

    AlgoritmoGenetico ag(60, 8000, false);

    for (int i = 0; i <= 500; i++) {
        window.clear();
        std::cout << "Starting generation " << i << "\n";
        ag.evoluir();

        const Individuo& melhor = ag.getMelhorIndividuo();
        std::cout << "Melhor distância: " << (1 / melhor.aptidao) << "\n";

        desenharIndividuo(melhor, window, 100);

        window.display();
    }

    return 0;
}
