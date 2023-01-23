#ifndef _STATE_H_
#define _STATE_H_

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include <iostream>
#include <stack>
#include <map>

#include "../entities/player.h"
#include "../Header Files/map.h"
#include "../Resource Files/animation.h"
#include "../Resource Files/projectile.h"
#include "../inventory/inventory.h"
#include "../chest.h"
#include "../pausemenu.h"
#include "../deathwindow.h"
#include "../victorywindow.h"
#include "../entities/monster.h"
#include "../entities/monsterCave.h"
#include "../door.h"
#include "../hud.h"
#include "../Resource Files/level.h"

class State {
public:

	/* State:
	* the constructor of State class, takes the following parameters:
	* - window @ Assigns class protected member window.
	* - states @ Assigns class protected std::stack states_ that holds states of the program.
	*/
	State(sf::RenderWindow* window, std::stack<State*>* states);

	/* ~State:
	* virtual Destructor.
	*/
	virtual ~State();

	/* getQuit:
	* A function that returns boolean value quit of state.
	*/
	const bool& getQuit() const;

	/* endState:
	* A function that sets the boolean value quit to true.
	* Ends the current state.
	*/
	virtual void endState();

	/* UpdateInput:
	* Pure virtual function for UpdateInput.
	*/
	virtual void UpdateInput(const float& dt) = 0;

	/* Update:
	* Pure virtual function for Update.
	*/
	virtual void Update(const float& dt) = 0;

	/* Render:
	* Pure virtual function for Render.
	*/
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;

	/* UpdateMouse:
	* Updates mousepositions for mousePosScreen, mousePosWindow and mousePosView.
	*/
	virtual void UpdateMouse();

protected:
	std::stack<State*>* states_;
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool menuMusicOn;
	bool quit;
	bool gameOn;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

#endif