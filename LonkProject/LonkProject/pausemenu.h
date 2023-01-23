#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

#include <iostream>

#include "Resource Files/button.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

class PauseMenu {
public:

	/* PauseMenu:
	* Default constructor.
	*/
	PauseMenu();

	/* PauseMenu:
	* the constructor of PauseMenu class, takes the following parameters:
	* - width @ The width of the window that opens when the player character dies.
	* - heigth @ The heigth of the window that opens when the player character dies.
	* - color @ pause text color.
	* - font @ pause text font.
	*/
	PauseMenu(float width, float height, sf::Color color, sf::Font* font);

	/* ~Pausemenu:
	* Destructor.
	*/
	~PauseMenu();

	/* Render:
	* Assigns position of the PauseMenuWindow in the window and draws the PauseMenu shape on the window.
	*/
	void Render(sf::RenderWindow& window, float x, float y);

	/* RenderButtons:
	* Calls RenderPausebutton function that assigns the buttons on the window.
	*/
	void RenderButtons(sf::RenderWindow* window);

	/* Update:
	* Updates the mouseposition on the window.
	* returns int value according to which button is pressed.
	*/
	int Update();

	/* UpdateMouse:
	* Updates the mousepositions.
	*/
	void UpdateMouse(sf::RenderWindow& window);

	/* CheckOpenPauseMenu:
	* Checks if the user presses ESC which changes the state of pauseOn flag.
	* Resets clock.
	* Returns clock.
	*/
	sf::Clock CheckOpenPauseMenu(sf::Clock clock);

	/* CheckClosePauseMenu:
	* Checks if PauseMenu window is open and if the user presses ESC which changes the state of pauseOn flag.
	* Resets clock.
	* Returns clock.
	*/
	sf::Clock CheckClosePauseMenu(sf::Clock clock);

	/* initFonts:
	* Loads font from a file.
	*/
	void initFonts();

	/* initButtons:
	* Initialises buttons by assigning the positions, sizes and colors.
	*/
	void initButtons(sf::Font* font);

	sf::RectangleShape rect;
	bool pauseOn = false;

protected:
	
	sf::Text text;
	sf::Font font;
	std::map<std::string, Button*> pauseButtons_;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

#endif