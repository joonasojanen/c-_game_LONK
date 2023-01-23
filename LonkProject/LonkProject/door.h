#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include <iostream>

class Door
{
public:

	/* Door:
	* Default constructor.
	*/
	Door();

	/* Door:
	* the constructor of door class, takes the following parameters:
	* - x @ x coordinate of door position.
	* - y @ y coordinate of door position.
	*/
	Door(float x, float y);

	/* ~Door:
	* Destructor.
	*/
	~Door();

	/* Render:
	* assigns position of the door in the window and draws the door shape on the window.
	*/
	void Render(sf::RenderWindow &w);

	/* DoorOpen:
	* Rotates the door shape which depicts the opening of a door and sets DoorOpen flag true.
	*/
	void DoorOpen(bool up);

	/* DoorClose:
	* Rotates the door shape which depicts the closing of a door and sets DoorOpen flag false.
	*/
	void DoorClose(bool up);

	/* DoorCollision:
	* Checks if characters collides with door shape and sets coldected flag true if that happens.
	*/
	bool doorCollision(sf::RectangleShape body1);

	sf::RectangleShape rect;
	sf::Texture doorTexture;

	bool doorOpen = false;

	bool opendoors = false;
	
};

