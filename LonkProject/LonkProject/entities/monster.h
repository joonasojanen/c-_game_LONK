#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <list>
#include "SFML\Graphics.hpp"
#include "../Header Files/collider.h"
#include "../Resource Files/animation.h"
#include "../Resource Files/projectile.h"
#include "../door.h"

class Monster : public Collider {
public:

	/* Monster:
	* Default constructor.
	*/
	Monster();

	/* Monster:
	* the constructor of Monster class, takes the following parameters:
	* - texture @ texture of the monster
	* - imgDirectory @ image of monster animation frames.
	* - switchTime @ time that every animation frame takes
	* - type @ type of the monster
	* - spawnPos @ spawn position coordinates
	* - nth @ nth monster in the array
	* - size @ size of the monster
	* - health @ health of the monster
	* - damage @ damage amount that the monster deals to target
	* - attackspeed
	* - projectile @ projectile texture and size
	*/
	Monster(sf::Texture* texture, sf::Vector2u imgDirectory, float switchTime, int type, sf::Vector2f spawnPos, int nth, float size, int health, int damage, float attackSpeed, Projectile projectile);

	/* ~Monster:
	* Destructor.
	*/
	~Monster();

	/* drawMonster:
	* Draws the monster on the window.
	*/
	void drawMonster(sf::RenderWindow &window);

	/* updateMonster:
	* Updates the position and other private variables of the monster.
	* Handles the collision algorithm and sets default variables depending of the type of the monster.
	*/
	void updateMonster(sf::RectangleShape body, float dt, std::list<Monster*> monsterArray_);

	/* getType:
	* Getter for the monster type.
	*/
	const int getType() const;

	/* getHealth:
	* Getter for monster health.
	*/
	int getHealth();

	/* getDamage:
	* Getter for monster damage.
	*/
	int getDamage();

	/* takeDamage:
	* decreases the amount of damage from monsters health.
	*/
	void takeDamage(int damage);

	/* MonsterCol:
	* Handles the monster collision between other monsters in the array.
	*/
	void monsterCol(std::list<Monster*> monsterArray_);

	/* getBody:
	* Getter for monster shape.
	*/
	sf::RectangleShape getBody();

	/* getSize:
	* Getter for monster size.
	*/
	float getSize();

	/* getLatestX:
	* Getter for latest x coordinate.
	*/
	float getLatestX();

	/* getLatestY:
	* Getter for latest y coordinate.
	*/
	float getLatestY();

	/* getXP:
	* Getter for xp amount.
	*/
	int getXP();

	/* getProjectile:
	* Getter for projectile.
	*/
	Projectile getProjectile();

	/* drawProjectiles:
	* Handles drawing all the projectiles for the monsters that are in the monster array.
	*/
	void drawProjectiles(sf::RenderWindow& window);

	/* getAttackspeed:
	* Getter for monsters attackspeed.
	*/
	int getAttackSpeed();

	/* doorCol:
	* Takes Door door as parameter.
	* Checks if monster collides with door.
	*/
	void doorCol(Door door);

	bool piu = false;
	std::vector<Projectile> monsterProjectiles;

private:
	int attackSpeed_;
	int xp;
	Projectile enemyFireball;
	bool down, up, left, right;
	sf::Vector2f direction;
	sf::Vector2f movement;
	sf::RectangleShape monster_body;
	sf::Texture monsterTexture;
	sf::Texture* texture_;
	sf::Vector2u imageCount;
	Animation animation;
	sf::Vector2u imgDirectory_;
	int type_;
	float size_;
	int nth_;
	int damage_;
	float speed_;
	int health_;
	float timeDelay;
	int row;
	int state;
	float latestx;
	float latesty;
	float pause = .2f;
	float curSpeed;
};

#endif