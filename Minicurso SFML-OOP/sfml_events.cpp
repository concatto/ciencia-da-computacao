#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.14159

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Events");
	std::vector<sf::CircleShape> circles;

	sf::Vector2f start;
	sf::Vector2f end(-1, -1);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f& vec = event.type == sf::Event::MouseButtonPressed ? start : end;
					vec = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
			}
		}

		window.clear();

		if (end.x >= 0 && end.y >= 0) {
			sf::Vector2f delta = end - start;

			std::cout << std::atan2(delta.y, delta.x) * (180.0 / PI) << "\n";

			end = sf::Vector2f(-1, -1);
		}

		window.display();
	}
}
