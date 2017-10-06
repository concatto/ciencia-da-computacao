#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <ctime>
#include <cstdlib>

#define PI 3.14159

std::ostream& operator<<(std::ostream& out, const sf::Vector2f vec) {
	out << "(" << vec.x << "," << vec.y << ")\n";
	return out;
}

class CorpoCeleste : public sf::CircleShape {
public:
     float massa;
     sf::Vector2f velocidade;
     bool ativo;
     float rotacao;

     CorpoCeleste(float raio, float massa, sf::Vector2f velocidade = sf::Vector2f(), bool ativo = true)
          : sf::CircleShape(raio), massa(massa), velocidade(velocidade), ativo(ativo) {
          setFillColor(sf::Color::White);
          setOrigin(raio, raio);
          
          rotacao = (std::rand() / static_cast<float>(RAND_MAX)) * 0.2 + 0.1;
     }
     
     void aumentarRaio(float valor) {
       setRadius(getRadius() + valor);
       setOrigin(getRadius(), getRadius());
     }

     sf::Vector2f getCentro() const {
          sf::Vector2f pos = getPosition();
          //return sf::Vector2f(pos.x + getRadius(), pos.y + getRadius());
          return pos;
     }

     void atualizar(float velEscalar, float direcao) {
          //Coordenadas polares para cartesianas
          velocidade.x += velEscalar * std::cos(direcao);
          velocidade.y += velEscalar * std::sin(direcao);
          move(velocidade);
          rotate(rotacao);
     }
};

class Estrela : public CorpoCeleste {
public:
     std::vector<CorpoCeleste> planetas;

     using CorpoCeleste::CorpoCeleste; //Explicitamente herdar o construtor da superclasse
};


std::vector<sf::IntRect> particionarTextura(const sf::Texture& textura, int linhas, int colunas) {
     sf::Vector2u tam = textura.getSize();
     int largura = tam.x / colunas;
     int altura = tam.y / linhas;

     std::vector<sf::IntRect> retangulos;
     for (int i = 0; i < linhas; i++) {
          for (int j = 0; j < colunas; j++) {
               retangulos.push_back(sf::IntRect(j * largura, i * altura, largura, altura));
          }
     }

     return retangulos;
}


sf::Vector2f getMousePosition(const sf::RenderWindow& window) {
  return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

sf::Vector2f getMousePosition(const sf::RenderWindow& window, const sf::Event::MouseButtonEvent& e) {
  return window.mapPixelToCoords(sf::Vector2i(e.x, e.y));
}


int main(int argc, char** argv) {
  std::srand(std::time(nullptr));
  
  float width = 1280;
  float height = 1024;
  
	sf::RenderWindow window(sf::VideoMode(width, height), L"Planetário");
	window.setFramerateLimit(60);
  
  sf::View view(sf::FloatRect(0, 0, width, height));
  window.setView(view);

	sf::Vector2f start;
	sf::Vector2f end;

	Estrela estrela(80, 1E5);
	estrela.setPosition(width / 2, height / 2);

	float alpha = 0.05;

	bool shouldSpawn = false;
	bool shouldDraw = false;

	sf::Font font;
	std::cout << font.loadFromFile("arial.ttf") << "\n";
  sf::Text textoEstrela;
  textoEstrela.setFont(font);
  textoEstrela.setCharacterSize(24);
  textoEstrela.setFillColor(sf::Color::White);
  textoEstrela.setPosition(10, 10);

	sf::Texture sunTexture;
	sunTexture.loadFromFile("sun3.png");

	std::vector<sf::IntRect> rects = particionarTextura(sunTexture, 1, 1);

  sf::Texture fundoTex;
  fundoTex.loadFromFile("fundo.jpg");
  sf::Sprite fundo(fundoTex);
  
	sf::VertexArray vertices(sf::PrimitiveType::Lines, 2);

	int frame = 0;
	int time = 0;
	estrela.setTexture(&sunTexture);
	estrela.setTextureRect(rects[frame]);
  
  std::vector<sf::Texture> planetasTex;
  for (int i = 1; i <= 8; i++) {
    sf::Texture tex;
    tex.loadFromFile("planet" + std::to_string(i) + ".png");
    planetasTex.push_back(tex);
  }

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					start = getMousePosition(window, event.mouseButton);
          
          CorpoCeleste planeta(4, 1, sf::Vector2f(), false);
          planeta.setPosition(start);
          planeta.setTexture(&planetasTex[std::rand() % planetasTex.size()]);
          
          estrela.planetas.push_back(planeta);
          
					shouldDraw = true;
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					end = getMousePosition(window, event.mouseButton);
					shouldSpawn = true;
					shouldDraw = false;
				}
			} else if (event.type == sf::Event::MouseWheelScrolled) {
        view.zoom(event.mouseWheelScroll.delta * -0.1 + 1);
        window.setView(view);
      }
		}


		if (shouldSpawn) {
			sf::Vector2f delta = end - start;

      CorpoCeleste& planeta = estrela.planetas.back();
      planeta.velocidade = sf::Vector2f(delta.x * alpha, delta.y * alpha);
      planeta.ativo = true;

			shouldSpawn = false;
		}

		float speed = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			speed = 7;
		} else {
			speed = 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			view.move(0, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			view.move(-1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			view.move(0, 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			view.move(1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			view.setCenter(estrela.getCentro());
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      estrela.massa += 500;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && estrela.massa > 500) {
      estrela.massa -= 500;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && estrela.getRadius() > 1) {
      estrela.aumentarRaio(-1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      estrela.aumentarRaio(1);
    }
		
		std::ostringstream oss;
    oss << "Massa: " << estrela.massa << " kg\nRaio: " << (estrela.getRadius() * 1E3) << " km";
		textoEstrela.setString(oss.str());

		window.clear();
    // Desenhar invariantemente
    window.setView(window.getDefaultView());
    window.draw(fundo);
    window.setView(view);
    

		for (auto it = estrela.planetas.begin(); it != estrela.planetas.end(); ) {
			CorpoCeleste& planeta = *it;

			if (estrela.getGlobalBounds().intersects(planeta.getGlobalBounds())) {
				it = estrela.planetas.erase(it);
			} else {
        if (planeta.ativo) {
          sf::Vector2f diferenca = estrela.getCentro() - planeta.getCentro();
          float distancia = std::sqrt(std::pow(diferenca.x, 2) + std::pow(diferenca.y, 2));
          float angulo = std::atan2(diferenca.y, diferenca.x);

          float forcaGravitacional = (planeta.massa * estrela.massa) / std::pow(distancia, 2);
          forcaGravitacional = forcaGravitacional / planeta.massa; //Segunda lei de Newton (F = m.a)

          sf::Vector2f pos = planeta.getCentro();
          planeta.atualizar(forcaGravitacional, angulo);
        }

				window.draw(planeta);

				++it;
			}
    }

		if (shouldDraw) {
			vertices[0] = sf::Vertex(sf::Vector2f(start), sf::Color::White);
			vertices[1] = sf::Vertex(sf::Vector2f(getMousePosition(window)), sf::Color::White);
			window.draw(vertices);
      
      CorpoCeleste& planeta = estrela.planetas.back();
      planeta.setRadius(planeta.getRadius() + 0.3);
      planeta.setOrigin(planeta.getRadius(), planeta.getRadius());
		}

		if (time == 4) {
			time = 0;
			frame = (frame + 1) % rects.size();
			estrela.setTextureRect(rects[frame]);
		}

		estrela.rotate(estrela.rotacao * 0.2);
		
		window.draw(estrela);
    
    // Desenhar texto
    window.setView(window.getDefaultView());
    window.draw(textoEstrela);
    window.setView(view);
    
		window.display();
		time++;
	}

	return 0;
}
