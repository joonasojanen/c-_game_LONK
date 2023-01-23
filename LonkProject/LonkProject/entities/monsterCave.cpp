#include "monsterCave.h"


const std::list<Monster*>& MonsterCave::getMonsters() const{
    return monsterArray_;
}


void MonsterCave::addMonster(Monster* monster) {
    monsterArray_.push_back(monster);
}


void MonsterCave::drawAllMonsters(sf::RenderWindow &window) {
    for (auto i : this->monsterArray_) {
        i->drawMonster(window);
    }
}


void MonsterCave::updateAllMonsters(sf::RectangleShape body, float dt) {
	if (monsterArray_.size() > 0) {
		auto it = monsterArray_.begin();
		for (auto i : this->monsterArray_) {
			if (i->getHealth() <= 0) {
				xpvalue += i->getXP();
				if (i->getType() == 3) {
					bossSpiderKilled = true;
				}
				if (i->getType() == 4) {
					bossWizardKilled = true;
				}
				monsterArray_.erase(it);
				break;
			}
			it++;
		}
	}
	for (auto i : this->monsterArray_) {
		i->updateMonster(body, dt, monsterArray_);
	}
}

void MonsterCave::drawAllMonsterProjectiles(sf::RenderWindow &window) {
	for (auto i : this->monsterArray_) {
		i->drawProjectiles(window);
	}
}

void MonsterCave::doorCol(Door door) {
	for (auto i : this->monsterArray_) {
		i->doorCol(door);
	}
}