#ifndef CIRCULOS_H
#define CIRCULOS_H

#include <SFML/Graphics.hpp>
#include <vector>

sf::Texture gerarTextura(const std::vector<int>& cromossomo, int largura, int altura) {
    sf::RenderTexture textura;
    textura.create(largura, altura);


}

#endif // CIRCULOS_H
