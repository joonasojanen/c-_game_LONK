#pragma once
#include <iostream>

#include "Resource Files/button.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

class VictoryWindow {
public:

	/* VictoryWindow:
	* Default constructor.
	*/
	VictoryWindow();

	/* VictoryWindow:
	* the constructor of VictoryWindow class, takes the following parameters:
	* - width @ The width of the window that opens when the player character wins.
	* - heigth @ The heigth of the window that opens when the player character wins.
	* - color @ NOT USED
	* - font @ Button text font
	*/
	VictoryWindow(float width, float height);

	/* ~VictoryWindow:
	* Destructor.
	*/
	~VictoryWindow();

	/* Render:
	* Assigns position of the VictoryWindow in the window and draws the VictoryWindow shape on the window.
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