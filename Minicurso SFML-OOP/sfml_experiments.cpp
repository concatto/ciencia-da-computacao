#include <SFML/Graphics.hpp>
#include <iostream>

class Application {
private:
	sf::Texture tex;
	sf::CircleShape circle;
	sf::Sprite sprite;

public:
	Application() {
		circle.setRadius(100);
		circle.setPointCount(100);
		circle.setPosition(400, 300);
		circle.setFillColor(sf::Color::White);

		std::cout << tex.loadFromFile("image2.png") << "\n";

		sf::Vector2u size = tex.getSize();

		circle.setTexture(&tex);
		sprite.setTexture(tex);
		sprite.setPosition(sf::Vector2f(200, 200));
		sprite.setScale(sf::Vector2f(0.4f, 0.4f));
		sprite.setOrigin(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
	}

	void draw(sf::RenderWindow& window) {
		window.draw(circle);
		window.draw(sprite);

		sprite.rotate(40);
		circle.scale(1.001f, 1.001f);
	}
};

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello");
   	window.setFramerateLimit(60);

	Application app;
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		app.draw(window);
		window.display();
	}	
}
