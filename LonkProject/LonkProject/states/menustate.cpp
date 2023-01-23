#include "menustate.h"

void MenuState::initButtons() {
	this->buttons_["START_BUTTON"] = new Button(302, 162, 160, 55,
		&this->font, "PLAY",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->buttons_["OPTIONS_BUTTON"] = new Button(302, 252, 160, 55,
		&this->font, "OPTIONS",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->buttons_["QUIT_BUTTON"] = new Button(302, 342, 160, 55,
		&this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);
}

void MenuState::initFonts() {
	if (!this->font.loadFromFile("Resource Files/fonts/akira.otf")) {
		throw("MENU -- FONT NOT LOADED");
	}
}

MenuState::MenuState(sf::RenderWindow* window, std::stack<State*> *states)
	: State(window, states) {

	this->initFonts();
	this->initButtons();

	this->background_.setSize(sf::Vector2f(765, 503));
	this->background_.setFillColor(sf::Color(128, 128, 128, 255));
	this->background_.setOrigin(sf::Vector2f(0, 0));
	this->backgroundTexture.loadFromFile("Resource Files/textures/Background.png");
	this->background_.setTexture(&backgroundTexture);

	if (!music.openFromFile("Resource Files/music/projectmusic.ogg")) {
		throw("ERROR LOADING MUSIC");
	}
	menuMusicOn = true;
	this->music.setLoop(true);
	this->music.setVolume(5);
	this->music.play();

}

MenuState::~MenuState() {

	for (auto it = this->buttons_.begin(); it != this->buttons_.end(); ++it) {
		delete it->second;
	}
}

void MenuState::Update(const float& dt) {
	this->UpdateInput(dt);
	this->UpdateMouse();
	this->UpdateButtons();

}

void MenuState::Render(sf::RenderTarget* target) {
	if (!target) {
		target = this->window;
	}
	target->draw(this->background_);
	this->RenderButtons(target);
}

void MenuState::RenderButtons(sf::RenderTarget* target) {
	for (auto i : this->buttons_) {
		i.second->Render(target);
	}
}


void MenuState::UpdateInput(const float& dt) {

}

void MenuState::UpdateButtons() {
	for (auto i : this->buttons_) {
		i.second->Update(this->mousePosView);
	}

	if (buttons_["START_BUTTON"]->isPressed()) {
		this->states_->pop();
		this->states_->push(new GameState(this->window, this->states_));

		music.stop();
	}

	if (buttons_["QUIT_BUTTON"]->isPressed()) {
		this->endState();
	}
}


