#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class PowerUp :
    public GameObject
{
public:
	PowerUp();
	~PowerUp();
	void start();
	void update();
	void draw();
	void setPosition(int xPos, int yPos);
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;
	int speed;
};

