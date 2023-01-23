#include "game.h"

Game::Game() {

	this->initWindow();
	this->initStates();

}

Game::~Game() {
	delete this->window;

	while (!this->states_.empty()) {
		delete this->states_.top();
		this->states_.pop();
	}
}

void Game::initWindow() {
	//const unsigned WINDOW_HEIGHT = 600;
	//const unsigned WINDOW_WIDTH = 1066;

	const unsigned WINDOW_HEIGHT = 503;
	const unsigned WINDOW_WIDTH = 765;

	sf::VideoMode window_bounds(WINDOW_WIDTH, WINDOW_HEIGHT);

	this->window = new sf::RenderWindow(window_bounds, "LONK");

	this->window->setFramerateLimit(60);
	this->window->setKeyRepeatEnabled(false);
}

void Game::initStates() {

	this->states_.push(new MenuState(this->window, &this->states_));

}

void Game::Run() {
	while (this->window->isOpen())
	{
		this->UpdateDeltaTime();
		this->Update();
		this->Render();
	}
}

void Game::endApplication() {
	std::cout << "END" << "\n";
}

void Game::Update() {
	this->UpdateSFMLEvents();

	if (!this->states_.empty()) {
		this->states_.top()->Update(this->dt);

		if (this->states_.top()->getQuit()) {

			delete this->states_.top();
			this->states_.pop();
		}
	}

	//Quit whole app
	else {
		this->endApplication();
		this->window->close();
	}
}

void Game::UpdateSFMLEvents() {
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed) {
			this->window->close();
		}

	}
}

void Game::UpdateDeltaTime() {
	this->dt = this->clock.restart().asSeconds();
}

void Game::Render() {

	this->window->clear();

	if (!this->states_.empty()) {
		this->states_.top()->Render(this->window);
	}

	this->window->display();

}