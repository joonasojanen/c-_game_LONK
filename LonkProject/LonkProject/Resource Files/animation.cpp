#include "animation.h"

Animation::Animation() {}

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::update(int row, float dt, int state)
{
	currentImage.y = row;
	totalTime += dt;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}


	uvRect.top = currentImage.y * uvRect.height;

	if (state == 1)
	{
		uvRect.left = (currentImage.x) * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else if (state == 2)
	{
		uvRect.left = (currentImage.x) * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else if (state == 3)
	{
		uvRect.left = (currentImage.x) * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else if (state == 4)
	{
		uvRect.left = (currentImage.x) * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
}