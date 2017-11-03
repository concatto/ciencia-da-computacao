#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

struct Nave : sf::CircleShape {
  float velMaxima;
  float velocidade = 0;
  float aceleracao = 0;
  float direcao = 0;
  
  Nave(float velMaxima) {
    this->velMaxima = velMaxima;
    setRadius(30);
    setOrigin(30, 30);
    setScale(0.6, 1);
    setPointCount(3);
  }
  
  void orientar(float graus) {
    setRotation(graus + 90);
    direcao = graus;
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
    
    float rad = direcao * (M_PI / 180);
    move(velocidade * cos(rad), velocidade * sin(rad));
  }
  
  void atualizarVelocidade() {
    // Acesso implícito aos membros da instância
    velocidade += aceleracao;
  }
};

int main() {
  sf::RenderWindow janela(sf::VideoMode(800, 600), "SFML");
  janela.setFramerateLimit(60);

  vector<sf::CircleShape> projeteis;
  
  Nave nave(20);
  nave.aceleracao = 0.05;
  nave.setPosition(150, 300);
  nave.orientar(0);
  
  float direcaoProjetil = 0;
  
  while (janela.isOpen()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      nave.orientar(nave.direcao + 4);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      nave.orientar(nave.direcao - 4);
    }
    
    sf::Event evento;
    while (janela.pollEvent(evento)) {
      if (evento.type == sf::Event::Closed) {
        janela.close();
      } else if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Space) {
          sf::CircleShape projetil(5);
          projetil.setOrigin(5, 5);
          projetil.setPosition(nave.getPosition());
          projetil.setRotation(nave.direcao);
          
          projeteis.push_back(projetil);
        }
      }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      nave.aceleracao = 0.1;
    } else {
      nave.aceleracao = -0.1;
    }
    
    nave.atualizar();
    
    janela.clear();
    
    for (int i = 0; i < projeteis.size(); i++) {
      sf::CircleShape& projetil = projeteis[i];
      
      float projetilRad = projetil.getRotation() * (M_PI / 180);
      projetil.move(20 * cos(projetilRad), 20 * sin(projetilRad));
      
      janela.draw(projetil);
    }
    
    janela.draw(nave);
    janela.display();
  }
  
  return 0;
}  

  
