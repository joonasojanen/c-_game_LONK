#include "game.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

int main() {

	srand(time(0));

	Game game;

	game.Run();

	return 0;
}