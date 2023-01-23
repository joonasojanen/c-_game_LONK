#ifndef _MONSTERCAVE_H_
#define _MONSTERCAVE_H_

#include <list>

#include "monster.h"

class MonsterCave : public Collider {
public:

	/* MonsterCave:
	* Default constructor.
	*/
	MonsterCave() {}

	/* ~MonsterCave:
	* Destructor.
	*/
	~MonsterCave() {}

	/* getMonsters:
	* Getter for monster list.
	*/
	const std::list<Monster*>& getMonsters() const;

	/* addMonster:
	* Adds the monster to the monster list.
	*/
	void addMonster(Monster* monster);

	/* drawAllMonsters:
	* Handles the drawing of the all monsters in the monster array.
	*/
	void drawAllMonsters(sf::RenderWindow &window);

	/* updateAllMonsters:
	* Updates the private variables for every monster in the monster array.
	*/
	void updateAllMonsters(sf::RectangleShape body, float dt);

	/* drawAllMonsterProjectiles:
	* Handles the drawing of the projectiles of every monster in the monster array.
	*/
	void drawAllMonsterProjectiles(sf::RenderWindow &window);

	/* doorCol:
	* Takes Door door as parameter.
	* Checks if monster collides with door.
	*/
	void doorCol(Door door);

	int xpvalue = 0;
	bool bossSpiderKilled = false;
	bool bossWizardKilled = false;
private:
	std::list<Monster*> monsterArray_;
	float latestx;
	float latesty;
};

#endif