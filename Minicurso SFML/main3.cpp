#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
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
  srand(time(nullptr));
  sf::RenderWindow janela(sf::VideoMode(800, 600), "SFML");
  janela.setFramerateLimit(60);

  vector<sf::RectangleShape> projeteis;
  vector<sf::RectangleShape> asteroides;
  
  Nave nave(20);
  nave.aceleracao = 0.05;
  nave.setPosition(150, 300);
  nave.orientar(0);
  
  //float direcaoProjetil = 0;
  sf::Clock relogio;
  sf::Clock relogioAsteroide;
  
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
          // Antigamente, Adicionava um projétil
        }
      }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      nave.aceleracao = 0.1;
    } else {
      nave.aceleracao = -0.1;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      if (relogio.getElapsedTime().asMilliseconds() > 100) {
        sf::RectangleShape projetil(sf::Vector2f(10, 4));
        projetil.setOrigin(5, 2);
        projetil.setPosition(nave.getPosition());
        projetil.setRotation(nave.direcao);
        
        projeteis.push_back(projetil);
        relogio.restart();
      }
    }
    
    if (relogioAsteroide.getElapsedTime().asSeconds() > 0.5) {
      relogioAsteroide.restart();
      
      sf::RectangleShape asteroide(sf::Vector2f(70, 70));
      asteroide.setPosition(rand() % 800, rand() % 600);
      asteroide.setFillColor(sf::Color::Red);
      
      asteroides.push_back(asteroide);
    }
    
    nave.atualizar();
    
    janela.clear();
    
    
    for (int i = asteroides.size() - 1; i >= 0; i--) {
      for (int j = projeteis.size() - 1; j >= 0; j--) {
        if (asteroides[i].getGlobalBounds().intersects(projeteis[j].getGlobalBounds())) {
          projeteis.erase(projeteis.begin() + j);
          asteroides.erase(asteroides.begin() + i);
          
          break;
        }
      }
      
      if (nave.getGlobalBounds().intersects(asteroides[i].getGlobalBounds())) {
        return 0;
      }
    }
    
    sf::FloatRect retanguloJanela(0, 0, 800, 600);
    for (int i = 0; i < projeteis.size(); i++) {
      sf::RectangleShape& projetil = projeteis[i];
      
      if (retanguloJanela.contains(projetil.getPosition())) {        
        float projetilRad = projetil.getRotation() * (M_PI / 180);
        projetil.move(20 * cos(projetilRad), 20 * sin(projetilRad));
        
        janela.draw(projetil);
      } else {
        projeteis.erase(projeteis.begin() + i);
        i--;
      }
    }
    
    for (sf::RectangleShape& asteroide : asteroides) {
      asteroide.move(5, 1);
      janela.draw(asteroide);
    }
    
    //cout << "Projeteis: " << projeteis.size() << "\n";
    
    janela.draw(nave);
    janela.display();
  }
  
  return 0;
}  

  
