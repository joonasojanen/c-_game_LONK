#include "state.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) {
	this->window = window;
	this->states_ = states;
	this->quit = false;
}

State::~State() {}

const bool& State::getQuit() const {
	return this->quit;
}

void State::endState() {

	this->quit = true;
}

void State::UpdateMouse() {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}