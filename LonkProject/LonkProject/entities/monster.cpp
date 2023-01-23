#include "monster.h"

Monster::Monster() {}

Monster::Monster(sf::Texture* texture, sf::Vector2u imgDirectory, float switchTime, int type, sf::Vector2f spawnPos, int nth, float size, int health, int damage, float attackSpeed, Projectile projectile)
	: animation(texture, imgDirectory, switchTime), imgDirectory_(imgDirectory), type_(type), nth_(nth), size_(size), health_(health), damage_(damage), enemyFireball(projectile) {
	monster_body.setSize(sf::Vector2f(size_, size_));
	monster_body.setTexture(texture);
	monster_body.setPosition(spawnPos);
	latestx = monster_body.getPosition().x;
	latesty = monster_body.getPosition().y;
	this->attackSpeed_ = attackSpeed;
	this->xp = health_ / 2;
}


Monster::~Monster() {
}

void Monster::drawMonster(sf::RenderWindow &window) {
	window.draw(monster_body);
}

sf::RectangleShape Monster::getBody() {
	return monster_body;
}

void Monster::monsterCol(std::list<Monster*> monsterArray_) {
	for (auto i : monsterArray_) {
		if (i->nth_ == this->nth_) continue;
		else {
			if (enemyCollision(monster_body, i->monster_body)) monster_body.setPosition(latestx, latesty);
		}
	}
}


void Monster::updateMonster(sf::RectangleShape body, float dt, std::list<Monster*> monsterArray_) {

	float xDif = (body.getPosition().x + (body.getSize().x)) - (monster_body.getPosition().x + (monster_body.getSize().x));
	float yDif = (body.getPosition().y + (body.getSize().y)) - (monster_body.getPosition().y + (monster_body.getSize().y));
	timeDelay += dt;
	latestx = monster_body.getPosition().x;
	latesty = monster_body.getPosition().y;
	movement = sf::Vector2f(0.0f, 0.0f);
	int i = 0;

	//Chases the player
	if (type_ == 1 || type_ == 3) {
		float range = size_ + 1;
		int i = 0;
		//up
		if (yDif < -range && abs(yDif) > abs(xDif) && yDif > (-192 - size_))
		{
			movement = sf::Vector2f(0.0f, -1.0f);
			monster_body.move(movement);
			row = 3;
			state = 3;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				//right
				if (xDif > (body.getSize().x + 1)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 0;
					state = 1;
				}
				//left
				else if (xDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(-1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 1;
					state = 2;
				}
				//down
				else if (yDif > (body.getSize().x + 1)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, 1.0f);
						monster_body.move(movement);
					}
					row = 2;
					state = 4;
				}
			}
		}
		//right
		else if (xDif > (body.getSize().x + 1) && abs(xDif) > abs(yDif) && xDif < 220)
		{
			movement = sf::Vector2f(1.0f, 0.0f);
			monster_body.move(movement);
			row = 0;
			state = 1;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				down = left = right = up = false;
				//down
				if (yDif > (body.getSize().x + 1)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, 1.0f);
						monster_body.move(movement);
					}
					row = 2;
					state = 4;
				}
				//up
				else if (yDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, -1.0f);
						monster_body.move(movement);
					}
					row = 3;
					state = 3;
				}
				//left
				else if (xDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(-1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 1;
					state = 2;
				}
			}
		}
		//left
		else if (xDif < -range && abs(xDif) > abs(yDif) && xDif > (-192 - size_))
		{
			movement = sf::Vector2f(-1.0f, 0.0f);
			monster_body.move(movement);
			row = 1;
			state = 2;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				//down
				if (yDif > (body.getSize().x + 1)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, 1.0f);
						monster_body.move(movement);
					}
					row = 2;
					state = 4;
				}
				//up
				else if (yDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, -1.0f);
						monster_body.move(movement);
					}
					row = 3;
					state = 3;
				}
				//right
				else if (xDif > (body.getSize().x + 1)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 0;
					state = 1;
				}
			}

		}
		//down
		else if (yDif > (body.getSize().x + 1) && abs(yDif) > abs(xDif) && yDif < 220)
		{
			movement = sf::Vector2f(0.0f, 1.0f);
			monster_body.move(movement);
			row = 2;
			state = 4;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				down = left = right = up = false;
				//right
				if (xDif > (body.getSize().x + 1)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 0;
					state = 1;
				}
				//up
				else if (xDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(-1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 3;
					state = 3;
				}
				//left
				else if (yDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, -1.0f);
						monster_body.move(movement);
					}
					row = 1;
					state = 2;
				}
			}
		}
		else {

			if (row == 0) row = 4;
			else if (row == 1) row = 5;
			else if (row == 2) row = 6;
			else if (row == 3) row = 7;

		}
		animation.update(row, dt, state);
		monster_body.setTextureRect(animation.uvRect);
	}


	else if (type_ == 2 || type_ == 4) {
		float range = size_ + 96;
		piu = false;
		int i = 0;
		curSpeed = speed_;
		float yCoordinate = (yDif / (sqrt(pow(xDif, 2) + pow(yDif, 2))));
		float xCoordinate = (xDif / (sqrt(pow(xDif, 2) + pow(yDif, 2))));
		if (abs(xDif) < 160 && abs(yDif) < 160) {
			if (timeDelay >= attackSpeed_)
			{
				piu = true;
				timeDelay = 0;
				monsterProjectiles.push_back(enemyFireball);
				monsterProjectiles.back().projectile_body.setPosition(monster_body.getPosition().x + (size_ / 2), monster_body.getPosition().y + (size_ / 2));
				monsterProjectiles.back().setStartDirection(sf::Vector2f(xCoordinate, yCoordinate));
			}
			if (timeDelay <= pause)
			{
				curSpeed = 0;
			}
		}
		//up
		if (yDif < -range && abs(yDif) > abs(xDif) && yDif > (-192 - size_))
		{
			movement = sf::Vector2f(0.0f, -1.0f);
			monster_body.move(movement);
			row = 3;
			state = 3;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				//right
				if (xDif > (body.getSize().x + 96)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 0;
					state = 1;
				}
				//left
				else if (xDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(-1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 1;
					state = 2;
				}
				//down
				else if (yDif > (body.getSize().x + 96)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, 1.0f);
						monster_body.move(movement);
					}
					row = 2;
					state = 4;
				}
			}
		}

		//right
		else if (xDif > (body.getSize().x + 96) && abs(xDif) > abs(yDif) && xDif < 220)
		{
			movement = sf::Vector2f(1.0f, 0.0f);
			monster_body.move(movement);
			row = 0;
			state = 1;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				down = left = right = up = false;
				//down
				if (yDif > (body.getSize().x + 96)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, 1.0f);
						monster_body.move(movement);
					}
					row = 2;
					state = 4;
				}
				//up
				else if (yDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, -1.0f);
						monster_body.move(movement);
					}
					row = 3;
					state = 3;
				}
				//left
				else if (xDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(-1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 1;
					state = 2;
				}
			}
		}
		//left
		else if (xDif < -range && abs(xDif) > abs(yDif) && xDif > (-192 - size_))
		{
			movement = sf::Vector2f(-1.0f, 0.0f);
			monster_body.move(movement);
			row = 1;
			state = 2;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				//down
				if (yDif > (body.getSize().x + 96)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, 1.0f);
						monster_body.move(movement);
					}
					row = 2;
					state = 4;
				}
				//up
				else if (yDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, -1.0f);
						monster_body.move(movement);
					}
					row = 3;
					state = 3;
				}
				//right
				else if (xDif > (body.getSize().x + 96)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 0;
					state = 1;
				}
			}

		}
		//down
		else if (yDif > (body.getSize().x + 96) && abs(yDif) > abs(xDif) && yDif < 220)
		{
			movement = sf::Vector2f(0.0f, 1.0f);
			monster_body.move(movement);
			row = 2;
			state = 4;

			monsterCol(monsterArray_);

			if (collision(monster_body)) {
				monster_body.setPosition(latestx, latesty);
				down = left = right = up = false;
				//right
				if (xDif > (body.getSize().x + 96)) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 0;
					state = 1;
				}
				//up
				else if (xDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(-1.0f, 0.0f);
						monster_body.move(movement);
					}
					row = 3;
					state = 3;
				}
				//left
				else if (yDif < -range) {
					if (collision(monster_body)) {
						monster_body.setPosition(latestx, latesty);
					}
					else {
						movement = sf::Vector2f(0.0f, -1.0f);
						monster_body.move(movement);
					}
					row = 1;
					state = 2;
				}
			}
		}
		animation.update(row, dt, state);
		monster_body.setTextureRect(animation.uvRect);
	}
}


void Monster::takeDamage(int damage) {
	health_ -= damage;
}

const int Monster::getType() const {
	return type_;
}

int Monster::getHealth() {
	return health_;
}

int Monster::getDamage() {
	return damage_;
}

float Monster::getSize() {
	return size_;
}

float Monster::getLatestX() {
	return latestx;
}

float Monster::getLatestY() {
	return latesty;
}

int Monster::getXP()
{
	return xp;
}


void Monster::drawProjectiles(sf::RenderWindow& window) {
	for (int i = 0; i < monsterProjectiles.size(); i++) {
		monsterProjectiles[i].Draw(window);
	}
}

Projectile Monster::getProjectile() {
	return enemyFireball;
}

int Monster::getAttackSpeed() {
	return attackSpeed_;
}

void Monster::doorCol(Door door) {
	if (door.doorCollision(monster_body)) {
		monster_body.setPosition(latestx, latesty);
	}
}