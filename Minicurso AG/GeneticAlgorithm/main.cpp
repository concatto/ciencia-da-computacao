#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "algoritmo_genetico.h"
#include "util.h"
#include "circulos.h"
#include <chrono>

void desenharIndividuo(const Individuo& individuo, sf::RenderWindow& janela, sf::RenderTexture& textura, int segmentos) {
    sf::Vector2u tamanho = janela.getSize();

    textura.clear();
    gerarTextura(textura, individuo.cromossomo, segmentos, tamanho.x, tamanho.y);

    janela.draw(sf::Sprite(textura.getTexture()));
}

int main() {    
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(203, 200), "Hello SFML");
    sf::RenderTexture textura;
    sf::Vector2u tamanho = window.getSize();
    textura.create(tamanho.x, tamanho.y);

    AlgoritmoGenetico ag(60, 8000, false);


    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= 500; i++) {
        window.clear();
        std::cout << "Starting generation " << i << "\n";
        ag.evoluir();

        const Individuo& melhor = ag.getMelhorIndividuo();
        std::cout << "Melhor distância: " << (1 / melhor.aptidao) << "\n";

        desenharIndividuo(melhor, window, textura, 100);

        window.display();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "\n";

    while (true) {
        window.display();
    }

    return 0;
}
