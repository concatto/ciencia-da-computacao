#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& out, const sf::Vector2f vec) {
	out << "(" << vec.x << "," << vec.y << ")\n";
	return out;
}

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello");
	window.setFramerateLimit(60);

	sf::CircleShape star(40);
	star.setFillColor(sf::Color::Yellow);
	star.setOrigin(sf::Vector2f(40, 40));

	sf::CircleShape planet(10);
	planet.setFillColor(sf::Color(220, 220, 255));
	planet.setOrigin(sf::Vector2f(10, 10));

	sf::Vector2f acceleration;
	sf::Vector2f velocity(5.0f, 0.0f);

	star.setPosition(sf::Vector2f(300, 300));
	planet.setPosition(sf::Vector2f(300, 100));

	float starMass = 23000;
	float planetMass = 5;

	sf::Font font;
	std::cout << font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") << "\n";

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::Vector2f delta(star.getPosition() - planet.getPosition());
		float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
		float force = (starMass * planetMass) / (dist * dist);

		float magnitude = force / planetMass;
		float angle = std::atan2(delta.y, delta.x);

		acceleration = sf::Vector2f(magnitude * std::cos(angle), magnitude * std::sin(angle));
		velocity += acceleration;

		float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		float direction = std::atan2(velocity.y, velocity.x);

		sf::Text label(std::to_string(dist) + "\nSpeed " + std::to_string(speed), font);
		label.setFillColor(sf::Color::White);

		planet.setPosition(planet.getPosition() + velocity);

		window.clear();
		window.draw(star);
		window.draw(planet);
		window.draw(label);
		window.display();
	}

	return 0;
}
