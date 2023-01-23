#ifndef _INV_H_
#define _INV_H_

#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"

#include "inventoryslot.h"
#include "../entities/player.h"

class Inventory {
public:

	/* Inventory:
	* Default constructor.
	*/
	Inventory();

	/* Inventory:
	* the constructor of Inventory class, takes the following parameters:
	* - width @ The width of the window that opens when inventory is rendered.
	* - heigth @ The heigth of the window that opens when inventory is rendered.
	* - color @ NOT USED
	* - font @ Inventory text font
	*/
	Inventory(float width, float height, sf::Color color, sf::Font* font);

	/* ~Inventory:
	* Destructor.
	*/
	~Inventory();

	/* Render:
	* Assigns position of the Inventory in the window and draws the Inventory on the window.
	*/
	void Render(sf::RenderWindow& window, float x, float y);

	/* RenderSlots:
	* Calls Render function for every InventorySlot that assigns slots on the window.
	*/
	void RenderSlots(sf::RenderWindow* window);

	/* Update:
	* Updates every inventoryslot and calls their Update function.
	*/
	void Update();

	/* UpdateMouse:
	* Updates mousepositions for mousePosScreen, mousePosWindow and mousePosView.
	*/
	void UpdateMouse(sf::RenderWindow& window);

	/* CheckOpenInventory:
	* A function that checks if TAB is pressed at right time and sets invOn to true.
	*/
	sf::Clock CheckOpenInventory(sf::Clock clock);

	/* CheckCloseInventory:
	* A function that checks if TAB is pressed at right time and sets invOn to false.
	*/
	sf::Clock CheckCloseInventory(sf::Clock clock);

	/* addInventorySlot:
	* Adds inventorySlot to invSlots_ map with given name.
	*/
	void addInventorySlot(std::string name);

	/* addInventorySlot:
	* Checks the whole invSlots_ map to see if slot is pressed with mouse1.
	* Removes the object if its name is health_potion# or water_potion#.
	* Returns removed slots name.
	*/
	std::string UpdateRemoveInventorySlot(Player player);

	/* invContain:
	* Checks the whole invSlots_ map to see if inventory contais slot with given name.
	*/
	bool invContain(std::string name);

	/* initFonts:
	* Loads font from file.
	*/
	void initFonts();

	bool invOn = false;
	sf::RectangleShape rect;
private:
	sf::Text text;
	sf::Font font;
	std::map<std::string, InventorySlot*> invSlots_;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

};

#endif