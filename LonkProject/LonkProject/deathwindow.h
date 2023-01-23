#pragma once
#include <iostream>

#include "Resource Files/button.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

class DeathWindow {
public:

	/* DeathWindow:
	* Default constructor.
	*/
	DeathWindow();

	/* DeathWindow:
	* the constructor of DeathWindow class, takes the following parameters:
	* - width @ The width of the window that opens when the player character dies.
	* - heigth @ The heigth of the window that opens when the player character dies.
	* - color @ NOT USED
	* - font @ Button text font
	*/
	DeathWindow(float width, float height);

	/* ~DeathWindow:
	* Destructor.
	*/
	~DeathWindow();

	/* Render:
	* Assigns position of the Deathwindow in the window and draws the DeathWindow shape on the window.
	*/
	void Render(sf::RenderWindow& window, float x, float y);

	/* RenderButton:
	* Calls RenderPausebutton function that assigns the buttons on the window.
	*/
	void RenderButton(sf::RenderWindow* window);

	/* Update:
	* Checks if Mouse1 is pressed by calling IsPressed function.
	*/
	int Update();

	/* UpdateMouse:
	* Updates mousepositions for mousePosScreen, mousePosWindow and mousePosView.
	*/
	void UpdateMouse(sf::RenderWindow& window);

	/* initFonts:
	* Loads font from file.
	*/
	void initFonts();

	/* initButtons:
	* Initialises buttons by assigning the positions, sizes and colors.
	*/
	void initButtons(sf::Font* font);

	sf::RectangleShape rect;

protected:

	sf::Text text;
	sf::Font font;
	Button* returnButton;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

