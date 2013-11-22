#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FrameRate.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Pyrohail - Pong Remake");
    sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(600, 600));
    rectangle.setFillColor(sf::Color::Green);

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	FrameRate fps;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
			}
		}

        window.clear();
        window.draw(rectangle);
		window.draw(fps.get());
        window.display();
    }

    return 0;
}