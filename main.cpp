#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <chrono>
#include <random>

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

	sf::CircleShape ball(10.f);
	ball.setFillColor(sf::Color(250, 250, 250));

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<float> xDistribution(100.f, 400.f);
	std::uniform_real_distribution<float> yDistribution(100.f, 676.f);
	
	sf::Vector2f ballStart;
	ballStart.x = xDistribution(generator);
	ballStart.y = yDistribution(generator);
	ball.setPosition(ballStart);

	sf::Vector2<float> ballSpeed(5, 5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				window.close();
			}
		}

		// Human control
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

		// AI control
		if (rightPaddle.getPosition().y > ball.getPosition().y - 100) {
			if (rightPaddle.getPosition().y > 0) {
				rightPaddle.move(0, -6);
			}
		}
		if (rightPaddle.getPosition().y < ball.getPosition().y - 100) {
			if (rightPaddle.getPosition().y < 568) {
				rightPaddle.move(0, 6);
			}
		}

		// Ball control
		if (ball.getPosition().y <= 5 || ball.getPosition().y >= 763) {
			ballSpeed.y = -ballSpeed.y;
		}
		if (ball.getPosition().x <= 5 || ball.getPosition().x >= 1019) {
			ballSpeed = sf::Vector2<float>(0.f, 0.f);
		}
		if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
			ballSpeed.x = -ballSpeed.x;
		}

		ball.move(ballSpeed);

		window.clear(sf::Color::Black);
		window.draw(ball);
		window.draw(leftPaddle);
		window.draw(rightPaddle);

		FrameRate::displayFPS(window);
        window.display();
    }

    return 0;
}