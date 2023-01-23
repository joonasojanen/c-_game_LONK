#ifndef _FIGHT_H_
#define _FIGHT_H_

#include "../entities/player.h"
#include "../entities/monsterCave.h"
#include "SFML\Graphics.hpp"


sf::Clock updateMakeDamage(Player &player, MonsterCave &monsters, sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();
	if (time.asSeconds() > 5) {
		for (auto i : monsters.getMonsters()) {
			float difx = player.getBody().getPosition().x - i->getBody().getPosition().x;
			float dify = player.getBody().getPosition().y - i->getBody().getPosition().y;
			if (abs(difx) < (i->getSize() + 10) && abs(dify) < (i->getSize() + 10)) {
				player.takeDamage(i->getDamage());
			}
		}
		clock.restart();
	}
	return clock;
}

void updateProjectiles(float dt, Player &player, MonsterCave &monsters) {
	bool col1 = false, col2 = false;
	for (auto i : monsters.getMonsters()) {

		for (int j = 0; j < i->monsterProjectiles.size(); j++) {
			col1 = monsters.collision(i->monsterProjectiles[j].projectile_body);
			col2 = monsters.enemyCollision(i->monsterProjectiles[j].projectile_body, player.getBody());
			if (col2) {
				player.takeDamage(i->monsterProjectiles[j].damage);
			}
			if (col1 || col2 || i->monsterProjectiles[j].lifeTime <= 0) {
				i->monsterProjectiles.erase(i->monsterProjectiles.begin() + j);
			}
		}
		for (int j = 0; j < i->monsterProjectiles.size(); j++) {
			i->monsterProjectiles[j].update(dt);
		}
	}
}


#endif