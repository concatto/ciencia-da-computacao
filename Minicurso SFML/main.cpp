#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct Nave {
  sf::CircleShape forma;
  float velocidade;
  float aceleracao;
  float velMaxima;
  
  Nave(float velMaxima) {
    this->velMaxima = velMaxima;
    this->aceleracao = 0; // Uso do this é opcional
    this->velocidade = 0;
    forma.setRadius(30);
    forma.setPointCount(3);
  }
  
  void desenhar(sf::RenderWindow& window) {
    window.draw(forma);
  }
  
  void verificarVelocidade() {
    if (velocidade > velMaxima) {
      aceleracao = 0;
      velocidade = velMaxima;
    } else if (velocidade < 0) {
      aceleracao = 0;
      velocidade = 0;
    }
  }
  
  void atualizar() {
    atualizarVelocidade();
    verificarVelocidade();
    forma.move(0, -velocidade);
  }
  
  void atualizarVelocidade() {
    // Acesso implícito aos membros da instância
    velocidade += aceleracao;
  }
};

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
  window.setFramerateLimit(60);
  
  Nave nave(10);
  nave.aceleracao = 0.1;
  nave.forma.setPosition(0, 600);
  nave.forma.setOrigin(30, 30);
  nave.forma.setScale(0.6, 1);
  
  float angulo = 323;
  float rad = angulo * (M_PI / 180);
  
  while (window.isOpen()) {
    window.clear();
    
    //nave.atualizar();
    
    nave.forma.setRotation(angulo + 90);
    nave.forma.move(2 * std::cos(rad), 2 * std::sin(rad));
    nave.desenhar(window);
    
    window.display();    
  }
  
  return 0;
}  

  
