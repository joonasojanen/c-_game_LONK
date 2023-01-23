#include "door.h"

Door::Door() {}

Door::Door(float x, float y)
{
	this->rect.setPosition(sf::Vector2f(x, y));
	this->rect.setSize(sf::Vector2f(32, 96));
}
Door::~Door() {}

void Door::Render(sf::RenderWindow & w)
{
	w.draw(this->rect);
}

void Door::DoorOpen(bool up) {

	if (up && !doorOpen) {
		this->rect.rotate(-90);
		this->rect.setPosition(this->rect.getPosition().x + 5, this->rect.getPosition().y + 20);
		doorOpen = true;
	}
	else if (!up && !doorOpen){
		this->rect.rotate(90);
		this->rect.setPosition(this->rect.getPosition().x + 100, this->rect.getPosition().y + 72);
		doorOpen = true;
	}
}

void Door::DoorClose(bool up) {
	if (up && doorOpen) {
		this->rect.rotate(90);
		this->rect.setPosition(this->rect.getPosition().x - 5, this->rect.getPosition().y - 20);
		doorOpen = false;
	}
	else if (!up && doorOpen) {
		this->rect.rotate(-90);
		this->rect.setPosition(this->rect.getPosition().x - 100, this->rect.getPosition().y - 72);
		doorOpen = false;
	}
}

bool Door::doorCollision(sf::RectangleShape body1) {
	bool coldetected = false;

	if (body1.getGlobalBounds().intersects(this->rect.getGlobalBounds())) {
		coldetected = true;
	}
	return coldetected;
}

