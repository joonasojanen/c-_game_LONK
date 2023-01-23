#include "inventory.h"

Inventory::Inventory(float width, float height, sf::Color color, sf::Font* font) {
	this->invOn = false;
	this->rect.setSize(sf::Vector2f(width, height));
	this->text.setFont(*font);
	this->text.setString("Inventory");
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(10);

}
Inventory::Inventory() {}

Inventory::~Inventory() {}

void Inventory::Render(sf::RenderWindow& window, float x, float y) {
	this->rect.setPosition(sf::Vector2f((x + 98), (y - 90)));
	this->text.setPosition(
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		(this->rect.getPosition().y + 10)
	);

	window.draw(this->rect);
	window.draw(this->text);
}

void Inventory::Update() {
	for (auto i : this->invSlots_) {
		i.second->Update(this->mousePosView);
	}
}
sf::Clock Inventory::CheckOpenInventory(sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && time.asSeconds() > 0.5 && !invOn) {
		this->invOn = true;
		clock.restart();

	}
	return clock;
}

sf::Clock Inventory::CheckCloseInventory(sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();

	if (this->invOn == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && time.asSeconds() > 0.5) {
			this->invOn = false;
			clock.restart();
		}
	}

	return clock;
}

void Inventory::addInventorySlot(std::string name) {


	this->invSlots_[name] = new InventorySlot(30, 30,
		&this->font, name,
		sf::Color(100, 100, 100, 255), sf::Color(200, 70, 70, 200), sf::Color::Black);
}

std::string Inventory::UpdateRemoveInventorySlot(Player player) {
	std::string removed;
	for (auto it : this->invSlots_) {
		if (it.second->isPressed()) {
			if (it.first == "health_potion" || it.first == "health_potion1" || it.first == "health_potion2" || it.first == "health_potion3" || it.first == "health_potion4" || it.first == "health_potion5"
				|| it.first == "health_potion6" || it.first == "health_potion7" || it.first == "health_potion8" || it.first == "health_potion9"
				|| it.first == "health_potion10" || it.first == "health_potion11" || it.first == "health_potion12" || it.first == "health_potion13") {
				if (player.health_ < 150) {
					removed = it.first;
					invSlots_.erase(it.first);
					break;
				}
			}
			if(it.first == "water_potion" || it.first == "water_potion1" || it.first == "water_potion2" || it.first == "water_potion3" || it.first == "water_potion4" || it.first == "water_potion5" || it.first == "water_potion6"
				|| it.first == "water_potion7" || it.first == "water_potion8" || it.first == "water_potion9" || it.first == "water_potion10" || it.first == "water_potion11" || it.first == "water_potion12" || it.first == "water_potion13") {
				removed = it.first;
				invSlots_.erase(it.first);
				break;
			}
		}
	}
	return removed;
}

bool Inventory::invContain(std::string name)
{
	for (auto i : invSlots_) {
		if (i.first == name) {
			return true;
		}
	}
	return false;
}

void Inventory::RenderSlots(sf::RenderWindow* window) {

	int k = 25;
	int j = 40;
	for (auto i : this->invSlots_) {
		if (k % 185 == 0) {
			k = 25;
			j += 40;
		}
		if (j < 201) {
			i.second->Render(window,
				(this->rect.getPosition().x + k),
				(this->rect.getPosition().y + j));
			k += 40;
		}		
	}
}

void Inventory::initFonts() {
	if (!this->font.loadFromFile("Resource Files/fonts/akira.otf")) {
		throw("Inventory -- FONT NOT LOADED");
	}
}

void Inventory::UpdateMouse(sf::RenderWindow& window) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(window);
	this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}