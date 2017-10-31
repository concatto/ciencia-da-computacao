#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
  
  while (window.isOpen()) {
    window.clear();
    
    // Operações de desenho...
    
    window.display();    
  }
  
  return 0;
}  

  
