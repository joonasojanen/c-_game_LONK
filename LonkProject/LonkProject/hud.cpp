#include "hud.h"

Hud::Hud()
{
	this->font.loadFromFile("Resource Files/fonts/akira.otf");
	this->hudTexture.loadFromFile("Resource Files/textures/HUDBar.png");
	this->heartTexture.loadFromFile("Resource Files/textures/Heart.png");
	this->strTexture.loadFromFile("Resource Files/textures/STR.png");
	this->hudRect.setSize(sf::Vector2f(600, 30));
	this->heartRect.setSize(sf::Vector2f(20, 20));
	this->strRect.setSize(sf::Vector2f(20, 20));
	this->hudRect.setTexture(&hudTexture);
	this->heartRect.setTexture(&heartTexture);
	this->strRect.setTexture(&strTexture);

	this->hpText.setFont(font);
	this->hpText.setFillColor(sf::Color::Black);
	this->hpText.setCharacterSize(15);

	this->strengthText.setFont(font);
	this->strengthText.setFillColor(sf::Color::Black);
	this->strengthText.setCharacterSize(15);

	this->expText.setFont(font);
	this->expText.setFillColor(sf::Color::Black);
	this->expText.setCharacterSize(15);



}

Hud::~Hud()
{

}

void Hud::Render(sf::RenderWindow & window, float x, float y)
{
	this->hpText.setString(hpString);
	this->expText.setString(expString);
	this->strengthText.setString(strengthString);


	this->hudRect.setPosition(sf::Vector2f((x - 300), (y + 160)));
	this->heartRect.setPosition(sf::Vector2f((this->hudRect.getPosition().x + 20), (this->hudRect.getPosition().y + 5)));
	this->strRect.setPosition(sf::Vector2f((this->hudRect.getPosition().x + 215), (this->hudRect.getPosition().y + 5)));

	this->hpText.setPosition(
		(this->hudRect.getPosition().x + 65),
		(this->hudRect.getPosition().y + 4)
	);
	this->strengthText.setPosition(
		(this->hudRect.getPosition().x + 265),
		(this->hudRect.getPosition().y + 4)
	);
	this->expText.setPosition(
		(this->hudRect.getPosition().x + 460),
		(this->hudRect.getPosition().y + 4)
	);
	


	window.draw(this->hudRect);

	window.draw(this->hpText);
	window.draw(this->strengthText);
	window.draw(this->expText);

	window.draw(this->heartRect);
	window.draw(this->strRect);

}

void Hud::Update(int hp, int exp, int strength)
{
	this->hpString = "HP: " + std::to_string(hp);
	this->expString = "XP: " + std::to_string(exp);
	this->strengthString = "STR: " + std::to_string(strength);
}
