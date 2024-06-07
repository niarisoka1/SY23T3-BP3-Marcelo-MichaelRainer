#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "text.h"
#include "draw.h"
#include "Explosion.h"
#include <vector>

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;
	Background* background;

	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Explosion*> explosions;

	void spawnLogic();
	void collisionLogic();
	void explosionLifespan();

	void spawn();
	void explode(int x, int y);
	void despawnEnemy(Enemy* enemy);

	int points;
};

