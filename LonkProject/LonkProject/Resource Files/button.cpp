#include "button.h"

Button::Button()
{
}

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color touchColor, sf::Color pressColor) {
	this->buttonState = button_idle;

	this->rect.setPosition(sf::Vector2f(x, y));
	this->rect.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(22);

	this->text.setPosition(
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		(this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2.f)- 7 - this->text.getGlobalBounds().height / 2.f)
	);

	this->idleColor = idleColor;
	this->touchColor = touchColor;
	this->pressColor = pressColor;

	this->rect.setFillColor(this->idleColor);

}

Button::~Button() {

}

void Button::Render(sf::RenderTarget* target) {

	target->draw(this->rect);
	target->draw(this->text);
}

void Button::RenderPauseButton(sf::RenderTarget* target, float x, float y) {
	this->rect.setPosition(x, y);
	this->text.setPosition(
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		(this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2.f) - 7 - this->text.getGlobalBounds().height / 2.f)
	);
	target->draw(this->rect);
	target->draw(this->text);
}

void Button::Update(const sf::Vector2f mousePos) {

	this->buttonState = button_idle;

	if (this->rect.getGlobalBounds().contains(mousePos)) {
		this->buttonState = button_touch;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = button_pressed;
		}
	}

	switch (this->buttonState) {
	case button_idle:
		this->rect.setFillColor(this->idleColor);
		break;

	case button_touch:
		this->rect.setFillColor(this->touchColor);
		break;

	case button_pressed:
		this->rect.setFillColor(this->pressColor);
		break;

	default:
		this->rect.setFillColor(this->idleColor);
		break;
	}
}

const bool Button::isPressed() const {
	if (this->buttonState == button_pressed) {
		return true;
	}
	else {
		return false;
	}
}

