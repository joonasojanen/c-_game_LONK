#ifndef _GAME_H_
#define _GAME_H_

#include "SFML\Audio.hpp"

#include "states/menustate.h"
#include "states/gamestate.h"


class Game
{
public:

	/* Game:
	* Default constructor.
	* Initialises the gamewindow and gamestate.
	*/
	Game();

	/* ~Game:
	* Virtual Destructor.
	*/
	virtual ~Game();

	/* Run:
	* Runs the mainwindow and calls UpdateDeltaTime, Update and Render functions.
	*/
	void Run();

	/* endApplication:
	* Prints "END"
	*/
	void endApplication();

	/* Update:
	* Calls UpdateSFMLEvent function.
	* Updates the current states.
	* Quits from the program if state is right.
	*/
	void Update();

	/* UpdateSFMLEvents:
	* Updates the mainwindow sfml events.
	*/
	void UpdateSFMLEvents();

	/* UpdateDeltaTime:
	* Resets deltatime.
	*/
	void UpdateDeltaTime();

	/* Render:
	* Renders the specific window according to the top state of the program.
	*/
	void Render();

private:
	float dt;
	sf::Clock clock;

	std::stack<State*> states_;

	sf::RenderWindow *window;
	sf::Event sfEvent;
	void initWindow();
	void initStates();
};

#endif