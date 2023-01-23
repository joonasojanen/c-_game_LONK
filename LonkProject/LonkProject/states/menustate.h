#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

#include "gamestate.h"
#include "../Resource Files/button.h"


class MenuState : public State {
public:

	/* MenuState:
	* State class that runs the MenuScreen.
	* the constructor of MenuState class, takes the following parameters:
	* - window @ Assigns class protected member window.
	* - states @ Assigns class protected std::stack states_ that holds states of the program.
	*/
	MenuState(sf::RenderWindow* window, std::stack<State*> *states);

	/* ~MenuState:
	* virtual Destructor.
	*/
	virtual ~MenuState();

	/* UpdateInput:
	* UpdateInput function.
	*/
	void UpdateInput(const float& dt);

	/* UpdateButtons:
	* Updates menuscreens buttons.
	* Acts if different buttons are pressed.
	* StartButton pushes GameState to states_ and starts the main game.
	* QuitButton ends the current state.
	*/
	void UpdateButtons();

	/* Update:
	* A function that calls all Update functions at once.
	*/
	void Update(const float& dt);

	/* RenderButtons:
	* Renders buttons from buttons_ map.
	*/
	void RenderButtons(sf::RenderTarget* target = nullptr);

	/* Render:
	* Renders background and buttons of the menu.
	*/
	void Render(sf::RenderTarget* target = nullptr);

private:
	sf::RectangleShape background_;
	sf::Font font;

	std::map<std::string, Button*> buttons_;

	sf::Texture backgroundTexture;

	sf::Music music;

	/* initFonts:
	* Loads font from file.
	*/
	void initFonts();

	/* initButtons:
	* Sets buttons to buttons_ map with own names.
	*/
	void initButtons();
};

#endif