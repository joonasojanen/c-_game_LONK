#pragma once

#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

class Hud
{
public:

	/* Hud:
	* Loads textures from files and sets sizes, fonts and colors of the texts.
	*/
	Hud();

	/* ~Hud:
	* Destructor.
	*/
	~Hud();

	/* Render:
	* Sets positions of hud shapes and draws them.
	*/
	void Render(sf::RenderWindow& window, float x, float y);

	/* Update:
	* Updates hpstring, expstring and strengthstring.
	*/
	void Update(int hp, int exp, int strenght);

	int hpAmount;
	int expAmount;
	int strengthAmount;

private:
	std::string strengthString;
	std::string hpString;
	std::string expString;

	sf::RectangleShape hudRect;
	sf::RectangleShape heartRect;
	sf::RectangleShape strRect;
	sf::Texture hudTexture;
	sf::Texture heartTexture;
	sf::Texture strTexture;

	sf::Text hpText;
	sf::Text expText;
	sf::Text strengthText;
	sf::Font font;
};

