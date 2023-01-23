#include "pausemenu.h"

PauseMenu::PauseMenu(float width, float height, sf::Color color, sf::Font* font) {
	this->pauseOn = false;
	this->rect.setSize(sf::Vector2f(width, height));
	this->rect.setFillColor(color);
	this->rect.setOrigin(sf::Vector2f(0, 0));
	this->text.setFont(*font);
	this->text.setString("Pause");
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(35);
}
PauseMenu::PauseMenu() {}

PauseMenu::~PauseMenu() {
	for (auto it = this->pauseButtons_.begin(); it != this->pauseButtons_.end(); ++it) {
		delete it->second;
	}
}

void PauseMenu::initButtons(sf::Font* font) {

	this->pauseButtons_["INVENTORY_BUTTON"] = new Button(0, 0, 200, 50,
		font, "INVENTORY",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->pauseButtons_["OPTIONS_BUTTON"] = new Button(0, 0, 200, 50,
		font, "OPTIONS",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->pauseButtons_["QUIT_BUTTON"] = new Button(0, 0, 200, 50,
		font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->pauseButtons_["RESUME_BUTTON"] = new Button(0, 0, 200, 50,
		font, "RESUME",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->pauseButtons_["INVENTORY_BUTTON"]->text.setCharacterSize(20);
	this->pauseButtons_["OPTIONS_BUTTON"]->text.setCharacterSize(20);
	this->pauseButtons_["QUIT_BUTTON"]->text.setCharacterSize(20);
	this->pauseButtons_["RESUME_BUTTON"]->text.setCharacterSize(20);
}

void PauseMenu::Render(sf::RenderWindow& window, float x, float y) {

	//RENDER PAUSEMENU BACKGROUND AND TEXT

	this->rect.setPosition(sf::Vector2f((x - 200), (y - 190)));
	this->text.setPosition(
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		(this->rect.getPosition().y + 5)
	);

	window.draw(this->rect);
	window.draw(this->text);
}

void PauseMenu::RenderButtons(sf::RenderWindow* window) {

	//RENDER PAUSEMENU BUTTONS

	this->pauseButtons_["RESUME_BUTTON"]->RenderPauseButton(window,
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 4.f)),
		(this->rect.getPosition().y + 70));

	this->pauseButtons_["INVENTORY_BUTTON"]->RenderPauseButton(window,
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 4.f)),
		(this->rect.getPosition().y + 150));

	this->pauseButtons_["OPTIONS_BUTTON"]->RenderPauseButton(window,
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 4.f)),
		(this->rect.getPosition().y + 230));

	this->pauseButtons_["QUIT_BUTTON"]->RenderPauseButton(window,
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 4.f)),
		(this->rect.getPosition().y + 310));

}

int PauseMenu::Update() {
	for (auto i : this->pauseButtons_) {
		i.second->Update(this->mousePosView);
	}

	if (pauseButtons_["RESUME_BUTTON"]->isPressed()) {
		pauseOn = false;
	}

	if (pauseButtons_["QUIT_BUTTON"]->isPressed()) {
		return 1;
	}

	if (pauseButtons_["INVENTORY_BUTTON"]->isPressed()) {
		return 2;
	}
	return 0;
}

sf::Clock PauseMenu::CheckOpenPauseMenu(sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && time.asSeconds() > 1 && !pauseOn) {
		this->pauseOn = true;
		clock.restart();

	}
	return clock;
}

sf::Clock PauseMenu::CheckClosePauseMenu(sf::Clock clock) {
	sf::Time time = clock.getElapsedTime();

	if (this->pauseOn == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && time.asSeconds() > 1) {
			this->pauseOn = false;
			clock.restart();
		}
	}

	return clock;
}

void PauseMenu::initFonts() {
	if (!this->font.loadFromFile("Resource Files/fonts/orange.ttf")) {
		throw("PauseMenu -- FONT NOT LOADED");
	}
}

void PauseMenu::UpdateMouse(sf::RenderWindow& window) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(window);
	this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}