#include "inventoryslot.h"

InventorySlot::InventorySlot(float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color touchColor, sf::Color pressColor) {
	this->slotState = slot_idle;

	this->rect.setPosition(sf::Vector2f(0, 0));
	this->rect.setSize(sf::Vector2f(width, height));
	if (text == "bronze_key") {
		this->slotTexture.loadFromFile("Resource Files/textures/Bronze_Key.png");
		this->rect.setTexture(&slotTexture);
	}
	if (text == "gold_key") {
		this->slotTexture.loadFromFile("Resource Files/textures/Gold_Key.png");
		this->rect.setTexture(&slotTexture);
	}
	if (text == "iron_key") {
		this->slotTexture.loadFromFile("Resource Files/textures/Iron_Key.png");
		this->rect.setTexture(&slotTexture);
	}
	if (text == "health_potion" || text == "health_potion1" || text == "health_potion2" || text == "health_potion3" || text == "health_potion4" || text == "health_potion5" 
		|| text == "health_potion6" || text == "health_potion7" || text == "health_potion8" || text == "health_potion9" || text == "health_potion10" || text == "health_potion11" || text == "health_potion12" || text == "health_potion13") {
		this->slotTexture.loadFromFile("Resource Files/textures/HealthPotion.png");
		this->rect.setTexture(&slotTexture);
	}

	if (text == "water_potion" || text == "water_potion1" || text == "water_potion2" || text == "water_potion3" || text == "water_potion4" || text == "water_potion5"
		|| text == "water_potion6" || text == "water_potion7" || text == "water_potion8" || text == "water_potion9" || text == "water_potion10" || text == "water_potion11" || text == "water_potion12" || text == "water_potion13") {
		this->slotTexture.loadFromFile("Resource Files/textures/WaterPotion.png");
		this->rect.setTexture(&slotTexture);
	}

	this->font = font;
	this->idleColor = idleColor;
	this->touchColor = touchColor;
	this->pressColor = pressColor;

	this->rect.setFillColor(this->idleColor);

}

InventorySlot::~InventorySlot() {}

void InventorySlot::Render(sf::RenderTarget* target, float x, float y) {

	this->rect.setPosition(x, y);
	this->text.setPosition(x - 10, y + 40);
	target->draw(this->rect);
	//target->draw(this->text);
}

void InventorySlot::Update(const sf::Vector2f mousePos) {

	this->slotState = slot_idle;

	if (this->rect.getGlobalBounds().contains(mousePos)) {
		this->slotState = slot_touch;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->slotState = slot_pressed;
		}
	}

	switch (this->slotState) {
	case slot_idle:
		this->rect.setFillColor(this->idleColor);
		break;

	case slot_touch:
		this->rect.setFillColor(this->touchColor);
		break;

	case slot_pressed:
		this->rect.setFillColor(this->pressColor);
		break;

	default:
		this->rect.setFillColor(this->idleColor);
		break;
	}
}

const bool InventorySlot::isPressed() const {
	if (this->slotState == slot_pressed) {
		return true;
	}
	else {
		return false;
	}
}
