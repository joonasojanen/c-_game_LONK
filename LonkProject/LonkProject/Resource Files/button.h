#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <iostream>
#include <ctime>
#include <sstream>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

enum button_states { button_idle = 0, button_touch, button_pressed };

class Button {
public:
	Button();
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color touchColor, sf::Color pressColor);
	~Button();

	void Render(sf::RenderTarget* target);
	void RenderPauseButton(sf::RenderTarget* target, float x, float y);
	void Update(const sf::Vector2f mousePos);

	const bool isPressed() const;
	sf::Font* font;
	sf::Text text;

private:
	int buttonState;

	sf::RectangleShape rect;


	sf::Color idleColor;
	sf::Color touchColor;
	sf::Color pressColor;
};

#endif