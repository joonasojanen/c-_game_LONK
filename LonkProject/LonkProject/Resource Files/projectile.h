#pragma once
#include "SFML\Graphics.hpp"
#include "animation.h"
#include <iostream>


class Projectile
{
public:
	/* Projectile:
	* Default constructor.
	*/
	Projectile();

	/* Projectile:
	*  Assigns the projectile's speed, size, texture and lifetime.
	*/
	Projectile(sf::Texture* texture, sf::Vector2f size, float speed);

	/* ~Projectile:
	* Destructor.
	*/
	~Projectile();

	/* update:
	* Updates the projetile's movement coordinates and moves the shape on the window.
	* decreases lifetime.
	*/
	void update(float deltaTime);

	/* Draw:
	* Draws the projectile shape on the window.
	*/
	void Draw(sf::RenderWindow& window);

	/* setStartDirection:
	* Assigns the startDirection according to the given vector.
	*/
	void setStartDirection(sf::Vector2f startDirection);

	/* getLifetime:
	* Getter for lifetime.
	*/
	int getLifetime();

	sf::RectangleShape projectile_body;
	sf::Vector2f startDirection;
	sf::Vector2f position;

	float speed;
	int lifeTime;
};