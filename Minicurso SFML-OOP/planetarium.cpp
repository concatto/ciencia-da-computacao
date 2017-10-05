#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

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

     CorpoCeleste(float raio, float massa, sf::Vector2f velocidade = sf::Vector2f(), bool ativo = true)
          : sf::CircleShape(raio), massa(massa), velocidade(velocidade), ativo(ativo) {
          setFillColor(sf::Color::White);
          setOrigin(raio, raio);
     }

     sf::Vector2f getCentro() const {
          sf::Vector2f pos = getPosition();
          return sf::Vector2f(pos.x + getRadius(), pos.y + getRadius());
     }

     void atualizar(float velEscalar, float direcao) {
          //Coordenadas polares para cartesianas
          velocidade.x += velEscalar * std::cos(direcao);
          velocidade.y += velEscalar * std::sin(direcao);
          move(velocidade);
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
  float width = 1280;
  float height = 1024;
  
	sf::RenderWindow window(sf::VideoMode(width, height), L"Planetário");
	window.setFramerateLimit(60);
  
  sf::View view(sf::FloatRect(0, 0, width, height));
  window.setView(view);

	sf::Vector2f start;
	sf::Vector2f end;

	Estrela estrela(70, 20000);
	CorpoCeleste planeta1(10, 1, sf::Vector2f(9, 0));
	CorpoCeleste planeta2(8, 3, sf::Vector2f(5, 0));
	CorpoCeleste planeta3(15, 5, sf::Vector2f(6, 0));

	estrela.setPosition(width / 2, height / 2);
	planeta1.setPosition(500, 300);
	planeta2.setPosition(400, 100);
	planeta3.setPosition(600, 50);

	//estrela.planetas.push_back(planeta1);
	//estrela.planetas.push_back(planeta2);
	//estrela.planetas.push_back(planeta3);

	float alpha = 0.05;

	bool shouldSpawn = false;
	bool shouldDraw = false;

	sf::Font font;
	std::cout << font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") << "\n";

	sf::Texture sunTexture;
	sunTexture.loadFromFile("sun.png");

	std::vector<sf::IntRect> rects = particionarTextura(sunTexture, 4, 8);

	sf::VertexArray vertices(sf::PrimitiveType::Lines, 2);

	int frame = 0;
	int time = 0;
	estrela.setTexture(&sunTexture);
	estrela.setTextureRect(rects[frame]);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					start = getMousePosition(window, event.mouseButton);
          
          estrela.planetas.emplace_back(4, 1, sf::Vector2f(), false);
          estrela.planetas.back().setPosition(start);
          
					shouldDraw = true;
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					end = getMousePosition(window, event.mouseButton);
					shouldSpawn = true;
					shouldDraw = false;
				}
			} else if (event.type == sf::Event::MouseWheelScrolled) {
        view.zoom(event.mouseWheelScroll.delta * 0.2 + 1);
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
			estrela.move(0, -speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			estrela.move(-speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			estrela.move(0, speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			estrela.move(speed, 0);
		}

		window.clear();

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
      planeta.massa += 0.9;
		}

		if (time == 5) {
			time = 0;
			frame = (frame + 1) % rects.size();
			estrela.setTextureRect(rects[frame]);
		}

		window.draw(estrela);
		window.display();
		time++;
	}

	return 0;
}
