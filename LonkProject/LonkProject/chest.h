#pragma once

#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"

#include "inventory/inventoryslot.h"

class Chest
{
public:
	/* Chest:
	* Default constructor.
	*/
	Chest();

	/* Chest:
	* the constructor of chest class, takes the following parameters:
	* - width @ The width of the window that opens when chest is opened.
	* - heigth @ The heigth of the window that opens when chest is opened.
	* - color @ NOT USED
	* - font @ chest text font
	*/
	Chest(float width, float height, sf::Color color, sf::Font* font);

	/* ~Chest:
	* Destructor.
	*/
	~Chest();

	/* Render:
	* Assigns the position of the chest window according to given x and y coordinates and draws the shape of the chest.
	*/
	void Render(sf::RenderWindow& window, float x, float y);

	/* RenderSlots:
	* Assigns the position of the chest slots and and draws the shapes of the slots.
	*/
	void RenderSlots(sf::RenderWindow* window);

	/* Update:
	* Updates mousepositions for mousePosScreen, mousePosWindow and mousePosView.
	*/
	void Update(sf::RenderWindow& window);

	/* addChestSlot:
	* Adds new slot to map according to slotname and initialises the size, font, color
	* and position of the slot.
	*/
	void addChestSlot(std::string name);
	
	/* initFonts:
	* Loads font from file.
	*/
	void initFonts();

	/* UpdateRemoveChestSlot:
	* Finds specific slot from map according to mouseposition and erases the slot
	* and its details from map.
	* returns the name of the removed item.
	*/
	std::string UpdateRemoveChestSlot();

	bool chestOn = false;

private:
	sf::RectangleShape rect;
	sf::Texture chestTexture;
	sf::Text text;
	sf::Font font;
	std::map<std::string, InventorySlot*> slots_;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

