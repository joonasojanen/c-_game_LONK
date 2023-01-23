#include "projectile.h"
#include "../entities/player.h"

Projectile::Projectile(sf::Texture* texture, sf::Vector2f size, float speed) {
	this->speed = speed;
	projectile_body.setSize(size);
	projectile_body.setTexture(texture);

	lifeTime = speed;
}

Projectile::~Projectile() {
}

Projectile::Projectile() {
}

void Projectile::update(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);
	movement.x += startDirection.x * speed * deltaTime;
	movement.y += startDirection.y * speed * deltaTime;

	projectile_body.move(movement);
	lifeTime--;
}

void Projectile::setStartDirection(sf::Vector2f startDirection) {
	this->startDirection = startDirection;
}

int Projectile::getLifetime() {
	return lifeTime;
}

void Projectile::Draw(sf::RenderWindow& window) {
	window.draw(projectile_body);
}