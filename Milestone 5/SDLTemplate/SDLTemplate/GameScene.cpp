#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new Background();
	this->addGameObject(background);

	player = new Player();
	this->addGameObject(player);

	currentSpawnTimer = 300;
	spawnTime = 300;
	points = 0;
	powerUpSpawnTime = (rand() % 240) + 120;
	currentPowerUpSpawnTimer = 180;
}

GameScene::~GameScene()
{
	delete player;
	delete enemy;
	delete background;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300;
	currentPowerUpSpawnTimer = 180;
	powerUpSpawnTime = (rand() % 240) + 120;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();

	drawText(15, 15, 255, 255, 204, TEXT_LEFT, "POINTS: %03d", points);
	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 50, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{
	Scene::update();
	
	spawnLogic();
	collisionLogic();
	explosionLifespan();
}

void GameScene::spawnLogic()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentPowerUpSpawnTimer > 0)
		currentPowerUpSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}

		currentSpawnTimer = spawnTime;
	}

	if (currentPowerUpSpawnTimer <= 0)
	{
		for (int i = 0; i < 1; i++)
		{
			drop();
			currentPowerUpSpawnTimer = powerUpSpawnTime;
			break;
		}
	}
}

void GameScene::collisionLogic()
{
	//Despawn enemies off screen
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPosY() > (SCREEN_HEIGHT + 50))
		{
			Enemy* EnemiesToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete EnemiesToErase;

			break;
		}

		if ((spawnedEnemies[i]->getPosX() > (SCREEN_WIDTH + 50)) || (spawnedEnemies[i]->getPosX() < (-50)))
		{
			Enemy* EnemiesToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete EnemiesToErase;

			break;
		}

	}

	//offscreen delete powerups
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		if (spawnedPowerUps[i]->getPosY() > (SCREEN_HEIGHT + 50))
		{
			PowerUp* PowerUpToErase = spawnedPowerUps[i];
			spawnedPowerUps.erase(spawnedPowerUps.begin() + i);
			delete PowerUpToErase;

			break;
		}
	}

	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		PowerUp* powerUp = spawnedPowerUps[i];

		int collision = checkCollision(
			player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
			powerUp->getPosX(), powerUp->getPosY(), powerUp->getWidth(), powerUp->getHeight()
		);

		//check collision between power up and player
		if (collision == 1)
		{
			despawnPowerUp(powerUp);
			player->getPowerUp();

			break;
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet != NULL)
		{
			//check if enemy bullet hit player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}

			//check if player bullet hit enemy
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)\
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPosX(), currentEnemy->getPosY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						explode(currentEnemy->getPosX(), currentEnemy->getPosY());
						despawnEnemy(currentEnemy);

						points++;
						//Despawn one at a time, might crash due to looping while deleting
						break;
					}
				}
			}
		}
	}
}

void GameScene::explosionLifespan()
{

	for (auto it = explosions.begin(); it != explosions.end();)
	{
		Explosion* explosion = *it;
		explosion->update(); // Update the explosion

		if (explosion->isExpired())
		{
			// remove the explosion if its lifespan has expired
			it = explosions.erase(it);
			delete explosion; 
		}
		else
		{
			++it;
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(100 + (rand() % 400), -50);
	spawnedEnemies.push_back(enemy);
}

void GameScene::explode(int x, int y)
{
	Explosion* explosion = new Explosion();
	this->addGameObject(explosion);
	explosion->setPosition(x, y);
	explosion->setLifespan(15);

	explosions.push_back(explosion);
}

void GameScene::drop()
{
	PowerUp* powerup = new PowerUp();
	this->addGameObject(powerup);
	powerup->setPosition(50 + (rand() % 350), -50);

	spawnedPowerUps.push_back(powerup);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::despawnPowerUp(PowerUp* powerup)
{
	int index = -1;
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		if (powerup == spawnedPowerUps[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
		delete enemy;
	}
}