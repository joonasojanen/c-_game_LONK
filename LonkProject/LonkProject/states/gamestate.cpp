#include "gamestate.h"


GameState::GameState(sf::RenderWindow* window, std::stack<State*> *states)
	: State(window, states)
{

	if (!map.loadMap("Resource Files/textures/Sprites.png", sf::Vector2u(32, 32), level, 103, 91))
		return;
	this->blurTexture.loadFromFile("Resource Files/textures/blur.png");
	this->blur.setTexture(&blurTexture);
	this->blur.setSize(sf::Vector2f(765.0f, 503.0f));
	InitFireball();
	InitToxicBall();
	InitPlayer();
	InitMonsters();
	InitFonts();
	InitInventory();
	InitChests();
	InitPauseMenu();
	InitDeathWindow();
	InitVictoryWindow();
	InitDoors();
	inventory_.initFonts();

	pauseMenu_.initButtons(&this->font);
	pauseMenu_.initFonts();

	deathWindow_->initButtons(&this->font);
	victoryWindow_->initButtons(&this->font);

	this->damageTakenText.setFont(font);
	this->damageTakenText.setFillColor(sf::Color::Black);
	this->damageTakenText.setCharacterSize(30);


	if (!this->music.openFromFile("Resource Files/music/projectmusic.ogg")) {
		throw("ERROR LOADING MUSIC");
	}
	
	this->combatmusicBuffer.loadFromFile("Resource Files/music/combatmusic.ogg");
	if (!this->combatmusic.openFromFile("Resource Files/music/combatmusic.ogg")) {
		throw("ERROR LOADING MUSIC");
	}
	this->combatmusic.setLoop(true);
	this->combatmusic.setVolume(40);

	this->music.setLoop(true);
	this->music.setVolume(2);
	this->music.play();

	this->footstepsBuffer.loadFromFile("Resource Files/music/footsteps.ogg");

	this->footsteps.setBuffer(footstepsBuffer);
	this->footsteps.setVolume(30);

	this->piuBuffer.loadFromFile("Resource Files/music/piu.ogg");

	this->piu.setBuffer(piuBuffer);
	this->piu.setVolume(20);

	this->slurpBuffer.loadFromFile("Resource Files/music/slurps.ogg");

	this->slurp.setBuffer(slurpBuffer);
	this->slurp.setVolume(50);

	this->moanBuffer.loadFromFile("Resource Files/music/moan.ogg");

	this->moan.setBuffer(moanBuffer);
	this->moan.setVolume(7);

	this->stabBuffer.loadFromFile("Resource Files/music/stab.ogg");

	this->stab.setBuffer(stabBuffer);
	this->stab.setVolume(20);

	this->spidersoundBuffer.loadFromFile("Resource Files/music/spidersound.ogg");

	this->spidersound.setBuffer(spidersoundBuffer);
	this->spidersound.setVolume(5);

	this->KeySoundBuffer.loadFromFile("Resource Files/music/goldkey.ogg");

	this->KeySound.setBuffer(KeySoundBuffer);
	this->KeySound.setVolume(10);

	this->chests_[0]->addChestSlot("health_potion");
	this->chests_[0]->addChestSlot("health_potion1");
	this->chests_[0]->addChestSlot("water_potion");
	this->chests_[0]->addChestSlot("water_potion1");

	this->chests_[1]->addChestSlot("health_potion2");
	this->chests_[1]->addChestSlot("health_potion3");
	this->chests_[1]->addChestSlot("water_potion2");
	this->chests_[1]->addChestSlot("water_potion3");

	this->chests_[2]->addChestSlot("health_potion4");
	this->chests_[2]->addChestSlot("health_potion5");
	this->chests_[2]->addChestSlot("water_potion4");
	this->chests_[2]->addChestSlot("water_potion5");

	this->chests_[3]->addChestSlot("health_potion6");
	this->chests_[3]->addChestSlot("health_potion7");
	this->chests_[3]->addChestSlot("water_potion6");
	this->chests_[3]->addChestSlot("water_potion7");

	this->chests_[4]->addChestSlot("health_potion8");
	this->chests_[4]->addChestSlot("health_potion9");
	this->chests_[4]->addChestSlot("water_potion8");
	this->chests_[4]->addChestSlot("water_potion9");

	this->chests_[5]->addChestSlot("health_potion10");
	this->chests_[5]->addChestSlot("health_potion11");
	this->chests_[5]->addChestSlot("water_potion10");
	this->chests_[5]->addChestSlot("water_potion11");

	this->chests_[6]->addChestSlot("health_potion12");
	this->chests_[6]->addChestSlot("health_potion13");
	this->chests_[6]->addChestSlot("water_potion12");
	this->chests_[6]->addChestSlot("water_potion13");

}

GameState::~GameState() {
	for (int i = 0; i < 7; i++) {
		delete chests_[i];
	}
	delete monsters_;
	delete player_;
	delete deathWindow_;
	delete victoryWindow_;
}

void GameState::Update(const float& dt) {
	sf::Time timeenemy = clockGUI_.getElapsedTime();
	sf::Time timeplayer = clockHit_.getElapsedTime();
	clock_ = pauseMenu_.CheckOpenPauseMenu(clock_);
	clock_ = pauseMenu_.CheckClosePauseMenu(clock_);

	clock_ = inventory_.CheckOpenInventory(clock_);
	clock_ = inventory_.CheckCloseInventory(clock_);

	clock_ = player_->CheckOpenChest(clock_, chestCollided);
	clock_ = player_->CheckCloseChest(clock_);

	updateEnemyMakeDamage();

	this->UpdateInput(dt);
	this->UpdateMouse();

	if (!dead && !victory) player_->updatePlayer(monsters_, dt);


	player_->enemyCol(monsters_);
	monsters_->updateAllMonsters(player_->getBody(), dt);

	inventory_.Update();
	inventory_.UpdateMouse(*this->window);

	this->UpdateChests();

	pauseMenu_.UpdateMouse(*this->window);
	result = pauseMenu_.Update();

	deathWindow_->UpdateMouse(*this->window);
	deadresult = deathWindow_->Update();

	victoryWindow_->UpdateMouse(*this->window);
	victoryresult = victoryWindow_->Update();

	UpdateChestsSlotRemoval();
	UpdateInventorySlotRemoval();
	CheckForCombatMusic();

	player_->doorCol(door1);
	player_->doorCol(door2);
	player_->doorCol(door3);
	player_->doorCol(door4);
	monsters_->doorCol(door3);
	monsters_->doorCol(door4);
	opendoors = player_->opendoors;

	if (opendoors) {
		if (this->inventory_.invContain("gold_key") && this->inventory_.invContain("iron_key")) {
			door1.DoorOpen(true);
			door2.DoorOpen(false);
		}
		else if (this->inventory_.invContain("iron_key")) {
			door3.DoorOpen(true);
			door4.DoorOpen(false);
			player_->opendoors = false;
		}
	}

	clockPlayer_ = player_->updateHit(*this->window, monsters_, clockPlayer_, dt);

	updateEnemyProjectiles(dt);

	hud.Update(player_->health_, player_->exp_, player_->strength_);

	player_->exp_ = monsters_->xpvalue;
	player_->strength_ = (player_->exp_ / 100) + 1;

	if (this->enemyHit && !dead && !victory) {
		if (timeenemy.asSeconds() > 0.7) {
			moan.play();
			clockGUI_.restart();
		}
	}

	if (player_->hitEnemy && !dead && !victory) {
		if (timeplayer.asSeconds() > 0.8) {
			stab.play();
			clockHit_.restart();
		}
	}

	if (monsters_->bossSpiderKilled) {
		KeySound.play();
		inventory_.addInventorySlot("gold_key");
		monsters_->bossSpiderKilled = false;
	}

	if (monsters_->bossWizardKilled) {
		KeySound.play();
		inventory_.addInventorySlot("iron_key");
		monsters_->bossWizardKilled = false;
	}

	if (combat && first) {
		music.pause();
		combatmusic.play();
		first = false;
	}
}

void GameState::Render(sf::RenderTarget* target) {
	this->blur.setPosition(sf::Vector2f((player_->getPosition().x - 382.5f), player_->getPosition().y - 251.5f));
	sf::View followPlayer(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(688.0f, 453.0f));
	followPlayer.setCenter(player_->getPosition().x + 14, player_->getPosition().y + 14);


	this->window->setView(followPlayer);
	this->window->draw(map);
	player_->drawPlayer(*this->window);

	monsters_->drawAllMonsterProjectiles(*this->window);

	door1.Render(*this->window);
	door2.Render(*this->window);
	door3.Render(*this->window);
	door4.Render(*this->window);

	monsters_->drawAllMonsters(*this->window);

	//this->window->draw(blur);

	hud.Render(*this->window, player_->getPosition().x, player_->getPosition().y);


	if (inventory_.invOn) {
		inventory_.Render(*this->window, player_->getPosition().x, player_->getPosition().y);
		inventory_.RenderSlots(this->window);
	}
	if (player_->chestOn) {
		chestindex = chestCollided - 25;
		chests_[chestindex]->Render(*this->window, player_->getPosition().x, player_->getPosition().y);
		chests_[chestindex]->RenderSlots(this->window);
	}
	if (!player_->chestOn) {
		chests_[chestindex]->chestOn = false;
	}

	if (pauseMenu_.pauseOn) {

		pauseMenu_.Render(*this->window, player_->getPosition().x, player_->getPosition().y);
		pauseMenu_.RenderButtons(this->window);
		door1.DoorClose(true);
		door2.DoorClose(false);
	}
	if (player_->hitEnemy) {
		this->window->draw(player_->hitDamageText);
		if (clock_.getElapsedTime().asSeconds() > 2) {
			player_->hitEnemy = false;
			clock_.restart();
		}
	}

	if (this->enemyHit) {
		this->window->draw(this->damageTakenText);
		if (clockEnemy_.getElapsedTime().asSeconds() > 2) {
			this->enemyHit = false;
			clockEnemy_.restart();
		}
	}
	if (player_->health_ <= 0) {
		dead = true;
		deathWindow_->Render(*this->window, player_->getPosition().x, player_->getPosition().y);
		deathWindow_->RenderButton(this->window);
	}

	if (player_->getPosition().x < 320 && player_->getPosition().y > 1377 && player_->getPosition().y < 1569) {
		victory = true;
		victoryWindow_->Render(*this->window, player_->getPosition().x, player_->getPosition().y);
		victoryWindow_->RenderButton(this->window);
	}

}

void GameState::UpdateInput(const float& dt) {
	timer = dt + timer;
	if (result == 1 || deadresult == 1 || victoryresult == 1) {
		this->states_->pop();
		this->states_->push(new MenuState(this->window, this->states_));
		sf::View menuView;
		menuView.reset(sf::FloatRect(0, 0, 765, 503));
		this->window->setView(menuView);
		this->music.stop();
		this->combatmusic.stop();
	}
	else if (result == 2) {
		pauseMenu_.pauseOn = false;
		inventory_.invOn = true;
	}
	if (player_->playerFoot && timer > 0.6 && !dead && !victory) {
		footsteps.play();
		timer = 0;
	}
	for (auto i : monsters_->getMonsters()) {
		if (i->piu && !dead && !victory) {
			piu.play();
		}
		if (spidersoundBool && !dead && !victory) {
			spidersound.play();
		}
	}

}


void GameState::InitPlayer() {
	sf::Vector2f spawnPos(430.0f, 1471.0f);
	this->playerTexture.loadFromFile("Resource Files/textures/CharacterMovement.png");
	player_ = new Player(&playerTexture, sf::Vector2u(3, 12), spawnPos, 0.2f, &this->font);
}

void GameState::InitFireball() {
	this->fireballTexture.loadFromFile("Resource Files/textures/fireball.png");
	Projectile fireball(&fireballTexture, sf::Vector2f(10.0f, 10.0f), 200.0f);
	fireball_ = fireball;
}

void GameState::InitToxicBall() {
	this->toxicballTexture.loadFromFile("Resource Files/textures/toxicball.png");
	Projectile toxicball(&toxicballTexture, sf::Vector2f(10.0f, 10.0f), 200.0f);
	toxicball_ = toxicball;
}

void GameState::InitInventory() {
	this->inventory_ = Inventory(200, 250, sf::Color(80, 80, 80, 255), &this->font);
	this->inventoryTexture.loadFromFile("Resource Files/textures/HUDInventory.png");
	this->inventory_.rect.setTexture(&inventoryTexture);
}

void GameState::InitChests() {
	this->chests_[0] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
	this->chests_[1] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
	this->chests_[2] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
	this->chests_[3] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
	this->chests_[4] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
	this->chests_[5] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
	this->chests_[6] = new Chest(380, 200, sf::Color(80, 80, 80, 255), &this->font);
}

void GameState::InitPauseMenu() {
	this->pauseMenu_ = PauseMenu(400, 407, sf::Color(80, 80, 80, 255), &this->font);
	this->pauseTexture.loadFromFile("Resource Files/textures/HUDInventory.png");
	this->pauseMenu_.rect.setTexture(&pauseTexture);
}

void GameState::InitFonts() {
	if (!this->font.loadFromFile("Resource Files/fonts/akira.otf")) {
		throw("GAME -- FONT NOT LOADED");
	}
}

void GameState::InitDeathWindow() {
	this->deathWindow_ = new DeathWindow(400, 407);
	this->deathWindowTexture_.loadFromFile("Resource Files/textures/DeathScreen.png");
	this->deathWindow_->rect.setTexture(&deathWindowTexture_);
}

void GameState::InitVictoryWindow() {
	this->victoryWindow_ = new VictoryWindow(400, 407);
	this->victoryWindowTexture_.loadFromFile("Resource Files/textures/VictoryWindow.png");
	this->victoryWindow_->rect.setTexture(&victoryWindowTexture_);
}

void GameState::UpdateChestsSlotRemoval() {
	sf::Time time = clockGUI_.getElapsedTime();

	std::string removed;
	if (time.asSeconds() > 0.5) {
		for (auto it : chests_) {
			removed = it.second->UpdateRemoveChestSlot();
			if (removed.length() != 0) {
				inventory_.addInventorySlot(removed);
				clockGUI_.restart();
			}
				
		}
		
	}
}

void GameState::UpdateInventorySlotRemoval() {
	sf::Time time = clockGUI_.getElapsedTime();

	std::string removed;
	if (time.asSeconds() > 1) {
		removed = inventory_.UpdateRemoveInventorySlot(*player_);
		if (removed == "health_potion" || removed == "health_potion1" || removed == "health_potion2" || removed == "health_potion3" || removed == "health_potion4" || removed == "health_potion5" ||
			removed == "health_potion6" || removed == "health_potion7" || removed == "health_potion8" || removed == "health_potion9" || removed == "health_potion10" || removed == "health_potion11" || removed == "health_potion12" || removed == "health_potion13") {
			if (player_->health_ < 150) {
				player_->health_ += 40;
				slurp.play();
				if (player_->health_ > 150) {
					player_->health_ = 150;
				}
			}
			clockGUI_.restart();
		}
		if (removed == "water_potion" || removed == "water_potion1" || removed == "water_potion2" || removed == "water_potion3" || removed == "water_potion4" || removed == "water_potion5" || 
			removed == "water_potion6" || removed == "water_potion7" || removed == "water_potion8" || removed == "water_potion9" || removed == "water_potion10" || removed == "water_potion11" || removed == "water_potion12" || removed == "water_potion13") {
			monsters_->xpvalue += 90;
			clockGUI_.restart();
		}
	}
}

void GameState::UpdateChests() {
	for (auto it : chests_) {
		it.second->Update(*this->window);
	}
}

void GameState::CheckForCombatMusic() {
	combat = false;
	if (player_->getPosition().x > 1870 && player_->getPosition().x < 2950 && player_->getPosition().y > 1220 && player_->getPosition().y < 1700) {
		if (!combat) {
			combat = true;
		}
	}
}


void GameState::InitDoors() {
	door1 = Door(320, 1377);
	door2 = Door(320, 1473);
	door3 = Door(2464, 1377);
	door4 = Door(2464, 1473);
	doorUpTexture.loadFromFile("Resource Files/textures/doorUp.png");
	doorDownTexture.loadFromFile("Resource Files/textures/doorDown.png");
	door1.rect.setTexture(&doorDownTexture);
	door2.rect.setTexture(&doorUpTexture);
	door3.rect.setTexture(&doorDownTexture);
	door4.rect.setTexture(&doorUpTexture);

}

void GameState::updateEnemyMakeDamage() {
	timedelay += enemyDt;
	for (auto i : monsters_->getMonsters()) {
		if (timedelay >= i->getAttackSpeed()) {
			spidersoundBool = false;
			float difx = player_->getBody().getPosition().x - (i->getBody().getPosition().x + (i->getSize() / 2));
			float dify = player_->getBody().getPosition().y - (i->getBody().getPosition().y + (i->getSize() / 2));
			if (abs(difx) < (i->getSize() + 10) && abs(dify) < (i->getSize() + 10) && (i->getType() == 1 || i->getType() == 3)) {
				spidersoundBool = true;
				player_->takeDamage(i->getDamage());
				damageTakenString = std::to_string(i->getDamage());
				damageTakenText.setString(damageTakenString);
				damageTakenText.setPosition(player_->getPosition().x - 15, player_->getPosition().y - 30);
				this->enemyHit = true;
				timedelay = 0;
			}
		}
	}
}

void GameState::updateEnemyProjectiles(float dt) {
	bool col1 = false, col2 = false;
	for (auto i : monsters_->getMonsters()) {

		for (std::size_t j = 0; j < i->monsterProjectiles.size(); j++) {
			col1 = monsters_->collision(i->monsterProjectiles[j].projectile_body);
			col2 = monsters_->enemyCollision(i->monsterProjectiles[j].projectile_body, player_->getBody());
			if (col2) {
				player_->takeDamage(i->getDamage());
				damageTakenString = std::to_string(i->getDamage());
				damageTakenText.setString(damageTakenString);
				damageTakenText.setPosition(player_->getPosition().x - 15, player_->getPosition().y - 30);
				this->enemyHit = true;
			}
			if (col1 || col2 || i->monsterProjectiles[j].lifeTime <= 0) {
				i->monsterProjectiles.erase(i->monsterProjectiles.begin() + j);
			}
		}
		for (std::size_t j = 0; j < i->monsterProjectiles.size(); j++) {
			i->monsterProjectiles[j].update(dt);
		}
	}
}

void GameState::InitMonsters() {
	this->enemyDt = clockEnemyHit_.restart().asSeconds();
	this->boss1Texture.loadFromFile("Resource Files/textures/SpiderAnimation.png");
	this->wizardBlueTexture.loadFromFile("Resource Files/textures/WizardBlue.png");
	this->wizardGreenTexture.loadFromFile("Resource Files/textures/WizardGreen.png");

	sf::Vector2f spawnPosOikeeAla1(2700.0f, 2000.0f);
	sf::Vector2f spawnPosOikeeAla2(2850.0f, 2300.0f);
	sf::Vector2f spawnPosOikeeAla3(2750.0f, 2500.0f);
	Monster* wizard1 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosOikeeAla1, 1, 32, 100, 10, 1, fireball_);
	Monster* spider1 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosOikeeAla2, 2, 32, 50, 20, 1, fireball_);
	Monster* wizard2 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosOikeeAla3, 3, 32, 50, 5, 1, fireball_);
	this->monsters_->addMonster(wizard1);
	this->monsters_->addMonster(spider1);
	this->monsters_->addMonster(wizard2);

	sf::Vector2f spawnPosVelhohuone(2100.0f, 1950.0f);
	Monster* wizard3 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosVelhohuone, 4, 32, 100, 2, 1, fireball_);
	this->monsters_->addMonster(wizard3);

	sf::Vector2f spawnPosIsoHuone1(1000.0f, 550.0f);
	sf::Vector2f spawnPosIsoHuone2(1000.0f, 300.0f);
	sf::Vector2f spawnPosIsoHuone3(1200.0f, 300.0f);
	sf::Vector2f spawnPosIsoHuone4(1600.0f, 500.0f);
	Monster* wizard4 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosIsoHuone1, 5, 32, 100, 15, 1, fireball_);
	Monster* spider2 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoHuone2, 6, 32, 50, 10, 1, fireball_);
	Monster* spider3 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoHuone3, 7, 32, 50, 10, 1, fireball_);
	Monster* spider4 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoHuone4, 8, 32, 50, 10, 1, fireball_);
	this->monsters_->addMonster(wizard4);
	this->monsters_->addMonster(spider2);
	this->monsters_->addMonster(spider3);
	this->monsters_->addMonster(spider4);

	sf::Vector2f spawnPosNelio(1650.f, 1130.f);
	Monster* wizard5 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosNelio, 9, 32, 80, 25, 2, fireball_);
	this->monsters_->addMonster(wizard5);

	sf::Vector2f spawnPosIsoOikeeYla1(2400.f, 800.f);
	sf::Vector2f spawnPosIsoOikeeYla2(2400.f, 500.f);
	sf::Vector2f spawnPosIsoOikeeYla3(2815.f, 555.f);
	sf::Vector2f spawnPosIsoOikeeYla4(2850.f, 700.f);
	sf::Vector2f spawnPosIsoOikeeYla5(2850.f, 1000.f);
	Monster* spider5 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoOikeeYla1, 10, 32, 50, 10, 2, fireball_);
	Monster* spider6 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoOikeeYla2, 11, 64, 50, 10, 1, fireball_);
	Monster* spider7 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoOikeeYla3, 12, 64, 50, 10, 2, fireball_);
	Monster* wizard6 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosIsoOikeeYla4, 13, 32, 100, 10, 1, fireball_);
	Monster* spider8 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosIsoOikeeYla5, 14, 32, 50, 10, 1, fireball_);
	this->monsters_->addMonster(spider5);
	this->monsters_->addMonster(spider6);
	this->monsters_->addMonster(spider7);
	this->monsters_->addMonster(wizard6);
	this->monsters_->addMonster(spider8);

	sf::Vector2f spawnPosRistiHuone(950.f, 950.f);
	Monster* wizard7 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosRistiHuone, 15, 32, 50, 20, 5, fireball_);
	this->monsters_->addMonster(wizard7);

	sf::Vector2f spawnPosKirjasto1(450.f, 350.f);
	sf::Vector2f spawnPosKirjasto2(650.f, 350.f);
	sf::Vector2f spawnPosKirjasto3(700.f, 500.f);
	sf::Vector2f spawnPosKirjasto4(450.f, 500.f);
	Monster* spider9 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosKirjasto1, 16, 20, 30, 6, 2, fireball_);
	Monster* spider10 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosKirjasto2, 17, 20, 30, 6, 2, fireball_);
	Monster* spider11 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosKirjasto3, 18, 20, 30, 6, 2, fireball_);
	Monster* spider12 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosKirjasto4, 19, 20, 30, 6, 2, fireball_);
	this->monsters_->addMonster(spider9);
	this->monsters_->addMonster(spider10);
	this->monsters_->addMonster(spider11);
	this->monsters_->addMonster(spider12);


	sf::Vector2f spawnPosBoss(2663.0f, 1405.0f);
	sf::Vector2f spawnPosPikkuHamis1(2100.0f, 1400.0f);
	sf::Vector2f spawnPosPikkuHamis2(2300.0f, 1300.0f);
	sf::Vector2f spawnPosPikkuHamis3(2400.0f, 1400.0f);
	sf::Vector2f spawnPosPikkuHamis4(2400.0f, 1550.0f);
	sf::Vector2f spawnPosPikkuHamis5(2300.0f, 1650.0f);
	sf::Vector2f spawnPosPikkuHamis6(2200.0f, 1600.0f);
	sf::Vector2f spawnPosPikkuHamis7(2050.0f, 1515.0f);
	Monster* spiderBoss = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 3, spawnPosBoss, 20, 128, 500, 25, 3, fireball_);
	Monster* spider13 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosPikkuHamis1, 21, 64, 50, 5, 1, fireball_);
	Monster* spider14 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosPikkuHamis2, 22, 64, 50, 5, 1, fireball_);
	Monster* spider15 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosPikkuHamis3, 23, 20, 50, 5, 1, fireball_);
	Monster* wizard8 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, spawnPosPikkuHamis4, 24, 32, 100, 20, 1, fireball_);
	Monster* spider16 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosPikkuHamis5, 25, 20, 50, 5, 1, fireball_);
	Monster* spider17 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosPikkuHamis6, 26, 20, 50, 5, 1, fireball_);
	Monster* spider18 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, spawnPosPikkuHamis7, 27, 20, 50, 5, 1, fireball_);
	this->monsters_->addMonster(spiderBoss);
	this->monsters_->addMonster(spider13);
	this->monsters_->addMonster(spider14);
	this->monsters_->addMonster(spider15);
	this->monsters_->addMonster(wizard8);
	this->monsters_->addMonster(spider16);
	this->monsters_->addMonster(spider17);
	this->monsters_->addMonster(spider18);

	sf::Vector2f wizardBossSpawn(2030.0f, 400);
	sf::Vector2f wizardBossSpawnSpider1(1925.0f, 488);
	sf::Vector2f wizardBossSpawnSpider2(1915.0f, 327);
	Monster* wizardBoss = new Monster(&wizardGreenTexture, sf::Vector2u(1, 4), 0.2f, 4, wizardBossSpawn, 28, 64, 200, 20, 2, toxicball_);
	Monster* spider19 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, wizardBossSpawnSpider1, 29, 20, 50, 5, 1, fireball_);
	Monster* spider20 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, wizardBossSpawnSpider2, 30, 20, 50, 5, 1, fireball_);
	this->monsters_->addMonster(wizardBoss);
	this->monsters_->addMonster(spider19);
	this->monsters_->addMonster(spider20);

	sf::Vector2f minRoom(1025.0f, 2166.0f);
	Monster* wizard9 = new Monster(&wizardBlueTexture, sf::Vector2u(1, 4), 0.2f, 2, minRoom, 31, 32, 75, 5, 1, fireball_);
	this->monsters_->addMonster(wizard9);

	sf::Vector2f garden(542.0f, 2140.0f);
	Monster* spider21 = new Monster(&boss1Texture, sf::Vector2u(3, 8), 0.2f, 1, garden, 32, 32, 40, 5, 1, fireball_);
	this->monsters_->addMonster(spider21);
}