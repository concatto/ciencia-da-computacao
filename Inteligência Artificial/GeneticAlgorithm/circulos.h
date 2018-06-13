#ifndef CIRCULOS_H
#define CIRCULOS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "util.h"

sf::CircleShape criarElipse(int x, int y, int largura, int altura) {
    int min = std::min(largura, altura) / 2;
    int max = std::max(largura, altura) / 2;

    double escala = max / static_cast<double>(min);

    sf::CircleShape elipse(min, 200);
    elipse.setOrigin(min, min);
    elipse.setPosition(x, y);

    if (largura > altura) {
        elipse.setScale(escala, 1);
    } else {
        elipse.setScale(1, escala);
    }

    return elipse;
}

sf::CircleShape criarElipse(const std::vector<int>& cromossomo, int larguraMax, int alturaMax) {
    //std::cout << paraString(cromossomo) << "\n";

    // 2 segmentos para posição, 2 para tamanho e 3 para cor
    int k = 8;
    std::vector<int> segmentos = segmentarDecimal(cromossomo, k);

    int limite = 2 << ((cromossomo.size() / k) - 1);
    Limitador limitador(0, limite);


    int x = limitador.aplicar(segmentos[0], 0, larguraMax);
    int y = limitador.aplicar(segmentos[1], 0, alturaMax);
    int largura = limitador.aplicar(segmentos[2], 0, larguraMax / 1.5);
    int altura = limitador.aplicar(segmentos[3], 0, alturaMax / 1.5);
    int r = limitador.aplicar(segmentos[4], 0, 255);
    int g = limitador.aplicar(segmentos[5], 0, 255);
    int b = limitador.aplicar(segmentos[6], 0, 255);
    int a = limitador.aplicar(segmentos[7], 127, 255);

//    std::cout << "X: " << x << "\n";
//    std::cout << "Y: " << y << "\n";
//    std::cout << "W: " << largura << "\n";
//    std::cout << "H: " << altura << "\n";
//    std::cout << "R: " << r << "\n";
//    std::cout << "G: " << g << "\n";
//    std::cout << "B: " << b << "\n";


    sf::CircleShape elipse = criarElipse(x, y, largura, altura);
    elipse.setFillColor(sf::Color(r, g, b, a));

    return elipse;
}

void gerarTextura(sf::RenderTexture& alvo, const std::vector<int>& cromossomo, int elipses, int largura, int altura) {
    std::vector<std::vector<int>> segmentos = segmentar(cromossomo, elipses);

    for (const std::vector<int>& segmento : segmentos) {
        sf::CircleShape elipse = criarElipse(segmento, largura, altura);

        alvo.draw(elipse);
    }

    alvo.display();
}

//double computarDiferenca(const sf::Image& imagemA, const sf::Image& imagemB) {
//    sf::Vector2u tamanho = imagemA.getSize();

//    int total = 0;

//    for (int x = 0; x < tamanho.x; x++) {
//        for (int y = 0; y < tamanho.y; y++) {
//            sf::Color corA = imagemA.getPixel(x, y);
//            sf::Color corB = imagemB.getPixel(x, y);

//            int r = std::abs(corA.r - corB.r);
//            int g = std::abs(corA.g - corB.g);
//            int b = std::abs(corA.b - corB.b);

//            total += r + g + b;
//        }
//    }

//    return total;
//}


double computarDiferenca(const sf::Uint8* pixelsA, const sf::Uint8* pixelsB, const sf::Vector2u& tamanho) {
    int total = 0;

    for (int k = 0; k < tamanho.x * tamanho.y; k++) {
        int i = k * 4;
        int r = std::abs(pixelsA[i + 0] - pixelsB[i + 0]);
        int g = std::abs(pixelsA[i + 1] - pixelsB[i + 1]);
        int b = std::abs(pixelsA[i + 2] - pixelsB[i + 2]);

        total += r + g + b;
    }

    return total;
}

#endif // CIRCULOS_H
