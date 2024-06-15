#include "Explosion.h"

void Explosion::start()
{
	texture = loadTexture("gfx/explosion.png");

	x = 0;
	y = 0;
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound->volume = 1;
}

void Explosion::update()
{
	SoundManager::playSound(sound);

	if (lifespan > 0)
	{
		lifespan--;
	}
}

void Explosion::draw()
{
	blit(texture, x, y);
}

void Explosion::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

void Explosion::setLifespan(int ms)
{
	lifespan = ms;
}

bool Explosion::isExpired() const
{
	return lifespan <= 0;
}

