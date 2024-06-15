#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"
#include "SoundManager.h"
#include "util.h"

class Explosion :
    public GameObject
{
public:
	void start();
	void update();
	void draw();
	void setPosition(int xPos, int yPos);
	void setLifespan(int ms);
	bool isExpired() const;
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;
	int width;
	int height;
	int lifespan;
};

