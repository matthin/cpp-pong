#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include "FrameRate.hpp"

sf::Text FrameRate::get() {
	static sf::Clock clock;
	static int fps;
	static sf::Text text_fps;
	static int fps_incrementor = 0;

	fps_incrementor++;

	if (clock.getElapsedTime().asSeconds() >= 1.f) {
		fps = fps_incrementor;
		fps_incrementor = 0;
		text_fps = FrameRate::configure_fps(fps);
		clock.restart();
	}

	return text_fps;
}

sf::Text FrameRate::configure_fps(int fps) {
	std::ostringstream convert;
	static std::string string_fps;
	static sf::Text text_fps;
	static sf::Font font;
	static int already_ran = false;

	if (already_ran == false) {
		// text_fps display configuration
		font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
		text_fps.setFont(font);
		text_fps.setCharacterSize(24);
		text_fps.setColor(sf::Color::Red);
		text_fps.setStyle(sf::Text::Bold | sf::Text::Underlined);

		already_ran = true;
	}

	// Convert int_fps into string string_fps, then finally into text_fps
	convert << fps;
	string_fps = convert.str();
	text_fps.setString(string_fps);

	return text_fps;;
}