#include "chest.h"

Chest::Chest(float width, float height, sf::Color color, sf::Font* font) {
	this->chestOn = false;
	this->rect.setSize(sf::Vector2f(width, height));
	this->rect.setOrigin(sf::Vector2f(0, 0));
	this->chestTexture.loadFromFile("Resource Files/textures/HUDInventory.png");
	this->rect.setTexture(&chestTexture);

	this->text.setFont(*font);
	this->text.setString("Chest");
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(20);


}
Chest::Chest() {}

Chest::~Chest() {}

void Chest::Render(sf::RenderWindow& window, float x, float y) {
	this->rect.setPosition(sf::Vector2f((x - 307), (y - 90)));
	this->text.setPosition(
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		(this->rect.getPosition().y + 10)
	);

	window.draw(this->rect);
	window.draw(this->text);
}

void Chest::Update(sf::RenderWindow& window) {
	for (auto i : this->slots_) {
		i.second->Update(this->mousePosView);
	}
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(window);
	this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}


void Chest::addChestSlot(std::string name) {


	this->slots_[name] = new InventorySlot(30, 30,
		&this->font, name,
		sf::Color(100, 100, 100, 255), sf::Color(200, 70, 70, 200), sf::Color::Black);
}

std::string Chest::UpdateRemoveChestSlot() {
	std::string removed;
	for (auto it : this->slots_) {
		if (it.second->isPressed()) {
			removed = it.first;
			slots_.erase(it.first);
			break;
		}
	}
	return removed;
}

void Chest::RenderSlots(sf::RenderWindow* window) {

	int k = 20;
	int j = 50;
	for (auto i : this->slots_) {
		if (k % 425 == 0) {
			k = 20;
			j += 60;
		}
		i.second->Render(window,
			(this->rect.getPosition().x + k),
			(this->rect.getPosition().y + j));
		k += 45;
	}
}

void Chest::initFonts() {
	if (!this->font.loadFromFile("Resource Files/fonts/akira.otf")) {
		throw("Chest -- FONT NOT LOADED");
	}
}
