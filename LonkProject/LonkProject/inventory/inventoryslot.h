#ifndef _INV_SLOT_
#define _INV_SLOT_

#include "../Resource Files/button.h"

/* enum slot_states:
* Assign states of one slot.
*/
enum slot_states { slot_idle = 0, slot_touch, slot_pressed };

class InventorySlot {
public:

	/* InventorySlot:
	* the constructor of InventorySlot class, takes the following parameters:
	* - width @ The width of the regtangle that shows when inventorySlot is rendered.
	* - heigth @ The heigth of the regtangle that shows when inventorySlot is rendered.
	* - font @ NOT USED.
	* - text @ Name of the slot.
	* - idleColor @ Color when slot is in idle state.
	* - touchColor @ Color when mousecursor is hovered on the slot.
	* - pressColor @ Color when mouse1 is pressed on the slot.
	*/
	InventorySlot(float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color touchColor, sf::Color pressColor);

	/* ~InventorySlot:
	* Destructor.
	*/
	~InventorySlot();

	/* Render:
	* Assigns position of the InventorySlot in the window and draws the InventorySlot on the window.
	*/
	void Render(sf::RenderTarget* target, float x, float y);

	/* Update:
	* Updates slots state according to mouses position on screen.
	*/
	void Update(const sf::Vector2f mousePos);

	/* isPressed:
	* Returns true if slots state is slot_pressed.
	*/
	const bool isPressed() const;

private:
	int slotState;
	sf::Texture slotTexture;
	sf::RectangleShape rect;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color touchColor;
	sf::Color pressColor;
};

#endif