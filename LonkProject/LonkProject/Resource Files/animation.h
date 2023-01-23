#pragma once
#include "SFML\Graphics.hpp"

class Animation
{
public:
	/* Animation:
	* Default constructor.
	*/
	Animation();

	/* Animation:
	* Assigns the private variables according to parameters.
	* Assigns totaltime and currentimage to 0.
	*/
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	/* ~Animation:
	* Destructor
	*/
	~Animation();

	/* update:
	* Handles the animation frames by incrementing the currentImage.y when switchTime has been elapsed.
	* Resets the animation after last frame in the row.
	*/
	void update(int row, float deltaTime, int state);

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};