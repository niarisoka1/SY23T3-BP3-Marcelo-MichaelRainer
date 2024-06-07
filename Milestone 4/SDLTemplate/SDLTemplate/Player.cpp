#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// This delete all bullets when the player dies
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	x = (SCREEN_WIDTH / 2) - 15;
	y = 850;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8;
	currentReloadTime = 0;
	altReloadTime = 48;
	altCurrentReloadTime = 0;
	isAlive = true;

	// Sets width n height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Laser sounds called and loaded
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	// This delete bullets that are off the game screen
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 6;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 3;
	}

	// Im too lazy to take my hand off my mouse :3
	if (app.keyboard[SDL_SCANCODE_SPACE])
	{
		speed = 3;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (altCurrentReloadTime > 0)
		altCurrentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 4 + height / 2, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && altCurrentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 12, y - 2, 0, -1, 25, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		Bullet* bullet2 = new Bullet(x + 12, y - 2 + height, 0, -1, 25, Side::PLAYER_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);

		bullet->start();
		bullet2->start();

		altCurrentReloadTime = altReloadTime;
	}
}

void Player::draw()
{
	if (!isAlive) return;
	blit(texture, x, y); 
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}
