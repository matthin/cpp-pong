#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FrameRate.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Pyrohail - Pong Remake", sf::Style::Default, settings);

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::RectangleShape leftPaddle;
	leftPaddle.setFillColor(sf::Color(250, 250, 250));
	leftPaddle.setSize(sf::Vector2f(20, 200));
	leftPaddle.setPosition(0, 0);

	sf::RectangleShape rightPaddle;
	rightPaddle.setFillColor(sf::Color(250, 250, 250));
	rightPaddle.setSize(sf::Vector2f(20, 200));
	rightPaddle.setPosition(1004, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		// Left paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (leftPaddle.getPosition().y > 0) {
				leftPaddle.move(0, -6);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (leftPaddle.getPosition().y < 568) {
				leftPaddle.move(0, 6);
			}
		}
		window.draw(leftPaddle);

		// Right paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (rightPaddle.getPosition().y > 0) {
				rightPaddle.move(0, -6);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (rightPaddle.getPosition().y < 568) {
				rightPaddle.move(0, 6);
			}
		}
		window.draw(rightPaddle);

		FrameRate::displayFPS(window);
        window.display();
    }

    return 0;
}