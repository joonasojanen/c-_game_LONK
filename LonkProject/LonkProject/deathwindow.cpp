#include "deathwindow.h"
DeathWindow::DeathWindow() {}

DeathWindow::DeathWindow(float width, float height) {
	this->rect.setSize(sf::Vector2f(width, height));
}

DeathWindow::~DeathWindow() {
	
}

void DeathWindow::initButtons(sf::Font* font) {

	this->returnButton = new Button(0, 0, 200, 50,
		font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(200, 70, 70, 200), sf::Color::Black);

	this->returnButton->text.setCharacterSize(20);

}

void DeathWindow::Render(sf::RenderWindow& window, float x, float y) {

	//RENDER DeathWindow BACKGROUND AND TEXT

	this->rect.setPosition(sf::Vector2f((x - 200), (y - 190)));

	window.draw(this->rect);

}

void DeathWindow::RenderButton(sf::RenderWindow* window) {

	//RENDER DeathWindow BUTTONS

	this->returnButton->RenderPauseButton(window,
		(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 4.f)),
		(this->rect.getPosition().y + 200));

}

int DeathWindow::Update() {

	this->returnButton->Update(this->mousePosView);

	if (returnButton->isPressed()) {
		return 1;
	}
	return 0;
}


void DeathWindow::initFonts() {
	if (!this->font.loadFromFile("Resource Files/fonts/akira.otf")) {
		throw("DeathWindow -- FONT NOT LOADED");
	}
}

void DeathWindow::UpdateMouse(sf::RenderWindow& window) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(window);
	this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}