#include "SFML\Graphics.hpp"
#include <iostream>
#include "../Resource Files/level.h"



class Collider
{
public:
	Collider() { }

	~Collider() {
	}

	bool collision(sf::RectangleShape body) {
		bool coldetected = false;
		float bottom = body.getPosition().y + body.getSize().y;
		float left = body.getPosition().x;
		float right = body.getPosition().x + body.getSize().x;
		float top = body.getPosition().y;
		for (int i = 0; i < 91; i++)
		{
			for (int j = 0; j < 103; j++)
			{
				if (world[i][j] == 1 || world[i][j] == 24 || world[i][j] == 25 || world[i][j] == 26 || world[i][j] == 27 || world[i][j] == 28 || world[i][j] == 29 || world[i][j] == 30 || world[i][j] == 31) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							coldetected = true;
						}
						if (left < CollRight) {
							coldetected = true;
						}
						if (top < CollBottom) {
							coldetected = true;
						}
						if (bottom > CollTop) {
							coldetected = true;
						}
						if (coldetected) break;
					}
				}
			}
		}
		return coldetected;
	}

	int chestCollision(sf::RectangleShape body) {
		int chestCollided = 0;
		bool coldetected = false;
		float bottom = body.getPosition().y + body.getSize().y + 16;
		float left = body.getPosition().x - 16;
		float right = body.getPosition().x + body.getSize().x + 16;
		float top = body.getPosition().y - 16;
		for (int i = 0; i < 91; i++)
		{
			for (int j = 0; j < 103; j++)
			{
				if (world[i][j] == 25) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 25;
						}
						if (left < CollRight) {
							chestCollided = 25;
						}
						if (top < CollBottom) {
							chestCollided = 25;
						}
						if (bottom > CollTop) {
							chestCollided = 25;
						}
						if (chestCollided) break;
					}
				}
				if (world[i][j] == 26) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 26;
						}
						if (left < CollRight) {
							chestCollided = 26;
						}
						if (top < CollBottom) {
							chestCollided = 26;
						}
						if (bottom > CollTop) {
							chestCollided = 26;
						}
						if (chestCollided) break;
					}
				}
				if (world[i][j] == 27) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 27;
						}
						if (left < CollRight) {
							chestCollided = 27;
						}
						if (top < CollBottom) {
							chestCollided = 27;
						}
						if (bottom > CollTop) {
							chestCollided = 27;
						}
						if (chestCollided) break;
					}
				}
				if (world[i][j] == 28) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 28;
						}
						if (left < CollRight) {
							chestCollided = 28;
						}
						if (top < CollBottom) {
							chestCollided = 28;
						}
						if (bottom > CollTop) {
							chestCollided = 28;
						}
						if (chestCollided) break;
					}
				}
				if (world[i][j] == 29) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 29;
						}
						if (left < CollRight) {
							chestCollided = 29;
						}
						if (top < CollBottom) {
							chestCollided = 29;
						}
						if (bottom > CollTop) {
							chestCollided = 29;
						}
						if (chestCollided) break;
					}
				}
				if (world[i][j] == 30) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 30;
						}
						if (left < CollRight) {
							chestCollided = 30;
						}
						if (top < CollBottom) {
							chestCollided = 30;
						}
						if (bottom > CollTop) {
							chestCollided = 30;
						}
						if (chestCollided) break;
					}
				}
				if (world[i][j] == 31) {
					int CollBottom, CollRight, CollLeft, CollTop;
					CollBottom = i * 32 + 32;
					CollTop = i * 32;
					CollLeft = j * 32;
					CollRight = j * 32 + 32;

					if (right < CollLeft || left > CollRight || top > CollBottom || bottom < CollTop) {
						continue;
					}
					else {
						if (right > CollLeft) {
							chestCollided = 31;
						}
						if (left < CollRight) {
							chestCollided = 31;
						}
						if (top < CollBottom) {
							chestCollided = 31;
						}
						if (bottom > CollTop) {
							chestCollided = 31;
						}
						if (chestCollided) break;
					}
				}		
				
			}	
		}
		return chestCollided;
	}

	bool enemyCollision(sf::RectangleShape body1, sf::RectangleShape body2) {
		bool coldetected = false;

		if (body1.getGlobalBounds().intersects(body2.getGlobalBounds())) {
			coldetected = true;
		}
		return coldetected;
	}

};