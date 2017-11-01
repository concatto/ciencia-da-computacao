#include <iostream>
#include <SFML/Graphics.hpp>

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
    forma.setScale(0.75, 1);
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
  nave.forma.setPosition(300, 500);
  
  while (window.isOpen()) {
    window.clear();
    
    nave.atualizar();
    
    nave.desenhar(window);
    
    window.display();    
  }
  
  return 0;
}  

  
