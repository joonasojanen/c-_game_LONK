#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>
#include "../Resource Files/animation.h"
#include "../Resource Files/projectile.h"
#include "../chest.h"
#include "monsterCave.h"
#include "../door.h"


class Player : public Collider {
public:

	/* Player:
	* Default constructor.
	*/
	Player();

	/* Player:
	* The constructor of Player class, takes the following parameters:
	* Texture @ Texture of the player.
	* ImgDirectory @ How many images/frames the player animation has.
	* SpawnPos @ Player spawn position in pixels.
	* SwitchTime @ Time that every animation frame takes.
	* Font @ Hitdamage font.
	* Constructor sets player pody size, location, health, exp and strength.
	*/
	Player(sf::Texture* texture, sf::Vector2u imgDirectory, sf::Vector2f spawnPos, float switchTime, sf::Font* font);

	/* ~DeathWindow:
	* Destructor.
	*/
	~Player();

	/* drawPlayer:
	* Handels player drawing to the winbdow.
	* Takes RenderWindow& window as parameter. 
	*/
	void drawPlayer(sf::RenderWindow &window);

	/* getHealth:
	* Returns player health.
	*/
	int getHealth();

	/* updateHit:
	* Returns clock.
	* Takes RenderWindow& window as parameter.
	* Takes MonsterCave monsters as parameter.
	* Takes sf::Clock clock as parameter.
	* Takes float dt as parameter.
	* UpdateHit function checks if the left mouse button is pressed and its been 0.5 seconds from the last press
	* after that it calculates the direction for the player(the player will turn towards the mouse position).
	* and the player makes the hitting animation.
	* After that it loops through the monster array and check if there is monster in range of player and mouse position.
	* If there is monster the monster takes damage and the damage text is printed on the window.
	*/
	sf::Clock updateHit(sf::RenderWindow& window, MonsterCave* monsters, sf::Clock clock, float dt);

	/* stopHitAnimation:
	* Returns clock.
	* Takes sf::Clock clock as parameter.
	* Takes float dt as parameter.
	* Stophitanimation function handles that the hitting animation is only done once when left mouse button is pressed.
	*/
	sf::Clock stopHitAnimation(sf::Clock clock, float dt);

	/* enemyCol:
	* Takes MonsterCave monsters as parameter.
	* Checks if player collides to enemy.
	*/
	void enemyCol(MonsterCave* monsters);

	/* doorCol:
	* Takes Door door as parameter.
	* Checks if player collides with door.
	* Opens door if E is pressed and the player is in specified location and has corrct key.
	*/
	void doorCol(Door door);

	/* getBody:
	* Returns player body.
	*/
	sf::RectangleShape getBody();

	/* updatePlayer:
	* Takes MonsterCave monsters as parameter.
	* Takes float dt as parameter.
	* Moves player to specified direction wich is determined by bressing W:A:S:D buttons.
	* And updates player animation acordinly to that.
.	*/
	void updatePlayer(MonsterCave* monsters, float dt);

	/* takeDamage:
	* Takes int damage as parameter.
	* Decreases health by amount specified by damage.
.	*/
	void takeDamage(int damage);

	/* getPosition:
	* Returns position.
.	*/
	sf::Vector2f getPosition();

	/* CheckOpenChest:
	* Returns clock.
	* Opens the chest if E is pressed next to the chest.
.	*/
	sf::Clock CheckOpenChest(sf::Clock clock, int &chestCollided);

	/* CheckCloseChest:
	* Returns clock.
	* Closes the chest if the player is not next to it after 0.5 seconds.
.	*/
	sf::Clock CheckCloseChest(sf::Clock clock);


	sf::Text hitDamageText;
	bool chestOn = false;
	bool opendoors = false;
	bool piu = false;
	bool hitEnemy = false;
	bool enemyHit = false;
	bool playerFoot = false;

	float bottom, top, left, right;
	int health_;
	int exp_ = 0;
	int strength_ = 1;
	int hitdamage = 30;
	
private:
	Animation animation;
	std::string hitDamageString;
	sf::Font* hitDamageFont;
	sf::Vector2f direction;
	sf::Vector2f movement;
	sf::RectangleShape player_body;
	sf::Texture playerTexture;

	float curSpeed;
	float speed = 80.0;
	float timeDelay;
	float latestx;
	float latesty;
	float pause = .2f;
	int row;
	int state;
};
