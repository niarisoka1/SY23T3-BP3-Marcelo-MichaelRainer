#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");

	directionX = 1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 3;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::update()
{
	y += directionY * speed;
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

void PowerUp::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int PowerUp::getPosX()
{
	return x;
}

int PowerUp::getPosY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}
