#include "player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imgDirectory, sf::Vector2f spawnPos, float switchTime, sf::Font* font) :
	animation(texture, imgDirectory, switchTime)
{
	player_body.setSize(sf::Vector2f(28.0f, 28.0f));
	player_body.setTexture(texture);
	player_body.setPosition(spawnPos);
	timeDelay = 0;
	row = 0;
	health_ = 150;
	exp_ = 0;
	strength_ = 1;
	state = 0;
	this->hitDamageFont = font;
	this->hitdamage = 30;

	this->hitDamageText.setFont(*this->hitDamageFont);
	this->hitDamageText.setFillColor(sf::Color::White);
	this->hitDamageText.setCharacterSize(30);
}

Player::Player() {}

void Player::drawPlayer(sf::RenderWindow &window) {
	window.draw(player_body);
}

Player::~Player() {

}

int Player::getHealth() {
	return health_;
}

sf::Vector2f Player::getPosition() {
	return player_body.getPosition();
}

sf::RectangleShape Player::getBody() {
	return player_body;
}

void Player::updatePlayer(MonsterCave* monsters, float dt) {
	playerFoot = false;
	timeDelay += dt;
	curSpeed = speed;
	float push = 0.f;
	bottom = player_body.getPosition().y + player_body.getSize().y;
	left = player_body.getPosition().x;
	right = player_body.getPosition().x + player_body.getSize().x;
	top = player_body.getPosition().y;

	movement = sf::Vector2f(0.0f, 0.0f);

	if (collision(player_body)) player_body.setPosition(latestx, latesty);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		playerFoot = true;
		direction = sf::Vector2f(0.0f, 1.0f);
		movement = sf::Vector2f(0.0f, 1.0f);
		movement.y += speed * dt;
		latestx = player_body.getPosition().x;
		latesty = player_body.getPosition().y - push;
		player_body.move(movement);
		row = 2;
		state = 4;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		playerFoot = true;
		direction = sf::Vector2f(0.0f, -1.0f);
		movement = sf::Vector2f(0.0f, -1.0f);
		movement.y -= speed * dt;
		latestx = player_body.getPosition().x;
		latesty = player_body.getPosition().y + push;
		player_body.move(movement);
		row = 3;
		state = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerFoot = true;
		direction = sf::Vector2f(1.0f, 0.0f);
		movement = sf::Vector2f(1.0f, 0.0f);
		movement.x += speed * dt;
		latestx = player_body.getPosition().x - push;
		latesty = player_body.getPosition().y;
		player_body.move(movement);
		row = 0;
		state = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerFoot = true;
		direction = sf::Vector2f(-1.0f, 0.0f);
		movement = sf::Vector2f(-1.0f, 0.0f);
		movement.x -= speed * dt;
		latestx = player_body.getPosition().x + push;
		latesty = player_body.getPosition().y;
		player_body.move(movement);
		row = 1;
		state = 2;
	}
	else {
		if (row == 1) row = 5;
		else if (row == 2) row = 6;
		else if (row == 3) row = 7;
		else if (row == 0) row = 4;
	}
	enemyCol(monsters);
	animation.update(row, dt, state);
	player_body.setTextureRect(animation.uvRect);

	this->hitdamage = (this->strength_ * 5);
}

sf::Clock Player::updateHit(sf::RenderWindow& window, MonsterCave* monsters, sf::Clock clock, float dt) {
	this->hitDamageString = std::to_string(hitdamage);
	this->hitDamageText.setString(hitDamageString);

	sf::Time time = clock.getElapsedTime();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time.asSeconds() > 0.5) {
		sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		float difMousex = (player_body.getPosition().x + 14) - mousepos.x;
		float difMousey = (player_body.getPosition().y + 14) - mousepos.y;
		float deltatime = dt / 4;
		float deg = (atan2(difMousey, difMousex)) * 180 / 3.14159265;

		if ((deg >= 135 && deg <= 180) || (deg >= -180 && deg < -135)) row = 8;
		else if ((deg >= -45 && deg < 0) || (deg >= 0 && deg < 45)) row = 9;
		else if ((deg >= -135 && deg < -45)) row = 10;
		else if (deg >= 45 && deg < 135) row = 11;
		animation.update(row, deltatime, state);
		player_body.setTextureRect(animation.uvRect);

		for (auto i : monsters->getMonsters()) {
			float difx = player_body.getPosition().x - i->getBody().getPosition().x;
			float dify = player_body.getPosition().y - i->getBody().getPosition().y;
			float difxMouse = mousepos.x - (i->getBody().getPosition().x + i->getSize() / 2);
			float difyMouse = mousepos.y - (i->getBody().getPosition().y + i->getSize() / 2);
			if (abs(difx) < (i->getSize() + 10) && abs(dify) < (i->getSize() + 10) && abs(difxMouse) < (i->getSize()) && abs(difyMouse) < (i->getSize())) {
				i->takeDamage(hitdamage);
				this->hitDamageText.setPosition(mousepos.x - 25, mousepos.y - 30);
				clock.restart();
				hitEnemy = true;
			}
		}

	}
	clock = stopHitAnimation(clock, (dt / 4));
	return clock;
}

sf::Clock Player::stopHitAnimation(sf::Clock clock, float dt) {
	sf::Time time = clock.getElapsedTime();
	if (time.asSeconds() > 1.2) {
		if (row == 8) row = 4;
		else if (row == 9) row = 5;
		else if (row == 10) row = 6;
		else if (row == 11) row = 7;
		animation.update(row, dt, state);
		player_body.setTextureRect(animation.uvRect);
		clock.restart();
	}
	return clock;
}


sf::Clock Player::CheckOpenChest(sf::Clock clock, int &chestCollided) {
	sf::Time time = clock.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && time.asSeconds() > 0.5 && !chestOn)
	{
		chestCollided = chestCollision(player_body);
		if (chestCollided && !chestOn) {
			chestOn = true;
			clock.restart();
		}
	}
	return clock;
}

sf::Clock Player::CheckCloseChest(sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();

	if (this->chestOn == true) {
		if (!chestCollision(player_body) && time.asSeconds() > 0.5) {
			std::cout << "Closed, time:" << time.asSeconds() << "\n";
			this->chestOn = false;
			clock.restart();
		}
	}

	return clock;
}

void Player::enemyCol(MonsterCave* monsters) {
	for (auto i : monsters->getMonsters()) {
		if (enemyCollision(player_body, i->getBody())) player_body.setPosition(latestx, latesty);
	}
}

void Player::doorCol(Door door) {
	opendoors = false;
	float posX = player_body.getPosition().x;
	float posY = player_body.getPosition().y;
	if (door.doorCollision(player_body)) {
		player_body.setPosition(latestx, latesty);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		if (posX > 2432 && posX < 2464 && posY > 1377 && posY < 1569) {
			opendoors = true;
		}
		else if (posX > 352 && posX < 384 && posY > 1377 && posY < 1569) {
			opendoors = true;
		}
	}
}

void Player::takeDamage(int damage) {
	health_ -= damage;
}